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

CWinApp* AfxGetApp()
{
	std::cout << "CWinApp::AfxGetApp\n";
	return theApp.m_pCurrentWinApp;
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

IMPLEMENT_DYNAMIC(CCmdTarget,CObject)
IMPLEMENT_DYNAMIC(CWinThread,CCmdTarget)
IMPLEMENT_DYNAMIC(CWinApp,CWinThread)
IMPLEMENT_DYNAMIC(CWnd,CCmdTarget)
IMPLEMENT_DYNAMIC(CFrameWnd,CWnd)
IMPLEMENT_DYNAMIC(CDocument,CCmdTarget)
IMPLEMENT_DYNAMIC(CView,CWnd)
