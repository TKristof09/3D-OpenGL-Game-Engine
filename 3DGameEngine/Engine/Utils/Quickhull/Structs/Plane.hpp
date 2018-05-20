/*
 * Plane.hpp
 *
 *  Created on: Dec 7, 2013
 *      Author: anttiku
 */

#ifndef QHPLANE_HPP_
#define QHPLANE_HPP_

#include "3DMath/3DMath.h"
#include "VertexDataSource.hpp"

namespace quickhull {

	template<typename T>
	class Plane {
	public:
		math::Vector3 m_N;
		
		// Signed distance (if normal is of length 1) to the plane from origin
		T m_D;
		
		// Normal length squared
		T m_sqrNLength;

		bool isPointOnPositiveSide(const math::Vector3& Q) const {
			T d = math::dot(m_N, Q)+m_D;
			if (d>=0) return true;
			return false;
		}

		Plane() = default;

		// Construct a plane using normal N and any point P on the plane
		Plane(const math::Vector3& N, const math::Vector3& P) : m_N(N), m_D(math::dot(math::Vector3(-N.x, -N.y,-N.z), P)), m_sqrNLength(m_N.x*m_N.x+m_N.y*m_N.y+m_N.z*m_N.z) {
			
		}
	};

}


#endif /* PLANE_HPP_ */
