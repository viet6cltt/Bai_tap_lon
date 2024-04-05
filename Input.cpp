#include "Input.h"
#include "Engine.h"

Input* Input::s_Instance = nullptr;

Input::Input()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr); //lay trang thai hien tai cua ban phim
}

void Input::Listen()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: Engine::GetInstance()->Quit(); break;
		case SDL_KEYDOWN: KeyDown(); break;
		case SDL_KEYUP:KeyUp(); break;
		}
	}
}

bool Input::GetKeyDown(SDL_Scancode key)
{
	if (m_KeyStates[key] == 1)
	{
		return true;
	}
	return false;
}

void Input::KeyUp()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

int Input::GetAxisKey(Axis axis)
{
	switch (axis) {
	case HORIZONTAL:
		if (GetKeyDown(SDL_SCANCODE_D) || GetKeyDown(SDL_SCANCODE_RIGHT)) return 1;
		if (GetKeyDown(SDL_SCANCODE_A) || GetKeyDown(SDL_SCANCODE_LEFT)) return -1;
		break;
	case VERTICAL:
		if (GetKeyDown(SDL_SCANCODE_W) || GetKeyDown(SDL_SCANCODE_UP)) return -1;
		if (GetKeyDown(SDL_SCANCODE_S) || GetKeyDown(SDL_SCANCODE_DOWN)) return 1;
		break;
	default:
		return 0;
	}
	return 0;
}
bool Input::GetLeftMouseButton()
{
	int x, y;
	Uint32 state = SDL_GetMouseState(&x, &y);
	if (state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		return true;
	}
	return false;
}

int Input::GetMouseX()
{
	int x;
	SDL_GetMouseState(&x, NULL);
	return x;
}

int Input::GetMouseY()
{
	int y;
	SDL_GetMouseState(NULL, &y);
	return y;
}

