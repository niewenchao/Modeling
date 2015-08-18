#ifndef _VCONTROL_H_
#define _VCONTROL_H_
/**********************************************************************
DESCRIPTION: 用来管理矩阵 控制VNode的视图变换 

CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************/
#include "vmatrix.h"
#include "vpoint.h"
#include <vector>

using namespace std;

class VControl
{
public:
	VControl(){}
	~VControl(){}
private:
	VMatrix3 m_mat;		//存储姿态矩阵
public:
	void Move(VVector3& move);//移动
	void Rotate(VAxisAngle& AxisAng);//旋转
	void Scale(VVector3& scale);//缩放
	void SetTM(VMatrix3& tm);  //设置矩阵
	void SetTM(VMatrix3* tm);  //设置矩阵
	VMatrix3 GetTM();//获取矩阵
	void CopyMat(VMatrix3& newMat);	//拷贝矩阵
};
#endif