#include "stdafx.h"
#include "Shape.h"


IMPLEMENT_SERIAL(CShape,CObject,1)
CShape::CShape()
{
}


CShape::~CShape()
{
}

BOOL CShape::DrawMe(CDC* pDC)
{
	return TRUE;
}

void CShape::Serialize(CArchive& ar)
{

}
