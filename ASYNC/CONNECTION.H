#pragma once

#include "stdafx.h"
#include <winsock2.h>
#include "define.h"

#define CONNECTION_CLOSED_BIT_MASK	0x00000008

enum CONNECTION_STATUS 
{
	CONNECTION_STATUS_CLOSED_FROM_LOCAL	 =	0x00000009,
	CONNECTION_STATUS_CLOSED_FROM_REMOTE =	0x00000010,
	CONNECTION_STATUS_BLOCKED			 =  1020,
	CONNECTION_STATUS_STANDBY			 =  1000,
};
class CConnection 
{
	CONNECTION_STATUS	m_dwStatus;
	SOCKET				m_socket;
	char*				m_pSendBuffer;
	char*				m_pRecvBuffer;


	DWORD				m_dwMaxBufferSize;
	DWORD				m_dwSendBufferPosition;
	DWORD				m_dwRecvBufferPosition;
public:
	bool				SendFromBuffer();
	DWORD				GetSendBufferPosition() {return m_dwSendBufferPosition;}
	DWORD				GetReceiveBufferPosition() {return m_dwRecvBufferPosition;}
	
	void				SetConnectionStatus(CONNECTION_STATUS st) { m_dwStatus = st;}
	CONNECTION_STATUS	GetConnectionStatus() {return m_dwStatus;}
	bool				Send(char* msg,DWORD length);
	bool				OnRead();
	SOCKET				GetSocket() {return m_socket;}
	char*				GetReceiveBufferPtr() {return m_pRecvBuffer;}
	char*				GetSendBufferPtr() {return m_pSendBuffer;}
	void				Init(SOCKET s,DWORD size);

	bool				DispatchMsg(char** ppMsg,DWORD* pdwLen)
	{
		if (m_dwRecvBufferPosition < DEFAULT_MESSAGE_LENGTH_)
			return false;
		
		*pdwLen = *(WORD*)m_pRecvBuffer;

		if (m_dwRecvBufferPosition < *pdwLen + DEFAULT_HEADER_SIZE_ )
			return false;
		
		*ppMsg = m_pRecvBuffer+DEFAULT_HEADER_SIZE_;
		
		return true;
	}
	void				ShiftRecv(DWORD dwLen)
	{
		m_dwRecvBufferPosition = m_dwRecvBufferPosition - dwLen - 2;
		memcpy(m_pRecvBuffer,m_pRecvBuffer+dwLen+2,m_dwRecvBufferPosition);
	}

	
	CConnection(SOCKET s,DWORD size);
	~CConnection();

	CConnection*	m_pNextConnection;
	CConnection*	m_pPrvConnection;
};

typedef CConnection* LPCConnection;


