#include "bullet.hxx"

Bullet::Bullet(int m,int _x,int _y,int d,int p)
{
	model=m;
	x=_x,y=_y,w=4,h=4;
	vel=24;
	dir=d;
	pow=p;
	run=true;
	mask=BULLET;
}
