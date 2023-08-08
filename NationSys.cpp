#include "stdafx.h"
#include "MAIN.H"
//#include <sqltypes.h>
//#include "define.h"
//#include "NetWork.h"
//#include "ServerTable.h"
#include "dragonLoginServer2.h" // For ConvertQueryString

// Extern Variable_____________________________________
extern HENV hEnv ;
extern HDBC hDBC ;
//______________________________________________________

extern void MyLog( int type, char *logmsg, ... );

void RecvCMD_SET_COMMANDER(t_packet *p, t_connection c[], int cn )	// 사령관의 데이터를 세트한다.
{
	NW_Character tempNWCharacter;
	DWORD		 tempDWORD;

	HSTMT	hStmt=NULL;
	RETCODE	ret;
	SWORD	nClos;
	char	query_stmt[80]={0,};
	SDWORD	cbValue;

	char szCommanderName[20];
	ConvertQueryString(p->u.NationWar.SetCommander.CommanderName, szCommanderName, 20); // Finito prevents sql injection

	SQLAllocStmt(hDBC,&hStmt);

	wsprintf(query_stmt,"select fame_pk from chr_info where name='%s'", szCommanderName);

	ret = SQLExecDirect(hStmt,(UCHAR*)query_stmt,SQL_NTS);
	if (ret!=SQL_SUCCESS_WITH_INFO && ret !=SQL_SUCCESS)
	{
		MyLog(0,"Query Failure!! RecvCMD_SET_COMMANDER..");
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}

	SQLNumResultCols(hStmt,&nClos);

	ret=SQLFetch(hStmt);
	if (ret!=SQL_SUCCESS_WITH_INFO && ret !=SQL_SUCCESS)
	{
		//MyLog(0,"WarField Fetch Error!!");
		SQLFreeStmt(hStmt,SQL_DROP);
		return ;
	}

	ret=SQLGetData(hStmt,1,SQL_C_SLONG,&tempDWORD,sizeof(int),&cbValue);
	if (ret!=SQL_SUCCESS_WITH_INFO && ret!=SQL_SUCCESS)
	{
		MyLog(0,"SQL Return Error(%d)!!",ret);
		SQLFreeStmt(hStmt,SQL_DROP);
		return ;
	}   

    SQLFreeStmt(hStmt,SQL_DROP);

	memcpy(&tempNWCharacter,&tempDWORD,sizeof(DWORD));

	tempNWCharacter.isCommander=1;

	memcpy(&tempDWORD,&tempNWCharacter,sizeof(DWORD));

	memcpy(&tempNWCharacter,&tempDWORD,sizeof(DWORD));

	SQLAllocStmt(hDBC,&hStmt);

	wsprintf(query_stmt,"update chr_info set fame_pk=%d where name='%s'",tempDWORD, szCommanderName);
	ret=SQLExecDirect(hStmt,(UCHAR*)query_stmt,SQL_NTS);
	if (ret!=SQL_SUCCESS_WITH_INFO && ret!=SQL_SUCCESS)
	{
		MyLog(0,"Update Query Failure!! RecvCMD_SET_COMMANDER..");
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}
	
	SQLFreeStmt(hStmt,SQL_DROP);
}

void RecvCMD_SET_WARFIELD_POSSESSION(t_packet *p, t_connection c[], int cn )
{
	HSTMT	hStmt=NULL;
	RETCODE	ret;
	char	query_stmt[80]={0,};

	SQLAllocStmt(hDBC,&hStmt);

	wsprintf(query_stmt,"update WarfieldTBL set NationCode=%d where WarfieldCode=%d",p->u.NationWar.SWarfieldPossession.Possession,p->u.NationWar.SWarfieldPossession.WarfieldNo);

	ret = SQLExecDirect(hStmt,(UCHAR*)query_stmt,SQL_NTS);
	if (ret!=SQL_SUCCESS_WITH_INFO && ret !=SQL_SUCCESS)
	{
		MyLog(0,"Update Query Failure!! RecvCMD_SET_WARFIELD_POSSESION");
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}
	SQLFreeStmt(hStmt,SQL_DROP);
}

void CheckEventJoin(CHARLIST *ch)		// 020115 LTS
{
	HSTMT	hStmt=NULL;
	RETCODE	ret;
	SWORD	nClos;
	char	query_stmt[80]={0,};
	SDWORD	cbValue;
	int		tempEventJoin[8];

	//ch->EventJoin=1;	// 나중에 나머지는 주석 처리 한다.

	SQLAllocStmt(hDBC,&hStmt);

	wsprintf(query_stmt,"select * from EventUser Where CharacterName='%s'",ch->Name);
	ret = SQLExecDirect(hStmt,(UCHAR*)query_stmt,SQL_NTS);
	if (ret!=SQL_SUCCESS_WITH_INFO && ret !=SQL_SUCCESS)
	{
		//MyLog(0,"Query Failure!! Event User Data.. (Not Join Event..)");
		SQLFreeStmt(hStmt,SQL_DROP);
		memset(&ch->EventJoin,0,1);
		return;
	}
	SQLNumResultCols(hStmt,&nClos);

	ret=SQLFetch(hStmt);
	if (ret!=SQL_SUCCESS_WITH_INFO && ret !=SQL_SUCCESS)
	{
		//MyLog(0,"Query Failure!! Event User Data.. (Not Join Event..)");
		SQLFreeStmt(hStmt,SQL_DROP);
		memset(&ch->EventJoin,0,1);
		return ;
	}
	for (int i=0;i<8;i++)
	{
		ret=SQLGetData(hStmt,3+i,SQL_C_SLONG,&tempEventJoin[i],sizeof(int),&cbValue);	// Event1
		if (ret!=SQL_SUCCESS_WITH_INFO && ret!=SQL_SUCCESS)
		{
			MyLog(0,"Query Failure!! Event User Data.. (Get Data..)",ret);
			SQLFreeStmt(hStmt,SQL_DROP);
			memset(&ch->EventJoin,0,1);
			return ;
		}   
	}

    SQLFreeStmt(hStmt,SQL_DROP);

	ch->EventJoin.Event1=tempEventJoin[0];
	ch->EventJoin.Event2=tempEventJoin[1];
	ch->EventJoin.Event3=tempEventJoin[2];
	ch->EventJoin.Event4=tempEventJoin[3];
	ch->EventJoin.Event5=tempEventJoin[4];
	ch->EventJoin.Event6=tempEventJoin[5];
	ch->EventJoin.Event7=tempEventJoin[6];
	ch->EventJoin.Event8=tempEventJoin[7];
}
void RecvCMD_DELETE_EVENT_JOIN(t_packet *p, t_connection c[], int cn )
{
	HSTMT	hStmt=NULL;
	RETCODE	ret;
	char	query_stmt[80]={0,};

	SQLAllocStmt(hDBC,&hStmt);

	char szCharacterName[20];
	ConvertQueryString(p->u.NationWar.DeleteEventJoin.UserName, szCharacterName, 20); // Finito prevents sql injection

	wsprintf(query_stmt,"update EventUser set Event%d=0 where CharacterName='%s'",p->u.NationWar.DeleteEventJoin.EventNo,szCharacterName);

	ret = SQLExecDirect(hStmt,(UCHAR*)query_stmt,SQL_NTS);
	if (ret!=SQL_SUCCESS_WITH_INFO && ret !=SQL_SUCCESS)
	{
		MyLog(0,"EventUser Set 1 Error!!!!! : User Name : %s, EventNo : %d",p->u.NationWar.DeleteEventJoin.UserName,p->u.NationWar.DeleteEventJoin.EventNo);
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}
	MyLog(0,"EventUser Set 1 : User Name : %s, EventNo : %d",p->u.NationWar.DeleteEventJoin.UserName,p->u.NationWar.DeleteEventJoin.EventNo);
	SQLFreeStmt(hStmt,SQL_DROP);
}

void RecvCMD_SAVE_WARNO(t_packet *p, t_connection c[], int cn )
{
	HSTMT	hStmt=NULL;
	RETCODE	ret;
	char	query_stmt[80]={0,};

	SQLAllocStmt(hDBC,&hStmt);
	wsprintf(query_stmt,"update WarStartUpTBL set DayofWeek=%d where Type=-1",p->u.NationWar.CommonDataDw);

	ret = SQLExecDirect(hStmt,(UCHAR*)query_stmt,SQL_NTS);
	if (ret!=SQL_SUCCESS_WITH_INFO && ret !=SQL_SUCCESS)
	{
		MyLog(0,"Update WarNo Error!!");
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}
	MyLog(0,"Update WarNo : %d",p->u.NationWar.CommonDataDw.Data);
	SQLFreeStmt(hStmt,SQL_DROP);
}

int CheckHandleByNationWar(t_packet *p, t_connection c[], int cn )
{
	switch( p->h.header.type )
	{
	case CMD_SET_COMMANDER : 
													RecvCMD_SET_COMMANDER(p,c,cn);
													break;
	case CMD_SET_WARFIELD_POSSESSION :
													RecvCMD_SET_WARFIELD_POSSESSION(p,c,cn);
													break;
	case CMD_DELETE_EVENT_JOIN :
													RecvCMD_DELETE_EVENT_JOIN(p,c,cn);
													break;
	case CMD_SAVE_WARNO :
													RecvCMD_SAVE_WARNO(p,c,cn);
													break;

	}
	return true;
} 