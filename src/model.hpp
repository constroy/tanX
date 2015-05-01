#ifndef _MODEL_HPP
#define _MODEL_HPP

#include <list>
#include "bullet.hpp"
#include "tank.hpp"
#include "terrain.hpp"

using std::list;

struct Model
{
	list<Tank> tanks;
	list<Bullet> bullets;
	Terrain *terrain;
};

#endif
