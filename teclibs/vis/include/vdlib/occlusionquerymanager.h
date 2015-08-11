/**
*	Manage sending and retrieving occlusion queries to/from OpenGL.
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	author: Vitor Barata <vbarata@tecgraf.puc-rio.br>
*	date:   10-Mar-2008
*/
#ifndef _VDLIB_OCCLUSIONQUERYMANAGER_H_
#define _VDLIB_OCCLUSIONQUERYMANAGER_H_

#include <GL/glew.h>
#include <vrbv/treebuilder.h>
#include <vdlib/opengl.h>
#include <vdlib/common.h>
#include <deque>
#include <vector>
#include <queue>

namespace vdlib {

class OcclusionQueryManager
{
public:
	// Constructor and destructor
	OcclusionQueryManager();
	~OcclusionQueryManager();

	// Cleanup memory (must be called with a valid OpenGL context)
	void cleanup();

	// Enable/disable color and depth writes if necessary (bounding-box queries only)
	void setQueriesEnabled( bool state );

	// Normal Query
	void beginQuery( vrbv::Node* node );
	void endQuery();

	// Multiquery
	void beginMultiQuery( int nodecount, std::deque<vrbv::Node*> &nodevector );
	void endMultiQuery();

	// Any queries left processing?
	bool done() const;

	// Front node represents oldest issued query
	unsigned int getFrontNodeCount();
	vrbv::Node* getFrontNode();
	void popFrontNode();
	bool frontResultAvailable() const;
	unsigned int getFrontResult();
	void popFrontResult();

	// Debug
	void ResetDebugCounters();
	void PrintDebugCounters();

private:
	struct QueryInfo {
		GLuint id;
		unsigned int nodecount;
	};

private:
	GLuint getFreeQueryID();

private:
	std::vector<GLuint> _queryIds;            // Pool of free query IDs
	std::queue<vrbv::Node*> _queryQueueNodes; // Query queue: contains every queried node
	std::queue<QueryInfo> _queryQueueInfos;   // Query queue: contains each queued query id and its node count
	bool _queriesEnabled;                     // Are queries currently enabled?
	int _numQueries;                          // Debug: Total number of issued queries
	int _numStateChanges;                     // Debug: Total number of state changes
};

} // namespace vdlib

#endif // _VDLIB_OCCLUSIONQUERYMANAGER_H_
