#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>
#include "client.hxx"
#include "config.hxx"
#include "display.hxx"
#include "model.hxx"
#include "timer.hxx"

Mix_Music *bgm=nullptr;

Display *display=nullptr;

Model model;

list<Tank> &tanks=model.tanks;
list<Bullet> &bullets=model.bullets;
Terrain *&terrain=model.terrain;
Client *client;

int myid,id,cmd,num;

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
int Ctrl(void *exit)
{
	Timer timer;
	SDL_Event event;
	while (!*(bool *)exit)
	{
		timer.Start();
		while (SDL_PollEvent(&event))
		{
			if (event.type==SDL_QUIT)
			{
				*(bool *)exit=true;
			}
			else if (event.type==SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:cmd=1;break;
					case SDLK_DOWN:cmd=2;break;
					case SDLK_LEFT:cmd=3;break;
					case SDLK_RIGHT:cmd=4;break;
					case SDLK_SPACE:cmd=0;break;
				}
				client->Send(myid,cmd);
			}
			else if (event.type==SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:cmd=-1;break;
					case SDLK_DOWN:cmd=-2;break;
					case SDLK_LEFT:cmd=-3;break;
					case SDLK_RIGHT:cmd=-4;break;
				}
				client->Send(myid,cmd);
			}
		}
		if (timer.GetTicks()<time_slot) SDL_Delay(time_slot-timer.GetTicks());
	}
}
bool Check(const Item &a,const Item &b)
{
	if (a.GetX()>=b.GetX()+b.GetW()) return false;
	if (a.GetX()+a.GetW()<=b.GetX()) return false;
	if (a.GetY()>=b.GetY()+b.GetH()) return false;
	if (a.GetY()+a.GetH()<=b.GetY()) return false;
	return true;
}
int main(int argc,char *argv[])
{
	if (argc!=2)
	{
		puts("usage: tanX server_ip");
		return -1;
	}
	puts("Connecting to server...");
	client=new Client(argv[1]);
	client->Connect(myid,num);
	puts("Server connected!");
	printf("myid: %d, num: %d", myid, num);
	if (!Init()) return -1;
	//Start drwing
	bool exit=false;
	SDL_Thread *ctrl_t=SDL_CreateThread(Ctrl,&exit);
	SDL_Thread *draw_t=SDL_CreateThread(Show,&exit);
	//Play the BGM
	if (!Mix_PlayingMusic()) if (Mix_PlayMusic(bgm,-1)==-1) return -1;

	for (int i=1;i<=num;++i)
		tanks.push_back(Tank(i,i-1,i*4,24));
	list<Tank>::iterator tank=tanks.begin();

	Timer timer;
	while(!exit)
	{
		timer.Start();
		while (client->Receive(id,cmd))
		{
			for (auto &t:tanks)
			{
				if (t.GetId()==id)
				{
					t.Execute(cmd);
					break;
				}
			}
		}
		for (auto i=tanks.begin(),j=tanks.begin();i!=tanks.end();i=j)
		{
			++j;
			if (i->Dead()) tanks.erase(i);
			i->Move(+1);
			if (terrain->Hit(*i))
			{
				i->Move(-1);
			}
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
			if (terrain->Hit(*i)) bullets.erase(i);
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
	Mix_HaltMusic();
	exit=true;
	SDL_WaitThread(ctrl_t,nullptr);
	SDL_WaitThread(draw_t,nullptr);
	CleanUp();
	return 0;
}
