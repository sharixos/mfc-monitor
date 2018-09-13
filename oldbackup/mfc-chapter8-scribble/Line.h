#pragma once
#include "Shape.h"
class CLine :
	public CShape
{
public:
	CArray<CPoint, CPoint> m_pointArray;
	CPoint m_ptPrev;
	CPoint m_ptOld;
public:
	CLine(UINT nPenWidth);
	~CLine();
protected:
	CLine();
	DECLARE_SERIAL(CLine)
public:
	virtual BOOL DrawMe(CDC* pDC);
	virtual void Serialize(CArchive& ar);


};

