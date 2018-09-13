
// ScribbleView.h : CScribbleView 类的接口
//

#pragma once


class CScribbleView : public CView
{
protected: // 仅从序列化创建
	CScribbleView();
	DECLARE_DYNCREATE(CScribbleView)

// 特性
public:
	CScribbleDoc* GetDocument() const;
	UINT type;
protected:
	CStroke* m_pStrokeCur;
	CLine* m_pLineCur;
	CPoint m_ptPrev;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CScribbleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // ScribbleView.cpp 中的调试版本
inline CScribbleDoc* CScribbleView::GetDocument() const
   { return reinterpret_cast<CScribbleDoc*>(m_pDocument); }
#endif

