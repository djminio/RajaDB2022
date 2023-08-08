#include "..\stdafx.h"//021007 lsw
#include "Async.h"
#include "msgproc.h"
#include "network.h"
#include "connection.h"
#include "../china/mysocket.h"
#include "../China/QueryDBSocket.h"
#include "../MyLog.h"
//#include "monitor.h"
//#include "..\Game.h"


CConnection* g_pConnection = NULL;

extern int Sendz(char* msg,int len);
extern void CloseForChina();
extern void CloseForChina();
int Sendz(char* msg,int len);


extern CMySocket *ConC;
extern CQueryDBSocket *ConQ;
CMySocket *ConC;
CQueryDBSocket *ConQ;


int Sendz(char* msg,int len)
{
	if( g_pConnection )
		g_pConnection->Send(msg,len);
	//2001/02/23 zhh
	else
		MyLog( LOG_FATAL, "[BILL] **** Warning! BillingServer Connection Closed! (Sendz)");

	return 0;
}

void CloseForChina( void )
{
	if(g_pConnection!=NULL)
		closesocket(g_pConnection->GetSocket());
}

//acer7
int ReleaseAsync()
{
	if( g_pNetwork )
	{
		delete g_pNetwork;
		g_pNetwork = NULL;
	}
	if( ConC )
	{
		delete ConC;
		ConC = NULL;
	}
	if( ConQ )
	{
		delete ConQ;
		ConQ = NULL;
	}
	return 1;
}

int InitAsync(  void )
{
	InitSocket();

	if(g_pNetwork==NULL)
		g_pNetwork = new CNetwork( 4000, 4000 );  // 010301 KHS

	if( g_pConnection )
	{	
		MyLog( LOG_NORMAL, "[BILL] Already connected to BillingServer !" );
		return 0;
	}	
	//2001/02/01 zhh
	static char sBillServerIP[ 20];
	static int  BillServerPort;
	static int  BillServerIndex;
	static int  BillServerMax;
	char	temps[ FILENAME_MAX];

read_bill_ip:

	sprintf( temps, "billing_server_info___ip%d", BillServerIndex );
	GetPrivateProfileString( "billing_server_info", temps, "", sBillServerIP, sizeof(sBillServerIP), DB_DEMON_INI_ );//021007 lsw

	sprintf( temps, "billing_server_info_port%d", BillServerIndex );
	BillServerPort= (DWORD)GetPrivateProfileInt( "billing_server_info", temps, 0, DB_DEMON_INI_);
	BillServerMax = (DWORD)GetPrivateProfileInt( "billing_server_info", "billing_server_num", 0, DB_DEMON_INI_);

	if( BillServerPort == 0 || BillServerMax == 0 || sBillServerIP[0] == 0 )
	{
		MyLog( LOG_NORMAL, "[BILL] Fail to read IP/Port in '%s' (%d)!!!!", DB_DEMON_INI_,BillServerIndex );
		return 0;
	}

	MyLog( LOG_NORMAL, "[BILL] Try to connect [%s, %d] ( %d ) !!!!", sBillServerIP, BillServerPort, BillServerIndex );

	g_pConnection = g_pNetwork->ConnectToServer(sBillServerIP, BillServerPort );	//client로서접속시	//2001/01/30 zhh 여기도

//	MyLog( LOG_NORMAL, "g_pConnection = %p", g_pConnection );

	if(g_pConnection==NULL)
	{	
		MyLog( LOG_NORMAL, "Can't Connect billing System Server[%s, %d] ( %d ) !!!!", sBillServerIP, BillServerPort, BillServerIndex );
		
		if( BillServerIndex < BillServerMax -1 )
			BillServerIndex ++;
		else
			BillServerIndex = 0;
		
		goto read_bill_ip;
	}	
	else
	{	
		ConC = new CMySocket((DWORD)g_pConnection->GetSocket());
		ConQ = new CQueryDBSocket();
		if(ConC==NULL) 
			//MessageBox(NULL,"Async Error","Do Restart",NULL);
			MyLog( LOG_FATAL, "[BILL] Async Error( ConQ == NULL )" );

		MyLog( LOG_NORMAL, "[BILL] Successfully Connected to BillingServer[%s:%d](%d) !!!!", sBillServerIP, BillServerPort, BillServerIndex );
	}	
		
	return(1);
}

/*
int ReadBillingText
		GetPrivateProfileString( "server_info", keyname_list[i], "", sDummyIP, sizeof(sDummyIP), sFileName );
*/


//2001/01/30 zhh 여기까지

void OnDestroyForAsync()
{
	if (g_pNetwork)
	{
		delete g_pNetwork;
		g_pNetwork = NULL;
	}
	ReleaseSocket();
}


void SendQuit()
{
	if( g_pNetwork )
		PostMessage( g_pNetwork->m_hProcWnd, WM_QUIT, 0, 0 );		// 스레드 종료
}

