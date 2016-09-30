#include <math.h>
#include "common.h"
#include "line.h"

extern void drawpixel(int i,int j, int color);

//DDA算法绘制直线
//(x0,y0),起点像素坐标
//(x1,y1),终点像素坐标
//setPixel,像素绘制函数（在main.cpp中定义）
void DDA(int x0,int y0,int x1,int y1,int color)
{
	//算法实现代码
	int x,temp;
	      float dx, dy, y, k;
	      dx=x1-x0;
          dy=y1-y0;
	      k=dy/dx; 
          y = y0;
	      for (x=x0; x<=x1; x++)
          {
            drawpixel(x, (int)(y+0.5),color);	
	        y=y+k;
          }
}

//Bresenham算法绘制直线
//参数同DDA
void Bresenham(int x0,int y0,int x1,int y1,int color)
{
	//算法实现代码
}

//中点线画法绘制直线
//参数同DDA
void MidPoint(int x0,int y0,int x1,int y1,int color)
{
	//算法实现代码

}