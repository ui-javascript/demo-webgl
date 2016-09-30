#include <GL/glut.h>	
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "common.h"
#include "line.h"

void DrawBezier_By_de_Casteljau(int g_iCtrlPntNum, wcPt3D	g_pCtrlPoints[])
{
		/*ansX和ansY两个数组是分别用来存储g_pCtrlPoints数组中x坐标的值和y坐标的值
		并且ansX数组和ansY数组也需要用来存储递推过程中的值。*/
		double ansX[1000],ansY[1000];

		/*X数组和Y数组则是用来存储每一次操作完之后的值*/
		double X[1000],Y[1000];

		/*pitch代表分割完后每一份的长度*/
		double pitch = 1.0 / (g_iCtrlPntNum * 30);

		/*now代表当前用的长度*/
		double now = 0;

		/*ans是一个计数器，用来记录每一次操作完的值的下标，而rest则用来记录一次操作中还有多少个点剩余*/
		int ans = 0,rest = g_iCtrlPntNum;

		/*先把所有数据全部赋值进来*/
		for(int i = 0; i < g_iCtrlPntNum; ++i)
		{
			ansX[i] = g_pCtrlPoints[i].x;
			ansY[i] = g_pCtrlPoints[i].y;
		}

		/*因为DDA算法画线需要两个点，所以我令第一个点就是起始点，先存储进去*/
		X[ans] = ansX[0];
		Y[ans] = ansY[0];

		/*暴力遍历所有可能的now，每遍历一次，计数器++，now的值发生变化，并且重新将原g_pCtrlPoints
		数组中的坐标给赋值进来操作，然后rest都要重新置为g_iCtrlPntNum-1.
		然后就在rest！=1时候一直进行类似倒杨辉三角的运算，直至算出最终结果，然后将这个最终结果扔进X
		和Y数组中，用DDA算法将当前点和前一个点连接起来。*/
		while(now <= 1 - pitch)
		{
			ans ++;
			now += pitch;
			rest = g_iCtrlPntNum - 1;
		
			for(int i = 0; i < g_iCtrlPntNum; ++i)
			{
				ansX[i] = g_pCtrlPoints[i].x;
				ansY[i] = g_pCtrlPoints[i].y;
			}

			while(rest)
			{
				/*类似杨辉三角的算法，不断递推回去，而且和杨辉三角相似的是每递推一层，下一层的个数会
				减少1个。*/
				for(int i = 0; i < rest; ++i)
				{
					ansX[i] = (1 - now) * ansX[i] + now * ansX[i + 1];
					ansY[i] = (1 - now) * ansY[i] + now * ansY[i + 1];
				}
				rest --;
			}
			 /*将当前结果存储进去*/
			X[ans] = ansX[0];
			Y[ans] = ansY[0];
			DDA((int)X[ans - 1],(int)Y[ans - 1],(int)X[ans],(int)Y[ans],(255 << 24));
		}
}
   