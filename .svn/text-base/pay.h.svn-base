#pragma once
//#include <afx.h>
#include "stdafx.h"

#define IP_LENGTH 16
#define ID_LENGTH 20

struct LoginInfoPay
{
	char id[40];			//라자 아이디
	char pw[40];			//패스워드
	char UserID[40];		//종량제 업체 아이디
	char ip[IP_LENGTH];			//ip
	int  type;				//어떤 종량제 인지 0이면 정액
	DWORD index;	
};

typedef struct OUTPUT
{
	DWORD dwIndex;
	int   nType;
	int   nRet;
}t_Output,*LPOUTPUT;

class COnePass
{
public:
	enum eBillingType//-값으로 구성 해야 합니다. CheckPW_TotalDB_SQL이 남은 날짜(양수)를 리턴하기 때문입니다.
	{//MapServer와 항상 동기화 시키십시요
		BT_WRONG_ID					= -1,//ID 틀림
		BT_WRONG_PW					= -2,//PW 틀림

		BT_NEED_PAY					= -3,//돈 부족

		BT_COMMERCIAL_TIME_REMAIN	= -4,//남은 시간 있는놈
		BT_COMMERCIAL_IP			= -20,//IP 종량제
		BT_WRONG_AGE_LIMITED		= -30,// 0303929 kyo just in thailand
		BT_FREE						= -100,//공짜
		BT_WAIT_BILLING_MSG			= -200,//대만 같은 곳의 처리 방식 빌링을 기다리도록 처리
	};

private:
	int				d_kyulje;

public:
	COnePass();
	~COnePass();

	OUTPUT OnePassID(const short nCn,LoginInfoPay &LIP,const bool bIsGMTool); 

	int CheckLoginIDForJapan(const short nCn,LoginInfoPay &LIP);// 030211 LSW

	int CheckPW_TotalDB_SQL(const short nCn,LoginInfoPay &LIP);
	int CheckGameBangIP_SQL( DWORD *can_use, LPSTR ip ,int &type, int &IP_TimeRemain,int &ip_idx);

	int CheckGameBangIPAccount_SQL( DWORD ip_idx, int &IP_TimeRemain);
	int DeleteUsedID_SQL_ForPay(LPSTR szMapName, LPSTR szUID,int port);
	int InsertUsedID_SQL_ForPay(LPSTR szMapName, LPSTR szUID, char *IP , char *joint_id, int type, WORD wPort, DWORD dwID);
	int SelectUsedID_SQL_ForPay(LPSTR szUID);
	bool CheckLimitedAgeAndTime(const char* szId);	// 030929 kyo just using in thai
};

extern COnePass onepass;