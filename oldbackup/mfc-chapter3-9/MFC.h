#include"windows.h"
#include"stdio.h"

#define TRUE 1
#define FALSE 0

typedef char* LPSTR;
typedef const char* LPCSTR;

typedef char* LPSTR;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef unsigned char BYTE;
typedef int BOOL;
typedef long LONG;

typedef UINT WPARAM;
typedef LONG LPARAM;
typedef LONG LRESULT;

#define TRACE1 printf
#define AfxDeferRegisterClass(param) AfxEndDeferRegisterClass(param)

#define CObjectid 0xffff
#define CCmdTargetid 1
#define CWinThreadid 11
#define CWinAppid 111
#define CMyWinAppid 1111
#define CWndid 12
#define CFrameWndid 121
#define CMyFrameWndid 1211
#define CViewid 122
#define CMyViewid 1221
#define CDocumentid 13
#define CMyDocid 131

#ifndef AFXAPI
	#define AFXAPI __stdcall
#endif

#include<iostream>
#include "AFXMSG_.h"

class CObject;
class CCmdTarget;
class CView;
class CFrameWnd;
struct CRuntimeClass;
class CWnd;

#define RUNTIME_CLASS(class_name)((CRuntimeClass*)(&class_name::class##class_name))

#define DECLARE_DYNAMIC(class_name) \
public: \
	static CRuntimeClass class##class_name; \
	virtual CRuntimeClass* GetRuntimeClass() const;

#define DECLARE_DYNCREATE(class_name)\
	DECLARE_DYNAMIC(class_name)\
	static CObject* PASCAL CreateObject();

#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
	static char _lpsz##class_name[]=#class_name;\
	CRuntimeClass class_name::class##class_name={_lpsz##class_name,sizeof(class_name),wSchema,pfnNew,RUNTIME_CLASS(base_class_name),NULL};\
	static AFX_CLASSINIT _init_##class_name(RUNTIME_CLASS(class_name));\
	CRuntimeClass* class_name::GetRuntimeClass() const { return RUNTIME_CLASS(class_name); }


#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)

#define IMPLEMENT_DYNCREATE(class_name,base_class_name)\
	CObject* PASCAL class_name::CreateObject(){return new class_name;}\
	IMPLEMENT_RUNTIMECLASS(class_name,base_class_name,0xFFFF,class_name::CreateObject)

struct AFX_CLASSINIT
{
	AFX_CLASSINIT(CRuntimeClass* pNewClass);
};

struct CRuntimeClass
{
	// Attributes
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema; // schema number of the loaded class
	CObject* (PASCAL* m_pfnCreateObject)(); // NULL => abstract class

	// Operations
	CObject* CreateObject();
	static CRuntimeClass* PASCAL Load();


	CRuntimeClass* m_pBaseClass;
	static CRuntimeClass* pFirstClass;
	CRuntimeClass* m_pNextClass;       // linked list of registered classes
//	const AFX_CLASSINIT* m_pClassInit;
};

//Message map handling
struct AFX_MSGMAP_ENTRY;
struct AFX_MSGMAP
{
	AFX_MSGMAP* pBaseMessageMap;
	AFX_MSGMAP_ENTRY* lpEntries;
};


#define DECLARE_MESSAGE_MAP() \
	static AFX_MSGMAP_ENTRY _messageEntries[];\
	static AFX_MSGMAP messageMap;\
	virtual AFX_MSGMAP* GetMessageMap() const;

#define BEGIN_MESSAGE_MAP(theClass, baseClass) \
	AFX_MSGMAP* theClass::GetMessageMap() const { return &theClass::messageMap; } \
	AFX_MSGMAP theClass::messageMap=\
	{&(baseClass::messageMap),(AFX_MSGMAP_ENTRY*) &(theClass::_messageEntries)};\
	AFX_MSGMAP_ENTRY theClass::_messageEntries[] =  \
	{

#define ON_COMMAND(id,memberFxn){WM_COMMAND,0,(WORD)id,(WORD)id,AfxSig_vv,(AFX_PMSG)memberFxn},

#define END_MESSAGE_MAP() \
		{0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0 } \
	};


// Message map signature values and macros in separate header

//Message map handling
class CObject
{
public:
	CObject::CObject(){}
	CObject::~CObject(){}
public:
	static CRuntimeClass classCObject;
public:
	virtual CRuntimeClass* GetRuntimeClass()const;
	BOOL IsKindOf(const CRuntimeClass* pClass)const;
};

class CCmdTarget:public CObject
{
	DECLARE_DYNAMIC(CCmdTarget)
public:
	CCmdTarget::CCmdTarget(){}
	CCmdTarget::~CCmdTarget(){}
public:
	virtual BOOL InitInstance()
	{
		std::cout << "CCmdTarget::InitInstance\n";
		return TRUE;
	}
	virtual int Run()
	{
		std::cout << "CCmdTarget::Run\n";
		return 1;
	}
	virtual BOOL OnCmdMsg(UINT nID, int nCode);
	DECLARE_MESSAGE_MAP()
};

typedef void(CCmdTarget::*AFX_PMSG)(void);
struct AFX_MSGMAP_ENTRY
{
	UINT nMessage;   // windows message
	UINT nCode;      // control code or WM_NOTIFY code
	UINT nID;        // control ID (or 0 for windows messages)
	UINT nLastID;    // used for entries specifying a range of control id's
	UINT nSig;       // signature type (action) or pointer to message #
	AFX_PMSG pfn;    // routine to call (or special value)
};

class CWinThread:public CCmdTarget
{
public:
	CWnd* m_pMainWnd;
	CWnd* m_pActiveWnd;
	MSG m_msgCur;
protected:
	DECLARE_DYNAMIC(CWinThread)
public:
	CWinThread::CWinThread(){}
	CWinThread::~CWinThread(){}
public:
	virtual BOOL InitInstance()
	{
		std::cout << "CWinThread::InitInstance\n";
		return TRUE;
	}
	BOOL PumpMessage()
	{
		::TranslateMessage(&m_msgCur);
		::DispatchMessage(&m_msgCur);
		return TRUE;
	}
	int ExitInstance()
	{
		int nResult = m_msgCur.wParam;  // returns the value from PostQuitMessage
		return nResult;
	}
	virtual int Run()
	{
	/*	while (::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))
		{
			if (!PumpMessage())
				return ExitInstance();
		}
		return 1;*/
		while (GetMessage(&m_msgCur, NULL, 0, 0))
		{
			if (!PumpMessage())
				return ExitInstance();
		}
		return 1;
	}

};
class CWnd;
typedef void(CWnd::*AFX_PMSGW)(void);
class CWnd:public CCmdTarget
{
public:
	HWND m_hWnd;
	DECLARE_DYNCREATE(CWnd)
public:
	CWnd::CWnd(){}
	CWnd::~CWnd(){}
public:
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID);

	BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		int x, int y, int nWidth, int nHeight,
		HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam);

	virtual BOOL PreCreateWindow(WNDCLASS* wndcls);
	virtual void ShowWindow(int nCmdShow);
	virtual void UpdateWindow();
	LRESULT CALLBACK WindowProc(HWND hWnd,UINT nMsg, WPARAM wParam, LPARAM lParam);
	BOOL CWnd::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	LRESULT DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);
	BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

class CDocument :public CCmdTarget
{
	DECLARE_DYNAMIC(CDocument)
public:
	CDocument::CDocument(){ std::cout << "CDocument Constructor\n"; }
	CDocument::~CDocument(){ std::cout << "CDocument Destructor\n"; }
public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode);

	DECLARE_MESSAGE_MAP()
};

class CFrameWnd:public CWnd
{
	DECLARE_DYNCREATE(CFrameWnd)
public:
	CView* m_pViewActive;
public:
	CFrameWnd(){ Create("Hello", "hai", WS_OVERLAPPEDWINDOW, NULL, CS_HREDRAW | CS_VREDRAW); }
	~CFrameWnd(){}
public:
	CView* GetActiveView() const;
	BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName,
		DWORD dwStyle,
		LPCTSTR lpszMenuName,
		DWORD dwExStyle);//virtual is removed
	virtual BOOL PreCreateWindow(WNDCLASS* wndcls);
public:
	virtual void ShowWindow(int nCmdShow);
	virtual void UpdateWindow();

	virtual BOOL OnCmdMsg(UINT nID, int nCode);
	BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
	friend CView;//友元类的使用
};
class CWinApp:public CWinThread
{
public:
	HINSTANCE m_hInstance;
	HINSTANCE m_hPrevInstance;
	LPTSTR m_lpCmdLine;
	int m_nCmdShow;

	DECLARE_DYNAMIC(CWinApp)
public:
	CWinApp* m_pCurrentWinApp;
public:
	CWinApp::CWinApp()
	{ 
		m_pCurrentWinApp = this;
	}
	CWinApp::~CWinApp(){ std::cout << "CWinApp Destructor\n"; }
public:
	virtual BOOL InitApplication()
	{
		return TRUE;
	}
	virtual BOOL InitInstance()
	{
		m_pMainWnd = new CFrameWnd;
		m_pMainWnd->ShowWindow(m_nCmdShow);
		m_pMainWnd->UpdateWindow();
		return TRUE;
	}
	virtual int Run()
	{
		return CWinThread::Run();
	}
	DECLARE_MESSAGE_MAP()
};


class CView:public CWnd
{
	DECLARE_DYNAMIC(CView)
public:
	CDocument* m_pDocument;
public:
	CView::CView(){ std::cout << "CView Constructor\n"; }
	CView::~CView(){ std::cout << "CView Destructor\n"; }

public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode);

	DECLARE_MESSAGE_MAP()
	friend CFrameWnd;
};

//global function

CWinApp* AfxGetApp();
LRESULT CALLBACK AfxWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AfxCallWndProc(CWnd* pWnd, HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
HINSTANCE AFXAPI AfxGetInstanceHandle();

BOOL AFXAPI AfxRegisterClass(WNDCLASS* lpWndClass);
BOOL AFXAPI AfxEndDeferRegisterClass(WNDCLASS* wndcls);

BOOL AFXAPI AfxWinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow);
int AFXAPI AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);
//general class
class CArchive
{
	CArchive::CArchive(){ std::cout << "CArchive Constructor"; }
	CArchive::~CArchive(){ std::cout << "CArchive Destructor"; }
};