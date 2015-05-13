#include "bullet.hxx"

Bullet::Bullet(int m,int x,int y,int d,int p)
{
	model=m;
	this->x=x,this->y=y,w=4,h=4;
	vel=24;
	dir=d;
	pow=p;
	run=true;
	mask=BULLET;
}
