#include "stdafx.h"
#include "Line.h"

IMPLEMENT_SERIAL(CLine,CShape,1)
CLine::CLine()
{
	_type = 1;
}
CLine::CLine(UINT nPenWidth)
{
	m_nPenWidth = nPenWidth;
	_type = 1;
}

CLine::~CLine()
{
}

BOOL CLine::DrawMe(CDC* pDC)
{
	CPen penStroke;
	if (!penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(0, 0, 255)))
		return FALSE;
	CPen* pOldPen = pDC->SelectObject(&penStroke);
	pDC->MoveTo(m_pointArray[0]);
	pDC->LineTo(m_pointArray[1]);
	pDC->SelectObject(pOldPen);
	return TRUE;
}

void CLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)m_nPenWidth;
		m_pointArray.Serialize(ar);
	}
	else
	{
		WORD w;
		ar >> w;
		m_nPenWidth = w;
		m_pointArray.Serialize(ar);
	}
}
