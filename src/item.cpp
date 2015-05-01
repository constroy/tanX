#include "item.hpp"

bool Item::Move()
{
	x+=dx[dir-1]*vel;
	y+=dy[dir-1]*vel;
	if (Terrain::GetInstance()->Check(mask,x/20,(x+w-1)/20,y/20,(y+h-1)/20))
	{
		x-=dx[dir-1]*vel;
		y-=dy[dir-1]*vel;
		return false;
	}
	return true;
}
int Item::GetModel() const
{
	return model;
}
int Item::GetX() const
{
	return x;
}
int Item::GetY() const
{
	return y;
}
int Item::GetDir() const
{
	return dir;
}
