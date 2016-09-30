#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <math.h>
#include <windows.h>

void setLightPos(int i)   //设定光源的位置
{
  GLfloat lightPos[5][4]={ {  0.0,  0.0, 10.0, 1.0},     //正前方
                           {  0.0,  10.0, 0.0, 1.0},     //正上方
				           {  0.0, -10.0, 0.0, 1.0},     //正下方
                           {-10.0,  10.0, 0.0, 1.0},     //左上方
                           { 10.0, -10.0, 0.0, 1.0}      //右下方
                         };
   glLoadIdentity();
   //指定光源GL_LIGHT0的位置为lightPos[i]：
   glLightfv(GL_LIGHT0,GL_POSITION,lightPos[i]);
}

void setLight(int lightNo)
{
  //定义一种适中的白色光源：
  GLfloat ambientLight[]   =  {0.3,0.3,0.3,1.0};     //环境光亮度
  GLfloat diffuseLight[]      =  {0.5,0.5,0.5,1.0};  //漫射光亮度
  GLfloat specularLight[]   =  {0.5,0.5,0.5,1.0};    //镜面反射光
  
  glEnable(GL_LIGHTING);  //启用光照模型
  setLightPos(lightNo);   //根据lightNo设置光源位置
  //建立和启用光源LIGHT0：
  glEnable(GL_LIGHT0);  //启用GL_LIGHT0
  glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);   //设置环境光
  glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);       //设置漫射光
  glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight); //设置镜面反射光
  
  glMaterialf(GL_FRONT, GL_SHININESS, 5.0);          //材料的镜面反射光泽度

  glEnable(GL_COLOR_MATERIAL);   //设置颜色跟踪法来实现质材属性
  //设置多边形正面的环境光和漫射光属性
  glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
  
  //设置材质的属性,参见p.190表5.4和p.193表5.5：
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight);   //材质属性的环境光 （p.193)
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseLight);       //材质属性的漫反射光
  glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight); //材质属性的镜面反射光
}


//装入纹理-------------------------
/* 函数LoadGLTextures  
 * 读取一个由BMPImageFileName指定的BMP文件作为纹理
 * 特别提醒：
 * （1）该文件的长和宽必须是2的乘幂
 * （2）该文件的图像存储格式必须是24bit的BMP文件
 * 如果失败，返回0，如果成功，返回纹理编号  
 */   

GLuint LoadGLTextures(char* BMPImageFileName)   
{
    GLuint  texture_ID=0;                                  // 纹理ID
    AUX_RGBImageRec *TextureImage[1];     // 创建纹理的存储空间（必须以数组的形式）
    memset(TextureImage,0,sizeof(void *)*1);   // 将指针设为 NULL
    // 载入纹理位图
    if (TextureImage[0]=auxDIBImageLoadA(BMPImageFileName))
    {
       glGenTextures(1,                      //  1.创建1个纹理标识符
		                         &texture_ID    //  存储在texture_ID中
			                    ); 
       //2.将纹理ID与纹理对象类型GL_TEXTURE_2D绑定： 
       glBindTexture(GL_TEXTURE_2D, texture_ID);
       //3.用来自位图的数据来生成纹理
       glTexImage2D(
		       GL_TEXTURE_2D, 
	           0, //指定mipmap的等级，0：硬件自动生成 
			   3, //图像内部格式，1：灰度图像, 3：RGB, 4：RGBA
			   TextureImage[0]->sizeX, //图像宽度（2的乘幂）
			   TextureImage[0]->sizeY, //图像高度（2的乘幂）
			   0,       //纹理边框宽度
			   GL_RGB,  //数据源格式
			   GL_UNSIGNED_BYTE,      //数据源类型
			   TextureImage[0]->data  //原始图像数据
			   );
	   //4.设置纹理对象状态：
       glTexParameteri(
		               GL_TEXTURE_2D,
		               GL_TEXTURE_MIN_FILTER, //纹理缩小时的滤波方法
					   GL_LINEAR); // 线性滤波
       glTexParameteri(
		               GL_TEXTURE_2D,
		               GL_TEXTURE_MAG_FILTER, //纹理放大时的滤波方法
					   GL_LINEAR); // 线性滤波
    }
    else
	  printf("纹理图像文件读入失败，检查路径和格式（24bit的bmp）\n");
    //----------------------------------------------------------------------------
	// 清理装入纹理时使用的临时工作数据垃圾
    if (TextureImage[0])        // 纹理是否存在
    {
       if (TextureImage[0]->data)      // 纹理图像是否存在
        {
           free(TextureImage[0]->data);    // 释放纹理图像占用的内存
        }
       free(TextureImage[0]);       // 释放图像结构
    }
	//----------------------------------------------------------------------------
    return texture_ID;    //返回所创建的纹理ID
}

//定义2个纹理ID：
GLuint groundTexture,  fenceTexture;

void init(void)
{ 
	glEnable(GL_DEPTH_TEST);   
	setLight(0);  //光源位置默认为0号（正前方）

	//创建地面纹理groundTexture：
    groundTexture = LoadGLTextures("鹅卵石.bmp");
	//groundTexture = LoadGLTextures("地板.bmp");
	groundTexture = LoadGLTextures("草地.bmp");
	//创建栅栏纹理FenceTexture：
	fenceTexture = LoadGLTextures("砖墙2.bmp");
	//fenceTexture = LoadGLTextures("围栏.bmp");

	//创建一个地面(Ground)的显示列表1,参见p.194上的5.6节
	glNewList(1,GL_COMPILE);
	  //glColor3f(0.0,1.0,0.0);
	  glBegin(GL_QUADS); 
	    //纹理映射：建立纹理空间（纹理坐标）与对象空间（顶点坐标）的对应关系：
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -8.0f, 0.0f);   
        glTexCoord2f(0.0f, 4.0f); glVertex3f(-8.0f, 8.0f, 0.0f);   
        glTexCoord2f(4.0f, 4.0f); glVertex3f(8.0f, 8.0f, 0.0f);   
        glTexCoord2f(4.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f); 
      glEnd();
	glEndList();
	
	//创建一个画栅栏（Fence）的显示列表2
	glNewList(2,GL_COMPILE);
	  //glColor3f(1.0,1.0,1.0);
	  glBegin(GL_QUADS);   
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -8.0f, 0.0f);   
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-8.0f, -8.0f, 1.5f);   
        glTexCoord2f(8.0f, 1.0f); glVertex3f(8.0f, -8.0f, 1.5f);   
        glTexCoord2f(8.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f);   
      glEnd();
	glEndList();
}

void drawTeapot()
{	glColor3f(0.5,0.3,0.3);      //设定茶壶色彩
	glRotatef(90,1.0,0.0,0.0);   //绕x轴旋转90°
	glTranslatef(1.0,0.75,-2.0);  //平移  

	glutSolidTeapot(1.0);      //绘制茶壶
	
	glTranslatef(-1.0,-0.75,2.0); //平移复原
	glRotatef(-90,1.0,0.0,0.0);  //旋转复原，即绕x轴旋转-90°(以便不影响后继的绘制)
    glColor3f(1.0,1.0,1.0);      //恢复白色
}

GLdouble  eyex=2,eyey=5,eyez=2;  //视点的初始位置坐标(1,5,5)

void display(void)
{
	  // 清除屏幕   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
   
    // 设置视角   
    glMatrixMode(GL_PROJECTION);   // 选择投影模视矩阵
    glLoadIdentity();   
	//定义透视投影：
    gluPerspective(75, //75°视野角度
		                       1, //纵横比（1：1）
					         0.1, //深度裁剪面到相机的近距离
					      1000  //深度裁剪面到相机的远距离
				             );   
    glMatrixMode(GL_MODELVIEW);   
    glLoadIdentity(); 
	//设定相机（视点）的位置：
    gluLookAt(eyex,eyey,eyez,  //视点E(eyex,eyey,eyez) 
			          0,0,0,  //参考点C(centerx,centery,centerz)
			          0,0,1   //相机视线向上方向U(upx,upy,upz)
			          );   
    drawTeapot();  //画茶壶

	glEnable(GL_TEXTURE_2D);  //启用GL_TEXTURE_2D纹理
	
	//5.绑定“groundTexture”纹理用于绘制地面   
    glBindTexture(GL_TEXTURE_2D, groundTexture); 
	glCallList(1); 	    
	//5.绑定“fenceTexture”纹理用于绘制栅栏   
    glBindTexture(GL_TEXTURE_2D, fenceTexture); 
    glCallList(2);  

    // 绕 z 轴旋转-90°、-180°、-270°后再绘制3个栅栏：
    glRotatef(-90, 0, 0, 1);   
    glCallList(2); 
	glRotatef(-180, 0, 0, 1);   
    glCallList(2); 
	glRotatef(-270, 0, 0, 1);   
    glCallList(2); 
	
	glDisable(GL_TEXTURE_2D); //关闭GL_TEXTURE_2D纹理
	 
    glFlush();  //刷新
}


//响应键盘按键的回调函数
void Keyboard(unsigned char uchKey, int iXPos, int iYPos)
{
	if (uchKey == 27/*Esc*/) {
		exit(0);
	}
		//光源位置控制：
	if (uchKey >='0' && uchKey <='4') {
	  setLight(uchKey-'0');
	}
	glutPostRedisplay(); 
}

void Special(int iKey, int iXPos, int iYPos)
{
	if(iKey == 100/*Left*/) {
		eyex -= 0.5;  //eyey += 1; 
	}
	if(iKey == 101/*Up*/) {
		eyez -= 0.5;
	}
	if(iKey == 102/*Right*/) {
	    eyex += 0.5; // eyey -= 1;
	}
	if(iKey == 103/*Down*/) {
		eyez += 0.5;
	}
	glutPostRedisplay(); 
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(400, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("纹理应用示例（Esc键退出）");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard); //键盘按下时调用的回调函数
	glutSpecialFunc(Special); //特殊按键的回调函数
	glutMainLoop();
	return 0;
}