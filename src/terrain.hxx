#ifndef _TERRAIN_HXX
#define _TERRAIN_HXX

#include <cstdio>

#include "config.hxx"
#include "item.hxx"

class Terrain
{
	private:
		char map[map_size][map_size];
		Terrain(){}
	public:
		static Terrain *GetInstance();
		void LoadMap();
		bool Hit(const Item &it);
		void Destroy(const Item &it);
		char GetGrid(int x,int y) const;
};

inline char Terrain::GetGrid(int x,int y) const
{
	return map[x][y];
}

#endif
