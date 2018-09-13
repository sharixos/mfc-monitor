#pragma once
#include "afx.h"
class CShape :
	public CObject
{
protected:
	DECLARE_SERIAL(CShape)
public:
	UINT m_nPenWidth;
	UINT _type;
public:
	CShape();
	~CShape();
public:
	virtual BOOL DrawMe(CDC* pDC);
	virtual void Serialize(CArchive& ar);

};

