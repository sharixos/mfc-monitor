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
	class CDocument :public CCmdTarget
	{
	REGISTER(CDocument)
	DECLARE_MESSAGE_MAP()
	public:
		CDocument() {
		}
		~CDocument() {}

	public:
		virtual int OnCmdMsg(int nID, int nCode) {
			std::cout << "cdocument oncmdmsg\n";
			if ((CCmdTarget::OnCmdMsg(nID, nCode))) return 1;
			return 0;
		}

	};
	REGISTER_CLASS(CDocument)
	IMPLEMENT_MESSAGE_MAP(CDocument, CCmdTarget)
}


