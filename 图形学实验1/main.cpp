#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "line.h"

#define defSCREEN_WIDTH 800								
#define defSCREEN_HEIGHT 600

int g_lineNum;
bool g_startSelect,g_endSelect,g_finish;
wcPt2D *g_lines;


static GLubyte g_iColorRed,g_iColorGreen,g_iColorBlue;
//屏幕像素数组
GLubyte g_abyScreenImage[defSCREEN_HEIGHT][defSCREEN_WIDTH][3];


unsigned short g_lineType;
static int tp;
//本程序特定的初始化代码放在此函数中：
void MyInit(void)
{
	g_lineNum = 0;
	g_startSelect = g_endSelect = g_finish = false;
	//动态申请存放直线端点的内存空间
	g_lines=(wcPt2D*)malloc(100*sizeof(wcPt2D));
	g_lineType=SOLID_LINE;
	tp=0;
}

//颜色设置方法
void setColour(int r,int g,int b)
{
	g_iColorRed = r;
	g_iColorGreen = g;
	g_iColorBlue = b;
}

//像素绘制
void drawpixel(int i,int j, int color)
{
	static unsigned short t=0x8000; //等价的二进制表示：1000 0000 0000 0000
	static unsigned short t1=t;
	static int nb = 8*sizeof(unsigned short); //t的bit数
	static int tx,ty;

    //注意:在内存中RGB32的各分量的排列顺序为：BGRA(最后8bit是Alpha通道)
	setColour(color>>8,color>>16,color>>24);

	t1 = t>>tp; //右移tp位
	tp=(tp+1) % nb;
	if((g_lineType & t1) != 0)  //线型控制
	{
		tx=i;
		ty=j;
		if( 0<=ty && ty<defSCREEN_HEIGHT && 0<=tx && tx<defSCREEN_WIDTH){
			g_abyScreenImage[ty][tx][0]=g_iColorRed;
			g_abyScreenImage[ty][tx][1]=g_iColorGreen;
			g_abyScreenImage[ty][tx][2]=g_iColorBlue;
		}
	}
}

//设置线条类型
void setLineType(unsigned short type)
{
	g_lineType = type;
	tp=0;
}

//初始化屏幕像素数组为全黑
void InitScreenImage()
{
	int iHeight,iWidth;
	for(iHeight=0;iHeight<defSCREEN_HEIGHT;iHeight++){
		for(iWidth=0;iWidth<defSCREEN_WIDTH;iWidth++){
			g_abyScreenImage[iHeight][iWidth][0]=0;
			g_abyScreenImage[iHeight][iWidth][1]=0;
			g_abyScreenImage[iHeight][iWidth][2]=0;
		}
	}
}

//修改图像
void ModifyScreenImage()
{
	static int i;
	int color;
	setColour(255,255,0);   //白色
	setLineType(SOLID_LINE);  //实线
	color = (g_iColorRed<<8)+(g_iColorGreen<<16)+(g_iColorBlue<<24);
	for(i=0;i<g_lineNum;i++){
		//调用相应的画线算法
		DDA(ROUND(g_lines[i*2].x),
			ROUND(g_lines[i*2].y),
			ROUND(g_lines[i*2+1].x),
			ROUND(g_lines[i*2+1].y),
			color);
	}
}

//响应键盘按键的回调函数
void Keyboard(unsigned char uchKey, int iXPos, int iYPos)
{
	if(iXPos<0 || iXPos>=defSCREEN_WIDTH || iYPos<0 || iYPos>=defSCREEN_HEIGHT)
		return;

	if(uchKey == 27/*Esc*/) {
		exit(0);
	}
	else 
	if(uchKey==' ')/*交替选定直线段的两个端点*/{
		if(!g_startSelect/*直线段起始端点尚未选定*/){

		    if(g_lineNum>=40) //直线段数目超过40
			{
				g_finish=true;
				return;
			}
			//将当前位置作为第g_lineNum条直线段的起点坐标：
			g_lines[g_lineNum*2].x = iXPos;
			g_lines[g_lineNum*2].y = defSCREEN_HEIGHT-iYPos;
			g_lineNum++; //直线段数量加 1
			g_startSelect=true; 
		}
		else{ //g_startSelect == true，
			//将当前位置作为第g_lineNum条直线段的终点坐标：
			g_lines[g_lineNum*2-1].x = iXPos;
			g_lines[g_lineNum*2-1].y = defSCREEN_HEIGHT-iYPos;
			//g_lineNum++; //直线段数量加 1
			g_startSelect = false;
			g_endSelect = true;
			glutPostRedisplay(); //标记当前窗口在glutMainLoop下一次循环时需要重新绘制。
		}
	}
	else if(uchKey=='c'|| uchKey=='C'){//清屏
		g_lineNum=0;
		g_startSelect = g_endSelect = g_finish = false;
		glutPostRedisplay();
	}
}

//响应特殊按键的回调函数
void Special(int iKey, int iXPos, int iYPos)
{

}

//响应鼠标按键的回调函数
void Mouse(int iButton,int iState,int iXPos, int iYPos)
{

}

//响应按下一个鼠标按钮移动鼠标的回调函数
void Motion(int iXPos, int iYPos)
{

}

//响应移动鼠标的回调函数
void PassiveMotionFunc(int iXPos, int iYPos)
{
	if(!g_finish){//如果还没有完成控制点的选择
		if(g_startSelect) //直线段的起点已经选定
		{   //将鼠标的当前位置作为直线段的临时终点：
			g_lines[g_lineNum*2-1].x = iXPos;
			g_lines[g_lineNum*2-1].y = defSCREEN_HEIGHT-iYPos;
			//绘制鼠标移动时的即刻直线段（称为“橡皮筋技术”）
			glutPostRedisplay(); //标记当前窗口在glutMainLoop下一次循环时需要重新绘制。
		}
	}
}

//改变当前窗口的大小时执行：
void Reshape(int iWidth, int iHeight)
{
	glutReshapeWindow(defSCREEN_WIDTH,defSCREEN_HEIGHT);  //保持不变
	//glutReshapeWindow(iWidth,iHeight);  
}

//只需要程序开始时执行1次的初始化代码都应该放在此方法中：
//如设置背景色、坐标系统等
void Init()  
{
	glClearColor(0.0,0.0,0.0,0.0); //清除RGBA模式下的颜色缓冲区
	glShadeModel(GL_FLAT);  //设置着色模式
	InitScreenImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT,1); //设置像素的存储模式（不压缩、对齐）
}

//需要随着程序的运行（重新）渲染的操作应该放在此回调函数中：
void Display() 
{	
	glClear(GL_COLOR_BUFFER_BIT); //清除指定的GL_COLOR_BUFFER_BIT缓冲区
	InitScreenImage();
	ModifyScreenImage();
	glDrawPixels(defSCREEN_WIDTH,
		         defSCREEN_HEIGHT,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 g_abyScreenImage);
	glutSwapBuffers(); //交换双缓冲的两个缓冲区指针
}

//程序的主函数
int main(int argc,char** argv)
{
	printf("%s","实验1：直线的绘制Demo使用说明：\n");
	printf("%s","1.空格键：选定直线段的端点\n");
	printf("%s","2.鼠标拖动：在一个端点已经确定时，动态第以鼠标的当前位置为另一个端点画直线\n");
	printf("%s","3.C键：清屏\n");
	printf("%s","4.Esc键：退出系统\n");
	MyInit(); //本程序特定的初始化
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //初始化为双缓冲、RGBA色彩模式
	glutInitWindowSize(defSCREEN_WIDTH,defSCREEN_HEIGHT);
	glutCreateWindow("实验一：直线段扫描转换算法的实现"); //创建绘图窗口
	Init();  //程序开始时的一次性初始化
	//注册回调函数：
	glutDisplayFunc(Display); //窗口重显时调用的回调函数
	glutReshapeFunc(Reshape); //窗口调整大小时调用的回调函数
	glutKeyboardFunc(Keyboard); //键盘按下时调用的回调函数
	glutSpecialFunc(Special); //特殊按键的回调函数
	glutMouseFunc(Mouse);   //在鼠标按钮按下时调用的回调函数
	glutMotionFunc(Motion); //在鼠标移动时调用的回调函数
	glutPassiveMotionFunc(PassiveMotionFunc);  //在鼠标按下按钮并拖动时调用的回调函数
	//注册完毕，启动程序（主循环）
	glutMainLoop();  
	return 0;
}
