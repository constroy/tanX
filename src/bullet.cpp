#include "bullet.hpp"

SDL_Surface *bullet_clips[8];

Bullet::Bullet(int model,short x,short y,int v,int d)
{
	image=bullet_clips[model];
	rect=(SDL_Rect){x,y,4,4};
	vel=v;
	dir=d;
	dead=false;
}
void Bullet::Move()
{
	if (run)
	{
		rect.x+=dx[dir-1]*vel;
		rect.y+=dy[dir-1]*vel;
	}
}
bool Bullet::Dead()
{
	return dead;
}
void Bullet::Show(SDL_Surface *screen)
{
	ApplySurface(image,screen,rect);
}
