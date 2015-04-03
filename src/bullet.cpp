#include "bullet.hpp"

SDL_Surface *Bullet::clips[6];

void Bullet::LoadClip()
{
	char file_path[256];
	for (int i=0;i<1;++i)
	{
		sprintf(file_path,"../img/bullet/%d.bmp",i);
		clips[0]=LoadImage(file_path);
	}
}
void Bullet::FreeClip()
{
	for (int i=0;i<1;++i) SDL_FreeSurface(clips[i]);
}
Bullet::Bullet(int model,short x,short y,int d,int p)
{
	image=clips[model];
	rect=(SDL_Rect){x,y,4,4};
	vel=16;
	dir=d;
	pow=p;
	dead=false;
}
