// LottoDBMgr.cpp: implementation of the CLottoDBMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "network.h"
#include "LottoDBMgr.h"
#include "sql.h"
#include "sqlext.h"
#include "Hong_Sub.h"
#include "Mylog.h"
#include <direct.h>
#include <STDIO.H>
#include "dragonLoginServer2.h" // For ConvertQueryString



#define SADONIX_NO	1046
#define SQLOK( x ) ( (x) == SQL_SUCCESS_WITH_INFO || (x) == SQL_SUCCESS )		//1027 YGI
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLottoDBMgr* CLottoDBMgr::m_pClass = NULL;
CLottoDBMgr::CLottoDBMgr()
{
	Clear();
	m_pClass = this;
	m_nLottoNumberCount = 4;//현재는 네개의 번호만으로 한다.
//	m_nGiveItemNumber = SADONIX_NO;//기본은 사드 오닉스를 준다.
	memset(m_anGiveItemNumber,0,sizeof(int)*5);//등수별로 지급되는 아이템 번호.
	memset(m_anItemCount4Grade,0,sizeof(int)*5);//등수별로 지급되는 아이템 겟수.
	memset(m_anWinNumberCount4Grade,0,sizeof(int)*5);//몇개의 전호가 맞아야 몇등인가..
	memset(m_anWinNumbers,0,sizeof(int)*10);
	m_nLottoPay = 0;
	mkdir( "LotteryLog" );
}

CLottoDBMgr::~CLottoDBMgr()
{

	Clear();
}

void CLottoDBMgr::Clear()
{
//	memset(&m_Lotto_Info,0,sizeof(m_Lotto_Info));
	m_pClass = NULL;
	m_hDragonDB = NULL;
}


bool CLottoDBMgr::LoadTable(HDBC hDBC)
{
//	memset(&m_Lotto_Info,0,sizeof(m_Lotto_Info));
	
	m_hDragonDB	 = hDBC;

	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	char		szQuerry[512];

	sprintf(szQuerry, "SELECT * FROM Lotto_Setting");
	SQLAllocStmt(m_hDragonDB, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);

	if (!SQLOK(retCode))
	{
		MyLog(0,"Lotto_Setting Table ....Loading Error!!!!");
		SQLFreeStmt(hStmt, SQL_DROP);
		return 0;
	}
	retCode = SQLFetch(hStmt);
	if (!SQLOK(retCode))
	{
		MyLog(0,"Lotto_Setting Table ....No Data!!!!");		
		SQLFreeStmt(hStmt, SQL_DROP);
		return 0;
	}
	SQLGetData(hStmt,1,SQL_C_LONG,&m_nLottoNumberCount,0,&cbValue);

	SQLGetData(hStmt,2,SQL_C_LONG,&m_anGiveItemNumber[0],0,&cbValue);
	SQLGetData(hStmt,3,SQL_C_LONG,&m_anGiveItemNumber[1],0,&cbValue);
	SQLGetData(hStmt,4,SQL_C_LONG,&m_anGiveItemNumber[2],0,&cbValue);
	SQLGetData(hStmt,5,SQL_C_LONG,&m_anGiveItemNumber[3],0,&cbValue);
	SQLGetData(hStmt,6,SQL_C_LONG,&m_anGiveItemNumber[4],0,&cbValue);

	SQLGetData(hStmt,7,SQL_C_LONG,&m_anItemCount4Grade[0],0,&cbValue);
	SQLGetData(hStmt,8,SQL_C_LONG,&m_anItemCount4Grade[1],0,&cbValue);
	SQLGetData(hStmt,9,SQL_C_LONG,&m_anItemCount4Grade[2],0,&cbValue);
	SQLGetData(hStmt,10,SQL_C_LONG,&m_anItemCount4Grade[3],0,&cbValue);
	SQLGetData(hStmt,11,SQL_C_LONG,&m_anItemCount4Grade[4],0,&cbValue);

	SQLGetData(hStmt,12,SQL_C_LONG,&m_anWinNumberCount4Grade[0],0,&cbValue);
	SQLGetData(hStmt,13,SQL_C_LONG,&m_anWinNumberCount4Grade[1],0,&cbValue);
	SQLGetData(hStmt,14,SQL_C_LONG,&m_anWinNumberCount4Grade[2],0,&cbValue);
	SQLGetData(hStmt,15,SQL_C_LONG,&m_anWinNumberCount4Grade[3],0,&cbValue);
	SQLGetData(hStmt,16,SQL_C_LONG,&m_anWinNumberCount4Grade[4],0,&cbValue);

	SQLGetData(hStmt,17,SQL_C_LONG,&m_nLottoPay,0,&cbValue);

	SQLFreeStmt(hStmt, SQL_DROP);



	sprintf(szQuerry, "SELECT * FROM Lotto_Event");
	SQLAllocStmt(m_hDragonDB, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);

	
	if (!SQLOK(retCode))
	{
		SQLFreeStmt(hStmt, SQL_DROP);
		return 0;
	}	
	
	retCode = SQLFetch(hStmt);
	
	if(!SQLOK(retCode))//테이블에 내용이 없다
	{
		SQLFreeStmt(hStmt, SQL_DROP);
		return false;
	}

	while (SQLOK(retCode))
	{	

/*		
		SQLGetData(hStmt, 1, SQL_C_LONG, &m_Lotto_Info.nLottoID, 0, &cbValue);//LottoID 마지막 회차의 로또 아이디가 로드 된다.
		SQLGetData(hStmt, 2, SQL_C_LONG, &m_Lotto_Info.StartDate.tm_year, 0, &cbValue);
		SQLGetData(hStmt, 3, SQL_C_LONG, &m_Lotto_Info.StartDate.tm_mon, 0, &cbValue);
		SQLGetData(hStmt, 4, SQL_C_LONG, &m_Lotto_Info.StartDate.tm_wday, 0, &cbValue);
		SQLGetData(hStmt, 5, SQL_C_LONG, &m_Lotto_Info.LotteryDate.tm_year, 0, &cbValue);
		SQLGetData(hStmt, 6, SQL_C_LONG, &m_Lotto_Info.LotteryDate.tm_mon, 0, &cbValue);
		SQLGetData(hStmt, 7, SQL_C_LONG, &m_Lotto_Info.LotteryDate.tm_wday, 0, &cbValue);
		SQLGetData(hStmt, 8, SQL_C_LONG, &m_Lotto_Info.nWinNumCount, 0, &cbValue);
*/
		SQLGetData(hStmt, 9, SQL_C_LONG, &m_anWinNumbers[0], 0, &cbValue);
		SQLGetData(hStmt, 10, SQL_C_LONG, &m_anWinNumbers[1], 0, &cbValue);
		SQLGetData(hStmt, 11, SQL_C_LONG, &m_anWinNumbers[2], 0, &cbValue);
		SQLGetData(hStmt, 12, SQL_C_LONG, &m_anWinNumbers[3], 0, &cbValue);
		SQLGetData(hStmt, 13, SQL_C_LONG, &m_anWinNumbers[4], 0, &cbValue);
		SQLGetData(hStmt, 14, SQL_C_LONG, &m_anWinNumbers[5], 0, &cbValue);
		SQLGetData(hStmt, 15, SQL_C_LONG, &m_anWinNumbers[6], 0, &cbValue);
		SQLGetData(hStmt, 16, SQL_C_LONG, &m_anWinNumbers[7], 0, &cbValue);
		SQLGetData(hStmt, 17, SQL_C_LONG, &m_anWinNumbers[8], 0, &cbValue);
		SQLGetData(hStmt, 18, SQL_C_LONG, &m_anWinNumbers[9], 0, &cbValue);

		retCode = SQLFetch(hStmt);

	}

	SQLFreeStmt(hStmt, SQL_DROP);
	return true;

}

void CLottoDBMgr::RecvNewEvent(LOTTO_EVENT_INFO* pInfo,int cn)
{
//	if(m_Lotto_Info.nLottoID >= pInfo->nLottoID)return;//이전 로또 회차가 새로운것보다 크면 아무일도.

	//Lotte_User 테이블을 깔끔히...하기 전에. 로그를 남기자.
	char		szQuerry[512];
	char		szFileName[512];
	RETCODE		retCode;
	HSTMT		hStmt = NULL;
		
	sprintf(szQuerry, "SELECT * from Lotto_Users order by User_ID");
	sprintf(szFileName,"./LotteryLog/_%dUsers.txt",pInfo->nLottoID - 1);//soto-031126

	
	FILE* fp = fopen( szFileName, "at+" );//soto-031126
	if(fp != NULL)
	{
		SQLAllocStmt(m_hDragonDB, &hStmt);
		retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
		retCode = SQLFetch(hStmt);
		SDWORD		cbValue;
		while(SQLOK(retCode))
		{
			int ct = 0;
			char	szUserID[20]		= {0,};
			int		nLottoID			= 0;
			int		nLottoNumberCount	= 0;
			int		anLottoNumbers[10]	= {0,};
			
			::SQLGetData(hStmt,	++ct,	SQL_C_CHAR,	szUserID,	20,	&cbValue);
			::SQLGetData(hStmt,	++ct,	SQL_C_LONG,	&nLottoID,	0,	&cbValue);
			::SQLGetData(hStmt,	++ct,	SQL_C_LONG,	&nLottoNumberCount,	0,	&cbValue);
			::SQLGetData(hStmt,	++ct,	SQL_C_LONG,	&anLottoNumbers[0],	0,	&cbValue);
			::SQLGetData(hStmt,	++ct,	SQL_C_LONG,	&anLottoNumbers[1],	0,	&cbValue);
			::SQLGetData(hStmt,	++ct,	SQL_C_LONG,	&anLottoNumbers[2],	0,	&cbValue);
			::SQLGetData(hStmt,	++ct,	SQL_C_LONG,	&anLottoNumbers[3],	0,	&cbValue);
			::SQLGetData(hStmt,	++ct,	SQL_C_LONG,	&anLottoNumbers[4],	0,	&cbValue);
			::SQLGetData(hStmt,	++ct,	SQL_C_LONG,	&anLottoNumbers[5],	0,	&cbValue);
			::SQLGetData(hStmt,	++ct,	SQL_C_LONG,	&anLottoNumbers[6],	0,	&cbValue);
			::SQLGetData(hStmt,	++ct,	SQL_C_LONG,	&anLottoNumbers[7],	0,	&cbValue);
			::SQLGetData(hStmt,	++ct,	SQL_C_LONG,	&anLottoNumbers[8],	0,	&cbValue);
			::SQLGetData(hStmt,	++ct,	SQL_C_LONG,	&anLottoNumbers[9],	0,	&cbValue);

			::EatRearWhiteChar(szUserID);			
			fprintf(fp,"LottoID : %4d,   UserID : [%s],  LottoNumbers : ",nLottoID,szUserID);
			for(int i = 0; i < nLottoNumberCount;++i)
			{
				fprintf(fp,"  %2d",anLottoNumbers[i]);
			}
			fprintf(fp,"\n");

			retCode = SQLFetch(hStmt);
		}

		fclose(fp);
	}
	else
	{
		
	}
	
			
	if(m_hDragonDB)
	{
		
		sprintf(szQuerry, "DELETE from Lotto_Users");
		SQLAllocStmt(m_hDragonDB, &hStmt);
		retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
		if(!SQLOK(retCode))
		{
			SQLFreeStmt(hStmt, SQL_DROP);
			return;
		}
		SQLFreeStmt(hStmt, SQL_DROP);
		
	}
		
	SendNewEvent(pInfo,cn);

}

void CLottoDBMgr::SendNewEvent(LOTTO_EVENT_INFO *pInfo,int cn)
{
	if(InsertToTabeInfo(pInfo))
	{	
		t_packet p;
		p.h.header.type = CMD_NEW_EVENT;
		p.h.header.size = sizeof(LOTTO_EVENT_INFO);
//		memcpy(&m_Lotto_Info,pInfo,sizeof(LOTTO_EVENT_INFO));
		memset(m_anWinNumbers,0,sizeof(int)*10);
		memcpy(&p.u.Lotto_Info,pInfo,sizeof(LOTTO_EVENT_INFO));

		QueuePacket(connections,cn,&p,1);
	}
}

bool CLottoDBMgr::InsertToTabeInfo(LOTTO_EVENT_INFO *pInfo)
{
	if(m_hDragonDB)
	{
//		if(pInfo->nLottoID <= m_Lotto_Info.nLottoID)return false;

		HSTMT		hStmt = NULL;
		RETCODE		retCode;
		char		szQuerry[512];
		sprintf(szQuerry,
			"insert into Lotto_Event (Lotto_ID, StartYear, StartMonth, StartDay, LotteryYear, LotteryMonth, LotteryDay, WinNumCount, WinNumber1,WinNumber2,WinNumber3,WinNumber4,WinNumber5,WinNumber6,WinNumber7,WinNumber8,WinNumber9,WinNumber10) values ( %d , %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d )",
			pInfo->nLottoID,
			pInfo->StartDate.tm_year,pInfo->StartDate.tm_mon,pInfo->StartDate.tm_mday,
			pInfo->LotteryDate.tm_year,pInfo->LotteryDate.tm_mon,pInfo->LotteryDate.tm_mday,
			pInfo->nWinNumCount,
			pInfo->anWinNumbers[0],pInfo->anWinNumbers[1],pInfo->anWinNumbers[2],pInfo->anWinNumbers[3],pInfo->anWinNumbers[4],
			pInfo->anWinNumbers[5],pInfo->anWinNumbers[6],pInfo->anWinNumbers[7],pInfo->anWinNumbers[8],pInfo->anWinNumbers[9]
			);

		SQLAllocStmt(m_hDragonDB, &hStmt);
		retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
		SQLFreeStmt(hStmt, SQL_DROP);
		
		return SQLOK(retCode);
	}
	
	return false;
}

void CLottoDBMgr::RecvCanBuyLotto(t_BUY_LOTTO *pCanBuy,int cn)
{
	t_packet p;
	p.h.header.type = CMD_CAN_BUY;
	p.h.header.size = sizeof(t_BUY_LOTTO);

	strcpy(p.u.Lotto_Buy.strCharName,pCanBuy->strCharName);
	
	char	strUserID[21] = {NULL,};
	
	GetUserIDFromName(pCanBuy->strCharName,strUserID);

	if(!strlen(strUserID))
	{
		return;
	}

	int nBuyCount = GetBuyCountByUser(strUserID, pCanBuy->nLottoID);

	p.u.Lotto_Buy.nLottoID = pCanBuy->nLottoID;
	
	if(nBuyCount == 0)//무조건 살수 있다.
	{
		memcpy(p.u.Lotto_Buy.anLottoNumber,pCanBuy->anLottoNumber,sizeof(int)*10);
	}
	else//soto-Lotto추가 if(nBuyCount < 5)// 중복 번호 검사를 해야한다.
	{
		//soto-031126 수치 조절의 문제로 한국쪽에는 10장의 한계를 둔다.
		if(LocalMgr.IsAbleNation(KOREA))
		{
			if(nBuyCount < 10)	// BBD 040211 50장에서 10장 제한으로 변경됨
			{
				
			}
			else
			{	//< CSD-031127
				p.u.Lotto_Buy.anLottoNumber[0] = -2; // -2 복권을 많이 샀다.
				QueuePacket(connections,cn,&p,1);
				return;
			}	//> CSD-031127
			
		}

		if(!ExistLottoNumber(pCanBuy->anLottoNumber,strUserID,pCanBuy->nLottoID))//중복 되지 않았다.
		{
			memcpy(p.u.Lotto_Buy.anLottoNumber,pCanBuy->anLottoNumber,sizeof(int)*10);
		}
		else//중복 되는 번호가 있다.
		{
			p.u.Lotto_Buy.anLottoNumber[0] = -3; // -3 중복 되는 번호.
		}
	}

//soto-Lotto추가
/*
	else//살수 있는 만큼 다샀다.
	{
		p.u.Lotto_Buy.anLottoNumber[0] = -2; // -2 복권을 많이 샀다.
	}
*/
	QueuePacket(connections,cn,&p,1);
}


int CLottoDBMgr::GetBuyCountByUser(char *pUserID , int nLottoID)
{
	if(m_hDragonDB)
	{
		HSTMT		hStmt = NULL;
		RETCODE		retCode;

		char		szQuerry[512];

		int			nRet = 0;

		sprintf(szQuerry, "SELECT * FROM Lotto_Users WHERE User_ID = '%s' and Lotto_ID = %d",pUserID,nLottoID);
		SQLAllocStmt(m_hDragonDB, &hStmt);
		retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);

		retCode = SQLFetch(hStmt);
		if (!SQLOK(retCode))
		{
			SQLFreeStmt(hStmt, SQL_DROP);
			return nRet;
		}
		while(SQLOK(retCode))
		{
			nRet++;
			retCode = SQLFetch(hStmt);			
		}
		
		SQLFreeStmt(hStmt, SQL_DROP);
		
		return nRet;
	}
	return 0;
}

int CLottoDBMgr::ExistLottoNumber(int anNumber[], char *pUserID , int nLottoID)//soto-LottoADD
{
	if(m_hDragonDB)
	{
		HSTMT		hStmt = NULL;
		RETCODE		retCode;
		SDWORD		cbValue;
		char		szQuerry[512];

		int			nRet = 0;

		sprintf(szQuerry, "SELECT "
			"Lotto_Numbers1 Lotto_Numbers2 Lotto_Numbers3 Lotto_Numbers4  Lotto_Numbers5 "
			"Lotto_Numbers6 Lotto_Numbers7 Lotto_Numbers8 Lotto_Numbers9 Lotto_Numbers10 "
			"FROM Lotto_Users WHERE User_ID = '%s' and Lotto_ID = %d",
			pUserID, nLottoID);
		SQLAllocStmt(m_hDragonDB, &hStmt);
		retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
		retCode = SQLFetch(hStmt);

		if (!SQLOK(retCode))
		{
			SQLFreeStmt(hStmt, SQL_DROP);
			return nRet; //번호가 없다.넣어라.
		}
		
		int anLottoNum[10] = {0,};
		
		while(SQLOK(retCode))
		{
			int nSameNum = 0;
			int nCt = 1;
			SQLGetData(hStmt, nCt, SQL_C_LONG, &anLottoNum[nCt-1], 0, &cbValue);++nCt;
			SQLGetData(hStmt, nCt, SQL_C_LONG, &anLottoNum[nCt-1], 0, &cbValue);++nCt;
			SQLGetData(hStmt, nCt, SQL_C_LONG, &anLottoNum[nCt-1], 0, &cbValue);++nCt;
			SQLGetData(hStmt, nCt, SQL_C_LONG, &anLottoNum[nCt-1], 0, &cbValue);++nCt;
			SQLGetData(hStmt, nCt, SQL_C_LONG, &anLottoNum[nCt-1], 0, &cbValue);++nCt;
			SQLGetData(hStmt, nCt, SQL_C_LONG, &anLottoNum[nCt-1], 0, &cbValue);++nCt;
			SQLGetData(hStmt, nCt, SQL_C_LONG, &anLottoNum[nCt-1], 0, &cbValue);++nCt;
			SQLGetData(hStmt, nCt, SQL_C_LONG, &anLottoNum[nCt-1], 0, &cbValue);++nCt;
			SQLGetData(hStmt, nCt, SQL_C_LONG, &anLottoNum[nCt-1], 0, &cbValue);++nCt;
			SQLGetData(hStmt, nCt, SQL_C_LONG, &anLottoNum[nCt-1], 0, &cbValue);
						
				
			nSameNum = this->CheckTwoLottos(anNumber,anLottoNum,m_nLottoNumberCount);
							
			if(nSameNum >= m_nLottoNumberCount)
			{
				SQLFreeStmt(hStmt, SQL_DROP);
				return 1;//존재 한다. 넣지 마라.
			}
			retCode = SQLFetch(hStmt);
		}
	
		SQLFreeStmt(hStmt, SQL_DROP);
		
		return 0;//넣을수 있다.
	}

	return 1;//넣을수 없다.
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      

void CLottoDBMgr::GetUserIDFromName(const char *pName, char strID[])
{
	if(m_hDragonDB)
	{
		HSTMT		hStmt = NULL;
		RETCODE		retCode;
		SDWORD		cbValue;
		char		szQuerry[512];

		int			nRet = 0;

		char szName[20];
		ConvertQueryString(pName, szName, 20); // Finito prevents sql injection
		
		sprintf(szQuerry, "SELECT login_id FROM Chr_Info WHERE name = '%s'",szName);
		SQLAllocStmt(m_hDragonDB, &hStmt);
		retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);

		if (!SQLOK(retCode))
		{
			SQLFreeStmt(hStmt, SQL_DROP);
			return;
		}

		retCode = SQLFetch(hStmt);

		if(SQLOK(retCode))
		{
			SQLGetData(hStmt, 1, SQL_C_CHAR, strID, 20, &cbValue);
			::EatRearWhiteChar(strID);
		}
		SQLFreeStmt(hStmt, SQL_DROP);
	}
}

void CLottoDBMgr::RecvLottoBuy(t_BUY_LOTTO *pBuyLotto)
{
	if(m_hDragonDB)
	{
		HSTMT		hStmt = NULL;
		RETCODE		retCode;
		char		szQuerry[512];
		int			nLottoCount = 0;

		int			nRet = 0;

		char	strUserID[21] = {NULL,};
		GetUserIDFromName(pBuyLotto->strCharName,strUserID);

		if(!strlen(strUserID))return;		

		nLottoCount = m_nLottoNumberCount;
				
		sprintf(
			szQuerry,
			"insert into Lotto_Users "
			" values( '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
			strUserID, pBuyLotto->nLottoID, nLottoCount,
			pBuyLotto->anLottoNumber[0],
			pBuyLotto->anLottoNumber[1],
			pBuyLotto->anLottoNumber[2],
			pBuyLotto->anLottoNumber[3],
			pBuyLotto->anLottoNumber[4],
			pBuyLotto->anLottoNumber[5],
			pBuyLotto->anLottoNumber[6],
			pBuyLotto->anLottoNumber[7],
			pBuyLotto->anLottoNumber[8],
			pBuyLotto->anLottoNumber[9]
			);
		
		SQLAllocStmt(m_hDragonDB, &hStmt);
		retCode= SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
		if(!SQLOK(retCode))//삽입 실패.
		{
//			SQLFreeStmt(hStmt, SQL_DROP);
			printf("Lotto Insert failed  ID : %s , Name : %s",strUserID,pBuyLotto->strCharName);
//			return;
		}			
//		retCode = SQLExecute(hStmt) ;
				
		SQLFreeStmt(hStmt, SQL_DROP);
		return;			
	}
}

void CLottoDBMgr::RecvWinnerCheck(t_CHECK_WINNER *pCheckWinner, int cn)
{
	if(m_hDragonDB)
	{
		HSTMT		hStmt = NULL;
		RETCODE		retCode;
		SDWORD		cbValue;
		char		szQuerry[512];
		int			nLottoPaperCount = 0;
		
		char	strUserID[21] = {NULL,};
		GetUserIDFromName(pCheckWinner->strCharName,strUserID);

		if(!strlen(strUserID))return;		

		sprintf(szQuerry, "SELECT * FROM Lotto_Users WHERE [User_ID] = '%s' AND [Lotto_ID] = %d",strUserID,pCheckWinner->nLottoID);
		SQLAllocStmt(m_hDragonDB, &hStmt);
		retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);

		retCode = SQLFetch(hStmt);
		
		while(SQLOK(retCode))
		{
			nLottoPaperCount++;
			retCode = SQLFetch(hStmt);
		}
		SQLFreeStmt(hStmt, SQL_DROP);
		
		int	nItemCount = 0;

		if(nLottoPaperCount)
		{
			sprintf(szQuerry, "SELECT * FROM Lotto_Users WHERE [User_ID] = '%s' AND [Lotto_ID] = %d",strUserID,pCheckWinner->nLottoID);
			SQLAllocStmt(m_hDragonDB, &hStmt);
			retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
			WORD	ct = 4;

			int	anWinItemsCount[5] = {0,};

			
			retCode = SQLFetch(hStmt);
			if(SQLOK(retCode))//유저가 있다.
			{
				for(int i = 0;i < nLottoPaperCount;i++)
				{
					int anLottoNumber[10] = {0,};
					SQLGetData(hStmt,ct,SQL_C_LONG,&anLottoNumber[0],0,&cbValue);ct++;
					SQLGetData(hStmt,ct,SQL_C_LONG,&anLottoNumber[1],0,&cbValue);ct++;
					SQLGetData(hStmt,ct,SQL_C_LONG,&anLottoNumber[2],0,&cbValue);ct++;
					SQLGetData(hStmt,ct,SQL_C_LONG,&anLottoNumber[3],0,&cbValue);ct++;
					SQLGetData(hStmt,ct,SQL_C_LONG,&anLottoNumber[4],0,&cbValue);ct++;
					SQLGetData(hStmt,ct,SQL_C_LONG,&anLottoNumber[5],0,&cbValue);ct++;
					SQLGetData(hStmt,ct,SQL_C_LONG,&anLottoNumber[6],0,&cbValue);ct++;
					SQLGetData(hStmt,ct,SQL_C_LONG,&anLottoNumber[7],0,&cbValue);ct++;
					SQLGetData(hStmt,ct,SQL_C_LONG,&anLottoNumber[8],0,&cbValue);ct++;
					SQLGetData(hStmt,ct,SQL_C_LONG,&anLottoNumber[9],0,&cbValue);
					
					
					int nSame = 0;
					
					nSame = CheckTwoLottos(anLottoNumber,pCheckWinner->anWinNumbers,m_nLottoNumberCount);
					
					if(nSame == m_anWinNumberCount4Grade[0])
					{
						nItemCount += m_anItemCount4Grade[0];
						anWinItemsCount[0] += m_anItemCount4Grade[0];
					}
					else if(nSame == m_anWinNumberCount4Grade[1])
					{
						nItemCount += m_anItemCount4Grade[1];
						anWinItemsCount[1] += m_anItemCount4Grade[1];
					}
					else if(nSame == m_anWinNumberCount4Grade[2])
					{
						nItemCount += m_anItemCount4Grade[2];
						anWinItemsCount[2] += m_anItemCount4Grade[2];
					}
					else if(nSame == m_anWinNumberCount4Grade[3])
					{
						nItemCount += m_anItemCount4Grade[3];
						anWinItemsCount[3] += m_anItemCount4Grade[3];
					}
					else if(nSame == m_anWinNumberCount4Grade[4])
					{
						nItemCount += m_anItemCount4Grade[4];
						anWinItemsCount[4] += m_anItemCount4Grade[4];
					}

					retCode = SQLFetch(hStmt);
					ct = 4;
				}
			}
			else//그런 유저 없다.
			{

			}
			
			SQLFreeStmt(hStmt, SQL_DROP);
			
			t_packet	p;
			p.h.header.type = CMD_CHECK_OK;
			p.h.header.size = sizeof(t_CHECK_WINNER);

			memcpy(&p.u.Check_Winner,pCheckWinner,sizeof(t_CHECK_WINNER));
			p.u.Check_Winner.nWinItemCount = nItemCount;
			memcpy(p.u.Check_Winner.anWinItemsCount,anWinItemsCount,sizeof(int)*5);

			QueuePacket(connections,cn,&p,1);
		}
		//<! BBD 040127	맵서버에 메시지 보내서 블록을 풀어주라고 한다
		else	// 이놈은 한장도 않남았다. 블록만 풀고 끝내자
		{
			t_packet	p;
			p.h.header.type = CMD_DEL_LOTTO_USER_OK;
			p.h.header.size = sizeof(t_DEL_LOTTO_USER_OK);
			p.u.Lotto_Del_Ok.bIsDelOK = true;

			QueuePacket(connections,cn,&p,1);
		}
		//> BBD 040127	맵서버에 메시지 보내서 블록을 풀어주라고 한다
	}	
}

void CLottoDBMgr::RecvDelUser(t_CHECK_WINNER *pDelUser, int cn)		// BBD 040127 인자 추가
{
	if(m_hDragonDB)
	{
		HSTMT		hStmt = NULL;
		RETCODE		retCode;
		char		szQuerry[512];
		int			nLottoCount = 0;
		
		char	strUserID[21] = {NULL,};
		GetUserIDFromName(pDelUser->strCharName,strUserID);

		if(!strlen(strUserID))return;

		sprintf(szQuerry, "DELETE from Lotto_Users WHERE User_ID = '%s'",strUserID);
		SQLAllocStmt(m_hDragonDB, &hStmt);
		retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
		
		SQLFreeStmt(hStmt, SQL_DROP);
		//<! BBD 040127	정상적으로 유저를 삭제하였음을 맵서버에 알린다
		// 만일 retCode가 문제있다면 어떻게 롤백시킬것인가? 일단 로그만 남기자
		if(retCode != SQL_SUCCESS)
		{
			FILE *fp;
			fp = fopen( "QuerryError.txt","at+" );
			if( fp )
			{
				fprintf( fp, szQuerry );
				fclose(fp);
			}
		}

		t_packet	p;
		p.h.header.type = CMD_DEL_LOTTO_USER_OK;
		p.h.header.size = sizeof(t_DEL_LOTTO_USER_OK);
		p.u.Lotto_Del_Ok.bIsDelOK = true;

		QueuePacket(connections,cn,&p,1);
		//> BBD 040127	정상적으로 유저를 삭제하였음을 맵서버에 알린다
	}
}

int CLottoDBMgr::CheckTwoLottos(int anTarget[], int anSource[], int count)
{
	int nCount = 0;
	for(int i = 0;i < count;i++)
	{
		for(int j = 0;j < count;j++)
		{
			if(anTarget[i] == anSource[j])
				nCount++;
		}
	}

	return nCount;
}

void CLottoDBMgr::RecvLottery(LOTTO_EVENT_INFO *pLottery,int cn)
{
//	memcpy(&m_Lotto_Info,pLottery,sizeof(LOTTO_EVENT_INFO));
	
	if(m_hDragonDB)
	{
		HSTMT		hStmt = NULL;
		RETCODE		retCode;
		char		szQuerry[512];
		int			nLottoCount = 0;
				
		sprintf(
			szQuerry,
			"Update Lotto_Event set "
			"LotteryYear = %d, LotteryMonth = %d, LotteryDay = %d, WinNumCount = %d, "
			"WinNumber1 = %d, WinNumber2 = %d, WinNumber3 = %d, WinNumber4 = %d, WinNumber5 = %d, WinNumber6 = %d"
			", WinNumber7 = %d , WinNumber8 = %d, WinNumber9 = %d, WinNumber10 = %d WHERE Lotto_ID = %d",
			pLottery->LotteryDate.tm_year, pLottery->LotteryDate.tm_mon, pLottery->LotteryDate.tm_mday,
			pLottery->nWinNumCount,
			pLottery->anWinNumbers[0],pLottery->anWinNumbers[1],pLottery->anWinNumbers[2],pLottery->anWinNumbers[3],pLottery->anWinNumbers[4],
			pLottery->anWinNumbers[5],pLottery->anWinNumbers[6],pLottery->anWinNumbers[7],pLottery->anWinNumbers[8],pLottery->anWinNumbers[9],
			pLottery->nLottoID
			);
		SQLAllocStmt(m_hDragonDB, &hStmt);
		retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
		
		if(!SQLOK(retCode))
		{
			MyLog(0,"Lotto  Lotto_Event Update...Fail.... Lotto Emergency!!!!!!!!!!");
		}
		SQLFreeStmt(hStmt, SQL_DROP);

		memcpy(m_anWinNumbers,pLottery->anWinNumbers,sizeof(int)*10);
	}
	
	t_packet	p;
	p.h.header.type = CMD_LOTTERY_INFO;
	p.h.header.size = sizeof(LOTTO_EVENT_INFO);
	
	memcpy(&p.u.Lotto_Info,pLottery,sizeof(LOTTO_EVENT_INFO));

	QueuePacket(connections,cn,&p,1);//맵 서버로 보내 준다.
}

void CLottoDBMgr::RecvCheckOpenWinnerMenu(t_WINNER_MENU *pWinnerMenu,int cn)
{
	if(m_hDragonDB)
	{
		HSTMT		hStmt = NULL;
		RETCODE		retCode;
		SDWORD		cbValue;
		char		szQuerry[512];
		int			nLottoPaperCount = 0;
				
		
		char	strUserID[21] = {NULL,};
		GetUserIDFromName(pWinnerMenu->strCharName,strUserID);

		if(!strlen(strUserID))return;	

		sprintf(szQuerry, "SELECT * FROM Lotto_Users WHERE User_ID = '%s' AND Lotto_ID = %d",strUserID,pWinnerMenu->nLottoID);
		SQLAllocStmt(m_hDragonDB, &hStmt);
		retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);

		t_packet	p;
		p.h.header.type = CMD_CHECK_WINNER_MENU;
		p.h.header.size = sizeof(t_WINNER_MENU);
		memcpy(&p.u.Lotto_Winner_Menu,pWinnerMenu,sizeof(t_WINNER_MENU));

//		p.u.Lotto_Winner_Menu.nPage = 1;
		p.u.Lotto_Winner_Menu.nViewCount = 0;
		memset(p.u.Lotto_Winner_Menu.anLottoNumber,0,sizeof(int)*10*5);
		memset(p.u.Lotto_Winner_Menu.anWinNumbers,0,sizeof(int)*10);

		retCode = SQLFetch(hStmt);//첫번째줄이 있는가.
		while(SQLOK(retCode))
		{
			if(nLottoPaperCount >= 5)break;
			SQLGetData(hStmt,4,SQL_C_LONG,&p.u.Lotto_Winner_Menu.anLottoNumber[nLottoPaperCount][0],4,&cbValue);
			SQLGetData(hStmt,5,SQL_C_LONG,&p.u.Lotto_Winner_Menu.anLottoNumber[nLottoPaperCount][1],4,&cbValue);
			SQLGetData(hStmt,6,SQL_C_LONG,&p.u.Lotto_Winner_Menu.anLottoNumber[nLottoPaperCount][2],4,&cbValue);
			SQLGetData(hStmt,7,SQL_C_LONG,&p.u.Lotto_Winner_Menu.anLottoNumber[nLottoPaperCount][3],4,&cbValue);
			SQLGetData(hStmt,8,SQL_C_LONG,&p.u.Lotto_Winner_Menu.anLottoNumber[nLottoPaperCount][4],4,&cbValue);
			SQLGetData(hStmt,9,SQL_C_LONG,&p.u.Lotto_Winner_Menu.anLottoNumber[nLottoPaperCount][5],4,&cbValue);
			SQLGetData(hStmt,10,SQL_C_LONG,&p.u.Lotto_Winner_Menu.anLottoNumber[nLottoPaperCount][6],4,&cbValue);
			SQLGetData(hStmt,11,SQL_C_LONG,&p.u.Lotto_Winner_Menu.anLottoNumber[nLottoPaperCount][7],4,&cbValue);
			SQLGetData(hStmt,12,SQL_C_LONG,&p.u.Lotto_Winner_Menu.anLottoNumber[nLottoPaperCount][8],4,&cbValue);
			SQLGetData(hStmt,13,SQL_C_LONG,&p.u.Lotto_Winner_Menu.anLottoNumber[nLottoPaperCount][9],4,&cbValue);
			nLottoPaperCount++;
			retCode = SQLFetch(hStmt);
		}
		SQLFreeStmt(hStmt, SQL_DROP);


		p.u.Lotto_Winner_Menu.nViewCount = nLottoPaperCount;
		memcpy(p.u.Lotto_Winner_Menu.anWinNumbers,m_anWinNumbers,sizeof(int)*10);
		p.u.Lotto_Winner_Menu.nTotalLottoCount = GetLottoCount(p.u.Lotto_Winner_Menu.strCharName,p.u.Lotto_Winner_Menu.nLottoID);

		::QueuePacket(connections,cn,&p,1);
	}
}

int CLottoDBMgr::GetLottoPay()
{
	return m_nLottoPay;
}

void CLottoDBMgr::RecvLottoSeek(t_LOTTOPAPER_SEEK *pLotto_Seek, int cn)
{
	packet p;
	p.h.header.type = CMD_LOTTO_SEEK;
	p.h.header.size = sizeof(t_LOTTOPAPER_SEEK);
	
	memcpy(&p.u.Lotto_Seek,pLotto_Seek,sizeof(t_LOTTOPAPER_SEEK));
	
	int			nLottoPaperCount = 0;

	if(m_hDragonDB)
	{
		HSTMT		hStmt = NULL;
		RETCODE		retCode;
		SDWORD		cbValue;
		char		szQuerry[512];
		


		char	strUserID[21] = {NULL,};
		GetUserIDFromName(pLotto_Seek->strChrName,strUserID);

		if(!strlen(strUserID))return;

		sprintf(szQuerry, "SELECT * FROM Lotto_Users WHERE User_ID = '%s' AND Lotto_ID = %d",strUserID,pLotto_Seek->nLottoID);

		SQLAllocStmt(m_hDragonDB, &hStmt);
		retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);

		for(int i = 0;i < ((pLotto_Seek->nPage-1) * 5);++i)
		{
			retCode = SQLFetch(hStmt);
			if(!SQLOK(retCode))break;
		}

		retCode = SQLFetch(hStmt);
		while(SQLOK(retCode))
		{
			if(nLottoPaperCount >= 5)break;
			SQLGetData(hStmt,4,SQL_C_LONG,&p.u.Lotto_Seek.anLottoNumber[nLottoPaperCount][0],4,&cbValue);
			SQLGetData(hStmt,5,SQL_C_LONG,&p.u.Lotto_Seek.anLottoNumber[nLottoPaperCount][1],4,&cbValue);
			SQLGetData(hStmt,6,SQL_C_LONG,&p.u.Lotto_Seek.anLottoNumber[nLottoPaperCount][2],4,&cbValue);
			SQLGetData(hStmt,7,SQL_C_LONG,&p.u.Lotto_Seek.anLottoNumber[nLottoPaperCount][3],4,&cbValue);
			SQLGetData(hStmt,8,SQL_C_LONG,&p.u.Lotto_Seek.anLottoNumber[nLottoPaperCount][4],4,&cbValue);
			SQLGetData(hStmt,9,SQL_C_LONG,&p.u.Lotto_Seek.anLottoNumber[nLottoPaperCount][5],4,&cbValue);
			SQLGetData(hStmt,10,SQL_C_LONG,&p.u.Lotto_Seek.anLottoNumber[nLottoPaperCount][6],4,&cbValue);
			SQLGetData(hStmt,11,SQL_C_LONG,&p.u.Lotto_Seek.anLottoNumber[nLottoPaperCount][7],4,&cbValue);
			SQLGetData(hStmt,12,SQL_C_LONG,&p.u.Lotto_Seek.anLottoNumber[nLottoPaperCount][8],4,&cbValue);
			SQLGetData(hStmt,13,SQL_C_LONG,&p.u.Lotto_Seek.anLottoNumber[nLottoPaperCount][9],4,&cbValue);
			nLottoPaperCount++;
			retCode = SQLFetch(hStmt);
		}

		SQLFreeStmt(hStmt, SQL_DROP);
	}

	if(nLottoPaperCount <= 0)
	{
		p.u.Lotto_Seek.nPage = 0;
	}
	
	p.u.Lotto_Seek.nViewCount = nLottoPaperCount;

	QueuePacket(connections,cn,&p,1);
}

int CLottoDBMgr::GetLottoCount(const char *pCharName, int nLottoID)
{
	int nRet = -1;
	if(m_hDragonDB)
	{
		HSTMT		hStmt = NULL;
		RETCODE		retCode;
		SDWORD		cbValue;
		char		szQuerry[512];
		int			nLottoPaperCount = 0;


		char	strUserID[21] = {NULL,};
		GetUserIDFromName(pCharName,strUserID);

		if(!strlen(strUserID))return nRet;

		sprintf(szQuerry, "SELECT count(*) FROM Lotto_Users WHERE User_ID = '%s' AND Lotto_ID = %d",strUserID,nLottoID);

		SQLAllocStmt(m_hDragonDB, &hStmt);
		retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
		retCode = SQLFetch(hStmt);

		if(SQLOK(retCode))
		{
			SQLGetData(hStmt,1,SQL_C_LONG,&nLottoPaperCount,0,&cbValue);
			nRet = nLottoPaperCount;
		}

		SQLFreeStmt(hStmt, SQL_DROP);

	}
	
	return nRet;
}
