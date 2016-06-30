#ifndef _DISPLAY_HXX
#define _DISPLAY_HXX

#include <SDL/SDL.h>

#include "model.hxx"
#include "terrain.hxx"

class Display
{
	private:
		SDL_Surface *screen;
		SDL_Surface *background;
		SDL_Surface *bar[9];
		SDL_Surface *bullet_clips[5];
		SDL_Surface *tank_clips[5][5];
		SDL_Surface *terrain_clips[128];
		SDL_Surface *LoadImage(const char filename[],bool trans=false);
		void ShowTerrain(Terrain *terrain,bool opt);
	public:
		static Display *GetInstance();
		void Init();
		void Quit();
		void Show(const Model &model,const bool *exit);
};

#endif
