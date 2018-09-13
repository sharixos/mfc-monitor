#include "My.h"

CMyWinApp theApp;

void main()
{
	CWinApp* pApp = AfxGetApp();
	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();
	PrintAllClasses();
	std::cout << "------\n";
	std::cout << pApp->IsKindOf(RUNTIME_CLASS(CCmdTarget));
	std::cout << "------\n";
	PrintAllClasses();
}

BOOL CMyWinApp::InitInstance()
{
	std::cout << "CMyWinApp::InitInstance\n";
	m_pMainWnd = new CMyFrameWnd;

	return TRUE;
}

IMPLEMENT_DYNAMIC(CMyWinApp,CWinApp)
IMPLEMENT_DYNAMIC(CMyFrameWnd,CFrameWnd)
IMPLEMENT_DYNAMIC(CMyDoc,CDocument)

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