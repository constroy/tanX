#ifndef _CONFIG_H
#define _CONFIG_H

//Screen
const int screen_width=800;
const int screen_height=640;
const int screen_bpp=32;
const int screen_fps=40;

//Item
enum ItemMask{BULLET=2,TANK=4,SHIP=8};
const int dx[]={0,0,-1,+1};
const int dy[]={-1,+1,0,0};

//Tank
const int reload_time=16;
const unsigned bar_back_color=0;
const unsigned bar_front_color=0XFF00;
const unsigned char bar_alpha=0X7F;
//Terrain
const int map_size=32;

#endif
