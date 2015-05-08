#ifndef _TANK_HXX
#define _TANK_HXX

#include "bullet.hxx"

class Tank:public Item
{
	private:
		int hp;
		int reload;
		int die;
	public:
		Tank(int img,int x,int y);
		void Damage(int damage);
		bool Dead();
		void Execute(int cmd);
		int GetHp() const;
		Bullet Fire() const;
		bool Reload();
};

#endif
