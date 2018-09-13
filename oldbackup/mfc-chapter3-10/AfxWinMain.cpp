#include "stdafx.h"


int AFXAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	return AfxWinMain(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
}

int AFXAPI AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CWinApp* pApp = AfxGetApp();
	AfxWinInit(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();

	return TRUE;
}

BOOL AFXAPI AfxWinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	CWinApp* pApp = AfxGetApp();

	pApp->m_hInstance = hInstance;
	pApp->m_hPrevInstance = hPrevInstance;
	pApp->m_lpCmdLine = lpCmdLine;
	pApp->m_nCmdShow = nCmdShow;
	//	pApp->SetCurrentHandles();

	return TRUE;
}

BOOL AFXAPI AfxEndDeferRegisterClass(WNDCLASS* wndcls)
{
	return AfxRegisterClass(wndcls);
}

BOOL AFXAPI AfxRegisterClass(WNDCLASS* wndcls)
{
	RegisterClass(wndcls);
	return TRUE;
}