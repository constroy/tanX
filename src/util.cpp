#include "util.hpp"

SDL_Surface *LoadImage(const char filename[],bool trans)
{
	SDL_Surface *loadedImage=NULL;
	SDL_Surface *optimizedImage=NULL;
	
	loadedImage=SDL_LoadBMP(filename);
	if (loadedImage)
	{
		optimizedImage=SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	if (trans)
	{
		Uint32 color_key=SDL_MapRGB(optimizedImage->format,0XFF,0XFF,0XFF);
		SDL_SetColorKey(optimizedImage,SDL_SRCCOLORKEY,color_key);
	}
	return optimizedImage;
}
void ApplySurface(SDL_Surface *src,SDL_Surface *dst,int x,int y)
{
	SDL_Rect offset={x,y};
	SDL_BlitSurface(src,NULL,dst,&offset);
}
void ApplySurface(SDL_Surface *src,SDL_Surface *dst,SDL_Rect offset)
{
	SDL_BlitSurface(src,NULL,dst,&offset);
}
