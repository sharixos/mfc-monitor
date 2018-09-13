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
 * CCmdTarget: virtual OnCmdMsg => wm_proc
 * 		CWnd: OnCommand => OnCmdMsg [will be CCmdTarget:OnCmdMsg]
 * 			CFrameWnd: OnCmdMsg => pView->OnCmdMsg
 * 					 			=> CWnd::OnCmdMsg
 * 								=> pApp->OnCmdMsg
 * 			CView: OnCmdMsg => CWnd::OnCmdMsg
 * 							=> pDocument->OnCmdMsg
 * 			CDocument: OnCmdMsg => CCmdTarget::OnCmdMsg
 */


#include "message.h"

namespace mfc {


	class CCmdTarget :public CObject
	{
		REGISTER(CCmdTarget)
		DECLARE_MESSAGE_MAP()
	public:
		CCmdTarget() {}
		~CCmdTarget() {}
	public:
		int wm_proc(AFX_MSGMAP *pMessageMap) {
			for (;pMessageMap != 0; pMessageMap = pMessageMap->pBaseMessageMap) {
				std::cout << "---***---" << std::endl;
				for (AFX_MSGMAP_ENTRY i : *(pMessageMap->pMessageEntries)) {
					std::cout << i.nMessage << " " << i.nCode << " " << i.nID << " " << i.nLastID << " " << i.nSig << " " << i.pfn << std::endl;
				}
			}
			return 1;
		}

		virtual int OnCmdMsg(int nID, int nCode) {
			std::cout << "ccmdtarget oncmdmsg\n";
			wm_proc(GetMessageMap());
			return 0;
		}

	};
	REGISTER_CLASS(CCmdTarget)

	AFX_MSGMAP* CCmdTarget::GetMessageMap() const
	{
		return &CCmdTarget::messageMap;
	}

	AFX_MSGMAP CCmdTarget::messageMap =
	{
		NULL,
		&CCmdTarget::messageEntries
	};

	std::vector<AFX_MSGMAP_ENTRY> CCmdTarget::messageEntries =
	{
		{ 0,0,0,0,0,0 }
	};


} 

	

