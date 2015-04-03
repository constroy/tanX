#include "item.hpp"

bool Item::Move()
{
	rect.x+=dx[dir-1]*vel;
	rect.y+=dy[dir-1]*vel;
	if (Terrain::GetInstance()->Check(mask,rect.x,rect.y,rect.x+rect.w-1,rect.y+rect.h-1))
	{
		rect.x-=dx[dir-1]*vel;
		rect.y-=dy[dir-1]*vel;
		return false;
	}
	return true;
}
void Item::Show(SDL_Surface *screen)
{
	ApplySurface(image,screen,rect);
}
