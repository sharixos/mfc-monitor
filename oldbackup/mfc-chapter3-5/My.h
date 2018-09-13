#include"MFC.h"

class CMyWinApp:public CWinApp
{
public:
	CMyWinApp::CMyWinApp(){ std::cout << "CMyWinApp Constructor"; }
	CMyWinApp::~CMyWinApp(){ std::cout << "CMyWinApp Destructor"; }
public:
	virtual BOOL InitInstance();
};

class CMyFrameWnd :public CFrameWnd
{
	DECLARE_DYNCREATE(CMyFrameWnd)
public:
	CMyFrameWnd::CMyFrameWnd();
	CMyFrameWnd::~CMyFrameWnd(){ std::cout << "CMyFrameWnd Destructor"; }
};

class CMyDoc :public CDocument
{
	DECLARE_DYNCREATE(CMyDoc)
public:
	CMyDoc::CMyDoc(){ std::cout << "CMyDoc Constructor"; }
	CMyDoc::~CMyDoc(){ std::cout << "CMyDoc Destructor"; }
};

class CMyView :public CView
{
	DECLARE_DYNCREATE(CMyView)
public:
	CMyView::CMyView(){ std::cout << "CMyView Constructor"; }
	CMyView::~CMyView(){ std::cout << "CMyView Destructor"; }
};

//global function
void PrintAllClasses();
