#include <afx.h>
//#include "..\Game.h"
//#include "..\SprObject.h"
//#include "..\ObjectManager.h"

#include "recvmsg.h"
#include "network.h"
#include "struct.h"
#include "Async.h"
#include "..\monitor.h"

//#include "monitor.h"

//char txt[128];

void ReceivedMsg(CConnection* con,char* msg,DWORD length)
{
	BYTE wID = msg[0];

	
	switch(wID)
	{
	case MSG_CHAT_BROADCAST:
		{
			char dis[200];
			memset(dis,0,200);
			memcpy(dis,msg+5 , msg[4]);
			MessageBox(NULL,"haha",dis,NULL);
			WriteText(msg);
		}
		break;
	default:
		{		
			WriteText(msg+1);
		}
		break;
	}
	
}
void OnDisconnect(CConnection* pCon)
{
	// 접속이 끊겼을때 자동 호출되는 함수
//	wsprintf(txt,"On Connect");

}
void OnConnect(CConnection* pCon)
{
	// 접속되었을때 자동 호출되는 함수	
//	wsprintf(txt,"On Disconnect");
}
