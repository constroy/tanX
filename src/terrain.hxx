#ifndef _TERRAIN_HXX
#define _TERRAIN_HXX

#include <cstdio>

#include "config.hxx"
#include "item.hxx"

class Terrain {
public:
	static Terrain *GetInstance() {
		static Terrain instance;
		return &instance;
	}
	void LoadMap();
	bool Hit(const Item &it);
	void Destroy(const Item &it);
	char GetGrid(int x, int y) const {
		return map[x][y];
	}
private:
	Terrain() {}
	char map[map_size][map_size];
};

#endif
