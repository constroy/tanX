#include "item.hxx"

void Item::Move(int opt)
{
	if (run)
	{
		x+=opt*dx[dir-1]*vel;
		y+=opt*dy[dir-1]*vel;
	}
}
