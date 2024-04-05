#pragma once

#include <SDL.h>
#include "Vector2D.h"

class Collider {
public:
	inline SDL_Rect Get() { return m_Box; }
	inline void SetBuffer(int x, int y, int w, int h) { m_Buffer = { x,y,w,h }; }

	void Set(int x, int y, int w, int h)
	{
		m_Box = {
			x - m_Buffer.x,
			y - m_Buffer.y,
			w - m_Buffer.w,
			h - m_Buffer.h
		};
	}
	inline Vector2D GetPosition() {
		Vector2D m_Position;
		m_Position.X = m_Box.x;
		m_Position.Y = m_Box.y;
		return m_Position;
	}

private:
	SDL_Rect m_Box;
	SDL_Rect m_Buffer;

};