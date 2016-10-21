#pragma once
#ifndef _INC_MATH
	#include <math.h>
#endif // !_INC_MATH

#ifndef _IOSTREAM_
	#include <iostream>
#endif // !_IOSTREAM_

namespace nario {
	class Quaternion;

	class Vector3
	{
	public:
		Vector3() { }

		Vector3(const Vector3& r)
		{
			(*this)[0] = r[0];
			(*this)[1] = r[1];
			(*this)[2] = r[2];
		}

		Vector3(float x, float y, float z)
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
		}

		inline float getX() const { return (*this)[0]; }
		inline float getY() const { return (*this)[1]; }
		inline float getZ() const { return (*this)[2]; }
		inline void setX(const float& x) { (*this)[0] = x; }
		inline void setY(const float& y) { (*this)[1] = y; }
		inline void setZ(const float& z) { (*this)[2] = z; }
		inline void set(const float& x, const float& y, const float& z) { setX(x); setY(y); setZ(z); }

		// ���
		Vector3 cross(const Vector3& r) const;

		// ���
		float dot(const Vector3& r) const;

		// ������
		float vecMax() const;

		// ���ȵ�ƽ��
		float lengthSq() const;

		// ����
		float length() const;

		// ��ת��ͨ����ת������ת�ǣ�
		Vector3 rotate(float angle, const Vector3& axis) const;

		// ��ת��ͨ����Ԫ����
		Vector3 rotate(const Quaternion& rotation) const;

		// ��λ��
		Vector3 normalized() const;

		// ���Բ�ֵ��this��r֮������Բ�ֵ��lerpFactor��Χ��[0, 1]
		Vector3 lerp(const Vector3& r, float lerpFactor) const;

		// ���淴�䣬normalΪ����
		Vector3 reflect(const Vector3& normal) const;

		Vector3 operator+(const Vector3& r) const;
		Vector3 operator-(const Vector3& r) const;
		Vector3 operator*(const float& r) const;
		Vector3 operator/(const float& r) const;

		Vector3& operator+=(const Vector3& r);
		Vector3& operator-=(const Vector3& r);
		Vector3& operator*=(const float& r);
		Vector3& operator/=(const float& r);

		bool operator==(const Vector3& r) const;
		bool operator!=(const Vector3& r) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector);

		// �޸�values
		inline float& operator [] (unsigned int i) { return m_Values[i]; }
		// ����values
		inline float operator [] (unsigned int i) const { return m_Values[i]; }

	private:
		float m_Values[3];
	};
}