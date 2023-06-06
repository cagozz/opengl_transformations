#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vec4f
{
private:
	float m_x, m_y, m_z, m_w;
public:
	Vec4f(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) {}

	float x() { return m_x; }
	float y() { return m_y; }
	float z() { return m_z; }
	float w() { return m_w; }

	Vec4f operator+(const Vec4f& r)
	{
		return { m_x + r.m_x, m_y + r.m_y, m_z + r.m_z, m_w + r.m_w };
	}

	Vec4f operator-(const Vec4f& r)
	{
		return { m_x - r.m_x, m_y - r.m_y, m_z - r.m_z, m_w - r.m_w };
	}

	Vec4f operator*(float val)
	{
		return { val * m_x, val * m_y, val * m_z, val * m_w };
	}

	float dot(const Vec4f& v)//like vec3
	{
		return (m_x * v.m_x + m_y * v.m_y + m_z * v.m_z);
	}

	Vec4f cross(const Vec4f& v)//like vec3
	{
		return { (m_y * v.m_z) - (m_z * v.m_y),
				 (m_z * v.m_x) - (m_x * v.m_z),
				 (m_x * v.m_y) - (m_y * v.m_x),
											0 
			   };
	}

	friend std::ostream& operator<<(std::ostream& os, const Vec4f& v);
};

inline Vec4f operator*(float val, Vec4f& v)
{
	return v * val;
}

inline std::ostream& operator<<(std::ostream& os, const Vec4f& v)
{
	os << v.m_x << " " << v.m_y << " " << v.m_z << " " << v.m_w << std::endl;
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
