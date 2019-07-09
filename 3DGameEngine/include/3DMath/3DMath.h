#ifndef MATH_H
#define MATH_H

#include "Vector.h"
#include "Quaternion.h"
#include "Matrix.h"


#define MATH_PI 3.1415926535897932384626433832795
namespace math
{
	typedef vec<2, float> Vector2;
	typedef vec<3, float> Vector3;
	typedef vec<4, float> Vector4;
	typedef quat<float> Quaternion;
	typedef mat<float> Matrix4x4;

	template <unsigned int L, typename T>
	T const* value_ptr(const vec<L, T>& v)
	{
		return &(v.x);
	}

	inline float ToRadians(float x)
	{
		return x * MATH_PI / 180.0;
	}

	inline float ToDegrees(float x)
	{
		return x * 180.0 / MATH_PI;
	}

	template <typename T>
	vec<3, T> rotate(const vec<3, T>& v, const quat<T>& q)
	{
		quat<T> result = q * v * inverse(q);
		return vec<3, T>(result.x, result.y, result.z);
	}

	template <typename T>
	T max(T v1, T v2)
	{
		if (v1 > v2)
			return v1;
		else
			return v2;
	}

	template<typename T>
	T sign(T a)
	{
		if (a == (T)0)
			return (T)0;
		if (a > (T)0)
			return (T)1;
		if (a < (T)0)
			return (T)-1;
	}

	template<typename T>
	void decompose(const Matrix4x4& mat, Vector3& translationOut, Quaternion& rotationOut, Vector3& scaleOut)
	{
		translationOut.x = mat[0][3];
		translationOut.y = mat[1][3];
		translationOut.z = mat[2][3];

		scaleOut.y = length(Vector3(mat[0][0], mat[1][0], mat[2][0]));
		scaleOut.x = length(Vector3(mat[0][1], mat[1][1], mat[2][1]));
		scaleOut.z = length(Vector3(mat[0][2], mat[1][2], mat[2][2]));
		if(determinant(mat) < 0)
			scaleOut = -scaleOut;

		Matrix4x4 rot;
		if(scaleOut.x)
		{
			rot[0][0] = mat[0][0] / scaleOut.x;
			rot[1][0] = mat[1][0] / scaleOut.x;
			rot[2][0] = mat[2][0] / scaleOut.x;
		}
		if(scaleOut.y)
		{
			rot[0][1] = mat[0][1] / scaleOut.y;
			rot[1][1] = mat[1][1] / scaleOut.y;
			rot[2][1] = mat[2][1] / scaleOut.y;
		}
		if(scaleOut.z)
		{
			rot[0][2] = mat[0][2] / scaleOut.z;
			rot[1][2] = mat[1][2] / scaleOut.z;
			rot[2][2] = mat[2][2] / scaleOut.z;
		}
		rotationOut = Quaternion(rot);
	}

}
#endif
