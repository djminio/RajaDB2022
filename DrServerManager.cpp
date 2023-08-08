// -----------------------------
// Wrote by chan78 at 2001/03/16
// -----------------------------
#include "DrServerManager.h"

#ifdef __IS_PROXY_SERVER
bool AnswerToManager( LP_MANAGER_PACKET pPacket, DWORD dwLength )
{
	pPacket->h.bPTCL = PTCL_MANAGER_ANSWER;

	return g_pUserTable->SendToUser( pPacket->h.uTarget.dwTargetManagerID, (char *)pPacket, dwLength );
}
#else
bool AnswerToManager( LP_MANAGER_PACKET pPacket, DWORD dwLength )
{
	pPacket->h.bPTCL = PTCL_MANAGER_ANSWER;

	// ����μ� ������ ������ �ϳ����̹Ƿ�.
	return g_pServerTable->SendToProxyServer( (char*)pPacket, dwLength );
}
#endif

// -------------------------------------------------------------------
// PROXY SERVER ��
// -------------------------------------------------------------------
#ifdef __IS_PROXY_SERVER
bool OnRecvAuthMsgFromManager( USERINFO *pUserInfo, LP_MANAGER_PACKET pPacket, DWORD dwLength )
{
	if( dwLength != sizeof( MGR_REQUEST_AUTH_PACKET ) )
	{
		return false;
	}
	if( pPacket->h.bPTCL != PTCL_MANAGER_QUERY )
	{
		return false;
	}
	if( pPacket->h.wCMD != MANAGER_CMD_AUTH )
	{
		return false;
	}
	if( pPacket->h.uTarget.wTargetServerID != g_pServerTable->GetOwnServerData()->wPort )
	{
		return false;
	}
	if( strcmp(pPacket->b.myMgrRequestAuthPacket.szID, MANAGER_ID) )
	{
		return false;
	}
	if( strcmp(pPacket->b.myMgrRequestAuthPacket.szPasswd, MANAGER_PASSWD) )
	{
		return false;
	}
	return true ;
}
bool OnRecvMsgFromManager( USERINFO *pUserInfo, LP_MANAGER_PACKET pPacket, DWORD dwLength )
{
	char szSendMsg[MM_MAX_PACKET_SIZE];
	LP_MANAGER_PACKET pSendPacket = (LP_MANAGER_PACKET)szSendMsg;

	// �̸� ä���д�. Answer ��.
	pSendPacket->h.bPTCL = PTCL_MANAGER_ANSWER;
	pSendPacket->h.uTarget.dwTargetManagerID = pUserInfo->dwID;

	// PROXY SERVER �� ��쿣 �� �Լ��� �Ѱ��� ��Ŷ�� Ÿ���� ���� �ƴҼ��� �ִ�.
	// �ٸ� ������ �����̷���.
	if( pPacket->h.uTarget.wTargetServerID != g_pServerTable->GetOwnServerData()->wPort )
	{
		// ���� ó���� ��Ŷ�� �ƴϴ�. Redirection.
		LP_SERVER_DATA pServerData = g_pServerTable->GetServerData( pPacket->h.uTarget.wTargetServerID );

		// Ÿ�� ������ ���ų� ���ӵǾ����� �ʴ�.
		if( !pServerData || !pServerData->dwConnectionIndex )
		{
			if( !AnswerToManager( pSendPacket, sizeof(MANAGER_PACKET_HEADER) ) )
			{
				MyLog( LOG_IMPORTANT, "MANAGER_CMD_TARGET_NOT_AVAILABLE :: Failed To Answer(dwID: %d, TargetServer:%d)", pUserInfo->dwID, pPacket->h.uTarget );
				return true;
			}
		}

		if( !g_pServerTable->Send( pServerData->dwConnectionIndex, (char *)pPacket, dwLength ) )
		{
			MyLog( LOG_IMPORTANT, "Failed To Send 'PTCL_MANAGER_QUERY' to (%d/Port:%d)", pServerData->dwConnectionIndex, pServerData->wPort );
		}
		return true;
	}

	// PROXY�� ���� ó���� �͵�.
	switch( pPacket->h.wCMD )
	{
	case MANAGER_CMD_REQUEST_SERVER_STATUS:
		{
			pSendPacket->b.myMgrServerStatusPacket.dwNumOfUsers = g_pUserTable->GetUserNum();
			pSendPacket->b.myMgrServerStatusPacket.dwTotalServerConnections = g_pServerTable->GetNumOfConnectedServers();
			pSendPacket->b.myMgrServerStatusPacket.dwStatus = g_pServerTable->GetOwnServerData()->dwStatus;
			sprintf( pSendPacket->b.myMgrServerStatusPacket.szServerName, "PROXY SERVER(%d)", g_pServerTable->GetOwnServerData()->wPort );

			if( !AnswerToManager( pSendPacket, (sizeof(MANAGER_PACKET_HEADER) + sizeof(MGR_SERVER_STATUS_PACKET)) ) )
			{
				MyLog( LOG_NORMAL, "MANAGER_CMD_REQUEST_SERVER_STATUS :: Failed To Answer" );
				break;
			}
		}
		break;
	default:
		{
			return false;
		}
	}
	return true;
}
#endif


// -------------------------------------------------------------------
// Agent SERVER ��
// -------------------------------------------------------------------
#ifdef __IS_AGENT_SERVER
bool OnRecvMsgFromManager( LP_MANAGER_PACKET pPacket, DWORD dwLength )
{
	char szSendMsg[MM_MAX_PACKET_SIZE];
	LP_MANAGER_PACKET pSendPacket = (LP_MANAGER_PACKET)szSendMsg;

	// �̸� ä���д�. Answer ��.
	pSendPacket->h.bPTCL = PTCL_MANAGER_ANSWER;
	pSendPacket->h.uTarget.dwTargetManagerID = pPacket->h.uTarget.dwTargetManagerID;

	switch( pPacket->h.wCMD )
	{
	case MANAGER_CMD_REQUEST_SERVER_STATUS:
		{
			pSendPacket->b.myMgrServerStatusPacket.dwNumOfUsers = g_pUserTable->GetUserNum();
			pSendPacket->b.myMgrServerStatusPacket.dwTotalServerConnections = g_pServerTable->GetNumOfConnectedServers();
			pSendPacket->b.myMgrServerStatusPacket.dwStatus = g_pServerTable->GetOwnServerData()->dwStatus;
			sprintf( pSendPacket->b.myMgrServerStatusPacket.szServerName, "AGENT SERVER(%d)", g_pServerTable->GetOwnServerData()->wPort );

			if( !AnswerToManager( pSendPacket, (sizeof(MANAGER_PACKET_HEADER) + sizeof(MGR_SERVER_STATUS_PACKET)) ) )
			{
				MyLog( LOG_NORMAL, "MANAGER_CMD_REQUEST_SERVER_STATUS :: Failed To Answer" );
				break;
			}
		}
		break;
	default:
		{
			return false;
		}
	}
	return true;
}
#endif


// -------------------------------------------------------------------
// Map SERVER ��
// -------------------------------------------------------------------
#ifdef __IS_MAP_SERVER
extern char MapName[ MAX_PATH];	

bool OnRecvMsgFromManager( LP_MANAGER_PACKET pPacket, DWORD dwLength )
{
	char szSendMsg[MM_MAX_PACKET_SIZE];
	LP_MANAGER_PACKET pSendPacket = (LP_MANAGER_PACKET)szSendMsg;

	// �̸� ä���д�. Answer ��.
	pSendPacket->h.bPTCL = PTCL_MANAGER_ANSWER;
	pSendPacket->h.uTarget.dwTargetManagerID = pPacket->h.uTarget.dwTargetManagerID;

	switch( pPacket->h.wCMD )
	{
	case MANAGER_CMD_REQUEST_SERVER_STATUS:
		{
			pSendPacket->b.myMgrServerStatusPacket.dwNumOfUsers = g_pServerTable->GetNumOfUsers();
			pSendPacket->b.myMgrServerStatusPacket.dwTotalServerConnections = g_pServerTable->GetNumOfConnectedServers();
			pSendPacket->b.myMgrServerStatusPacket.dwStatus = g_pServerTable->GetOwnServerData()->dwStatus;
			sprintf( pSendPacket->b.myMgrServerStatusPacket.szServerName, "MAP SERVER(%d/%s)", g_pServerTable->GetOwnServerData()->wPort, MapName );

			if( !AnswerToManager( pSendPacket, (sizeof(MANAGER_PACKET_HEADER) + sizeof(MGR_SERVER_STATUS_PACKET)) ) )
			{
				MyLog( LOG_NORMAL, "MANAGER_CMD_REQUEST_SERVER_STATUS :: Failed To Answer" );
				break;
			}
		}
		break;
	default:
		{
			return false;
		}
	}
	return true;
}
#endif


// -------------------------------------------------------------------
// DB Demon ��
// -------------------------------------------------------------------
#ifdef __IS_DB_DEMON
bool OnRecvMsgFromManager( LP_MANAGER_PACKET pPacket, DWORD dwLength )
{
	char szSendMsg[MM_MAX_PACKET_SIZE];
	LP_MANAGER_PACKET pSendPacket = (LP_MANAGER_PACKET)szSendMsg;

	// �̸� ä���д�. Answer ��.
	pSendPacket->h.bPTCL = PTCL_MANAGER_ANSWER;
	pSendPacket->h.uTarget.dwTargetManagerID = pPacket->h.uTarget.dwTargetManagerID;

	switch( pPacket->h.wCMD )
	{
	case MANAGER_CMD_REQUEST_SERVER_STATUS:
		{
			pSendPacket->b.myMgrServerStatusPacket.dwNumOfUsers = g_pServerTable->GetNumOfUsers();
			pSendPacket->b.myMgrServerStatusPacket.dwTotalServerConnections = g_pServerTable->GetNumOfConnectedServers();
			pSendPacket->b.myMgrServerStatusPacket.dwStatus = g_pServerTable->GetOwnServerData()->dwStatus;
			sprintf( pSendPacket->b.myMgrServerStatusPacket.szServerName, "DB DEMON(%d)", g_pServerTable->GetOwnServerData()->wPort );

			if( !AnswerToManager( pSendPacket, (sizeof(MANAGER_PACKET_HEADER) + sizeof(MGR_SERVER_STATUS_PACKET)) ) )
			{
				MyLog( LOG_NORMAL, "MANAGER_CMD_REQUEST_SERVER_STATUS :: Failed To Answer" );
				break;
			}
		}
		break;
	default:
		{
			return false;
		}
	}
	return true;
}
#endif
