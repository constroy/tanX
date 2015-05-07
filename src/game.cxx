#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>
#include "config.hxx"
#include "display.hxx"
#include "model.hxx"
#include "timer.hxx"

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
	//Set the window caption
	SDL_WM_SetCaption("tanX",NULL);
	//Set the window icon
	SDL_WM_SetIcon(SDL_LoadBMP("../img/icon.bmp"),NULL);
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)==-1) return false;
	//Get an instance of terrain
	terrain=Terrain::GetInstance();
	//Get an instance of display
	display=Display::GetInstance();
	//Init the display
	display->Init();
	//Load the map
	terrain->LoadMap();
	//Load the background music
	bgm=Mix_LoadMUS("../snd/tank_draft_mix.mp3");
	if (bgm==NULL) return false;
	return true;
}
void CleanUp()
{
	//Quit display
	display->Quit();
	//Free the music
    Mix_FreeMusic(bgm);
	//Quit SDL_mixer
	Mix_CloseAudio();
	SDL_Quit();
}
int Show(void *exit)
{
	display->Show(model,(bool*)exit);
	return 0;
}
bool Check(const Item &a,const Item &b)
{
	if (a.GetX()>=b.GetX()+b.GetW()) return false;
	if (a.GetX()+a.GetW()<=b.GetX()) return false;
	if (a.GetY()>=b.GetY()+b.GetH()) return false;
	if (a.GetY()+a.GetH()<=b.GetY()) return false;
	return true;
}
int main(int argc,char *args[])
{	
	if (!Init()) return -1;

	//Start drwing
	bool exit=false;
	SDL_Thread *draw=SDL_CreateThread(Show,&exit);
	//Play the BGM
	if (!Mix_PlayingMusic()) if (Mix_PlayMusic(bgm,-1)==-1) return -1;
	tanks.push_back(Tank(1,1,1));
	tanks.push_back(Tank(4,16,24));
	Timer timer;

	list<Tank>::iterator tank=tanks.begin();
	LOOP:
	{
		timer.Start();
		
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type==SDL_QUIT) goto END;
			else if (event.type==SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:tank->Execute(1);break;
					case SDLK_DOWN:tank->Execute(2);break;
					case SDLK_LEFT:tank->Execute(3);break;
					case SDLK_RIGHT:tank->Execute(4);break;
					case SDLK_SPACE:tank->Execute(0);break;
				}
			}
			else if (event.type==SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:tank->Execute(-1);break;
					case SDLK_DOWN:tank->Execute(-2);break;
					case SDLK_LEFT:tank->Execute(-3);break;
					case SDLK_RIGHT:tank->Execute(-4);break;
				}
			}
		}
		for (list<Tank>::iterator i=tanks.begin();i!=tanks.end();++i)
		{
			
			i->Move(+1);
			if (terrain->Check(*i)) i->Move(-1);
			else
			{
				for (list<Tank>::iterator j=tanks.begin();j!=tanks.end();++j)
				{
					if (i!=j && Check(*i,*j)) i->Move(-1);
				}
			}
			if (i->Reload()) bullets.push_back(i->Fire());
		}
		for (list<Bullet>::iterator i=bullets.begin(),j=bullets.begin();i!=bullets.end();i=j)
		{
			++j;
			i->Move(+1);
			if (terrain->Check(*i)) bullets.erase(i);
			else
			{
				for (list<Tank>::iterator k=tanks.begin();k!=tanks.end();++k)
				{
					if (Check(*i,*k)) bullets.erase(i);
				}
			}
		}
		if (timer.GetTicks()<time_slot) SDL_Delay(time_slot-timer.GetTicks());
	}
	goto LOOP;
	END:
	Mix_HaltMusic();
	exit=true;
	SDL_WaitThread(draw,NULL);
	CleanUp();
	return 0;
}
