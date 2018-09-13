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

/**
 * Notice that message from CWinApp go to CCmdTarget directly
 */

#include "cwnd.h"

namespace mfc {
	class CWinApp :public CWinThread
	{
		REGISTER(CWinApp)
		DECLARE_MESSAGE_MAP()
	public:
		CWinApp * m_pCurrentWinApp;
		CWnd * m_pMainWnd;
	public:
		CWinApp() :m_pCurrentWinApp(this)
		{
		}
		~CWinApp() {
		}

		virtual bool InitApplication()
		{
			std::cout << __FUNCTION__ << std::endl;
			return true;
		}
		virtual bool InitInstance()
		{
			std::cout << __FUNCTION__ << std::endl;
			return true;
		}
		virtual int Run()
		{
			std::cout << __FUNCTION__ << std::endl;
			return CWinThread::Run();
		}

	private:

	};
	REGISTER_CLASS(CWinApp)
	IMPLEMENT_MESSAGE_MAP(CWinApp, CCmdTarget)
}


