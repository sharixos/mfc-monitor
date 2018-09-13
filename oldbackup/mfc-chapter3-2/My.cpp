#include "My.h"

CMyWinApp theApp;

void main()
{
	CWinApp* pApp = AfxGetApp();
	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();
}

bool CMyWinApp::InitInstance()
{
	std::cout << "CMyWinApp::InitInstance\n";
	m_pMainWnd = new CMyFrameWnd;

	return true;
}