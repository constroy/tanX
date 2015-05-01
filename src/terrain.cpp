#include "terrain.hpp"

Terrain *Terrain::GetInstance()
{
	static Terrain instance;
	return &instance;
}
void Terrain::LoadMap()
{
	FILE *file=fopen("../map/demo.map","r");
	for (int j=0;j<map_size;++j)
	{
		for (int i=0;i<map_size;++i) map[i][j]=getc(file);
		getc(file);
	}
	fclose(file);
}
bool Terrain::Check(ItemMask mask,int x0,int x1,int y0,int y1)
{
	for (int i=x0;i<=x1;++i) for (int j=y0;j<=y1;++j)
	{
		if (map[i][j]&mask) return true;
	}
	return false;
}
char Terrain::GetGrid(int x,int y) const
{
	return map[x][y];
}
