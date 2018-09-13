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

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "define.h"
#include "tools.h"

#include "cobject.h"
#include "ccmdtarget.h"

#include "cwinthread.h"
#include "cwinapp.h"

#include "cwnd.h"
#include "cview.h"
#include "cframewnd.h"

#include "cdocument.h"

#include "message.h"
	
