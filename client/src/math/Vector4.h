#pragma once
#ifndef _INC_MATH
	#include <math.h>
#endif // !_INC_MATH

#ifndef _IOSTREAM_
	#include <iostream>
#endif // !_IOSTREAM_

namespace nario {
	class Vector4
	{
	public:
		Vector4() { }

		Vector4(const Vector4& r)
		{
			(*this)[0] = r[0];
			(*this)[1] = r[1];
			(*this)[2] = r[2];
			(*this)[3] = r[3];
		}

		Vector4(float x, float y, float z, float w)
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
			(*this)[3] = w;
		}

		// set and get
		inline float getX() const { return (*this)[0]; }
		inline float getY() const { return (*this)[1]; }
		inline float getZ() const { return (*this)[2]; }
		inline float getW() const { return (*this)[3]; }
		inline void setX(const float& x) { (*this)[0] = x; }
		inline void setY(const float& y) { (*this)[1] = y; }
		inline void setZ(const float& z) { (*this)[2] = z; }
		inline void setW(const float& w) { (*this)[3] = w; }
		inline void set(const float& x, const float& y, const float& z, const float& w)
		{
			setX(x);
			setY(y);
			setZ(z);
			setW(w);
		}

		// 点积
		float dot(const Vector4& r) const;

		// 最大分量
		float max() const;

		// 长度的平方
		float lengthSq() const;

		// 长度
		float length() const;

		// 单位化
		Vector4 normalized() const;

		// 线性插值，this与r之间的线性插值，lerpFactor范围：[0, 1]
		Vector4 lerp(const Vector4& r, float lerpFactor) const;

		// 镜面反射，normal为法线
		Vector4 reflect(const Vector4& normal) const;

		Vector4 operator+(const Vector4& r) const;
		Vector4 operator-(const Vector4& r) const;
		Vector4 operator*(const float& r) const;
		Vector4 operator/(const float& r) const;

		Vector4& operator+=(const Vector4& r);
		Vector4& operator-=(const Vector4& r);
		Vector4& operator*=(const float& r);
		Vector4& operator/=(const float& r);

		bool operator==(const Vector4& r) const;
		bool operator!=(const Vector4& r) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector);

		// 修改values
		inline float& operator [] (unsigned int i) { return m_Values[i]; }
		// 访问values
		inline float operator [] (unsigned int i) const { return m_Values[i]; }

	private:
		float m_Values[4];
	};
}