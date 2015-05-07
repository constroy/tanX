#ifndef _ITEM_HPP
#define _ITEM_HPP

#include "config.hpp"

class Item
{
	protected:
		int model;
		int x,y,w,h;
		int vel,dir;
		int pow;
		bool run;
		ItemMask mask;
	public:
		void Move(int opt);
		int GetModel() const;
		int GetX() const;
		int GetY() const;
		int GetW() const;
		int GetH() const;
		int GetDir() const;
		int GetMask() const;
};
static int Item::GetModel() const
{
	return model;
}
#endif
