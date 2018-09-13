
// ScribbleDoc.h : CScribbleDoc 类的接口
//

#include "Stroke.h"
#include "Line.h"
#pragma once


class CScribbleDoc : public CDocument
{
protected: // 仅从序列化创建
	CScribbleDoc();
	DECLARE_DYNCREATE(CScribbleDoc)

// 特性
protected:
	UINT m_nPenWidth;
	CPen m_penCur;
	UINT type;
public:
	CTypedPtrList<CObList, CShape*> m_shapeList;
	CPen* GetCurrentPen();
// 操作
public:
	CStroke* NewStroke();
	CLine* NewLine();
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CScribbleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void InitDocument();
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
};
