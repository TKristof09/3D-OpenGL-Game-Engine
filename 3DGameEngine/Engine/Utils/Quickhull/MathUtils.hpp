
#ifndef QuickHull_MathUtils_hpp
#define QuickHull_MathUtils_hpp

#include "Structs/Ray.hpp"

namespace quickhull {
	
	namespace mathutils {
		
		template <typename T>
		inline T getSquaredDistanceBetweenPointAndRay(const math::Vector3& p, const Ray<T>& r) {
			const math::Vector3 s = p-r.m_S;
			T t = math::dot(s, r.m_V);
			return math::lengthSq(s) - t*t*r.m_VInvLengthSquared;
		}
		
		// Note that the unit of distance returned is relative to plane's normal's length (divide by N.getNormalized() if needed to get the "real" distance).
		template <typename T>
		inline T getSignedDistanceToPlane(const math::Vector3& v, const Plane<T>& p) {
			return math::dot(p.m_N, v) + p.m_D;
		}
		
		
		inline math::Vector3 getTriangleNormal(const math::Vector3& a,const math::Vector3& b,const math::Vector3& c) {
			// We want to get (a-c).crossProduct(b-c) without constructing temp vectors
			float x = a.x - c.x;
			float y = a.y - c.y;
			float z = a.z - c.z;
			float rhsx = b.x - c.x;
			float rhsy = b.y - c.y;
			float rhsz = b.z - c.z;
			float px = y * rhsz - z * rhsy ;
			float py = z * rhsx - x * rhsz ;
			float pz = x * rhsy - y * rhsx ;
			return math::Vector3(px,py,pz);
		}
		
		
	}
	
}


#endif
