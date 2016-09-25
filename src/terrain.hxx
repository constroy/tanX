#ifndef _TERRAIN_HXX
#define _TERRAIN_HXX

#include <cstdio>

#include "config.hxx"
#include "item.hxx"

class Terrain {
public:
	Terrain(Terrain &) = delete;
	Terrain(Terrain &&) = delete;
	static Terrain &GetInstance() {
		static Terrain instance;
		return instance;
	}
	char GetGrid(int x, int y) const {	
		return map[x][y];
	}
	bool Hit(const Item &it);
	void LoadMap();
private:
	Terrain() = default;
	~Terrain() = default;
	char map[map_size][map_size];
};

#endif
