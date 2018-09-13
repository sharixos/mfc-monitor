
// ScribbleDoc.cpp : CScribbleDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Scribble.h"
#endif

#include "ScribbleDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CScribbleDoc

IMPLEMENT_DYNCREATE(CScribbleDoc, CDocument)

BEGIN_MESSAGE_MAP(CScribbleDoc, CDocument)
END_MESSAGE_MAP()


// CScribbleDoc 构造/析构

CScribbleDoc::CScribbleDoc()
{
	// TODO:  在此添加一次性构造代码
	type = 0;
}

CScribbleDoc::~CScribbleDoc()
{
}

BOOL CScribbleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	InitDocument();
	return TRUE;
}




// CScribbleDoc 序列化

void CScribbleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
	m_shapeList.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CScribbleDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CScribbleDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CScribbleDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CScribbleDoc 诊断

#ifdef _DEBUG
void CScribbleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScribbleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CScribbleDoc 命令


BOOL CScribbleDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码
	InitDocument();
	return TRUE;
}


void CScribbleDoc::DeleteContents()
{
	// TODO:  在此添加专用代码和/或调用基类
	while (!m_shapeList.IsEmpty())
	{
		delete m_shapeList.RemoveHead();
	}
	CDocument::DeleteContents();
}

CPen* CScribbleDoc::GetCurrentPen()
{
	return &m_penCur;
}

void CScribbleDoc::InitDocument()
{
	m_nPenWidth = 2;
	m_penCur.CreatePen(PS_SOLID, m_nPenWidth, RGB(255, 0, 0));
}

CStroke* CScribbleDoc::NewStroke()
{
	CStroke* pStrokeItem = new CStroke(m_nPenWidth);
	m_shapeList.AddTail(pStrokeItem);
	SetModifiedFlag();
	return pStrokeItem;
}

CLine* CScribbleDoc::NewLine()
{
	CLine* pLineItem = new CLine(m_nPenWidth);
	m_shapeList.AddTail(pLineItem);
	SetModifiedFlag();
	return pLineItem;
}