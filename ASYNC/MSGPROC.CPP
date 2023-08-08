#include "msgproc.h"
#include "network.h"
#include "define.h"
#include "recvmsg.h"
#include "../MyLog.h"

//#include "..\Game.h"

void InitSocket()
{
//	WSACleanup();
//	WORD Version;
//	WSADATA wsaData;
	
//	Version = MAKEWORD(2, 2);
	//2001.01.27 zhh 디비 데몬에서 이미 초기화 한다.
//	WSAStartup(Version, &wsaData);

}
void ReleaseSocket()
{
	//2001.01.27 zhh 디비 데몬에서 해제한다..
//	WSACleanup();

}
//2001/01/28 zhh
#include "..\main.h"
HWND CreateMessageWindow(char* szName,WNDPROC func)
{
	
	WNDCLASS wndclass;
	HWND hWnd;
	HINSTANCE hInst = (HINSTANCE)GetModuleHandle(NULL);

	ZeroMemory(&wndclass,sizeof(wndclass));
	
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= (WNDPROC)func;
	wndclass.hInstance		= hInst;
	wndclass.lpszClassName	= szName;
	if(RegisterClass(&wndclass) == 0)
		return NULL;

	hWnd = CreateWindowEx(WS_EX_TOPMOST,szName,szName,WS_POPUP | WS_OVERLAPPED,0,0,100,100,NULL,NULL, hInst, NULL);
	
	return hWnd;
	
}

extern bool sw;
#include "../china/mysocket.h"
#include "../China/QueryDBSocket.h"
extern CMySocket *ConC;
extern CQueryDBSocket *ConQ;
extern HANDLE	g_hEvent;
extern CConnection* g_pConnection;
extern int InitAsync(void);
LRESULT CALLBACK MessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char buf[256] = {0,};

	CConnection* pCon = NULL;
	DWORD dwLen = 0;

	switch(message)
	{
	case WM_SOCKET_EVENT:
		switch(LOWORD(lParam))
		{
		case FD_ACCEPT:
			{
				pCon = g_pNetwork->Accepting();
				if (pCon)
					OnConnect(pCon);
			}
			break;

		case FD_READ:
			{
			//	if(!g_pNetwork)
			//		break;
			//	pCon = g_pNetwork->GetConnection(wParam);
			//	SetEvent(0);
				SetEvent(g_hEvent);
			//	ConC->OnReceive(0) ;
				/*
				pCon = g_pNetwork->GetConnection(wParam);
				if (pCon)
				{
					pCon->OnRead();
					while (pCon->DispatchMsg(&pMsg,&dwLen))
					{
						ReceivedMsg(pCon,pMsg,dwLen);
						pCon->ShiftRecv(dwLen);
					}
				}
				*/
			}
			break;

		case FD_CLOSE:
			{	
				if(!g_pNetwork)
					break;
				pCon = g_pNetwork->GetConnection(wParam);
				if (pCon)
				{
//					MessageBox(hWindow,"서버와의 연결이 끊어졌습니다","Error",MB_ICONSTOP);
//					PostQuitMessage(WM_QUIT);//020831 lsw
					OnDisconnect(pCon);
					g_pNetwork->OnCloseConnection(wParam);
					g_pConnection=NULL;
					MyLog( LOG_FATAL, "[BILL] **** Warning! Connection To Billing Server is Closed! (FD_CLOSE) ");
					InitAsync();
				}
			}
			break;

		case FD_WRITE:
			{	
				if(!g_pNetwork)
					break;
				pCon = g_pNetwork->GetConnection(wParam);				
				if (pCon)
				{
					pCon->SendFromBuffer();
				}
			}
			break;
		}
		break;
	}
	return 1;
	
	//	return DefWindowProc (hWnd, message, wParam, lParam);
}
