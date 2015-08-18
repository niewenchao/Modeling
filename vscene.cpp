//#include "stdafx.h"
#include "vscene.h"
#include <gl/GL.h>
#include <gl/glu.h>
#include "vcamera.h"
VScene* VScene::m_pScence = NULL;

VScene::VScene()
{
	m_pRootNode = VNode::GetRootNode();											//根结点指针
	m_pNodeSel = VNodeSelector::GetInstance();									//结点选择器指针
}

VScene::~VScene()
{
	DeleteAllNodes();
}

//////////////////////////////////////////

VScene* VScene::GetInstance() //返回场景实例
{
	if(!m_pScence)																//如果场景实例还未创建
	{ m_pScence = new VScene; }													//创建场景实例
	return m_pScence;															//返回场景实例指针
}

void VScene::DestroyInstance() //释放场景实例
{
	if(m_pScence)
		delete m_pScence;
	m_pScence = NULL;
}


VNode* VScene::CreateNode()//创建一个新的结点
{
	VNode* node= new VNode;													//创建一个新结点
	if(node)																	//创建成功
		VNode::GetRootNode()->AttachChild(node);									//默认悬挂至场景根结点下
	return node;																//返回结点指针
}


VNode* VScene::CreateNode(VMesh* pMesh)//创建一个新的场景结点悬挂物体	
{
	VNode* node = new VNode;													//创建一个新结点
	if(node)																	//创建成功
		VNode::GetRootNode()->AttachChild(node);									//默认悬挂至场景根结点下
	node->SetMesh(pMesh);													//将物体挂接到新结点下
	return node;																//返回结点指针
}


VNode* VScene::CreateNode(VNode* attachNode)									//创建一个新的场景结点悬挂物体	
{
	VNode* node = new VNode;													//创建一个新结点
	if(node)																	//创建成功
		attachNode->AttachChild(node);
	return node;																//返回结点指针
}

VNode* VScene::CreateNode(VMesh* pMesh,VNode* attachNode)				//创建一个新的场景结点悬挂物体	
{
	VNode* node = new VNode;													//创建一个新结点
	if(node)																	//创建成功
		attachNode->AttachChild(node);									
	node->SetMesh(pMesh);		
	return node;																//返回结点指针
}
void VScene::ReadAllNodes(VNodeVector& vNodesVec)//读取场景中的所有结点并存入指定列表
{
	int numChild = m_pRootNode->GetChildList().size();							//读取根结点子树个数
	for (int i = 0; i < numChild; i++)											//对于根结点的每个子结点
	{
		ReadSubTree(m_pRootNode->GetChildNode(i),vNodesVec);					//读取每一颗子树
	}
}


void VScene::ReadSubTree(VNode* pNode,VNodeVector& vNodeVec)					//读取一颗子树
{
	vNodeVec.push_back(pNode);													//当前结点如列表
	int numChild = pNode->GetChildList().size();										//子结点个数
	for (int i = 0; i < numChild; i++)											//遍历每个子结点
	{
		ReadSubTree(pNode->GetChildNode(i),vNodeVec);							//读取子树
	}
}


void VScene::DeleteNode(VNode* pNode, bool dSubTree /* = false */)
{
	pNode->DeleteThis(dSubTree);												//删除该结点（dSubTree标志是否删除此子树）
}


void VScene::DeleteAllNodes()                                             //删除场景中所有的结点
{
	for(int i=0;i<m_pRootNode->GetNumChild();i++)
	{
		m_pRootNode->GetChildNode(i)->Delete();
	}
}
int VScene::GetNumSel()
{
	return m_pNodeSel->GetNumSelNodes();										//返回选择器列表中结点的个数
}


VNode* VScene::GetSelNode(int i)
{
	return m_pNodeSel->GetSelNode(i);											//选择器中第i个结点
}


void VScene::SelectNode(VNode* pNode, bool bClearSel /* = true */)//选择该结点，并标志是否清除以前的结点指针	
{
	m_pNodeSel->AppendSelNode(pNode, bClearSel);								//选择该结点
}
void VScene::DeleteSelNodes()  //删除所有被选择的结点
{
	VNodeVector vNodeList;
	m_pNodeSel->GetSelNodeTab(vNodeList);										//获取结点选择器中所有结点指针
	m_pNodeSel->Clear();														//清空结点选择器
	int numSel = vNodeList.size();												//原选择器中被选择结点的个数
	for (int i = 0; i < numSel; i++)											//遍历每个被选择的结点
	{
		vNodeList[i]->DeleteThis();												//删除该结点
	}
}

void VScene::ClearScence()                                                  //清空场景
{
	m_pNodeSel->Clear();													//清空选择器
	DeleteAllNodes();														//删除所有场景结点
	VNode::DestroyRootNode();
	VScene::DestroyInstance();
}


void VScene::Render()                                             //渲染整个场景
{
	//渲染场景，遍历场景结点树
	// 	int numChild = m_pRootNode->GetChildList().size();									//根结点的孩子结点个数，（场景根结点并不悬挂任何物体，不需要渲染）
	// 	for (int i = 0; i < numChild; i++)											//对于根结点的每个子结点
	// 	{
	// 		VNode* node = m_pRootNode->GetChildNode(i);
	// 		RenderNode(m_pRootNode->GetChildNode(i),t);								//渲染该子树
	// 	}
	VNodeVector nodeVec;
	ReadAllNodes(nodeVec);
	for (int i=0;i<nodeVec.size();i++)
	{
		VNode* node = nodeVec.at(i);
		RenderNode(node);									
	}
}

//////////////////////////////////////////
//函数：	RenderNode(DNode* pNode)	//
//功能：	渲染指定结点及其孩子结点	//
//CREATED BY:  [8/9/2015 niewenchao]
//////////////////////////////////////////
void VScene::RenderNode(VNode* pNode)
{
	if(!pNode) return;
	bool exsited = false;
	if (GetNodeSelector()->IndexOf(pNode) >= 0)
		exsited = TRUE;
	pNode->Display(exsited);
}

/*********************************************************************************
  *Function: GetViewPortPt(DPoint3& p0)	 
  *Description：将opengl世界坐标转换为屏幕坐标（视口坐标） 
  *Input:  p0-opengl世界坐标
  *Return: 屏幕坐标 
              *CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************************/
VPoint3 VScene::GetViewPortPt(VPoint3& p0)
{
	VPoint3 p1;

	GLint    viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	glGetIntegerv(GL_VIEWPORT, viewport);											//视口矩阵
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);									//模型变换矩阵
	glGetDoublev(GL_PROJECTION_MATRIX, projection);									//投影矩阵
	GLdouble px, py, pz;
	gluProject(p0.x, p0.y, p0.z, modelview, projection, viewport, &px, &py, &pz);	//投影
	py = viewport[3] - py;															//校正纵坐标
	p1.SetXYZ(px, py, pz);															//投影后的点
	/**/
	return p1;																		//返回投影后的点坐标
}

/*********************************************************************************
  *Function: GetGLPortPt(VPoint3& p0) 
  *Description：将屏幕坐标转化为opengl世界坐标 
  *Input:  p0-屏幕坐标
  *Return: opengl世界坐标 
              *CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************************/
VPoint3 VScene::GetGLPortPt(VPoint3& p0)
{
	VPoint3 p1;

	GLint    viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	glGetIntegerv(GL_VIEWPORT, viewport);											//视口矩阵
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);									//模型变换矩阵
	glGetDoublev(GL_PROJECTION_MATRIX, projection);									//投影矩阵
	GLdouble px, py, pz;
	p0.y= viewport[3] - p0.y;	                                                    //校正纵坐标
	gluUnProject(p0.x, p0.y, p0.z, modelview, projection, viewport, &px, &py, &pz);	//反投影	
	p1.SetXYZ(px, py, pz);															//反投影后的点

	return p1;																		//返回反投影后的点坐标
}



/*********************************************************************************
  *Function: GetTransPt(VPoint3 p_start,VPoint3 p_end,VPoint3 centerPt)  
  *Description：获取移动物体的移动向量 
  *Input:  p_start,p_end屏幕上鼠标移动的两个点，centerPt：模型的屏幕中心坐标
  *Return: opengl世界坐标的移动向量 
              *CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************************/
VPoint3 VScene::GetTransPt(VPoint3 p_start,VPoint3 p_end,VPoint3 centerPt)	//获得平移向量
{
	VPoint3 transEnd(float(p_end.x),float(p_end.y),centerPt.z);//屏幕点平移和缩放为物体点
	transEnd = GetGLPortPt(transEnd);
	VPoint3 transStart(float(p_start.x),float(p_start.y),centerPt.z);
	transStart = GetGLPortPt(transStart);	

	VPoint3 transMove; 
	transMove.SetXYZ((transEnd.x-transStart.x),(transEnd.y-transStart.y),(transEnd.z-transStart.z));//获得平移向量

	return transMove;
}
/*********************************************************************************
  *Function: GetRotatePt(VPoint3 startPt,VPoint3 endPt,VPoint3 CenterPt) 
  *Description：获取移动物体的移动向量 
  *Input:  p_start,p_end屏幕上鼠标移动的两个点，centerPt：模型的屏幕中心坐标
  *Return: opengl世界坐标的旋转向量 
              *CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************************/
VPoint3 VScene::GetRotatePt(VPoint3 p_start,VPoint3 p_end,VPoint3 centerPt)
{
	VPoint3 transREnd(-float(p_end.y),float(p_end.x),centerPt.z);
	transREnd = GetGLPortPt(transREnd);
	VPoint3 transRStart(-float(p_start.y),float(p_start.x),centerPt.z);
	transRStart = GetGLPortPt(transRStart);
	VPoint3 transRotate;
	transRotate.SetXYZ(5*(transRStart.x-transREnd.x),(transRStart.y-transREnd.y),(transRStart.z-transREnd.z));

	return transRotate;
}
//获取缩放向量
VPoint3 VScene::GetScalePt(VPoint3 p_start,VPoint3 p_end)
{
	float k=1+6.0f*(p_end.y-p_start.y)/512.0;//设置物体旋转向量
	VPoint3 transScale(k,k,k);

	return transScale;
}
/*********************************************************************************
  *Function: Hit(int x, int y) 
  *Description： 通过包围盒的比较从场景中拾取模型，拾取到的模型保存到vnodeselector
  *Input:  x,y点击屏幕坐标
  *Return: 无 
              *CREATED BY:  [8/10/2015 niewenchao]
**********************************************************************************/
void VScene::Hit(int x, int y)
{
	m_pNodeSel->Clear();														//清空选择器
	VNodeVector vNodeList;														//定义一个结点指针数组
	ReadAllNodes(vNodeList);													//获取场景中所有结点指针
	int i, j, numNodes = vNodeList.size();										//场景中结点的个数
	VBoundBox* pBB;																//包围盒指针
	VMatrix3 mat;																//结点矩阵
	VPoint3 p[9];
	VPoint3 world;
	for (i = 0; i < numNodes; i++)												//遍历每个结点
	{
		VNode* node = vNodeList[i];
		if(vNodeList[i]->GetDisplayFlag() == false)	continue;					//如果处于隐藏状态忽略
		pBB = &(vNodeList[i]->GetMesh()->GetBoundBox());									//返回结点物体的包围盒
		mat = vNodeList[i]->GetNodeTM();										//返回结点的矩阵
		if(pBB)																	//如果包围盒存在
		{
			p[0] = pBB->m_Pmin;													//8个角点
			p[1] = pBB->m_Pmax;
			p[2].SetXYZ(p[0].x, p[1].y, p[0].z);
			p[3].SetXYZ(p[0].x, p[1].y, p[1].z);
			p[4].SetXYZ(p[0].x, p[0].y, p[1].z);
			p[5].SetXYZ(p[1].x, p[0].y, p[0].z);
			p[6].SetXYZ(p[1].x, p[1].y, p[0].z);
			p[7].SetXYZ(p[1].x, p[0].y, p[1].z);
			for (j = 0; j < 8; j++)												//遍历每个角点
			{
				p[j] = mat.TransPoint(p[j]);									//经过结点转换后的点
				p[j] = GetViewPortPt(p[j]);										//转换为视口坐标
			}
			p[8].SetXYZ(p[0]);
			for (j = 1; j < 8; j++)												//对于转换后的每个角点，记录其最高点和最低点
			{
				if(p[j].x < p[0].x)	p[0].x = p[j].x;
				if(p[j].x > p[8].x)	p[8].x = p[j].x;
				if(p[j].y < p[0].y) p[0].y = p[j].y;
				if(p[j].y > p[8].y) p[8].y = p[j].y;
			}
			
			
			/*VPoint3 temp;
			temp = GetGLPortPt(VPoint3(x,y,0));*/
			
			//if((temp.x > p[0].x) && (temp.x < p[8].x) && (temp.y > p[0].y) && (temp.y < p[8].y))	//如果当前点落入包围盒关联区域
			if((x > p[0].x) && (x < p[8].x) && (y > p[0].y) && (y < p[8].y))
			{
				this->SelectNode(vNodeList[i]);									//选择该模型
				vNodeList.clear();												//清空列表
				return;															//返回
			}
		}  
	}
	vNodeList.clear();															//清空列表
}