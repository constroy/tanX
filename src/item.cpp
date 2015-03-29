#include "item.hpp"

bool Item::Dead()
{
	return dead;
}
void Item::Move()
{
	rect.x+=dx[dir-1]*vel;
	rect.y+=dy[dir-1]*vel;
}
void Item::Show(SDL_Surface *screen)
{
	ApplySurface(image,screen,rect);
}
