#ifndef _TANK_HPP
#define _TANK_HPP

#include "bullet.hpp"

class Tank:public Item
{
	private:
		int hp;
		int reload;
		bool run;
		bool dead;
	public:
		Tank(int img,int x,int y,int v=4,int h=40);
		void Ctrl(int cmd);
		void Work();
		bool Ready();
		Bullet Fire();
		int GetHp() const;
};

#endif
