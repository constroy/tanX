#include "tank.hpp"

SDL_Surface *Tank::clips[6][6];
SDL_Surface *Tank::bar;

const int bx[]={+18,+18,-4,+44};
const int by[]={-4,+44,+18,+18};

void Tank::LoadClip()
{
	char file_path[256];
	for (int i=0;i<6;++i) for (int j=0;j<5;++j)
	{
		sprintf(file_path,"../img/tank/%d-%d.bmp",i,j);
		clips[i][j]=LoadImage(file_path,true);
	}
	bar=SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA,40,4,32,0,0,0,0);
	SDL_SetAlpha(bar,SDL_SRCALPHA|SDL_RLEACCEL,bar_alpha);
}
void Tank::FreeClip()
{
	for (int i=0;i<6;++i)
		for (int j=0;j<4;++j) SDL_FreeSurface(clips[i][j]);
	SDL_FreeSurface(bar);
}
Tank::Tank(int model,short x,short y,int v,int h)
{
	clip=clips[model];
	image=clip[0];
	rect=(SDL_Rect){(short)(x*20),(short)(y*20),40,40};
	vel=v;
	dir=0;
	hp=h;
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
		image=clip[dir];
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
	SDL_Rect dst=bar->clip_rect;
	dst.w=hp;
	SDL_FillRect(bar,NULL,bar_back_color);
	SDL_FillRect(bar,&dst,bar_front_color);
	ApplySurface(bar,screen,rect.x,(short)(rect.y-8));
	ApplySurface(image,screen,rect);
}
