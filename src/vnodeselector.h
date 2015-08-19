
/**********************************************************************
DESCRIPTION: 节点选择器 管理被选中的模型 

CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************/
#ifndef _VNODESELECTOR_H_
#define _VNODESELECTOR_H_
#include "vnode.h"
class VNodeSelector
{
private:
	VNodeSelector(){};//构造函数
	~VNodeSelector();
private:
	static VNodeSelector* m_pNodeSelector;//结点选择类指针
	VNodeVector m_vSelList;//被选择的结点列表
public:
	static VNodeSelector* GetInstance();//获取结点选择器类的唯一实例
	static void DestoryInstance();//销毁实例
	void Clear();//清空选择器的内容
	int GetNumSelNodes(){return m_vSelList.size();}//返回被选择的结点的数目
	VNode* GetSelNode(int i);//返回第i个结点指针
	void GetSelNodeTab(VNodeVector& vNodeList);//取得结点列表中所有的结点指针
	int IndexOf(VNode* pNode);											//查看指定结点是否已经在选择器中
	void AppendSelNode(VNode* pNode, bool bClearSel = true);			//将指定结点加入选择器
	void AppendSelNodeTab(VNodeVector& vSelList, bool bClearSel);		//将指定结点表中的所有结点加入选择器
	bool DeleteSelNode(VNode* pNode);									//取消该结点的选择状态，即从选择器中移除

};
#endif