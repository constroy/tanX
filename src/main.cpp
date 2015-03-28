#include <bits/stdc++.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "config.hpp"
#include "bullet.hpp"
#include "tank.hpp"
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
	//Initialize SDL_ttf
	if (TTF_Init()==-1) return false;
	//Set up screen
	screen=SDL_SetVideoMode(screen_width,screen_height,screen_bpp,SDL_SWSURFACE);
	//If there was an error in setting up the screen
	if (screen==NULL) return false;
	//Set the window caption
	SDL_WM_SetCaption("TanX",NULL);
	return true;
}
bool LoadFiles()
{
	char file_path[256];
	
	//Load the background image
	background=LoadImage("../img/background.bmp");
		
	for (int i=0;i<=0;++i) for (int j=0;j<=4;++j)
	{
		sprintf(file_path,"../img/tank/%d-%d.bmp",i,j);
		tank_clips[i][j]=LoadImage(file_path,true);
	}
	for (int i=0;i<=0;++i)
	{
		sprintf(file_path,"../img/bullet/%d.bmp",i);
		bullet_clips[0]=LoadImage(file_path);
	}
	//Open the font
	font=TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf",24);
	if (background==NULL) return false;
	if (font==NULL) return false;
	return true;
}
void Clean()
{
	//Free the loaded image
	SDL_FreeSurface(background);
	for (int i=0;i<=0;++i) for (int j=0;j<4;++j) SDL_FreeSurface(tank_clips[i][j]);
	for (int i=1;i<=4;++i) SDL_FreeSurface(bullet_clips[i]);

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
	Tank tank(0,20,20,4,40);
	list<Bullet*> bullets;
	
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
		for (list<Bullet*>::iterator i=bullets.begin(),j=bullets.begin();i!=bullets.end();i=j)
		{
			++j;
			(*i)->Move();
			if ((*i)->Dead())
			{
				delete (*i);
				bullets.erase(i);
			}
		}
		//Fill the screen black
		SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
		
		tank.Show(screen);
		for (list<Bullet*>::iterator i=bullets.begin();i!=bullets.end();++i) (*i)->Show(screen);

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
