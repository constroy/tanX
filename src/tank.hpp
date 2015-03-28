#ifndef _TANK_HPP
#define _TANK_HPP

#include <SDL/SDL.h>
#include "config.hpp"
#include "bullet.hpp"
#include "util.hpp"

extern SDL_Surface *tank_clips[8][8];

class Tank
{
	private:
		SDL_Surface **clips;
		SDL_Surface *image;
		SDL_Rect rect;
		int vel,dir;
		short hp;
		int reload;
		bool run,dead;
	public:
		Tank(int model,short x,short y,int v,int h);
		void Ctrl(int cmd);
		void Work();
		bool Dead();
		bool Ready();
		Bullet *Fire();
		void Show(SDL_Surface *screen);
		
};

#endif
