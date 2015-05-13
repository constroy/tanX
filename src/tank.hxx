#ifndef _TANK_HXX
#define _TANK_HXX

#include "item.hxx"

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
		bool Reload();
};
inline bool Tank::Dead()
{
	return die && --die==0;
}
inline int Tank::GetHp() const
{
	return hp;
}
inline bool Tank::Reload()
{
	if (!die && reload) return reload--==reload_time;
	else return false;
}

#endif
