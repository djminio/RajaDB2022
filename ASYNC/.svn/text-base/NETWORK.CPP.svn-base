#include "define.h"
#include "network.h"
#include "msgproc.h"


#include "../MyLog.h"

//#include "monitor.h"


CNetwork* g_pNetwork = NULL;

CNetwork::CNetwork(DWORD dwMaxConnectionNum,DWORD dwMaxBucketNum)
{
	Initialize(dwMaxBucketNum);
	
	m_hProcWnd = CreateMessageWindow("net_proc");
	m_dwConnectionNum = 0;
	m_dwMaxConnectionNum = dwMaxConnectionNum;
	m_wPort = 0;
	memset(&m_sckadrAdress,0,sizeof(sockaddr_in));
	
}

void CNetwork::ReleaseSocket()
{
	if(m_socketBase)
	{
		closesocket(m_socketBase);
		m_socketBase = NULL;
	}
}

CNetwork::~CNetwork()
{
	CloseAllConnection();
	ReleaseSocket();

}

bool CNetwork::StartServer(char* ip,WORD port)
{
	m_socketBase = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(m_socketBase == INVALID_SOCKET )
	{
		MessageBox(GetActiveWindow(),"Fail to create socket","Error",MB_OK);
		return false;
	}

	m_sckadrAdress.sin_family = AF_INET;
	m_sckadrAdress.sin_port = htons(port);
	
	m_sckadrAdress.sin_addr.s_addr = inet_addr(ip);
	//m_sckadrAdress.sin_addr.s_addr = htons(INADDR_ANY);
	if(bind(m_socketBase, (struct sockaddr *)&m_sckadrAdress, sizeof(m_sckadrAdress)) < 0) 
	{
		char txt[256];
		memset(txt,0,256);
		wsprintf(txt,"Fail to socket bind with port %d",port);
		MessageBox(GetActiveWindow(),txt,"Error",MB_OK);
		closesocket(m_socketBase);
		m_socketBase = NULL;
		return false;
	}
	
	if(listen(m_socketBase, DEFAULT_QUEUE_NUM) < 0) 
	{
		MessageBox(GetActiveWindow(),"Socket Listen Fail","Error",MB_OK);
		closesocket(m_socketBase);
		m_socketBase = NULL;
		
		return false;
	}

	// 리슨 소켓을 비동기적으로 구동.
	WSAAsyncSelect(m_socketBase,m_hProcWnd,WM_SOCKET_EVENT,FD_ACCEPT);

	return true;
}



void CNetwork::CloseAllConnection()
{
	SetPositionHead();
	CConnection* pCon = NULL;
	
	while(pCon = (CConnection*)GetData())
	{
		delete pCon;
		pCon = NULL;
	}
}


void CNetwork::OnCloseConnection(SOCKET s)
{
	char txt[128] = {0,};
	CConnection* con = (CConnection*)GetData(s);
	if (con)
	{
		delete con;
		Remove(s);
	}	
}


CConnection* CNetwork::Accepting()
{
	SOCKET csock;
	int caddr_len;
	struct sockaddr_in caddr;
	char address[128];
	
	// accept the connection
	caddr_len = sizeof(caddr);
	csock = accept(m_socketBase, (struct sockaddr *)&caddr, &caddr_len);
	
	if(csock < 0) 
	{
		MessageBox(GetActiveWindow(),"Fail Socket to Accept","Error",MB_OK);
		return false;
	}
	if (m_dwConnectionNum >= m_dwMaxConnectionNum)
	{
		MessageBox(GetActiveWindow(),"Connection Table is full","Error",MB_OK);
		closesocket(csock);
		csock = NULL;
		return false;
	}

	memset(address, 0, 128);
    strcpy(address, inet_ntoa(caddr.sin_addr));

	WSAAsyncSelect(csock,m_hProcWnd,WM_SOCKET_EVENT, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
	CConnection* con = AddConnection(csock);

	return con;
}
CConnection* CNetwork::AddConnection(SOCKET s)
{
	CConnection* pCon = new CConnection(s,MAX_BUFFER_SIZE);
	Add(pCon,s);

	return pCon;
}
CConnection* CNetwork::ConnectToServer(char* szIP,WORD port)
{
	sockaddr_in addr;
	SOCKET csock;

	WORD s = port;

	csock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
//	MyLog( LOG_NORMAL, "csock = %d", csock  );
	

	if(csock == INVALID_SOCKET )
	{
	//	MessageBox(GetActiveWindow(),"Fail to create socket","Error",MB_OK);
		MyLog( LOG_NORMAL, "csock == INVALID_SOCKET" );
		return NULL;
	}

	addr.sin_family = AF_INET;
	addr.sin_port   = htons(port);
	addr.sin_addr.s_addr = inet_addr(szIP);
	
	if(connect(csock, (LPSOCKADDR)&addr, sizeof(addr)) < 0)
	{
	//	MessageBox(GetActiveWindow(),"Fail to connect","Error",MB_OK);
		MyLog( LOG_NORMAL, "Fail to connect" );

		closesocket(csock);
		csock = 0;
		return NULL;
	}

	WSAAsyncSelect(csock,m_hProcWnd,WM_SOCKET_EVENT,FD_READ | FD_WRITE | FD_CLOSE | FD_CONNECT);
	CConnection*	con = AddConnection(csock);

//	MyLog( LOG_NORMAL, "con = %p", con );
	return con;
}

