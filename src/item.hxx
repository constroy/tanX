#ifndef _ITEM_HXX
#define _ITEM_HXX

#include "config.hxx"

class Item {
public:
	Item(int m, int x, int y, int w, int h, int v, int d, int p, bool run,
		 ItemMask mask):
		model(m), x(x), y(y), w(w), h(h), vel(v), dir(d), pow(p), run(run),
		mask(mask) {}
	void Move(int opt) {
		if (run) {
			x += opt * dx[dir - 1] * vel;
			y += opt * dy[dir - 1] * vel;
		}
	}
	int GetModel() const {
		return model;
	}
	int GetX() const {
		return x;
	}
	int GetY() const {
		return y;
	}
	int GetW() const {
		return w;
	}
	int GetH() const {
		return h;
	}
	int GetDir() const {
		return dir;
	}
	int GetPow() const {
		return pow;
	}
	ItemMask GetMask() const {
		return mask;
	}
protected:
	int model;
	int x, y, w, h;
	int vel, dir;
	int pow;
	bool run;
	ItemMask mask;
};

#endif
