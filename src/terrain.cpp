#include "terrain.hpp"

char Terrain::map[map_size][map_size];
SDL_Surface *Terrain::clips[128];
Terrain *Terrain::instance=NULL;


void Terrain::LoadClip()
{
	char file_path[256];
	for (int i=0;i<128;++i)
	{
		sprintf(file_path,"../img/terrain/%X.bmp",i);
		clips[i]=LoadImage(file_path,true);
	}
}
void Terrain::FreeClip()
{
	for (int i=0;i<128;++i) SDL_FreeSurface(clips[i]);
}
void Terrain::LoadMap()
{
	for (int i=0;i<map_size;++i) for (int j=0;j<map_size;++j) map[i][j]=' ';
	/*
	FILE *file=fopen("../map/demo.map","r");
	for (int i=0;i<map_size;i+=2)
	{
		for (int j=0;j<map_size;j+=2)
		{
			map[i][j]=map[i+1][j]=map[i][j+1]=map[i+1][j+1]=getc(file);
		}
		getc(file);
	}
	*/
	for (int i=6;i<24;++i) for (int j=6;j<12;++j) map[i][j]='$';
	for (int i=0;i<map_size;++i) map[i][0]=map[i][map_size-1]='.';
	for (int j=0;j<map_size;++j) map[0][j]=map[map_size-1][j]='.';
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
bool Terrain::Check(ItemMask mask,int x0,int y0,int x1,int y1)
{
	x0/=20,y0/=20;
	x1/=20,y1/=20;
	for (int i=x0;i<=x1;++i) for (int j=y0;j<=y1;++j)
	{
		if (map[i][j]&mask) return true;
	}
	return false;
}
void Terrain::Show(int opt,SDL_Surface *screen)
{
	for (int i=0;i<map_size;++i) for (int j=0;j<map_size;++j)
	{
		if ((map[i][j]&1)==opt) ApplySurface(clips[(int)map[i][j]],screen,i*20,j*20);
	}
}
