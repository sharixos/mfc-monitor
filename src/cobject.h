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
	class CObject
	{
	private:
		const std::string name = "CObject";
	public:
		virtual std::string get_name() { return name; }
	public:
		CObject() {}
		~CObject() {
			system("pause");
		}

	};

	REGISTER_CLASS(CObject)

}

