#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vec3f
{
private:
	float m_x, m_y, m_z;
public:
	Vec3f(float x = 0, float y = 0, float z = 0) : m_x(x), m_y(y), m_z(z) {}

	float& x() { return m_x; }
	float& y() { return m_y; }
	float& z() { return m_z; }

	Vec3f operator+(const Vec3f& r)
	{
		return { m_x + r.m_x, m_y + r.m_y, m_z + r.m_z };
	}

	Vec3f operator-(const Vec3f& r)
	{
		return { m_x - r.m_x, m_y - r.m_y, m_z - r.m_z};
	}

	Vec3f operator*(float val)
	{
		return { val * m_x, val * m_y, val * m_z};
	}

	Vec3f operator/(float val)
	{
		return { m_x / val, m_y / val, m_z / val };
	}

	float dot(const Vec3f& v)
	{
		return (m_x * v.m_x + m_y * v.m_y + m_z * v.m_z);
	}

	Vec3f cross(const Vec3f& v)
	{
		return { (m_y * v.m_z) - (m_z * v.m_y),
				 (m_z * v.m_x) - (m_x * v.m_z),
				 (m_x * v.m_y) - (m_y * v.m_x)
			   };
	}

	float length()
	{
		return sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2));
	}

	Vec3f unit()
	{
		return (*this / (this->length()));
	}

	Vec3f normalize()
	{
		return (*this / (this->length()));
	}

	friend std::ostream& operator<<(std::ostream& os, const Vec3f& v);
};

inline Vec3f operator*(float val, Vec3f& v)
{
	return v * val;
}

inline std::ostream& operator<<(std::ostream& os, const Vec3f& v)
{
	os << v.m_x << " " << v.m_y << " " << v.m_z << std::endl;
	return os;
}


struct Vec3
{
	unsigned int x, y, z;
};

inline std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
	os << v.x << " " << v.y << " " << v.z << std::endl;
	return os;
}

#endif // !VECTOR_H
