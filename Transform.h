
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2D.h"
#include<iostream>

class Transform
{
public:
	float X, Y;

public:
	Transform(float x = 0, float y = 0) :X(x), Y(y) {} //khoi tao X va Y voi gia tri mac dinh = 0
public:
	inline void TranslateX(float x) { X += x; } //dich chuyen dt theo truc X
	inline void TranslateY(float y) { Y += y; } //dich chuyen dt theo truc Y
	inline void Translate(Vector2D v) { X += v.X; Y += v.Y; } //dich chuyen dt theo 1 vector nao do
};

#endif