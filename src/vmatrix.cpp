#include "vmatrix.h"

//////////////////////////////////////
//函数：	VMatrix3()				//
//功能：	默认构造函数，为单位阵	//
//参数：	无						//
//返回值：	无						//
//			by xcc	2013.12.5	//
//////////////////////////////////////
VMatrix3::VMatrix3()
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = 0.0f;
	}
	m_fMat[0] = m_fMat[5] = m_fMat[10] = 1.0f;
}

//////////////////////////////////////////////////
//函数：	VMatrix3(const VMatrix3& mat2)	//
//功能：	拷贝构造函数						//
//参数：	mat2-为源矩阵						//
//返回值：	无									//
//						by xcc	2013.12.5	//
//////////////////////////////////////////////////
VMatrix3::VMatrix3(const VMatrix3& mat2)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = mat2.m_fMat[i];
	}
}

//////////////////////////////////////////
//函数：	VMatrix3(float fVal)		//
//功能：	构造一个对角线为fVal的矩阵	//
//参数：	fVal-对角线值				//
//返回值：	无							//
//				by xcc	2013.12.5	//
//////////////////////////////////////////
VMatrix3::VMatrix3(float fVal)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = 0.0f;
	}
	m_fMat[0] = m_fMat[5] = m_fMat[10] = fVal;
}

//////////////////////////////
//函数：	~VMatrix3()	//
//功能：	析构函数		//
//参数：	无				//
//返回值：	无				//
//	by xcc	2013.12.5	//
//////////////////////////////
VMatrix3::~VMatrix3()
{
	//
}

//////////////////////////////////////////////
//函数：	SetValue(float* pMat)			//
//功能：	设置矩阵所有的元素值			//
//参数：	pMat-用以设置矩阵所有元素的数组	//
//			长度必须为12					//
//返回值：	无								//
//					by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::SetValue(float* pMat)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = pMat[i];
	}
}

//////////////////////////////////////////////
//函数：	SetValue(VMatrix3& mat2)		//
//功能：	根据源矩阵设置当前矩阵的值		//
//参数：	mat2-源矩阵						//
//返回值：	无								//
//					by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::SetValue(VMatrix3& mat2)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = mat2.m_fMat[i];
	}
}

//////////////////////////////////////////////////
//函数：	GetRowValue(int iRow, float* pRow)	//
//功能：	设置矩阵指定行的元素值				//
//参数：	iRow-行索引，pRow-用以设置该行的	//
//			元素值的数组，长度必须为4			//
//返回值：	无									//
//						by xcc	2013.12.5	//
//////////////////////////////////////////////////
void VMatrix3::SetRowValue(int iRow, float* pRow)
{
	for (int i = 0; i < 4; i++)
	{
		m_fMat[4 * iRow + i] = pRow[i];
	}
}

//////////////////////////////////////////////////
//函数：	SetColValue(int iCol, float* pCol)	//
//功能：	设置矩阵指定列的元素值				//
//参数：	iCol-列索引，pCol-用以设置该列的	//
//			元素值的数组，长度必须为3			//
//返回值：	无									//
//						by xcc	2013.12.5	//
//////////////////////////////////////////////////
void VMatrix3::SetColValue(int iCol, float* pCol)
{
	for (int i = 0; i < 3; i++)
	{
		m_fMat[i * 4 + iCol] = pCol[i];
	}
}

//////////////////////////////////////////////////////
//函数：	SetValue(int i, int j, float fValue)	//
//功能：	设置矩阵指定位置的元素值				//
//参数：	i,j-分别标志行列的索引，fValue-设置值	//
//返回值：	无										//
//							by xcc	2013.12.5	//
//////////////////////////////////////////////////////
void VMatrix3::SetValue(int i, int j, float fValue)
{
	m_fMat[4 * i + j] = fValue;
}

//////////////////////////////////////////////
//函数：	GetAllValue(float* pMat)		//
//功能：	返回矩阵所有的元素值			//
//参数：	pMat-用以存储矩阵所有元素的数组	//
//			长度必须为12					//
//返回值：	无								//
//					by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::GetAllValue(float* pMat)
{
	for (int i = 0; i < 12; i++)
	{
		pMat[i] = m_fMat[i];
	}
}

//////////////////////////////////////////////////
//函数：	GetRowValue(int iRow, float* pRow)	//
//功能：	返回矩阵指定行的元素值				//
//参数：	iRow-行索引，pRow-用以存储该行的	//
//			元素值的数组，长度必须为4			//
//返回值：	无									//
//						by xcc	2013.12.5	//
//////////////////////////////////////////////////
void VMatrix3::GetRowValue(int iRow, float* pRow)
{
	for (int i = 0; i < 4; i++)
	{
		pRow[i] = m_fMat[4 * iRow + i];
	}
}

//////////////////////////////////////////////////
//函数：	GetColValue(int iCol, float* pCol)	//
//功能：	返回矩阵指定列的元素值				//
//参数：	iCol-列索引，pCol-用以存储该列的	//
//			元素值的数组，长度必须为3			//
//返回值：	无									//
//						by xcc	2013.12.5	//
//////////////////////////////////////////////////
void VMatrix3::GetColValue(int iCol, float* pCol)
{
	for (int i = 0; i < 3; i++)
	{
		pCol[i] = m_fMat[i * 4 + iCol];
	}
}

//////////////////////////////////////////////
//函数：	GetValue(int i, int j)			//
//功能：	返回矩阵指定位置的元素值		//
//参数：	i,j-分别标志行列的索引			//
//返回值：	指定位置的元素值				//
//					by xcc	2013.12.5	//
//////////////////////////////////////////////
float VMatrix3::GetValue(int i, int j)
{
	return m_fMat[4 * i + j];
}

//////////////////////////////////////////////
//函数：	GetMatDet()						//
//功能：	返回该矩阵的行列式值			//
//参数：	无								//
//返回值：	无								//
//					by xcc	2013.12.5	//
//////////////////////////////////////////////
float VMatrix3::GetMatDet()
{
	return(m_fMat[0]*m_fMat[5]*m_fMat[10] + m_fMat[1]*m_fMat[6]*m_fMat[8] + m_fMat[2]*m_fMat[4]*m_fMat[9]
	- m_fMat[0]*m_fMat[6]*m_fMat[9] - m_fMat[1]*m_fMat[4]*m_fMat[10] - m_fMat[2]*m_fMat[5]*m_fMat[8]);
}

//////////////////////////////////////////////
//函数：	GetInverseMat(VMatrix3& mat)	//
//功能：	获取改变换矩阵的逆矩阵			//
//参数：	mat-用以存储逆矩阵值			//
//返回值：	存在逆矩阵则返回true，否则false.//
//					by xcc	2013.12.5	//
//////////////////////////////////////////////
bool VMatrix3::GetInverseMat(VMatrix3& mat)
{
	float fDet = GetMatDet();
	if(fDet == 0.0)	return false;
	mat.m_fMat[0] = (m_fMat[5] * m_fMat[10] - m_fMat[9] * m_fMat[6]) / fDet;
	mat.m_fMat[1] = -(m_fMat[1] * m_fMat[10] - m_fMat[9] * m_fMat[2]) / fDet;
	mat.m_fMat[2] = (m_fMat[1] * m_fMat[6] - m_fMat[5] * m_fMat[2]) / fDet;
	mat.m_fMat[3] = -(m_fMat[1] * m_fMat[6] * m_fMat[11] - m_fMat[1] * m_fMat[7] * m_fMat[10]
		- m_fMat[5] * m_fMat[2] * m_fMat[11] + m_fMat[5] * m_fMat[3] * m_fMat[10]
		+ m_fMat[9] * m_fMat[2] * m_fMat[7] - m_fMat[9] * m_fMat[3] * m_fMat[6]) / fDet;
	mat.m_fMat[4] = -(m_fMat[4] * m_fMat[10] - m_fMat[8] * m_fMat[6]) / fDet;
	mat.m_fMat[5] = (m_fMat[0] * m_fMat[10] - m_fMat[8] * m_fMat[2]) / fDet;
	mat.m_fMat[6] = -(m_fMat[0] * m_fMat[6] - m_fMat[4] * m_fMat[2]) / fDet;
	mat.m_fMat[7] = (m_fMat[0] * m_fMat[6] * m_fMat[11] - m_fMat[0] * m_fMat[7] * m_fMat[10]
		- m_fMat[4] * m_fMat[2] * m_fMat[11] + m_fMat[4] * m_fMat[3] * m_fMat[10]
		+ m_fMat[8] * m_fMat[2] * m_fMat[7] - m_fMat[8] * m_fMat[3] * m_fMat[6]) / fDet;
	mat.m_fMat[8] = (m_fMat[4] * m_fMat[9] - m_fMat[8] * m_fMat[5]) / fDet;
	mat.m_fMat[9] = -(m_fMat[0] * m_fMat[9] - m_fMat[8] * m_fMat[1]) / fDet;
	mat.m_fMat[10] = (m_fMat[0] * m_fMat[5] - m_fMat[4] * m_fMat[1]) / fDet;
	mat.m_fMat[11] = (-m_fMat[0] * m_fMat[5] * m_fMat[11] + m_fMat[0] * m_fMat[7] * m_fMat[9]
		+ m_fMat[4] * m_fMat[1] * m_fMat[11] - m_fMat[4] * m_fMat[3] * m_fMat[9]
		- m_fMat[8] * m_fMat[1] * m_fMat[7] + m_fMat[8] * m_fMat[3] * m_fMat[5]) / fDet;
	return true;
}

//////////////////////////////////////////////////
//函数：	GetTransPoseMat(float* pMat)		//
//功能：	获取矩阵的转置矩阵元素值			//
//参数：	pMat-用以存储该矩阵转置矩阵元素值的	//
//			数组，长度必须为16					//
//返回值：	无									//
//						by xcc	2013.12.5	//
//////////////////////////////////////////////////
void VMatrix3::GetTransPoseMat(float* pMat) const
{
	pMat[0] = m_fMat[0];
	pMat[1] = m_fMat[4];
	pMat[2] = m_fMat[8];
	pMat[3] = 0.0f;
	pMat[4] = m_fMat[1];
	pMat[5] = m_fMat[5];
	pMat[6] = m_fMat[9];
	pMat[7] = 0.0f;
	pMat[8] = m_fMat[2];
	pMat[9] = m_fMat[6];
	pMat[10] = m_fMat[10];
	pMat[11] = 0.0f;
	pMat[12] = m_fMat[3];
	pMat[13] = m_fMat[7];
	pMat[14] = m_fMat[11];
	pMat[15] = 1.0f;
}
void VMatrix3::GetTransMat(VMatrix3& tMat)								//得到该矩阵的平移矩阵
{
	tMat.IdentifyTM();
	tMat.m_fMat[3]=m_fMat[3]; //为平移矩阵赋值
	tMat.m_fMat[7]=m_fMat[7];
	tMat.m_fMat[11]=m_fMat[11];
}

void VMatrix3::GetRotateMat(VMatrix3& rMat)								//得到该矩阵的旋转矩阵
{
	rMat.IdentifyTM();
	VMatrix3 sMat;
	GetScaleMat(sMat);
	for(int j=0;j<11;j++)
	{
		if(j==0 || j==4 || j==8)
			rMat.m_fMat[j]=m_fMat[j]/sMat.m_fMat[0];
		else if(j==1 || j==5 ||j==9)
			rMat.m_fMat[j]=m_fMat[j]/sMat.m_fMat[5];
		else if(j==2 || j==6 ||j==10)
			rMat.m_fMat[j]=m_fMat[j]/sMat.m_fMat[10];
	}
}

void VMatrix3::GetScaleMat(VMatrix3& sMat)								//得到该矩阵的缩放矩阵
{
	sMat.IdentifyTM();
	sMat.m_fMat[0]=sqrt(m_fMat[0]*m_fMat[0]+m_fMat[4]*m_fMat[4]+m_fMat[8]*m_fMat[8]);
	sMat.m_fMat[5]=sqrt(m_fMat[1]*m_fMat[1]+m_fMat[5]*m_fMat[5]+m_fMat[9]*m_fMat[9]);
	sMat.m_fMat[10]=sqrt(m_fMat[2]*m_fMat[2]+m_fMat[6]*m_fMat[6]+m_fMat[10]*m_fMat[10]);
}

void VMatrix3::GetTRSMat(VMatrix3& tMat,VMatrix3& rMat,VMatrix3& sMat)								//得到该矩阵的旋转缩放平移矩阵
{
	tMat.IdentifyTM();
	tMat.m_fMat[3]=m_fMat[3]; //为平移矩阵赋值
	tMat.m_fMat[7]=m_fMat[7];
	tMat.m_fMat[11]=m_fMat[11];

	sMat.IdentifyTM();
	sMat.m_fMat[0]=sqrt(m_fMat[0]*m_fMat[0]+m_fMat[4]*m_fMat[4]+m_fMat[8]*m_fMat[8]);
	sMat.m_fMat[5]=sqrt(m_fMat[1]*m_fMat[1]+m_fMat[5]*m_fMat[5]+m_fMat[9]*m_fMat[9]);
	sMat.m_fMat[10]=sqrt(m_fMat[2]*m_fMat[2]+m_fMat[6]*m_fMat[6]+m_fMat[10]*m_fMat[10]);

	rMat.IdentifyTM();
	for(int j=0;j<11;j++)
	{
		if(j==0 || j==4 || j==8)
			rMat.m_fMat[j]=m_fMat[j]/rMat.m_fMat[0];
		else if(j==1 || j==5 ||j==9)
			rMat.m_fMat[j]=m_fMat[j]/rMat.m_fMat[5];
		else if(j==2 || j==6 ||j==10)
			rMat.m_fMat[j]=m_fMat[j]/rMat.m_fMat[10];
	}
}
//////////////////////////////////////
//函数：	IdentifyTM()			//
//功能：	将该矩阵设置为单位阵	//
//参数：	无						//
//返回值：	无						//
//			by xcc	2013.12.5	//
//////////////////////////////////////
void VMatrix3::IdentifyTM()
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = 0.0f;
	}
	m_fMat[0] = m_fMat[5] = m_fMat[10] = 1.0f;
}

//////////////////////////////////////
//函数：	InverseTM()				//
//功能：	将该矩阵设置为其逆矩阵	//
//参数：	无						//
//返回值：	无						//
//			by xcc	2013.12.5	//
//////////////////////////////////////
void VMatrix3::InverseTM()
{
	VMatrix3 tm1;
	GetInverseMat(tm1);
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = tm1.m_fMat[i];
	}
}

//////////////////////////////////////
//函数：	TransPoint(VPoint3& p1)	//
//功能：	对点进行空间变换		//
//参数：	p1-原空间点坐标			//
//返回值：	变换后的空间点坐标		//
//			by xcc	2013.12.5	//
//////////////////////////////////////
VPoint3 VMatrix3::TransPoint(VPoint3& p1)
{
	VPoint3 p2;
	p2.x = m_fMat[0]*p1.x + m_fMat[1]*p1.y + m_fMat[2]*p1.z + m_fMat[3];
	p2.y = m_fMat[4]*p1.x + m_fMat[5]*p1.y + m_fMat[6]*p1.z + m_fMat[7];
	p2.z = m_fMat[8]*p1.x + m_fMat[9]*p1.y + m_fMat[10]*p1.z + m_fMat[11];
	return p2;
}

//////////////////////////////////////////////
//函数：	SetTMForMove(VVector3& vMove)	//
//功能：	设置该矩阵为指定平移矩阵		//
//参数：	vMove-平移向量					//
//返回值：	无								//
//			by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::SetTMForMove(VVector3& vMove)
{
	IdentifyTM();
	m_fMat[3] = vMove.x;
	m_fMat[7] = vMove.y;
	m_fMat[11] = vMove.z;
}

/*********************************************************************************
  *Function:  SetTMForRotate(VAxisAngle& AxisAng)
  *Description： 通过旋转轴与旋转角得到该旋转矩阵
  *Input:  VAxisAngle指定旋转轴、旋转角
  *Output: 无
  *Return: 无 
  *CREATED BY:  [7/29/2015 niewenchao]
**********************************************************************************/
void VMatrix3::SetTMForRotate(VAxisAngle& AxisAng)
{
	/*
	IdentifyTM();
	DPoint3 axis;
	float fAngle, fSA, fCA, fX, fY, fZ;
	AxisAng.GetAxisAngle(axis, fAngle);
	fSA = sin(fAngle);
	fCA = cos(fAngle);
	fX = axis.x;
	fY = axis.y;
	fZ = axis.z;
	m_fMat[0] = fCA + (1 - fCA) * fX * fX;
	m_fMat[1] = (1 - fCA) * fX * fY - fSA * fZ;
	m_fMat[2] = (1 - fCA) * fX * fZ + fSA * fY;
	m_fMat[4] = (1 - fCA) * fX * fY + fSA * fZ;
	m_fMat[5] = fCA + (1 - fCA) * fY * fY;
	m_fMat[6] = (1 - fCA) * fY * fZ - fSA * fX;
	m_fMat[8] = (1 - fCA) * fX * fZ - fSA * fY;
	m_fMat[9] = (1 - fCA) * fY * fZ + fSA * fX;
	m_fMat[10] = fCA + (1 - fCA) * fZ * fZ;
	}


*/
	IdentifyTM();
	VPoint3 axis;
	float fAngle, fSA, fCA, fX, fY, fZ;
	AxisAng.GetAxisAngle(axis, fAngle);
	fSA = sin(fAngle);//输入值为弧度
	fCA = cos(fAngle);
	fX = axis.x;
	fY = axis.y;
	fZ = axis.z;
	m_fMat[0] = fCA + (1 - fCA) * fX * fX;
	m_fMat[1] = (1 - fCA) * fX * fY - fSA * fZ;
	m_fMat[2] = (1 - fCA) * fX * fZ + fSA * fY;
	m_fMat[4] = (1 - fCA) * fX * fY + fSA * fZ;
	m_fMat[5] = fCA + (1 - fCA) * fY * fY;
	m_fMat[6] = (1 - fCA) * fY * fZ - fSA * fX;
	m_fMat[8] = (1 - fCA) * fX * fZ - fSA * fY;
	m_fMat[9] = (1 - fCA) * fY * fZ + fSA * fX;
	m_fMat[10] = fCA + (1 - fCA) * fZ * fZ;
	/*m_fMat[0] = fX * fX + (1 - fX * fX) * fCA;
	m_fMat[1] = (1 - fCA) * fX * fY + fSA * fZ;
	m_fMat[2] = (1 - fCA) * fX * fZ - fSA * fY;
	m_fMat[4] = (1 - fCA) * fX * fY - fSA * fZ;
	m_fMat[5] = fY * fY + (1 - fY * fY) * fCA;
	m_fMat[6] = (1 - fCA) * fY * fZ + fSA * fX;
	m_fMat[8] = (1 - fCA) * fX * fZ + fSA * fY;
	m_fMat[9] = (1 - fCA) * fY * fZ - fSA * fX;
	m_fMat[10] = fZ * fZ + (1 - fZ * fZ) * fCA;*/

}

//////////////////////////////////////////////
//函数：	SetTMForScale(VVector3& vScale)	//
//功能：	设置该矩阵为指定缩放矩阵		//
//参数：	vScale-缩放量					//
//返回值：	无								//
//			by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::SetTMForScale(VVector3& vScale)
{
	IdentifyTM();
	m_fMat[0] = vScale.x;
	m_fMat[5] = vScale.y;
	m_fMat[10] = vScale.z;
}

//////////////////////////////////////////////
//函数：	MoveTM(VVector3& vec)			//
//功能：	在变换矩阵的基础上叠加平移		//
//参数：	vec-叠加平移的量				//
//返回值：	无								//
//			by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::MoveTM(VVector3& vec)
{
	m_fMat[3] += vec.x;
	m_fMat[7] += vec.y;
	m_fMat[11] += vec.z;
}

//////////////////////////////////////////////////////////////////
//函数：	Rotate(VMatrix3& tmAxis, VAxisAngle& vAxisAng)		//
//功能：	在该变换矩阵上叠加旋转变换							//
//参数：	tmAxis-指定旋转坐标系，vAxisAng-旋转轴旋转角		//
//返回值：	无													//
//			by xcc	2013.12.5	//
//////////////////////////////////////////////////////////////////
void VMatrix3::RotateTM(VAxisAngle& vAxisAng)
{
	VMatrix3 tmR;
	tmR.SetTMForRotate(vAxisAng);
	(*this) = (*this) * tmR;
}

//////////////////////////////////////////////
//函数：	ScaleTM(VVector3& vScale)		//
//功能：	在变换矩阵的基础上叠加缩放		//
//参数：	vScale-叠加缩放的量				//
//返回值：	无								//
//			by xcc	2013.12.5	//
//////////////////////////////////////////////
void VMatrix3::ScaleTM(VVector3& vScale)
{
	/*for (int i = 0; i < 4; i++)
	{
		m_fMat[i] *= vScale.x;
		m_fMat[4 + i] *= vScale.y;
		m_fMat[8 + i] *= vScale.z;
	}*/
	m_fMat[0] *= vScale.x;
	m_fMat[5] *= vScale.y;
	m_fMat[11] *= vScale.z;
}

////////////////////////////////////以下均为操作符重载///////////////////////////////////////////

VMatrix3 VMatrix3::operator +() const
{
	VMatrix3 mat;
	for (int i = 0; i < 12; i++)
	{
		mat.m_fMat[i] = m_fMat[i];
	}
	return mat;
}

VMatrix3 VMatrix3::operator -() const
{
	VMatrix3 mat;
	for (int i = 0; i < 12; i++)
	{
		mat.m_fMat[i] = - m_fMat[i];
	}
	return mat;
}

VMatrix3 VMatrix3::operator *(float scl) const
{
	VMatrix3 mat;
	for (int i = 0; i < 12; i++)
	{
		mat.m_fMat[i] = scl * m_fMat[i];
	}
	return mat;
}

VMatrix3 VMatrix3::operator /(float scl) const
{
	VMatrix3 mat;
	for (int i = 0; i < 12; i++)
	{
		mat.m_fMat[i] = m_fMat[i] / scl;
	}
	return mat;
}

VMatrix3 VMatrix3::operator +(VMatrix3& mat2)
{
	VMatrix3 mat;
	for (int i = 0; i < 12; i++)
	{
		mat.m_fMat[i] = m_fMat[i] + mat2.m_fMat[i];
	}
	return mat;
}

VMatrix3 VMatrix3::operator -(VMatrix3& mat2)
{
	VMatrix3 mat;
	for (int i = 0; i < 12; i++)
	{
		mat.m_fMat[i] = m_fMat[i] - mat2.m_fMat[i];
	}
	return mat;
}

VMatrix3 VMatrix3::operator *(VMatrix3& mat2)
{
	VMatrix3 mat;
	int i, j = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
		{
			mat.m_fMat[4 * i + j] = m_fMat[4 * i] * mat2.m_fMat[j] 
			+ m_fMat[4 * i + 1] * mat2.m_fMat[4 + j]
			+ m_fMat[4 * i + 2]*mat2.m_fMat[8 + j];
		}
	}
	mat.m_fMat[3] += m_fMat[3];
	mat.m_fMat[7] += m_fMat[7];
	mat.m_fMat[11] += m_fMat[11];
	return mat;
}

VMatrix3 VMatrix3::operator /(VMatrix3& mat2)
{
	VMatrix3 mat, mat1;
	if(mat2.GetInverseMat(mat1))
	{
		mat = (*this) * mat1;
	}
	return mat;
}

VMatrix3& VMatrix3::operator +=(VMatrix3& mat2)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] += mat2.m_fMat[i];
	}
	return (*this);
}

VMatrix3& VMatrix3::operator -=(VMatrix3& mat2)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] -= mat2.m_fMat[i];
	}
	return (*this);
}

VMatrix3& VMatrix3::operator *=(VMatrix3& mat2)
{
	VMatrix3 mat1;
	mat1 = (*this) * mat2;
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = mat1.m_fMat[i];
	}
	return (*this);
}

VMatrix3& VMatrix3::operator /=(VMatrix3& mat2)
{
	VMatrix3 mat,mat1;
	if(mat2.GetInverseMat(mat1))
	{
		mat = (*this) * mat1;
	}
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = mat.m_fMat[i];
	}
	return (*this);
}

VMatrix3& VMatrix3::operator *=(float scl)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] *= scl;
	}
	return (*this);
}

VMatrix3& VMatrix3::operator /=(float scl)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] /= scl;
	}
	return (*this);
}

bool VMatrix3::operator ==(VMatrix3& mat2)
{
	for (int i = 0; i < 12; i++)
	{
		if(m_fMat[i] != mat2.m_fMat[i])
			return false;
	}
	return true;
}

VMatrix3& VMatrix3::operator =(const VMatrix3& mat2)
{
	for (int i = 0; i < 12; i++)
	{
		m_fMat[i] = mat2.m_fMat[i];
	}
	return (*this);
}