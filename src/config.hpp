#ifndef _CONFIG_H
#define _CONFIG_H

#include <cstdio>

//Screen
extern const int screen_width=800;
extern const int screen_height=640;
extern const int screen_bpp=32;
extern const int screen_fps=40;

//Tank
extern const int reload_time=16;
extern const unsigned bar_color=65280u;

extern const int dx[]={0,0,-1,+1};
extern const int dy[]={-1,+1,0,0};

//Terrain
extern const int map_size=32;

#endif
