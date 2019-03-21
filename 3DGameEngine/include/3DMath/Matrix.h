#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <assimp/matrix4x4.h>

namespace math
{
	template <typename T>
	struct mat
	{
		mat()
		{
			//might be bad layout but I think it is good
			m_values[0][0] = 1; m_values[0][1] = 0; m_values[0][2] = 0; m_values[0][3] = 0;
			m_values[1][0] = 0; m_values[1][1] = 1; m_values[1][2] = 0; m_values[1][3] = 0;
			m_values[2][0] = 0; m_values[2][1] = 0; m_values[2][2] = 1; m_values[2][3] = 0;
			m_values[3][0] = 0; m_values[3][1] = 0; m_values[3][2] = 0; m_values[3][3] = 1;
		};

		mat(T s)
		{
			for (int column = 0; column < 4; column++)
			{
				for (int row = 0; row < 4; row++)
				{
					if (row == column)
						m_values[column][row] = s;
					else
						m_values[column][row] = 0;
				}
			}
		}

		const T* operator[](unsigned int i) const
		{
			return m_values[i];
		}

		T* operator[](unsigned int i)
		{
			return m_values[i];
		}
		mat<T>& operator=(const aiMatrix4x4& aiMatrix)
		{

			m_values[0][0] = aiMatrix.a1; m_values[0][1] = aiMatrix.a2; m_values[0][2] = aiMatrix.a3; m_values[0][3] = aiMatrix.a4;
			m_values[1][0] = aiMatrix.b1; m_values[1][1] = aiMatrix.b2; m_values[1][2] = aiMatrix.b3; m_values[1][3] = aiMatrix.b4;
			m_values[2][0] = aiMatrix.c1; m_values[2][1] = aiMatrix.c2; m_values[2][2] = aiMatrix.c3; m_values[2][3] = aiMatrix.c4;
			m_values[3][0] = aiMatrix.d1; m_values[3][1] = aiMatrix.d2; m_values[3][2] = aiMatrix.d3; m_values[3][3] = aiMatrix.d4;

			return *this;
		}

	private:
		T m_values[4][4];
	};

	template <typename T>
	mat<T> operator*(const mat<T>& m1, const mat<T>& m2)
	{
		mat<T> result;
		for (int column = 0; column < 4; column++)
		{
			for (int row = 0; row < 4; row++)
			{
				result[column][row] = T(0);
				for (int k = 0; k < 4; k++)
				{
					result[column][row] += m1[k][row] * m2[column][k];
				}
			}
		}

		return result;
	}

	template <typename T>
	mat<T> operator*(const mat<T>& m, T scalar)
	{
		mat<T> result;
		for (int column = 0; column < 4; column++)
		{
			for (int row = 0; row < 4; row++)
			{
				result[column][row] = m[column][row] * scalar;
			}
		}
		return result;
	}

	template <typename T>
	mat<T> operator*(T scalar, const mat<T>& m)
	{
		mat<T> result;
		for (int column = 0; column < 4; column++)
		{
			for (int row = 0; row < 4; row++)
			{
				result[column][row] = m[column][row] * scalar;
			}
		}
		return result;
	}

	template <typename T>
	mat<T> operator+(const mat<T>& m1, const mat<T>& m2)
	{
		mat<T> result;
		for (int column = 0; column < 4; column++)
		{
			for (int row = 0; row < 4; row++)
			{
				result[column][row] = m1[column][row] + m2[column][row];
			}
		}
		return result;
	}

	template <typename T>
	mat<T> operator+(const mat<T>& m, T scalar)
	{
		mat<T> result;
		for (int column = 0; column < 4; column++)
		{
			for (int row = 0; row < 4; row++)
			{
				result[column][row] = m[column][row] + scalar;
			}
		}
		return result;
	}

	template <typename T>
	mat<T> translate(const vec<3, T>& v)
	{
		mat<T> result;
		result[3][0] = v.x;
		result[3][1] = v.y;
		result[3][2] = v.z;

		return result;
	}

	template <typename T>
	mat<T> scale(const vec<3, T>& v)
	{
		mat<T> result;
		result[0][0] = v.x;
		result[1][1] = v.y;
		result[2][2] = v.z;
		return result;
	}

	template <typename T>
	mat<T> transpose(const mat<T>& m)
	{
		mat<T> result;
		for (int column = 0; column < 4; column++)
		{
			for (int row = 0; row < 4; row++)
			{
				result[column][row] = m[row][column];
			}
		}
		return result;
	}

	template <typename T>
	mat<T> perspective(T fov, T aspectRatio, T zNear, T zFar)
	{
		mat<T> result(static_cast<T>(0));
		const float tanHalfFOV = tan(fov / 2.0f);

		result[0][0] = static_cast<T>(1) / (aspectRatio * tanHalfFOV);
		result[1][1] = static_cast<T>(1) / (tanHalfFOV);
		result[2][3] = -static_cast<T>(1);

		result[2][2] = -(zFar + zNear) / (zFar - zNear);
		result[3][2] = -(static_cast<T>(2) * zFar * zNear) / (zFar - zNear);

		return result;
	}

    //Function taken from glm library
    template<typename T>
    mat<T> inverse(const mat<T>& m)
    {
        T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
        T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
        T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

        T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
        T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
        T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

        T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
        T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
        T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

        T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
        T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
        T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

        T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
        T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
        T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

        T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
        T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
        T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

        math::vec<4, T> Fac0(Coef00, Coef00, Coef02, Coef03);
        math::vec<4, T> Fac1(Coef04, Coef04, Coef06, Coef07);
        math::vec<4, T> Fac2(Coef08, Coef08, Coef10, Coef11);
        math::vec<4, T> Fac3(Coef12, Coef12, Coef14, Coef15);
        math::vec<4, T> Fac4(Coef16, Coef16, Coef18, Coef19);
        math::vec<4, T> Fac5(Coef20, Coef20, Coef22, Coef23);

        math::vec<4, T> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
        math::vec<4, T> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
        math::vec<4, T> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
        math::vec<4, T> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

        math::vec<4, T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
        math::vec<4, T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
        math::vec<4, T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
        math::vec<4, T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

        math::vec<4, T> SignA(+1, -1, +1, -1);
        math::vec<4, T> SignB(-1, +1, -1, +1);
        math::mat<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

        math::vec<4, T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

        math::vec<4, T> Dot0(m[0] * Row0);
        T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

        T OneOverDeterminant = static_cast<T>(1) / Dot1;

        return Inverse * OneOverDeterminant;
    }

	template <typename T>
	T determinant(const mat<T>& m)
	{
		return    m[0][0]*m[1][1]*m[2][2]*m[3][3] - m[0][0]*m[1][1]*m[2][3]*m[3][2] + m[0][0]*m[1][2]*m[2][3]*m[3][1] - m[0][0]*m[1][2]*m[2][1]*m[3][3]
				+ m[0][0]*m[1][3]*m[2][1]*m[3][2] - m[0][0]*m[1][3]*m[2][2]*m[3][1] - m[0][1]*m[1][2]*m[2][3]*m[3][0] + m[0][1]*m[1][2]*m[2][0]*m[3][3]
				- m[0][1]*m[1][3]*m[2][0]*m[3][2] + m[0][1]*m[1][3]*m[2][2]*m[3][0] - m[0][1]*m[1][0]*m[2][2]*m[3][3] + m[0][1]*m[1][0]*m[2][3]*m[3][2]
				+ m[0][2]*m[1][3]*m[2][0]*m[3][1] - m[0][2]*m[1][3]*m[2][1]*m[3][0] + m[0][2]*m[1][0]*m[2][1]*m[3][3] - m[0][2]*m[1][0]*m[2][3]*m[3][1]
				+ m[0][2]*m[1][1]*m[2][3]*m[3][0] - m[0][2]*m[1][1]*m[2][0]*m[3][3] - m[0][3]*m[1][0]*m[2][1]*m[3][2] + m[0][3]*m[1][0]*m[2][2]*m[3][1]
				- m[0][3]*m[1][1]*m[2][2]*m[3][0] + m[0][3]*m[1][1]*m[2][0]*m[3][2] - m[0][3]*m[1][2]*m[2][0]*m[3][1] + m[0][3]*m[1][2]*m[2][1]*m[3][0];
	}

	template <typename T>
	std::string ToString(const mat<T>& m)
	{
		std::string result = "Matrix 4x4 :\n" + std::to_string(m[0][0]) + "; " + std::to_string(m[1][0]) + "; " + std::
			to_string(m[2][0]) + "; " + std::to_string(m[3][0]) + "\n"
			+ std::to_string(m[0][1]) + "; " + std::to_string(m[1][1]) + "; " + std::to_string(m[2][1]) + "; " + std::
			to_string(m[3][1]) + "\n"
			+ std::to_string(m[0][2]) + "; " + std::to_string(m[1][2]) + "; " + std::to_string(m[2][2]) + "; " + std::
			to_string(m[3][2]) + "\n"
			+ std::to_string(m[0][3]) + "; " + std::to_string(m[1][3]) + "; " + std::to_string(m[2][3]) + "; " + std::
			to_string(m[3][3]);

		return result;
	}
}
#endif
