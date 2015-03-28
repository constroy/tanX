#ifndef _UTIL_HPP
#define _UTIL_HPP

#include <SDL/SDL.h>

SDL_Surface *LoadImage(const char filename[],bool trans=false);

void ApplySurface(SDL_Surface *src,SDL_Surface *dst,int x,int y);

void ApplySurface(SDL_Surface *src,SDL_Surface *dst,SDL_Rect offset);

#endif
