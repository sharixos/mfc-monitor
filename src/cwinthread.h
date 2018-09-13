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
 * Notice that CWinThread do not join the message map route
 * message from CWinApp will go to CCmdTarget directly
 */

namespace mfc {
	class CWinThread :public CCmdTarget
	{
		REGISTER(CWinThread)

	public:
		CWinThread() {}
		~CWinThread() {}

	private:

	public:
		virtual int Run() {
			std::cout << __FUNCTION__ << std::endl;
			return 1;
		}
	};
	REGISTER_CLASS(CWinThread)

}



