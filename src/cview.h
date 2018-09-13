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

#include "cdocument.h"

namespace mfc {
	class CView :public CWnd
	{
	REGISTER(CView)
	DECLARE_MESSAGE_MAP()
	public:
		CDocument * m_pDocument;
	public:
		CView() {

		}
		~CView() {

		}

	public:
		virtual int OnCmdMsg(int nID, int nCode) {
			std::cout << "cview oncmdmsg\n";
			if (CWnd::OnCmdMsg(nID, nCode)) return 1;
			int bHandled = 0;
			bHandled = m_pDocument->OnCmdMsg(nID, nCode);
			return bHandled;
		}

	};
	REGISTER_CLASS(CView)
	IMPLEMENT_MESSAGE_MAP(CView, CWnd)
}

