
#include "vnodeselector.h"
VNodeSelector* VNodeSelector::m_pNodeSelector=NULL;
VNodeSelector::~VNodeSelector()
{

	m_pNodeSelector->Clear();
}
VNodeSelector* VNodeSelector::GetInstance()  //获取实例
{
  if(m_pNodeSelector==NULL)
	  m_pNodeSelector=new VNodeSelector;
  return m_pNodeSelector;

}
void VNodeSelector::DestoryInstance()//销毁实例
{

	if(m_pNodeSelector)
		delete m_pNodeSelector;
}
void VNodeSelector::Clear()//清空结点选择器
{
	int num=m_vSelList.size();
	for(int i=0;i<num;i++)
	{
		m_vSelList[i]->UnSelect();
	}
	m_vSelList.clear();
}
int VNodeSelector::IndexOf(VNode* pNode)  //返回结点在结点选择器中的索引
{
	int numNodes = GetNumSelNodes();											//选择器中结点的个数
	for (int i = 0; i < numNodes; i++)											//对于选择器中的每个结点
	{
		if(m_vSelList[i] == pNode)												//如果与给定结点指针相同
			return i;															//返回索引
	}
	return -1;																	//不存在该指针返回-1
}


VNode* VNodeSelector::GetSelNode(int i) //获取第i个结点指针
{
	if (i >= 0 && i < m_vSelList.size())
	{
		return m_vSelList[i];
	}
	return NULL;
}

void VNodeSelector::GetSelNodeTab(VNodeVector& vNodeList) //取得结点列表中所有的结点指针
{
	vNodeList.clear();															//清除该结点指针容器
	int numSel = m_vSelList.size();												//结点选择器中结点指针的个数
	for (int i = 0; i < numSel; i++)											//遍历选择器中所有结点指针
	{
		vNodeList.push_back(m_vSelList[i]);										//将该结点存入结点指针容器
	}
}


void VNodeSelector::AppendSelNode(VNode* pNode, bool bClearSel /* = true */)//添加一个结点指针
{
	if(bClearSel)																//如果需要清除结点选择器中原有的结点指针
	{
		Clear();																//清除结点选择器中内容
		m_vSelList.push_back(pNode);											//加入该结点指针
		pNode->SetSelect();														//设置其选择状态
	}
	else
	{
		if(IndexOf(pNode) == -1)												//如果结点选择器中没有此结点指针
		{
			m_vSelList.push_back(pNode);										//则将结点指针加入列表中
			pNode->SetSelect();													//设置其选择状态
		}
	}
}

void VNodeSelector::AppendSelNodeTab(VNodeVector& vSelList, bool bClearSel /* = true */)//指定结点列表中的所有结点加入选择器
{
	int i, numSel = vSelList.size();											//要加入结点的个数
	if(bClearSel)																//如果需要清除结点选择器中内容
	{
		Clear();																//首先清除结点选择器中内容
		for (i = 0; i < numSel; i++)
		{
			vSelList[i]->SetSelect();											//设置结点的选择状态
			m_vSelList.push_back(vSelList[i]);									//将该结点加入至结点选择器
		}
	}
	else
	{
		int index = 0;
		for (i = 0; i < numSel; i++)
		{
			index = IndexOf(vSelList[i]);										//首先检查该结点是否已存在于结点选择器中
			if(index != -1)														//如果该结点不存在于结点选择器
			{
				vSelList[i]->SetSelect();										//设置结点的选择状态
				m_vSelList.push_back(vSelList[i]);								//将该结点加入至结点选择器
			}
		}
	}
}

bool VNodeSelector::DeleteSelNode(VNode* pNode)//删除指定的结点指针
{
	int index = IndexOf(pNode);													//该结点在选择器中的索引
	if(index != -1)																//如果选择器中存在该结点
	{
		m_vSelList[index]->UnSelect();											//先取消该结点的选择状态
		m_vSelList.erase(m_vSelList.begin() + index);							//然后从选择器中移除该结点指针
		return true;															//从选择器中移除结点成功
	}
	return false;																//选择器中不存在该结点
}

