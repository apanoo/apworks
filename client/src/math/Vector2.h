#pragma once
#ifndef _INC_MATH
	#include <math.h>
#endif // !_INC_MATH

#ifndef _IOSTREAM_
	#include <iostream>
#endif // !_IOSTREAM_

namespace nario {
	class Vector2
	{
	public:
		Vector2() { }

		Vector2(const Vector2& r)
		{
			(*this)[0] = r[0];
			(*this)[1] = r[1];
		}

		Vector2(float x, float y)
		{
			(*this)[0] = x;
			(*this)[1] = y;
		}

		inline float getX() const { return (*this)[0]; }
		inline float getY() const { return (*this)[1]; }
		inline void setX(const float& x) { (*this)[0] = x; }
		inline void setY(const float& y) { (*this)[1] = y; }
		inline void set(const float& x, const float& y) { setX(x); setY(y); }

		// 叉积
		float cross(const Vector2& r) const;

		// 点积
		float dot(const Vector2& r) const;

		// 最大分量
		float max() const;

		// 长度的平方
		float lengthSq() const;

		// 长度
		float length() const;

		// 单位化
		Vector2 normalized() const;

		// 线性插值，this与r之间的线性插值，lerpFactor范围：[0, 1]
		Vector2 lerp(const Vector2& r, float lerpFactor) const;

		// 镜面反射，normal为法线
		Vector2 reflect(const Vector2& normal) const;

		Vector2 operator+(const Vector2& r) const;
		Vector2 operator-(const Vector2& r) const;
		Vector2 operator*(const float& r) const;
		Vector2 operator/(const float& r) const;

		Vector2& operator+=(const Vector2& r);
		Vector2& operator-=(const Vector2& r);
		Vector2& operator*=(const float& r);
		Vector2& operator/=(const float& r);

		bool operator==(const Vector2& r) const;
		bool operator!=(const Vector2& r) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector);

		// 修改values
		inline float& operator [] (unsigned int i) { return m_Values[i]; }
		// 访问values
		inline float operator [] (unsigned int i) const { return m_Values[i]; }

	private:
		float m_Values[2];
	};
}