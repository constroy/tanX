#ifndef _BULLET_HPP
#define _BULLET_HPP

#include <SDL/SDL.h>
#include "item.hpp"
#include "util.hpp"

class Bullet:public Item
{
	private:
		static SDL_Surface *clips[6];
	public:
		static void LoadClip();
		static void FreeClip();
		Bullet(int model,short x,short y,int d,int p);
		void Show(SDL_Surface *screen);
};

#endif

