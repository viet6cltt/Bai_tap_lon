#pragma once

#include <string>

class GameState
{
public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual bool OnEnter() = 0;
	virtual bool OnExit() = 0;

	virtual std::string getStateID() const = 0;
};