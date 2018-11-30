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
 


//�����Դ����ɫ��λ��
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat Light_Model_Ambient[] = { 0.2 , 0.2 , 0.2 , 1.0 }; 


void init(void)
{
	   
	AUX_RGBImageRec *TextureImage[2];
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //����ε���ʾ��ʽ,ģʽ���������������������������ʽ
	
	glGenTextures(2, &texName);
	//��������
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	if (TextureImage[0] = auxDIBImageLoadA("earth.bmp"))   
	{
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}
    //̫������
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
	   //glEnable(GL_NORMALIZE);//���÷�������λ��״̬
	   //glFrontFace(GL_CW);
	   
	   
	   //��������ɫ  
	   glClearColor (0.0, 0.0, 0.0, 0.0);
	   //������ɫģʽ��Ĭ��Ϊsmooth
	   glShadeModel (GL_SMOOTH);
	   
	   
	   
	   
	   //glClearDepth(1.0f);
	   //glDepthFunc(GL_LEQUAL);//��Ȼ���Ƚ�ֵ,ͨ�������zֵ�Ƿ�С�ڻ���ڴ洢zֵ
	   
	   //glMatrixMode(GL_PROJECTION);
	   //glLoadIdentity();
	   //	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);//����ͶӰ����
	   
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
	gluQuadricTexture(qobj[1], GL_TRUE);//������
	glPushMatrix();
	day = (day + 5) % 360;
	year0 = (year0 + 2) % 360;
	year1 = (year1 + 2) % 360;
	year2 = (year2 + 3)% 360;
	year3 = (year3 + 5)% 360;
	
	glRotatef ((GLfloat) year0, 0.0, 0.0, 1.0);  //̫����ת��
    glColor3f(1,0.18824,0.18824);
	gluSphere(qobj[1], 1, 60, 60);
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, texName[0]);
	gluQuadricTexture(qobj[0], GL_TRUE);//������
    //��һ������
	glPushMatrix();
	glRotatef ((GLfloat) year2, 0.0, 0.0, 1.0);
	glTranslatef (0.0, 2.8, 0.0);
	glRotatef ((GLfloat) day, 0.0, 0.0, 1.0);
    glColor3f(0.11765,0.56471,1);
	gluSphere(qobj[0], 0.3, 60, 60);//��������qobj
	glPopMatrix();
	
	
	glBindTexture(GL_TEXTURE_2D, texName[2]);
	gluQuadricTexture(qobj[2], GL_TRUE);//������
	glPushMatrix();
	
	//��һ������
	
	glRotatef ((GLfloat) year2, 0.0, 0.0, 1.0);
	
	//��y��-�����ƶ�2.8����λ���ȣ���ʱ����ľֲ�����ϵͳ�Ѿ���ȫ�ֵ�����ϵͳƫ��  
	glTranslatef (0.0, 2.8, 0.0);
    //��z����תday�ȣ���ʱ����ľֲ�����ϵͳ��ȫ������ϵͳһ�£����ֳ���ת  
	glRotatef ((GLfloat) day, 0.0, 0.0, 1.0);
	
	
	glRotatef ((GLfloat) year3, 0.0, 0.0, 1.0);
	glTranslatef (0.0, 0.5, 0.0);
	glRotatef ((GLfloat) day, 0.0, 0.0, 1.0);
	
	
	glColor3f(1,0.87059,0.67843);
	//glutSolidSphere(0.08, 30, 30);
	gluSphere(qobj[2], 0.08, 60, 60);
	
	
	glutPostRedisplay();
	//����ջ������  
	glPopMatrix();
	//ǿ����ɻ���ָ��  
    glFlush ();
	//��������������  
	glutSwapBuffers();
	glutPostRedisplay();
	Sleep(100);//��ʱ0.05���ִ��
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
	
	//������
	//�����ӿھ���������Ĭ������£��ӿڱ�����Ϊռ�ݴ򿪴��ڵ��������ؾ���  
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	//֮��ľ����������ΪͶӰ�������  
	glMatrixMode (GL_PROJECTION);
	//�����ǽ�֮ǰ����任���±仯����ջ���������¹�λ����Ϊ��λ����.������֮ǰ�ľ���任������Ӱ�쵽��Ϊֹ
	glLoadIdentity ();
	//�����۾������ĽǶȣ��Ӿ���Ŀ�߱ȣ�������ľ��룬Զ����ľ���  
	gluPerspective(60, (GLfloat) w/(GLfloat) h, 1 ,20);
	
	//�ù�Դλ�ñ��ֲ��� 
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
	else
		glOrtho(1.5*(GLfloat)w/(GLfloat)h,1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
    //֮��ľ����������Ϊģ����ͼ�������  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//���λ��(5, 0, 0)�������ͷ����(0, 0, 0)�����������ǰ��  
	gluLookAt (5.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);// GLUT ������ʼ��
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // ��ʾģʽ��ʼ��
	glutInitWindowSize (900, 600);// ���崰�ڴ�С
	glutInitWindowPosition (100, 100);// ���崰��λ�� 
	glutCreateWindow ("201151217-����Զ-ʵ��3"); // ��ʾ����,���ڱ���Ϊִ�к�����
	init ();
	glutDisplayFunc(display);// ע�� OpenGL ��ͼ����(һ������ĵ��÷�ʽ,��ͬ)
	//glutDisplayFunc(draw_tellurion);
    //glutIdleFunc(Moving);
	glutIdleFunc(display);
	glutReshapeFunc(reshape); // ע�ᴰ�ڴ�С�ı�ʱ����Ӧ����
	glutKeyboardFunc(keyboard);
	glutMainLoop(); // ���� GLUT ��Ϣѭ������ʼִ�г���
	return 0;
}
