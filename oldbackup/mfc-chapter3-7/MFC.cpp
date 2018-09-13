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
