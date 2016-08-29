#pragma once
#ifndef _INC_MATH
	#include <math.h>
#endif // !_INC_MATH

#ifndef _IOSTREAM_
	#include <iostream>
#endif // !_IOSTREAM_

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

namespace nario {
	class Quaternion : public Vector4
	{
	public:
		Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f)
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
			(*this)[3] = w;
		}

		// ��ά�����ʼ����Ԫ��
		Quaternion(const Vector4& r);

		// ʹ����ת�����ת�Ƕȳ�ʼ����Ԫ��
		Quaternion(const Vector3& axis, float angle);

		// ʹ�þ����ʼ����Ԫ�� �� ����ת��Ԫ��
		Quaternion(const Matrix4& m);

		// ���Բ�ֵ
		Quaternion nLerp(const Quaternion& r, float lerpFactor, bool shortestPath) const;

		// �������Բ�ֵ
		Quaternion sLerp(const Quaternion& r, float lerpFactor, bool shortestPath) const;

		// ��Ԫ��ת��ά����
		Matrix4 toRotationMatrix() const;

		// ����ǰ��������
		Vector3 getForward() const;

		// ������������
		Vector3 getBack() const;

		// �����Ϸ�������
		Vector3 getUp() const;

		// �����·�������
		Vector3 getDown() const;

		// �����ҷ�������
		Vector3 getRight() const;

		// ������������
		Vector3 getLeft() const;

		// ����
		Quaternion conjugate() const;

		Quaternion operator*(const Quaternion& r) const;

		Quaternion operator*(const Vector3& v) const;

		friend std::ostream& operator<<(std::ostream& stream, const Quaternion& quaternion);
	};
}