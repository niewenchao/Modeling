/**********************************************************************
DESCRIPTION: 定义了基本图元的绘制接口 

CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************/
#ifndef _VRENDER_H_
#define _VRENDER_H_
///////////////////////////////////////////////
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <gl/glaux.h>
#include "vmatrix.h"
#include "vboundbox.h"
#include "vface.h"
//////////////////////////////////////////////////////////////////////////
class VRender
{
public:
	VRender(){};
	~VRender(){};
	static VRender* GetSingleton();
	static void DestroySingleton();	
public:
	//矩阵变换
	void SetTransform(const VMatrix3& matrix);
	void RemoveTransform(const VMatrix3& matrix);
public:
	//基本图元绘制接口	
	//绘制点集 
	void DrawPoints(int numVerts,VPoint3* pVerts,VPoint3* pColor );
	//绘制线段
	void DrawLine(VPoint3& p0,VPoint3& p1,VPoint3& pColor);
	//绘制连接线段集
	void DrawLines(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor,bool bClosed = TRUE);
	//绘制一个多边形
	void DrawPolygon(int numVerts,VPoint3* pVerts,VPoint3* pColor);
	//绘制三角形
	void DrawTriangle(VPoint3* pVerts,VPoint3* pColor );
	//绘制连接三角形带
	void DrawTriStrip(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor);
	//绘制多个三角形
	void DrawTriangles(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor);	
	//绘制包围盒
	void DrawBoundBox(VBoundBox& box); 
	//绘制网格边环
	//void DrawBorder(vector<VPoint3>& vpt,VPoint3 color);

	//使用摄像机
	void RenderCamera(VVector3& camPos,VVector3& camView,VVector3& camDir);
private:
	static VRender* m_pRender;//单例
};





///////////////////////////////////////////////
#endif