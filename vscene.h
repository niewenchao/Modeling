#ifndef _VSCENE_H_
#define _VSCENE_H_

/**********************************************************************
DESCRIPTION:场景类定义 管理VNode节点  

CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************/

#include "vnode.h"
#include "vnodeselector.h"
#include <fstream>


class VScene
{
private:
	VScene();														//私有以禁止在类外创建实例
public:
	~VScene();

private:
	static VScene* m_pScence;										//场景实例指针(唯一)
	VNode* m_pRootNode;												//场景根结点
	VNodeSelector* m_pNodeSel;										//结点选择器指针
	
public:
	static VScene* GetInstance();									//获取场景唯一的实例
	static void DestroyInstance();									//释放场景实例
	
	//结点相关方法
	VNode* CreateNode();											//创建一个新结点
	VNode* CreateNode(VMesh* pMesh);							//为物体创建一个结点
	VNode* CreateNode(VNode* attachNode);							//创建一个新结点挂到attachNode下
	VNode* CreateNode(VMesh* pMesh,VNode* attachNode);			//为物体创建一个结点挂到attachNode下
	void ReadAllNodes(VNodeVector& vNodesVec);						//读取场景内所有结点并将指针存入列表
	void ReadSubTree(VNode* pNode,VNodeVector& vNodeVec);			//读取一颗子树的所有结点
	void DeleteNode(VNode* pNode, bool dSubTree = false);			//删除指定结点
	void DeleteAllNodes();											//删除所有结点
	void ClearScence();												//清空场景

	//选择节点相关方法
	int GetNumSel();												//返回当前选择器列表中结点的个数
	VNode* GetSelNode(int i);										//返回当前选择的第i个结点
	void SelectNode(VNode* pNode, bool bClearSel = true);			//选择当前结点
	void DeleteSelNodes();											//删除选定结点
	////摄像机相关方法
	//void RenderCamera(VNode* camNode);								//启用指定摄像机
	//VCamNode* GetCurCamera();										//获得当前正在使用的摄像机节点指针
	//void JudgeScene();									//调整视点


	//场景中物体信息相关方法
	int GetNumVerts();												//得到场景中所有的物体顶点总数
	int GetNumFaces();												//得到场景中所有物体的面片总数
	void GetNumVerts(VNode* pNode, int& numVerts);					//得到以pNode为根结点的子树顶点总数
	void GetNumFaces(VNode* pNode, int& numFaces);					//得到以pNode为根结点的子树面片总数
	void GetNumVertsFaces(int& numVerts, int& numFaces);			//得到场景中所有物体的顶点和面片总数
	void GetNumVertsFaces(VNode* pNode, int& numVerts, int& numFaces);//得到以pNode为根结点的子树顶点面片总数

	//渲染场景
	void Render();							//渲染场景
	void RenderNode(VNode* pNode);			//渲染指定结点及其孩子结点

	//点击测试
	void Hit(int x, int y);											//点击测试
public:
	inline VNode* GetRootNode(){ return m_pRootNode; }				//返回场景根结点
	inline VNodeSelector* GetNodeSelector(){ return m_pNodeSel; }	//返回结点选择器指针
	static VPoint3 GetViewPortPt(VPoint3& p0);								//返回GL点在视口中的位置
	static VPoint3 GetGLPortPt(VPoint3& p0);									//返回视口中的点在GL位置
	static VPoint3 GetTransPt(VPoint3 p_start,VPoint3 p_end,VPoint3 centerPt);//通过鼠标移动的两个点 和物体中心点得到物体移动平移向量
	static VPoint3 GetRotatePt(VPoint3 p_start,VPoint3 p_end,VPoint3 centerPt);//通过鼠标移动的两个点 和物体中心点得到物体旋转向量
	static VPoint3 GetScalePt(VPoint3 p_start,VPoint3 p_end);//通过鼠标移动的两个点得到物体缩放向量
};




#endif