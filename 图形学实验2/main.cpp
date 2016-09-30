#include <GL/glut.h>	
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "common.h"
#include "line.h"
							
extern void DrawPolygon(int g_iCtrlPntNum, wcPt3D	g_pCtrlPoints[]);

static GLubyte g_iColorRed,g_iColorGreen,g_iColorBlue;
//屏幕像素数组
GLubyte g_abyScreenImage[defSCREEN_HEIGHT][defSCREEN_WIDTH][3];

int		g_iCtrlPntNum = 0;	//多边形顶点个数
wcPt3D	g_pCtrlPoints[50];	//多边形的顶点

bool g_bPointMoving;	//按下空格键选择一个顶点，该变量被置为true
bool g_bFinish;			//按下'm'键，结束顶点的选择，该变量被置为true

int iSrcX,iSrcY,iDestX,iDestY; //直线起点，终点像素坐标

unsigned short g_lineType;
static int tp;

//初始化
void MyInit(void)
{
	g_iCtrlPntNum=0;
	g_bFinish=false;
	g_bPointMoving=false;
	g_lineType=SOLID_LINE;
	tp=0;
}

//颜色
void setColour(int r,int g,int b)
{
	g_iColorRed=r;
	g_iColorGreen=g;
	g_iColorBlue=b;
}

//像素绘制
void drawpixel(int i,int j, int color)
{
	static unsigned short t=0x8000;
	static unsigned short t1=t;
	static int nb=8*sizeof(unsigned short);
	static int tx,ty;

	setColour(color>>24,color>>16,color>>8);

	t1=t>>tp;
	tp=(tp+1)%nb;
	if((g_lineType & t1)!=0)
	{
		tx=i;
		ty=j;

		if(0<=ty&&ty<defSCREEN_HEIGHT&&0<=tx&&tx<defSCREEN_WIDTH){
			g_abyScreenImage[ty][tx][0]=g_iColorRed;
			g_abyScreenImage[ty][tx][1]=g_iColorGreen;
			g_abyScreenImage[ty][tx][2]=g_iColorBlue;
		}
	}
}

//线条类型
void setLineType(unsigned short type)
{
	g_lineType=type;
	tp=0;
}

//初始化屏幕像素数组为全黑
void InitScreenImage()
{
	int iHeight,iWidth;
	for(iHeight=0;iHeight<defSCREEN_HEIGHT;iHeight++){
		for(iWidth=0;iWidth<defSCREEN_WIDTH;iWidth++){
			g_abyScreenImage[iHeight][iWidth][0]=255;
			g_abyScreenImage[iHeight][iWidth][1]=255;
			g_abyScreenImage[iHeight][iWidth][2]=255;
		}
	}
}


//修改图像
void ModifyScreenImage()
{
	static int i;
	static int dsx,dsy;

	//兰色实线
	setLineType(SOLID_LINE);

	//绘制控制图
	int line_count;
	if (g_bPointMoving)	//正在移动鼠标，需要实时画移动的点，线数=顶点数
		line_count = g_iCtrlPntNum;
	else				//否则，线数=顶点数-1
		line_count = g_iCtrlPntNum-1;

	for(i=0;i< line_count;i++){ 
		//这里为简单起见，三维空间坐标系中的点转换到平面坐标系的方法是：
		//忽略点的z坐标，并将x，y坐标转换为最接近它们的整数
		iSrcX=ROUND(g_pCtrlPoints[i].x);
		iSrcY=ROUND(g_pCtrlPoints[i].y);
		iDestX=ROUND(g_pCtrlPoints[i+1].x);
		iDestY=ROUND(g_pCtrlPoints[i+1].y);
		
		DDA(iSrcX,iSrcY,iDestX,iDestY,255<<8 /*兰色*/ );
	}

	if (g_bFinish)
	{
		//调用多边形扫描转换算法对选定的区域填充红色
		//请同学们实现 DrawPolygon函数
		DrawPolygon(g_iCtrlPntNum, g_pCtrlPoints);
	}
}

//响应键盘按键
void Keyboard(unsigned char uchKey, int iXPos, int iYPos)
{
	if(iXPos<0||iXPos>=defSCREEN_WIDTH||iYPos<0||iYPos>=defSCREEN_HEIGHT)
		return;

	if(uchKey == 27/*Esc*/) {
		exit(0);
	}
	else if(uchKey==' '){//空格键选择一个顶点

		if(g_bFinish){//当所有顶点都已选择完，按下空格键，重新选择顶点集
			g_iCtrlPntNum=0;
			g_bFinish=false;
		}

		if(g_iCtrlPntNum>=30)//过多的顶点，会导致计算值过大，甚至超出计算机所能表示的数的上限
			return;

		//设置新的顶点坐标
		g_pCtrlPoints[g_iCtrlPntNum].x=iXPos;
		g_pCtrlPoints[g_iCtrlPntNum].y=defSCREEN_HEIGHT-1-iYPos;
		g_pCtrlPoints[g_iCtrlPntNum].z=0;
		g_iCtrlPntNum++;//顶点数加1
		
		g_bPointMoving=false;

	}
	else if(uchKey=='m'||uchKey=='M'){//结束顶点的选择

		if(!g_bFinish){
			//顶点数不变，重新设置曲线相关属性值
			g_pCtrlPoints[g_iCtrlPntNum].x = g_pCtrlPoints[0].x;
			g_pCtrlPoints[g_iCtrlPntNum].y = g_pCtrlPoints[0].y;
			g_pCtrlPoints[g_iCtrlPntNum].z = 0;
			g_iCtrlPntNum++;//顶点数加1
			g_bFinish=true;
			g_bPointMoving = false;
		}

	}
	glutPostRedisplay();
}

//响应特殊按键
void Special(int iKey, int iXPos, int iYPos)
{

}

//响应鼠标按键
void Mouse(int iButton,int iState,int iXPos, int iYPos)
{

}

//响应按下一个鼠标按钮移动鼠标
void Motion(int iXPos, int iYPos)
{

}

//响应移动鼠标
void PassiveMotionFunc(int iXPos, int iYPos)
{
	if(!g_bFinish){//如果没有完成顶点的选择
		//实时保存光标位置
		g_pCtrlPoints[g_iCtrlPntNum].x=iXPos;
		g_pCtrlPoints[g_iCtrlPntNum].y=defSCREEN_HEIGHT-1-iYPos;
		g_pCtrlPoints[g_iCtrlPntNum].z=0;

		if(g_bPointMoving==false){//如果刚刚选择了一个顶点,当前的光标位置还不能成为新的顶点，但应该显示到屏幕上，以实现"拖动"的效果
			g_bPointMoving=true;
		}
	}
	glutPostRedisplay();

}

void Reshape(int iWidth, int iHeight)
{
	glutReshapeWindow(defSCREEN_WIDTH,defSCREEN_HEIGHT);

}

//初始化
void Init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_FLAT);
	InitScreenImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
}

//绘制回调函数
void Display() 
{	
	glClear(GL_COLOR_BUFFER_BIT);
	InitScreenImage();
	ModifyScreenImage();
	glDrawPixels(defSCREEN_WIDTH,defSCREEN_HEIGHT,GL_RGB,GL_UNSIGNED_BYTE,g_abyScreenImage);
	glutSwapBuffers();
}

int main(int argc,char** argv)
{
	MyInit();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(defSCREEN_WIDTH,defSCREEN_HEIGHT);
	glutCreateWindow("多边形扫描转换: 空格键选择多边形顶点,'m'结束顶点的选择(顶点不能超过30个)");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(PassiveMotionFunc);
	glutMainLoop();

	return 0;
}

