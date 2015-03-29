#ifndef _ITEM_HPP
#define _ITEM_HPP

#include <SDL/SDL.h>
#include "config.hpp"
#include "util.hpp"

class Item
{
	protected:
		SDL_Surface *image;
		SDL_Rect rect;
		int vel,dir;
		int pow;
		bool dead;
	public:
		bool Dead();
		void Move();
		void Show(SDL_Surface *screen);
};

#endif
