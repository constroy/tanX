#include "tank.hxx"

Tank::Tank(int id, int m, int x, int y):
	Item(m, 20 * x, 20 * y, 40, 40, 4, 1, 2, false, TANK), id(id), hp(8), reload(0),
	die(0) {}

void Tank::Damage(int damage) {
	if (die) return;
	if ((hp -= damage) <= 0) {
		hp = 0;
		dir = 0;
		run = false;
		die = die_time;
	}
}
void Tank::Execute(int cmd) {
	if (die) return;
	if (cmd > 0) {
		run = true;
		dir = cmd;
	} else if (cmd < 0) {
		if (cmd == -dir) run = false;
	} else {
		if (!reload) reload = reload_time;
	}
}
