#include "tank.hpp"

SDL_Surface *tank_clips[8][8];

const int bx[]={+18,+18,-4,+44};
const int by[]={-4,+44,+18,+18};

Tank::Tank(int model,short x,short y,int v,int h)
{
	clips=tank_clips[model];
	image=clips[1];
	rect=(SDL_Rect){x,y,40,40};
	vel=v;
	dir=0;
	hp=h;
	reload=0;
	run=false;
}
void Tank::Ctrl(int cmd)
{
	if (cmd>0)
	{
		run=true;
		dir=cmd;
		image=clips[dir];
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
	int x,y;
	x=rect.x+bx[dir-1];
	y=rect.y+by[dir-1];
	return Bullet(0,x,y,dir,pow);
}
void Tank::Show(SDL_Surface *screen)
{
	SDL_Rect dst={rect.x,rect.y-8,hp,4};
	SDL_FillRect(screen,&dst,bar_color);
	ApplySurface(image,screen,rect);
}
