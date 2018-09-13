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


BOOL CWnd::Create(LPCTSTR lpszClassName,
	LPCTSTR lpszWindowName, DWORD dwStyle,
	const RECT& rect,
	CWnd* pParentWnd, UINT nID)
{
	return TRUE;
}

void CFrameWnd::ShowWindow(int nCmdShow)
{
	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
}

void CFrameWnd::UpdateWindow()
{
	::UpdateWindow(m_hWnd);
}
BOOL CWnd::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
	LPCTSTR lpszWindowName, DWORD dwStyle,
	int x, int y, int nWidth, int nHeight,
	HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam)
{
	CREATESTRUCT cs;
	cs.dwExStyle = dwExStyle;
	cs.lpszClass = lpszClassName;
	cs.lpszName = lpszWindowName;
	cs.style = dwStyle;
	cs.x = x;
	cs.y = y;
	cs.cx = nWidth;
	cs.cy = nHeight;
	cs.hwndParent = hWndParent;
	cs.hMenu = nIDorHMenu;
	cs.hInstance = AfxGetInstanceHandle();
	cs.lpCreateParams = lpParam;

	CWinApp* pApp = AfxGetApp();
	CWnd * pWnd = pApp->m_pMainWnd;
	WNDCLASS wndcls;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);
	wndcls.hIcon = LoadIcon(NULL, IDC_CROSS);
	wndcls.hInstance = pApp->m_hInstance;
	wndcls.lpfnWndProc = AfxWndProc;
	wndcls.lpszClassName = "Weixin2003";
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;

	PreCreateWindow(&wndcls);

	m_hWnd = CreateWindow("Weixin2003", "Ich bin Zerd", WS_OVERLAPPEDWINDOW,
		0, 0, 600, 400, NULL, NULL, pApp->m_hInstance, NULL);

	return TRUE;
}

BOOL CWnd::PreCreateWindow(WNDCLASS* wndcls)
{
	AfxDeferRegisterClass(wndcls);
	return TRUE;
}

BOOL CFrameWnd::Create(LPCTSTR lpszClassName,
	LPCTSTR lpszWindowName,
	DWORD dwStyle,
	LPCTSTR lpszMenuName,
	DWORD dwExStyle)
{
	HMENU hMenu=NULL;
	CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle,
		20, 40,60,80,
		m_hWnd, hMenu, NULL);
	return TRUE;
}

BOOL CFrameWnd::PreCreateWindow(WNDCLASS* wndcls)
{
	AfxDeferRegisterClass(wndcls);
	return TRUE;
}

CView* CFrameWnd::GetActiveView() const
{
	return m_pViewActive;
}

void CWnd::ShowWindow(int nCmdShow)
{
	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
}

void CWnd::UpdateWindow()
{
	::UpdateWindow(m_hWnd);
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
	
	return FALSE;
}

LRESULT CALLBACK CWnd::WindowProc(HWND hWnd,UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	
	if (nMsg == WM_COMMAND)
	{
		if (OnCmdMsg(wParam, lParam))
			return 1L;
		else
			return(LRESULT)DefWindowProc(nMsg, wParam, lParam);
	}

	
	// OnWndMsg does most of the work, except for DefWindowProc call
	LRESULT lResult = 0;
	if (!OnWndMsg(nMsg, wParam, lParam, &lResult))
		lResult = DefWindowProc(nMsg, wParam, lParam);
	return lResult;

}
BOOL CWnd::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch (message)
	{
	case WM_CHAR:
		char szChar[20];
		sprintf_s(szChar, "char is d%", wParam);
		MessageBox(m_hWnd, szChar, "ff", 0);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(m_hWnd, "m  c", "ff", 0);
		HDC hdc;
		hdc = GetDC(m_hWnd);
		TextOut(hdc, 0, 0, "Zerd", strlen("Zerd"));
		ReleaseDC(m_hWnd, hdc);
		break;
	case WM_PAINT:
		HDC hDc;
		PAINTSTRUCT ps;
		hDc = BeginPaint(m_hWnd, &ps);
		EndPaint(m_hWnd, &ps);
		break;
	case WM_CLOSE:
//		if (IDYES == MessageBox(m_hWnd, " «∑Ò’ÊΩ· ¯£ø", "ff", MB_YESNO))
		{
			DestroyWindow(m_hWnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(message, wParam, lParam);
	}
	return 0;
}
LRESULT CWnd::DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	
	return ::DefWindowProc(m_hWnd, nMsg, wParam, lParam);
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
	if (CCmdTarget::OnCmdMsg(nID, nCode))
		return TRUE;

	return FALSE;
}

BOOL CView::OnCmdMsg(UINT nID, int nCode)
{
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

HINSTANCE AFXAPI AfxGetInstanceHandle()
{
	CWinApp* pApp = AfxGetApp();
	return pApp->m_hInstance;
}
LRESULT CALLBACK AfxWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	CWinApp* pApp = AfxGetApp();
	CWnd* pWnd = pApp->m_pMainWnd;//CWnd::FromHandlePermanent(hWnd);
	if (pWnd == NULL || pWnd->m_hWnd != hWnd)
		return ::DefWindowProc(hWnd, nMsg, wParam, lParam);

	return AfxCallWndProc(pWnd, hWnd, nMsg, wParam, lParam);
}
LRESULT CALLBACK AfxCallWndProc(CWnd* pWnd, HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = pWnd->WindowProc(hWnd,nMsg, wParam, lParam);
	return lResult;
}
