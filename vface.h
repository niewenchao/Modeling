

/**********************************************************************
DESCRIPTION: 定义三角面片 

CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************/
#ifndef _VFACE_H_
#define _VFACE_H_
//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
//////////////////////////////////////////////////////////////////////////

class VFace{																		// 面的定义
public:
	VFace(){ //默认构造函数
		vert[0] = vert[1] = vert[2] = 0;
	}				
	VFace(const VFace& fromFace)													//拷贝构造函数
	{
		vert[0] = fromFace.vert[0];													//拷贝面顶点索引
		vert[1] = fromFace.vert[1];
		vert[2] = fromFace.vert[2];
	}
	~VFace(){}																		//析构函数

public:
	int vert[3];
	int index_normals[3];

public:

	//顶点信息及设置
	inline int GetVert(int i){return vert[i];}										//返回面片第i个顶点索引
	inline int GetNormal(int i){return index_normals[i];}							//返回面片第i个法线顶点索引
	inline int* GetAllVerts(){return vert;}											//返回面片所有顶点数组指针
	int GetVertIndex(int v0)														//返回顶点索引在该面片下的下标
	{
		for (int i = 0; i < 3; i++)													//对于每个面片顶点
		{
			if(vert[i] == v0)	return i;											//如果存在，返回该下标索引
		}
		return -1;																	//不存在返回-1
	}
	inline void SetVert(int index,int VertIndex){vert[index] = VertIndex;}			//设置面片顶点
	inline void SetVerts(int v0, int v1, int v2){vert[0] = v0; vert[1] = v1; vert[2] = v2;}	//设置所有面片所有顶点
	inline void SetVerts(int pVerts[3]){vert[0] = pVerts[0]; vert[1] = pVerts[1]; vert[2] = pVerts[2];}//设置面片所有顶点

	VFace& operator =(const VFace& fromFace)
	{
		vert[0] = fromFace.vert[0];													//拷贝面顶点索引
		vert[1] = fromFace.vert[1];
		vert[2] = fromFace.vert[2];
		
		index_normals[0] = fromFace.index_normals[0];
		index_normals[1] = fromFace.index_normals[1];
		index_normals[2] = fromFace.index_normals[2];
		return (*this);																//返回赋值后的面片
	}



};
//////////////////////////////////////////////////////////////////////////
#endif