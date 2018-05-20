//
//  VertexDataSource.hpp
//  QuickHull
//
//  Created by Antti Kuukka on 1/5/16.
//  Copyright © 2016 Antti Kuukka. All rights reserved.
//

#ifndef VertexDataSource_h
#define VertexDataSource_h

#include "3DMath/3DMath.h"

namespace quickhull {
	
	template<typename T>
	class VertexDataSource {
		const math::Vector3* m_ptr;
		std::size_t m_count;
	
	public:
		VertexDataSource(const math::Vector3* ptr, std::size_t count) : m_ptr(ptr), m_count(count) {
			
		}
		
		VertexDataSource(const std::vector<math::Vector3>& vec) : m_ptr(&vec[0]), m_count(vec.size()) {
			
		}
		
		VertexDataSource() : m_ptr(nullptr), m_count(0) {
			
		}
		
		VertexDataSource& operator=(const VertexDataSource& other) = default;
		
		std::size_t size() const {
			return m_count;
		}
		
		const math::Vector3& operator[](std::size_t index) const {
			return m_ptr[index];
		}
		
		const math::Vector3* begin() const {
			return m_ptr;
		}
		
		const math::Vector3* end() const {
			return m_ptr + m_count;
		}
	};
	
}


#endif /* VertexDataSource_h */
