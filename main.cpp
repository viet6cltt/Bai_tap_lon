﻿#include "Engine.h"
#include "TextureManager.h"
#include "Timer.h"

int main(int argc, char **argv) {
	
	
	Engine::GetInstance()->Init();

	while (Engine::GetInstance()->IsRunning())
	{
		Timer::GetInstance()->Tick();
		Engine::GetInstance()->Events();
		Engine::GetInstance()->Update();
		Engine::GetInstance()->Render();
		
		
	}

	Engine::GetInstance()->Clean();
	return 0;
}