#include "stdafx.h"
#include "inetwork.h"
#include "ServerTable.h"
#include "RMDefine.h"

/*
bool CServerTable::SendToProxyServer( char* pMsg, DWORD dwLength )
{
	LP_SERVER_DATA pProxyServer = this->m_pOwnProxyServerData[PRIMARY_SERVER];

	if( !pProxyServer || (pProxyServer->dwConnectionIndex == 0) )
	{
		pProxyServer = this->m_pOwnProxyServerData[SECONDARY_SERVER];
	}
	if( !pProxyServer || (pProxyServer->dwConnectionIndex == 0) )
	{
		return false;
	}

	return this->m_pINet->SendToServer( pProxyServer->dwConnectionIndex, pMsg, dwLength, FLAG_SEND_NOT_ENCRYPTION );
}
*/
extern void ReLoadGameServerDataByKeyInput( void );

void RMProc(DWORD dwConnectionIndex, char* pMsg, DWORD dwLength)
{
	BYTE header;
	memcpy(&header,pMsg+1, 1);

	switch(header)
	{
	case MSG_SHUT_DOWN:
		{
			//CServerTable *pVoid = NULL;
			//	pVoid->StartServer(0);
			
			g_pServerTable->DestroyServer( FINISH_TYPE_NORMAL );
		}
		break;


	case MSG_ECHO:
		{
			//Echo
			g_pINet->SendToServer(dwConnectionIndex, pMsg, dwLength, FLAG_SEND_NOT_ENCRYPTION);
		}
		break;

	}

}