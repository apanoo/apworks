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

		// 四维数组初始化四元数
		Quaternion(const Vector4& r);

		// 使用旋转轴和旋转角度初始化四元数
		Quaternion(const Vector3& axis, float angle);

		// 使用矩阵初始化四元数 ： 矩阵转四元数
		Quaternion(const Matrix4& m);

		// 线性插值
		Quaternion nLerp(const Quaternion& r, float lerpFactor, bool shortestPath) const;

		// 球面线性插值
		Quaternion sLerp(const Quaternion& r, float lerpFactor, bool shortestPath) const;

		// 四元数转四维矩阵
		Matrix4 toRotationMatrix() const;

		// 求正前方向向量
		Vector3 getForward() const;

		// 求正后方向向量
		Vector3 getBack() const;

		// 求正上方向向量
		Vector3 getUp() const;

		// 求正下方向向量
		Vector3 getDown() const;

		// 求正右方向向量
		Vector3 getRight() const;

		// 求正左方向向量
		Vector3 getLeft() const;

		// 求共轭
		Quaternion conjugate() const;

		Quaternion operator*(const Quaternion& r) const;

		Quaternion operator*(const Vector3& v) const;

		friend std::ostream& operator<<(std::ostream& stream, const Quaternion& quaternion);
	};
}