#include <math.h>
#include "common.h"
#include "line.h"

extern void drawpixel(int i,int j, int color);

bool re_arrange_xy(int &x0, int &y0, int &x1, int &y1, float &dx, float &dy) {
	dx = x1-x0;
	dy = y1-y0;
	bool x_y_swap = false;
	if(fabs(dx) < fabs(dy)){  //包括k不存在的情况
		swap(x0,y0);
		swap(x1,y1);
		swap(dx,dy);
		x_y_swap = true;  //true表示坐标系变换过了
	}
	if(x0>x1){
		swap(x0,x1);
		swap(y0,y1); //端点次序问题对调即可
		dx = -dx;
		dy = -dy;    //dx保证为正数，但k不能改变
	}

	return x_y_swap;
}

//DDA算法绘制直线
//(x0,y0),起点像素坐标
//(x1,y1),终点像素坐标
//setPixel,像素绘制函数（在main.cpp中定义）
void DDA(int x0,int y0,int x1,int y1,int color)
{
	//算法实现代码
	int x;
	float dx, dy, y, k; //y要进行四舍五入
	bool x_y_swap = re_arrange_xy(x0, y0, x1, y1, dx, dy);
	k = dy/dx;
	for(x = x0,y=y0; x<=x1; x++)
    {
        if(!x_y_swap)   drawpixel(x,(int)(y+0.5),color);
		else            drawpixel((int)(y+0.5),x,color); 
		            //让y-x坐标系来画，k不存在的问题也解决了
		y = y+k;   //k已经讨论过了
    }
}

//Bresenham算法绘制直线
//参数同DDA
void Bresenham(int x0,int y0,int x1,int y1,int color) 
{
	int x, y, dx, dy, i,e;
	int flag1=1,flag2=1; //没有用到float
	bool changeFlag = false;
	dx=abs(x0-x1); //取绝对值，后面有定义的i
	dy=abs(y0-y1);
	if(x0>x1) {
		flag1 = -1;
	}
	if(y0>y1) {
		flag2 = -1;
	}
	if(dx<dy) { // |k|>1包括k无穷大的情况，dx可以等于0
		swap(dx,dy);
		changeFlag = true;
	}
	x=x0; y=y0; //指定画线的起点
	e = -dx;
	for(i=0; i<=dx; i++) {
		drawpixel(x,y,color);
		if(!changeFlag) x += flag1; //端点问题导致的反个方向
		else            y += flag2; //k值问题换个坐标系 
		e = e+2*dy;
		if(e>=0) { //e=0是约定 
		    if(!changeFlag) y += flag2;
		    else            x += flag1; 
			e = e-2*dx;
		}
	}
} 

/*
void Bresenham(int x0,int y0,int x1,int y1,int color)
{
    //算法实现代码
	int x,y;  //这里的y不用四舍五入
	float dx,dy,e;  
	bool x_y_swap = re_arrange_xy(x0, y0, x1, y1, dx, dy);
	e = -dx;
	int sign = 1;   //还是另外使用了一个标记
	if(dy<0) sign=-1;  //k<0的情况
	for(x=x0, y=y0; x<=x1; x++) {
		if(x_y_swap)  drawpixel(y, x, color);
		else          drawpixel(x, y, color);
		e = e+2*sign*dy; //k<0时
		if(e>=0) {
			y += sign;  //y坐标的变化
			e = e-2*dx;
		}
	}
}
*/


//中点线画法绘制直线
//参数同DDA
void MidPoint(int x0,int y0,int x1,int y1,int color)
{
    //算法实现代码
    int a, b, d1, d2, d, x, y;
    a=y0-y1; b=x1-x0; 
    x=x0; y=y0; 
	int flag1=(b >= 0 ? 1 : (b = -b, -1)); //x-y坐标系下与y坐标有关 
    int flag2=(a <= 0 ? 1 : (a = -a, -1)); //x-y坐标系下与x坐标有关
	                       //使a非正，b非负，则k为正
	d2=2* (a+b);  //对称性，所以是确定的
    drawpixel(x, y, color); //画起始点
	if(-a <= b) {
        d=2*a+b;
        d1=2*a; 
        while (x!=x1)
        {
            if (d<0) { 
				y += flag2; 
				d+=d2; 
			}
            else { 
				d+=d1;
			}
			x += flag1;
            drawpixel (x, y, color);
        } 
	}

	else { //讨论|k|>1包括k无穷大
		d=2*b+a;
        d1=2*b;  //反转过来
        while (y!=y1)
        {
            if (d<0) { 
				d+=d1; 
			}
            else { 
				x += flag1; 
				d+=d2;
			}
			y += flag2; //flag2是跟y的
            drawpixel (x, y, color);
        }
	}
}

