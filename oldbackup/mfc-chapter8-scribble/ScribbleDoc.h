
// ScribbleDoc.h : CScribbleDoc ��Ľӿ�
//

#include "Stroke.h"
#include "Line.h"
#pragma once


class CScribbleDoc : public CDocument
{
protected: // �������л�����
	CScribbleDoc();
	DECLARE_DYNCREATE(CScribbleDoc)

// ����
protected:
	UINT m_nPenWidth;
	CPen m_penCur;
	UINT type;
public:
	CTypedPtrList<CObList, CShape*> m_shapeList;
	CPen* GetCurrentPen();
// ����
public:
	CStroke* NewStroke();
	CLine* NewLine();
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CScribbleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void InitDocument();
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
};
