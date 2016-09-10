#ifndef _BULLET_HXX
#define _BULLET_HXX

#include "item.hxx"

class Bullet: public Item {
public:
	Bullet(int m, int x, int y, int d, int p):
		Item(m, x, y, 4, 4, 24, d, p, true, BULLET) {}
};

#endif
