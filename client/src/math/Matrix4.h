#pragma once
#ifndef _INC_MATH
	#include <math.h>
#endif // !_INC_MATH

#ifndef _IOSTREAM_
	#include <iostream>
#endif // !_IOSTREAM_

#include "Vector3.h"
#include "Vector4.h"

class Quaternion;
namespace nario {

#define EPS 1e-6
#define CHECK_ZERO(x) (abs(x) < EPS ? 0 : x)

	/*
	* ע�⣺m[i][j] j��ʾ�У�i��ʾ��
	* ʹ����������Ҫ��Shader��glUniformMatrix4fv������������
	* ʹ���͵�shader�ľ��󱣳ִ洢��ʽһ��
	*/
	class Matrix4
	{
	public:
		Matrix4()
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m[i][j] = 0.0f;
				}
			}
		}

		Matrix4(const Matrix4& r)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				for (unsigned int i = 0; i < 4; i++)
				{
					(*this)[i][j] = r[i][j];
				}
			}
		}


		Matrix4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
		{
			// ��һ��
			(*this)[0][0] = CHECK_ZERO(m00);
			(*this)[1][0] = CHECK_ZERO(m01);
			(*this)[2][0] = CHECK_ZERO(m02);
			(*this)[3][0] = CHECK_ZERO(m03);
							
			// �ڶ���		  
			(*this)[0][1] = CHECK_ZERO(m10);
			(*this)[1][1] = CHECK_ZERO(m11);
			(*this)[2][1] = CHECK_ZERO(m12);
			(*this)[3][1] = CHECK_ZERO(m13);
							
			// ������		
			(*this)[0][2] = CHECK_ZERO(m20);
			(*this)[1][2] = CHECK_ZERO(m21);
			(*this)[2][2] = CHECK_ZERO(m22);
			(*this)[3][2] = CHECK_ZERO(m23);
							
			// ������		  
			(*this)[0][3] = CHECK_ZERO(m30);
			(*this)[1][3] = CHECK_ZERO(m31);
			(*this)[2][3] = CHECK_ZERO(m32);
			(*this)[3][3] = CHECK_ZERO(m33);
		}

		// ʹ����Ԫ����ʼ������
		Matrix4(const Quaternion& quaternion);

		// ��λ����
		Matrix4 identityMatrix();

		// ����
		Matrix4 scaleMatrix(const Vector3& r);

		// ƽ��
		Matrix4 translationMatrix(const Vector3& r);

		// ��ת
		Matrix4 rotationMatrix(float angle, const Vector3& axis);

		// ŷ������ת : ��������������
		Matrix4 rotationEulerMatrix(float rotateX, float rotateY, float rotateZ);

		// ��Ԫ��ת 
		//Matrix4 rotationQuaternionMatrix(float rotateX, float rotateY, float rotateZ);

		Matrix4 rotationFromVectorsMatrix(const Vector3& n, const Vector3& v, const Vector3& u);

		// ��������ת
		Matrix4 rotationFromDirectionMatrix(const Vector3& forward, const Vector3& up);

		// Camera
		Matrix4 cameraMatrix(const Vector3& forward, const Vector3& up);

		// ͸��
		Matrix4 perspectiveMatrix(float fov, float aspectRatio, float zNear, float zFar);

		// ����
		Matrix4 orthographicMatrix(float left, float right, float bottom, float top, float near, float far);

		// ת��
		Matrix4 transpose() const;

		// ����
		Matrix4 inverse() const;

		// ������
		Vector4 operator*(const Vector4& r) const;
		Matrix4 operator*(const Matrix4& r) const;

		bool operator==(const Matrix4& r) const;
		bool operator!=(const Matrix4& r) const;

		friend std::ostream& operator<<(std::ostream& stream, const Matrix4& matrix);

		inline void set(unsigned int x, unsigned int y, float val) { m[x][y] = val; }
		inline const float* operator[](int index) const { return m[index]; }
		inline float* operator[](int index) { return m[index]; }
	private:
		float m[4][4];
	};
}