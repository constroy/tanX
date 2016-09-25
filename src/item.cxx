#include "item.hxx"

bool Check(const Item &a, const Item &b) {
	if (a.GetX() >= b.GetX() + b.GetW()) return false;
	if (a.GetX() + a.GetW() <= b.GetX()) return false;
	if (a.GetY() >= b.GetY() + b.GetH()) return false;
	if (a.GetY() + a.GetH() <= b.GetY()) return false;
	return true;
}
