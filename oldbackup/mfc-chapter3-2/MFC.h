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
public:
	virtual bool InitInstance()
	{
		std::cout << "CCmdTarget::InitInstance\n";
		return true;
	}
	virtual int Run()
	{
		std::cout << "CCmdTarget::Run\n";
		return 1;
	}
};

class CWinThread:public CCmdTarget
{
public:
	CWinThread::CWinThread(){ std::cout << "CWinThread Constructor\n"; }
	CWinThread::~CWinThread(){ std::cout << "CWinThread Destructor\n"; }
public:
	virtual bool InitInstance()
	{
		std::cout << "CWinThread::InitInstance\n";
		return true;
	}
	virtual int Run()
	{
		std::cout << "CWinThread::Run\n";
		return 1;
	}

};

class CWnd:public CCmdTarget
{
public:
	CWnd::CWnd(){ std::cout << "CWnd Constructor\n"; }
	CWnd::~CWnd(){ std::cout << "CWnd Destructor\n"; }
public:
	virtual bool Create();
	bool CreateEx();
	virtual bool PreCreateWindow();
};

class CWinApp:public CWinThread
{
public:
	CWinApp* m_pCurrentWinApp;
	CWnd* m_pMainWnd;
public:
	CWinApp::CWinApp()
	{ 
		std::cout << "CWinApp Constructor\n"; 
		m_pCurrentWinApp = this;
	}
	CWinApp::~CWinApp(){ std::cout << "CWinApp Destructor\n"; }
public:
	virtual bool InitApplication()
	{
		std::cout << "CWinApp::InitApplication\n";
		return true;
	}
	virtual bool InitInstance()
	{
		std::cout << "CWinApp::InitInstance\n";
		return true;
	}
	virtual int Run()
	{
		std::cout << "CWinApp::Run\n";
		return CWinThread::Run();
	}
};

class CFrameWnd:public CWnd
{
public:
	CFrameWnd::CFrameWnd(){ std::cout << "CFrameWnd Constructor\n"; }
	CFrameWnd::~CFrameWnd(){ std::cout << "CFrameWnd Destructor\n"; }
public:
	bool Create();//virtual is removed
	virtual bool PreCreateWindow();
};

class CView:public CWnd
{
public:
	CView::CView(){ std::cout << "CView Constructor\n"; }
	CView::~CView(){ std::cout << "CView Destructor\n"; }

public:

};

//global function

CWinApp* AfxGetApp();