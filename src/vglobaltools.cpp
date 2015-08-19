#include "vglobaltools.h"

//VPoint2类相关,可参看class VPoint2,包含文件VPoint.h
float GetFLength(const VPoint2& p1)
{	return sqrt(p1.x*p1.x + p1.y*p1.y);	}
float GetFLength(VPoint2& p1, VPoint2& p2)
{
	VPoint2 p3 = p1 - p2;
	return GetFLength(p3);
}
float GetFLenSquared(const VPoint2& p1)
{	return (p1.x*p1.x + p1.y*p1.y);	}
float GetFLenSquared(VPoint2& p1, VPoint2& p2)
{
	VPoint2 p3 = p1 - p2;
	return GetFLenSquared(p3);
}
VPoint2 FNormalize(const VPoint2& p1)
{
	VPoint2 p2;
	float len = GetFLength(p1);
	p2 = p1 / len;
	return p2;
}
float FDotProd(const VPoint2& p1,const VPoint2& p2)
{	return (p1.x * p2.x + p1.y * p2.y);	}

float GetFCosA(VVector2& vec1,VVector2& vec2)
{
	return FDotProd(vec1,vec2)/(GetFLength(vec1)*GetFLength(vec2));
}

//VPoint3类相关,可参看class VPoint3,包含文件VPoint3.h
float GetFLength(const VPoint3& p1)
{	return sqrt(p1.x*p1.x + p1.y*p1.y + p1.z*p1.z);	}
float GetFLength(VPoint3& p1, VPoint3& p2)
{
	VPoint3 p3 = p1 - p2;
	return GetFLength(p3);
}
float GetFLenSquared(const VPoint3& p1)
{	return (p1.x*p1.x + p1.y*p1.y + p1.z*p1.z);	}
float GetFLenSquared(VPoint3& p1, VPoint3& p2)
{
	VPoint3 p3 = p1 - p2;
	return GetFLenSquared(p3);
}
VPoint3 FNormalize(const VPoint3& p1)
{
	VPoint3 p2;
	float len = GetFLength(p1);
	p2 = p1 / len;
	return p2;
}
float FDotProd(const VPoint3& p1,const VPoint3& p2)
{	return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);	}
VPoint3 FCrossProd(const VPoint3& p1,const VPoint3& p2)
{
	VPoint3 p3;
	p3.x = p1.y * p2.z - p1.z * p2.y; 
	p3.y = p1.z * p2.x - p1.x * p2.z;
	p3.z = p1.x * p2.y - p1.y * p2.x; 
	return p3;
}
float GetFCosA(VVector3& vec1,VVector3& vec2)
{
	return FDotProd(vec1,vec2)/(GetFLength(vec1)*GetFLength(vec2));
}

float GetFArea(VPoint3& p1,VPoint3& p2,VPoint3& p3)			//求三个点组成的三角形的面积
{
	VVector3 v1 = p2 - p1;
	VVector3 v2 = p3 - p1;
	float cosa = GetFCosA(v1,v2);						//求夹角的余弦值
	float sina = sqrt(1.0 - cosa*cosa);					//求夹角的正弦值
	
	return GetFLength(p1,p2)*GetFLength(p1,p3)/sina;	//返回三角形的面积
}

VPoint3 GetFGravityCenter(VPoint3& p1,VPoint3& p2,VPoint3& p3){	//求三个点组成的三角形的重心
	VPoint3 gc(0.0,0.0,0.0);
	gc += p1 + p2 + p3;
	gc /= 3.0f;
	return gc;
}

void string_replace(string & strBig, const string & strsrc, const string &strdst)//子字符串替换
{
	string::size_type pos=0;
	string::size_type srclen=strsrc.size();
	string::size_type dstlen=strdst.size();
	while( (pos=strBig.find(strsrc, pos)) != string::npos)
	{
		strBig.replace(pos, srclen, strdst);
		pos += dstlen;
	}
}