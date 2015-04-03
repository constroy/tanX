#ifndef _TANK_HPP
#define _TANK_HPP

#include <SDL/SDL.h>
#include "item.hpp"
#include "bullet.hpp"
#include "util.hpp"

class Tank:public Item
{
	private:
		static SDL_Surface *clips[6][6];
		SDL_Surface **clip;
		short hp;
		int reload;
		bool run;
		bool dead;
	public:
		static void LoadClip();
		static void FreeClip();
		Tank(int model,short x,short y,int v=4,int h=40);
		void Ctrl(int cmd);
		void Work();
		bool Ready();
		Bullet Fire();
		void Show(SDL_Surface *screen);
};

#endif
