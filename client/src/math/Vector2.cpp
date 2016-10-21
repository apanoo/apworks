#include "Vector2.h"

namespace nario {
	float Vector2::cross(const Vector2& r) const
	{
		return getX() * r.getY() - getY() * r.getX();
	}

	float Vector2::dot(const Vector2& r) const
	{
		float result = 0.0f;
		for (unsigned int i = 0; i < 2; i++)
		{
			result += (*this)[i] * r[i];
		}

		return result;
	}

	float Vector2::vecMax() const
	{
		float maxVal = (*this)[0];

		for (unsigned int i = 0; i < 2; i++)
		{
			if ((*this)[i] > maxVal)
			{
				maxVal = (*this)[i];
			}
		}
		return maxVal;
	}

	float Vector2::lengthSq() const
	{
		return this->dot(*this);
	}

	float Vector2::length() const
	{
		return sqrt(lengthSq());
	}

	Vector2 Vector2::normalized() const
	{
		return *this / length();
	}

	Vector2 Vector2::lerp(const Vector2& r, float lerpFactor) const
	{
		return (r - *this) * lerpFactor + *this;
	}

	// R = L - 2 (L.dot(n)n)
	// normal 必须为单位向量
	Vector2 Vector2::reflect(const Vector2& normal) const
	{
		return *this - (normal * (this->dot(normal) * 2));
	}

	Vector2 Vector2::operator+(const Vector2& r) const
	{
		Vector2 result;
		for (unsigned int i = 0; i < 2; i++)
		{
			result[i] = m_Values[i] + r[i];
		}

		return result;
	}

	Vector2 Vector2::operator-(const Vector2& r) const
	{
		Vector2 result;
		for (unsigned int i = 0; i < 2; i++)
		{
			result[i] = m_Values[i] - r[i];
		}

		return result;
	}

	Vector2 Vector2::operator*(const float& r) const
	{
		Vector2 result;
		for (unsigned int i = 0; i < 2; i++)
		{
			result[i] = m_Values[i] * r;
		}

		return result;
	}

	Vector2 Vector2::operator/(const float& r) const
	{
		Vector2 result;
		for (unsigned int i = 0; i < 2; i++)
		{
			result[i] = m_Values[i] / r;
		}

		return result;
	}

	Vector2& Vector2::operator/=(const float& r)
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			(*this)[i] = m_Values[i] / r;
		}

		return *this;
	}

	std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
	{
		stream << "Vector2(" << vector.getX() << "," << vector.getY() << ")";
		return stream;
	}

	bool Vector2::operator!=(const Vector2& r) const
	{
		return !operator==(r);
	}

	bool Vector2::operator==(const Vector2& r) const
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			if ((*this)[i] != r[i])
			{
				return false;
			}
		}
		return true;
	}

	Vector2& Vector2::operator*=(const float& r)
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			(*this)[i] = m_Values[i] * r;
		}

		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& r)
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			(*this)[i] = m_Values[i] - r[i];
		}

		return *this;
	}

	Vector2& Vector2::operator+=(const Vector2& r)
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			(*this)[i] = m_Values[i] + r[i];
		}

		return *this;
	}
}