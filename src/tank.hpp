#ifndef _TANK_HPP
#define _TANK_HPP

#include <SDL/SDL.h>
#include "item.hpp"
#include "bullet.hpp"
#include "util.hpp"

extern SDL_Surface *tank_clips[8][8];

class Tank:public Item
{
	private:
		SDL_Surface **clips;
		short hp;
		int reload;
		bool run;
	public:
		Tank(int model,short x,short y,int v=4,int h=40);
		void Ctrl(int cmd);
		void Work();
		bool Ready();
		Bullet Fire();
		void Show(SDL_Surface *screen);
};

#endif
