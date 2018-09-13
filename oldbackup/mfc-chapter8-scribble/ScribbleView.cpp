
// ScribbleView.cpp : CScribbleView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Scribble.h"
#endif

#include "ScribbleDoc.h"
#include "ScribbleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScribbleView

IMPLEMENT_DYNCREATE(CScribbleView, CView)

BEGIN_MESSAGE_MAP(CScribbleView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_LINE, &CScribbleView::OnLine)
	ON_COMMAND(IDM_STROKE, &CScribbleView::OnStroke)
END_MESSAGE_MAP()

// CScribbleView 构造/析构

CScribbleView::CScribbleView()
{
	// TODO:  在此处添加构造代码
	type = 0;
}

CScribbleView::~CScribbleView()
{
}

BOOL CScribbleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CScribbleView 绘制

void CScribbleView::OnDraw(CDC* pDC)
{
	CScribbleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	CTypedPtrList<CObList, CShape*>& shapeList = pDoc->m_shapeList;
	POSITION pos = shapeList.GetHeadPosition();
	while (pos != NULL)
	{
		CShape* pShape=shapeList.GetNext(pos);
		switch (pShape->_type)
		{
		case 0:
			break;
		case 1:
			(CLine*)pShape->DrawMe(pDC);
			break;
		case 2:
			(CStroke*)pShape->DrawMe(pDC);
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}
	}
}

void CScribbleView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CScribbleView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CScribbleView 诊断

#ifdef _DEBUG
void CScribbleView::AssertValid() const
{
	CView::AssertValid();
}

void CScribbleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CScribbleDoc* CScribbleView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScribbleDoc)));
	return (CScribbleDoc*)m_pDocument;
}
#endif //_DEBUG


// CScribbleView 消息处理程序


void CScribbleView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (type)
	{
	case 1:
		m_pLineCur = GetDocument()->NewLine();
		m_pLineCur->m_pointArray.Add(point);
		break;
	case 2:
		m_pStrokeCur = GetDocument()->NewStroke();
		m_pStrokeCur->m_pointArray.Add(point);
		break;
	default:
		break;
	}
	SetCapture();
	m_ptPrev = point;
	CView::OnLButtonDown(nFlags, point);
}


void CScribbleView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (GetCapture() != this)
		return;
	CScribbleDoc* pDC = GetDocument();
	CClientDC dc(this);

	CPen* pOldPen = dc.SelectObject(pDC->GetCurrentPen());
	switch (type)
	{
	case 1:
		dc.MoveTo(m_ptPrev);
		dc.LineTo(point);
		dc.SelectObject(pOldPen);
		m_pLineCur->m_pointArray.Add(point);
		break;
	case 2:
		dc.MoveTo(m_ptPrev);
		dc.LineTo(point);
		dc.SelectObject(pOldPen);
		m_pStrokeCur->m_pointArray.Add(point);

		break;
	default:
		break;
	}
	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}


void CScribbleView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (GetCapture() != this)
		return;
	CClientDC dc(this);
	CPen *pOldPen = dc.SelectObject(GetDocument()->GetCurrentPen());
	switch (type)
	{
	case 1:
		break;
	case 2:
		m_pStrokeCur->m_pointArray.Add(point);
		dc.MoveTo(m_ptPrev);
		dc.LineTo(point);
		dc.SelectObject(pOldPen);
		m_ptPrev = point;
		break;
	default:
		break;
	}

	CView::OnMouseMove(nFlags, point);
}


void CScribbleView::OnLine()
{
	// TODO:  在此添加命令处理程序代码
	type = 1;
}


void CScribbleView::OnStroke()
{
	// TODO:  在此添加命令处理程序代码
	type = 2;
}
