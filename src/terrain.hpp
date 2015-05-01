#ifndef _TERRAIN_HPP
#define _TERRAIN_HPP

#include <cstdio>
#include "config.hpp"

class Terrain
{
	private:
		char map[map_size][map_size];
		Terrain(){}
	public:
		static Terrain *GetInstance();
		void LoadMap();
		bool Check(ItemMask mask,int x0,int x1,int y0,int y1);
		char GetGrid(int x,int y) const;
};

#endif
