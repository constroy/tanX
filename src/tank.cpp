#include "tank.hpp"

Tank::Tank(int m,int _x,int _y,int v,int _hp)
{
	model=m;
	x=_x*20,y=_y*20,w=40,h=40;
	vel=v;
	dir=0;
	hp=_hp;
	reload=0;
	run=false;
	mask=TANK;
}
void Tank::Ctrl(int cmd)
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
void Tank::Work()
{
	if (reload) --reload;
	if (run) Move();
}
bool Tank::Ready()
{
	return reload==reload_time;
}
Bullet Tank::Fire()
{	
	return Bullet(0,x+bx[dir-1],y+by[dir-1],dir,pow);
}
int Tank::GetHp() const
{
	return hp;
}
/*
void Show(SDL_Surface *screen)
{
	SDL_Rect dst=bar->clip_rect;
	dst.w=hp;
	SDL_FillRect(bar,NULL,bar_back_color);
	SDL_FillRect(bar,&dst,bar_front_color);
	ApplySurface(bar,screen,rect.x,(short)(rect.y-8));
	ApplySurface(image,screen,rect);
}
*/
