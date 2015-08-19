#include "vcontrol.h"

void VControl::Move(VVector3& move) //ÒÆ¶¯¾ØÕó
{
	m_mat.MoveTM(-move);
}
void VControl::Rotate(VAxisAngle& AxisAng)//Ğı×ª¾ØÕó
{
	m_mat.RotateTM(AxisAng);
}
void VControl::Scale(VVector3& scale)//Ëõ·Å¾ØÕó
{
	m_mat.ScaleTM(scale);
}
VMatrix3 VControl::GetTM()//·µ»Ø¾ØÕó
{
	return m_mat;
}

void VControl::SetTM(VMatrix3& tm)//ÉèÖÃ¸Ã¾ØÕó
{
	m_mat = tm;								
}

void VControl::SetTM(VMatrix3* p_mat)//ÉèÖÃ¸Ã¾ØÕó
{
	m_mat = *p_mat;								
}

//¿½±´¾ØÕó
void VControl::CopyMat(VMatrix3& newMat)
{
	m_mat = newMat;
}