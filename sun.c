#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <GL/glaux.h>
#include <stdlib.h>
#include <windows.h>
#pragma comment ( lib, "glaux.lib" )
static int year0 = 0 ,year1 = 0,year2=0, year3=0,day = 0;

#define stripeImageWidth 12
GLboolean isvisible=1;
static GLuint texName[3];

GLuint flag = 1;
GLUquadricObj* qobj[3];
 


//定义光源的颜色和位置
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat Light_Model_Ambient[] = { 0.2 , 0.2 , 0.2 , 1.0 }; 


void init(void)
{
	   
	AUX_RGBImageRec *TextureImage[2];
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //多边形的显示方式,模式将适用于物体的所有面采用填充形式
	
	glGenTextures(2, &texName);
	//地球纹理
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	if (TextureImage[0] = auxDIBImageLoadA("earth.bmp"))   
	{
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}
    //太阳纹理
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//	memset(TextureImage, 0, sizeof(void *) * 1);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	if (TextureImage[1] = auxDIBImageLoadA("sun1.bmp"))   
	{
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);
	}
	
	
	glBindTexture(GL_TEXTURE_2D, texName[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	memset(TextureImage, 0, sizeof(void *) * 1);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	if (TextureImage[2] = auxDIBImageLoadA("moon.bmp"))   
	{
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[2]->sizeX, TextureImage[2]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[2]->data);
	}
	
	
	
	
	
	   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	   glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	   glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	   glLightModelfv( GL_LIGHT_MODEL_AMBIENT , Light_Model_Ambient ); 
	   
	   
	   //	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	   
	   
	   //glEnable(GL_AUTO_NORMAL);
	   //glEnable(GL_NORMALIZE);//启用法向量单位化状态
	   //glFrontFace(GL_CW);
	   
	   
	   //设置清屏色  
	   glClearColor (0.0, 0.0, 0.0, 0.0);
	   //设置着色模式，默认为smooth
	   glShadeModel (GL_SMOOTH);
	   
	   
	   
	   
	   //glClearDepth(1.0f);
	   //glDepthFunc(GL_LEQUAL);//深度缓冲比较值,通过传入的z值是否小于或等于存储z值
	   
	   //glMatrixMode(GL_PROJECTION);
	   //glLoadIdentity();
	   //	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);//正射投影函数
	   
	   //	glLightModeli( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	   glEnable( GL_COLOR_MATERIAL );
	   glEnable(GL_LIGHTING);
	   glEnable(GL_LIGHT0);
	   glEnable(GL_DEPTH_TEST);
	   
}




void display(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    qobj[0] = gluNewQuadric();
    qobj[1] = gluNewQuadric();
	qobj[2] = gluNewQuadric();
	
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	gluQuadricTexture(qobj[1], GL_TRUE);//纹理函数
	glPushMatrix();
	day = (day + 5) % 360;
	year0 = (year0 + 2) % 360;
	year1 = (year1 + 2) % 360;
	year2 = (year2 + 3)% 360;
	year3 = (year3 + 5)% 360;
	
	glRotatef ((GLfloat) year0, 0.0, 0.0, 1.0);  //太阳自转，
    glColor3f(1,0.18824,0.18824);
	gluSphere(qobj[1], 1, 60, 60);
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, texName[0]);
	gluQuadricTexture(qobj[0], GL_TRUE);//纹理函数
    //画一个地球
	glPushMatrix();
	glRotatef ((GLfloat) year2, 0.0, 0.0, 1.0);
	glTranslatef (0.0, 2.8, 0.0);
	glRotatef ((GLfloat) day, 0.0, 0.0, 1.0);
    glColor3f(0.11765,0.56471,1);
	gluSphere(qobj[0], 0.3, 60, 60);//二次曲面qobj
	glPopMatrix();
	
	
	glBindTexture(GL_TEXTURE_2D, texName[2]);
	gluQuadricTexture(qobj[2], GL_TRUE);//纹理函数
	glPushMatrix();
	
	//画一个月亮
	
	glRotatef ((GLfloat) year2, 0.0, 0.0, 1.0);
	
	//沿y轴-方向移动2.8个单位长度，此时地球的局部坐标系统已经与全局的坐标系统偏移  
	glTranslatef (0.0, 2.8, 0.0);
    //沿z轴旋转day度，此时地球的局部坐标系统与全局坐标系统一致，表现出自转  
	glRotatef ((GLfloat) day, 0.0, 0.0, 1.0);
	
	
	glRotatef ((GLfloat) year3, 0.0, 0.0, 1.0);
	glTranslatef (0.0, 0.5, 0.0);
	glRotatef ((GLfloat) day, 0.0, 0.0, 1.0);
	
	
	glColor3f(1,0.87059,0.67843);
	//glutSolidSphere(0.08, 30, 30);
	gluSphere(qobj[2], 0.08, 60, 60);
	
	
	glutPostRedisplay();
	//弹出栈顶矩阵  
	glPopMatrix();
	//强制完成绘制指令  
    glFlush ();
	//交换缓冲区数据  
	glutSwapBuffers();
	glutPostRedisplay();
	Sleep(100);//延时0.05秒后执行
    //glEnable(GL_TEXTURE_1D);
}

void keyboard(int btn, int x, int y){
	if(isvisible){
		glEnable(GL_TEXTURE_2D);
		isvisible=0;
	}else {
		glDisable(GL_TEXTURE_2D);
		isvisible=1;
	}
}

void reshape (int w, int h)
{
	
	//环境光
	//设置视口矩形区域，在默认情况下，视口被设置为占据打开窗口的整个像素矩形  
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	//之后的矩阵操作定义为投影矩阵操作  
	glMatrixMode (GL_PROJECTION);
	//等于是将之前矩阵变换导致变化过的栈顶矩阵重新归位，置为单位矩阵.等于是之前的矩阵变换带来的影响到此为止
	glLoadIdentity ();
	//设置眼睛睁开的角度，视景体的宽高比，近截面的距离，远截面的距离  
	gluPerspective(60, (GLfloat) w/(GLfloat) h, 1 ,20);
	
	//让光源位置保持不变 
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
	else
		glOrtho(1.5*(GLfloat)w/(GLfloat)h,1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
    //之后的矩阵操作定义为模型视图矩阵操作  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//相机位置(5, 0, 0)，相机镜头朝向(0, 0, 0)，相机顶部朝前方  
	gluLookAt (5.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);// GLUT 环境初始化
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // 显示模式初始化
	glutInitWindowSize (900, 600);// 定义窗口大小
	glutInitWindowPosition (100, 100);// 定义窗口位置 
	glutCreateWindow ("201151217-李致远-实验3"); // 显示窗口,窗口标题为执行函数名
	init ();
	glutDisplayFunc(display);// 注册 OpenGL 绘图函数(一种特殊的调用方式,下同)
	//glutDisplayFunc(draw_tellurion);
    //glutIdleFunc(Moving);
	glutIdleFunc(display);
	glutReshapeFunc(reshape); // 注册窗口大小改变时的响应函数
	glutKeyboardFunc(keyboard);
	glutMainLoop(); // 进入 GLUT 消息循环，开始执行程序
	return 0;
}
