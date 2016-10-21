#include "Vector4.h"

namespace nario {

	float Vector4::dot(const Vector4& r) const
	{
		float result = 0.0f;
		for (unsigned int i = 0; i < 4; i++)
		{
			result += (*this)[i] * r[i];
		}

		return result;
	}

	float Vector4::vecMax() const
	{
		float maxVal = (*this)[0];

		for (unsigned int i = 0; i < 4; i++)
		{
			if ((*this)[i] > maxVal)
			{
				maxVal = (*this)[i];
			}
		}
		return maxVal;
	}

	float Vector4::lengthSq() const
	{
		return this->dot(*this);
	}

	float Vector4::length() const
	{
		return sqrt(lengthSq());
	}

	Vector4 Vector4::normalized() const
	{
		return *this / length();
	}

	Vector4 Vector4::lerp(const Vector4& r, float lerpFactor) const
	{
		return (r - *this) * lerpFactor + *this;
	}

	// R = L - 2 (L.dot(n)n)
	// normal 必须为单位向量
	Vector4 Vector4::reflect(const Vector4& normal) const
	{
		return *this - (normal * (this->dot(normal) * 2));
	}

	Vector4 Vector4::operator+(const Vector4& r) const
	{
		Vector4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			result[i] = m_Values[i] + r[i];
		}

		return result;
	}

	Vector4 Vector4::operator-(const Vector4& r) const
	{
		Vector4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			result[i] = m_Values[i] - r[i];
		}

		return result;
	}

	Vector4 Vector4::operator*(const float& r) const
	{
		Vector4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			result[i] = m_Values[i] * r;
		}

		return result;
	}

	Vector4 Vector4::operator/(const float& r) const
	{
		Vector4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			result[i] = m_Values[i] / r;
		}

		return result;
	}

	Vector4& Vector4::operator/=(const float& r)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			(*this)[i] = m_Values[i] / r;
		}

		return *this;
	}

	bool Vector4::operator!=(const Vector4& r) const
	{
		return !operator==(r);
	}

	bool Vector4::operator==(const Vector4& r) const
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			if ((*this)[i] != r[i])
			{
				return false;
			}
		}
		return true;
	}

	Vector4& Vector4::operator*=(const float& r)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			(*this)[i] = m_Values[i] * r;
		}

		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& r)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			(*this)[i] = m_Values[i] - r[i];
		}

		return *this;
	}

	Vector4& Vector4::operator+=(const Vector4& r)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			(*this)[i] = m_Values[i] + r[i];
		}

		return *this;
	}

	std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
	{
		stream << "Vector4(" << vector.getX() << "," << vector.getY() << "," << vector.getZ() << "," << vector.getW() << ")";
		return stream;
	}
}