#include "connection.h"

CConnection::CConnection(SOCKET s,DWORD size)
{
	m_dwStatus = CONNECTION_STATUS_STANDBY;
	m_pSendBuffer = NULL;
	m_pRecvBuffer = NULL;
	m_socket = s;
	m_dwMaxBufferSize = size;
	m_dwSendBufferPosition = 0;
	m_dwRecvBufferPosition = 0;
	m_pSendBuffer = NULL;
	m_pRecvBuffer = NULL;
	
	m_pSendBuffer = new char[m_dwMaxBufferSize];
	m_pRecvBuffer = new char[m_dwMaxBufferSize];
	
	memset(m_pSendBuffer,0,m_dwMaxBufferSize);
	memset(m_pRecvBuffer,0,m_dwMaxBufferSize);
}

bool CConnection::Send(char* msg,DWORD length)
{
	if (length >= MAX_PACKET_SIZE_)
	{
		return false;
	}
	if (m_dwRecvBufferPosition + length >= m_dwMaxBufferSize)
	{
		SetConnectionStatus(CONNECTION_STATUS_CLOSED_FROM_LOCAL);
		closesocket(m_socket);
		return false;
	}
	
//	*(WORD*)(m_pSendBuffer+m_dwSendBufferPosition) = (WORD)length;
//	m_dwSendBufferPosition += 2;
	memcpy(m_pSendBuffer+m_dwSendBufferPosition,msg,length);
	m_dwSendBufferPosition += length;

	return SendFromBuffer();
}

bool CConnection::SendFromBuffer()
{	
	if (m_dwSendBufferPosition <= 0)
		return false;

	int result;

	while (m_dwSendBufferPosition>0)
	{
		result = send(m_socket,m_pSendBuffer,m_dwSendBufferPosition,NULL);
		if (result == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				SetConnectionStatus(CONNECTION_STATUS_BLOCKED);
				return true;
			}	
			else
			{
				SetConnectionStatus(CONNECTION_STATUS_CLOSED_FROM_LOCAL);
				closesocket(m_socket);
				return false;
			}
		}
		m_dwSendBufferPosition -= result;
		memcpy(m_pSendBuffer,m_pSendBuffer+result,m_dwSendBufferPosition);
	}
	return true;
}

bool CConnection::OnRead()
{
	int result;

	if (m_dwMaxBufferSize-m_dwRecvBufferPosition <= 0)
	{
		SetConnectionStatus(CONNECTION_STATUS_CLOSED_FROM_LOCAL);
		closesocket(m_socket);
		return false;
	}

	result = recv(m_socket,m_pRecvBuffer+m_dwRecvBufferPosition,m_dwMaxBufferSize-m_dwRecvBufferPosition,NULL);

	if(result == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			SetConnectionStatus(CONNECTION_STATUS_BLOCKED);
			return true;
		}
		else
		{
			SetConnectionStatus(CONNECTION_STATUS_CLOSED_FROM_LOCAL);
			closesocket(m_socket);
			return false;
		}
	}
	m_dwRecvBufferPosition += result;
	
	return true;
}



CConnection::~CConnection()
{
//	MsgBox("close");

	if (m_pSendBuffer)
	{
		delete [] m_pSendBuffer;
		m_pSendBuffer = NULL;
	}
	if (m_pRecvBuffer)
	{
		delete [] m_pRecvBuffer;
		m_pRecvBuffer = NULL;
	}
	if (GetConnectionStatus() != CONNECTION_STATUS_CLOSED_FROM_LOCAL)
		closesocket(m_socket);

}
