#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>
#include "config.hxx"
#include "display.hxx"
#include "model.hxx"
#include "timer.hxx"

#define DEMO

Mix_Music *bgm=nullptr;

Display *display=nullptr;

Model model;

list<Tank> &tanks=model.tanks;
list<Bullet> &bullets=model.bullets;
Terrain *&terrain=model.terrain;

bool Init()
{
	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING)==-1) return false;
	//Set the window caption
	SDL_WM_SetCaption("tanX",nullptr);
	//Set the window icon
	SDL_WM_SetIcon(SDL_LoadBMP("img/icon.bmp"),nullptr);
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
	bgm=Mix_LoadMUS("snd/tank_draft_mix.mp3");
	if (bgm==nullptr) return false;
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

#ifdef DEMO
	for (int i=0;i<3;++i) for (int j=0;j<3;++j) tanks.push_back(Tank(rand()%5,i*8+4,j*8+12));
	list<Tank>::iterator tank=tanks.begin();
#endif

	Timer timer;	
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
		for (auto i=tanks.begin(),j=tanks.begin();i!=tanks.end();i=j)
		{
			++j;
			if (i->Dead()) tanks.erase(i);
			i->Move(+1);
			if (terrain->Check(*i)) i->Move(-1);
			else
			{
				for (auto k=tanks.begin();k!=tanks.end();++k)
				{
					if (i!=k && Check(*i,*k)) i->Move(-1);
				}
			}
			if (i->Reload())
			{
				bullets.push_back(Bullet(0,i->GetX()+18,i->GetY()+18,i->GetDir(),i->GetPow()));
			}
		}
		for (auto i=bullets.begin(),j=bullets.begin();i!=bullets.end();i=j)
		{
			++j;
			i->Move(+1);
			if (terrain->Check(*i)) bullets.erase(i);
			else
			{
				for (auto k=tanks.begin();k!=tanks.end();++k)
				{
					if (Check(*i,*k))
					{
						k->Damage(i->GetPow());
						bullets.erase(i);
					}
				}
			}
		}
		if (timer.GetTicks()<time_slot) SDL_Delay(time_slot-timer.GetTicks());
	}
	goto LOOP;
	END:
	Mix_HaltMusic();
	exit=true;
	SDL_WaitThread(draw,nullptr);
	CleanUp();
	return 0;
}
