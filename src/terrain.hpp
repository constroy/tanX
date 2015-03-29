#ifndef _TERRAIN_HPP
#define _TERRAIN_HPP

#include <cstdio>
#include "config.hpp"

class Terrain
{
	private:
		char map[map_size][map_size];
		static Terrain *instance;
		Terrain();
	public:
		~Terrain();
		static Terrain *GetInstance();
};

#endif
