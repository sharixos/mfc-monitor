#include "My.h"

CMyWinApp theApp;
void MsgMapPrinting(AFX_MSGMAP* pMessageMap);
void main()
{
	CWinApp* pApp = AfxGetApp();
	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();
	
	CMyDoc* pMyDoc = new CMyDoc;
	CMyView* pMyView = new CMyView;
	CFrameWnd* pMyFrame =(CFrameWnd*) pApp->m_pMainWnd;

	AFX_MSGMAP* pMessageMap = pMyView->GetMessageMap();
	std::cout << std::endl << "CMyView MessageMap:" << std::endl;
	MsgMapPrinting(pMessageMap);

	pMessageMap = pMyDoc->GetMessageMap();
	std::cout << std::endl << "pMyDoc MessageMap:" << std::endl;
	MsgMapPrinting(pMessageMap);

	pMessageMap = pMyFrame->GetMessageMap();
	std::cout << std::endl << "pMyFrame MessageMap:" << std::endl;
	MsgMapPrinting(pMessageMap);

	
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

BEGIN_MESSAGE_MAP(CMyWinApp, CWinApp)
	ON_COMMAND(CMyWinAppid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_COMMAND(CMyFrameWndid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
	ON_COMMAND(CMyDocid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyView, CView)
	ON_COMMAND(CMyViewid, 0)
END_MESSAGE_MAP()

//global function
void PrintlpEntries(AFX_MSGMAP_ENTRY* lpEntry)
{
	struct
	{
		int classid;
		char * className;
	}classinfo[] = {
		CCmdTargetid, "CCmdTarget",
		CWinThreadid, "CWinThread",
		CWinAppid, "CWinApp",
		CMyWinAppid, "CMyWinApp",
		CWndid, "CWnd",
		CFrameWndid, "CFrameWnd",
		CMyFrameWndid, "CMyFrameWnd",
		CViewid, "CView",
		CMyViewid, "CMyView",
		CDocumentid, "CDocument",
		CMyDocid, "CMyDoc",
		0, "   "
	};

	for (int i = 0; classinfo[i].classid!= 0; i++)
	{
		if (classinfo[i].classid == lpEntry->nID)
		{
			std::cout << lpEntry->nID << "";
			std::cout << classinfo[i].className << std::endl;
			break;
		}
	}
}

void MsgMapPrinting(AFX_MSGMAP* pMessageMap)
{
	for (; pMessageMap != NULL; pMessageMap = pMessageMap->pBaseMessageMap)
	{
		AFX_MSGMAP_ENTRY* lpEntry = pMessageMap->lpEntries;
		PrintlpEntries(lpEntry);
	}
}