#ifndef _BULLET_HPP
#define _BULLET_HPP

#include <SDL/SDL.h>
#include "config.hpp"
#include "util.hpp"

extern SDL_Surface *bullet_clips[8];

class Bullet
{
	private:
		SDL_Surface *image;
		SDL_Rect rect;
		int vel,dir;
		bool dead;
	public:
		Bullet(int model,short x,short y,int v,int d);
		void Move();
		bool Dead();
		void Show(SDL_Surface *screen);
};

#endif

