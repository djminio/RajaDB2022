#include "struct.h"
#include "servertable.h"
#include "recvmsg.h"
#include "packed.h"
#include "network_base.h"
#include "monitor.h"
#include <sqltypes.h>
#include "network.h"
#include "mainheader.h"
#include "mylog.h"
#include "pay.h"
#include "DrServerManager.h"


//2001/02/19 zhh
#include "./China/QueryDBSocket.h"
extern CQueryDBSocket *ConQ;

// 011205 KBS
extern void RMProc(DWORD dwConnectionIndex, char* pMsg, DWORD dwLength);

void SendUserOutMsg(DWORD dwConnectionIndex);
bool Login(DWORD dwConnectionIndex,char* msg);
void __stdcall OnAcceptUser(DWORD dwConnectionIndex);
void __stdcall OnAcceptServer(DWORD dwConnectionIndex);

void __stdcall OnAcceptUser(DWORD dwConnectionIndex)
{
//	WriteText("user connected");
}			


void __stdcall OnAcceptServer(DWORD dwConnectionIndex)
{
//	WriteText("server connected");
}

int GetUserCN( LP_SERVER_DATA pServer, DWORD dwUniqID, short int MsgID)
{			
	if (dwUniqID == 0)
	{
		return 0;
	}

	IDCN* pCN;
			
	if (CMD_ACCESS_LOGIN == MsgID)
	{			
		pCN = pServer->dwUSERCN;
		for (int i = 0; i<MAX_USER_NUM; i++)
		{		
			if ((pCN+i)->dwUserID == dwUniqID)
			{	
				return (pCN+i)->cn;// 이미 접속한 놈이라면.
			}	
		}		
		for (int k = DRAGON_CONNECTIONS_START; k <MAX_USER_NUM; k++)
		{		
			if (connections[k].bUse == 0)
			{	
				connections[k].bUse = 1;
				
				for (int i =0; i<MAX_USER_NUM;i++)
				{
					if ((pCN+i)->dwUserID == 0)
					{
						(pCN+i)->dwUserID = dwUniqID;
						(pCN+i)->cn = k;
						return k;
					}
				}
			}
		}		
		MyLog( LOG_FATAL, "Error: OVERFLOW USER CN");
	}			
	else //아직 로긴관련 나머지 메세지
	{		
		pCN = pServer->dwUSERCN;
		for (int i = 0; i<MAX_USER_NUM;i++)
		{	
			if ((pCN+i)->dwUserID == dwUniqID)
				return (pCN+i)->cn;
		}	
	}	
	
	MyLog( LOG_NORMAL, "Error: USERID = %d, MsgID %d", dwUniqID, MsgID );
	return 0;
}

void ClearUserCN( DWORD dwConnectionIndex, char* pMsg, DWORD dwLength)
{
	DWORD	dwUserID;
	memcpy(&dwUserID,pMsg+1,4);

	LP_SERVER_DATA pServer = g_pServerTable->GetServerData(dwConnectionIndex);
	if (!pServer)
	{
		MyLog(0,"ERROR : NULL SERVER INDEX %d",dwConnectionIndex);
		return;
	}
	IDCN* pCN;
	pCN = pServer->dwUSERCN;
	for (int i =0; i<MAX_USER_NUM;i++)
	{
		if ((pCN+i)->dwUserID == dwUserID)
		{	//001211 zhh 			
			connections[(pCN+i)->cn].bUse = 0;
			memset(connections+(pCN+i)->cn,0,sizeof(t_connection));
			(pCN+i)->cn = 0;
			(pCN+i)->dwUserID = 0;
		}
	}
}

void __stdcall ReceivedMsgServer(DWORD dwConnectionIndex,char* pMsg,DWORD dwLength)
{
	EXCEPTION_POINTERS* pException = NULL;//020508 lsw
	__try	//020508 lsw
	{

		BYTE bID;
		bID = (BYTE)pMsg[0];

		if (dwConnectionIndex == 0)
		{
	#ifdef __ON_DEBUG
	//		_asm int 3;
	#endif
			return;
		}

		if( bID == (BYTE)PTCL_NOTIFY_SERVER_UP )
		{
			if( g_pServerTable->OnRecvServerUpMsg(dwConnectionIndex, *(WORD*)(pMsg+1)) )
			{
	#ifdef __ON_DEBUG
	//			_asm int 3;
	#endif
			}
			return;
		}

		LP_SERVER_DATA pSender = g_pServerTable->GetConnectedServerData( dwConnectionIndex );

		if( !pSender ) return;

		switch (bID)
		{
		// -------------
		// 기본패킷 
		// -------------
		// 전용
		case PTCL_ORDER_SET_SERVER_LIST:
		case PTCL_ORDER_CONNECT_TO_SERVERS:
		case PTCL_ORDER_SET_DB_DEMON:
		case PTCL_ORDER_TO_REPORT_SERVER_DATAS:
		case PTCL_NOTIFY_YOU_ARE_CERTIFIED:

		//공통
		case PTCL_ORDER_DESTROY_SERVER:
		case PTCL_NOTIFY_SERVER_STATUS:
		case PTCL_SERVER_TRY_TO_CHECK_CONNECTION:
		case PTCL_SERVER_CONNECTION_OK:
		case PTCL_ORDER_TO_REPORT_SERVER_STATUS:
			{
				if( !g_pServerTable->OnRecvNegotiationMsgs( pSender, bID, pMsg+1, dwLength-1 ) )
				{
					MyLog( LOG_FATAL, "OnRecvNegotiationMsg() Failed :: (pSender(%d), bId(%d), MsgLength(%d))", pSender->wPort, bID, dwLength );
	#ifdef __ON_DEBUG
	//				_asm int 3;
	#endif
				}
			}
			break;
		case PTCL_AGENT_TO_DB_REMOVE_USER_FROM_LOGIN_TABLE:
			{
				char id[20];
				memset(id,0,20);
				memcpy(id,pMsg+4+1,20);
				if(LocalMgr.IsAbleNation(TAIWAN|CHINA|HONGKONG))//021007 lsw
				{
					//2001/02/24 zhh
					if(dwLength>1+4+ID_LENGTH+2+15)
					{
					char in[15],out[15];
					memset(in,0,15);
					memset(out,0,15);
					memcpy(out,pMsg+1+4+ID_LENGTH+2, 15);
					memcpy(in ,pMsg+1+4+ID_LENGTH+2+15, 15);

					//2001/08/30 zhh
					char IP[IP_LENGTH]={0,};
					memcpy(IP ,pMsg+1+4+ID_LENGTH+2+15+15, IP_LENGTH);


					//2001/02/19 zhh
					for(int i=0;i<14;i++)
					{
						if(out[i]==' ')	out[i]='0';
						if( in[i]==' ')	 in[i]='0';
					}
					// acer5
					if(ConQ && out[0]!=0 && in[0]!=0)
						ConQ->AskCheckLogoutWithIP(id,in,out,IP);
					}
				}

				//001218 zhh
				int ret = onepass.DeleteUsedID_SQL_ForPay(NULL,id,0);
				if( ret != 1 )
				{
					MyLog( LOG_NORMAL, "<zoung>%d %s close ret = %d(1 = success)", dwConnectionIndex, id, ret);
				}
			}
			break;
		case PTCL_AGENT_TO_DB_REQUEST_REMOVE_USER:
			{
				ClearUserCN(dwConnectionIndex,pMsg,dwLength);
			}
			break;
		case PTCL_AGENT_TO_DB:
		case PTCL_MAP_TO_DB:
			{
				DWORD dwUniqID;
				t_packet raja_packet;
				memset(&raja_packet,0,sizeof(t_packet));
				memcpy(&dwUniqID, pMsg+1, 4);
				memcpy(raja_packet.h.data, pMsg+1+4, HEADER_SIZE);
				memcpy(raja_packet.u.data, pMsg+1+4+HEADER_SIZE, raja_packet.h.header.size);
			
				DWORD cn = GetUserCN( pSender, dwUniqID, raja_packet.h.header.type );
				//if( cn == -1 ) break;
				///////////////////////////////////////////////////////////////////////////
				
				connections[cn].dwUserID = dwUniqID;
				connections[cn].dwConIndex = dwConnectionIndex;

				//sprintf(txt,"cn: %d USERID %d Index %d",cn, dwUniqID,dwConnectionIndex);
				//WriteText(txt);

				HandleCommand( connections, dwConnectionIndex, &raja_packet ,dwUniqID,cn );
			}
			break;





		// Added by chan78 at 2000/12/17
		case PTCL_ORDER_TO_CLEAR_PAY_TABLE:
			{
				onepass.DeleteUsedID_SQL_ForPay(NULL," ", (int)*(WORD*)(pMsg+1));
			}
			break;
		// Added by chan78 at 2001/03/16
		// -----------------------------
		case PTCL_MANAGER_QUERY:
			{
				if( !OnRecvMsgFromManager( (LP_MANAGER_PACKET)pMsg, dwLength ) )
				{
					MyLog( LOG_FATAL, "PTCL_MANAGER_ANSWER :: OnRecvMsgFromManager() has return false(%d)", pSender->wPort );
					break;
				}
			}
			break;
		// Added by chan78 at 2001/03/16
		case PTCL_MANAGER_ANSWER:
			{
				// 있을 수 없다.
				MyLog( LOG_FATAL, "PTCL_MANAGER_ANSWER :: has received!!!(%d)", pSender->wPort );
				g_pServerTable->DestroyServer( FINISH_TYPE_UNKNOWN_ERROR);
			}
			break;
		// -----------------------------

		// Added by KBS 011012
		case PTCL_RM_FROM_PROXY:
			{
				RMProc(dwConnectionIndex, pMsg, dwLength);
			}
			break;
		//

		default:
			{
				MyLog( LOG_FATAL, "Unknown bID(%d) Received. From %s(wPort:%d) Size(%d) ConnectionID(%d)", bID, GetTypedServerText(pSender->dwServerType), pSender->wPort, dwLength, dwConnectionIndex);
	#ifdef __ON_DEBUG
	//			_asm int 3;
	#endif
			}
			break;
			
		}
	}
	__except(reinterpret_cast<int>(pException = GetExceptionInformation()))//020508 lsw
	{
		//acer7
		DumpException( pException, "Exception Raised on HadleCommand()", pMsg, dwLength );
		ProcessEnd(FINISH_TYPE_UNKNOWN_ERROR);
	}
}
void __stdcall ReceivedMsgUser(DWORD dwConnectionIndex,char* pMsg,DWORD dwLength)
{
}

void __stdcall OnDisconnectUser(DWORD dwConnectionIndex)
{
}

void __stdcall OnDisconnectServer(DWORD dwConnectionIndex)
{
	LP_SERVER_DATA pDisconnectedServer = g_pServerTable->GetServerData( dwConnectionIndex );

	if( pDisconnectedServer)
	{
		MyLog( LOG_NORMAL, "Server(%s:%d) Disconnected", GetTypedServerText(pDisconnectedServer->dwServerType), pDisconnectedServer->wPort );
	}
	else
	{
		MyLog( LOG_NORMAL, "Not Certified Server Connection(%d) Has Disconnected", dwConnectionIndex );
	}

	g_pServerTable->RemoveConnectedServerDataFromHashTable( dwConnectionIndex );
	return;
}					



