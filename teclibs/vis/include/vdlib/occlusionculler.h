/**
*	Implements Coherent Hierarchical Culling algorithm.
*	See "Coherent Hierarchical Culling: Hardware Occlusion Queries Made Useful"
*		Jiri Bittner, Michael Wimmer, Harald Piringer, Werner Purgathofer
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	date:   10-Mar-2008
*
*	See also "CHC++: Coherent Hierarchical Culling Revisited"
*		Oliver Mattausch, Jiri Bittner, Michael Wimmer
*	author: Vitor Barata <vbarata@tecgraf.puc-rio.br>
*	date:   01-Out-2010
*/
#ifndef _VDLIB_OCCLUSIONCULLER_H_
#define _VDLIB_OCCLUSIONCULLER_H_

#include <vrbv/common.h>
#include <vrbv/plane.h>
#include <vrbv/node.h>
#include <vrbv/treebuilder.h>
#include <vr/Platform.h>
#include <vdlib/common.h>
#include <vdlib/occlusionquerymanager.h>
#include <queue>

namespace vdlib {

// Callback used to determine valid nodes to visit and rendering notification to client
class IOcclusionCallback
{
public:
	typedef std::deque<vrbv::Node*> NodeBatch;
	typedef NodeBatch::const_iterator NodeIterator;

public:
	virtual ~IOcclusionCallback ()
	{
	}
	// Called whenever a node batch should be rendered.
	virtual void draw( const NodeBatch& nodebatch )
	{
		for ( NodeIterator it = nodebatch.begin(); it != nodebatch.end(); ++it )
			draw( *it );
	}

	// Called whenever a node should be rendered.
	virtual void draw( vrbv::Node* node ) {}

	// Called for every visited node during traversal.
	// Determine whether the node should be traversed or not (i.e. frustum culling).
	virtual bool isValid( vrbv::Node* node ) { return true; }

	// Called to see if an internal node must be drawn (as if it was a leaf node).
	// Traversal stops at this node.
  virtual bool isDrawable( vrbv::Node* node ) { return node->isLeaf(); }
};

// Warning: assumes node ids are consecutive and start with zero (TreeBuilder guarantees this).
// Node bounding volumes must be defined in World Space
class OcclusionCuller
{
public:
	// Constructor and destructor
	OcclusionCuller();
	~OcclusionCuller();

	// Reallocate occlusion information for all nodes
	void init( const vrbv::TreeBuilder::Statistics& stats );

	// Cleanup memory (must be called with a valid OpenGL context)
	void cleanup();

	// Viewing information needs to be updated whenever camera changes
	void updateViewerParameters( const float* viewMatrix, const float* projectionMatrix );

	// Viewing information needs to be updated whenever camera changes.
	// Use this method if these parameters are readily available.
	// Use the other method if not.
	void updateViewerParametersVP( const float* viewProjMatrix, const float viewPoint[3] );

	// Minimum resulting pixels required for a geometry to be considered "visible"
	void setVisibilityThreshold( unsigned int numPixels );
	unsigned int getVisibilityThreshold() const;

	// Minimum frames that need to pass for a query to be repeated on a visible object (CHC++)
	void setQueryInterval( unsigned int numFrames );
	unsigned int getQueryInterval() const;

	// Use of query batches for invisible nodes (CHC++)
	void setMaxIBatchSize( unsigned int size );
	unsigned int getMaxIBatchSize() const;

	// Use of query batches for visible nodes (CHC++)
	void setMaxVBatchSize( unsigned int size );
	unsigned int getMaxVBatchSize() const;

	// Use of rendering batches (CHC++)
	void setUseRBatches( bool state );
	bool getUseRBatches() const;

	// Use of multiqueries for invisible nodes (CHC++)
	void setUseMultiqueries( bool state );
	bool getUseMultiqueries() const;

	// Tight Bounding Box Maximum Depth (CHC++)
	void setTightBBoxMaxDepth( unsigned int depth );
	unsigned int getTightBBoxMaxDepth() const;

	// Tight Bounding Box Area Factor (CHC++)
	void setTightBBoxAreaFactor( float factor );
	float getTightBBoxAreaFactor() const;

	// Returns whether a node was rendered on the last frame
	bool wasRendered( Node* node ) const;

	// Traverse hierarchy performing occlusion culling.
	// If traverse is to be called more than once each frame,
	// pass 'traversal_index'.
	void traverse( vrbv::Node* node,
	               IOcclusionCallback* callback,
	               int traversal_index = 0 );

private:
	// Store per-node occlusion information
	class OcclusionInfo
	{
	public:
		OcclusionInfo()
		: lastVisited( -1 )
		, lastRendered( -1 )
		, nextQuery( 0 )
		, tightbboxdepth( -1 )
		, wasVisible( false )
		, isVisible( false )
		, distanceToViewpoint( 0.0f )
		{
		}

		int   lastVisited;          // Last time node was visited during traversal
		int   lastRendered;         // Last time node was rendered
		int   nextQuery;            // Next time node will be queried for occlusion if it remains visible
		int   tightbboxdepth;       // Children depth to use for tight bounding box
		bool  wasVisible;           // Last frame's visibility information
		bool  isVisible;            // This frame's visibility information
		float distanceToViewpoint;  // This frame's distance to viewpoint
	};
	typedef std::vector<OcclusionInfo> OcclusionInfoVector;

	// Predicate for ordering traversal of Nodes from closest to viewpoint to farthest.
	// For use in a priority queue, where the top element has greater priority than all others.
	class ClosestToViewpoint
	{
	public:
		ClosestToViewpoint( const OcclusionInfoVector& info )
		: _info( info )
		{
			// empty
		}

		// Predicate operator for sorting
		VR_FORCEINLINE bool operator()( const vrbv::Node* first, const vrbv::Node* second ) const
		{
			return _info[first->getId()].distanceToViewpoint > _info[second->getId()].distanceToViewpoint;
		}

	private:
		const OcclusionInfoVector& _info;		
	};

	// Predicate for ordering Nodes from highest visibility persistence to lowest.
	// For use in the sort algorithm call for the i-batch multiqueries
	class HighestVisibilityPersistence
	{
	public:
		HighestVisibilityPersistence( const OcclusionInfoVector& info )
		: _info( info )
		{
			// empty
		}

		// Predicate operator for sorting
		VR_FORCEINLINE bool operator()( const vrbv::Node* first, const vrbv::Node* second ) const
		{
			return _info[first->getId()].lastRendered < _info[second->getId()].lastRendered;
		}

	private:
		const OcclusionInfoVector& _info;    
	};

private:

	void traverseNode( vrbv::Node* node );
	void drawBoundingBox( vrbv::Node* node );
	void drawBoundingBox( vrbv::Node* node, int depth );
	int getTightBBoxDepth( vrbv::Node* node );

	void addNodeToVBatch( vrbv::Node* node );
	void addNodeToIBatch( vrbv::Node* node );
	void addNodeToRBatch( vrbv::Node* node );

	void processVBatch();
	void processIBatch();
	void processRBatch();
	void processMultiquery();
	void processFailedMultiquery( unsigned int nodecount );
	void processGeometryQuery( vrbv::Node* node );

	void getNextQueryResult( bool forced );
	int getNextMultiQueryCount();

	// Push children to distance queue
	void pushChildren( vrbv::Node* node );

	// Update ancestors visibility
	void pullUpVisibility( vrbv::Node* node );

	// Debug
	void ResetDebugCounters();
	void PrintDebugCounters();

private:

	// Viewing information
	vr::Vec3f _viewpoint;
	vrbv::Plane _nearPlane;

	// Occlusion information
	float _tightBBoxAreaFactor;
	unsigned int _tightBBoxMaxDepth;
	unsigned int _visibilityThreshold;
	unsigned int _queryInterval;
	unsigned int _maxSizeIBatch;
	unsigned int _maxSizeVBatch;
	bool _useMultiQueries;
	bool _useRBatch;

	OcclusionInfoVector _occlusionInfo;
	OcclusionQueryManager _queryManager;

	// Priority queue for front-to-back traversal
	typedef std::priority_queue<vrbv::Node*, std::vector<vrbv::Node*>, ClosestToViewpoint> DistanceQueue;

	// Query batch (CHC++)
	typedef std::deque<vrbv::Node*> NodeBatch;

	IOcclusionCallback* _callback;
	DistanceQueue _distanceQueue;
	NodeBatch _ibatch;
	NodeBatch _vbatch;
	NodeBatch _rbatch;
	int _frameId;

	// Debug
	int _numFrustumCulled;
	int _numRendered;
	int _numStalls;
};

} // namespace vdlib

#endif // _VDLIB_OCCLUSIONCULLER_H_
