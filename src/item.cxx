#include "item.hxx"

Item::Item(int m,int x,int y,int w,int h,int v,int d,int p,bool run,ItemMask mask):
		model(m),x(x),y(y),w(w),h(h),vel(v),dir(d),pow(p),run(run),mask(mask) {}

void Item::Move(int opt)
{
	if (run)
	{
		x+=opt*dx[dir-1]*vel;
		y+=opt*dy[dir-1]*vel;
	}
}
