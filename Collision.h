#ifndef __Collision__
#define __Collision__

#include <SDL.h>
#include "Vector2D.h"

// hardcode and may consider adapt other solution to deal with collision
const static int s_buffer = 4;

static bool RectRect(SDL_Rect *A, SDL_Rect *B)
{
	int aHBuf = /*A->h / s_buffer*/ 0;
	int aWBuf = /*A->w / s_buffer*/ 0;

	int bHBuf = /*B->h / s_buffer*/ 0;
	int bWBuf = /*B->w / s_buffer*/ 0;

	if (A->y + A->h - aHBuf <= B->y + bHBuf)
		return false;
	if (A->y + aHBuf >= B->y + B->h - bHBuf)
		return false;
	if (A->x + A->w - aWBuf <= B->x + bWBuf)
		return false;
	if (A->x + aWBuf >= B->x + B->w - bWBuf)
		return false;

	return true;
}

#endif