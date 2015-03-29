#include "terrain.hpp"

Terrain *Terrain::instance;

Terrain::Terrain()
{
	FILE *file=fopen("../map/demo.map","r");
	for (int i=0;i<map_size;i+=2)
	{
		for (int j=0;j<map_size;j+=2)
		{
			map[i][j]=map[i+1][j]=map[i][j+1]=map[i+1][j+1]=getc(file);
		}
		getc(file);
	}
	for (int i=0;i<map_size;++i) map[i][0]=map[i][map_size-1]='/';
	for (int j=0;j<map_size;++j) map[0][j]=map[map_size-1][j]='/';
}
Terrain::~Terrain()
{
	instance=NULL;
}
Terrain *Terrain::GetInstance()
{
	if (instance==NULL) instance=new Terrain;
	return instance;
}
