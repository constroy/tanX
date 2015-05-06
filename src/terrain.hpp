#ifndef _TERRAIN_HPP
#define _TERRAIN_HPP

#include <cstdio>
#include "config.hpp"
#include "item.hpp"

class Terrain
{
	private:
		char map[map_size][map_size];
		Terrain(){}
	public:
		static Terrain *GetInstance();
		void LoadMap();
		bool Check(const Item &it);
		char GetGrid(int x,int y) const;
};

#endif
