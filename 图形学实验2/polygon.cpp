#include <GL/glut.h>	
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "common.h"
#include "line.h"

//实现DrawPolygon函数，完成多边形的扫描转换算法
//实现分类边表和活化边表的数据结构与相应算法
//顶点数存于g_iCtrlPntNum，顶点坐标值存于g_pCtrlPoints数组中，由于是二维点，可以忽略z坐标
//!!!注意!!!：按M键结束选择后，最后一个顶点 等于 第一个顶点，
//即g_pCtrlPoints[g_iCtrlPntNum-1] 与 g_pCtrlPoints[0]是相同的
//以四边形为例，g_iCtrlPntNum=5，起点g_pCtrlPoints[0]与终点g_pCtrlPoints[4]指同一个点

typedef struct edge 
{
	int    y;   //边的上端点的y坐标（y_max）
	double x;   //边与当前扫描线交点的x坐标
	double dx;  //x的增量
	struct edge * next;
} edge ;

//分类边表NET的初始化：
void init_edge_list (edge *edge_header,    //指向要创建的NET的头指针
	                 int g_iCtrlPntNum,     //多边形的顶点数
					 wcPt3D	g_pCtrlPoints[] //多边形的顶点坐标数组
                    )					
{
	int i;
	wcPt3D start_point, end_point;  //某边的起点和终点
	wcPt3D *up,*down;  //指向某边的上端点和下端点的指针
	edge *bak, *header ;
	
	int prev_trend,
		current_trend;	//如果边往上走，该值为1；边往下走，该值为-1；用于奇异点的处理

	if (g_iCtrlPntNum<3)	//顶点数太少，无法构成多边形
		return;

	//判定最后一条边（即第一条边的上一条边）的走势(因为多边形的边构成闭环)
	if (g_pCtrlPoints[g_iCtrlPntNum-1].y > g_pCtrlPoints[g_iCtrlPntNum-2].y )
		prev_trend = 1;   //上一条边往上走
	else if (g_pCtrlPoints[g_iCtrlPntNum-1].y < g_pCtrlPoints[g_iCtrlPntNum-2].y )
		prev_trend = -1;  //上一条边往下走
	else 
		prev_trend = 0;   //上一条是水平边
	
	for (i=0;i<g_iCtrlPntNum-1;i++)
	{
		start_point = g_pCtrlPoints[i];
		end_point   = g_pCtrlPoints[i+1];
	    //计算本条边的朝向current_trend
		if ( g_pCtrlPoints[i].y == g_pCtrlPoints[i+1].y )  
			continue;	//水平边，不处理，进入下一条边的处理
		else 
		if ( g_pCtrlPoints[i+1].y > g_pCtrlPoints[i].y ) { //向上边
			   up = &end_point;
			   down = &start_point;
			   current_trend = 1; 
		}
		else  {  //向下边
		   up = &start_point;
		   down = &end_point;
		   current_trend = -1;
		}
		//创建存放一条边数据的动态变量:
		edge * new_edge = (edge * )malloc(sizeof(edge));
		//并初始化:
		new_edge->y = up->y;   //y_max
		new_edge->x = down->x; //x_min
		new_edge->dx = double(up->x - down->x) / double(up->y - down->y); //斜率的倒数
		new_edge->next = NULL;
		//处理奇异点：
		if (prev_trend == current_trend ) //2线段连接处与扫描线的交点只算1次
		{
			if (current_trend == 1) //线段走向为往上
			{
				//线段下端点y提升一条扫描线,加入NET[y+1]类：
				new_edge->x = new_edge->x + new_edge->dx;
				header = &edge_header[(int)down->y+1];  
			}
			else if (current_trend == -1) //线段走向为往下
			{
				//线段下端点不变，上端点下降一条扫描线
				new_edge->y = new_edge->y-1;
				header= &edge_header[(int)down->y]; //加入NET[y]类
			}
		}
		else //极值点，2线段连接处与扫描线的交点只算2次
			header= &edge_header[(int)down->y];
		//若原先线段的y跨度只为1，处理奇异点后变为水平线:
		if ( abs(down->y - new_edge->y) <0.1 )	
		{
			free(new_edge);  
			continue;
		}

		prev_trend = current_trend; 
	    //按x的递增序，移动bak和header指针，使其依次指向正确插入new_edge的前/后一个位置
		while (1) {
			bak = header;
			header = header->next;
			if (header==NULL)
				break;
			if ( header->x > new_edge->x  ||
				 ( header->x == new_edge->x  &&	header->dx >= new_edge->dx) )
				break;
		}
		//将new_edge插入NET[y]类：
		bak->next = new_edge;
		new_edge->next = header;
	} //end of “for (i=0;i<g_iCtrlPntNum-1;i++)”，处理下一条边
}

//将NET[y]中的边，按x的递增序合并到AET中：
void merge_two_list( edge * cur,    //初值为AET的起始地址
	                 edge * first,  //初值为NET[y].next
					 edge * second  //初值为AET.next
				   )
{
	while (first!=NULL && second!=NULL)
	{
		if (first->x < second->x
			|| (first->x == second->x && first->dx < second->dx)
			)  //将first所指的边插入AET
		{
			cur->next = first;
			cur = first;
			first = first->next; //取NET[y]中的下一条边
		}
		else { //后移second及cur指针，直至满足“first->x < second->x”
			cur->next = second;
			cur = second;
			second = second->next;
		}
	}
	if (first!=NULL)
		cur->next = first;
	if (second!=NULL)
		cur->next = second;
}

//重排header所指的AET：
void Resort(edge *header)
{
	int i,len=0;
	edge *p,*selected,*bak_sel,*q, *bak_q;

	//获取表的长度
	for (p=header->next;p!=NULL;p=p->next)
		len++;
	
	p = header;
	
	//做len-1次排序
	for (i=0;i<len-1;i++)
	{
		bak_sel = p;
		selected =p->next;

		for (bak_q=selected,q=selected->next;
			 q!=NULL;
			 bak_q=q,q=q->next)
		{
			if (q->x < selected->x || (q->x == selected->x && q->dx < selected->dx) )
			{
				bak_sel = bak_q;
				selected = q;
			}
		}

		bak_sel ->next = selected->next;
		selected->next = p->next;
		p->next = selected;
		p = p->next;
	}
}

void DrawPolygon(int g_iCtrlPntNum, wcPt3D	g_pCtrlPoints[])
{
	int i,y;
	edge edge_header[defSCREEN_HEIGHT];  //NET数组
	edge active_edge_list;  //AET的头结点

	
	//初始化分类边表
	active_edge_list.next = NULL;
	for(y = 0; y < defSCREEN_HEIGHT; ++y)
		edge_header[y].next = NULL;
	init_edge_list(edge_header,g_iCtrlPntNum,g_pCtrlPoints);


	for (y=0;y<defSCREEN_HEIGHT;y++)
	{
		//若第y扫描线的分类边表非空，则取下并入活化边表中
		if(edge_header[y].next != NULL)
		{
			merge_two_list(&active_edge_list,edge_header[y].next,active_edge_list.next);
		}

		//重新对活化边表进行排序
		Resort(&active_edge_list);

		//逐段求扫描线与多边形的交点并填充
		edge *p = active_edge_list.next;

		p = active_edge_list.next;
		while( p != NULL && p->next != NULL )  
		{  
			for(float j = p->x;j <= p->next->x; j++)  
			{  
				//drawpixel(static_cast<int>(j),y,(0xff<<16));   //更改颜色
				drawpixel((int)j,y,(0xff<<16));
   
			}
			p = p->next->next;//考虑端点情况  
		}
		

		//在AET中删除ymax=当前扫描线y的边
		edge *q = &active_edge_list;
		p = q->next;
		while(p != NULL)
		{
			if(p->y == y)
			{
				q->next = p->next;
				delete p;
				p = q->next;
			}
			else
			{
				q = q->next;
				p = q->next;
			}
		}
		
		//修正AET中剩下边的x值（加斜率的倒数)
		p = active_edge_list.next;
		while( p != NULL )  
		{  
			p->x += p->dx;
			p = p->next;  
		}
	}
}
   

