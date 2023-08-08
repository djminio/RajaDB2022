#ifndef MSG_PROC_H
#define MSG_PROC_H

//#include <winsock2.h>
#include "stdafx.h"

LRESULT CALLBACK MessageProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam);
HWND CreateMessageWindow(char* szName,WNDPROC func = MessageProc);
void InitSocket();
void ReleaseSocket();

#endif
