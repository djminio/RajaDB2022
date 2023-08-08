#ifndef NETWORK_H
#define NETWORK_H

#include "connection.h"
#include "define.h"
#include "msgproc.h"
#include "hashtable.h"



class CNetwork : CHashTable
{
	
	WORD			m_wPort;
	DWORD			m_dwConnectionNum;
	DWORD			m_dwMaxConnectionNum;
	SOCKET			m_socketBase;
	sockaddr_in		m_sckadrAdress;
	void			ReleaseSocket();
	CConnection*	AddConnection(SOCKET s);

public:
	//2001/02/01 zhh
	HWND			m_hProcWnd;

	WORD			GetPort() {return m_wPort;}
	void			Send(DWORD dwConnectionIndex,char* msg,DWORD length);
	CConnection*	ConnectToServer(char* szIP,WORD port);
	bool			StartServer(char* ip,WORD port);
	void			CloseAllConnection();
	void			OnCloseConnection(SOCKET s);
	CConnection*	GetConnection(SOCKET s) {return (CConnection*)GetData(s);}	
	CConnection*	Accepting();
	CNetwork(DWORD dwMaxConnectionNum,DWORD dwMaxBucketNum);
	~CNetwork();
	
};

extern CNetwork* g_pNetwork;


#endif
