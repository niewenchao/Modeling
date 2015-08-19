#include "vmesh.h"

VPoint3 VMesh::m_PointColor(1.0,1.0,1.0);									//初始化默认的点显示方式时的点颜色
VPoint3 VMesh::m_LineColor(1.0,1.0,1.0);									//初始化默认的线显示方式的线颜色

/*********************************************************************************
  *Function:  VMesh()
  *Description： 默认构造函数
  *Input:  无
  *Return: 无 
               *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
VMesh::VMesh()
{
	m_iNumVerts = m_iNumFaces = 0;	//顶点、面片长度置0
	m_pVerts = NULL;															//顶点数组置空
	m_pVertColors = NULL;															//顶点颜色数组置空
	m_pFaces = NULL;															//面片数组置空
	m_iShowMode = MESH_LINE;													//默认以线框方式显示
	m_bSelect = false;                                                          //默认为非选择
}

/*********************************************************************************
  *Function:  VMesh(const VMesh& fromMesh)
  *Description： 拷贝构造函数
  *Input:  原网格
  *Return: 无 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
VMesh::VMesh(const VMesh& fromMesh)
{
	CopyVerts(fromMesh);														//拷贝顶点
	CopyVertColors(fromMesh);														//拷贝顶点颜色
	CopyFaces(fromMesh);														//拷贝面片
}

VMesh::~VMesh()
{
	if(m_pVerts)																//如果顶点数组存在
		delete[] m_pVerts;														//删除顶点数组
	if (m_pVertColors)															//如果顶点颜色数组存在
		delete[] m_pVertColors;													//删除顶点颜色数组
	if(m_pFaces)																//如果面片数组存在
		delete[] m_pFaces;														//删除面片数组
	
}

/*********************************************************************************
  *Function: Display(const VMatrix3& mat,bool flag) 
  *Description：绘制网格 
  *Input:  mat-网格姿态矩阵
  *Return: 无 
              *CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************************/
void VMesh::Display(const VMatrix3& mat,bool flag)
{
	VRender* render = VRender::GetSingleton();
	int showMod = GetShowMode();
	render->SetTransform(mat);//设置变换矩阵
	if (flag)
	{
		render->DrawBoundBox(m_bBox);
	}
	
	//////////////////////////////////////////////////////////////////////////
		switch (showMod)														//网格的显示方式
		{
		case MESH_POINT:														//点显示
			render->DrawPoints(m_iNumVerts,m_pVerts,m_pVertColors);
			break;
		case MESH_LINE:															//线显示
			render->DrawLines(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors,true);
			break;
		case MESH_SOLID:														//实体面显示，用三角形，默认填充
			render->DrawTriangles(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors);
			break;
		case MESH_POINT_LINE:													//点线混合显示
			render->DrawPoints(m_iNumVerts,m_pVerts,m_pVertColors);
			render->DrawLines(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors);
			break;
		case MESH_POINT_SOLID:													//点面混合显示
			render->DrawPoints(m_iNumVerts,m_pVerts,m_pVertColors);
			render->DrawTriangles(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors);
			break;
		case MESH_LINE_SOLID:													//线面混合显示
			render->DrawLines(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors,true);
			render->DrawTriangles(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors);
			break;
		case MESH_POINT_LINE_SOLID:													//点线面混合显示
			render->DrawPoints(m_iNumVerts,m_pVerts,m_pVertColors);
			render->DrawLines(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors,true);
			render->DrawTriangles(m_iNumFaces,m_pFaces,m_pVerts,m_pVertColors);
			break;
		}
	//////////////////////////////////////////////////////////////////////////
	render->RemoveTransform(mat);
								

}
/*********************************************************************************
  *Function: InitMesh() 
  *Description： 初始化网格
  *Input:  无
  *Return: 无 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/

void VMesh::InitMesh()
{
	m_iNumVerts = m_iNumFaces = 0;		//顶点、面片长度置0
	if(m_pVerts)																//旧顶点数组存在
	{
		delete[] m_pVerts;														//删除旧顶点数组
		m_pVerts = NULL;														//顶点数组置空
	}
	if(m_pFaces)																//旧面片数组存在
	{
		delete[] m_pFaces;														//删除旧面片数组
		m_pFaces = NULL;														//面片数组置空
	}
	
}

/*********************************************************************************
  *Function:  SetNumVerts(int num,bool keep //= false )
  *Description： 设置顶点个数,并重置顶点颜色数组
  *Input:  num-顶点个数，keep-是否保持元数组数据
  *Return: 设置成功返回true，失败返回false 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
bool VMesh::SetNumVerts(int num,bool keep /* = false */)
{
	if(num <= 0)																//如果数组长度小于或等于0
	{
		m_iNumVerts = 0;														//数组长度置0
		if(m_pVerts)															//如果旧数组存在
		{
			delete[] m_pVerts;													//删除旧数组
			m_pVerts = NULL;													//数组置空
		}
		if (m_pVertColors)
		{
			delete[] m_pVertColors;
			m_pVertColors = NULL;
		}
		return true;
	}

	if(num == m_iNumVerts)														//如果数组长度相同
	{
		return true;															//不做任何操作返回
	}
	int originNum = m_iNumVerts;
	m_iNumVerts = num;
	if (!keep)																	//如果不需要保持原数据
	{
		if(m_pVerts)	delete[] m_pVerts;										//删除旧数组
		m_pVerts = new VPoint3[m_iNumVerts];									//建立启用新数组
		if(!m_pVerts)	{m_iNumVerts = 0; m_pVerts = NULL;return false;}		//内存分配失败
		FreeVertColors();																//删除旧数组
		m_pVertColors = new VPoint3[m_iNumVerts];										//建立启用新数组
		if(!m_pVertColors)	{ m_pVertColors = NULL;return false;}						//内存分配失败
		SetDefColor();                                                            //所有顶点设置为默认颜色
	}
	else																		//如果需要保持原数据
	{
		int MinNum = originNum;													//记录新旧数组中长度较小值
		if(MinNum > m_iNumVerts)	MinNum = m_iNumVerts;						//新旧数组长度中的较小值
		VPoint3 *pNewVerts = new VPoint3[m_iNumVerts];							//建立新数组
		if(!pNewVerts)	{m_iNumVerts = originNum; return false;}				//内存分配失败
		for (int i = 0; i < MinNum; i++)										//复制旧数组数据
		{
			pNewVerts[i] = m_pVerts[i];
		}
		delete[] m_pVerts;														//删除旧数组
		m_pVerts = pNewVerts;													//启用新数组
	}									//重新建立顶点标记位数组
	return true;
}

/*********************************************************************************
  *Function: CopyVerts(const VMesh& fromMesh) 
  *Description： 从源网格中拷贝顶点
  *Input: fromeMesh-源网格
  *Return: 拷贝成功返回true，错误返回false 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
bool VMesh::CopyVerts(const VMesh& fromMesh)
{
	if(m_pVerts)																//如果原顶点数组存在
	{
		if(m_iNumVerts != fromMesh.m_iNumVerts)									//如果当前数组长度和复制源数组长度不相同
		{
			this->m_iNumVerts = fromMesh.m_iNumVerts;							//复制源顶点数目
			delete[] m_pVerts;													//删除旧数组
			m_pVerts = NULL;
			if(m_iNumVerts != 0)
			{
				m_pVerts = new VPoint3[m_iNumVerts];							//建立新数组			
				if(!m_pVerts) return false;										//内存分配失败
				memcpy(m_pVerts,fromMesh.m_pVerts,m_iNumVerts*sizeof(m_pVerts[0]));	//内存拷贝
			}
		}
		else
		{
			memcpy(m_pVerts,fromMesh.m_pVerts,m_iNumVerts*sizeof(m_pVerts[0]));	//如数组长度相同仅拷贝内容即可
		}
	}
	else																		//如数组不存在
	{
		if(fromMesh.m_iNumVerts > 0)											//如果源网格数组存在
		{
			this->m_iNumVerts = fromMesh.m_iNumVerts;							//拷贝源网格顶点数目
			m_pVerts = new VPoint3[m_iNumVerts];								//建立新数组
			if(!m_pVerts)	return false;										//内存分配失败			
			memcpy(m_pVerts,fromMesh.m_pVerts,m_iNumVerts*sizeof(m_pVerts[0]));	//内存拷贝
		}
	}
	return true;
}

/*********************************************************************************
  *Function: FreeVerts() 
  *Description： 释放顶点数组
  *Input:  无
  *Return: 无 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
void VMesh::FreeVerts()
{
	if(m_pVerts)																//如果存在顶点数组
		delete[] m_pVerts;														//释放顶点数组
	m_pVerts = NULL;															//顶点数组指针置空
	m_iNumVerts = 0;															//顶点个数置0
}




/*********************************************************************************
  *Function: CopyVertColors(const VMesh& fromMesh) 
  *Description： 从源网格中拷贝顶点颜色数组
  *Input: fromeMesh-源网格
  *Return: 拷贝成功返回true，错误返回false 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
bool VMesh::CopyVertColors(const VMesh& fromMesh)
{
	if(m_pVertColors)																//如果原顶点颜色数组存在
	{
		if(m_iNumVerts != fromMesh.m_iNumVerts)									//如果当前数组长度和复制源数组长度不相同
		{
			delete[] m_pVertColors;												//删除旧数组
			m_pVertColors = NULL;
			if(m_iNumVerts != 0)												//源网格面片数组存在
			{
				m_pVertColors = new VPoint3[m_iNumVerts];							//建立新数组	
				if(!m_pVertColors) return false;									//内存分配失败
				memcpy(m_pVertColors,fromMesh.m_pVertColors,
					m_iNumVerts*sizeof(m_pVertColors[0]));							//内存拷贝
			}
		}
		else																	//如数组长度相同，仅拷贝内存数据即可
		{
			memcpy(m_pVertColors,fromMesh.m_pVertColors,
				m_iNumVerts*sizeof(m_pVertColors[0]));								//拷贝内存数据
		}
	}
	else																		//若该网格顶点颜色数组不存在
	{
		if(fromMesh.m_iNumVerts > 0)											//若源网格顶点颜色数组存在
		{
			m_pVertColors = new VPoint3[m_iNumVerts];								//建立新数组
			if(!m_pVertColors)	return false;									//内存分配失败
			memcpy(m_pVertColors,fromMesh.m_pVertColors,
				m_iNumVerts*sizeof(m_pVertColors[0]));							//内存拷贝
		}
	}
	return true;
}
/*********************************************************************************
  *Function:SetDefColor()  
  *Description： 设置顶点默认颜色
  *Input:  无
  *Return: 无 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
void VMesh::SetDefColor()
{
	if(m_pVertColors)																//如果存在顶点颜色数组
	{
		for (int i=0;i<m_iNumVerts;i++)
			SetVertColor(i,m_PointColor);										//依次设置顶点颜色为默认颜色
	}
}
/*********************************************************************************
  *Function: SetAllToColor(float x,float y,float z) 
  *Description： 设置多有顶点为该颜色
  *Input:  RGB
  *Return: 无 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
void VMesh::SetAllToColor(float x,float y,float z)
{
	if(m_pVertColors)																//如果存在顶点颜色数组
	{
		VPoint3 color(x,y,z);
		for (int i=0;i<m_iNumVerts;i++)
			SetVertColor(i,color);											//依次设置顶点颜色为默认颜色
	}
}
/*********************************************************************************
  *Function: FreeVertColors() 
  *Description：释放顶点颜色数组 
  *Input:  无
  *Return: 无 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
void VMesh::FreeVertColors()
{
	if(m_pVertColors)																//如果存在顶点颜色数组
		delete[] m_pVertColors;													//释放顶点颜色数组
	m_pVertColors = NULL;															//顶点颜色数组指针置空
}

/*********************************************************************************
  *Function: SetNumFaces(int num,bool keep / = false /) 
  *Description：设置面片数组个数 
  *Input:  num-面片个数，keep-是否保持原始数据
  *Return: 无 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
bool VMesh::SetNumFaces(int num,bool keep /* = false */)
{
	if(num <= 0)																//如果数组长度小于或等于0
	{
		m_iNumFaces = 0;														//数组长度置0
		if(m_pFaces)															//如果旧数组存在
		{
			delete[] m_pFaces;													//删除旧数组
			m_pFaces = NULL;													//数组置空
		}
		return true;
	}

	if(num == m_iNumFaces)	return true;										//如果数组长度相同，不需要动作

	int originNum = m_iNumFaces;
	m_iNumFaces = num;
	if (!keep)																	//如果不需要保持原数据
	{
		if(m_pFaces)	delete[] m_pFaces;										//删除旧数组
		m_pFaces = new VFace[m_iNumFaces];										//建立启用新数组
		if(!m_pFaces)	{m_iNumFaces = 0; m_pFaces = NULL;return false;}		//内存分配失败
	}
	else																		//如果需要保持原数据
	{
		int MinNum = originNum;													//记录新旧数组中长度较小值
		if(MinNum > m_iNumFaces)	MinNum = m_iNumFaces;						//新旧数组长度中的较小值
		VFace *pNewFaces = new VFace[m_iNumFaces];								//建立新数组
		if(!pNewFaces)	{m_iNumFaces = originNum; return false;}				//内存分配失败
		for (int i = 0; i < MinNum; i++)										//拷贝就数组中数据
		{
			pNewFaces[i] = m_pFaces[i];
		}
		delete[] m_pFaces;														//删除旧的面片数组
		m_pFaces = pNewFaces;													//启用新的面片数组
	}
	return true;
}

/*********************************************************************************
  *Function:  CopyFaces(const VMesh& fromMesh)
  *Description： 从源网格拷贝面片数据
  *Input:  fromMesh-源网格
  *Return: 数据拷贝成功返回true，失败返回false 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
bool VMesh::CopyFaces(const VMesh& fromMesh)
{
	if(m_pFaces)																//如果原面片数组存在
	{
		if(m_iNumFaces != fromMesh.m_iNumFaces)									//如果当前数组长度和复制源数组长度不相同
		{
			this->m_iNumFaces = fromMesh.m_iNumFaces;							//复制源网格面片数目
			delete[] m_pFaces;													//删除旧数组
			m_pFaces = NULL;
			if(m_iNumFaces != 0)												//源网格面片数组存在
			{
				m_pFaces = new VFace[m_iNumFaces];								//建立新数组	
				if(!m_pFaces) return false;										//内存分配失败
				memcpy(m_pFaces,fromMesh.m_pFaces,m_iNumFaces*sizeof(m_pFaces[0]));	//内存拷贝
			}
		}
		else																	//如数组长度相同，仅拷贝内存数据即可
		{
			memcpy(m_pFaces,fromMesh.m_pFaces,m_iNumFaces*sizeof(m_pFaces[0]));	//拷贝内存数据
		}
	}
	else																		//若该网格面片数组不存在
	{
		if(fromMesh.m_iNumFaces > 0)											//若源网格面片数组存在
		{
			this->m_iNumFaces = fromMesh.m_iNumFaces;							//拷贝源网格面片数目
			m_pFaces = new VFace[m_iNumFaces];									//建立新数组
			if(!m_pFaces)	return false;										//内存分配失败
			memcpy(m_pFaces,fromMesh.m_pFaces,m_iNumFaces*sizeof(m_pFaces[0]));	//内存拷贝
		}
	}
	return true;
}

/*********************************************************************************
  *Function:  FreeFaces()
  *Description： 释放面片数组
  *Input:  无
  *Return: 无 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
void VMesh::FreeFaces()
{
	if(m_pFaces)																//如果存在面片数组
		delete[] m_pFaces;														//释放面片数组
	m_pFaces = NULL;															//面片数组指针置空
	m_iNumFaces = 0;															//面片个数置0
}



/*********************************************************************************
  *Function:  operator=(const VMesh& fromMesh)
  *Description： 重载操作符operator =
  *Input:  fromMesh-源网格
  *Return: 拷贝后的网格 
              *CREATED BY:  [7/30/2015 niewenchao]
**********************************************************************************/
VMesh& VMesh::operator=(const VMesh& fromMesh)
{
	CopyVerts(fromMesh);														//拷贝顶点
	CopyFaces(fromMesh);														//拷贝面片
	CopyVertColors(fromMesh);
	return (*this);
}



void VMesh::PrintMesh(char* cFileName)
{
	FILE* fp = fopen(cFileName,"wt");
	fprintf(fp,"Verts:\n");
	for (int i = 0; i < m_iNumVerts; i++)
	{
		fprintf(fp,"%d-(%f,%f,%f)\n",i,m_pVerts[i].x,m_pVerts[i].y,m_pVerts[i].z);
	}
	fprintf(fp,"Faces:\n");
	for (int i = 0; i < m_iNumFaces; i++)
	{
		fprintf(fp,"%d-(%d,%d,%d)\n",i,m_pFaces[i].vert[0],m_pFaces[i].vert[1],m_pFaces[i].vert[2]);
	}
	fclose(fp);
}
//////////////////////////////////////////////////////////////////////////
//包围盒相关方法
/*********************************************************************************
  *Function: ComputeBoundBox() 
  *Description： 计算包围盒
  *Input:  无
  *Return: 无 
              *CREATED BY:  [8/7/2015 niewenchao]
**********************************************************************************/
void VMesh::ComputeBoundBox()
{
	if(m_iNumVerts <= 0)
	{
		m_bBox.InitBoundBox();
		return;
	}
	m_bBox.m_Pmin = m_pVerts[0];
	m_bBox.m_Pmax = m_pVerts[0];
	for (int i = 1; i < m_iNumVerts; i++)										//遍历所有顶点，建立包围盒
	{
		if(m_bBox.m_Pmin.x > m_pVerts[i].x)								//找出最小的x坐标值
			m_bBox.m_Pmin.x = m_pVerts[i].x;
		if(m_bBox.m_Pmin.y > m_pVerts[i].y)								//找出最小的y坐标值
			m_bBox.m_Pmin.y = m_pVerts[i].y;
		if(m_bBox.m_Pmin.z > m_pVerts[i].z)								//找出最小的z坐标值
			m_bBox.m_Pmin.z = m_pVerts[i].z;
		if(m_bBox.m_Pmax.x < m_pVerts[i].x)								//找出最大的x坐标值
			m_bBox.m_Pmax.x = m_pVerts[i].x;
		if(m_bBox.m_Pmax.y < m_pVerts[i].y)								//找出最大的y坐标值
			m_bBox.m_Pmax.y = m_pVerts[i].y;
		if(m_bBox.m_Pmax.z < m_pVerts[i].z)								//找出最大的z坐标值
			m_bBox.m_Pmax.z = m_pVerts[i].z;
	}
}