#ifndef _BULLET_HPP
#define _BULLET_HPP

#include <SDL/SDL.h>
#include "item.hpp"
#include "util.hpp"

extern SDL_Surface *bullet_clips[8];

class Bullet:public Item
{
	public:
		Bullet(int model,short x,short y,int d,int p);
};

#endif

