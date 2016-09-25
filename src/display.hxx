#ifndef _DISPLAY_HXX
#define _DISPLAY_HXX

#include <list>
#include <mutex>

#include <SDL/SDL.h>

#include "bullet.hxx"
#include "tank.hxx"
#include "terrain.hxx"

class Display {
public:
	Display(Display &) = delete;
	Display(Display &&) = delete;
	static Display &GetInstance() {
		static Display instance;
		return instance;
	}
	void Init();
	void Quit();
	void Show(const std::list<Tank> &tanks, const std::list<Bullet> &bullets,
			  const Terrain &terrain, std::mutex &item_mutex);
private:
	Display() = default;
	~Display() = default;
	SDL_Surface *LoadImage(const char filename[], bool trans = false);
	void ShowTerrain(const Terrain &terrain, bool opt);
	SDL_Surface *screen;
	SDL_Surface *background;
	SDL_Surface *bar[9];
	SDL_Surface *bullet_clips[5];
	SDL_Surface *tank_clips[5][5];
	SDL_Surface *terrain_clips[128];
};

#endif
