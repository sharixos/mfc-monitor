#pragma once

#include "mfc.h"
using namespace mfc;



//mfc::CWinApp* AfxGetApp()
//{
//	return (mfc::CWinApp*)(pApp->m_pCurrentWinApp);
//}


class CMyWinApp:public mfc::CWinApp
{
	REGISTER(CMyWinApp)
	public:
		CMyWinApp::CMyWinApp() {}
		CMyWinApp::~CMyWinApp(){}

	public:
		virtual bool InitInstance();
		DECLARE_MESSAGE_MAP()
};
IMPLEMENT_MESSAGE_MAP(CMyWinApp, CWinApp)


 class CMyFrameWnd :public mfc::CFrameWnd
 {
	 REGISTER(CMyFrameWnd)
	 public:
 		CMyFrameWnd::CMyFrameWnd(){ 
			Create();
		}
 		CMyFrameWnd::~CMyFrameWnd(){}
		DECLARE_MESSAGE_MAP()
 };
IMPLEMENT_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)

 class CMyView :public mfc::CView
 {
	 REGISTER(CMyView)
 public:
	 CMyView() {

	 }
	 ~CMyView() {}

	 DECLARE_MESSAGE_MAP()
 };
IMPLEMENT_MESSAGE_MAP(CMyView, CView)

 class CMyDoc:public mfc::CDocument 
 {
	 REGISTER(CMyDoc)
 public:
	 CMyDoc()
	 {

	 }

	 ~CMyDoc()
	 {
	 }

	 DECLARE_MESSAGE_MAP()
 };
IMPLEMENT_MESSAGE_MAP(CMyDoc, CDocument)
