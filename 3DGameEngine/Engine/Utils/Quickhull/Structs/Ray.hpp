#ifndef QuickHull_Ray_hpp
#define QuickHull_Ray_hpp

#include "3DMath/3DMath.h"

namespace quickhull {

	template <typename T>
	struct Ray {
		const math::Vector3 m_S;
		const math::Vector3 m_V;
		const T m_VInvLengthSquared;
		
		Ray(const math::Vector3& S,const math::Vector3& V) : m_S(S), m_V(V), m_VInvLengthSquared(1/math::lengthSq(m_V)) {
		}
	};
	
}


#endif
