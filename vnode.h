
#ifndef _VNODE_H_
#define _VNODE_H_
/**********************************************************************
DESCRIPTION:场景关键结构，VNode是一个多叉树结构，里面挂载着网格，网格的姿态等信息  

CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************/
#include "vcontrol.h"
#include "vmesh.h"

class VNode;
typedef vector<VNode*> VNodeVector;//定义个vnode型的vector存放子节点
typedef VNode VCamNode;
class VNode
{
public:
	VNode();
	~VNode();
public:
	//NODE Naming
	char * GetName();//获得节点名称
	void SetNodeName(char *s);//设置节点名称为s

	//父子节点相关操作
	VNode* GetParentNode(){return m_parentnode;} //返回父节点 
	static VNode* GetRootNode();
	static void DestroyRootNode();
	VMatrix3 GetParentTM();//获得父节点的矩阵
	VNodeVector& GetChildList();	//获得孩子节点树引用 
	VNode* GetChildNode(int i);//获取子节点
	void AttachChild(VNode* node);//增加子节点
	void Detach();//将该节点与其父节点分离
	int GetChildIndex(VNode* pchild);//获得子节点的索引
	void RemoveChild(VNode* pchild);//移除子节点
	void GetSubTree(VNode* node,VNodeVector& nodevector);//获得node节点的子树，存储在nodevector中
	int GetNumChild(){return m_vChildList.size();}

	void Delete();//删除节点
	void DeleteThis(bool subtree=false);//删除节点，如果subtree为tree，则将子树一起删除，否则只删除该节点
	int IsRootNode();//判断是否是根节点
	//控制器
	void SetTMController(VControl* m3cont){m_matCtrler = m3cont;}//设置控制器
	VControl* GetTMController(){
		if (!m_matCtrler)
			m_matCtrler = new VControl;
		return m_matCtrler;
	}//获取控制器

	//Transformation Matrices
	VMatrix3 GetNodeTM();//获得节点矩阵
	void SetNodeTM(VMatrix3& tm);//设置节点矩阵
	void SetNodeTM(VMatrix3* tm);//设置节点矩阵指针

	//按轴tmAxis移动节点或者几何体
	void Move(VVector3& move);//移动
	void Rotate(VAxisAngle& val);//旋转
	void Scale(VVector3& scale);//缩放
	//Display
	void Display(bool flag); //是否被选中 选中渲染包围盒
	//object相关方法
	VMesh* GetMesh();											//返回关联物体指针
	VMesh* SetMesh(VMesh* mesh);								//设置关联物体,返回原来的Object指针
public:
	//Node Selection
	void SetSelect() { m_select = true;}//设置选择
	bool GetSelect() { return m_select;}//返回选择状态
	void UnSelect(){ m_select=false;}//撤销选择状态

	//显示属性
	void Hide();//隐藏
	int IsHidden();//是否被隐藏
	void SetDisplayFlag(bool show){m_displayFlag = show;}
	int GetDisplayFlag(){return m_displayFlag;}
private:
	static VNode* m_rootnode;  //根节点
	VNode* m_parentnode; //父节点
	VNodeVector m_vChildList;//存储子节点的vector
	VControl* m_matCtrler;//控制器
	VMesh* m_pMesh;//节点下挂的物体
	bool m_select;//选择属性
	bool m_displayFlag; //显示属性

private:
	char m_NodeName[256];//存放节点名称

};
#endif




