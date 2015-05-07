#ifndef _ITEM_HXX
#define _ITEM_HXX

#include "config.hxx"

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

#endif
