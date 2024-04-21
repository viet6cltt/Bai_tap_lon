
#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include "TextureManager.h"
#include "GameStateMachine.h"
#include "PauseState.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
class Engine
{
public:
	static Engine* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
	}
	bool Init();
	bool Clean();
	void Quit();

	void Update();
	void Render();
	void Events();

	inline bool IsRunning() { return m_IsRunning; }
	inline SDL_Renderer* GetRenderer() { return m_Renderer; }

	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

	void setPlayerType(int type) { player_type = type; }
	int getPlayerType() { return player_type; }

	void setMouse(int x,int y) {
		mouseX = x;
		mouseY = y;
	}
	
	Vector2D getMouse() {
		Vector2D Mouse;
		Mouse.X = mouseX;
		Mouse.Y = mouseY;
		return Mouse;
	}

	int getScores() { return m_scores; }
	void setScores(int score) { m_scores = score; }

	int getTime() { return m_Time; }
	void setTime(int time) { m_Time = time; }
	
private:
	Engine() {}

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	static Engine* s_Instance;
	GameStateMachine* m_pGameStateMachine;
	bool m_IsRunning;

	int m_scores;
	int mouseX, mouseY;
	int screen_type;
	int player_type;
	int m_Time;

	
};

#endif
