#pragma once


/**
* CObject
* |__ CCmdTarget
*		|__ CWinThread
*		|	|__ CWinApp
*		|		|__ CMyWinApp
*		|__ CWnd
*		|	|__ CView
*		|	|	|__ CMyView
*		|	|__ CFrameWnd
*		|		|__ CMyFrameWnd
*		|__ CDocument
*				|__ CMyDoc
*/
#include "global.h"

namespace mfc {
	class CFrameWnd :public CWnd
	{
	REGISTER(CFrameWnd)
	DECLARE_MESSAGE_MAP()
	public:
		CView *m_pViewActive;
	public:
		CFrameWnd() {}
		~CFrameWnd() {}

	private:

	public:
		virtual bool Create() {
			CreateEx();
			return true;
		}

		virtual bool CreateEx() {
			PreCreateWindow();
			return true;
		}

		virtual bool PreCreateWindow() {
			return true;
		}

		CView * GetActiveView() const {
			return m_pViewActive;
		}

		virtual int OnCmdMsg(int nID, int nCode) {

			std::cout << "cframewnd oncmdmsg\n";

			CView *pView = GetActiveView();

			if (pView->OnCmdMsg(nID, nCode)) return 1;

			if (CWnd::OnCmdMsg(nID, nCode)) return 1;

			CWinApp *pApp = AfxGetApp();
			if (pApp->OnCmdMsg(nID, nCode)) return 1;

			return 0;
		}

		virtual int OnCommand(int wParam, int lParam) {
			std::cout << "cframewnd oncmd\n";
			return CWnd::OnCommand(wParam, lParam);
		}
	};

	REGISTER_CLASS(CFrameWnd)
	IMPLEMENT_MESSAGE_MAP(CFrameWnd, CWnd)
}

