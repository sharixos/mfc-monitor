#include "My.h"

CMyWinApp theApp;
void main()
{
	CWinApp* pApp = AfxGetApp();
	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();
	
	CRuntimeClass* pClassRef;
	CObject* pOb;
	while (1)
	{
		if ((pClassRef = CRuntimeClass::Load()) == NULL)
			break;
		pOb = pClassRef->CreateObject();
	//	if (pOb != NULL)
		//调用pOb的函数
	}
}

BOOL CMyWinApp::InitInstance()
{
	std::cout << "CMyWinApp::InitInstance\n";
	m_pMainWnd = new CMyFrameWnd;

	return TRUE;
}

CMyFrameWnd::CMyFrameWnd()
{
	std::cout << "CMyFrameWnd Constructor\n";
	Create();
}

IMPLEMENT_DYNCREATE(CMyFrameWnd, CFrameWnd)
IMPLEMENT_DYNCREATE(CMyDoc, CDocument)
IMPLEMENT_DYNCREATE(CMyView,CView)

//global function
void PrintAllClasses()
{
	CRuntimeClass* pClass;

	for (pClass = CRuntimeClass::pFirstClass; pClass != NULL; pClass=pClass->m_pNextClass)
	{
		std::cout << pClass->m_lpszClassName << "\n";
		std::cout << pClass->m_nObjectSize << "\n";
		std::cout << pClass->m_wSchema << "\n";
	}
}