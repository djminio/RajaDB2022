// AbstractSock.h: interface for the CAbstractSock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSTRACTSOCK_H__6C1FBCE2_E1B0_11D4_966C_0050DAED441D__INCLUDED_)
#define AFX_ABSTRACTSOCK_H__6C1FBCE2_E1B0_11D4_966C_0050DAED441D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MySocket.h"
class CAbstractSock  
{
public:
	CAbstractSock();
	virtual ~CAbstractSock();
	virtual void MyAccept(CMySocket *SendSock)=0;
	virtual void MyError(CMySocket *SendSock)=0;
	virtual void MyRead(CMySocket *SendSock)=0;
};

#endif // !defined(AFX_ABSTRACTSOCK_H__6C1FBCE2_E1B0_11D4_966C_0050DAED441D__INCLUDED_)
