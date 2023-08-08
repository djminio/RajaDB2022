#include "StdAfx.h"
#include "packed.h"
#include "servertable.h"
#include "MAIN.H"
#include "Scrp_exe.H"
#include "ID.h"
#include "SealStone.h"
#include "Debug.h"
#include "mainheader.h"
#include "monitor.h"
#include "Citem.h"
#include "Pay.h"
#include "network.h"
#include "dragonLoginServer2.h" // For ConvertQueryString

#define MAX_CHR_LOG_	1000

typedef struct chr_log
{
	int index;
	char id[ NM_LENGTH];
	char name[ NM_LENGTH];

	char state;
	char Level;
	int	 fame_pk;	// 010915 LTS	//Fame_PK -> NWCharacter로 교체 DB에는 실제로 NWCharacter의 값이 들어갑니다.		
	NW_Character	NWCharacter;	// 010915 LTS
	int  Str;
	int  Con;
	int  Dex;
	int  Wis;
	int  Int;
	int  MoveP;
	int  Char;
	int  Endu;
	int  Moral;
	int  Luck;
	int  wsps;

	int  Tactics;
	DWORD nation;	

	DWORD Money;
	int HpMax ;
	int ManaMax;

	char MapName[ NM_LENGTH];
	int HungryMax;

	int Resis_Poison;
	int Resis_Stone	;
	int Resis_Magic	;
	int Resis_Fire	;
	int Resis_Ice	;
	int Resis_Elect	;

	int X, Y;

	int		reserved_point;
	DWORD	BankMoney;
	DWORD	Exp;

	char Skill[ SIZE_OF_SKILL];
	char skillexp[ SIZE_OF_SKILL_EXP];
	char tac_skillEXP[ SIZE_OF_TAC_SKILL_EXP];
	char equip[ SIZE_OF_EQUIP];
	char quick[ SIZE_OF_QUICK];
	char inv[ SIZE_OF_INV];
	char bankitem[ SIZE_OF_BANKITEM];

	struct chr_log	*next;
	struct chr_log	*prev;
	
}t_chr_log;

 
t_chr_log  *chr_log;

int Push_Chr_Log( t_chr_log *q )
{		
	t_chr_log  *temp;
		
	if( chr_log == NULL )
	{	
		chr_log = q;
		chr_log->next	= NULL;
		chr_log->prev	= NULL;
		return 1;
	}	
	else
	{	
		temp = chr_log;

		chr_log = q;
		chr_log->next = temp;
		chr_log->prev = NULL;
		temp->prev = chr_log;

		return 1;
	}
}

int Delete_Chr_Log( t_chr_log *q )
{
	t_chr_log *temp;


	if( chr_log == q )
	{	
		temp = chr_log;

		chr_log = temp;
		chr_log->prev = NULL;

		delete temp;
		return 1;
	}	
	else		
	{			
		temp = chr_log->next;
				
		while( temp )
		{		
			if( temp == q )
			{	
				if( temp->next )
				{
					temp->next->prev = temp->prev;
					temp->prev->next = temp->next;
				}
				else
				{
					temp->prev->next = NULL;
				}

				delete temp;
				return 1;
			}	
				
			temp = temp->next;
		}		
	}			
	return 0;
}				
				
t_chr_log *Find_Chr_Log( char *name )
{
	t_chr_log *t = chr_log;

	while( t )
	{
		if( strcmp( t->name, name ) == 0 ) return t;
		t = t->next;
	}
	return NULL;
}


int PushCharData2ChrLogDB_Basic( t_chr_log *t )
{
	char		szQuerry[1024];
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SQLINTEGER	cbskilllen, cbskillexplen,cbtacskillexplen, cbinvlen, cbquick, cbequip, cbbankitem;		
	SQLINTEGER	cbInt[33] = {0, };			// int 형은 0
	SQLINTEGER	cbName, cbId, cbMapName;	// 문자열은 SQL_NTS
	cbName = cbId = cbMapName = SQL_NTS;

	int			s_IntOuput[33];
	char		szName[20], szId[20], szMapName[20];

	SQLPOINTER	pParamData;

	int			server_set_num;
	SQLINTEGER	server_set_num_int = 0;


	struct tm *today;
	time_t lTime;
	time(&lTime);
	today = localtime(&lTime);
	
	g_year = today->tm_year + 1900;
	g_mon  = today->tm_mon;
	g_yday = today->tm_yday + 1;
	g_day  = today->tm_mday;
#ifdef BUFF_BUG_CHECKS // Finito 26/08/07 buff bug checks to take away 12 hours when time changes
	if (today->tm_hour - g_hour >= 12 && g_hour != -1)
	{
		g_hour = today->tm_hour - 12;
	}
	else
	{
		g_hour = today->tm_hour;
	}
#else
	g_hour = today->tm_hour;
#endif
	g_min  = today->tm_min;
	g_sec  = today->tm_sec;

	server_set_num = g_pServerTable->GetServerSetNum();


//	sprintf(szQuerry, "INSERT INTO ChrLog ( name, skill ) VALUES ( ? , ? ) " );
	sprintf(szQuerry, 
			"INSERT INTO ChrLog_%04d%02d%02d  "
			"( server_set_num, id,name,state, Lev,fame_pk,Str,Con,Dex,Wis,Int,"
			"  MoveP,Char,Endu,Moral,Luck,wsps,Tactics,nation,Money,HpMax, "
			"  ManaMax,MapName,HungryMax,Resis_Poison,Resis_Stone,Resis_Magic,Resis_Fire,Resis_Ice,Resis_Elect,X, "
			"  Y,reserved_point,BankMoney,Exp, "
			"  skill, skill_exp, tac_skillEXP, inventory, equip, quick, bankitem )"
			" VALUES "
			" (	?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
			"	?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
			"	?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
			"	?, ?, ?, ?, "
			"	?, ?, ?, ?, ?, ?, ? ) ", g_year, g_mon+1, g_day );

	SQLAllocStmt(hDBC_ChrLogDB, &hStmt);
	retCode= SQLPrepare(hStmt, (UCHAR *)szQuerry, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{	
		WORD ct = 1;

		SQLBindParameter(hStmt, ct, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &server_set_num, 0, &server_set_num_int);	ct++;
		SQLBindParameter(hStmt, ct, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 20, 0, &szId, 0, &cbId); ct++;
		SQLBindParameter(hStmt, ct, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 20, 0, &szName, 0, &cbName); ct++;
		for( int i=0; i<32; i++ )
		{
			if( i == 19 )		// because mapname field
			{
				SQLBindParameter(hStmt, ct, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 20, 0, &szMapName, 0, &cbMapName);
			}
			else 
			{
				SQLBindParameter(hStmt, ct, SQL_PARAM_INPUT, SQL_C_LONG,SQL_INTEGER, 0, 0, &s_IntOuput[i], 0, &cbInt[i]);				
			}			
			ct++;
		}
		SQLBindParameter(hStmt, ct, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_SKILL, 0, t->Skill, 0, &cbskilllen); ct++;
		SQLBindParameter(hStmt, ct, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_SKILL_EXP, 0, t->skillexp, 0, &cbskillexplen);  ct++;
		SQLBindParameter(hStmt, ct, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_TAC_SKILL_EXP, 0, t->tac_skillEXP, 0, &cbtacskillexplen); ct++;
		SQLBindParameter(hStmt, ct, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_INV, 0, t->inv, 0, &cbinvlen); ct++;
		SQLBindParameter(hStmt, ct, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_EQUIP, 0, t->equip, 0, &cbequip); ct++;
		SQLBindParameter(hStmt, ct, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_QUICK, 0, t->quick, 0, &cbquick); ct++;
		SQLBindParameter(hStmt, ct, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_BANKITEM, 0, t->bankitem, 0, &cbbankitem); ct++;



		strcpy( szId, t->id );
		strcpy(	szName, t->name );

		
		s_IntOuput[0] =t->state; 
		s_IntOuput[1] =t->Level; 
		//s_IntOuput[2] =t->fame_pk;	// 010915 LTS				//Fame_PK -> NWCharacter로 교체 DB에는 실제로 NWCharacter의 값이 들어갑니다.		
		memcpy(&s_IntOuput[2],&t->NWCharacter,sizeof(DWORD));		// 010915 LTS
		s_IntOuput[3] =t->Str; 
		s_IntOuput[4] =t->Con; 
		s_IntOuput[5] =t->Dex; 
		s_IntOuput[6] =t->Wis; 
		s_IntOuput[7] =t->Int;
		s_IntOuput[8] =t->MoveP; 
		s_IntOuput[9] =t->Char; 

		s_IntOuput[10] =t->Endu; 
		s_IntOuput[11] =t->Moral; 
		s_IntOuput[12] =t->Luck ; 
		s_IntOuput[13] =t->wsps ; 
		s_IntOuput[14] =t->Tactics ; 
		s_IntOuput[15] =t->nation ; 
		s_IntOuput[16] =t->Money ; 
		s_IntOuput[17] =t->HpMax  ;
		s_IntOuput[18] =t->ManaMax ;
		strcpy( szMapName, t->MapName );		// 19

		s_IntOuput[20] =t->HungryMax ;
		s_IntOuput[21] =t->Resis_Poison ; 
		s_IntOuput[22] =t->Resis_Stone	 ; 
		s_IntOuput[23] =t->Resis_Magic	 ; 
		s_IntOuput[24] =t->Resis_Fire	 ; 
		s_IntOuput[25] =t->Resis_Ice	 ; 
		s_IntOuput[26] =t->Resis_Elect; 
		s_IntOuput[27] =t->X / 32;
		s_IntOuput[28] =t->Y / 32;
		s_IntOuput[29] =t->reserved_point; 

		s_IntOuput[30] =t->BankMoney;
		s_IntOuput[31] =t->Exp;

		cbskilllen		= SQL_LEN_DATA_AT_EXEC(0);
		cbskillexplen	= SQL_LEN_DATA_AT_EXEC(0);
		cbtacskillexplen= SQL_LEN_DATA_AT_EXEC(0);
		cbinvlen		= SQL_LEN_DATA_AT_EXEC(0);
		cbequip			= SQL_LEN_DATA_AT_EXEC(0);
		cbquick			= SQL_LEN_DATA_AT_EXEC(0);
		cbbankitem		= SQL_LEN_DATA_AT_EXEC(0);
				
		retCode = SQLExecute(hStmt) ;

		while(retCode == SQL_NEED_DATA) 
		{		
			retCode = SQLParamData(hStmt, &pParamData) ;
			if(retCode == SQL_NEED_DATA) 
			{	
					 if(pParamData == t->Skill) 		SQLPutData(hStmt, t->Skill,		SIZE_OF_SKILL);      
				else if(pParamData == t->skillexp) 		SQLPutData(hStmt, t->skillexp,	SIZE_OF_SKILL_EXP );      
				else if(pParamData == t->tac_skillEXP)	SQLPutData(hStmt, t->tac_skillEXP, SIZE_OF_TAC_SKILL_EXP );      
				else if(pParamData == t->inv) 			SQLPutData(hStmt, t->inv,		SIZE_OF_INV);
				else if(pParamData == t->equip) 		SQLPutData(hStmt, t->equip,	SIZE_OF_EQUIP);
				else if(pParamData == t->quick) 		SQLPutData(hStmt, t->quick,	SIZE_OF_QUICK );
				else if(pParamData == t->bankitem ) 	SQLPutData(hStmt, t->bankitem,	SIZE_OF_BANKITEM );
			}	
			else break ;
		}
		retCode = SQLExecute(hStmt) ;
		
		if(retCode == SQL_NEED_DATA)
		{
			SQLCancel(hStmt) ;
//			SQLTransact(SQL_NULL_HENV, hDBC_ChrLogDB, SQL_COMMIT);
			SQLFreeStmt(hStmt, SQL_DROP);
			return 1;
		}
		else
		{
			SQLFreeStmt(hStmt, SQL_DROP);
			return 0;
		}
	}		
	else 
	{
		SQLFreeStmt(hStmt, SQL_DROP);
		return 0; // fail....
	}

}

int PushCharData2ChrLogDB_Binary( t_chr_log *t )
{	
	SQLINTEGER	cbskilllen, cbskillexplen,cbtacskillexplen, cbinvlen, cbquick, cbequip, cbbankitem;
	SQLRETURN	retcode;
	SQLHSTMT	hstmt;
	SQLPOINTER	pParamData;
	char		query[256];

	
//	sprintf(query, "Insert into ChrLog ( skill, skill_exp, tac_skillEXP, inventory, equip, quick, bankitem )"
//		"values ( ?, ?, ?, ?, ?, ?, ? ) ");

	sprintf(query, "Update ChrLog_%d%d%d SET skill=?, skill_exp=?, tac_skillEXP=?, inventory=?, equip=?, quick=?, bankitem=? WHERE index_ = %d", t->index );


	SQLAllocStmt(hDBC_ChrLogDB, &hstmt);
	retcode = SQLPrepare(hstmt, (UCHAR *)query, SQL_NTS);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
	{
		retcode= SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_SKILL,			0, t->Skill,			0, &cbskilllen); 
		retcode= SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_SKILL_EXP,		0, t->skillexp,		0, &cbskillexplen); 
		retcode= SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_TAC_SKILL_EXP,	0, t->tac_skillEXP,		0, &cbtacskillexplen); 
		retcode= SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_INV,			0, t->inv,				0, &cbinvlen); 
		retcode= SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_EQUIP,			0, t->equip,			0, &cbequip); 
		retcode= SQLBindParameter(hstmt, 6, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_QUICK,			0, t->quick,			0, &cbquick); 
		retcode= SQLBindParameter(hstmt, 7, SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY, SIZE_OF_BANKITEM,		0, t->bankitem,	0, &cbbankitem); 
		
		cbequip			= SQL_LEN_DATA_AT_EXEC(0);
		cbquick			= SQL_LEN_DATA_AT_EXEC(0);
		cbskilllen		= SQL_LEN_DATA_AT_EXEC(0);
		cbskillexplen	= SQL_LEN_DATA_AT_EXEC(0);
		cbtacskillexplen= SQL_LEN_DATA_AT_EXEC(0);
		cbinvlen		= SQL_LEN_DATA_AT_EXEC(0);
		cbbankitem		= SQL_LEN_DATA_AT_EXEC(0);
				
		retcode = SQLExecute(hstmt) ;
				
		while(retcode == SQL_NEED_DATA) 
		{		
			retcode = SQLParamData(hstmt, &pParamData) ;
			if(retcode == SQL_NEED_DATA) 
			{	
					 if(pParamData == t->Skill) 		SQLPutData(hstmt, t->Skill,		SIZE_OF_SKILL);      
				else if(pParamData == t->skillexp) 		SQLPutData(hstmt, t->skillexp,	SIZE_OF_SKILL_EXP );      
				else if(pParamData == t->tac_skillEXP)	SQLPutData(hstmt, t->tac_skillEXP, SIZE_OF_TAC_SKILL_EXP );      
				else if(pParamData == t->inv) 			SQLPutData(hstmt, t->inv,		SIZE_OF_INV);
				else if(pParamData == t->equip) 		SQLPutData(hstmt, t->equip,	SIZE_OF_EQUIP);
				else if(pParamData == t->quick) 		SQLPutData(hstmt, t->quick,	SIZE_OF_QUICK );
				else if(pParamData == t->bankitem ) 	SQLPutData(hstmt, t->bankitem,	SIZE_OF_BANKITEM );
			}	
			else break ;
		}		
		
		retcode = SQLExecute(hstmt);
		
		if(retcode == SQL_NEED_DATA)
		{
			retcode= SQLCancel(hstmt);
//			retcode= SQLTransact(SQL_NULL_HENV, hDBC_ChrLogDB, SQL_COMMIT);
					
			if(retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
			{		
				//printf("\n Transact commit Error");
			}		
					
			retcode= SQLFreeStmt(hstmt, SQL_DROP );
			return(1); // succeed
		}			
		else		
		{			
//			SQLTransact(SQL_NULL_HENV, hDBC_ChrLogDB, SQL_ROLLBACK);
			SQLFreeStmt(hstmt, SQL_DROP);
			return(-3); 
		}		
				
	}			
	else
	{
		SQLFreeStmt(hstmt, SQL_DROP);
	}
				
	return 1;	
				
}

int PushCharData2ChrLogDB( t_chr_log *t )
{
	int ret;
	ret = PushCharData2ChrLogDB_Basic( t );
	//if( ret ) ret = PushCharData2ChrLogDB_Binary( t );

	return ret;
}




// ret :	Write at ChrLogDB	: 1
//			Just Buffering		: 0
int  Recv_ChrLogDB( t_packet *p, int cn )
{		
	t_chr_log *t;
	t_server_chr_log_basic_data		*tp;
	t_server_chr_log_binary_data0	*tp0;
	t_server_chr_log_binary_data1	*tp1;
	t_server_chr_log_binary_data2	*tp2;
	t_server_chr_log_binary_data3	*tp3;


	switch( p->h.header.type )
	{	
		case CMD_CHR_LOG_CHAR_DB		:	t = new t_chr_log;	tp  = &p->u.server_chr_log_basic_data;	break;
		case CMD_CHR_LOG_BINARY_DATA0	:	tp0 = &p->u.server_chr_log_binary_data0; t = Find_Chr_Log( tp0->name ); break;
		case CMD_CHR_LOG_BINARY_DATA1	:	tp1 = &p->u.server_chr_log_binary_data1; t = Find_Chr_Log( tp1->name ); break;
		case CMD_CHR_LOG_BINARY_DATA2	:	tp2 = &p->u.server_chr_log_binary_data2; t = Find_Chr_Log( tp2->name ); break;
		case CMD_CHR_LOG_BINARY_DATA3	:	tp3 = &p->u.server_chr_log_binary_data3; t = Find_Chr_Log( tp3->name ); break;
	}	

	if( t == NULL ) return 0;
	
	switch( p->h.header.type )
	{	
		case CMD_CHR_LOG_CHAR_DB	:	
			{	
				strcpy( t->name,	tp->name );
				strcpy( t->id,		tp->id );
				t->state	= tp->state;
				t->Level = tp->btLevel; // CSD-030806
				t->fame_pk	= tp->fame_pk;	// 010915 LTS		//Fame_PK -> NWCharacter로 교체 DB에는 실제로 NWCharacter의 값이 들어갑니다.		
				t->NWCharacter = t->NWCharacter; // 010915 LTS
				t->Str		= tp->Str;
				t->Con		= tp->Con;
				t->Dex	= tp->Dex;
				t->Wis = tp->Wis;
				t->Int = tp->Int;
				t->MoveP = tp->MoveP;
				t->Char = tp->Char;
				t->Endu = tp->Endu;
				t->Moral = tp->Moral;
				t->Luck = tp->Luck;
				t->wsps = tp->wsps;

				t->Tactics = tp->Tactics;
				t->nation = tp->nation;	

				t->Money = tp->Money;
				t->HpMax  = tp->HpMax ;
				t->ManaMax = tp->ManaMax;

				strcpy( t->MapName, tp->MapName );
				t->HungryMax = tp->HungryMax;

				t->Resis_Poison = tp->Resis_Poison;
				t->Resis_Stone	 = tp->Resis_Stone	;
				t->Resis_Magic	 = tp->Resis_Magic	;
				t->Resis_Fire	 = tp->Resis_Fire	;
				t->Resis_Ice	 = tp->Resis_Ice	;
				t->Resis_Elect	 = tp->Resis_Elect	;

				t->X = tp->X;
				t->Y = tp->Y;

				t->reserved_point = tp->reserved_point;
				t->BankMoney = tp->BankMoney;
				t->Exp = tp->Exp;
				
				Push_Chr_Log( t );
			}	
			break;
				
		case CMD_CHR_LOG_BINARY_DATA0	:	
			{	
				memcpy( t->Skill, tp0->Skill, SIZE_OF_SKILL );
				memcpy( t->skillexp,tp0->skillexp, SIZE_OF_SKILL_EXP);
 				memcpy( t->tac_skillEXP,tp0->tac_skillEXP, SIZE_OF_TAC_SKILL_EXP);
			}	
			break;
				
		case CMD_CHR_LOG_BINARY_DATA1	:
			{	
				memcpy( t->equip, tp1->equip, SIZE_OF_EQUIP);
				memcpy( t->quick, tp1->quick, SIZE_OF_QUICK);
			}	
			break;
				
		case CMD_CHR_LOG_BINARY_DATA2	:
			{	
				memcpy( t->inv, tp2->inv, SIZE_OF_INV );
			}	
			break;
		case CMD_CHR_LOG_BINARY_DATA3	:	
			{	
				memcpy( t->bankitem, tp3->bankitem, SIZE_OF_BANKITEM );
				if( PushCharData2ChrLogDB( t ) )
				{
					MyLog( LOG_NORMAL, "SUCCESS : '%s' Character Logged ( %d )", t->name, t->state );
				}
				else 
				{
					MyLog( LOG_NORMAL, "'%s' Character Logged ****** FAIL !!!  ( %d )", t->name, t->state );
				}

				Delete_Chr_Log( t );

				
			}	
			break;
	}			

	return 1;
}				
				





bool IsDefTable(HDBC hDBC, char* pTblName)
{
  HSTMT hStmt = NULL;
  SQLAllocStmt(hDBC, &hStmt);
  // 테이블의 정보 가져오기
  RETCODE retCode = SQLTables(hStmt, NULL, SQL_NTS, NULL, SQL_NTS, 
                              (SQLCHAR*)(pTblName), SQL_NTS, (SQLCHAR*)("'TABLE'"), SQL_NTS);
  
  if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
  {
    char szBuffer[256];
    SDWORD cbValue;
    // 세번째 열의 값인 테이블명 자져오기
    SQLBindCol(hStmt, 3, SQL_C_CHAR, szBuffer, sizeof(szBuffer), &cbValue);
    
    if (SQLFetch(hStmt) == SQL_SUCCESS)
    { 
      SQLFreeStmt(hStmt, SQL_DROP);
      return true;
    }
  }

  SQLFreeStmt(hStmt, SQL_DROP);
  return false;
}




//010822 lsw 서버셋 넣음
void InitHackingLog( void )
{	
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	
	SQLAllocStmt(hDBC_ChrLogDB, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)
			"CREATE TABLE DoubtUser (						\
							[id] [char] (20) NULL ,			\
							[name] [char] (20) NULL ,		\
							[server_no] [int] NULL ,		\
							[date] [datetime] NOT NULL ,	\
							[type] [int] NULL ,				\
							[ip] [varchar] (50) NULL ,		\
							[cause] [varchar] (50) NULL		\
			) ON [PRIMARY]", SQL_NTS);
	SQLFreeStmt(hStmt, SQL_DROP);
	
	if(retCode != SQL_SUCCESS && retCode != SQL_SUCCESS_WITH_INFO) goto SUCCESS_;


	SQLAllocStmt(hDBC_ChrLogDB, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)
			"ALTER TABLE DoubtUser WITH NOCHECK ADD 								\
				CONSTRAINT [DF_DoubtUser_date] DEFAULT (getdate()) FOR [date],		\
				CONSTRAINT [PK_DoubtUser] PRIMARY KEY  NONCLUSTERED 				\
				(																	\
					[date]															\
				)  ON [PRIMARY]", SQL_NTS);
	SQLFreeStmt(hStmt, SQL_DROP);

	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO) 
	{
		MyLog( LOG_NORMAL, " 'DoubtUser' Table successfully Created !" );
		
	}
	else
	{
		MyLog( LOG_NORMAL, " 'DoubtUser' Table Checking : *** Error !!" );
		return;
	}

SUCCESS_:

	MyLog( LOG_NORMAL, " 'DoubtUser' Table Checking...OK !" );

}

//020330 lsw
void InitRareItemMakeResultLog( void )
{	
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	
	SQLAllocStmt(hDBC_ChrLogDB, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)
	"CREATE TABLE ItemLog (				\
		[date]				[datetime]	NOT NULL,\
		[ServerSetNo]		[int]	,\
		[map]				[int]	,\
		[maker]			[char](20)	,\
		[itemno]			[int]	,\
		[today_count]		[int]	,\
		[grade]				[int]	,\
		[mutanttype1]		[int]	,\
		[mutanttype2]		[int]	,\
		[mutanttype3]		[int]	,\
		[addeditem1]		[int]	,\
		[addeditem1limit]	[int]	,\
		[addeditem2]		[int]	,\
		[addeditem2limit]	[int]	,\
		[resultlimit]		[int]	,\
		[resultnowdur]		[int]	,\
		[resultmaxdur]		[int]	,\
		[why]				[int]	,\
		[why2]				[int]	,\
		[resource1limit]	[int]	,\
		[resource2limit]	[int]	,\
		[resource3limit]	[int]	,\
		[resource4limit]	[int]	,\
		[resource5limit]	[int]	,\
		[resource6limit]	[int]	\
	) ON [PRIMARY]", SQL_NTS);
	SQLFreeStmt(hStmt, SQL_DROP);
	
	if(retCode != SQL_SUCCESS && retCode != SQL_SUCCESS_WITH_INFO) goto SUCCESS_;

	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO) 
	{
		MyLog( LOG_NORMAL, " 'ItemLog' Table successfully Created !" );
	}
	else
	{
		MyLog( LOG_NORMAL, " 'ItemLog' Table Checking : *** Error !!" );
		return;
	}

SUCCESS_:

	MyLog( LOG_NORMAL, " 'RareLog' Table Checking...OK !" );
}
void InitBanlist(void)
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode;

	SQLAllocStmt(hDBC_TotalDB, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR*)
		"CREATE TABLE ban_table (				\
		[account]				[nchar](20)	NOT NULL,\
		[reason]		[nchar](255)	NOT NULL ,\
		[unBanDate]				[int]	NOT NULL ,\
		[bywho]			[nchar](20)	    NOT NULL \
	) ON[PRIMARY]", SQL_NTS);

	if (retCode != SQL_SUCCESS && retCode != SQL_SUCCESS_WITH_INFO) goto SUCCESS_;

	if (retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{
		MyLog(LOG_NORMAL, " 'ban_table' Table successfully Created !");
	}
	else
	{
		MyLog(LOG_NORMAL, " 'ban_table' Table Checking : *** Error !!");
		return;
	}

SUCCESS_:

	MyLog(LOG_NORMAL, " 'ban_table' Table Checking...OK !");
}
void InitAccountLock(void)
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode;

	SQLAllocStmt(hDBC_TotalDB, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR*)
		"CREATE TABLE AccountLock (				\
		[account]				[nchar](20)	NOT NULL,\
		[reason]		[nchar](255)	,\
		[bywho]			[nchar](20)	     \
	) ON[PRIMARY]", SQL_NTS);

	if (retCode != SQL_SUCCESS && retCode != SQL_SUCCESS_WITH_INFO) goto SUCCESS_;

	if (retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{
		MyLog(LOG_NORMAL, " 'AccountLock' Table successfully Created !");
	}
	else
	{
		MyLog(LOG_NORMAL, " 'AccountLock' Table Checking : *** Error !!");
		return;
	}

SUCCESS_:

	MyLog(LOG_NORMAL, " 'AccountLock' Table Checking...OK !");
}
//010822 lsw
bool RecvHackingUser( const char *id, const char *name, const int type, const char *ip, const char *cause )
{	
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	char		szQuerry[256];

	int		len;
	int server_no = g_pServerTable->GetServerSetNum();
	
	if( id == NULL )			goto FAIL_;
	if( ip == NULL )			goto FAIL_; 
	if( cause == NULL )			goto FAIL_;
	if( strlen(id) <= 0 )		goto FAIL_;
	if( strlen(ip) <= 0 )		goto FAIL_;
	len = strlen(cause);
	if( len <= 0 || len >= 50 )	goto FAIL_;

	char szID[ID_LENGTH];
	char szName[NM_LENGTH];
	char szIP[IP_LENGTH];
	char szCause[100];
	ConvertQueryString(id, szID, ID_LENGTH); // Finito prevents sql injection
	ConvertQueryString(name, szName, NM_LENGTH); // Finito prevents sql injection
	ConvertQueryString(ip, szIP, IP_LENGTH); // Finito prevents sql injection
	ConvertQueryString(cause, szCause, 100); // Finito prevents sql injection
	
	sprintf(szQuerry,"DELETE DoubtUser where date < ( getdate()-%d )",LocalMgr.GetDoubtUserTableLimitDay());//030102 lsw
	Querry_SQL(szQuerry , hDBC_ChrLogDB );		// 021128 YGI

	sprintf( szQuerry, "INSERT INTO DoubtUser (id, name, server_no ,type, ip, cause )" 
		" VALUES ('%s', '%s', '%d','%d', '%s', '%s' )",szID, szName, server_no,type, szIP, szCause );
	
	SQLAllocStmt(hDBC_ChrLogDB, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
	SQLFreeStmt(hStmt, SQL_DROP);
	
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO) return true;
	
	MyLog( LOG_NORMAL, " *** Error : 'DoubtUser' Insert FAIL !!\n( Name: %s, Type: %d, Server_no: %d, ip: %s, cause: %s )", szID, type, server_no , szIP, szCause );

FAIL_:
	return false;
}



//011030 lsw >
bool RecvRareItemMakeLog( t_rare_item_make_log *tp )
{	
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	char		szQuerry[2048];
	const int server_no = g_pServerTable->GetServerSetNum();
	
	if( tp->maker == NULL )
	{
		MyLog( LOG_NORMAL, "Warning!!  *** Error:'ItemLog' Charcter Data NULL!!!!! *** " );
		goto FAIL_;
	}
	sprintf( szQuerry, "INSERT INTO ItemLog										\
		(																		\
		date,ServerSetNo,map,maker,itemno,today_count,grade,mutanttype1,mutanttype2,mutanttype3,\
		addeditem1,addeditem1limit,addeditem2,addeditem2limit,resultlimit,		\
		resultnowdur,resultmaxdur,why,why2,resource1limit,resource2limit,		\
		resource3limit,resource4limit,resource5limit,resource6limit				\
		)																		\
		VALUES 																	\
		(																		\
		getdate(),  '%d', '%d','%s',											\
		'%d', '%d', '%d', '%d','%d', '%d',										\
		'%d', '%d', '%d', '%d','%d',											\
		'%d', '%d', '%d', '%d','%d',											\
		'%d', '%d', '%d', '%d','%d'												\
		)"

	,
	server_no,
	tp->map,
	tp->maker,
	tp->itemno,
	tp->today_count,
	tp->grade,
	tp->mutanttype1,
	tp->mutanttype2,
	tp->mutanttype3,
	tp->addeditem1,
	tp->addeditem1limit,
	tp->addeditem2,
	tp->addeditem2limit,
	tp->resultlimit,
	tp->resultnowdur,
	tp->resultmaxdur,
	tp->why,
	tp->why2,
	tp->resource1limit,
	tp->resource2limit,
	tp->resource3limit,
	tp->resource4limit,
	tp->resource5limit,
	tp->resource6limit
	);

	SQLAllocStmt(hDBC_ChrLogDB, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
	SQLFreeStmt(hStmt, SQL_DROP);
	
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO) return true;
	
	MyLog( LOG_NORMAL, "Warning!!  *** Error:'ItemLog' Data Insert Failed *** " );
	

FAIL_:
	
	return false;
	
}
//011030 lsw <








