#include "item.hpp"

void Item::Move(int opt)
{
	if (run)
	{
		x+=opt*dx[dir-1]*vel;
		y+=opt*dy[dir-1]*vel;
	}
}

int Item::GetX() const
{
	return x;
}
int Item::GetY() const
{
	return y;
}
int Item::GetW() const
{
	return w;
}
int Item::GetH() const
{
	return h;
}
int Item::GetDir() const
{
	return dir;
}
int Item::GetMask() const
{
	return mask;
}