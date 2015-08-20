#ifndef _VIMPORT_H_
#define _VIMPORT_H_
/**********************************************************************
DESCRIPTION:用来读取VCC三角网格，所有的网格与一个VNode绑定并挂载在VScene类中  

CREATED BY:  [8/17/2015 niewenchao]
**********************************************************************/
///////////////////////////////////////////////
#include <cstdio>
#include <string>
#include <iostream>
#include "vmesh.h"
#include "vscene.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
using std::string;
class VImport
{
public:
	VImport(void) {};
	~VImport(void) {};
	//单例模式
	static VImport* GetInstance()
	{ 
		if (m_pImport == NULL) 
			m_pImport = new VImport();
		return m_pImport;
	}
	 bool DoImport(string fileName);//导入
	 bool OnImportMesh(FILE* fp);												//导入Mesh
	 bool OnReadOnePart(FILE* fp);
	 void OnImportVertex(FILE* fp,VMesh* mesh);									//导入顶点数据
	 void OnImportFace(FILE* fp,VMesh* mesh,bool nExist = true,bool tExist = true);									//导入面片数据
	 void OnImportNormal(FILE* fp,VMesh* mesh);									//导入顶点法线数据
	 void OnImportTVert(FILE* fp,VMesh* mesh);									//导入纹理顶点数据
protected:
	
private:
	VScene* m_pScence;
	static VImport* m_pImport;
};







///////////////////////////////////////////////
#endif