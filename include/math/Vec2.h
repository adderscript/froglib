#pragma once

#include <cmath>
#include <iostream>
#include <raylib.h>

class Vec2
{
  public:
	float x, y;

	// Constructors
	Vec2() : x(0), y(0) {}
	Vec2(float x, float y) : x(x), y(y) {}
	Vec2(const Vector2 &v) : x(v.x), y(v.y) {} // From raylib Vector2

	// Basic math operators
	Vec2 operator+(const Vec2 &other) const
	{
		return Vec2(x + other.x, y + other.y);
	}

	Vec2 operator-(const Vec2 &other) const
	{
		return Vec2(x - other.x, y - other.y);
	}

	inline Vec2 operator*(float scalar) const
	{
		return Vec2(x * scalar, y * scalar);
	}

	Vec2 operator/(float scalar) const { return Vec2(x / scalar, y / scalar); }

	// Assignment operators
	Vec2 &operator+=(const Vec2 &other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2 &operator-=(const Vec2 &other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vec2 &operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vec2 &operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	// Comparison
	bool operator==(const Vec2 &other) const
	{
		return x == other.x && y == other.y;
	}

	// Essential vector operations
	float length() const { return std::sqrt(x * x + y * y); }

	Vec2 normalized() const
	{
		float len = length();
		if (len == 0) return Vec2(0, 0);
		return Vec2(x / len, y / len);
	}

	float distanceTo(const Vec2 &other) const
	{
		return (*this - other).length();
	}

	float dot(const Vec2 &other) const { return x * other.x + y * other.y; }

	// Convert to raylib Vector2
	operator Vector2() const { return Vector2{x, y}; }

	// Static helpers
	static Vec2 zero() { return Vec2(0, 0); }
	static Vec2 one() { return Vec2(1, 1); }
	static Vec2 up() { return Vec2(0, -1); }
	static Vec2 down() { return Vec2(0, 1); }
	static Vec2 left() { return Vec2(-1, 0); }
	static Vec2 right() { return Vec2(1, 0); }
};

// Allow scalar * vector (not just vector * scalar)
inline Vec2 operator*(float scalar, const Vec2 &vec) { return vec * scalar; }

// Print vectors easily
inline std::ostream &operator<<(std::ostream &os, const Vec2 &vec)
{
	os << "(" << vec.x << ", " << vec.y << ")";
	return os;
}
