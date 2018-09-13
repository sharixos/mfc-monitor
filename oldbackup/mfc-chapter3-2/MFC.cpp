#include "My.h"

extern CMyWinApp theApp;

CWinApp* AfxGetApp()
{
	return theApp.m_pCurrentWinApp;
}

bool CWnd::Create()
{
	std::cout << "CWnd::Create\n";
	return true;
}

bool CWnd::CreateEx()
{
	std::cout << "CWnd::CreateEx\n";
	PreCreateWindow();
	return true;
}

bool CWnd::PreCreateWindow()
{
	std::cout << "CWnd::PreCreateWindow\n";
	return true;
}

bool CFrameWnd::Create()
{
	std::cout << "CFrame::Create\n";
	CreateEx();
	return true;
}

bool CFrameWnd::PreCreateWindow()
{
	std::cout << "CFrameWnd::PreCreateWindow\n";
	return true;
}
