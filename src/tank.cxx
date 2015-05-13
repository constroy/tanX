#include "tank.hxx"

Tank::Tank(int m,int _x,int _y)
{
	model=m;
	x=_x*20,y=_y*20,w=40,h=40;
	vel=4;
	dir=1;
	hp=8;
	pow=2;
	reload=0;
	die=0;
	run=false;
	mask=TANK;
}
void Tank::Damage(int damage)
{
	if ((hp-=damage)<=0)
	{
		hp=0;
		dir=0;
		run=false;
		die=die_time;
	}
}
void Tank::Execute(int cmd)
{
	if (die) return;
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
