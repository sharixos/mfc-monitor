#pragma once

namespace mfc {
	class CCmdTarget;
	typedef void(CCmdTarget::*AFX_PMSG)(void);
	struct AFX_MSGMAP_ENTRY
	{
		int nMessage;   // windows message
		int nCode;      // control code or WM_NOTIFY code
		int nID;        // control ID (or 0 for windows messages)
		int nLastID;    // used for entries specifying a range of control id's
		int nSig;       // signature type (action) or pointer to message #
		AFX_PMSG pfn;    // routine to call (or special value)
	};

	//Message map handling
	struct AFX_MSGMAP_ENTRY;
	struct AFX_MSGMAP
	{
		AFX_MSGMAP* pBaseMessageMap;
		std::vector<AFX_MSGMAP_ENTRY> * pMessageEntries;
	};

	enum AfxSig
	{
		AfxSig_end = 0,
		AfxSig_vv,
	};
}
