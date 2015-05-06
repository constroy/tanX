#include "tank.hpp"

Tank::Tank(int m,int _x,int _y)
{
	model=m;
	x=_x*20,y=_y*20,w=40,h=40;
	vel=4;
	dir=1;
	hp=40;
	reload=0;
	run=false;
	mask=TANK;
}
void Tank::Execute(int cmd)
{
	if (cmd>0)
	{
		run=true;
		dir=cmd;
	}
	else if (cmd<0)
	{
		if (cmd==-dir) run=false;
	}
	else
	{
		if (!reload) reload=reload_time;
	}
}
bool Tank::Reload()
{
	if (reload) return reload--==reload_time;
	return false;
}
Bullet Tank::Fire() const
{	
	return Bullet(0,x+18,y+18,dir,pow);
}
int Tank::GetHp() const
{
	return hp;
}
