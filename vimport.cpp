#include "vimport.h"
#include "vmatrix.h"
VImport* VImport::m_pImport = NULL;
/*********************************************************************************
  *Function:DoImport(string fileName)  
  *Description：导入VCC模型文件，目前支持仅含有网格数据的VCC模型，材质、光照、骨骼动作数据待加入 
  *Input:  fileName-模型文件路径
  *Return: 导入成功返回true 否则false 
              *CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************************/
bool VImport::DoImport(string fileName)
{
	string ext = fileName.substr(fileName.rfind('.')+1);
	if (ext.compare("VCC") || ext.compare("vcc"))
	{
		FILE* fp = fopen(fileName.c_str(), "r+");
		if (NULL == fp) return false;
		char buf[512];
		//	#Head------------->#HeadEnd
		bool bone_exist = false;
		bool skin_exist = false;
		bool mesh_exist = false;
		bool mtl_exist =false;
		while(fscanf(fp,"%[^\n]\n",buf))
		{
			if(0 == strcmp(buf, "#HeadEnd"))
			{
				break;
			}
			switch(buf[0])
			{
			case 'b':bone_exist = true;break;
			case 's':skin_exist = true;break;
			case 'm':mesh_exist = true;break;
			case 't':mtl_exist = true;break;
			}
			
	    }
		// #Mesh----------------->#MeshEnd
		if(mesh_exist) 
			return  OnImportMesh(fp);
	}
	else
	{
		return true;
	}
}
/*********************************************************************************
  *Function:OnImportMesh(FILE* fp)  
  *Description：导入VCC模型网格部分，一个模型网格部分里可能存在多个网格part 
  *Input:  fp-打开的文件指针
  *Return: 导入成功返回true 否则false  
              *CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************************/
bool VImport::OnImportMesh(FILE* fp)
{
	char buf[512];

	// 判断文件指针是否正确
	fscanf(fp,"%[^\n]\n",buf);
	if(0 != strcmp(buf, "#Mesh"))
	{
		return false;
	}


	while(fscanf(fp,"%s",buf) != EOF && strcmp(buf,"#MeshEnd") != 0 )
	{	
		if (strcmp(buf,"#Part") == 0)
		{
			fseek(fp,-5L,SEEK_CUR);
			OnReadOnePart(fp);
		}
		else
		{
			fscanf(fp,"%[^\n]\n",buf);
		}
	}
	fscanf(fp,"\n");
	if(0 != strcmp(buf, "#MeshEnd"))
	{
		return false;
	}
	else
	{
		return true;
	}
}
/*********************************************************************************
  *Function: OnReadOnePart(FILE* fp) 
  *Description： 导入网格模型中的一个part，并挂载到场景结构中
  *Input:  fp-文件指针
  *Return: 成功true 否则false 
              *CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************************/
bool VImport::OnReadOnePart(FILE* fp)
{
	char buf[512];
	fscanf(fp,"#Part\n");

	fscanf(fp,"n %s\n",buf);									//	mesh的名称
	VMesh* m_mesh = new VMesh();
	VNode* node = m_pScence->CreateNode(m_mesh);
	node->SetNodeName(buf);
	float mat[12];
	fscanf(fp,"m %f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",			//读取对象矩阵
		&mat[0],&mat[1],&mat[2],&mat[3],&mat[4],&mat[5],&mat[6],
		&mat[7],&mat[8],&mat[9],&mat[10],&mat[11]);
	VMatrix3* pmat = new VMatrix3;
	pmat->SetValue(mat);
	node->GetTMController()->SetTM(pmat);
	// 问题，忽略最后一个字符行
	fscanf(fp,"t %s\n",buf);
	

	bool nExist=false;
	bool tExist=false;
	while(fscanf(fp,"%s",buf) != EOF && strcmp(buf,"#PartEnd") != 0) {
		switch(buf[0]){
		case 'v':
			fseek(fp,-1L,SEEK_CUR);
			OnImportVertex(fp,m_mesh);	//导入顶点数据	
			break;
		case 'n':
			nExist = true;
			fseek(fp,-1L,SEEK_CUR);
			OnImportNormal(fp,m_mesh);	//导入法线数据
			break;
		case 't':
			tExist = true;
			fseek(fp,-1L,SEEK_CUR);
			OnImportTVert(fp,m_mesh);		//导入纹理顶点数据
			break;
		case 'f':
			fseek(fp,-1L,SEEK_CUR);
			OnImportFace(fp,m_mesh,nExist,tExist);		//导入面片数据
			break;
		}
	}
	fscanf(fp,"\n");
	m_mesh->ComputeBoundBox();
	return true;
}
/*********************************************************************************
  *Function: OnImportVertex(FILE* fp,VMesh* m_mesh) 
  *Description： 导入网格顶点到VMesh中
  *Input:  fp-文件指针，m_mesh VMesh对象指针
  *Return: 无 
              *CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************************/
void VImport::OnImportVertex(FILE* fp,VMesh* m_mesh){			//导入顶点数据
	int vNum = 0;
	fscanf(fp,"v %d\n",&vNum);									//读取网格顶点数目
	m_mesh->SetNumVerts(vNum);										//设置网格顶点数目
	float x = 0.0f,y=0.0f,z=0.0f;
	for (int i=0;i<vNum;i++)
	{
		fscanf(fp,"%f,%f,%f\n",&x,&y,&z);						//依次读取顶点坐标
		m_mesh->SetVert(i,x,y,z);									//设置顶点坐标
	}
}
//导入面片
void VImport::OnImportFace(FILE* fp,VMesh* m_mesh,bool nExist /* = true */,bool tExist /* = true */){
	int fNum = 0;
	fscanf(fp,"f %d\n",&fNum);									//读取网格面片数目
	m_mesh->SetNumFaces(fNum);										//设置网格面片数目

	if (nExist&&tExist)
	{
		int x = 0, y = 0, z = 0;
		int nx = 0, ny = 0, nz = 0;
		int tx = 0, ty = 0, tz = 0;
		for (int i=0;i<fNum;i++)
		{
			fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &x, &nx, &tx, &y, &ny, &ty, &z, &nz, &tz);
			//mesh.SetFace_Normal_Verts(i, x, y, z, nx, ny, nz);
			//mesh.SetTVFace(i, tx, ty, tz);
			m_mesh->SetFace(i, x, y, z);
		}
	}
	else if (nExist&&!tExist)
	{
		int x = 0, y = 0, z = 0;
		int nx = 0, ny = 0, nz = 0;
		for (int i=0;i<fNum;i++)
		{
			fscanf(fp, "%d/%d %d/%d %d/%d\n", &x, &nx, &y, &ny, &z, &nz);
			m_mesh->SetFace(i, x, y, z);
			//mesh.SetFace_Normal_Verts(i, x, y, z, nx, ny, nz);
		}
	}
	else if (!nExist&&tExist)
	{
		int x = 0, y = 0, z = 0;
		int tx = 0, ty = 0, tz = 0;
		for (int i=0;i<fNum;i++)
		{
			fscanf(fp, "%d/%d %d/%d %d/%d\n", &x, &tx, &y,&ty, &z, &tz);
			m_mesh->SetFace(i, x, y, z);
			//mesh.SetTVFace(i, tx, ty, tz);
		}
	}
	else
	{
		int x = 0, y = 0, z = 0;
		for (int i=0;i<fNum;i++)
		{
			fscanf(fp, "%d %d %d\n", &x,&y,&z);
			m_mesh->SetFace(i, x, y, z);
		}
	}

}
//导入法线
void VImport::OnImportNormal(FILE* fp,VMesh* m_mesh){			//导入顶点数据
	int vNum = 0;
	fscanf(fp,"n %d\n",&vNum);									//读取网格法线数目
	//mesh.SetNumNormals(vNum);
	float x = 0.0f,y=0.0f,z=0.0f;
	for (int i=0;i<vNum;i++)
	{
		fscanf(fp,"%f,%f,%f\n",&x,&y,&z);						//依次读取顶点法线坐标
		//mesh.SetNormal(i,x,y,z);									//设置顶点法线坐标
	}
}
//导入纹理顶点
void VImport::OnImportTVert(FILE* fp,VMesh* m_mesh){			//导入顶点数据
	int tvNum = 0;
	fscanf(fp,"t %d\n",&tvNum);								//读取网格纹理顶点数目
	//mesh.SetNumTVerts(tvNum);									//设置网格纹理顶点数目
	float x = 0.0f,y=0.0f,z=0.0f;
	for (int i=0;i<tvNum;i++)
	{
		fscanf(fp,"%f,%f,%f\n",&x,&y,&z);						//依次读取纹理顶点坐标
		//mesh.SetTVert(i,x,y,z);									//设置纹理顶点坐标
	}
}