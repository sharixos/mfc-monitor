#include"MFC.h"

class CMyWinApp:public CWinApp
{
	DECLARE_DYNAMIC(CMyWinApp)
public:
	CMyWinApp::CMyWinApp(){ std::cout << "CMyWinApp Constructor"; }
	CMyWinApp::~CMyWinApp(){ std::cout << "CMyWinApp Destructor"; }
public:
	virtual BOOL InitInstance();
};

class CMyFrameWnd :public CFrameWnd
{
	DECLARE_DYNAMIC(CMyFrameWnd)
public:
	CMyFrameWnd::CMyFrameWnd(){ std::cout << "CMyFrameWnd Constructor"; }
	CMyFrameWnd::~CMyFrameWnd(){ std::cout << "CMyFrameWnd Destructor"; }
};

class CMyDoc :public CDocument
{
	DECLARE_DYNAMIC(CMyDoc)
public:
	CMyDoc::CMyDoc(){ std::cout << "CMyDoc Constructor"; }
	CMyDoc::~CMyDoc(){ std::cout << "CMyDoc Destructor"; }
};

//global function
void PrintAllClasses();
