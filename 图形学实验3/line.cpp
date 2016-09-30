
#include <math.h>
#include "common.h"

#include "line.h"

extern void drawpixel(int i,int j, int color);

bool re_arrange_xy(int &x0, int &y0, int &x1, int &y1, int &dx, int &dy)
{
	bool x_y_swap=false;

	dx = x1-x0;
	dy = y1-y0;

	if (fabs(float(dx))<fabs(float(dy)))
	{
		swap(x0,y0);
		swap(x1,y1);
		swap(dx,dy);
		x_y_swap = true;
	}

	if (x0>x1)
	{
		swap(x0,x1);
		swap(y0,y1);
		dx = -dx;
		dy = -dy;
	}
	return x_y_swap;
}

void DDA(int x0,int y0,int x1,int y1,int color)
{
	//请实现本算法
	int x;
	int dx, dy;
	float y, k;
	bool x_y_swap;

	x_y_swap = re_arrange_xy(x0,y0,x1,y1,dx,dy);

	if (fabs(float(dx))<=0.0001)	//dy is zero
		return ;

	k = (float)dy/dx;
	y=(float)y0;
	for (x=x0;x<=x1;x++)
	{
		if (!x_y_swap) drawpixel(x,int(y+0.5),color);
		else drawpixel(int(y+0.5),x,color);
		y+=k;
	}
}

//Bresenham算法绘制直线
//参数同DDA
void Bresenham(int x0,int y0,int x1,int y1,int color)
{
	//请实现本算法
	
}

//中点线画法绘制直线
//参数同DDA
void MidPoint(int x0,int y0,int x1,int y1,int color)
{
	//请实现本算法
	
}