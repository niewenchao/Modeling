/**********************************************************************
DESCRIPTION: 主函数 负责图形显示、交互 

CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************/
#include <windows.h>		// Must have for Windows platform builds
#define _USE_MATH_DEFINES  //没有这个不能使用M_PI
#include <cmath>
#include <stdlib.h>
#include "glee.h"			// OpenGL Extension "autoloader"
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <gl\glu.h>			// OpenGL Utilities
#define GLUT_DISABLE_ATEXIT_HACK
#include "glut.h"			// Glut (Free-Glut on Windows)
#include "vmatrix.h"
#include "vcamera.h"
#include "vmesh.h"
#include "vimport.h"   
#include "vscene.h"
#include <fstream>
#include <vector>
#include "define.h"
std::vector<VPoint3> vecPoint;

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
//vcamera
VCamera gcamera;
//定义视图、对象 旋转 移动 缩放
int op_type;
//记录鼠标按下的点
VPoint3 startPt;					
VPoint3 endPt;
//左鼠标是否按下
bool LB_Down;

void ReadCgal(string fileName)
{
	FILE* fp = fopen(fileName.c_str(), "r+");
	VPoint3 pt1,pt2;
	while(fscanf(fp,"%f %f %f %f %f %f\n",&pt1.x,&pt1.y,&pt1.z,&pt2.x,&pt2.y,&pt2.z) != EOF)
	{
		vecPoint.push_back(pt1);
		vecPoint.push_back(pt2);
	}
	fclose(fp);
}
void DrawXYZ()
{
	glPushMatrix();  
	glTranslatef(-2.2,-1.7,0.0);  
	float fCurColor[4];															//记录当前颜色
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);//获取当前颜色
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0);//X
	glVertex3f(0,0,0);  
	glVertex3f(0.2,0,0);

	glColor3f(0.0,1.0,0.0);//Y
	glVertex3f(0,0,0);  
	glVertex3f(0,0.2,0);  

	glColor3f(0.0,0.0,1.0);//Z
	glVertex3f(0,0,0);  
	glVertex3f(0,0,0.2); 
	glEnd();  
	glColor4fv(fCurColor);											//恢复上一次绘制的颜色
	glLineWidth(1.0);
	glPopMatrix();  
}
// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	glViewport(0, 0, w, h);//把视口想象为一个单位正方形

	fAspect = (GLfloat)w / (GLfloat)h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the clipping volume
	gluPerspective(45.0f, fAspect, 0.1f, 100000.0f);
	//默认情况下，相机位于原点，指向z轴的负向，同时把y轴的正向作为向上向量。
	//这就相当于调用：gluLookAt(0.0,0.0,0.0,    0.0,0.0,-100.0,    0.0,1.0,0.0 ),不对参数重新设置很有可能看不到图像
	gluLookAt(0.0f,0.0f,400.0f,//摄像机位置 越远越小
		0.0f,0.0f,0.0f,//看向哪边
		0.0f,1.0f,0.0f);//摄像机朝向
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
}


// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
{
	
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, .50f, 1.0f );
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	// Draw everything as wire frame
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//VImport::GetInstance()->DoImport("I:/毕设/VCC例子1/海龟/triangle.VCC");
	VImport::GetInstance()->DoImport("E:/Data/haiguimesh.VCC");
	VNode* pNode = VScene::GetInstance()->GetRootNode()->GetChildNode(0);
	/*pNode->Scale(VVector3(0.001,0.001,0.001));
	pNode->Rotate(VAxisAngle(VVector3(1,0,0),-90*M_PI/180));
	pNode->Rotate(VAxisAngle(VVector3(0,0,1),90*M_PI/180));
	pNode->Move(VVector3(0.0,-1.0,0.0));*/
	//pNode->GetMesh()->SetShowMode(MESH_POINT_LINE_SOLID);
	ReadCgal("F:/programming software/cgal-releases-CGAL-4.7-alpha1/build/examples/Surface_mesh_skeletonization/skel.cgal");

}

// Respond to arrow keys
void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		gcamera.TransferCamera(VVector3(0.0,0.0,-0.1));

	if(key == GLUT_KEY_DOWN)
		gcamera.TransferCamera(VVector3(0.0,0.0,0.1));

	if(key == GLUT_KEY_LEFT)
		gcamera.RotateCamera(VVector3(0.0,1.0,0.0),0.1);

	if(key == GLUT_KEY_RIGHT)
		gcamera.RotateCamera(VVector3(0.0,1.0,0.0),-0.1);
	if (key == GLUT_KEY_F1)
	{
		op_type = ID_VIEW_MOVE;
	}
	if (key == GLUT_KEY_F2)
	{
		op_type = ID_VIEW_ROTATE;
	}
	if (key == GLUT_KEY_F3)
	{
		op_type = ID_VIEW_SCALE;
	}
	if (key == GLUT_KEY_F4)
	{
		op_type = ID_OBJECT_MOVE;
	}
	if (key == GLUT_KEY_F5)
	{
		op_type = ID_OBJECT_ROTATE;
	}
	if (key == GLUT_KEY_F6)
	{
		op_type = ID_OBJECT_SCALE;
	}
	// Refresh the Window
	glutPostRedisplay();
}

// Draw a torus (doughnut), using the current 1D texture for light shading
void DrawTorus(VMatrix3 mTransform)
{
	GLfloat majorRadius = 0.25f;
	GLfloat minorRadius = 0.1f;
	GLint   numMajor = 40;
	GLint   numMinor = 20;
	VPoint3 objectVertex;         // Vertex in object/eye space
	VPoint3 transformedVertex;    // New Transformed vertex   
	double majorStep = 2.0f*M_PI / numMajor;
	double minorStep = 2.0f*M_PI / numMinor;
	int i, j;

	for (i=0; i<numMajor; ++i) 
	{
		double a0 = i * majorStep;
		double a1 = a0 + majorStep;
		GLfloat x0 = (GLfloat) cos(a0);
		GLfloat y0 = (GLfloat) sin(a0);
		GLfloat x1 = (GLfloat) cos(a1);
		GLfloat y1 = (GLfloat) sin(a1);

		glBegin(GL_TRIANGLE_STRIP);
		for (j=0; j<=numMinor; ++j) 
		{
			double b = j * minorStep;
			GLfloat c = (GLfloat) cos(b);
			GLfloat r = minorRadius * c + majorRadius;
			GLfloat z = minorRadius * (GLfloat) sin(b);

			// First point
			objectVertex.x = x0*r;
			objectVertex.y = y0*r;
			objectVertex.z = z;
			transformedVertex = mTransform.TransPoint(objectVertex);
			float v[3] = {transformedVertex.x,transformedVertex.y,transformedVertex.z };
			glVertex3fv(v);

			// Second point
			objectVertex.x = x1*r;
			objectVertex.y = y1*r;
			objectVertex.z = z;
			transformedVertex = mTransform.TransPoint(objectVertex);
			v[0] = transformedVertex.x;
			v[1] = transformedVertex.y;
			v[2] = transformedVertex.z;
			glVertex3fv(v);
		}
		glEnd();
	}
}
// Draw a gridded ground
void DrawGround(void)
{
	GLfloat fExtent = 1000.0f;
	GLfloat fStep = 1.0f;
	GLfloat y = -0.9f;
	GLint iLine;

	glBegin(GL_LINES);
	for(iLine = -fExtent; iLine <= fExtent; iLine += fStep)
	{
		glVertex3f(iLine, y, fExtent);    // Draw Z lines
		glVertex3f(iLine, y, -fExtent);

		glVertex3f(fExtent, y, iLine);
		glVertex3f(-fExtent, y, iLine);
	}

	glEnd();
}

void DrawCgal(std::vector<VPoint3> vec_point)
{
	for (int i = 0; i < vec_point.size(); i+=2)
	{
		glPointSize(5.0f);
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_POINTS);
			glVertex3f(vec_point[i].x, vec_point[i].y, vec_point[i].z);
			glVertex3f(vec_point[i+1].x, vec_point[i+1].y, vec_point[i+1].z);
		glEnd();
		glPointSize(1.0f);
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_LINES);
			glVertex3f(vec_point[i].x, vec_point[i].y, vec_point[i].z);
			glVertex3f(vec_point[i+1].x, vec_point[i+1].y, vec_point[i+1].z);
		glEnd();
	}
}

// Called to draw scene
void RenderScene(void)
{
	VMatrix3   transformationMatrix;   // Storeage for rotation matrix
	static GLfloat yRot = 0.0f;         // Rotation angle for animation
	yRot += 0.5f;

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	//DrawGround();
	//DrawXYZ();
	glPopMatrix();
	
	gcamera.ApplyCameraTransform();
	gcamera.Identify();
	//gluLookAt(0.0f,0.0f,0.0f,//摄像机位置 越远越小
	//	0.0f,0.0f,1.0f,//看向哪边
	//	0.0f,1.0f,0.0f);//摄像机朝向
	
	VScene::GetInstance()->Render();
	//DrawCgal(vecPoint);

	// Do the buffer Swap
	glutSwapBuffers();
	//glFlush();
}
void TimerFunction(int value)
{
	// Redraw the scene with new coordinates
	glutPostRedisplay();
	glutTimerFunc(33,TimerFunction, 1);
}

static void MouseClick(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		VScene::GetInstance()->Hit(x,y);
		startPt = VPoint3(x, y, 0);
		LB_Down = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		LB_Down = false;
	}
		
	
	
}
static void MouseClickMotion(int x, int y)
{
	if (LB_Down)
	{
		
		endPt = VPoint3(x, y, 0);
		if (op_type == ID_VIEW_MOVE || op_type == ID_VIEW_ROTATE || op_type == ID_VIEW_SCALE)
		{
			float xDist = 0,yDist = 0;
			switch(op_type)
			{
			case ID_VIEW_MOVE://平移场景
				
				gcamera.TransferCamera(gcamera.GetCamMovePara(startPt,endPt));
				break;
			case ID_VIEW_ROTATE://旋转场景
				gcamera.RotateCamera(gcamera.GetCamMovePara(startPt,endPt),0.003);
				break;
			case ID_VIEW_SCALE://缩放场景
				xDist = endPt.x - startPt.x; 
				yDist = endPt.y - startPt.y;
				gcamera.ZoomCamera(1.0+0.05*xDist+0.05*yDist);
				break;
			}
		}
		else
		{
			VNodeSelector* selector = VScene::GetInstance()->GetNodeSelector();
			for (int i = selector->GetNumSelNodes()-1; i>=0; i-- )
			{
				VNode* node = selector->GetSelNode(i);
				if(!node) continue;
				VMatrix3 mat = node->GetNodeTM();
				VPoint3 CenterPt(mat.GetValue(0,3),mat.GetValue(1,3),mat.GetValue(2,3));//获取深度
				CenterPt = VScene::GetViewPortPt(CenterPt);
				VVector3 vTemp;
				switch(op_type)
				{
				case ID_OBJECT_MOVE://平移物体
					node->Move(VScene::GetTransPt(startPt,endPt,CenterPt));  
					break;
				case ID_OBJECT_ROTATE://旋转物体
					vTemp = VScene::GetRotatePt(startPt,endPt,CenterPt);
					node->Rotate(VAxisAngle(vTemp, 0.05f));
					break;
				case ID_OBJECT_SCALE://缩放物体
					node->Scale(VScene::GetScalePt(startPt,endPt));//对物体进行缩放操作
					break;
				}
			}
		}
		startPt = endPt;
	}
	else return;
  }

	

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Perspective Projection");
	glutReshapeFunc(ChangeSize);//窗口尺寸改变
	glutSpecialFunc(SpecialKeys);//按键
	glutMouseFunc(MouseClick);//鼠标点击事件
	glutMotionFunc(MouseClickMotion);//鼠标点击移动
	glutDisplayFunc(RenderScene);//渲染
	glutTimerFunc(33, TimerFunction, 1);//间隔时间调用
	
	SetupRC();
	glutMainLoop();



	return 0;
}


