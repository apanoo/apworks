#include "Vector3.h"
#include "Quaternion.h"

namespace nario {
	Vector3 Vector3::cross(const Vector3& r) const
	{
		float x = (*this)[1] * r[2] - (*this)[2] * r[1];
		float y = (*this)[2] * r[0] - (*this)[0] * r[2];
		float z = (*this)[0] * r[1] - (*this)[1] * r[0];

		return Vector3(x, y, z);
	}

	float Vector3::dot(const Vector3& r) const
	{
		float result = 0.0f;
		for (unsigned int i = 0; i < 3; i++)
		{
			result += (*this)[i] * r[i];
		}

		return result;
	}

	float Vector3::max() const
	{
		float maxVal = (*this)[0];

		for (unsigned int i = 0; i < 3; i++)
		{
			if ((*this)[i] > maxVal)
			{
				maxVal = (*this)[i];
			}
		}
		return maxVal;
	}

	float Vector3::lengthSq() const
	{
		return this->dot(*this);
	}

	float Vector3::length() const
	{
		return sqrt(lengthSq());
	}

	Vector3 Vector3::rotate(float angle, const Vector3& axis) const
	{
		Quaternion rotationQ(axis, angle);
		return rotate(rotationQ);
	}

	Vector3 Vector3::rotate(const Quaternion& rotation) const
	{
		Quaternion conjugateQ = rotation.conjugate();
		Quaternion w = rotation * (*this) * conjugateQ;

		Vector3 ret(w.getX(), w.getY(), w.getZ());

		return ret;
	}

	Vector3 Vector3::normalized() const
	{
		return *this / length();
	}

	Vector3 Vector3::lerp(const Vector3& r, float lerpFactor) const
	{
		return (r - *this) * lerpFactor + *this;
	}

	// R = L - 2 (L.dot(n)n)
	// normal 必须为单位向量
	Vector3 Vector3::reflect(const Vector3& normal) const
	{
		return *this - (normal * (this->dot(normal) * 2));
	}

	Vector3 Vector3::operator+(const Vector3& r) const
	{
		Vector3 result;
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = m_Values[i] + r[i];
		}

		return result;
	}

	Vector3 Vector3::operator-(const Vector3& r) const
	{
		Vector3 result;
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = m_Values[i] - r[i];
		}

		return result;
	}

	Vector3 Vector3::operator*(const float& r) const
	{
		Vector3 result;
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = m_Values[i] * r;
		}

		return result;
	}

	Vector3 Vector3::operator/(const float& r) const
	{
		Vector3 result;
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = m_Values[i] / r;
		}

		return result;
	}

	Vector3& Vector3::operator/=(const float& r)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			(*this)[i] = m_Values[i] / r;
		}

		return *this;
	}

	bool Vector3::operator!=(const Vector3& r) const
	{
		return !operator==(r);
	}

	bool Vector3::operator==(const Vector3& r) const
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			if ((*this)[i] != r[i])
			{
				return false;
			}
		}
		return true;
	}

	Vector3& Vector3::operator*=(const float& r)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			(*this)[i] = m_Values[i] * r;
		}

		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& r)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			(*this)[i] = m_Values[i] - r[i];
		}

		return *this;
	}

	Vector3& Vector3::operator+=(const Vector3& r)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			(*this)[i] = m_Values[i] + r[i];
		}

		return *this;
	}

	std::ostream& operator<<(std::ostream& stream, const Vector3& vector)
	{
		stream << "Vector3(" << vector.getX() << "," << vector.getY() << "," << vector.getZ() << ")";
		return stream;
	}
}