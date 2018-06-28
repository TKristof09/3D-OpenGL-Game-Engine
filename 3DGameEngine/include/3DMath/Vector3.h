#ifndef VECTOR3_H
#define VECTOR3_H
#include <cassert>
#include <cassert>
#include "LinearMath/btVector3.h"

namespace math
{
	template <unsigned int L, typename T>
	struct vec;

	template <typename T>
	struct vec<3, T>
	{
		vec()
		{
            vec(0);
		}

		vec(T _s)
		{
			x = _s;
			y = _s;
			z = _s;
		}

		vec(const vec<2, T>& v, T _z)
		{
			x = v.x;
			y = v.y;
			z = _z;
		}

		vec(const vec<4, T>& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}

		vec(T _x, T _y, T _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		vec(const btVector3& v)
		{
			x = v.x();
			y = v.y();
			z = v.z();
		}

		union
		{
			struct
			{
				T x, y, z;
			};

			struct
			{
				T r, g, b;
			};

			struct
			{
				T v[3];
			};
		};

		T& operator[](unsigned int i)
		{
			assert(i <= 3);
			return v[i];
		}

		T operator[](unsigned int i) const
		{
			assert(i <= 3);
			return v[i];
		}

		template <typename U>
		vec<3, T>& operator+=(const vec<3, U>& v);
		template <typename U>
		vec<3, T>& operator-=(const vec<3, U>& v);
		template <typename U>
		vec<3, T>& operator*=(const vec<3, U>& v);

		template <typename U>
		bool operator!=(const vec<3, U>& v) const;

		btVector3 ToBtVector3() const
		{
			return btVector3(x, y, z);
		}
	};


	
	static vec<3, float> pointsOnUnitSphere[] = {
		vec<3, float>(0.000000f, -0.000000f, -1.000000f),
		vec<3, float>(0.723608f, -0.525725f, -0.447219f),
		vec<3, float>(-0.276388f, -0.850649f, -0.447219f),
		vec<3, float>(-0.894426f, -0.000000f, -0.447216f),
		vec<3, float>(-0.276388f, 0.850649f, -0.447220f),
		vec<3, float>(0.723608f, 0.525725f, -0.447219f),
		vec<3, float>(0.276388f, -0.850649f, 0.447220f),
		vec<3, float>(-0.723608f, -0.525725f, 0.447219f),
		vec<3, float>(-0.723608f, 0.525725f, 0.447219f),
		vec<3, float>(0.276388f, 0.850649f, 0.447219f),
		vec<3, float>(0.894426f, 0.000000f, 0.447216f),
		vec<3, float>(-0.000000f, 0.000000f, 1.000000f),
		vec<3, float>(0.425323f, -0.309011f, -0.850654f),
		vec<3, float>(-0.162456f, -0.499995f, -0.850654f),
		vec<3, float>(0.262869f, -0.809012f, -0.525738f),
		vec<3, float>(0.425323f, 0.309011f, -0.850654f),
		vec<3, float>(0.850648f, -0.000000f, -0.525736f),
		vec<3, float>(-0.525730f, -0.000000f, -0.850652f),
		vec<3, float>(-0.688190f, -0.499997f, -0.525736f),
		vec<3, float>(-0.162456f, 0.499995f, -0.850654f),
		vec<3, float>(-0.688190f, 0.499997f, -0.525736f),
		vec<3, float>(0.262869f, 0.809012f, -0.525738f),
		vec<3, float>(0.951058f, 0.309013f, 0.000000f),
		vec<3, float>(0.951058f, -0.309013f, 0.000000f),
		vec<3, float>(0.587786f, -0.809017f, 0.000000f),
		vec<3, float>(0.000000f, -1.000000f, 0.000000f),
		vec<3, float>(-0.587786f, -0.809017f, 0.000000f),
		vec<3, float>(-0.951058f, -0.309013f, -0.000000f),
		vec<3, float>(-0.951058f, 0.309013f, -0.000000f),
		vec<3, float>(-0.587786f, 0.809017f, -0.000000f),
		vec<3, float>(-0.000000f, 1.000000f, -0.000000f),
		vec<3, float>(0.587786f, 0.809017f, -0.000000f),
		vec<3, float>(0.688190f, -0.499997f, 0.525736f),
		vec<3, float>(-0.262869f, -0.809012f, 0.525738f),
		vec<3, float>(-0.850648f, 0.000000f, 0.525736f),
		vec<3, float>(-0.262869f, 0.809012f, 0.525738f),
		vec<3, float>(0.688190f, 0.499997f, 0.525736f),
		vec<3, float>(0.525730f, 0.000000f, 0.850652f),
		vec<3, float>(0.162456f, -0.499995f, 0.850654f),
		vec<3, float>(-0.425323f, -0.309011f, 0.850654f),
		vec<3, float>(-0.425323f, 0.309011f, 0.850654f),
		vec<3, float>(0.162456f, 0.499995f, 0.850654f)
	};
	static size_t numPointsOnUnitSphere = sizeof(pointsOnUnitSphere) / sizeof(vec<3, float>);

	template <typename T>
	template <typename U>
	vec<3, T>& vec<3, T>::operator+=(const vec<3, U>& v)
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.y);
		this->z += static_cast<T>(v.z);
		return *this;
	}

	template <typename T>
	template <typename U>
	vec<3, T>& vec<3, T>::operator-=(const vec<3, U>& v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.y);
		this->z -= static_cast<T>(v.z);
		return *this;
	}

	template <typename T>
	template <typename U>
	vec<3, T>& vec<3, T>::operator*=(const vec<3, U>& v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.y);
		this->z *= static_cast<T>(v.z);
		return *this;
	}

	template <typename T>
	template <typename U>
	bool vec<3, T>::operator!=(const vec<3, U>& v) const
	{
		return x != v.x || y != v.y || z != v.z;
	}

	template <typename T>
	vec<3, T> operator-(const vec<3, T>& v)
	{
		return vec<3, T>(-v.x, -v.y, -v.z);
	}

	template <typename T>
	vec<3, T> operator+(const vec<3, T>& v1, const vec<3, T>& v2)
	{
		return vec<3, T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	template <typename T>
	vec<3, T> operator-(const vec<3, T>& v1, const vec<3, T>& v2)
	{
		return vec<3, T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	template <typename T>
	vec<3, T> operator*(const vec<3, T>& v1, const vec<3, T>& v2)
	{
		return vec<3, T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}

	template <typename T>
	vec<3, T> operator*(const vec<3, T>& v1, T scalar)
	{
		return vec<3, T>(v1.x * scalar, v1.y * scalar, v1.z * scalar);
	}


	template <typename T>
	vec<3, T> operator/(const vec<3, T>& v1, T scalar)
	{
		return vec<3, T>(v1.x / scalar, v1.y / scalar, v1.z / scalar);
	}

	template <typename T>
	T compMax(const vec<3, T>& v)
	{
		return max(v.x, max(v.y, v.z));
	}
}
#endif
