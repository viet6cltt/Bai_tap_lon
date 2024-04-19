#pragma once

#include "GameObject.h"
#include <string>
#include "Collider.h"
#include "Animation.h"
#include "RigidBody.h"

class RangedType : public GameObject
{
public:
	RangedType(Properties* props) : GameObject(props){}

	virtual void Activate(Vector2D,Vector2D) = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
protected:
	std::string m_Name;
};

