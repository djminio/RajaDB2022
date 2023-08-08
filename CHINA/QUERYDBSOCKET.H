// QueryDBSocket.h: interface for the CQueryDBSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUERYDBSOCKET_H__6C1FBCE1_E1B0_11D4_966C_0050DAED441D__INCLUDED_)
#define AFX_QUERYDBSOCKET_H__6C1FBCE1_E1B0_11D4_966C_0050DAED441D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXCONNECTION 10
#define OK 0
#define FAIL -1

#include "MySocket.h"
#include "PointDataStruct.h"
//#include "UsingDB.h"
#include "AbstractSock.h"
class CQueryDBSocket  : public CAbstractSock  
{
public:
	CQueryDBSocket();
	virtual ~CQueryDBSocket();
public:
	int Send_Data_To_Server(int protocolID,void *databuf, int size);	
	virtual void MyAccept(CMySocket *SendSock);
	virtual void MyError(CMySocket *SendSock);
	virtual void MyRead(CMySocket *SendSock);
	BOOL Connsock(const char *ipaddr,LONG port);
	int Receive_Data(WPARAM w, LPARAM l, char *MsgBuf, int *size);
	
	BOOL AskCheckLoginWithIP(char * strID, char *strIP );//021007 lsw
	BOOL AskCheckLogoutWithIP(char *strID,char *login_time,char *logout_time,char *IP);//021007 lsw
	BOOL AskCheckLogin(char * strID);
	BOOL AskCheckLogout(char *strID,char *login_time,char *logout_time);	

private:
	CMySocket *m_AcceptSock;
//	CMySocket m_AcceptSock[MAXCONNECTION];
};

#endif // !defined(AFX_QUERYDBSOCKET_H__6C1FBCE1_E1B0_11D4_966C_0050DAED441D__INCLUDED_)
