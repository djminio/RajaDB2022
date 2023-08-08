// MySocket.cpp : implementation file
//

#include "..\stdafx.h"
//#include "DRPointManger.h"

#include "MySocket.h"
#include "PointDatastruct.h"
#include "../Async/Async.h"
#include "Abstractsock.h"
//#include "UsingSocket.h"


#include "../MyLog.h" 


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySocket

CMySocket::CMySocket(DWORD a)
{

	outputWnd=NULL;
    myReadQ = new PacketQ;
    myWriteQ = new PacketQ;
	ReadOffset=0;
	WriteOffset=0;

	m_hSocket = (DWORD)g_pConnection->GetSocket();
}

CMySocket::CMySocket()
{

	outputWnd=NULL;
    myReadQ = new PacketQ;
    myWriteQ = new PacketQ;
	ReadOffset=0;
	WriteOffset=0;

	m_hSocket = (DWORD)g_pConnection->GetSocket();
}


CMySocket::~CMySocket()
{
	//Msg("close socket");
	delete myReadQ;
	delete myWriteQ;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMySocket, CSocket)
	//{{AFX_MSG_MAP(CMySocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMySocket member functions

void CMySocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
//	CSocket::OnAccept(nErrorCode);
//	((CAbstractSock   *)parent)->MyAccept(this);		

	
}	

void CMySocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
//	CSocket::OnConnect(nErrorCode);
	//DebugPrintf("Client Connected ");
	//((CGSession *)parent)->MyConnect(this);		
		
	
}

void CMySocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
//	CSocket::OnClose(nErrorCode);
    DebugPrintf("連線關閉");
	//((CGSession *)parent)->MyClose(this);		
}


void CMySocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
//	CSocket::OnReceive(nErrorCode);
	int iRet = Read();
    if ( iRet > 0 )
	{
		DebugPrintf("Read something,parent=%d",parent);

		if( iRet > 1 )
		{
			_asm nop;
		}

		for( int i = 0 ; i < iRet ; i ++)
			((CAbstractSock   *)parent)->MyRead(this);		

		DebugPrintf("Send to gameClient Success");
    } 
	else if( iRet == 0 )
	{
		DebugPrintf("Read nothing");
        return;
    }
	else 
	{
//		((CAbstractSock   *)parent)->MyError(this);		
        DebugPrintf("Network Error: 無法讀到data(iRet=%d)",iRet);
    }
	
}

void CMySocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
//	CSocket::OnSend(nErrorCode);
	int iRet = Write();
    if ( iRet == -1 ) 
	{
//		((CAbstractSock   *)parent)->MyError(this);		
        DebugPrintf("Network Error: 無法寫出data");
    }
	
}

void CMySocket::Close()
{
	
	//Csocket's close code
	
	if (m_hSocket != INVALID_SOCKET)
	{
		
	//	CancelBlockingCall();
		//VERIFY(AsyncSelect(0));
		
	//	CAsyncSocket::Close();
		
		m_hSocket = INVALID_SOCKET;		
	}
	
}
int CMySocket::Read()
{
	int numBytes, len, offset, packetcount=0;
	int i;

	if ( MAX_PACKET_LEN-ReadOffset > 0 ) 
	{
		numBytes = recv(m_hSocket,tmpReadBuf+ReadOffset, MAX_PACKET_LEN-ReadOffset, 0);
	//	numBytes = Receive(tmpReadBuf+ReadOffset, MAX_PACKET_LEN-ReadOffset, 0);
		if ( numBytes == SOCKET_ERROR ) 
		{   /* Socket Error */
			DebugPrintf("Socket error: read(errno=%d)", WSAGetLastError());
			PrintfSockError(10054);
			return -2;
		}
		if ( numBytes == 0 ) 
		{  /* Connection Closed */
			DebugPrintf("Socket error: Connection Closed");
			return -1;
		}
		DebugPrintf("Actually receive %d bytes", numBytes);
    ReadOffset+=numBytes;
  }

	offset=0;
	while ( ReadOffset-offset>5 )
	{


		if ( tmpReadBuf[offset]!='-' && tmpReadBuf[offset]!='+') 
		{ /* Got a Noisy packet */
			DebugPrintf("error: Got a Noisy packet(%c)",tmpReadBuf[offset]);
			return -2;
		}
		len = myReadQ->bufToInt((unsigned char *)tmpReadBuf+offset+1)+5;
		if ( len > MAX_PACKET_LEN ) 
		{
			DebugPrintf("error: Packet too Large(%d)", len);
			return -2;
		}
		if ( len <= 5 ) 
		{
			DebugPrintf("error: Malformed packet");
			return -2;
		}
		if ( len <= ReadOffset-offset ) 
		{
			if (myReadQ->put(tmpReadBuf+offset+5,len-5,false)==0) 
			{
				DebugPrintf("Queue full or out of resource");
				break;
			}
			else
			{
				packetcount++;
			}
			offset+=len;
		} 
		else /* 長度不足 */
			break;
  }

//	010309 KHS billing test code...
//	static int cccc;
//	cccc += packetcount;
//	MyLog( LOG_NORMAL, "packetcount = %d : %d", packetcount, cccc );


	if (offset)
	{ /* 已讀出過packet */
		for (i=0; i<ReadOffset-offset; i++) /* 向前填滿 */
			tmpReadBuf[i] = tmpReadBuf[i+offset];
		tmpReadBuf[i]=0;
		ReadOffset-=offset;
		DebugPrintf("Got %d Packets",packetcount);
		return packetcount;
	}
	else
	{
		DebugPrintf("Packet length not enough");
		return 0;
	}

	
	



}
extern int Sendz(char* msg,int len);
int CMySocket::Write()
{
	int	i, len, iRet=0;
	char	packetBuf[MAX_PACKET_LEN+1];
	DebugPrintf("Write Begin");
	while ( WriteOffset < MAX_PACKET_LEN )
	{
		if ( (myWriteQ->get(packetBuf,&len)) == 0 ) 
		{
		//DebugPrintf("get packet Write buffer Error(%d)",WriteOffset);
		  break;
		}
		memcpy(tmpWriteBuf+WriteOffset, packetBuf, len);
		WriteOffset+=len;
	}
	
	if ( WriteOffset > 0 )
	{
	
		Sendz(tmpWriteBuf, WriteOffset);
		iRet = WriteOffset;
	//	iRet = Send(tmpWriteBuf, WriteOffset, 0);
		if ( iRet == SOCKET_ERROR ) 
		{
			if ( (iRet = WSAGetLastError()) == WSAEWOULDBLOCK )
				return 0;
			DebugPrintf("send socket error, errno=%d", WSAGetLastError());
			return -1;
		}

		if ( iRet == 0 ) 
		{
			DebugPrintf("select ok/send 0 bytes");
			return 0;
		}

		DebugPrintf("Actually send %d bytes", iRet);
		for (i=0; i<WriteOffset-iRet; i++) /* 向前填滿 */
		
			tmpWriteBuf[i] = tmpWriteBuf[i+iRet];
		WriteOffset-=iRet;
		
	}
	return iRet;
}
//---------------------------------------------------------------------------
// 0 : read no packet
// 1 : read OK
int CMySocket::ReadPacket(char *pkt, int *len)
{
	int iRet;
    iRet = myReadQ->get(pkt,len);

    //if (myReadQ->notEmpty())
	//((CGSession *)parent)->MyRead(this);		
	return iRet;
}
//---------------------------------------------------------------------------
int CMySocket::WritePacket(char *Cmd, int len)
{
	char	packetBuf[MAX_PACKET_LEN+1];

	if (1+4+len>MAX_PACKET_LEN)
		return -1;
	
		packetBuf[0] = '-';

	myWriteQ->intToBuf(packetBuf+1,len);
	memcpy(packetBuf+1+4, Cmd, len);
	packetBuf[1+4+len]=0;
	
	//DebugPrintf("put(%s)(%d)",packetBuf+1+4,len);
	if (myWriteQ->put(packetBuf,len+5,true)==0) 
	{
		DebugPrintf("Queue full or out of resource");
		return 0;
	}
	//DebugPrintf("write socket");
	if (Write() == -1 ) 
	{
		DebugPrintf("Network Error");
		return 0;
	}
	return 1;
}

void CMySocket::PrintfSockError(int iError)
{
	switch(iError)
	{
		case WSANOTINITIALISED :  
			DebugPrintf("SocketError: %s","WSANOTINITIALISED");
			break;
		case WSAENETDOWN  :
			DebugPrintf("SocketError: %s","WSAENETDOWN");
			break;
		case WSAEADDRNOTAVAIL   :
			DebugPrintf("SocketError: %s","WSAEADDRNOTAVAIL");
			break;
		case WSAEAFNOSUPPORT      :
			DebugPrintf("SocketError: %s","WSAEAFNOSUPPORT   ");
			break;
		case WSAECONNREFUSED         :
			DebugPrintf("SocketError: %s","WSAECONNREFUSED   ");
			break;
		case WSAEDESTADDRREQ               :
			DebugPrintf("SocketError: %s","WSAEDESTADDRREQ      ");
			break;
		case WSAEISCONN   			              :
			DebugPrintf("SocketError: %s","WSAEISCONN   			      ");
			break;
		case WSAEMFILE  			              :
			DebugPrintf("SocketError: %s","WSAEMFILE   			      ");
			break;
		case WSAENETUNREACH  			              :
			DebugPrintf("SocketError: %s","WSAENETUNREACH   			      ");
			break;
		case WSAETIMEDOUT 			              :
			DebugPrintf("SocketError: %s","WSAETIMEDOUT  			      ");
			break;
		case WSAEWOULDBLOCK   			              :
			DebugPrintf("SocketError: %s","WSAEWOULDBLOCK    			      ");
			break;


		case WSAEADDRINUSE  :
			DebugPrintf("SocketError: %s","WSAEADDRINUSE");
			break;
		case WSAEFAULT   :
			DebugPrintf("SocketError: %s","WSAEFAULT");
			break;
		case WSAEINPROGRESS  :
			DebugPrintf("SocketError: %s","WSAEINPROGRESS");
			break;
		case WSAEINVAL   :
			DebugPrintf("SocketError: %s","WSAEINVAL");
			break;
		case WSAENOBUFS  :
			DebugPrintf("SocketError: %s","WSAENOBUFS");
			break;

		case WSAENOTSOCK  :
			DebugPrintf("SocketError: %s","WSAENOTSOCK");
			break;
		case WSAENOTCONN   :
			DebugPrintf("SocketError: %s","WSAENOTCONN");
			break;
		case WSAEOPNOTSUPP    :
			DebugPrintf("SocketError: %s","WSAEOPNOTSUPP   ");
			break;
		case WSAESHUTDOWN       :
			DebugPrintf("SocketError: %s","WSAESHUTDOWN      ");
			break;
		case WSAEMSGSIZE:
			DebugPrintf("SocketError: %s","SAEMSGSIZE     ");
			break;
		case  WSAECONNABORTED   :
			DebugPrintf("SocketError: %s","WSAECONNABORTED        ");
			break;
		case WSAECONNRESET:
			DebugPrintf("SocketError: %s","WSAECONNRESET        ");
			break;

		default:
			DebugPrintf("SocketError: UnKnow error");
			break;
	}
}
int CMySocket::SoftClose(int mode) /* mode: wait for read or write to complete */
{				                  /* 0 : both 1: read 2: write */
    int iRet;


    	if (myWriteQ->notEmpty()) {
	        iRet = Write();
	        if (iRet >0 && mode != 1) {
		        return 0;
       	    }
    	}

        Close();
    return 1;
}

