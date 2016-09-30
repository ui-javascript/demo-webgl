
#ifndef LINE_H
#define LINE_H


//DDA算法绘制直线
//(x0,y0),起点像素坐标
//(x1,y1),终点像素坐标
//setPixel,像素处理函数
void DDA(int x0,int y0,int x1,int y1,int color);

//Bresenham算法绘制直线
//参数同DDA
void Bresenham(int x0,int y0,int x1,int y1,int color);

//中点线画法绘制直线
//参数同DDA
void MidPoint(int x0,int y0,int x1,int y1,int color);

//颜色的值：假如红、绿、蓝3个分量为别为R、G、B，那么，color=(R<<24+G<<16+B<<8)

void drawpixel(int i,int j, int color);

#endif