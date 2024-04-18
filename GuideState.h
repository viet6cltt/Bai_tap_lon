#pragma onced

#include "GameState.h"
#include "GameObject.h"
#include <vector>
#include "Engine.h"
#include <string>

#include "Engine.h"

class GuideState : public GameState
{
public:
	virtual void Update(float dt);
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string getStateID() const { return s_guideID; }
private:
	static void s_guidetoMain();

	static const std::string s_guideID;

	std::vector<MenuButton*> m_buttons;

	bool is_Out;

};

