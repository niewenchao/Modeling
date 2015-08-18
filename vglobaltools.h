/**********************************************************************
DESCRIPTION: 定义一些不适合放在类里面的常用的工具 

CREATED BY:  [8/2/2015 niewenchao]
**********************************************************************/
#ifndef _VGLOBALTOOLS_H_
#define _VGLOBALTOOLS_H_

#include "vpoint.h"
#include <math.h>
#include <string>
using namespace std;

//VPoint2类相关,可参看class VPoint2,包含文件VPoint.h
inline float GetFLength(const VPoint2& p1);				//求一个二维点到原点的距离
float GetFLength(VPoint3& p1, VPoint3& p2);				//求两个二维点之间的距离
inline float GetFLenSquared(const VPoint2& p1);			//求一个二维点到原点距离的平方
float GetFLenSquared(VPoint3& p1, VPoint3& p2);
VPoint2 FNormalize(const VPoint2& p1);
inline float FDotProd(const VPoint2& p1,const VPoint2& p2);//点积
float GetFCosA(VVector2& vec1, VVector2& vec2);//叉积

//VPoint3类相关,可参看class VPoint3,包含文件VPoint.h
inline float GetFLength(const VPoint3& p1);
float GetFLength(VPoint3& p1, VPoint3& p2);
inline float GetFLenSquared(const VPoint3& p1);
float GetFLenSquared(VPoint3& p1, VPoint3& p2);
VPoint3 FNormalize(const VPoint3& p1);
inline float FDotProd(const VPoint3& p1,const VPoint3& p2);
VPoint3 FCrossProd(const VPoint3& p1,const VPoint3& p2);
float GetFCosA(VVector3& vec1,VVector3& vec2);
float GetFArea(VPoint3& p1,VPoint3& p2,VPoint3& p3);	//求三个点组成的三角形的面积
VPoint3 GetFGravityCenter(VPoint3& p1,VPoint3& p2,VPoint3& p3);	//求三个点组成的三角形的重心

void string_replace(string & strBig, const string & strsrc, const string &strdst);
#endif
