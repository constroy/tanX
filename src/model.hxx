#ifndef _MODEL_HXX
#define _MODEL_HXX

#include <list>

#include "bullet.hxx"
#include "tank.hxx"
#include "terrain.hxx"

using std::list;

struct Model
{
	list<Tank> tanks;
	list<Bullet> bullets;
	Terrain *terrain;
};

#endif
