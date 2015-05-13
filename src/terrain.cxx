#include "terrain.hxx"

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
bool Terrain::Check(const Item &it)
{
	int x0=it.GetX()/20;
	int x1=(it.GetX()+it.GetW()-1)/20;
	int y0=it.GetY()/20;
	int y1=(it.GetY()+it.GetH()-1)/20;
	for (int i=x0;i<=x1;++i) for (int j=y0;j<=y1;++j)
	{
		if (map[i][j]&it.GetMask()) return true;
	}
	return false;
}
