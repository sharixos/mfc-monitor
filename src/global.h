#pragma once

#include "cwinapp.h"

namespace mfc {
	static CWinApp *pApp;
	
	static CWinApp * AfxGetApp() {
		return ((CWinApp *)pApp)->m_pCurrentWinApp;
	}

	int AfxCallWndProc(CWnd *pWnd, int hWnd, int nMsg, int wParam, int lParam) {
		int result = pWnd->WindowProc(nMsg, wParam, lParam);
		return result;
	}

	int AfxWndProc(int hWnd, int nMsg,int wParam, int lParam, CWnd* pWnd) {
		return AfxCallWndProc(pWnd, hWnd, nMsg, wParam, lParam);
	}



}