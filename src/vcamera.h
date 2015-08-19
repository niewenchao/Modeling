/**********************************************************************
DESCRIPTION: vcamera.h
摄像机 lookat的封装，使用VMatrix3类包装lookat三个参数

CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************/
#ifndef _H_VCAMERA_H_
#define _H_VCAMERA_H_
///////////////////////////////////////////////
#include "vpoint.h"
#include "vglobaltools.h"
#include "vmatrix.h"

class VCamera{
protected:
	VMatrix3 m_Mat;//使用矩阵保持摄像机位置、方向、朝向
public:
	//构造函数
	VCamera()
	{
	}
	
	//摄像机单位化
	void Identify()
	{
		m_Mat.IdentifyTM();
	}
	//获得摄像机位置
	VVector3 GetCameraPos()
	{
		return m_Mat.TransPoint(VVector3(0.0f,0.0f,0.0f));
	}
	//获得摄像机方向
	VVector3 GetCameraView()
	{
		return m_Mat.TransPoint(VVector3(0.0f,0.0f,-300.0f));
	}
	//获得摄像机朝向
	VVector3 GetCameraDir()
	{
		VVector3 camPos = m_Mat.TransPoint(VVector3(0.0f,0.0f,0.0f));
		VVector3 camDir = m_Mat.TransPoint(VVector3(0.0f,1.0f,0.0f));
		camDir = camDir - camPos;
		return camDir;
	}
	//移动摄像机，v-移动向量
	void TransferCamera(VVector3& v)					//平移视图
	{
		m_Mat.MoveTM(v);
	}
	//旋转摄像机 v-旋转轴 angle-旋转角度
	void RotateCamera(VVector3& v,float angle)				//旋转视图
	{
		VPoint3 oldPos = GetCameraPos();						//
		VPoint3 view = GetCameraView();						//
		VVector3 oldDir = GetCameraDir();						//
		VVector3 axis = v - oldPos;
		m_Mat.MoveTM(view - oldPos);						//平移
		m_Mat.RotateTM(VAxisAngle(axis,angle));		//旋转
		m_Mat.MoveTM(GetCameraPos() - GetCameraView());						//再平移回来
	}
	//缩放摄像机 factor-缩放因子
	void ZoomCamera(float factor)						//缩放视图
	{
		m_Mat.ScaleTM(VVector3(factor,factor,factor));
	}
	/*********************************************************************************
	  *Function:GetCamPara(VPoint3 p_start,VPoint3 p_end)  
	  *Description：从两个点的坐标获得摄像机移动向量 
	  *Input: p_start-左鼠标点击点，p_end-鼠标移动点 
	  *Return: 摄像机在摄像机空间的移动向量 
	              *CREATED BY:  [8/10/2015 niewenchao]
	**********************************************************************************/
	VVector3 GetCamMovePara(VPoint3 p_start,VPoint3 p_end)
	{
		VVector3 v;
		v = VVector3(int(p_start.x-p_end.x),int(p_end.y-p_start.y),0);
		//转换到摄像机空间  
		v = m_Mat.TransPoint(v);
		v -= m_Mat.TransPoint(VVector3(0.0f,0.0f,0.0f));
		//v /= 250;
		return v;
		
	}
	VVector3 GetCamRotatePara(VPoint3 p_start,VPoint3 p_end)
	{
		float x = p_end.x-p_start.x;
		float y = p_end.y-p_start.y;
		int xSbl = 1,ySbl = 1;
		VVector3 v;
		if (y<0) ySbl = -1;
		if (x<0) xSbl = -1;
		if (x == 0)
			v.SetXYZ(-10.0*ySbl,0.0,0.0);
		else if (y == 0)
			v.SetXYZ(0.0,-10.0*xSbl,0.0);
		else
			v.SetXYZ(-10.0*ySbl,-10.0*(float)y/(float)x*ySbl,0.0);
		v = m_Mat.TransPoint(v);
		return v;

	}
	//应用摄像机
	inline void ApplyCameraTransform(bool bRotOnly = false)    
			{
			VVector3 vPos = GetCameraPos();
			VVector3 vView = GetCameraView();
			VVector3 vUp = GetCameraDir();

			gluLookAt(vPos.x, vPos.y, vPos.z,
						vView.x, 
						vView.y, 
						vView.z , 
						vUp.x, vUp.y, vUp.z);
			
			}

};
///////////////////////////////////////////////
#endif