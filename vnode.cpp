#include "vnode.h"

VNode* VNode::m_rootnode = new VNode;								//初始化场景根结点
VNode::VNode()//构造函数
{
	strcpy(m_NodeName,"VNode");
	m_parentnode=NULL;											//初始父结点为场景结点
	m_displayFlag=true; //true设置节点为可见
	m_vChildList.clear();
	m_pMesh=NULL;
	m_matCtrler = new VControl;
}

VNode::~VNode()//析构函数
{
	m_vChildList.clear();
	if (m_matCtrler)
		delete m_matCtrler;
	if (m_pMesh)
		delete m_pMesh;
}


char* VNode::GetName()  //获得节点名称
{
	return m_NodeName;
}
void VNode::SetNodeName(char *s)  //设置节点名称
{

	strcpy(m_NodeName,s);
}
int VNode::IsRootNode()//判断是否是根节点
{
	return(this==m_rootnode);

}

VMatrix3 VNode::GetNodeTM()  //获得节点矩阵
{
	if(this==m_rootnode) return VMatrix3();
	VMatrix3 mat;
	mat = m_matCtrler->GetTM();
	return m_parentnode->GetNodeTM()*mat;

}

// VMatrix3 VNode::GetNodeTMPtr(VTimeValue t)  //获得节点矩阵
// {
// 	return m_matCtrler->GetTM(t);
// }

void VNode::SetNodeTM(VMatrix3& tm)
{
	if(this == m_rootnode)														//如果该结点即为根结点								
	{
			m_matCtrler->SetTM(VMatrix3());
	}
	else m_matCtrler->SetTM(tm);
}

void VNode::SetNodeTM(VMatrix3* tm)
{
	if(this == m_rootnode)														//如果该结点即为根结点								
	{
		m_matCtrler->SetTM(VMatrix3());
	}
	else m_matCtrler->SetTM(tm);

	
}

void VNode::Move(VVector3& move)//移动
{

	if(this!=m_rootnode)
		m_matCtrler->Move(-move);




}
void VNode::Rotate(VAxisAngle& val)//旋转
{
	if(this!=m_rootnode)
		m_matCtrler->Rotate(val);

	

}
void VNode::Scale(VVector3& scale)//缩放
{
	if(this!=m_rootnode)
		m_matCtrler->Scale(scale);

	
}


VMatrix3 VNode::GetParentTM()//获得父节点的矩阵
{

	if(this==m_rootnode)
		return this->GetNodeTM();
	else return m_parentnode->GetNodeTM();
}
VNode* VNode::GetChildNode(int i)//获得第i个子节点
{
	if(m_vChildList.size()<0||i<0)
		return NULL;
	return m_vChildList[i];

}
VNode* VNode::GetRootNode()
{
	if (m_rootnode == NULL)
	{
		m_rootnode = new VNode;
	}
	return m_rootnode;
}

void VNode::DestroyRootNode()
{
	if (m_rootnode)
		delete m_rootnode;
	m_rootnode = NULL;
}

VNodeVector& VNode::GetChildList()	//获得孩子节点树引用 
{
	return m_vChildList;
}

void VNode::Delete()//删除节点
{
	VNodeVector nodelist;
	GetSubTree(this,nodelist);
	int num=nodelist.size();
	for(int i=0;i<num;i++)
	{
		delete nodelist[i]; //直接删除节点？？？
	}
	nodelist.clear();
	m_vChildList.clear();
}
void VNode::DeleteThis(bool subtree)  //删除节点（子树）
{

	if(this==m_rootnode) //如果是根节点，不予删除
		return ;
	this->Detach();//先脱离父子关系
	if(subtree)  //删除整个子树
	{

		Delete();
		

	}
	else
	{
		int i,numchild=m_vChildList.size();
		for(i=0;i<numchild;i++)
		{
			m_parentnode->AttachChild(m_vChildList[i]);

		}
		delete this;
		


	}

}
void VNode::GetSubTree(VNode* node,VNodeVector& nodevector) //获取node节点的子树，保存在nodevector中

{  
	nodevector.push_back(node);
	int num=node->m_vChildList.size();
	for(int i=0;i<num;i++)
	{
		GetSubTree(node->GetChildNode(i),nodevector);
	}
}
int VNode::GetChildIndex(VNode* pchild)//返回子节点pchild在子节点数组中的索引
{
	int numChild=m_vChildList.size();
	for(int i=0;i<numChild;i++)
	{
		if(m_vChildList[i]==pchild)
			return i;

	}
	return -1;

}
void VNode::RemoveChild(VNode* pchild) //将pchild的父子关系去掉
{

	int index=GetChildIndex(pchild);
	if(index==-1)
		return;
	m_vChildList.erase(m_vChildList.begin()+index);//从子节点列表中移除
	pchild->m_parentnode=NULL;//置空父节点
}

void VNode::Detach()//分离父子关系
{
	if(m_parentnode)
		RemoveChild(this);
	
}

void VNode::AttachChild(VNode* node)//添加子节点,node为要添加的子节点
{
	node->Detach(); 
	m_vChildList.push_back(node);//node添加到子节点列表
	node->m_parentnode=this; //设置node的父节点
	

}

void VNode::Display(bool flag)
{
	return m_pMesh->Display(GetNodeTM(),flag);
}

VMesh* VNode::GetMesh()
{
	return m_pMesh;													//返回结点悬挂物体的指针
}

VMesh* VNode::SetMesh(VMesh* mesh)
{
	VMesh* tempMesh = m_pMesh;
	m_pMesh = mesh;												
	return tempMesh;
}



