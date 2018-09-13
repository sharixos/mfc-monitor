#include "My.h"

class CObject;
class CCmdTarget;
class CWinThread;
class CWinApp;
class CWnd;
class CDocument;
class CFrameWnd;
class CView;

extern CMyWinApp theApp;
extern void PrintlpEntries(AFX_MSGMAP_ENTRY* lpEntry);

static char szCObject[] = "CObject";
struct CRuntimeClass CObject::classCObject ={szCObject, sizeof(CObject), 0xffff, NULL, NULL, NULL};
static AFX_CLASSINIT _init_CObject(&CObject::classCObject);

CRuntimeClass* CRuntimeClass::pFirstClass = NULL;

AFX_CLASSINIT::AFX_CLASSINIT(CRuntimeClass* pNewClass)
{
	pNewClass->m_pNextClass = CRuntimeClass::pFirstClass;
	CRuntimeClass::pFirstClass = pNewClass;
}

CRuntimeClass* CObject::GetRuntimeClass()const
{
	return &CObject::classCObject;
}

BOOL CObject::IsKindOf(const CRuntimeClass* pClass)const
{
	CRuntimeClass* pClassThis = GetRuntimeClass();
	while (pClassThis != NULL)
	{
		if (pClassThis == pClass)
		{
			return TRUE;
		}
		pClassThis = pClassThis->m_pBaseClass;
	}
	return FALSE;
}

CObject* CRuntimeClass::CreateObject()
{
	if (m_pfnCreateObject == NULL)
	{
		TRACE1("Error: Trying to create object which is not "
			"DECLARE_DYNCREATE \nor DECLARE_SERIAL: %hs.\n",
			m_lpszClassName);
		return NULL;
	}

	CObject* pObject = NULL;
	pObject = (*m_pfnCreateObject)();

	return pObject;
}

CRuntimeClass* PASCAL CRuntimeClass::Load()
{
	char szClassName[64];
	CRuntimeClass* pClass;

	std::cout << "please enter a class name...?";
	std::cin >> szClassName;

	for (pClass = pFirstClass; pClass != NULL; pClass = pClass->m_pNextClass)
	{
		if (strcmp(szClassName, pClass->m_lpszClassName) == 0)
			return pClass;
	}

	TRACE1("Error: Class not found:%s\n", szClassName);
	return NULL;
}


BOOL CWnd::Create()
{
	std::cout << "CWnd::Create\n";
	return TRUE;
}

BOOL CWnd::CreateEx()
{
	std::cout << "CWnd::CreateEx\n";
	PreCreateWindow();
	return TRUE;
}

BOOL CWnd::PreCreateWindow()
{
	std::cout << "CWnd::PreCreateWindow\n";
	return TRUE;
}

BOOL CFrameWnd::Create()
{
	std::cout << "CFrame::Create\n";
	CreateEx();
	return TRUE;
}

BOOL CFrameWnd::PreCreateWindow()
{
	std::cout << "CFrameWnd::PreCreateWindow\n";
	return TRUE;
}

CView* CFrameWnd::GetActiveView() const
{
	return m_pViewActive;
}

AFX_MSGMAP* CCmdTarget::GetMessageMap() const
{
	return &CCmdTarget::messageMap;
}

AFX_MSGMAP CCmdTarget::messageMap =
{
	NULL,
	&CCmdTarget::_messageEntries[0]
};

AFX_MSGMAP_ENTRY CCmdTarget::_messageEntries[]=
{
	{0,0,CCmdTargetid,0,AfxSig_end,0}
};

BOOL CCmdTarget::OnCmdMsg(UINT nID, int nCode)
{
	std::cout << "CCmdTarget::OnCmdMsg" << std::endl;
	AFX_MSGMAP* pMessageMap;
	AFX_MSGMAP_ENTRY* lpEntry;
	for (pMessageMap=GetMessageMap(); pMessageMap != NULL; pMessageMap = pMessageMap->pBaseMessageMap)
	{
		lpEntry = pMessageMap->lpEntries;
		PrintlpEntries(lpEntry);
	}
	return FALSE;
}

LRESULT CWnd::WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	AFX_MSGMAP* pMessageMap;
	AFX_MSGMAP_ENTRY* lpEntry;
	
	if (nMsg == WM_COMMAND)
	{
		if (OnCmdMsg(wParam, lParam))
			return 1L;
		else
			return(LRESULT)DefWindowProc(nMsg, wParam, lParam);
	}

	pMessageMap = GetMessageMap();
	for (; pMessageMap != NULL; pMessageMap = pMessageMap->pBaseMessageMap)
	{
		lpEntry = pMessageMap->lpEntries;
		PrintlpEntries(lpEntry);
	}
	return 0;
}
LRESULT CWnd::DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}
BOOL CWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	std::cout << "CWnd::OnCommand" << std::endl;
	return OnCmdMsg(0, 0);
}

BOOL CFrameWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	std::cout << "CFrameWnd::OnCommand" << std::endl;
	return CWnd::OnCommand(wParam, lParam);
}

BOOL CFrameWnd::OnCmdMsg(UINT nID, int nCode)
{
	std::cout << "CFrameWnd::OnCmdMsg" << std::endl;
	CView* pView = GetActiveView();

	//pump throuht current view FIRST
	if (pView->OnCmdMsg(nID, nCode))
		return TRUE;

	//then pump through frame
	if (CWnd::OnCmdMsg(nID, nCode))
		return TRUE;

	//last but not least,pump through app
	CWinApp* pApp = AfxGetApp();
	if (pApp->OnCmdMsg(nID, nCode))
		return TRUE;

	return FALSE;
}

BOOL CDocument::OnCmdMsg(UINT nID, int nCode)
{
	std::cout << "CDocument::OnCmdMsg" << std::endl;
	if (CCmdTarget::OnCmdMsg(nID, nCode))
		return TRUE;

	return FALSE;
}

BOOL CView::OnCmdMsg(UINT nID, int nCode)
{
	std::cout << "CView::OnCmdMsg" << std::endl;
	if (CWnd::OnCmdMsg(nID, nCode))
		return TRUE;
	BOOL bHandled = FALSE;
	bHandled = m_pDocument->OnCmdMsg(nID, nCode);
	return bHandled;
}

IMPLEMENT_DYNAMIC(CCmdTarget,CObject)
IMPLEMENT_DYNAMIC(CWinThread,CCmdTarget)
IMPLEMENT_DYNAMIC(CWinApp,CWinThread)
IMPLEMENT_DYNCREATE(CWnd,CCmdTarget)
IMPLEMENT_DYNCREATE(CFrameWnd, CWnd)
IMPLEMENT_DYNAMIC(CDocument,CCmdTarget)
IMPLEMENT_DYNAMIC(CView,CWnd)

BEGIN_MESSAGE_MAP(CWnd,CCmdTarget)
	ON_COMMAND(CWndid,0)		
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CFrameWnd, CWnd)
	ON_COMMAND(CFrameWndid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDocument, CCmdTarget)
	ON_COMMAND(CDocumentid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CView, CWnd)
	ON_COMMAND(CViewid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CWinApp, CCmdTarget)
	ON_COMMAND(CWinAppid, 0)
END_MESSAGE_MAP()

CWinApp* AfxGetApp()
{
	std::cout << "CWinApp::AfxGetApp\n";
	return theApp.m_pCurrentWinApp;
}

LRESULT AfxWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam, CWnd* pWnd)
{
	return AfxCallWndProc(pWnd, hWnd, nMsg, wParam,lParam);
}
LRESULT AfxCallWndProc(CWnd* pWnd, HWND hWnd, UINT nMsg, WPARAM wParam,LPARAM lParam)
{
	LRESULT lResult = pWnd->WindowProc(nMsg, wParam, lParam);
	return lResult;
}
