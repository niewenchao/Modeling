/**********************************************************************
DESCRIPTION: 定义网格结构 

CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************/
#ifndef _VMESH_H_
#define _VMESH_H_
#include "vpoint.h"
#include "vmatrix.h"
#include "vface.h"
#include "glut.h"
#include "vrender.h"
//////////////////////////////////////////////////////////////////////////
//mesh显示方式
#define MESH_NONE				0x0000
#define MESH_SOLID				0x0001
#define MESH_POINT				0x0002
#define MESH_POINT_SOLID		0x0003
#define MESH_LINE				0x0004
#define MESH_LINE_SOLID			0x0005
#define MESH_POINT_LINE			0x0006
#define MESH_POINT_LINE_SOLID	0x0007
																								
class VMesh
{
public:
	VMesh();																					//默认构造函数
	VMesh(const VMesh& fromMesh);																//拷贝构造函数
	~VMesh();																					//析构函数

private:
	static VPoint3 m_PointColor;															//mesh在点显示状态下的颜色
	static VPoint3 m_LineColor;																//mesh在线显示状态下的颜色
	int m_iShowMode;																			//显示方式
	bool m_bSelect;																				//是否被选择
public:
	int m_iNumVerts;																			//顶点数目
	int m_iNumFaces;																			//面片数目
	VPoint3 *m_pVerts;																			//顶点数组
	VPoint3 *m_pVertColors;																		//顶点颜色数组
	VFace *m_pFaces;																			//面片数组
public:
	VBoundBox m_bBox;//包围盒
	
public:
	static VPoint3& GetPointColor() { return m_PointColor; }										//返回显示颜色
	static void SetPointColor(VPoint3& newColor) { m_PointColor = newColor; }					//设置显示颜色
	static VPoint3& GetLineColor() { return m_LineColor; }										//返回显示颜色
	static void SetLineColor(VPoint3& newColor) { m_LineColor = newColor; }						//设置显示颜色
	int GetShowMode(){ return m_iShowMode; }                                             //返回显示方式
	void SetShowMode(int showMode){ m_iShowMode = showMode;}

public:

	//网络的绘制
	void Display(const VMatrix3& mat,bool flag);											//网格的绘制

	//初始化
	void InitMesh();																			//初始化网格
	
	//顶点相关方法
	inline int GetNumVerts(){ return m_iNumVerts; }												//返回定点数数目
	bool SetNumVerts(int num,bool keep = false);												//设置顶点数目
	bool CopyVerts(const VMesh& fromMesh);														//从源网格拷贝顶点数组
	inline VPoint3& GetVert(int index){ return m_pVerts[index]; }								//返回指定索引的顶点
	inline VPoint3* GetVertPtr(int index){ return &(m_pVerts[index]); }							//以指针形式返回指定索引的顶点
	inline void SetVert(int index, const VPoint3& xyz){ m_pVerts[index].SetXYZ(xyz); }			//设置指定索引顶点的坐标
	inline void SetVert(int index,float x,float y,float z){ m_pVerts[index].SetXYZ(x,y,z); }	//这只指定索引顶点的坐标
	void FreeVerts();																			//释放顶点数组
	

	//顶点颜色相关方法
	bool SetNumVertColors(int num);																//设置颜色顶点数目
	bool CopyVertColors(const VMesh& fromMesh);													//从源网格拷贝顶点数组
	inline VPoint3& GetVertCol(int index){ return m_pVertColors[index]; }							//返回指定索引的顶点
	inline VPoint3* GetVertColPtr(int index){ return &(m_pVertColors[index]); }					//以指针形式返回指定索引的顶点
	inline void SetVertColor(int index, const VPoint3& xyz){ m_pVertColors[index].SetXYZ(xyz); }		//设置指定索引顶点的坐标
	inline void SetVertColor(int index,float x,float y,float z){ m_pVertColors[index].SetXYZ(x,y,z); }	//这只指定索引顶点的坐标
	inline void SetDefColor();																	//
	void SetAllToColor(float x,float y,float z);
	void FreeVertColors();																		//释放顶点数组

	//面片相关方法
	inline int GetNumFaces(){ return m_iNumFaces; }												//返回面片数目
	bool SetNumFaces(int num,bool keep = false);												//设置面片数目
	bool CopyFaces(const VMesh& fromMesh);														//从源网格拷贝面片
	VFace& GetFace(int fIndex){ return m_pFaces[fIndex]; }										//返回指定索引的面片
	VFace* GetFacePtr(int fIndex) { return &(m_pFaces[fIndex]); }								//返回指定面片的指针
	void SetFace(int fIndex, int v0, int v1, int v2){ m_pFaces[fIndex].SetVerts(v0,v1,v2); }	//设置指定面片的顶点索引
	void SetFace(int fIndex, int f_v[3]){ m_pFaces[fIndex].SetVerts(f_v); }						//设置指定面片的顶点索引
	void SetFace(int fIndex, VFace& f1){ m_pFaces[fIndex] = f1; }								//设置指定索引面片
	void SetFace_Normal_Verts(int fIndex, int x, int y, int z, int nx, int ny, int nz)
	{
		SetFace(fIndex,x, y,z);	
		m_pFaces[fIndex].index_normals[0] = nx;
		m_pFaces[fIndex].index_normals[1] = ny;
		m_pFaces[fIndex].index_normals[2] = nz;
	}
	void FreeFaces();																			//释放面片数组
	
	//操作符重载
	//!!等待验证，未验证
	VMesh& operator=(const VMesh& fromMesh);													//重载等于符号

	//TestPrint
	void PrintMesh(char* cFileName);

	//包围盒相关方法
	inline VBoundBox& GetBoundBox(){ return m_bBox; }											//返回包围盒
	void ComputeBoundBox();																		//计算包围盒

	//选择状态
	inline bool GetSelect(){ return m_bSelect; }												//返回当前选择状态
	inline void SetSelect(bool bSelect = true){ m_bSelect = bSelect; }							//设置当前选择状态
	inline void UnSelect(){ m_bSelect = false; }												//设置当前选择状态为非选择
	
};
//////////////////////////////////////////////////////////////////////////
#endif