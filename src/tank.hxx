#ifndef _TANK_HXX
#define _TANK_HXX

#include "bullet.hxx"

class Tank:public Item
{
	private:
		int hp;
		int reload;
		bool dead;
	public:
		Tank(int img,int x,int y);
		void Execute(int cmd);
		bool Reload();
		Bullet Fire() const;
		int GetHp() const;
};

#endif
