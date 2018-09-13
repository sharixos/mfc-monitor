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


namespace mfc {
	class CWnd :public CCmdTarget
	{
	REGISTER(CWnd)
	DECLARE_MESSAGE_MAP()
	public:
		CWnd() {}
		~CWnd() {}

	public:
		int WindowProc(int nMsg, int wParam, int lParam) {
			
			if (nMsg == WM_COMMAND)
			{
				if (OnCommand(wParam, lParam))
					return 1;
				else
					return DefWindowProc(nMsg, wParam, lParam);
			}
			wm_proc(GetMessageMap());
			return 0;
		}

		int DefWindowProc(int nMsg, int wParam, int lParam) {
			return 1;
		}

		virtual int OnCommand(int wParam, int lParam) {
			std::cout << "cwnd oncmd\n";
			return OnCmdMsg(0, 0);
		}

	};
	REGISTER_CLASS(CWnd)
	IMPLEMENT_MESSAGE_MAP(CWnd, CCmdTarget)
}



