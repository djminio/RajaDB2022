// MailMgr.h: interface for the CMailMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAILMGR_H__F092DE1B_42E7_4588_8ECB_8568879732B8__INCLUDED_)
#define AFX_MAILMGR_H__F092DE1B_42E7_4588_8ECB_8568879732B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum eMAIL_VIEW_TYPE
{//인터페이스의 nWillDo에도 사용 됩니다.
	MVT_RECV_LIST = 0,//받은편지함
	MVT_DELETE_LIST = 1,//지운 편지함
};

class CMailMgr  
{
public:
	enum eMAIL_TYPE
	{
		NORMAL_MAIL	= 1,
		GUILD_MAIL	= 2,
		GAMEMASTER_MAIL	= 3,
		
		NORMAL_MAIL_REPLY		= 101,
		GAMEMASTER_MAIL_REPLY	= 103,
	};

public:
	CMailMgr();
	virtual ~CMailMgr();

public://실제 코딩
	void Recv(const int cn, t_packet *p);
	void RecvReqMailList(const int cn, t_packet *p);//리스트 요청을 받음 //받은 맵서버로 되돌림

	bool InsertMail( const int iType, const char *szSender, const char *szReceiver, char *title, char *body );
	bool InsertMail2( const int iType, const char *szSender, const char *szReceiver, char *title, char *body );

	void SendAlert(const char *szName);//메일이 추가 될 경우 유저에게 메세지를 날림.
	void SendInsertMailResult( const char *szName, const int cn, const int cmd_type );//메일이 추가 될 경우 유저에게 메세지를 날림.

	bool RecvDelete(const int cn, t_packet *p);//메일이 지워짐 
	bool RecvRepair(const int cn, t_packet *p);//메일이 복구됨 

public://설계시
	void RecvRequestList();//시작점을 가지고 받음 한페이지 만큼 보내줌.
	void RecvRequestBody(const int cn,t_packet *p);//Index 를 가지고 참조
	bool IsExistNotRead(const int cn,t_packet *p);//안읽은 메일이 있는가?
};

extern CMailMgr g_MailMgr;
#endif // !defined(AFX_MAILMGR_H__F092DE1B_42E7_4588_8ECB_8568879732B8__INCLUDED_)
