#ifndef _ITEM_HPP
#define _ITEM_HPP

#include <SDL/SDL.h>
#include "config.hpp"
#include "util.hpp"
#include "terrain.hpp"

class Item
{
	protected:
		SDL_Surface *image;
		SDL_Rect rect;
		int vel,dir;
		int pow;
		ItemMask mask;
	public:
		bool Dead();
		bool Move();
		void Show(SDL_Surface *screen);
};

#endif
