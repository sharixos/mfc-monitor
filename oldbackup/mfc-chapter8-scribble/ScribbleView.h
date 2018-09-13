
// ScribbleView.h : CScribbleView ��Ľӿ�
//

#pragma once


class CScribbleView : public CView
{
protected: // �������л�����
	CScribbleView();
	DECLARE_DYNCREATE(CScribbleView)

// ����
public:
	CScribbleDoc* GetDocument() const;
	UINT type;
protected:
	CStroke* m_pStrokeCur;
	CLine* m_pLineCur;
	CPoint m_ptPrev;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CScribbleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLine();
	afx_msg void OnStroke();
};

#ifndef _DEBUG  // ScribbleView.cpp �еĵ��԰汾
inline CScribbleDoc* CScribbleView::GetDocument() const
   { return reinterpret_cast<CScribbleDoc*>(m_pDocument); }
#endif

