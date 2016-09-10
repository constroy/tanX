#ifndef _TANK_HXX
#define _TANK_HXX

#include "item.hxx"

class Tank: public Item {
public:
	Tank(int id, int img, int x, int y);
	void Damage(int damage);
	bool Dead() {
		return die && --die == 0;
	}
	void Execute(int cmd);
	int GetHp() const {
		return hp;
	}
	int GetId() const {
		return id;
	}
	bool Reload() {
		if (!die && reload) return reload-- == reload_time;
		else return false;
	}
private:
	int id;
	int hp;
	int reload;
	int die;
};

#endif
