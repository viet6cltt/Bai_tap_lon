#include "Timer.h"
#include <SDL.h>
#include <iostream>

Timer* Timer::s_Instance = nullptr;

void Timer::Tick()
{
	m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (TARGET_FPS / 1000.0f);

	if (m_DeltaTime > TARGET_DEALTATIME)
		m_DeltaTime = TARGET_DEALTATIME;


	m_LastTime = SDL_GetTicks();

}