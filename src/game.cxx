#include <mutex>
#include <thread>

#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>

#include "bullet.hxx"
#include "client.hxx"
#include "config.hxx"
#include "display.hxx"
#include "tank.hxx"
#include "terrain.hxx"
#include "timer.hxx"

using std::list;
using std::mutex;

bool quit;

Mix_Music *bgm = nullptr;

mutex item_mutex;

list<Tank> tanks;
list<Bullet> bullets;
Terrain &terrain = Terrain::GetInstance();
Display &display = Display::GetInstance();
Client *client;

int myid, id, cmd, num;

bool Init() {
	// Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
	// Set the window caption
	SDL_WM_SetCaption("tanX", nullptr);
	// Set the window icon
	SDL_WM_SetIcon(SDL_LoadBMP("img/icon.bmp"), nullptr);
	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) return false;
	// Init the display
	display.Init();
	// Load the map
	terrain.LoadMap();
	// Load the background music
	bgm = Mix_LoadMUS("snd/tank_draft_mix.mp3");
	if (bgm == nullptr) return false;
	return true;
}
void CleanUp() {
	// Quit display
	display.Quit();
	// Free the music
	Mix_FreeMusic(bgm);
	// Quit SDL_mixer
	Mix_CloseAudio();
	// Quit SDL
	SDL_Quit();
}

void Ctrl(bool &quit) {
	Timer timer;
	SDL_Event event;
	while (!quit) {
		timer.Start();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
				return;
			}
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_UP: cmd = 1; break;
					case SDLK_DOWN: cmd = 2; break;
					case SDLK_LEFT: cmd = 3; break;
					case SDLK_RIGHT: cmd = 4; break;
					case SDLK_SPACE: cmd = 0; break;
					default: continue;
				}
				client->Send(myid, cmd);
			} else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
					case SDLK_UP: cmd = -1; break;
					case SDLK_DOWN: cmd = -2; break;
					case SDLK_LEFT: cmd = -3; break;
					case SDLK_RIGHT: cmd = -4; break;
					default: continue;
				}
				client->Send(myid, cmd);
			}
		}
		if (timer.GetTicks() < time_slot) SDL_Delay(time_slot - timer.GetTicks());
	}
}

void Show(const bool &quit) {
	using std::list;
	Timer timer;
	Timer fps;
	unsigned frame = 0;
	fps.Start();
	while (!quit) {
		timer.Start();
		display.Show(tanks, bullets, terrain, item_mutex);
		++frame;
		if (timer.GetTicks() * screen_fps < 1000)
			SDL_Delay(1000 / screen_fps - timer.GetTicks());
		if (fps.GetTicks() >= 1000) {
			printf("fps:%.3f\n", frame * 1000. / fps.GetTicks());
			frame = 0;
			fps.Start();
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		puts("usage: tanX server_ip");
		return -1;
	}
	
	puts("Connecting to server...");
	client = new Client(argv[1]);
	client->Connect(myid, num);
	puts("Server connected!");
	printf("myid: %d, num: %d", myid, num);
	
	if (!Init()) return -1;
	for (int i = 1; i <= num; ++i)
		tanks.push_back(Tank(i, i - 1, i * 4, 24));
	
	std::thread t_ctrl(Ctrl, std::ref(quit));
	std::thread t_show(Show, std::ref(quit));
	// Play BGM
	if (!Mix_PlayingMusic()) if (Mix_PlayMusic(bgm, -1) == -1) return -1;
	Timer timer;
	while (!quit) {
		timer.Start();
		item_mutex.lock();
		while (client->Receive(id, cmd)) {
			for (auto &t : tanks) {
				if (t.GetId() == id) {
					t.Execute(cmd);
					break;
				}
			}
		}
		for (auto i = tanks.begin(), j = i; i != tanks.end(); i = j) {
			++j;
			if (i->Dead()) tanks.erase(i);
			if (i->Reload()) bullets.push_back(i->Fire());
			i->Move(+1);
			if (terrain.Hit(*i)) {
				i->Move(-1);
				continue;
			}
			for (const auto &k : tanks)
				if (i->GetId() != k.GetId() && Check(*i, k)) {
					i->Move(-1);
					break;
				}
		}
		for (auto i = bullets.begin(), j = i; i != bullets.end(); i = j) {
			++j;
			i->Move(+1);
			if (terrain.Hit(*i)) {
				bullets.erase(i);
				continue;
			}
			for (auto &&k : tanks) {
				if (Check(*i, k)) {
					k.Damage(i->GetPow());
					bullets.erase(i);
					break;
				}
			}
		}
		item_mutex.unlock();
		if (timer.GetTicks() < time_slot)
			SDL_Delay(time_slot - timer.GetTicks());
	}
	Mix_HaltMusic();
	t_ctrl.join();
	t_show.join();
	CleanUp();
	delete client;
	return 0;
}
