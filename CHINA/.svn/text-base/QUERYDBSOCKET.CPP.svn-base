// QueryDBSocket.cpp: implementation of the CQueryDBSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
//#include "DRPointManger.h"
#include "QueryDBSocket.h"
#include "../Async/Async.h"
#include "../MyLog.h"
#include "../ShopDemon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CMySocket *ConC;
CQueryDBSocket::CQueryDBSocket()
{
//	for(int i=0;i<MAXCONNECTION;i++)
//	{
		m_AcceptSock = ConC;
		m_AcceptSock->status=EMPTY;
		m_AcceptSock->parent=LONG(this);
		
//	}
	


}

CQueryDBSocket::~CQueryDBSocket()
{

}
void CQueryDBSocket::MyAccept(CMySocket *SendSock)
{
	return;
}
void CQueryDBSocket::MyError(CMySocket *SendSock)
{
	DebugPrintf("network error(myERRORevent)...");

//	for (int i=0;i<MAXCONNECTION;i++)
		if (SendSock==m_AcceptSock)
		{
				if ( m_AcceptSock->status!=WAITING ) 
				{
					//PostMessage(outputWnd, GAME_EVENT, i, NetErrorEvent);
				}
				else
				{
				//	m_AcceptSock.Close();
					m_AcceptSock->status = EMPTY;
					DebugPrintf("... before he logon");
				}
			 
		}

}

BOOL CQueryDBSocket::Connsock(const char *ipaddr,LONG port) 
{
	// TODO: Add your command handler code here
//		if (!m_AcceptSock[0].Create()) 
//		{
//			DebugPrintf("無法開啟資料 socket_create");
			//delete mysession[ID].player;
			//mysession[ID].player=NULL;
//			return FALSE;
//		}	
//		if (!m_AcceptSock[0].Connect(ipaddr,port)) 
//		{
//			m_AcceptSock[0].PrintfSockError(m_AcceptSock[0].GetLastError());
		
//			DebugPrintf("無法開啟資料 socket_Socket");
			//delete mysession[ID].player;
			//mysession[ID].player=NULL;
//			return FALSE;
//		}
	return TRUE;	
}


int CQueryDBSocket::Send_Data_To_Server(int protocolID, void *databuf, int size)
{
    int oRet=FAIL;
    char *GameCmd;
	DebugPrintf("Send_Data_To_Server then ");
	GameCmd = (char*) malloc(3+1+size+1);
    if (GameCmd==NULL) 
	{
	    DebugPrintf("malloc error");
        return oRet;
    }
    sprintf(GameCmd,"%d ",protocolID);
    memcpy(GameCmd+4,databuf, size);

	//2001/01/30 zhh
	if(m_AcceptSock==NULL)
		return OK;

    if (m_AcceptSock->WritePacket(GameCmd, size+4) <= 0 ) 
	{
        DebugPrintf("Send_Data_To_Server無法送出request");
    } else
        oRet = OK;

	GameCmd[size+4]=0;
	DebugPrintf("Send_Data_To_Server:%s",GameCmd);
	free(GameCmd);
    return oRet;
}

int CQueryDBSocket::Receive_Data(WPARAM w, LPARAM l, char *MsgBuf, int *size)
{
    int oRet=0;
    int MsgSize;
    char Msg[4096], *msg ;
    int protocol;

	if (m_AcceptSock->ReadPacket(Msg, &MsgSize)==0) 
	{
		DebugPrintf("NetworkReadEvent Error! No data\n");
		return oRet;
	}
	Msg[MsgSize]=0;
    protocol = ((Msg[0]-'0') * 100 + (Msg[1]-'0') * 10 + (Msg[2]-'0'));
	msg = Msg+3;
	while (*msg != 0 && *msg==' ' ) msg++ ;

	DebugPrintf("Protocol:%d,Msg=%s\n",protocol,msg);
	*size = MsgSize-(msg-Msg);
	memcpy(MsgBuf, msg, *size);

	return protocol;
}

extern int SendYesorNo(	char *ID,			//[11]; //user'ID
						char *type,		//[2]; //type=P or M
						long point,		//user's Points(using in type=P)
						char *expiredata,	//[9];  //User's expire data(using in type=M) EX:20001220
						int success);		//if login or logout success

void CQueryDBSocket::MyRead(CMySocket *SendSock)
{		
	int datasize = 0;
	char datain[4096]={0,};
		
	for (int i=0;i<MAXCONNECTION;i++)
	{	
		//DebugPrintf("Receive clinet %d",i);
		if (SendSock==m_AcceptSock )
		{	
			int ProtocolID = Receive_Data(i,NULL,datain,&datasize);		
			UserData dUserdata;
			switch(ProtocolID)
			{	
			case RETURN_USERDATA:
				{	
					::memcpy(&dUserdata,datain,sizeof(UserData));
					int ret = ::SendYesorNo(dUserdata.ID,dUserdata.type,dUserdata.point,dUserdata.expiredata,dUserdata.success);
					DebugPrintf("Get From Server:ID=%s,Type=%s,point=%d,ExpireData=%s,Success=%d login=%d(success=1)"
						,dUserdata.ID,dUserdata.type,dUserdata.point,dUserdata.expiredata,dUserdata.success,ret);
				}break;
			default:
				{
					//soto-HK
					if(ProtocolID >= 500 && ProtocolID < 599)
					{
						GetShopDemon()->RecvShopProcess(ProtocolID, datain, datasize);
					}
					else
					{
						return;
						DebugPrintf("Error Receieve");
					}
				}break;
			}
			break;
		}
	}
}

BOOL CQueryDBSocket::AskCheckLoginWithIP(char * strID, char *strIP )//021007 lsw
{
	CheckLoginWithIP dLogin;
	::strcpy(dLogin.ID,strID);
	::strcpy(dLogin.IP,strIP);
	//2001/02/23 zhh
	int oRet;
	if(g_pConnection!=NULL)
	{
		oRet=Send_Data_To_Server(CHECK_LOGIN,&dLogin,sizeof(CheckLoginWithIP));
	}
	else
	{
		MyLog( LOG_FATAL, "[BILL] **** Warning! BillingServer Connection Closed!!! (AskCheckLogin)");
		oRet=FAIL;
	}
	if(oRet==FAIL)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL CQueryDBSocket::AskCheckLogoutWithIP(char *strID,char *login_time,char *logout_time,char *IP)//021007 lsw
{
	CheckLogout dLogout;
	strcpy(dLogout.ID,strID);
	strcpy(dLogout.logintime,login_time);
	strcpy(dLogout.logouttime,logout_time);
	strcpy(dLogout.IP,IP);
	int oRet=Send_Data_To_Server(CHECK_LOGOUT,&dLogout,sizeof(CheckLogout));
	if(oRet==FAIL)
		return FALSE;
	else
		return TRUE;
}
BOOL CQueryDBSocket::AskCheckLogin(char * strID)
{
	CheckLogin dLogin;
	strcpy(dLogin.ID,strID);
	//2001/02/23 zhh
	int oRet;
	if(g_pConnection!=NULL)
		oRet=Send_Data_To_Server(CHECK_LOGIN,&dLogin,sizeof(CheckLogin));
	else
	{
		MyLog( LOG_FATAL, "[BILL] **** Warning! BillingServer Connection Closed!!! (AskCheckLogin)");
		oRet=FAIL;
	}
	if(oRet==FAIL)
		return FALSE;
	else
		return TRUE;
}
BOOL CQueryDBSocket::AskCheckLogout(char *strID,char *login_time,char *logout_time)
{
	CheckLogout dLogout;
	strcpy(dLogout.ID,strID);
	strcpy(dLogout.logintime,login_time);
	strcpy(dLogout.logouttime,logout_time);

	//2001/02/23 zhh
	int oRet;
	if(g_pConnection!=NULL)
		oRet=Send_Data_To_Server(CHECK_LOGOUT,&dLogout,sizeof(CheckLogout));
	else
	{
		MyLog( LOG_FATAL, "[BILL] **** Warning! BillingServer Connection Closed! (AskCheckLogout) ");
		oRet=FAIL;
	}
	if(oRet==FAIL)
		return FALSE;
	else
		return TRUE;
}