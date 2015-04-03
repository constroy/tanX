#ifndef _UTIL_HPP
#define _UTIL_HPP

#include <cstdio>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

SDL_Surface *LoadImage(const char filename[],bool trans=false);

void ApplySurface(SDL_Surface *src,SDL_Surface *dst,int x,int y);

void ApplySurface(SDL_Surface *src,SDL_Surface *dst,SDL_Rect offset);

#endif
