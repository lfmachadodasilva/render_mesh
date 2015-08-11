/**
 * Class with callbacks to access vertices in a geometryinfo 
 * when using pointers rather than storing vertices' coordinates 
 * explicitly.
 * author: Cesar Palomo <cpalomo@tecgraf.puc-rio.br>
 * date:   11-Jun-2010
*/
#ifndef GEOMINFO_CB_H
#define GEOMINFO_CB_H

#include <string.h>
#include <cassert>
#include <iterator>
#include <cstdlib>
#include "defines.h"

namespace vrbv {

class VRBV_API GeomInfoCallback
{
public:

	/** Default constructor. */
	GeomInfoCallback ();

	/** 
	 * Set callback for retrieving vertices coordinates given a geometryinfo id.
	 * @param 1: cb
	 * @param 2: reference to class to resolve cb, if necessary.
	 * Callback param 1: return parameter: vertices coordinates.
	 * Callback param 2: geometryinfo id.
	 * Callback param 3: reference to class to resolve cb, if necessary.
	 * Callback return: return parameter: number of vertices returned.
	 */
	void SetVertexCoordsCB (int (*GetVertexCoordsCB) (float** coords, int, void*),
	                        void* getVertextCoordsCB_data);

	/** 
	 * Invoke callback that retrieves vertices coordinates given a geometryinfo id.
	 * @param coords return parameter with vertex coordinates.
	 * @param geometryinfo_id geometryinfo id.
	 * @return number of vertices for geominfo.
	 */
  int GetVertexCoords (float** coords, int geominfo_id) const
  {
    return m_GetVertexCoordsCB(coords,
                               geominfo_id,
                               m_GetVertexCoordsCB_data);
  }

private:
	int (*m_GetVertexCoordsCB) (float** coords, int, void*);
	void* m_GetVertexCoordsCB_data;

public:
	class CoordsIterator : public std::iterator<std::input_iterator_tag, float*>
	{
		float* m_vertex_coords;
		float* m_coords;
		int* m_geominfo_ids;
		int m_geominfo_ids_count;
		int m_geominfo_i;
		int m_vertex_count;
		int m_vertex_i;
		bool m_ended;
		GeomInfoCallback* m_cb;
	public:
		CoordsIterator (int id, 
		                GeomInfoCallback* cb) 
		{
			m_geominfo_ids = &id;
			m_geominfo_ids_count = 1;
			m_cb = cb;
			m_coords = m_vertex_coords = NULL;
			First();
		}
		CoordsIterator (int* geominfo_ids, 
		                int geominfo_ids_count, 
		                GeomInfoCallback* cb) 
		{
			assert(geominfo_ids_count > 0);
			m_geominfo_ids = geominfo_ids;
			m_geominfo_ids_count = geominfo_ids_count;
			m_cb = cb;
			m_coords = m_vertex_coords = NULL;
			First();
		}
		CoordsIterator (const CoordsIterator& mit)
			: m_vertex_coords(mit.m_vertex_coords)
			, m_coords(mit.m_coords)
			, m_geominfo_ids(mit.m_geominfo_ids)
			, m_geominfo_ids_count(mit.m_geominfo_ids_count)
			, m_geominfo_i(mit.m_geominfo_i)
			, m_vertex_count(mit.m_vertex_count)
			, m_vertex_i(mit.m_vertex_i)
			, m_ended(mit.m_ended)
			, m_cb(mit.m_cb)
		{
		}
		~CoordsIterator ()
		{
			free(m_coords);
		}
		void First ()
		{
			m_geominfo_i = -1;
			m_vertex_count = 0;
			m_vertex_i = -1;
			m_ended = false;
			Next();
		}
		void Next ()
		{
			// go to next vertex
			m_vertex_i++;
	
			if (m_vertex_i < m_vertex_count)
				m_vertex_coords += 3;
			else {
				// test each geometry info from current
				m_vertex_count = 0;
				while (m_vertex_count == 0 && m_geominfo_i+1 < m_geominfo_ids_count) {
					m_geominfo_i++;
					int id = m_geominfo_ids[m_geominfo_i];
					m_vertex_count = m_cb->GetVertexCoords(&m_coords, id);
				}

				// any geometry info found with vertices?
				if (m_vertex_count > 0) {
					m_vertex_i = 0;
					m_vertex_coords = m_coords;
				}
				else
					m_ended = true;
			}
		}
		CoordsIterator& operator++()
		{
			// read next vertex' coordinates
			Next();
			return *this;
		}
		CoordsIterator& operator++(int)
		{
			// read next vertex' coordinates
			Next();
			return *this;
		}
		bool operator==(const CoordsIterator& rhs) 
		{
			return 
				m_geominfo_ids == rhs.m_geominfo_ids &&
				m_geominfo_ids_count == rhs.m_geominfo_ids_count &&
				m_geominfo_i == rhs.m_geominfo_i &&
				m_vertex_count == rhs.m_vertex_count &&
				m_vertex_i == rhs.m_vertex_i &&
				m_ended == rhs.m_ended &&
				m_cb == rhs.m_cb &&
				m_vertex_coords == rhs.m_vertex_coords &&
				m_coords == rhs.m_coords;
		}
		bool operator!=(const CoordsIterator& rhs) 
		{
			return !(*this == rhs);
		}
		bool end()
		{
			return m_ended;
		}
		const float* operator*()
		{
			return m_vertex_coords;
		}
	};

};

} // namespace vrbv

#endif // GEOMINFO_CB_H
