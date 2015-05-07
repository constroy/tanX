#include "display.hxx"

Display *Display::GetInstance()
{
	static Display instance;
	return &instance;
}
SDL_Surface *Display::LoadImage(const char filename[],bool trans)
{
	SDL_Surface *loadedImage=NULL;
	SDL_Surface *optimizedImage=NULL;
	loadedImage=SDL_LoadBMP(filename);
	if (loadedImage)
	{
		optimizedImage=SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
		if (trans)
		{
			Uint32 color_key=SDL_MapRGB(optimizedImage->format,0XFF,0XFF,0XFF);
			SDL_SetColorKey(optimizedImage,SDL_SRCCOLORKEY,color_key);
		}
	}
	return optimizedImage;
}
void Display::ApplySurface(SDL_Surface *src,SDL_Surface *dst,short x,short y)
{
	SDL_Rect offset={x,y};
	SDL_BlitSurface(src,NULL,dst,&offset);
}
void Display::ApplySurface(SDL_Surface *src,SDL_Surface *dst,SDL_Rect offset)
{
	SDL_BlitSurface(src,NULL,dst,&offset);
}
void Display::Init()
{
	//Initialize SDL_ttf
	//TTF_Init();
	//Open the font
	//font=TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf",24);
	
	screen=SDL_SetVideoMode(screen_width,screen_height,screen_bpp,
							SDL_HWSURFACE|SDL_ASYNCBLIT|SDL_DOUBLEBUF);
	char file_path[256];
	for (int i=0;i<1;++i)
	{
		sprintf(file_path,"../img/bullet/%d.bmp",i);
		bullet_clips[i]=LoadImage(file_path);
	}
	for (int i=0;i<5;++i) for (int j=0;j<5;++j)
	{
		sprintf(file_path,"../img/tank/%d-%d.bmp",i,j);
		tank_clips[i][j]=LoadImage(file_path,true);
	}
	for (int i=0;i<128;++i)
	{
		sprintf(file_path,"../img/terrain/%x.bmp",i);
		terrain_clips[i]=LoadImage(file_path,true);
	}
	for (int i=0;i<41;++i)
	{
		bar[i]=SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA,40,4,32,0,0,0,0);
		SDL_SetAlpha(bar[i],SDL_SRCALPHA|SDL_RLEACCEL,bar_alpha);
		SDL_Rect dst=bar[i]->clip_rect;
		dst.w=i;
		SDL_FillRect(bar[i],NULL,bar_back_color);
		SDL_FillRect(bar[i],&dst,bar_front_color);
	}
}
void Display::Quit()
{
	//Close the font that was used
	//TTF_CloseFont(font);
	//TTF_Quit();
	for (int i=0;i<1;++i) SDL_FreeSurface(bullet_clips[i]);
	for (int i=0;i<5;++i) for (int j=0;j<5;++j) SDL_FreeSurface(tank_clips[i][j]);
	for (int i=0;i<128;++i) SDL_FreeSurface(terrain_clips[i]);
	for (int i=0;i<41;++i) SDL_FreeSurface(bar[i]);
}
//opt 0:lower grid 1:upper grid
void Display::ShowTerrain(Terrain *terrain,bool opt)
{
	for (int i=0;i<map_size;++i) for (int j=0;j<map_size;++j)
	{
		char grid=terrain->GetGrid(i,j);
		if ((grid&1)==opt) ApplySurface(terrain_clips[(int)grid],screen,i*20,j*20);
	}
}
void Display::Show(const Model &model,const bool *exit)
{
	const list<Tank> &tanks=model.tanks;
	const list<Bullet> &bullets=model.bullets;
	Terrain *const &terrain=model.terrain;
	Timer timer;
	Timer fps;
	int frame=0;
	fps.Start();
	while (!*exit)
	{
		timer.Start();
		++frame;
		ShowTerrain(terrain,0);
		for (list<Bullet>::const_iterator i=bullets.begin();i!=bullets.end();++i)
		{
			ApplySurface(bullet_clips[i->GetModel()],screen,i->GetX(),i->GetY());
		}
		for (list<Tank>::const_iterator i=tanks.begin();i!=tanks.end();++i)
		{
			ApplySurface(tank_clips[i->GetModel()][i->GetDir()],screen,i->GetX(),i->GetY());
		}
		for (list<Tank>::const_iterator i=tanks.begin();i!=tanks.end();++i)
		{
			ApplySurface(bar[i->GetHp()],screen,i->GetX(),i->GetY()-8);
		}
		ShowTerrain(terrain,1);
		//Update Screen
		SDL_Flip(screen);
		
		if (timer.GetTicks()*screen_fps<1000)
		{
			SDL_Delay(1000/screen_fps-timer.GetTicks()+(frame&1));
		}
		if (fps.GetTicks()>=1000)
		{
			printf("fps:%.3f\n",frame*1000.0f/fps.GetTicks());
			frame=0;
			fps.Start();
		}	
	}
}
