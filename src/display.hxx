#ifndef _DISPLAY_HXX
#define _DISPLAY_HXX

#include <cstdio>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "config.hxx"
#include "model.hxx"
#include "timer.hxx"

class Display
{
	private:
		SDL_Surface *screen;
		SDL_Surface *background;
		SDL_Surface *bar[41];
		SDL_Surface *bullet_clips[5];
		SDL_Surface *tank_clips[5][5];
		SDL_Surface *terrain_clips[128];
		SDL_Surface *LoadImage(const char filename[],bool trans=false);
		void ApplySurface(SDL_Surface *src,SDL_Surface *dst,short x,short y);
		void ApplySurface(SDL_Surface *src,SDL_Surface *dst,SDL_Rect offset);
		void ShowTerrain(Terrain *terrain,bool opt);
	public:
		static Display *GetInstance();
		void Init();
		void Show(const Model &model,const bool *exit);
		void Quit();
};

#endif
