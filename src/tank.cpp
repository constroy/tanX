#include "tank.hpp"

SDL_Surface *tank_clips[8][8];

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
	if (run)
	{
		rect.x+=dx[dir-1]*vel;
		rect.y+=dy[dir-1]*vel;
	}

}
bool Tank::Ready()
{
	return reload==reload_time;
}
Bullet *Tank::Fire()
{
	int x,y;
	switch (dir)
	{
		case 1:
		{
			x=rect.x+18;
			y=rect.y-4;
			break;
		}
		case 2:
		{
			x=rect.x+18;
			y=rect.y+44;
			break;
		}
		case 3:
		{
			x=rect.x-4;
			y=rect.y+18;
			break;
		}
		case 4:
		{
			x=rect.x+44;
			y=rect.y+18;
			break;
		}
	}
	return new Bullet(0,x,y,16,dir);
}
bool Tank::Dead()
{
	return dead;
}
void Tank::Show(SDL_Surface *screen)
{
	SDL_Rect dst={rect.x,rect.y-8,hp,4};
	SDL_FillRect(screen,&dst,bar_color);
	ApplySurface(image,screen,rect);
}
