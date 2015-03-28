#include "terrain.hpp"


//For test demo
void GenTerrain()
{
	for (int i=0;i<map_size;++i) terrain[i][0]=terrain[i][map_size-1]='/';
	for (int j=0;j<map_size;++j) terrain[0][j]=terrain[map_size-1][j]='/';
}
void ReadTerrain()
{
	FILE *file=fopen("demo.map","r");
	for (int i=0;i<map_size;++i)
	{
		for (int j=0;j<map_size;++j)
		{
			terrain[i][j]=getchar();
		}
		getchar();
	}
}
