#pragma once
#include "afx.h"
#include "Shape.h"
class CStroke :
	public CShape
{
public :
	CArray<CPoint, CPoint> m_pointArray;
public:
	CStroke(UINT m_nPenWidth);
	~CStroke();
protected:
	CStroke();
	DECLARE_SERIAL(CStroke)
//·½·¨
public:

public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL DrawMe(CDC* pDC);

};

