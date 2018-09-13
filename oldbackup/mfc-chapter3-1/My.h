#include"MFC.h"

class CMyWinApp:public CWinApp
{
public:
	CMyWinApp::CMyWinApp(){ std::cout << "CMyWinApp Constructor"; }
	CMyWinApp::~CMyWinApp(){ std::cout << "CMyWinApp Destructor"; }
};

class CMyFrameWnd :public CFrameWnd
{
public:
	CMyFrameWnd::CMyFrameWnd(){ std::cout << "CMyFrameWnd Constructor"; }
	CMyFrameWnd::~CMyFrameWnd(){ std::cout << "CMyFrameWnd Destructor"; }
};
