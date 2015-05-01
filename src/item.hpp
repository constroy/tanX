#ifndef _ITEM_HPP
#define _ITEM_HPP

#include "config.hpp"
#include "terrain.hpp"

class Item
{
	protected:
		int model;
		int x,y,w,h;
		int vel,dir;
		int pow;
		ItemMask mask;
	public:
		bool Move();
		int GetModel() const;
		int GetX() const;
		int GetY() const;
		int GetDir() const;
};
#endif
