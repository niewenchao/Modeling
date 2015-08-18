/**********************************************************************
DESCRIPTION: 矩阵相关操作，注意4维矩阵里起作用的只有12个元素，
因此可以用12元素数组存储4维矩阵
矩阵为3*4矩阵，进行矩阵操作的时候想成4维矩阵 M*X^T

CREATED BY:  [8/9/2015 niewenchao]
**********************************************************************/
#ifndef _VMATRIX_H_
#define _VMATRIX_H_
//////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <cmath>
#include "vaxisangle.h"
//////////////////////////////////////////////////////////////////////////
class VMatrix3														//VMatrix3为3×4的矩阵
{
public:
	VMatrix3();														//构造函数
	VMatrix3(float fVal);											//建立一个对角线为val的矩阵
	VMatrix3(const VMatrix3& mat2);									//拷贝构造函数
	~VMatrix3();													//析构函数
public:
	float m_fMat[12];												//用一维数组存储矩阵元素{(0,1,2,3);(3,4,5,6);(7,8,9,10)}

public:

	void SetValue(float* pMat);										//设置矩阵的元素值
	void SetValue(VMatrix3& mat2);									//根据源矩阵设置该矩阵的元素值
	void SetRowValue(int iRow, float* pRow);						//设置矩阵一行的值
	void SetColValue(int iCol, float* pCol);						//设置矩阵一列的值
	void SetValue(int i, int j, float fValue);						//设置矩阵元素的值
	void GetAllValue(float* pMat);									//返回矩阵所有元素
	void GetRowValue(int iRow, float* pRow);						//返回矩阵一行的元素值
	void GetColValue(int iCol, float* pCol);						//返回矩阵一列的元素值
	float GetValue(int i, int j);									//返回矩阵某一元素值
	float* operator[](int iRow);									//重载[]操作符
	float GetMatDet();												//返回该矩阵的行列式值
	bool GetInverseMat(VMatrix3& mat);								//返回该矩阵的逆矩阵
	void GetTransPoseMat(float* pMat) const;						//返回该矩阵的转置矩阵
	void GetTransMat(VMatrix3& tMat);								//得到该矩阵的平移矩阵			
	void GetRotateMat(VMatrix3& rMat);								//得到该矩阵的旋转矩阵，这里是R*S
	void GetScaleMat(VMatrix3& sMat);								//得到该矩阵的缩放矩阵，这里是R*S
	void GetTRSMat(VMatrix3& tMat,VMatrix3& rMat,VMatrix3& sMat);	//分解矩阵为平移、旋转和缩放矩阵

	void IdentifyTM();												//设置为单位阵
	void InverseTM();												//设置该矩阵为其逆矩阵
	VPoint3 TransPoint(VPoint3& p1);								//对点进行空间变换
	void SetTMForMove(VVector3& vMove);								//设置该矩阵为指定平移矩阵
	void SetTMForRotate(VAxisAngle& AxisAng);						//设置该矩阵为指定旋转矩阵
	void SetTMForScale(VVector3& vScale);							//设置该矩阵为指定缩放矩阵
	void MoveTM(VVector3& vec1);									//叠加平移矩阵
	void RotateTM(VAxisAngle& AxisAng);			//在给定坐标系上旋转变换矩阵
	void ScaleTM(VVector3& vScale);									//叠加缩放矩阵

	VMatrix3 operator +() const;									//重载正号+操作符
	VMatrix3 operator -() const;									//重载负号-操作符
	VMatrix3 operator *(float scl) const;							//重载乘号操作符*
	VMatrix3 operator /(float scl) const;							//重载除号操作符/
	VMatrix3 operator + (VMatrix3& mat2);							//重载加号+操作符
	VMatrix3 operator - (VMatrix3& mat2);							//重载减号-操作符
	VMatrix3 operator * (VMatrix3& mat2);							//重载乘号*操作符
	VMatrix3 operator / (VMatrix3& mat2);							//重载除号操作符
	VMatrix3& operator += (VMatrix3& mat2);						//重载+=
	VMatrix3& operator -= (VMatrix3& mat2);						//重载-=
	VMatrix3& operator *= (VMatrix3& mat2);						//重载*=
	VMatrix3& operator /= (VMatrix3& mat2);						//重载/=
	VMatrix3& operator *= (float scl);								//重载*=
	VMatrix3& operator /= (float scl);								//重载/=
	bool operator == (VMatrix3& mat2);								//重载等号==操作符
	VMatrix3& operator = (const VMatrix3& mat2);					//重载赋值=操作符

};


#endif