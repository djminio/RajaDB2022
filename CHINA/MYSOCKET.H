#if !defined(AFX_MYSOCKET_H__DC51AD8F_B40A_11D4_966C_0050DAED441D__INCLUDED_)
#define AFX_MYSOCKET_H__DC51AD8F_B40A_11D4_966C_0050DAED441D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySocket.h : header file
//

#define EMPTY     0
#define WAITING   1
#define CONNECTED 2


/////////////////////////////////////////////////////////////////////////////
// CMySocket command target
#include "PacketQ.h"
//#include "agzapi.h"
//#include "DRPointManger.h"

class CMySocket
{

// Attributes
public:
	DWORD m_hSocket;
	
	int ReadPacket(char *pkt, int *len);
	int WritePacket(char *pkt, int len);
	int SoftClose(int mode);
    HWND outputWnd;
	virtual void Close();

    
    LONG parent;

    HWND myHandle;
	//
	#define SOCKET_EVENT (WM_USER+1)
	int Read();
	int Write();
	PacketQ *myReadQ;
	PacketQ *myWriteQ;
    char tmpReadBuf[MAX_PACKET_LEN+1];
    char tmpWriteBuf[MAX_PACKET_LEN*2+1];
    int ReadOffset;
    int WriteOffset;
	int status;
// Operations
public:
	CMySocket(DWORD a);
	CMySocket();
	virtual ~CMySocket();

// Overrides
public:
	void PrintfSockError(int iError);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMySocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCKET_H__DC51AD8F_B40A_11D4_966C_0050DAED441D__INCLUDED_)
