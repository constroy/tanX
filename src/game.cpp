#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>
#include "config.hpp"
#include "display.hpp"
#include "model.hpp"
#include "timer.hpp"

//Font
const SDL_Color text_color={0X1F,0X3F,0XAF};

TTF_Font *font=NULL;
Mix_Music *bgm=NULL;

Display *display=NULL;

Model model;

list<Tank> &tanks=model.tanks;
list<Bullet> &bullets=model.bullets;
Terrain *&terrain=model.terrain;

bool Init()
{
	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING)==-1) return false;
	//Initialize SDL_ttf
	if (TTF_Init()==-1) return false;
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)==-1) return false;
	//Set the window caption
	SDL_WM_SetCaption("tanX",NULL);
	//Set the window icon
	SDL_WM_SetIcon(SDL_LoadBMP("../img/icon.bmp"),NULL);
	//Get an instance of terrain
	terrain=Terrain::GetInstance();
	//Get an instance of display
	display=Display::GetInstance();
	//Init the display
	display->Init();
	return true;
}
bool LoadFiles()
{
	terrain->LoadMap();
	//Open the font
	font=TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf",24);
	if (font==NULL) return false;
	//Load the background music
	bgm=Mix_LoadMUS("../snd/tank_draft_mix.mp3");
	if (bgm==NULL) return false;
	return true;
}
void CleanUp()
{
	display->Quit();
	//Free the music
    Mix_FreeMusic(bgm);
	//Close the font that was used
	TTF_CloseFont(font);
	//Quit SDL_mixer
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}
int Show(void *data)
{
	display->Show(model);
	return 0;
}
int main(int argc,char *args[])
{	
	if (!Init()) return -1;
	if (!LoadFiles()) return -1;
	if (!Mix_PlayingMusic()) if (Mix_PlayMusic(bgm,-1)==-1) return -1;

	SDL_Thread *draw=SDL_CreateThread(Show,NULL);

	model.tanks.push_back(Tank(4,1,1,4,25));
	Timer timer;
	LOOP:
	{
		timer.Start();
		list<Tank>::iterator tank=tanks.begin();
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type==SDL_QUIT) goto END;
			else if (event.type==SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:tank->Ctrl(1);break;
					case SDLK_DOWN:tank->Ctrl(2);break;
					case SDLK_LEFT:tank->Ctrl(3);break;
					case SDLK_RIGHT:tank->Ctrl(4);break;
					case SDLK_SPACE:tank->Ctrl(0);break;
				}
			}
			else if (event.type==SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:tank->Ctrl(-1);break;
					case SDLK_DOWN:tank->Ctrl(-2);break;
					case SDLK_LEFT:tank->Ctrl(-3);break;
					case SDLK_RIGHT:tank->Ctrl(-4);break;
				}
			}
		}
		for (list<Tank>::iterator i=tanks.begin();i!=tanks.end();++i)
		{
			if (i->Ready()) bullets.push_back(i->Fire());
		}
		for (list<Bullet>::iterator i=bullets.begin(),j=bullets.begin();i!=bullets.end();i=j)
		{
			++j;
			if (!i->Move()) bullets.erase(i);
		}
		for (list<Tank>::iterator i=tanks.begin();i!=tanks.end();++i) i->Work();
		
		if (timer.GetTicks()<time_slot) SDL_Delay(time_slot-timer.GetTicks());
	}
	goto LOOP;
	END:
	SDL_KillThread(draw);
	CleanUp();
	return 0;
}
