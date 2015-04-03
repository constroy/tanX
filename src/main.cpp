#include <bits/stdc++.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "config.hpp"
#include "bullet.hpp"
#include "tank.hpp"
#include "terrain.hpp"
#include "timer.hpp"
#include "util.hpp"

using namespace std;

const SDL_Color text_color={0X1F,0X3F,0XAF};

SDL_Surface *screen=NULL;
SDL_Surface *background=NULL;

SDL_Event event;

TTF_Font *font=NULL;

bool Init()
{
	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING)==-1) return false;
	//Set the window caption
	SDL_WM_SetCaption("TanX",NULL);
	//Set the window icon
	SDL_WM_SetIcon(SDL_LoadBMP("../img/icon.bmp"),NULL);
	//Initialize SDL_ttf
	if (TTF_Init()==-1) return false;
	//Set up screen
	screen=SDL_SetVideoMode(screen_width,screen_height,screen_bpp,SDL_SWSURFACE);
	//If there was an error in setting up the screen
	if (screen==NULL) return false;
	//Initialize the terrain
	Terrain::GetInstance();
	
	return true;
}
bool LoadFiles()
{
	//Load the background image
	//background=LoadImage("../img/background.bmp");
	//if (background==NULL) return false;
	Tank::LoadClip();
	Bullet::LoadClip();
	//Open the font
	font=TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf",24);
	
	
	if (font==NULL) return false;
	return true;
}
void Clean()
{
	//Free the loaded image
	SDL_FreeSurface(background);
	Tank::FreeClip();
	Bullet::FreeClip();
	//Close the font that was used
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}
int main(int argc,char *args[])
{	
	if (!Init()) return -1;
	if (!LoadFiles()) return -1;
	
	Timer timer;
	Terrain *terrain=Terrain::GetInstance();
	Tank tank(3,20,20);
	list<Bullet> bullets;
	
	LOOP:
	{
		timer.Start();
		while (SDL_PollEvent(&event))
		{
			if (event.type==SDL_QUIT) goto END;
			else if (event.type==SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:tank.Ctrl(1);break;
					case SDLK_DOWN:tank.Ctrl(2);break;
					case SDLK_LEFT:tank.Ctrl(3);break;
					case SDLK_RIGHT:tank.Ctrl(4);break;
					case SDLK_SPACE:tank.Ctrl(0);break;
				}
			}
			else if (event.type==SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:tank.Ctrl(-1);break;
					case SDLK_DOWN:tank.Ctrl(-2);break;
					case SDLK_LEFT:tank.Ctrl(-3);break;
					case SDLK_RIGHT:tank.Ctrl(-4);break;
				}
			}
		}
		if (tank.Ready()) bullets.push_back(tank.Fire());
		tank.Work();
		for (list<Bullet>::iterator i=bullets.begin(),j=bullets.begin();i!=bullets.end();i=j)
		{
			++j;
			i->Move();
			//if (terrain.Blocked())
			if (i->Dead()) bullets.erase(i);
		}
		//Fill the screen black
		SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
		
		tank.Show(screen);
		for (list<Bullet>::iterator i=bullets.begin();i!=bullets.end();++i) i->Show(screen);

		//Update Screen
		if (SDL_Flip(screen)==-1) return -1;

		if (timer.GetTicks()<1000/screen_fps)
		{
			SDL_Delay(1000/screen_fps-timer.GetTicks());
		}
	}
	goto LOOP;
	END:
	Clean();
	return 0;
}
