#include "display.hxx"

#include <cstdio>

#include "config.hxx"

using std::list;

inline void ApplySurface(SDL_Surface *src, SDL_Surface *dst, short x, short y) {
	SDL_Rect offset = {x, y};
	SDL_BlitSurface(src, nullptr, dst, &offset);
}
SDL_Surface *Display::LoadImage(const char filename[], bool trans) {
	SDL_Surface *loadedImage = nullptr;
	SDL_Surface *optimizedImage = nullptr;
	loadedImage = SDL_LoadBMP(filename);
	if (loadedImage) {
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
		if (trans) {
			Uint32 color_key = SDL_MapRGB(optimizedImage->format, 0XFF, 0XFF, 0XFF);
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, color_key);
		}
	}
	return optimizedImage;
}
void Display::Init() {
	// Initialize SDL_ttf
	// TTF_Init();
	// Open the font
	// font=TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf",24);

	screen = SDL_SetVideoMode(screen_width, screen_height, screen_bpp,
							  SDL_HWSURFACE | SDL_ASYNCBLIT | SDL_DOUBLEBUF);
	char file_path[256];
	for (int i = 0; i < 1; ++i) {
		sprintf(file_path, "img/bullet/%d.bmp", i);
		bullet_clips[i] = LoadImage(file_path);
	}
	for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j) {
			sprintf(file_path, "img/tank/%d-%d.bmp", i, j);
			tank_clips[i][j] = LoadImage(file_path, true);
		}
	for (int i = 0; i < 128; ++i) {
		sprintf(file_path, "img/terrain/%x.bmp", i);
		terrain_clips[i] = LoadImage(file_path, true);
	}
	for (int i = 0; i < 9; ++i) {
		bar[i] = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, 40, 4, 32, 0, 0, 0,
									  0);
		SDL_SetAlpha(bar[i], SDL_SRCALPHA | SDL_RLEACCEL, bar_alpha);
		SDL_Rect dst = bar[i]->clip_rect;
		dst.w = i * 5;
		SDL_FillRect(bar[i], nullptr, bar_back_color);
		SDL_FillRect(bar[i], &dst, bar_front_color);
	}
}
void Display::Quit() {
	// Close the font that was used
	// TTF_CloseFont(font);
	// TTF_Quit();
	for (int i = 0; i < 1; ++i) SDL_FreeSurface(bullet_clips[i]);
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			SDL_FreeSurface(tank_clips[i][j]);
	for (int i = 0; i < 128; ++i) SDL_FreeSurface(terrain_clips[i]);
	for (int i = 0; i < 9; ++i) SDL_FreeSurface(bar[i]);
}
// opt false: lower grid; true: upper grid
void Display::ShowTerrain(const Terrain &terrain, bool opt) {
	for (int i = 0; i < map_size; ++i)
		for (int j = 0; j < map_size; ++j) {
			int grid = terrain.GetGrid(i, j);
			if ((grid & 1) == opt) ApplySurface(terrain_clips[grid], screen,
												i * 20, j * 20);
		}
}
void Display::Show(const list<Tank> &tanks, const list<Bullet> &bullets,
				   const Terrain &terrain, std::mutex &item_mutex) {
	SDL_FillRect(screen, 0, 0U);
	ShowTerrain(terrain, false);
	item_mutex.lock();
	for (auto &b : bullets)
		ApplySurface(bullet_clips[b.GetModel()], screen, b.GetX(), b.GetY());
	for (auto &t : tanks)
		ApplySurface(tank_clips[t.GetModel()][t.GetDir()], screen, t.GetX(), t.GetY());
	for (auto &t : tanks)
		ApplySurface(bar[t.GetHp()], screen, t.GetX(), t.GetY() - 8);
	item_mutex.unlock();
	ShowTerrain(terrain, true);
	// Update Screen
	SDL_Flip(screen);
}
