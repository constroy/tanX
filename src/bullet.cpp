#include "bullet.hpp"

SDL_Surface *bullet_clips[8];

Bullet::Bullet(int model,short x,short y,int d,int p)
{
	image=bullet_clips[model];
	rect=(SDL_Rect){x,y,4,4};
	vel=16;
	dir=d;
	pow=p;
	dead=false;
}
