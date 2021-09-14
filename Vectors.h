#pragma once
#include <math.h>

#define M_PI	3.14159265358979323846264338327950288419716939937510

//Vector2
class Vector2
{
public:
	Vector2()
	{
		x = y = 0.f;
	}

	Vector2(float fx, float fy)
	{
		x = fx;
		y = fy;
	}

	float x, y;

	Vector2 operator+(const Vector2& input) const
	{
		return Vector2{ x + input.x, y + input.y };
	}

	Vector2 operator-(const Vector2& input) const
	{
		return Vector2{ x - input.x, y - input.y };
	}

	Vector2 operator/(float input) const
	{
		return Vector2{ x / input, y / input };
	}

	Vector2 operator*(float input) const
	{
		return Vector2{ x * input, y * input };
	}

	Vector2& operator-=(const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2& operator/=(float input)
	{
		x /= input;
		y /= input;
		return *this;
	}

	Vector2& operator*=(float input)
	{
		x *= input;
		y *= input;
		return *this;
	}

	float length() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	Vector2 normalized() const
	{
		return { x / length(), y / length() };
	}

	float dot_product(Vector2 input) const
	{
		return (x * input.x) + (y * input.y);
	}

	float distance(Vector2 input) const
	{
		return (*this - input).length();
	}

	bool empty() const
	{
		return x == 0.f && y == 0.f;
	}
};


class Vector4
{
public:
	Vector4()
	{
		x = y = z = a = 0.f;
	}

	Vector4(float fx, float fy, float fz, float fa)
	{
		x = fx;
		y = fy;
		z = fz;
		a = fa;
	}

	float x, y, z, a;

	Vector4 operator+(const Vector4& input) const
	{
		return Vector4{ x + input.x, y + input.y, z + input.z, a + input.a };
	}

	Vector4 operator-(const Vector4& input) const
	{
		return Vector4{ x - input.x, y - input.y, z - input.z, a - input.a };
	}

	Vector4 operator/(float input) const
	{
		return Vector4{ x / input, y / input, z / input, a / input };
	}

	Vector4 operator*(float input) const
	{
		return Vector4{ x * input, y * input, z * input, a * input };
	}

	Vector4& operator-=(const Vector4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		a -= v.a;

		return *this;
	}

	Vector4& operator/=(float input)
	{
		x /= input;
		y /= input;
		z /= input;
		a /= input;
		return *this;
	}

	Vector4& operator*=(float input)
	{
		x *= input;
		y *= input;
		z *= input;
		a *= input;
		return *this;
	}

	bool operator==(const Vector4& input) const
	{
		return x == input.x && y == input.y && z == input.z && a == input.a;
	}

	void make_absolute()
	{
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
		a = std::abs(a);
	}

	float length_sqr() const
	{
		return (x * x) + (y * y) + (z * z) + (a * a);
	}

	float length() const
	{
		return std::sqrt(length_sqr());
	}

	float length_2d() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	Vector4 normalized() const
	{
		return { x / length(), y / length(), z / length(), a / length() };
	}

	float dot_product(Vector4 input) const
	{
		return (x * input.x) + (y * input.y) + (z * input.z) + (a * input.a);
	}

	float distance(Vector4 input) const
	{
		return (*this - input).length();
	}

	float distance_2d(Vector4 input) const
	{
		return (*this - input).length_2d();
	}

	void clamp()
	{
		std::clamp(x, -89.f, 89.f);
		std::clamp(y, -180.f, 180.f);

		z = 0.f;
	}

	bool empty() const
	{
		return x == 0.f && y == 0.f && z == 0.f && a == 0.f;
	}
};