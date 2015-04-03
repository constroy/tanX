#ifndef _TERRAIN_HPP
#define _TERRAIN_HPP

#include "config.hpp"
#include "util.hpp"

class Terrain
{
	private:
		static char map[map_size][map_size];
		static SDL_Surface *clips[128];
		static Terrain *instance;
		Terrain(){}
	public:
		~Terrain();
		static void LoadClip();
		static void FreeClip();
		static void LoadMap();
		static Terrain *GetInstance();
		bool Check(ItemMask mask,int x0,int y0,int x1,int y1);
		void Show(int opt,SDL_Surface *screen);
};

#endif
