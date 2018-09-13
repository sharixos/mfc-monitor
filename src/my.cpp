#include "my.h"
#include "message.h"
#include <iostream>
#include <typeinfo>
using namespace std;
using namespace mfc;

#include "global.h"

CMyWinApp theApp;

void init()
{
	pApp = theApp.m_pCurrentWinApp;
}


void main()
{
	init();
	mfc::CWinApp *pApp = AfxGetApp();
	if (pApp)
	{
		pApp->InitApplication();
		pApp->InitInstance();
		pApp->Run();

		//mfc::CObject * p = static_cast<mfc::CObject *>(Tools::CreateObject("CObject"));

		//mfc::CFrameWnd *pMyFrame = (mfc::CFrameWnd*)pApp->m_pMainWnd;

		//mfc::AFX_MSGMAP* pMessageMap = pMyFrame->GetMessageMap();

		//pMessageMap->pMessageEntries->push_back(ON_COMMAND(Tools::getId("CWnd"), 0));

		//for (;pMessageMap != 0; pMessageMap = pMessageMap->pBaseMessageMap) {
		//	std::vector<AFX_MSGMAP_ENTRY> * pMessageEntries = pMessageMap->pMessageEntries;
		//	
		//	cout << "-----" << endl;
		//	for (AFX_MSGMAP_ENTRY i : (*pMessageEntries)) {
		//		cout <<i.nMessage<<" "<< i.nCode<<" "<<i.nID<<" "<<i.nLastID<<" "<<i.nSig<<" "<<i.pfn << endl;
		//	}
		//}


		CMyDoc *pMyDoc = new CMyDoc;
		CMyView *pMyView = new CMyView;
		mfc::CFrameWnd *pMyFrame = (mfc::CFrameWnd*)pApp->m_pMainWnd;

		pMyFrame->m_pViewActive = pMyView;
		pMyView->m_pDocument = pMyDoc;

		AfxWndProc(0, WM_COMMAND, 1, 2, pMyFrame);

	}
	else {
		std::cout << "ERROR pApp is NULL\n";
	}
}

bool CMyWinApp::InitInstance()
{
	std::cout << __FUNCTION__ << std::endl;
	m_pMainWnd = (mfc::CFrameWnd*)new CMyFrameWnd;

	return true;
}