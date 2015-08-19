/**********************************************************************
DESCRIPTION: 包围盒定义 

CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************/
#ifndef _VBOUNDBOX_H_
#define _VBOUNDBOX_H_
//////////////////////////////////////////////////////////////////////////
#include "vpoint.h"
//////////////////////////////////////////////////////////////////////////
class VBoundBox	{													// 包围盒的定义
public:
	// constructor
	VBoundBox(){}
	VBoundBox(const VPoint3& minpoint,const VPoint3& maxpoint, const VPoint3 color){
		m_Pmin = minpoint;
		m_Pmax = maxpoint;
		m_Color = color;
	}
	~VBoundBox(){}

public:
	VPoint3 m_Pmin;													// 低点
	VPoint3 m_Pmax;													// 高点
	VPoint3 m_Color;
public:	
	
	VPoint3& GetColor() {return m_Color;}
	void SetColor(VPoint3& newColor) {m_Color = newColor;}							//设置默认显示颜色
	void SetColor(float x, float y, float z)	{m_Color.SetXYZ(x, y, z);}				//设置默认显示颜色

	const VPoint3& Min() { return m_Pmin; }							// 返回低点
	const VPoint3& Max() { return m_Pmax; }							// 返回高点

	void InitBoundBox(){ m_Pmin.SetXYZ(0.0,0.0,0.0); m_Pmax.SetXYZ(0.0,0.0,0.0);}	// 初始化包围盒
											
	void SetBoundBox(VPoint3& p1,VPoint3& p2){	m_Pmin.SetXYZ(p1);	m_Pmax.SetXYZ(p2);}// 设置包围盒

	inline const VPoint3 Center(){ return (m_Pmax+m_Pmin)/(float)2.0;}	// 返回中心点
	inline const VPoint3 Width() { return (m_Pmax - m_Pmin);}			// 返回表示长宽高的点
	VPoint3 operator[](int i)const{										// 返回包围盒的8个端点
		switch (i)
		{
		case 0:return VPoint3(m_Pmin.x,m_Pmin.y,m_Pmin.z);
		case 1:return VPoint3(m_Pmax.x,m_Pmin.y,m_Pmin.z);
		case 2:return VPoint3(m_Pmin.x,m_Pmax.y,m_Pmin.z);
		case 3:return VPoint3(m_Pmax.x,m_Pmax.y,m_Pmin.z);
		case 4:return VPoint3(m_Pmin.x,m_Pmin.y,m_Pmax.z);
		case 5:return VPoint3(m_Pmax.x,m_Pmin.y,m_Pmax.z);
		case 6:return VPoint3(m_Pmin.x,m_Pmax.y,m_Pmax.z);
		case 7:return VPoint3(m_Pmax.x,m_Pmax.y,m_Pmax.z);
		}
	}
	VBoundBox& operator+=(const VPoint3& p){					//包围盒加上一个点
		m_Pmin += p;
		m_Pmax += p;
		return (*this);
	}
	

};
//////////////////////////////////////////////////////////////////////////
#endif