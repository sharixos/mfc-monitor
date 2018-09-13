
// ScribbleView.cpp : CScribbleView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CScribbleView ����/����

CScribbleView::CScribbleView()
{
	// TODO:  �ڴ˴���ӹ������
	type = 0;
}

CScribbleView::~CScribbleView()
{
}

BOOL CScribbleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CScribbleView ����

void CScribbleView::OnDraw(CDC* pDC)
{
	CScribbleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CScribbleView ���

#ifdef _DEBUG
void CScribbleView::AssertValid() const
{
	CView::AssertValid();
}

void CScribbleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CScribbleDoc* CScribbleView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScribbleDoc)));
	return (CScribbleDoc*)m_pDocument;
}
#endif //_DEBUG


// CScribbleView ��Ϣ�������


void CScribbleView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ���������������
	type = 1;
}


void CScribbleView::OnStroke()
{
	// TODO:  �ڴ���������������
	type = 2;
}
