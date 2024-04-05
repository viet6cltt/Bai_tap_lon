
#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>

class Vector2D
{
public:
	float X, Y;
public:
	Vector2D(float x = 0, float y = 0) : X(x), Y(y) {}
public:
	//addition +
	inline Vector2D operator+(const Vector2D& v2) const
	{
		return Vector2D(X + v2.X, Y + v2.Y);
	}

	//difference - 
	inline Vector2D operator-(const Vector2D& v2) const
	{
		return Vector2D(X - v2.X, Y - v2.Y);
	}

	//multiplication
	inline Vector2D operator*(const float scalar) const
	{
		return Vector2D(X * scalar, Y * scalar);
	}
	// Normalize
	Vector2D& Normalize()
		{
		float length = sqrt(X * X + Y * Y);
		if (length > 0) {   // we never want to divide by zero
			float invLength = 1.0f / length;
			X *= invLength;
			Y *= invLength;
		}
		return *this;
	}

	static float Distance(const Vector2D& v1, const Vector2D& v2)
	{
		float dx = v2.X - v1.X;
		float dy = v2.Y - v1.Y;
		return sqrt(dx * dx + dy * dy);
	}

};

#endif
