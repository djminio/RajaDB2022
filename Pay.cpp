#include "pay.h"
//#include "StdAfx.h"

#include "MAIN.H"
//#include "NPC_Pattern.h"
//#include "Map.h"
//#include "Scrp_exe.h"
#include "monitor.h"
#include "servertable.h"
//#include "Id.h"
#include "dragonLoginServer2.h" // For ConvertQueryString

//혹시라도 문제생기면 주석 풀것
const int month_tbl[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };	
extern HDBC  hDBC_TotalDB;
		
extern int GetUserAge(const char* szID);	// 030929 kyo
extern bool IsLimitedTime();				// 030929 kyo

COnePass onepass;
		
COnePass::COnePass()
{
}		

COnePass::~COnePass()
{		
}		
		
int COnePass::InsertUsedID_SQL_ForPay( LPSTR szMapName, LPSTR szUID, 
									  char *IP , char *joint_id, 
									  int type, WORD wPort, DWORD dwID )
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode = 0;
	
	char		szQuerry[512] = {0,};
	char szIP[IP_LENGTH] = {0,};
	//char szMapName2[20];
	char szUID2[ID_LENGTH] = {0,};
	char szJointID[ID_LENGTH] = {0,};
	ConvertQueryString(IP, szIP, IP_LENGTH); // Finito prevents sql injection
	//ConvertQueryString(szMapName, szMapName2, 20); // Finito removed because szMapName is always " " ( empty )
	ConvertQueryString(szUID, szUID2, ID_LENGTH); // Finito prevents sql injection
	ConvertQueryString(joint_id, szJointID, ID_LENGTH); // Finito prevents sql injection

	::sprintf(szQuerry, "insert into logintable (servername, user_id, type, ip, joint_id, port, d_kyulje, agent_id, server_set_num) values "
						"('%s','%s',"
						"'%d','%s','%s',"
						"'%d','%d','%d','%d')",
						szMapName, szUID2 , 
						type , szIP, szJointID, 
						wPort, this->d_kyulje, dwID, g_pServerTable->GetServerSetNum());

	::SQLAllocStmt(hDBC_TotalDB, &hStmt);
	retCode = ::SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
	::SQLFreeStmt(hStmt, SQL_DROP);
			
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{		
		return 1;
	}		

	return 0;
}

int COnePass::SelectUsedID_SQL_ForPay( LPSTR szUID )
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode = 0;
	
	char		szQuerry[512] = {0,};
	char szUID2[40];
	ConvertQueryString(szUID, szUID2, 40); // Finito prevents sql injection
	::sprintf(szQuerry, "select * from logintable where user_id = '%s'",szUID2);

	::SQLAllocStmt(hDBC_TotalDB, &hStmt);
	retCode = ::SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
			
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{
		retCode = SQLFetch(hStmt);
		
		if(retCode == SQL_SUCCESS)
		{
			SQLFreeStmt(hStmt, SQL_DROP);
			return 1;
		}
	}	

	return 0;
}

//1207 zhh
int COnePass::DeleteUsedID_SQL_ForPay(LPSTR szMapName, LPSTR szUID,int port)
{	
	char	szQuerry[255]={0,};
	HSTMT		hStmt = NULL;
	RETCODE		retCode;

	//001218 zhh
	if(port==0)
	{
		if(szUID == NULL)
		{
			char szMapName2[21];
			ConvertQueryString(szMapName, szMapName2, 21); // Finito prevents sql injection
			sprintf(szQuerry, "delete from logintable where servername='%s' AND server_set_num = %d", szMapName2, g_pServerTable->GetServerSetNum() );
		}
		else
		{
			char szUID2[20];
			ConvertQueryString(szUID, szUID2, 20); // Finito prevents sql injection
			sprintf(szQuerry, "delete from logintable where user_id='%s'", szUID2);
		}
	}		
	else	
	{		
		sprintf(szQuerry, "DELETE FROM logintable WHERE port=%d AND server_set_num = %d ", port,  g_pServerTable->GetServerSetNum());
		MyLog( LOG_NORMAL, szQuerry);
	}
			
	SQLAllocStmt(hDBC_TotalDB, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
	SQLFreeStmt(hStmt, SQL_DROP);
		
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{	
		return 1;
	}	
	else
	{	
		MyLog( LOG_FATAL, "<< QUERY FAIL >> User '%s's DELETE QUERY has Failed!!!", szUID );
	}	
		
	return 0;
}
	
//2001/02/19 zhh
#include "./China/QueryDBSocket.h"
extern CQueryDBSocket *ConQ;

OUTPUT COnePass::OnePassID(const short nCn,LoginInfoPay &LIP,const bool bIsGMTool)
{
	OUTPUT Output = {0,};
	if(LocalMgr.IsAbleNation(JAPAN) && !bIsGMTool)//일본인데 일반 유저일 경우
	{
		Output.nRet		=	CheckLoginIDForJapan(nCn,LIP);
		Output.nType	=	LIP.type;
		Output.dwIndex	=	LIP.index;
	}
	else
	{
		Output.nRet		=	CheckPW_TotalDB_SQL(nCn,LIP);//로그인 가능한지에 대한 변수 입니다.
		Output.nType	=	LIP.type;//결제 타입입니다.
		Output.dwIndex	=	LIP.index;//
		// 중국의 과금에서 IP단위의 과금이 들어가면 이부분에 추가된다. 
		if(LocalMgr.IsAbleNation(TAIWAN|CHINA|HONGKONG))//021007 lsw//중국홍콩대만 모두 아이피를 추가한다. 
		{
			if( Output.nRet > 0 || Output.nRet == BT_NEED_PAY )//0보다 클 경우는 남은 날짜가 있는 것이고
			{
				ConQ->AskCheckLoginWithIP( LIP.id, LIP.ip );
				Output.nRet = COnePass::BT_WAIT_BILLING_MSG;//중국의 경우는
			}
		}

		//// Check if the user is banned
		if (Output.nRet == BT_FREE)
		{
			bool bIsBanned = 0;
			HSTMT		hStmt = NULL;
			RETCODE		retCode = 0;
			SDWORD		cbValue = 0;

			char		szQuerry[MAX_PATH] = { 0, };
			::sprintf(szQuerry, "SELECT unBanDate FROM TotalDB.dbo.ban_table WHERE account = '%s';", LIP.id);

			::SQLAllocStmt(hDBC_TotalDB, &hStmt);
			retCode = ::SQLExecDirect(hStmt, (UCHAR*)szQuerry, SQL_NTS);
			if (retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
			{

				retCode = ::SQLFetch(hStmt);
				if (retCode == SQL_SUCCESS)
				{
					// account was found in ban_table
					const auto currentTime = time(nullptr);

					char unBanDateC[255] = { 0 };

					retCode = ::SQLGetData(hStmt, 1, SQL_C_CHAR, &unBanDateC, 13, &cbValue);
					Output.nRet = BT_BANNED; // TODO have a ban message but for now just use wrong password error
					MyLog(LOG_IMPORTANT, "Account %s tried logging in but is banned! ip: %d", LIP.id, LIP.ip);
					//::SQLFreeStmt(hStmt, SQL_DROP);
					if (retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
					{
						

						
							const auto unBanDate = std::atoi(unBanDateC);

							// his ban has passed
							if (currentTime >= unBanDate)
							{

								::SQLFreeStmt(hStmt, SQL_DROP);
								::SQLAllocStmt(hDBC_TotalDB, &hStmt);

								ZeroMemory(szQuerry, sizeof(szQuerry));

								::sprintf(szQuerry, "DELETE FROM TotalDB.dbo.ban_table WHERE account = '%s';", LIP.id);
								retCode = ::SQLExecDirect(hStmt, (UCHAR*)szQuerry, SQL_NTS);
								if (retCode == SQL_SUCCESS)
								{
									
									MyLog(LOG_IMPORTANT, "Unbanned account %s", LIP.id);
								}
								
							}
							
						}
					
					}
				::SQLFreeStmt(hStmt, SQL_DROP);
				

				}
			
			
			//// still banned
			
		
		}
		if (Output.nRet == BT_FREE)
		{
			bool bIsBanned = 0;
			HSTMT		hStmt = NULL;
			RETCODE		retCode = 0;
			SDWORD		cbValue = 0;

			char		szQuerry[MAX_PATH] = { 0, };
			::sprintf(szQuerry, "SELECT * FROM TotalDB.dbo.AccountLock WHERE account = '%s';", LIP.id);

			::SQLAllocStmt(hDBC_TotalDB, &hStmt);
			retCode = ::SQLExecDirect(hStmt, (UCHAR*)szQuerry, SQL_NTS);
			if (retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
			{

				retCode = ::SQLFetch(hStmt);
				if (retCode == SQL_SUCCESS)
				{
					// account was found in ban_table

					char account[255] = { 0 };

					retCode = ::SQLGetData(hStmt, 1, SQL_C_CHAR, &account, 13, &cbValue);


					// still banned
					Output.nRet = BT_BANNED; // ban message
					MyLog(LOG_IMPORTANT, "Account %s tried logging in but is perm banned! ip %d", LIP.id, LIP.ip);

				}
			}
			::SQLFreeStmt(hStmt, SQL_DROP);
		}
	}

	return Output;
}


// 프리 베타일 경우 접속 가능한 아이디 인지 날자로 확인 할때 사용
int GetAccessPossableDay( int &year, int &month, int &day )
{
	char szRegistDate[50]= {0,};
	// YYYY/MM/DD 형식이어야 함
	if( GetPrivateProfileString( "nation_set", "RegistDate", "" , szRegistDate, 50,DB_DEMON_INI_ ) )
	{
		char *token = strtok( szRegistDate, "/" );
		if( !token ) return 0;
		year = atoi(token);
		
		token = strtok( NULL, "/" );
		if( !token ) return 0;
		month = atoi(token);

		token = strtok( NULL, "/" );
		if( !token ) return 0;
		day = atoi(token);

		return 1;
	}
	
	return 0;
}

// 리턴값..
// -1 : ID 없음. 
// -2 : PW 틀림..
// -3 : 돈내야함..
//      남은 날짜..
extern bool IsFreeLevel( char *szUID );
int COnePass::CheckPW_TotalDB_SQL(const short nCn,LoginInfoPay &LIP)//사용 가능한 날짜를 리턴 합니다.
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode= 0;
	SDWORD		cbValue= 0;
	bool		bIsPwRight= 0;	
	bool        bIsBanned = 0;
	int			User_TimeReamin=0;
	int			ip_idx=0;
	
	if(SearchStrStr(LIP.id, " \'\"")) return BT_WRONG_ID;
	if(SearchStrStr(LIP.pw, " \'\"")) return BT_WRONG_ID;

	TIMESTAMP_STRUCT	date = {0,};

	if( LIP.pw == NULL || ::strlen(LIP.pw) <= 0 ){ return(BT_WRONG_PW); }

	::prepare( connections );

	::EatRearWhiteChar( LIP.id );

	char Id[40]; // Finito prevents sql injection
	ConvertQueryString(LIP.id, Id, 40); // Finito prevents sql injection

	char		szQuerry[ MAX_PATH ] = {0,};
    ::sprintf(szQuerry, "EXEC up_get_user_info2 '%s'", Id);//	sprintf(szQuerry, "select id_index, passwd, d_eday from chr_log_info where login_id='%s'", LIP.id );


	extern HDBC brokenShit;

	hDBC_TotalDB = brokenShit;

	::SQLAllocStmt(hDBC_TotalDB, &hStmt);
	retCode = ::SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{															
		retCode = ::SQLFetch(hStmt);
		if( retCode != SQL_SUCCESS) 
		{
			goto ERROR_NO_ID_;	// 등록되지 않은 ID입니다. 
		}
		
		while(retCode == SQL_SUCCESS)
		{
			char PW[PW_LENGTH+1]= {0,};
			retCode = ::SQLGetData(hStmt, 1, SQL_C_ULONG,		&LIP.index,		0,		 &cbValue);
			retCode = ::SQLGetData(hStmt, 2, SQL_C_CHAR,		PW,				PW_LENGTH, &cbValue);
			retCode = ::SQLGetData(hStmt, 3, SQL_C_ULONG,		&this->d_kyulje,		0,		 &cbValue);
			retCode = ::SQLGetData(hStmt, 4, SQL_C_TIMESTAMP,	&date,			sizeof( TIMESTAMP_STRUCT ), &cbValue);
			retCode = ::SQLGetData(hStmt, 5, SQL_C_ULONG,		&User_TimeReamin, 0,		 &cbValue);

			::EatRearWhiteChar(PW);
			if(!::strcmp(LIP.pw, PW))
			{
				bIsPwRight = TRUE;
				break;
			}
		}
		::SQLFreeStmt(hStmt, SQL_DROP);

		if(!bIsPwRight){return(BT_WRONG_PW);}// password 틀림..
		
		if(LocalMgr.IsFreeBeta())//021007 lsw
		{
			/*int year = 0, month = 0, day = 0;
			if( ::GetAccessPossableDay( year, month, day ) )//등록 날짜로 프리베타가 가능 한지 체크
			{
				sprintf(szQuerry, "username = '%s' AND d_regday > '%d-%d-%d' ", Id, year, month, day);
				int nCount = 0;
				::GetRowLineOfSQL( "login_info", "*", &nCount, szQuerry, hDBC_TotalDB );
				if( !nCount ) 
				{
					return BT_WRONG_ID;
				}
			}*/
			return BT_FREE;
		}

		const int iLimitDay = date.year * 365 + month_tbl[ date.month-1] + date.day; 
		const int iToday = g_year * 365 + g_yday;	
		if( iLimitDay >= iToday )// 1단계 : 유저날짜 체크.
		{
			return 1 + iLimitDay - iToday;// 앞으로 사용가능한 날짜수 
		}
		//< CSD-040127
		if (LocalMgr.IsAbleNation(TAIWAN|HONGKONG))
		{
			return BT_FREE;
		}

		if (LocalMgr.IsAbleNation(CHINA))
		{
			if (IsFreeLevel(LIP.id))
			{
				return BT_FREE;
			}

			return BT_FREE;
		}
		//> CSD-040127
		DWORD can_use = 0;
		int IP_TimeRemain=0;
		const int ret = CheckGameBangIP_SQL( &can_use, LIP.ip ,LIP.type,IP_TimeRemain,ip_idx);

		LIP.type = 0;
		
		if( ret > 0 )// 2단계 : IP날짜 체크..
		{	
			this->d_kyulje=0;
			return BT_COMMERCIAL_IP;
		}
		if(IP_TimeRemain>0)// 3단계 : IP 선불종량제 체크..
		{
			this->d_kyulje=0;	//ip와 관련될 경우 0으로 넣어달라는 강해원 팀장님의 요구에 따라 0으로 세팅.
			LIP.type = ip_idx + 50000;
			return BT_COMMERCIAL_IP;
		}
		else if(User_TimeReamin>0)// 4단계 : 유저 선불종량제 체크..
		{
			this->d_kyulje=4000;	
			LIP.type = 4000; // 유저 시간 종량제 타입
			return BT_COMMERCIAL_TIME_REMAIN; // 4일 이상남은것으로 간주. 
		}

		if (LocalMgr.IsAbleNation(KOREA))//돈을 안낸 사람이다
		{	//< CSD-040127
			if( ::IsFreeLevel( LIP.id ) )
			{
				return BT_FREE;
			}// 프리레벨유저이므로 통과
		}	//> CSD-040127

		return BT_FREE;	// 돈내야함..
	}
	else
	{
		displaySQLError( hStmt, szQuerry ); // 030923 HK YGI
	}
ERROR_NO_ID_:
	::SQLFreeStmt(hStmt, SQL_DROP);	
	return BT_WRONG_ID;							// 그런 ID없음.
}



int COnePass::CheckGameBangIP_SQL( DWORD *can_use, LPSTR ip ,int &type, int &IP_TimeRemain,int &ip_idx)
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	BOOL		bCheck;
	char		szQuerry[255];
	TIMESTAMP_STRUCT	date;
	int month_tbl[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };	
	int rt, ct;

	char IP[IP_LENGTH]; // Fintio prevents sql injection
	ConvertQueryString(ip, IP, IP_LENGTH); // Finito prevents sql injection

	if(LocalMgr.IsAbleNation(TAIWAN|CHINA|HONGKONG))//021007 lsw
	{
		return BT_NEED_PAY;
	}

	bCheck = FALSE;
	//010104 zhh
	//sprintf(szQuerry, "select can_use, Billing_eday, ip_type from IP_USE where ip ='%s'", ip );
    /////////////////////////////////////////////////////////////////////////////
    sprintf(szQuerry, "EXEC up_get_ip_info '%s'", IP);
    /////////////////////////////////////////////////////////////////////////////
	SQLAllocStmt(hDBC_TotalDB, &hStmt);

	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{		
		retCode = SQLFetch(hStmt);
			
		if( retCode == SQL_SUCCESS ) // 등록된 IP가 존재함. 
		{	
			SQLGetData(hStmt, 1, SQL_C_ULONG, can_use, 0, &cbValue);
			SQLGetData(hStmt, 2, SQL_C_TIMESTAMP, &date,  sizeof( TIMESTAMP_STRUCT ), &cbValue);

			//1207 zhh
			SQLGetData(hStmt, 3, SQL_C_ULONG, &type, 0, &cbValue);
			SQLGetData(hStmt, 4, SQL_C_ULONG, &ip_idx, 0, &cbValue);
			
			SQLFreeStmt(hStmt, SQL_DROP);
			
			this->CheckGameBangIPAccount_SQL( ip_idx, IP_TimeRemain);
			//	날짜 계산.. 
			if( *can_use == 1 ) // 사용가능한 IP..
			{	
				rt = date.year * 365 + month_tbl[ date.month-1] + date.day;
				ct = g_year * 365 + g_yday;
				
				if( rt < ct )	return BT_NEED_PAY;
				else			return 1 + rt - ct;	// 앞으로 사용가능한 날짜에 
			}	
			else
			{	
				return -2;
			}	
		}		
		else	
		{		
			SQLFreeStmt(hStmt, SQL_DROP);
			return -2;
		}		
	}			
	else
	{
		SQLFreeStmt(hStmt, SQL_DROP);	
		return -1;							// 그런 겜방IP없음.
	}
	SQLFreeStmt(hStmt, SQL_DROP);			// 0414 YGI
	return(-2);
};

int COnePass::CheckLoginIDForJapan(const short nCn, LoginInfoPay &LIP)
{
	HSTMT	hStmt = NULL;
	RETCODE	retCode= 0;
	SDWORD	cbValue= 0;
	char	szQuerry[ MAX_PATH ] = {0,};
	int		rt = 0, ct= 0;

	EatRearWhiteChar( LIP.id );
	EatRearWhiteChar( LIP.pw );

	char Id[40]; // Finito prevents sql injection
	char Pw[40]; // Finito prevents sql injection 
	ConvertQueryString(LIP.id, Id, 40); // Finito prevents sql injection
	ConvertQueryString(LIP.pw, Pw, 40); // Finito prevents sql injection

	sprintf(szQuerry, "SELECT   Memidx,Uid FROM NgcTempUser WHERE (Utid = '%s%s')", Id,Pw);//일본 DB참조//TID로 ID 가져오기.

	SQLAllocStmt(hDBC_NGCDB, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{															
		retCode = SQLFetch(hStmt);
		if( retCode != SQL_SUCCESS) 
		{
			goto ERROR_NO_ID_;	// 등록되지 않은 ID입니다. 
		}
		retCode = ::SQLGetData(hStmt, 1, SQL_C_LONG,	&LIP.index,	ID_LENGTH, &cbValue);
		
		char szID[ID_LENGTH]= {0,};
		retCode = ::SQLGetData(hStmt, 2, SQL_C_CHAR,		szID,	ID_LENGTH, &cbValue);
		::EatRearWhiteChar( szID );
		::CharUpper( szID );
		::strcpy(connections[nCn].id,szID);
		::strcpy(LIP.id,szID);
		::SQLFreeStmt(hStmt, SQL_DROP);
		return 100;//일본인 경우 공짜입니다. NGC에서 과금을 하기 때문에.
	}
ERROR_NO_ID_:

	::SQLFreeStmt(hStmt, SQL_DROP);	
	return BT_WRONG_ID;							// 그런 ID없음.
}

int COnePass::CheckGameBangIPAccount_SQL( DWORD ip_idx, int &IP_TimeRemain)
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	char		szQuerry[255];

	if(LocalMgr.IsAbleNation(TAIWAN|CHINA|HONGKONG))//021007 lsw
	{
		IP_TimeRemain = 0;
		return 0;
	}

	sprintf(szQuerry, "select timeremain from IP_ACCOUNT where ip_idx ='%d'", ip_idx );

	SQLAllocStmt(hDBC_TotalDB, &hStmt);

	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{		
		retCode = SQLFetch(hStmt);
			
		if( retCode == SQL_SUCCESS ) // 등록된 IP가 존재함. 
		{	
			SQLGetData(hStmt, 1, SQL_C_ULONG, &IP_TimeRemain, 0, &cbValue);
			SQLFreeStmt(hStmt, SQL_DROP);			
			return IP_TimeRemain;
		}
	}
	SQLFreeStmt(hStmt, SQL_DROP);	
	return -1;
}

bool COnePass::CheckLimitedAgeAndTime(const char* szID) // 30929 kyo
{
	if(NULL == szID )
	{
		return false;
	}

	::prepare( connections );
	if( IsLimitedTime() )
	{
		int nAge = GetUserAge( szID );
		int nLimitedAge = ::GetPrivateProfileInt( "Thai Limited", "Age", 18, DB_DEMON_INI_ );
		if( nAge < nLimitedAge || nAge <=0 )
		{
			return true;
		}		
	}
	return false;	
}

