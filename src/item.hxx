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
		Item(int m,int x,int y,int w,int h,int v,int d,int p,bool run,ItemMask mask);
		void Move(int opt);
		int GetModel() const;
		int GetX() const;
		int GetY() const;
		int GetW() const;
		int GetH() const;
		int GetDir() const;
		int GetPow() const;
		ItemMask GetMask() const;
};

inline int Item::GetModel() const
{
	return model;
}
inline int Item::GetX() const
{
	return x;
}
inline int Item::GetY() const
{
	return y;
}
inline int Item::GetW() const
{
	return w;
}
inline int Item::GetH() const
{
	return h;
}
inline int Item::GetDir() const
{
	return dir;
}
inline int Item::GetPow() const
{
	return pow;
}
inline ItemMask Item::GetMask() const
{
	return mask;
}

#endif
