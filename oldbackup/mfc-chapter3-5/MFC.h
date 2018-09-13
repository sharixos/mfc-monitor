#define BOOL int
#define TRUE 1
#define FALSE 0
#define LPCSTR LPSTR
#define LPCWSTR LPSTR
typedef char* LPSTR;
#define UINT int
#define PASCAL _stdcall
#define TRACE1 printf

#ifndef AFXAPI
	#define AFXAPI __stdcall
#endif

#include<iostream>
class CObject;
struct CRuntimeClass;

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

//void AFXAPI AfxClassInit(CRuntimeClass* pNewClass);
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


class CObject
{
public:
	CObject::CObject(){ std::cout << "CObject Constructor\n"; }
	CObject::~CObject(){ 
		std::cout << "CObject Destructor\n"; 
		system("pause");
	}
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
	CCmdTarget::CCmdTarget(){ std::cout << "CCmdTarget Constructor\n"; }
	CCmdTarget::~CCmdTarget(){ std::cout << "CCmdTarget Destructor\n"; }
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
};

class CWinThread:public CCmdTarget
{
	DECLARE_DYNAMIC(CWinThread)
public:
	CWinThread::CWinThread(){ std::cout << "CWinThread Constructor\n"; }
	CWinThread::~CWinThread(){ std::cout << "CWinThread Destructor\n"; }
public:
	virtual BOOL InitInstance()
	{
		std::cout << "CWinThread::InitInstance\n";
		return TRUE;
	}
	virtual int Run()
	{
		std::cout << "CWinThread::Run\n";
		return 1;
	}

};

class CWnd:public CCmdTarget
{
	DECLARE_DYNCREATE(CWnd)
public:
	CWnd::CWnd(){ std::cout << "CWnd Constructor\n"; }
	CWnd::~CWnd(){ std::cout << "CWnd Destructor\n"; }
public:
	virtual BOOL Create();
	BOOL CreateEx();
	virtual BOOL PreCreateWindow();
};

class CDocument :public CCmdTarget
{
	DECLARE_DYNAMIC(CDocument)
public:
	CDocument::CDocument(){ std::cout << "CDocument Constructor\n"; }
	CDocument::~CDocument(){ std::cout << "CDocument Destructor\n"; }
};
class CWinApp:public CWinThread
{
	DECLARE_DYNAMIC(CWinApp)
public:
	CWinApp* m_pCurrentWinApp;
	CWnd* m_pMainWnd;
public:
	CWinApp::CWinApp()
	{ 
		std::cout << "CWinApp Constructor\n"; 
		m_pCurrentWinApp = this;
	}
	CWinApp::~CWinApp(){ std::cout << "CWinApp Destructor\n"; }
public:
	virtual BOOL InitApplication()
	{
		std::cout << "CWinApp::InitApplication\n";
		return TRUE;
	}
	virtual BOOL InitInstance()
	{
		std::cout << "CWinApp::InitInstance\n";
		return TRUE;
	}
	virtual int Run()
	{
		std::cout << "CWinApp::Run\n";
		return CWinThread::Run();
	}
};

class CFrameWnd:public CWnd
{
	DECLARE_DYNCREATE(CFrameWnd)
public:
	CFrameWnd::CFrameWnd(){ std::cout << "CFrameWnd Constructor\n"; }
	CFrameWnd::~CFrameWnd(){ std::cout << "CFrameWnd Destructor\n"; }
public:
	BOOL Create();//virtual is removed
	virtual BOOL PreCreateWindow();
};

class CView:public CWnd
{
	DECLARE_DYNAMIC(CView)
public:
	CView::CView(){ std::cout << "CView Constructor\n"; }
	CView::~CView(){ std::cout << "CView Destructor\n"; }

public:

};

//global function

CWinApp* AfxGetApp();

//general class
class CArchive
{
	CArchive::CArchive(){ std::cout << "CArchive Constructor"; }
	CArchive::~CArchive(){ std::cout << "CArchive Destructor"; }
};