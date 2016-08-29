#include "Quaternion.h"

namespace nario {
	Quaternion::Quaternion(const Matrix4& m)
	{
		// 求迹
		float trace = m[0][0] + m[1][1] + m[2][2];

		// 根据迹不同情况分别求四元数的四个分量
		if (trace > 0)
		{
			float s = 0.5f / sqrtf(trace + 1.0f);
			(*this)[3] = 0.25f / s;
			(*this)[0] = (m[1][2] - m[2][1]) * s;
			(*this)[1] = (m[2][0] - m[0][2]) * s;
			(*this)[2] = (m[0][1] - m[1][0]) * s;
		}
		else if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
		{
			float s = 2.0f * sqrtf(1.0f + m[0][0] - m[1][1] - m[2][2]);
			(*this)[3] = (m[1][2] - m[2][1]) / s;
			(*this)[0] = 0.25f * s;
			(*this)[1] = (m[1][0] + m[0][1]) / s;
			(*this)[2] = (m[2][0] + m[0][2]) / s;
		}
		else if (m[1][1] > m[2][2])
		{
			float s = 2.0f * sqrtf(1.0f + m[1][1] - m[0][0] - m[2][2]);
			(*this)[3] = (m[2][0] - m[0][2]) / s;
			(*this)[0] = (m[1][0] + m[0][1]) / s;
			(*this)[1] = 0.25f * s;
			(*this)[2] = (m[2][1] + m[1][2]) / s;
		}
		else
		{
			float s = 2.0f * sqrtf(1.0f + m[2][2] - m[1][1] - m[0][0]);
			(*this)[3] = (m[0][1] - m[1][0]) / s;
			(*this)[0] = (m[2][0] + m[0][2]) / s;
			(*this)[1] = (m[1][2] + m[2][1]) / s;
			(*this)[2] = 0.25f * s;
		}

		// 单位化
		float length = this->length();
		(*this)[3] = (*this)[3] / length;
		(*this)[0] = (*this)[0] / length;
		(*this)[1] = (*this)[1] / length;
		(*this)[2] = (*this)[2] / length;
	}

	Quaternion::Quaternion(const Vector3& axis, float angle)
	{
		float sinHalfAngle = sinf(angle / 2);
		float cosHalfAngle = cosf(angle / 2);

		(*this)[0] = axis.getX() * sinHalfAngle;
		(*this)[1] = axis.getY() * sinHalfAngle;
		(*this)[2] = axis.getZ() * sinHalfAngle;
		(*this)[3] = cosHalfAngle;
	}

	Quaternion::Quaternion(const Vector4& r)
	{
		(*this)[0] = r[0];
		(*this)[1] = r[1];
		(*this)[2] = r[2];
		(*this)[3] = r[3];
	}

	Quaternion Quaternion::nLerp(const Quaternion& r, float lerpFactor, bool shortestPath) const
	{
		Quaternion correctedDest;

		if (shortestPath && this->dot(r) < 0)
		{
			correctedDest = r * -1;
		}
		else
		{
			correctedDest = r;
		}

		return Quaternion(lerp(correctedDest, lerpFactor).normalized());
	}

	Quaternion Quaternion::sLerp(const Quaternion& r, float lerpFactor, bool shortestPath) const
	{
		static const float EPSILON = 1e3;

		float cos = this->dot(r);
		Quaternion correctedDest;

		if (shortestPath && cos < 0)
		{
			cos *= -1;
			correctedDest = r * -1;
		}
		else
		{
			correctedDest = r;
		}

		if (fabs(cos) >(1 - EPSILON))
		{
			return nLerp(correctedDest, lerpFactor, false);
		}

		float sin = (float)sqrtf(1.0f - cos * cos);
		float angle = atan2(sin, cos);
		float invSin = 1.0f / sin;

		float srcFactor = sinf((1.0f - lerpFactor) * angle) * invSin;
		float destFactor = sinf((lerpFactor)* angle) * invSin;

		return Quaternion((*this) * srcFactor + correctedDest * destFactor);
	}

	Matrix4 Quaternion::toRotationMatrix() const
	{
		Vector3 forward = Vector3(2.0f * (getX() * getZ() - getW() * getY()), 2.0f * (getY() * getZ() + getW() * getX()), 1.0f - 2.0f * (getX() * getX() + getY() * getY()));
		Vector3 up = Vector3(2.0f * (getX()*getY() + getW()*getZ()), 1.0f - 2.0f * (getX()*getX() + getZ()*getZ()), 2.0f * (getY()*getZ() - getW()*getX()));
		Vector3 right = Vector3(1.0f - 2.0f * (getY()*getY() + getZ()*getZ()), 2.0f * (getX()*getY() - getW()*getZ()), 2.0f * (getX()*getZ() + getW()*getY()));

		return Matrix4().rotationFromVectorsMatrix(forward, up, right);
	}

	Vector3 Quaternion::getForward() const
	{
		return Vector3(0, 0, 1).rotate(*this);
	}

	Vector3 Quaternion::getBack() const
	{
		return Vector3(0, 0, -1).rotate(*this);
	}

	Vector3 Quaternion::getUp() const
	{
		return Vector3(0, 1, 0).rotate(*this);
	}

	Vector3 Quaternion::getDown() const
	{
		return Vector3(0, -1, 0).rotate(*this);
	}

	Vector3 Quaternion::getRight() const
	{
		return Vector3(1, 0, 0).rotate(*this);
	}

	Vector3 Quaternion::getLeft() const
	{
		return Vector3(-1, 0, 0).rotate(*this);
	}

	Quaternion Quaternion::conjugate() const
	{
		return Quaternion(-getX(), -getY(), -getZ(), getW());
	}

	Quaternion Quaternion::operator*(const Vector3& v) const
	{
		const float _w = -(getX() * v.getX()) - (getY() * v.getY()) - (getZ() * v.getZ());
		const float _x = (getW() * v.getX()) + (getY() * v.getZ()) - (getZ() * v.getY());
		const float _y = (getW() * v.getY()) + (getZ() * v.getX()) - (getX() * v.getZ());
		const float _z = (getW() * v.getZ()) + (getX() * v.getY()) - (getY() * v.getX());

		return Quaternion(_x, _y, _z, _w);
	}

	Quaternion Quaternion::operator*(const Quaternion& r) const
	{
		const float _w = (getW() * r.getW()) - (getX() * r.getX()) - (getY() * r.getY()) - (getZ() * r.getZ());
		const float _x = (getX() * r.getW()) + (getW() * r.getX()) + (getY() * r.getZ()) - (getZ() * r.getY());
		const float _y = (getY() * r.getW()) + (getW() * r.getY()) + (getZ() * r.getX()) - (getX() * r.getZ());
		const float _z = (getZ() * r.getW()) + (getW() * r.getZ()) + (getX() * r.getY()) - (getY() * r.getX());

		return Quaternion(_x, _y, _z, _w);
	}

	std::ostream& operator<<(std::ostream& stream, const Quaternion& quaternion)
	{
		stream << "Quaternion(" << quaternion.getX() << "," << quaternion.getY() << "," << quaternion.getZ() << "," << quaternion.getW() << ")";
		return stream;
	}
}