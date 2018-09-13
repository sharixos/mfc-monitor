#include<iostream>

class CObject
{
public:
	CObject::CObject(){ std::cout << "CObject Constructor\n"; }
	CObject::~CObject(){ std::cout << "CObject Destructor\n"; }
};

class CCmdTarget:public CObject
{
public:
	CCmdTarget::CCmdTarget(){ std::cout << "CCmdTarget Constructor\n"; }
	CCmdTarget::~CCmdTarget(){ std::cout << "CCmdTarget Destructor\n"; }
};

class CWinThread:public CCmdTarget
{
public:
	CWinThread::CWinThread(){ std::cout << "CWinThread Constructor\n"; }
	CWinThread::~CWinThread(){ std::cout << "CWinThread Destructor\n"; }
};

class CWinApp:public CWinThread
{
public:
	CWinApp* m_pCurrentWinApp;
public:
	CWinApp::CWinApp()
	{ 
		std::cout << "CWinApp Constructor\n"; 
		m_pCurrentWinApp = this;
	}
	CWinApp::~CWinApp(){ std::cout << "CWinApp Destructor\n"; }
};

class CWnd:public CCmdTarget
{
public:
	CWnd::CWnd(){ std::cout << "CWnd Constructor\n"; }
	CWnd::~CWnd(){ std::cout << "CWnd Destructor\n"; }
};

class CFrameWnd:public CWnd
{
public:
	CFrameWnd::CFrameWnd(){ std::cout << "CFrameWnd Constructor\n"; }
	CFrameWnd::~CFrameWnd(){ std::cout << "CFrameWnd Destructor\n"; }
};

class CView:public CWnd
{
public:
	CView::CView(){ std::cout << "CView Constructor\n"; }
	CView::~CView(){ std::cout << "CView Destructor\n"; }
};

//global function

CWinApp* AfxGetApp();