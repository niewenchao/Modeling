/**********************************************************************

DESCRIPTION:管理旋转轴和旋转角度 ，旋转角单位为弧度 

CREATED BY: 小菜C不是菜  [7/29/2015 niewenchao]
**********************************************************************/
#ifndef _VAXISANGLE_H_
#define _VAXISANGLE_H_
//////////////////////////////////////////////////////////////////////////
#include "vpoint.h"
//////////////////////////////////////////////////////////////////////////
class VAxisAngle
{
public:
	VAxisAngle(){ m_fAngle = 0.0; }
	VAxisAngle(VVector3& axis, float fAngle){ m_fAxis = axis; m_fAngle = fAngle; }
	VAxisAngle(VAxisAngle& AxisAng2){ m_fAxis = AxisAng2.m_fAxis; m_fAngle = AxisAng2.m_fAngle; }
	~VAxisAngle(){}

public:
	VVector3 m_fAxis;
	float m_fAngle;

public:
	VVector3 GetAxis(){ return m_fAxis; }
	float GetAngle(){ return m_fAngle; }
	void GetAxisAngle(VVector3& axis, float& fAngle){ axis = m_fAxis; fAngle = m_fAngle; }
	void SetAxis(VVector3& axis){ m_fAxis = axis; }
	void SetAngle(float fAngle){ m_fAngle = fAngle; }
	void SetAxisAngle(VVector3& axis, float fAngle){ m_fAxis = axis; m_fAngle = fAngle; }
	void SetAxisAngle(float x, float y, float z, float fAngle){ m_fAxis.SetXYZ(x,y,z); m_fAngle = fAngle; }
};

#endif