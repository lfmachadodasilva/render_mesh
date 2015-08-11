/*****************************************************************************\
*
* $Header: /home/t/tecgraf/prod/lib/vis/src/ds/graph.h,v 1.2 2010-08-17 20:40:38 fabraham Exp $
* sam@tecgraf.puc-rio.br
*
\*****************************************************************************/

#ifndef _GRAPH_TEMPLATE_H_
#define _GRAPH_TEMPLATE_H_

#include <cstdio>
#include <cassert>
#include <map>
#include <vector>
#include <set>


namespace gph
{
	enum color { white, gray, black }; 

	typedef unsigned int VertexHandle;
	typedef unsigned int EdgeHandle;

	template <typename VertexProperty, typename EdgeProperty> class Graph
	{
	protected:
		class Vertex;
		class Edge;

		typedef std::vector<Vertex*> VertexVector;
		typedef std::set<VertexHandle> VertexSet;
		typedef typename std::set<VertexHandle>::iterator VertexSetIterator;

		typedef std::map<VertexHandle, EdgeHandle> EdgeMap;
		typedef std::vector<Edge*> EdgeVector;
		typedef std::set<EdgeHandle> EdgeSet;
		typedef typename std::map<VertexHandle, EdgeHandle>::iterator EdgeMapIterator;
		typedef typename std::set<EdgeHandle>::iterator EdgeSetIterator;

		unsigned int _nVertices;
		unsigned int _nEdges;

		unsigned int _lastVertexHandle;
		unsigned int _lastEdgeHandle;

		struct Vertex
		{
			EdgeMap in;
			EdgeMap out;
			VertexHandle handle;
			VertexProperty property;
		};

		struct Edge
		{
			Vertex* src;
			Vertex* tgt;
			EdgeHandle handle;
			EdgeProperty property;
		};

		VertexVector _vertexVector;
		VertexSet _vertexSet;
		
		EdgeVector _edgeVector;
		EdgeSet _edgeSet;
	
	public:

		class EdgeIterator
		{
		public:
			EdgeIterator() {}
			EdgeIterator(EdgeSetIterator i) { _itr = i; }
			EdgeIterator operator++() { return _itr++; }
			EdgeHandle operator*() { return *_itr; }
			EdgeIterator& operator=(const EdgeIterator& i) { _itr = i._itr; return *this; }
			bool operator==(const EdgeIterator& a) { return a._itr == _itr; }
			bool operator!=(const EdgeIterator& a)	{ return a._itr != _itr; }
		private:
			 EdgeSetIterator _itr;
		};

		class IncidentEdgeIterator
		{
		public:
			IncidentEdgeIterator() {}
			IncidentEdgeIterator(EdgeMapIterator i) { _itr = i; }
			IncidentEdgeIterator operator++() { return _itr++; }
			EdgeHandle operator*() { return (*_itr).second; }
			IncidentEdgeIterator& operator=(const IncidentEdgeIterator& i) { _itr = i._itr; return *this; }
			bool operator==(const IncidentEdgeIterator& a) { return a._itr == _itr; }
			bool operator!=(const IncidentEdgeIterator& a)	{ return a._itr != _itr; }
		private:
			EdgeMapIterator _itr;
		};

		class VertexIterator
		{
		public:
			VertexIterator() {}
			VertexIterator(VertexSetIterator i) { _itr = i; }
			VertexIterator operator++() { return _itr++; }
			VertexHandle operator*() { return *_itr; }
			VertexIterator& operator=(const VertexIterator& i) { _itr = i._itr; return *this; }
			bool operator==(const VertexIterator& a) { return a._itr == _itr; }
			bool operator!=(const VertexIterator& a)	{ return a._itr != _itr; }
		private:
			VertexSetIterator _itr;
		};
				
		Graph()
		{
			_lastVertexHandle = 0;
			_lastEdgeHandle = 0;

			_nVertices = 0;
			_nEdges = 0;

			_vertexVector.push_back(new Vertex);
			_edgeVector.push_back(NULL);
		}

		virtual ~Graph()
		{			
			clear();
		}

		void clear(void)
		{
			clearEdges();
			clearVertices();
		}

		unsigned int vertices(void) 
		{ 
			return _nVertices; 
		}

		unsigned int edges(void) 
		{ 
			return _nEdges; 
		}

		int edges(VertexHandle v) 
		{ 
			return inEdges(v) + outEdges(v); 
		}

		int inEdges(VertexHandle v) 
		{ 
			std::pair<Vertex*, bool> tmp = getVertex(v);
			if(tmp.second)
				return tmp.first->in.size();
			return 0; 
		}

		int outEdges(VertexHandle v) 
		{ 
			std::pair<Vertex*, bool> tmp = getVertex(v);
			if(tmp.second)
				return tmp.first->out.size();
			return 0;
		}

		unsigned int lastVertexHandle(void) 
		{ 
			return _lastVertexHandle; 
		}

		unsigned int lastEdgeHandle(void) 
		{ 
			return _lastEdgeHandle; 
		}

		VertexHandle addVertex(VertexProperty p)
		{
			Vertex* tmp = new Vertex;
			
			tmp->handle = ++_lastVertexHandle;
			tmp->property = p;
			
			_nVertices++;

			_vertexVector.push_back(tmp);

			if(_vertexSet.insert(_lastVertexHandle).second == false)
				assert(0);

			return _lastVertexHandle;
		}

		EdgeHandle addEdge(VertexHandle src, VertexHandle tgt, EdgeProperty p)
		{
			std::pair<EdgeHandle, bool> e = edge(src, tgt);

			if(e.second)
				return 0;

			std::pair<Vertex*, bool> s = getVertex(src);
			std::pair<Vertex*, bool> t = getVertex(tgt);

			if(s.second == false || t.second == false)
				return 0;

			Edge* tmp = new Edge;
			tmp->src = s.first;
			tmp->tgt = t.first;
			tmp->property = p;
			tmp->handle = ++_lastEdgeHandle;

			_edgeVector.push_back(tmp);

			bool sinsert, tinsert, minsert;
			sinsert = s.first->out.insert(std::make_pair(t.first->handle, _lastEdgeHandle)).second;
			tinsert = t.first->in.insert(std::make_pair(s.first->handle, _lastEdgeHandle)).second;
			minsert = _edgeSet.insert(_lastEdgeHandle).second;
			assert(sinsert && tinsert && minsert);
			
			_nEdges++;

			return _lastEdgeHandle;
		}

		bool removeEdge(EdgeHandle e)
		{
			std::pair<Edge*, bool> tmp = getEdge(e);

			if(tmp.second)
			{
				tmp.first->src->out.erase(tmp.first->tgt->handle);
				tmp.first->tgt->in.erase(tmp.first->src->handle);
				_edgeSet.erase(e);

				delete _edgeVector[e];
				_edgeVector[e] = NULL;

				_nEdges--;

				return true;
			}

			return false;
		}

		void removeInEdges(VertexHandle v)
		{
			for(IncidentEdgeIterator i = inBegin(v); i != inEnd(v); )
			{
				IncidentEdgeIterator tmp = i;
				++i;
				removeEdge(*tmp);
			}
		}

		void removeOutEdges(VertexHandle v)
		{
			for(IncidentEdgeIterator i = outBegin(v); i != outEnd(v); )
			{
				IncidentEdgeIterator tmp = i;
				++i;
				removeEdge(*tmp);
			}
		}

		void removeEdges(VertexHandle v)
		{
			removeInEdges(v);
			removeOutEdges(v);
		}

		bool removeVertex(VertexHandle v)
		{
			std::pair<Vertex*, bool> tmp = getVertex(v);

			if(tmp.second)
			{
				removeEdges(v);

				_vertexSet.erase(v);
				delete _vertexVector[v];
				_vertexVector[v] = NULL;

				_nVertices--;

				return true;
			}

			return false;
		}

		IncidentEdgeIterator inBegin(VertexHandle v)
		{
			std::pair<Vertex*, bool> tmp = getVertex(v);
			if(tmp.second)
				return IncidentEdgeIterator(_vertexVector[v]->in.begin());
			return inEnd(v);
		}

		IncidentEdgeIterator inEnd(VertexHandle v)
		{
			std::pair<Vertex*, bool> tmp = getVertex(v);
			if(tmp.second)
				return IncidentEdgeIterator(_vertexVector[v]->in.end());
			return IncidentEdgeIterator(_vertexVector[0]->in.end());
		}

		IncidentEdgeIterator outBegin(VertexHandle v)
		{
			std::pair<Vertex*, bool> tmp = getVertex(v);
			if(tmp.second)
				return IncidentEdgeIterator(_vertexVector[v]->out.begin());
			return outEnd(v);
		}

		IncidentEdgeIterator outEnd(VertexHandle v)
		{
			std::pair<Vertex*, bool> tmp = getVertex(v);
			if(tmp.second)
				return IncidentEdgeIterator(_vertexVector[v]->out.end());
			return IncidentEdgeIterator(_vertexVector[0]->out.end());
		}

		VertexIterator vertexBegin(void) 
		{ 
			return VertexIterator(_vertexSet.begin()); 
		}

		VertexIterator vertexEnd(void) 
		{ 
			return VertexIterator(_vertexSet.end()); 
		}

		EdgeIterator edgeBegin(void) 
		{ 
			return EdgeIterator(_edgeSet.begin()); 
		}

		EdgeIterator edgeEnd(void) 
		{ 
			return EdgeIterator(_edgeSet.end()); 
		}

		std::pair<EdgeProperty, bool> edgeProperty(EdgeHandle e)
		{
			std::pair<Edge*, bool> tmp = getEdge(e);
			if(tmp.second)
				return std::make_pair(tmp.first->property, true);
			return std::make_pair(EdgeProperty(), false);
		}

		std::pair<VertexProperty, bool> vertexProperty(VertexHandle v)
		{
			std::pair<Vertex*, bool> tmp = getVertex(v);
			if(tmp.second)
				return std::make_pair(tmp.first->property, true);
			return std::make_pair(VertexProperty(), false);
		}

		VertexHandle source(EdgeHandle e)
		{
			std::pair<Edge*, bool> tmp = getEdge(e);
			if(tmp.second)
				return tmp.first->src->handle;
			return 0;
		}

		VertexHandle target(EdgeHandle e)
		{
			std::pair<Edge*, bool> tmp = getEdge(e);
			if(tmp.second)
				return tmp.first->tgt->handle;
			return 0;
		}

		std::pair<EdgeHandle, bool> edge(VertexHandle s, VertexHandle t)
		{
			std::pair<Vertex*, bool> tmp = getVertex(s);
			if(tmp.second)
			{
				EdgeMapIterator i = tmp.first->out.find(t);
				if(i != tmp.first->out.end())
					return std::make_pair((*i).second, true);
			}
			return std::make_pair(0, false);
		}

	protected:

		std::pair<Vertex*, bool> getVertex(VertexHandle v)
		{
			if(v > 0 && v <= _lastVertexHandle && _vertexVector[v] != NULL)
				return std::make_pair(_vertexVector[v], true);
			else
				return std::make_pair((Vertex*)0, false);
		}

		std::pair<Edge*, bool> getEdge(EdgeHandle e)
		{
			if(e > 0 && e <= _lastEdgeHandle && _edgeVector[e] != NULL)
				return std::make_pair(_edgeVector[e], true);
			else
				return std::make_pair((Edge*)0, false);
		}

		void clearVertices(void)
		{
			VertexSetIterator i;
			for(i = _vertexSet.begin(); i != _vertexSet.end(); )
			{
				VertexSetIterator tmp = i;
				++i;
				removeVertex(*tmp);
			}
		}

		void clearEdges(void)
		{
			VertexSetIterator i;
			for(i = _vertexSet.begin(); i != _vertexSet.end(); ++i)
				removeEdges(*i);
		}

	};

};

#endif
