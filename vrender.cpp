#include "vrender.h"
VRender* VRender::m_pRender = NULL;
//////////////////////////////////////////////////////////////////////////
//获取单例
VRender* VRender::GetSingleton()
{
	if (!m_pRender)	
	{m_pRender = new VRender;}
	return m_pRender;
}
//摧毁单例
void VRender::DestroySingleton()
{
	if (m_pRender)

	{
		delete m_pRender;
		m_pRender = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//	渲染矩阵变换
void VRender::SetTransform(const VMatrix3& matrix)
{
	glPushMatrix();
	float fMatrix[16];
	matrix.GetTransPoseMat(fMatrix);//opengl识别的矩阵为16个元素的数组
	glMultMatrixf(fMatrix);
}
//恢复变换之前的矩阵状态
void VRender::RemoveTransform(const VMatrix3& matrix)
{
	glPopMatrix();
}
//////////////////////////////////////////////////////////////////////////
//基本图元绘制接口
/*********************************************************************************
  *Function:  DrawPoints(int num,VPoint3* pVerts,VPoint3* pColor)
  *Description： 绘制顶点数组
  *Input: num：顶点个数；pVerts：顶点数组；pColor：顶点颜色
  *Return: 无 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawPoints(int num,VPoint3* pVerts,VPoint3* pColor)
{      
	if(num <= 0 || !pVerts)
		return;
	float fCurColor[4];
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);//查询系统状态的当前值，可以是颜色，可以使模型视图矩阵等
	//启用顶点数组
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,sizeof(VPoint3),pVerts);	
	if(pColor)
	{
		//启用颜色数组
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3,GL_FLOAT,sizeof(VPoint3),pColor);		
	}
	glDrawArrays(GL_POINTS,0,num);
	if(pColor) glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glColor4fv(fCurColor);//恢复系统的状态
}
/*********************************************************************************
  *Function: DrawLine(VPoint3& p0,VPoint3& p1,VPoint3& pColor) 
  *Description：绘制线段P0P1 
  *Input:  p0：顶点0；p1：顶点1；pColor：线段颜色
  *Return: 无 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawLine(VPoint3& p0,VPoint3& p1,VPoint3& pColor)
{
	float fCurColor[4];
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);
	glColor4f(pColor.x,pColor.y,pColor.z,1.0f);
	glBegin(GL_LINES);		
	glVertex3f(p0.x,p0.y,p0.z);
	glVertex3f(p1.x,p1.y,p1.z);
	glEnd();
	glColor4fv(fCurColor);
}
/*********************************************************************************
  *Function:DrawLines(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor,bool bClosed )  
  *Description：按照面的拓扑绘制闭合线段或连接线段 
  *Input:  numFaces：面数;pVerts:顶点数组;pColor：顶点颜色;  bClosed：是否为闭合线段；pFaces:面数组
  *Return: 无 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawLines(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor,bool bClosed /* = TRUE */)
{
	if(numFaces <= 0)
		return;
	float fCurColor[4];
	int LineMode = 0;
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);
	if(bClosed)
		LineMode = GL_LINE_LOOP;
	else
		LineMode = GL_LINE_STRIP;
	for (int i = 0;i<numFaces;i++)
	{
		glBegin(LineMode);
		for (int j = 0;j<3;j++)
		{
			int indexVert = pFaces[i].GetVert(j);
			if(pColor)
				glColor4f(pColor[indexVert].x,pColor[indexVert].y,pColor[indexVert].z,1.0f);
			//glColor4f(0.6,0.6,0.6,1.0);
			glVertex3f(pVerts[indexVert].x,pVerts[indexVert].y,pVerts[indexVert].z);
		}
		glEnd();
	}
	glColor4fv(fCurColor);
}
/*********************************************************************************
  *Function: DrawPolygon(int numVerts,VPoint3* pVerts,VPoint3* pColor) 
  *Description：绘制多边形 
  *Input:  numVerts：顶点个数；pVerts：顶点数组；pColor：顶点颜色;
  *Return: 无 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawPolygon(int numVerts,VPoint3* pVerts,VPoint3* pColor)
{
	if(numVerts <= 0)
		return;
	float fCurColor[4];
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);
	glBegin(GL_POLYGON);
	for (int i = 0;i<numVerts;i++)
	{
		if (pColor)
			glColor4f(pColor[i].x,pColor[i].y,pColor[i].z,1.0f);
		glVertex3f(pVerts[i].x,pVerts[i].y,pVerts[i].z);
	}
	glEnd();
	glColor4fv(fCurColor);
}
/*********************************************************************************
  *Function:  DrawTriangle(VPoint3* pVerts,VPoint3* pColor)
  *Description：绘制三角形 
  *Input:  pVerts：顶点数组；pColor：顶点颜色
  *Return: 无 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawTriangle(VPoint3* pVerts,VPoint3* pColor)
{	
	float fCurColor[4];
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);
	glBegin(GL_TRIANGLES);
	for(int i = 0;i<3;i++)
	{
		if(pColor)
			glColor4f(pColor[i].x,pColor[i].y,pColor[i].z,1);
		glVertex3f(pVerts[i].x,pVerts[i].y,pVerts[i].z);
	}		
	glEnd();
	glColor4fv(fCurColor);
}
/*********************************************************************************
  *Function: DrawTriStrip(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor) 
  *Description： 绘制三角形带
  *Input:  numFaces：面数；pFaces:面数组；pVerts：顶点数组； pColor：顶点颜色;
  *Return: 无 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawTriStrip(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor)
{
	if(numFaces <= 0)
		return;
	float fCurColor[4];
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0;i<numFaces;i++)
	{
		for (int j = 0;j<3;j++)
		{
			int index = pFaces[i].GetVert(j);
			if (pColor)
				glColor4f(pColor[index].x, pColor[index].y, pColor[index].z, 1.0f);
			glVertex3f(pVerts[index].x, pVerts[index].y, pVerts[index].z);
		}		

	}
	glEnd();
	glColor4fv(fCurColor);
}
/*********************************************************************************
  *Function:DrawTriangles(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor)  
  *Description：绘制numFaces个三角形 
  *Input:  numFaces：面数；pFaces:面数组；pVerts：顶点数组； pColor：顶点颜色
  *Return: 无 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawTriangles(int numFaces,VFace* pFaces,VPoint3* pVerts,VPoint3* pColor)
{
	if(numFaces <= 0)
		return;
	float fCurColor[4];
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);		
	glBegin(GL_TRIANGLES);
	for (int i = 0;i<numFaces;i++)
	{	
		for (int j = 0;j<3;j++)
		{
			int vindex = pFaces[i].GetVert(j);
			if (pColor)
				glColor4f(pColor[vindex].x,pColor[vindex].y,pColor[vindex].z,1.0f);
			glVertex3f(pVerts[vindex].x,pVerts[vindex].y,pVerts[vindex].z);
		}		
	}
	glEnd();
	glColor4fv(fCurColor);
}
/*********************************************************************************
  *Function: DrawBoundBox(VBoundBox& box) 
  *Description：绘制包围盒 
  *Input:  box 包围盒
  *Return: 无 
              *CREATED BY:  [8/6/2015 niewenchao]
**********************************************************************************/
void VRender::DrawBoundBox(VBoundBox& box)
{
	VPoint3 pDefC, pLC, pHC;
	pDefC = box.GetColor();
	pLC = box.Min();
	pHC = box.Max();
	float fCurColor[4];															//记录当前颜色
	glGetFloatv(GL_CURRENT_COLOR,fCurColor);										//获取当前颜色
	glColor3f(pDefC.x, pDefC.y, pDefC.z);									//设置当前绘制颜色
	//长方体共有12条边
	glBegin(GL_LINE_LOOP);
	//绘制背面线
	glVertex3f(pLC.x, pLC.y, pLC.z);
	glVertex3f(pLC.x, pLC.y, pHC.z);
	glVertex3f(pLC.x, pHC.y, pHC.z);
	glVertex3f(pLC.x, pHC.y, pLC.z);
	glEnd();
	glBegin(GL_LINE_LOOP);
	//绘制正面线
	glVertex3f(pHC.x, pLC.y, pLC.z);
	glVertex3f(pHC.x, pHC.y, pLC.z);
	glVertex3f(pHC.x, pHC.y, pHC.z);
	glVertex3f(pHC.x, pLC.y, pHC.z);
	glEnd();
	glBegin(GL_LINES);
	//绘制剩余的四条线
	glVertex3f(pLC.x, pLC.y, pLC.z);
	glVertex3f(pHC.x, pLC.y, pLC.z);										//1-th Edge
	glVertex3f(pLC.x, pLC.y, pHC.z);
	glVertex3f(pHC.x, pLC.y, pHC.z);										//2-th Edge
	glVertex3f(pLC.x, pHC.y, pLC.z);
	glVertex3f(pHC.x, pHC.y, pLC.z);										//3-th Edge
	glVertex3f(pLC.x, pHC.y, pHC.z);
	glVertex3f(pHC.x, pHC.y, pHC.z);										//4-th Edge
	glEnd();
	glColor4fv(fCurColor);											//恢复上一次绘制的颜色
}