#include "StdAfx.h"
#include "main.h"



NPCName_by_Gender	NPC_Name_Ref[Num_Of_NPC_Name] ;
NPC_Info			NPC_Info_Ref[Num_Of_NPC_Type] ;
NPC_Generation		NPC_Gen_Ref[Num_Of_NPC_Generation] ;

int NPC_First_Ref[2][10]= {
	10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
	1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003, 1003
} ;

int NPC_Class_Ref[6][10]= {
1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002,
1010, 1008, 0, 0, 0, 1005, 1006, 1004, 0, 0,
0, 1005, 1008, 0, 1004, 1010, 0, 0, 0, 1006,
1006, 1005, 1010, 0, 1004, 1008, 0, 0, 0, 0,
0, 0, 0, 1008, 1010, 1005, 0, 1006, 0, 1004,
0, 1005, 0, 1010, 1008, 0, 1004, 1006, 0, 0
} ;


short int nNPC_Type, nNPC_Name, nNPC_Lev ;

int initNPCInfoTable(void) ;
int initNPCNameTable(void) ;
int initNPCGenerationTable(void) ;

extern HDBC hDBC ;

// DB에 있는 3개의 NPC 테이블을 메모리로 읽어온다.
int initNPCTable(void)
{
	if(initNPCInfoTable() < 0) return -1 ;
	if(initNPCNameTable() < 0) return -1 ;
	if(initNPCGenerationTable() < 0) return -1 ;
	return 1 ;
}

// NPC이름 생성을 위한 테이블을 DB에서 읽어오는 함수
int initNPCNameTable(void)
{
	if(Num_Of_NPC_Name <= 0) {
		//fprintf(stdout, "\n	No item's available ") ;
		return -4 ; // No item's available
	}

	HSTMT hStmt= NULL ;
	RETCODE ret ;
	char query_stmt[80]= {0, } ;
	SDWORD cbValue ;
	int c= 0 ;
	SQLAllocStmt(hDBC, &hStmt);
  /////////////////////////////////////////////////////////////////////////////
  //strcpy(query_stmt, "select * from NPC_NamebyGender") ;
  sprintf(query_stmt, "EXEC up_get_npc_namebygender");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;

	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nNPC init: ExecDirect Error ") ;
		return -1 ;
	}

	//SQLNumResultCols(hStmt, &nCols) ;
	
	ret= SQLFetch(hStmt) ;
	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,    NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,    0,    NULL );// Process any inserts in lpMsgBuf.
		// ...// Display the string.
		printf("\nLast Error: %s", (LPCTSTR)lpMsgBuf) ;
		// Free the buffer.
		LocalFree( lpMsgBuf );
		printf("\nNPC init: Fetch Error ") ;
		return -1 ;
	}
		
	while(c < Num_Of_NPC_Name && ret == SQL_SUCCESS)
	{
		ret= SQLGetData(hStmt, 2, SQL_C_CHAR, (UCHAR *)NPC_Name_Ref[c].Female, 17, &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}
		
		ret= SQLGetData(hStmt, 3, SQL_C_CHAR, (UCHAR *)NPC_Name_Ref[c].Male, 17, &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}

		ret= SQLGetData(hStmt, 4, SQL_C_CHAR, (UCHAR *)NPC_Name_Ref[c].Last, 17, &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}
						
		c++ ;
		ret= SQLFetch(hStmt) ;
	}
	
	nNPC_Name= c ;
	SQLFreeStmt(hStmt, SQL_DROP) ;
	printf("	  .NPC Name   %3d data Loaded !\n", c) ;
	return c ;
}

// NPC정보(상태정보, 힘/지능 등의 각종 수치)를 담고 있는 테이블을 
// DB에서 읽어오는 함수
int initNPCInfoTable(void)
{
	if(Num_Of_NPC_Type <= 0) {
		//fprintf(stdout, "\n	No item's available ") ;
		return -4 ; // No item's available
	}

	HSTMT hStmt= NULL ;
	RETCODE ret ;
	char query_stmt[80]= {0, } ;
	SDWORD cbValue ;
	int c= 0 ;
	SQLAllocStmt(hDBC, &hStmt);
  /////////////////////////////////////////////////////////////////////////////
  //strcpy(query_stmt, "select * from NPC_Info") ;
  strcpy(query_stmt, "EXEC up_get_npc_info");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;

	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nNPC init: ExecDirect Error ") ;
		return -1 ;
	}

	//SQLNumResultCols(hStmt, &nCols) ;
	
	ret= SQLFetch(hStmt) ;
	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,    NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,    0,    NULL );// Process any inserts in lpMsgBuf.
		// ...// Display the string.
		printf("\nLast Error: %s", (LPCTSTR)lpMsgBuf) ;
		// Free the buffer.
		LocalFree( lpMsgBuf );
		printf("\nNPC init: Fetch Error ") ;
		return -1 ;
	}
		
	while(c < Num_Of_NPC_Type && ret == SQL_SUCCESS)
	{
		// Accquire the DATA
		/*
		ret= SQLGetData(hStmt, 1, SQL_C_CHAR, (UCHAR *)NPC_Ref[c].Name, 20, &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}
				
		ret= SQLGetData(hStmt, 2, SQL_C_SLONG, &NPC_Ref[c].SprNo, sizeof(NPC_Ref[c].SprNo), &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nError!!! (%d)", ret) ;
			return -1 ;
		}
		*/
		//printf("\n %s %d", NPC_Ref[c].Name, NPC_Ref[c].SprNo) ;
		ret = SQLGetData(hStmt,  3, SQL_C_ULONG,		&NPC_Info_Ref[c].sprno,				0, &cbValue);
		ret = SQLGetData(hStmt,  4, SQL_C_ULONG,		&NPC_Info_Ref[c].face,				0, &cbValue);
		ret = SQLGetData(hStmt,  5, SQL_C_ULONG,		&NPC_Info_Ref[c].race,				0, &cbValue);
		ret = SQLGetData(hStmt,  6, SQL_C_ULONG,		&NPC_Info_Ref[c].spritvalue,		0, &cbValue);
		ret = SQLGetData(hStmt,  7, SQL_C_ULONG,		&NPC_Info_Ref[c].Class,				0, &cbValue);
		ret = SQLGetData(hStmt,  8, SQL_C_ULONG,		&NPC_Info_Ref[c].class_sprituality, 0, &cbValue);
		ret = SQLGetData(hStmt,  9, SQL_C_ULONG,		&NPC_Info_Ref[c].class_poisoning,	0, &cbValue);
		ret = SQLGetData(hStmt,  10, SQL_C_ULONG,		&NPC_Info_Ref[c].class_bombplay,	0, &cbValue);
		ret = SQLGetData(hStmt,  11, SQL_C_ULONG,		&NPC_Info_Ref[c].class_entrapment,	0, &cbValue);
		ret = SQLGetData(hStmt,  12, SQL_C_ULONG,		&NPC_Info_Ref[c].class_scrolling,	0, &cbValue);
		ret = SQLGetData(hStmt,  13, SQL_C_ULONG,		&NPC_Info_Ref[c].class_cunning1,	0, &cbValue);
		ret = SQLGetData(hStmt,  14, SQL_C_ULONG,		&NPC_Info_Ref[c].class_cunning2,	0, &cbValue);
		ret = SQLGetData(hStmt,  15, SQL_C_ULONG,		&NPC_Info_Ref[c].class_cunning3,	0, &cbValue);
		ret = SQLGetData(hStmt,  16, SQL_C_ULONG,		&NPC_Info_Ref[c].class_stealing,	0, &cbValue);
		ret = SQLGetData(hStmt,  17, SQL_C_ULONG,		&NPC_Info_Ref[c].job,				0, &cbValue);
		ret = SQLGetData(hStmt,  18, SQL_C_ULONG,		&NPC_Info_Ref[c].age,				0, &cbValue);
		ret = SQLGetData(hStmt,  19, SQL_C_ULONG,		&NPC_Info_Ref[c].lev,				0, &cbValue);
		ret = SQLGetData(hStmt,  20, SQL_C_ULONG,		&NPC_Info_Ref[c].hd,				0, &cbValue);
		ret = SQLGetData(hStmt,  21, SQL_C_ULONG,		&NPC_Info_Ref[c].exp,				0, &cbValue);
		ret = SQLGetData(hStmt,  22, SQL_C_ULONG,		&NPC_Info_Ref[c].pspow,				0, &cbValue);
		ret = SQLGetData(hStmt,  23, SQL_C_ULONG,		&NPC_Info_Ref[c].wspow,				0, &cbValue);
		ret = SQLGetData(hStmt,  24, SQL_C_ULONG,		&NPC_Info_Ref[c].divpow,			0, &cbValue);
		ret = SQLGetData(hStmt,  25, SQL_C_ULONG,		&NPC_Info_Ref[c].manapow,			0, &cbValue);
		ret = SQLGetData(hStmt,  26, SQL_C_ULONG,		&NPC_Info_Ref[c].orsnpow,			0, &cbValue);
		ret = SQLGetData(hStmt,  27, SQL_C_ULONG,		&NPC_Info_Ref[c].mjypow,			0, &cbValue);
		ret = SQLGetData(hStmt,  28, SQL_C_ULONG,		&NPC_Info_Ref[c].attackpow,			0, &cbValue);
		ret = SQLGetData(hStmt,  29, SQL_C_ULONG,		&NPC_Info_Ref[c].vitalpow,			0, &cbValue);
		ret = SQLGetData(hStmt,  30, SQL_C_ULONG,		&NPC_Info_Ref[c].hungrymax,			0, &cbValue);
		ret = SQLGetData(hStmt,  31, SQL_C_ULONG,		&NPC_Info_Ref[c].money,				0, &cbValue);
		ret = SQLGetData(hStmt,  32, SQL_C_ULONG,		&NPC_Info_Ref[c].strold,			0, &cbValue);
		ret = SQLGetData(hStmt,  33, SQL_C_ULONG,		&NPC_Info_Ref[c].conold,			0, &cbValue);
		ret = SQLGetData(hStmt,  34, SQL_C_ULONG,		&NPC_Info_Ref[c].dexold,			0, &cbValue);
		ret = SQLGetData(hStmt,  35, SQL_C_ULONG,		&NPC_Info_Ref[c].wisold,			0, &cbValue);
		ret = SQLGetData(hStmt,  36, SQL_C_ULONG,		&NPC_Info_Ref[c].intold,			0, &cbValue);
		ret = SQLGetData(hStmt,  37, SQL_C_ULONG,		&NPC_Info_Ref[c].movepold,			0, &cbValue);
		ret = SQLGetData(hStmt,  38, SQL_C_ULONG,		&NPC_Info_Ref[c].charold,			0, &cbValue);
		ret = SQLGetData(hStmt,  39, SQL_C_ULONG,		&NPC_Info_Ref[c].enduold,			0, &cbValue);
		ret = SQLGetData(hStmt,  40, SQL_C_ULONG,		&NPC_Info_Ref[c].healthold,			0, &cbValue);
		ret = SQLGetData(hStmt,  41, SQL_C_ULONG,		&NPC_Info_Ref[c].moralold,			0, &cbValue);
		ret = SQLGetData(hStmt,  42, SQL_C_ULONG,		&NPC_Info_Ref[c].luckold,			0, &cbValue);
		ret = SQLGetData(hStmt,  43, SQL_C_ULONG,		&NPC_Info_Ref[c].condition,			0, &cbValue);
    //< CSD-010907
    /*
		ret = SQLGetData(hStmt,  44, SQL_C_ULONG,		&NPC_Info_Ref[c].resist_poison,		0, &cbValue);
		ret = SQLGetData(hStmt,  45, SQL_C_ULONG,		&NPC_Info_Ref[c].resist_stone,		0, &cbValue);
		ret = SQLGetData(hStmt,  46, SQL_C_ULONG,		&NPC_Info_Ref[c].resist_magic,		0, &cbValue);
		ret = SQLGetData(hStmt,  47, SQL_C_ULONG,		&NPC_Info_Ref[c].resist_fire,		0, &cbValue);
		ret = SQLGetData(hStmt,  48, SQL_C_ULONG,		&NPC_Info_Ref[c].resist_ice,		0, &cbValue);
		ret = SQLGetData(hStmt,  49, SQL_C_ULONG,		&NPC_Info_Ref[c].resist_elect,		0, &cbValue);
    */
    ret = SQLGetData(hStmt,  44, SQL_C_ULONG,		&NPC_Info_Ref[c].nPoison,	0, &cbValue);
		ret = SQLGetData(hStmt,  45, SQL_C_ULONG,		&NPC_Info_Ref[c].nCurse,	0, &cbValue);
		ret = SQLGetData(hStmt,  46, SQL_C_ULONG,		&NPC_Info_Ref[c].nHoly,		0, &cbValue);
		ret = SQLGetData(hStmt,  47, SQL_C_ULONG,		&NPC_Info_Ref[c].nFire,		0, &cbValue);
		ret = SQLGetData(hStmt,  48, SQL_C_ULONG,		&NPC_Info_Ref[c].nIce,		0, &cbValue);
		ret = SQLGetData(hStmt,  49, SQL_C_ULONG,		&NPC_Info_Ref[c].nElect,	0, &cbValue);
    //> CSD-010907
		ret = SQLGetData(hStmt,  50, SQL_C_ULONG,		&NPC_Info_Ref[c].ws[0],				0, &cbValue);
		ret = SQLGetData(hStmt,  51, SQL_C_ULONG,		&NPC_Info_Ref[c].ws[1],				0, &cbValue);
		ret = SQLGetData(hStmt,  52, SQL_C_ULONG,		&NPC_Info_Ref[c].ws[2],				0, &cbValue);
		ret = SQLGetData(hStmt,  53, SQL_C_ULONG,		&NPC_Info_Ref[c].ws[3],				0, &cbValue);
		ret = SQLGetData(hStmt,  54, SQL_C_ULONG,		&NPC_Info_Ref[c].ws[4],				0, &cbValue);
		ret = SQLGetData(hStmt,  55, SQL_C_ULONG,		&NPC_Info_Ref[c].ws[5],				0, &cbValue);
		ret = SQLGetData(hStmt,  56, SQL_C_ULONG,		&NPC_Info_Ref[c].ws[6],				0, &cbValue);
		ret = SQLGetData(hStmt,  57, SQL_C_ULONG,		&NPC_Info_Ref[c].ws[7],				0, &cbValue);
		ret = SQLGetData(hStmt,  58, SQL_C_ULONG,		&NPC_Info_Ref[c].ws[8],				0, &cbValue);
		ret = SQLGetData(hStmt,  59, SQL_C_ULONG,		&NPC_Info_Ref[c].ws[9],				0, &cbValue);
		ret = SQLGetData(hStmt,  60, SQL_C_ULONG,		&NPC_Info_Ref[c].ps[0],				0, &cbValue);
		ret = SQLGetData(hStmt,  61, SQL_C_ULONG,		&NPC_Info_Ref[c].ps[1],				0, &cbValue);
		ret = SQLGetData(hStmt,  62, SQL_C_ULONG,		&NPC_Info_Ref[c].ps[2],				0, &cbValue);
		ret = SQLGetData(hStmt,  63, SQL_C_ULONG,		&NPC_Info_Ref[c].ps[3],				0, &cbValue);
		ret = SQLGetData(hStmt,  64, SQL_C_ULONG,		&NPC_Info_Ref[c].ps[4],				0, &cbValue);
		ret = SQLGetData(hStmt,  65, SQL_C_ULONG,		&NPC_Info_Ref[c].ps[5],				0, &cbValue);
		ret = SQLGetData(hStmt,  66, SQL_C_ULONG,		&NPC_Info_Ref[c].ps[6],				0, &cbValue);
		ret = SQLGetData(hStmt,  67, SQL_C_ULONG,		&NPC_Info_Ref[c].ps[7],				0, &cbValue);
		ret = SQLGetData(hStmt,  68, SQL_C_ULONG,		&NPC_Info_Ref[c].ps[8],				0, &cbValue);
		ret = SQLGetData(hStmt,  69, SQL_C_ULONG,		&NPC_Info_Ref[c].ps[9],				0, &cbValue);
		ret = SQLGetData(hStmt,  70, SQL_C_ULONG,		&NPC_Info_Ref[c].acc_equip[0],		0, &cbValue);
		ret = SQLGetData(hStmt,  71, SQL_C_ULONG,		&NPC_Info_Ref[c].acc_equip[1],		0, &cbValue);
		ret = SQLGetData(hStmt,  72, SQL_C_ULONG,		&NPC_Info_Ref[c].acc_equip[2],		0, &cbValue);
		ret = SQLGetData(hStmt,  73, SQL_C_ULONG,		&NPC_Info_Ref[c].acc_equip[3],		0, &cbValue);
		ret = SQLGetData(hStmt,  74, SQL_C_ULONG,		&NPC_Info_Ref[c].acc_equip[4],		0, &cbValue);
		ret = SQLGetData(hStmt,  75, SQL_C_ULONG,		&NPC_Info_Ref[c].acc_equip[5],		0, &cbValue);
		ret = SQLGetData(hStmt,  76, SQL_C_ULONG,		&NPC_Info_Ref[c].normal_sight,		0, &cbValue);
		ret = SQLGetData(hStmt,  77, SQL_C_ULONG,		&NPC_Info_Ref[c].battle_sight,		0, &cbValue);
		ret = SQLGetData(hStmt,  78, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[0],			0, &cbValue);
		ret = SQLGetData(hStmt,  79, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[1],			0, &cbValue);
		ret = SQLGetData(hStmt,  80, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[2],			0, &cbValue);
		ret = SQLGetData(hStmt,  81, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[3],			0, &cbValue);
		ret = SQLGetData(hStmt,  82, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[4],			0, &cbValue);
		ret = SQLGetData(hStmt,  83, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[5],			0, &cbValue);
		ret = SQLGetData(hStmt,  84, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[6],			0, &cbValue);
		ret = SQLGetData(hStmt,  85, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[7],			0, &cbValue);
		ret = SQLGetData(hStmt,  86, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[8],			0, &cbValue);
		ret = SQLGetData(hStmt,  87, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[9],			0, &cbValue);
		ret = SQLGetData(hStmt,  88, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[10],		0, &cbValue);
		ret = SQLGetData(hStmt,  89, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[11],		0, &cbValue);
		ret = SQLGetData(hStmt,  90, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[12],		0, &cbValue);
		ret = SQLGetData(hStmt,  91, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[13],		0, &cbValue);
		ret = SQLGetData(hStmt,  92, SQL_C_ULONG,		&NPC_Info_Ref[c].invtry[14],		0, &cbValue);
		ret = SQLGetData(hStmt,  93, SQL_C_ULONG,		&NPC_Info_Ref[c].tactics,			0, &cbValue);
		ret = SQLGetData(hStmt,  94, SQL_C_ULONG,		&NPC_Info_Ref[c].CRAPPLE,			0, &cbValue);
		ret = SQLGetData(hStmt,  95, SQL_C_ULONG,		&NPC_Info_Ref[c].SWORDMANSHIP,		0, &cbValue);
		ret = SQLGetData(hStmt,  96, SQL_C_ULONG,		&NPC_Info_Ref[c].ARCHERY,			0, &cbValue);
		ret = SQLGetData(hStmt,  97, SQL_C_ULONG,		&NPC_Info_Ref[c].FENCING,			0, &cbValue);
		ret = SQLGetData(hStmt,  98, SQL_C_ULONG,		&NPC_Info_Ref[c].MACEFIGHTING,		0, &cbValue);
		ret = SQLGetData(hStmt,  99, SQL_C_ULONG,		&NPC_Info_Ref[c].PIERCE,			0, &cbValue);
		ret = SQLGetData(hStmt,  100, SQL_C_ULONG,		&NPC_Info_Ref[c].WHIRL,				0, &cbValue);
		ret = SQLGetData(hStmt,  101, SQL_C_ULONG,		&NPC_Info_Ref[c].HURL,				0, &cbValue);
		ret = SQLGetData(hStmt,  102, SQL_C_ULONG,		&NPC_Info_Ref[c].PARRING,			0, &cbValue);
		ret = SQLGetData(hStmt,  103, SQL_C_ULONG,		&NPC_Info_Ref[c].DOUBL_SWORDMANSHIP, 0, &cbValue);
		ret = SQLGetData(hStmt,  104, SQL_C_ULONG,		&NPC_Info_Ref[c].DOUBL_MACEFIGHTING, 0, &cbValue);
		ret = SQLGetData(hStmt,  105, SQL_C_ULONG,		&NPC_Info_Ref[c].cooper,			0, &cbValue);
		ret = SQLGetData(hStmt,  106, SQL_C_ULONG,		&NPC_Info_Ref[c].MORDERATION,		0, &cbValue);
		ret = SQLGetData(hStmt,  107, SQL_C_ULONG,		&NPC_Info_Ref[c].royal,				0, &cbValue);
		ret = SQLGetData(hStmt,  108, SQL_C_ULONG,		&NPC_Info_Ref[c].courage,			0, &cbValue);
		ret = SQLGetData(hStmt,  109, SQL_C_ULONG,		&NPC_Info_Ref[c].faith,				0, &cbValue);
		ret = SQLGetData(hStmt,  110, SQL_C_ULONG,		&NPC_Info_Ref[c].truth,				0, &cbValue);
		ret = SQLGetData(hStmt,  111, SQL_C_ULONG,		&NPC_Info_Ref[c].justice,			0, &cbValue);
		ret = SQLGetData(hStmt,  112, SQL_C_ULONG,		&NPC_Info_Ref[c].mercy,				0, &cbValue);
		ret = SQLGetData(hStmt,  113, SQL_C_ULONG,		&NPC_Info_Ref[c].murder,			0, &cbValue);
		ret = SQLGetData(hStmt,  114, SQL_C_ULONG,		&NPC_Info_Ref[c].robery,			0, &cbValue);
		ret = SQLGetData(hStmt,  115, SQL_C_ULONG,		&NPC_Info_Ref[c].betrayal,			0, &cbValue);
		ret = SQLGetData(hStmt,  116, SQL_C_ULONG,		&NPC_Info_Ref[c].disroyal,			0, &cbValue);
		ret = SQLGetData(hStmt,  117, SQL_C_ULONG,		&NPC_Info_Ref[c].greed,				0, &cbValue);
		ret = SQLGetData(hStmt,  118, SQL_C_ULONG,		&NPC_Info_Ref[c].idol,				0, &cbValue);
		ret = SQLGetData(hStmt,  119, SQL_C_ULONG,		&NPC_Info_Ref[c].r_fame,			0, &cbValue);
		ret = SQLGetData(hStmt,  120, SQL_C_ULONG,		&NPC_Info_Ref[c].r_truth,			0, &cbValue);
		ret = SQLGetData(hStmt,  121, SQL_C_ULONG,		&NPC_Info_Ref[c].r_bow,				0, &cbValue);
		ret = SQLGetData(hStmt,  122, SQL_C_ULONG,		&NPC_Info_Ref[c].r_propagation,		0, &cbValue);
		ret = SQLGetData(hStmt,  123, SQL_C_ULONG,		&NPC_Info_Ref[c].r_service,			0, &cbValue);
		ret = SQLGetData(hStmt,  124, SQL_C_ULONG,		&NPC_Info_Ref[c].nor_range,			0, &cbValue);
		ret = SQLGetData(hStmt,  125, SQL_C_ULONG,		&NPC_Info_Ref[c].att_range,			0, &cbValue);
		ret = SQLGetData(hStmt,  126, SQL_C_ULONG,		&NPC_Info_Ref[c].enemy_no,			0, &cbValue);
		ret = SQLGetData(hStmt,  127, SQL_C_ULONG,		&NPC_Info_Ref[c].party,				0, &cbValue);
		ret = SQLGetData(hStmt,  128, SQL_C_ULONG,		&NPC_Info_Ref[c].levelgap,			0, &cbValue);
		ret = SQLGetData(hStmt,  129, SQL_C_ULONG,		&NPC_Info_Ref[c].offset,			0, &cbValue);
		ret = SQLGetData(hStmt,  130, SQL_C_ULONG,		&NPC_Info_Ref[c].apgap,				0, &cbValue);
		ret = SQLGetData(hStmt,  131, SQL_C_ULONG,		&NPC_Info_Ref[c].vpgap,				0, &cbValue);
		ret = SQLGetData(hStmt,  132, SQL_C_ULONG,		&NPC_Info_Ref[c].attackpattern,		0, &cbValue);
		ret = SQLGetData(hStmt,  133, SQL_C_ULONG,		&NPC_Info_Ref[c].partyattack,		0, &cbValue);
		ret = SQLGetData(hStmt,  134, SQL_C_ULONG,		&NPC_Info_Ref[c].afterattack,		0, &cbValue);
		ret = SQLGetData(hStmt,  135, SQL_C_ULONG,		&NPC_Info_Ref[c].attackend,			0, &cbValue);
		ret = SQLGetData(hStmt,  136, SQL_C_ULONG,		&NPC_Info_Ref[c].opendoor,			0, &cbValue);
		ret = SQLGetData(hStmt,  137, SQL_C_ULONG,		&NPC_Info_Ref[c].lockdoor,			0, &cbValue);
		ret = SQLGetData(hStmt,  138, SQL_C_ULONG,		&NPC_Info_Ref[c].closedoor,			0, &cbValue);
		ret = SQLGetData(hStmt,  139, SQL_C_ULONG,		&NPC_Info_Ref[c].breakobj,			0, &cbValue);
		ret = SQLGetData(hStmt,  140, SQL_C_ULONG,		&NPC_Info_Ref[c].pickobj,			0, &cbValue);
		ret = SQLGetData(hStmt,  141, SQL_C_ULONG,		&NPC_Info_Ref[c].openbox,			0, &cbValue);
		ret = SQLGetData(hStmt,  142, SQL_C_ULONG,		&NPC_Info_Ref[c].lockbox,			0, &cbValue);
		ret = SQLGetData(hStmt,  143, SQL_C_ULONG,		&NPC_Info_Ref[c].closebox,			0, &cbValue);
		ret = SQLGetData(hStmt,  144, SQL_C_ULONG,		&NPC_Info_Ref[c].pathrange,			0, &cbValue);
		ret = SQLGetData(hStmt,  145, SQL_C_ULONG,		&NPC_Info_Ref[c].neglect,			0, &cbValue);
		ret = SQLGetData(hStmt,  146, SQL_C_ULONG,		&NPC_Info_Ref[c].checklevel,		0, &cbValue);
		ret = SQLGetData(hStmt,  147, SQL_C_ULONG,		&NPC_Info_Ref[c].absolattack,		0, &cbValue);
		ret = SQLGetData(hStmt,  148, SQL_C_ULONG,		&NPC_Info_Ref[c].stop,				0, &cbValue);
		ret = SQLGetData(hStmt,  149, SQL_C_ULONG,		&NPC_Info_Ref[c].backdown,			0, &cbValue);
		ret = SQLGetData(hStmt,  150, SQL_C_ULONG,		&NPC_Info_Ref[c].act_month,			0, &cbValue);
		ret = SQLGetData(hStmt,  151, SQL_C_ULONG,		&NPC_Info_Ref[c].act_space,			0, &cbValue);
		ret = SQLGetData(hStmt,  152, SQL_C_ULONG,		&NPC_Info_Ref[c].act_time,			0, &cbValue);
		ret = SQLGetData(hStmt,  153, SQL_C_ULONG,		&NPC_Info_Ref[c].act_weather,		0, &cbValue);
		
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nError!!! (%d)", ret) ;
			return -1 ;
		}
		c++ ;
		ret= SQLFetch(hStmt) ;
	}
	
//	printf("\n<<<<<< %d Rows.>>>>>>>>", c) ;
	nNPC_Type= c ;
	SQLFreeStmt(hStmt, SQL_DROP) ;
	printf("	  .NPC Info   %3d data Loaded !\n", c) ;

//	for(i=0 ; i<nNPC_Type; i++) {
//		printf("\n %s %d", NPC_Ref[i].Name, NPC_Ref[i].SprNo) ;
//	}

	return c ;
}

// NPC정보(상태정보, 힘/지능 등의 각종 수치)를 담고 있는 테이블을 

// DB에서 읽어오는 함수
int initNPCGenerationTable(void)
{
	if(Num_Of_NPC_Generation <= 0) {
		//fprintf(stdout, "\n	No item's available ") ;
		return -4 ; // No item's available
	}

	HSTMT hStmt= NULL ;
	RETCODE ret ;
	char query_stmt[80]= {0, } ;
	SDWORD cbValue ;
	int c= 0 ;
	SQLAllocStmt(hDBC, &hStmt);
	/////////////////////////////////////////////////////////////////////////////
	//strcpy(query_stmt, "select * from NPC_Generation_sp order by SprNO") ;  
	strcpy(query_stmt, "EXEC up_get_npc_generation_sp");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;

	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nNPC init: ExecDirect Error ") ;
		return -1 ;
	}

	//SQLNumResultCols(hStmt, &nCols) ;
	
	ret= SQLFetch(hStmt) ;
	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,    NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,    0,    NULL );// Process any inserts in lpMsgBuf.
		// ...// Display the string.
		printf("\nLast Error: %s", (LPCTSTR)lpMsgBuf) ;
		// Free the buffer.
		LocalFree( lpMsgBuf );
		printf("\nNPC init: Fetch Error ") ;
		return -1 ;
	}
		
	while(c < Num_Of_NPC_Generation && ret == SQL_SUCCESS)
	{
		ret = SQLGetData(hStmt,  1, SQL_C_ULONG,		&NPC_Gen_Ref[c].SprNO,0, &cbValue);
		ret = SQLGetData(hStmt,  2, SQL_C_CHAR,			NPC_Gen_Ref[c].Han_name, 30, &cbValue);
		ret = SQLGetData(hStmt,  3, SQL_C_CHAR,			NPC_Gen_Ref[c].Name, 30, &cbValue);
		ret = SQLGetData(hStmt,  4, SQL_C_ULONG,		&NPC_Gen_Ref[c].Selectable,0, &cbValue);
		ret = SQLGetData(hStmt,  5, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_gender,0, &cbValue);
		ret = SQLGetData(hStmt,  6, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_FirstName,0, &cbValue);
		ret = SQLGetData(hStmt,  7, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_LastName,0, &cbValue);
		ret = SQLGetData(hStmt,  8, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_race,0, &cbValue);
		ret = SQLGetData(hStmt,  9, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Class_Warrior,0, &cbValue);
		ret = SQLGetData(hStmt,  10, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Class_Thief,0, &cbValue);
		ret = SQLGetData(hStmt,  11, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Class_Archery,0, &cbValue);
		ret = SQLGetData(hStmt,  12, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Class_Wizard,0, &cbValue);
		ret = SQLGetData(hStmt,  13, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Class_Priest,0, &cbValue);
		ret = SQLGetData(hStmt,  14, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_Farmer,0, &cbValue);
		ret = SQLGetData(hStmt,  15, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_Miner,0, &cbValue);
		ret = SQLGetData(hStmt,  16, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_FishHooker,0, &cbValue);
		ret = SQLGetData(hStmt,  17, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_Lumberjack,0, &cbValue);
		ret = SQLGetData(hStmt,  18, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_Butcher,0, &cbValue);
		ret = SQLGetData(hStmt,  19, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_Herbdigger,0, &cbValue);
		ret = SQLGetData(hStmt,  20, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_Herdman,0, &cbValue);
		ret = SQLGetData(hStmt,  21, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_Carpenter,0, &cbValue);
		ret = SQLGetData(hStmt,  22, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_Blacksmith,0, &cbValue);
		ret = SQLGetData(hStmt,  23, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_Cooker,0, &cbValue);
		ret = SQLGetData(hStmt,  24, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_Tailor,0, &cbValue);
		ret = SQLGetData(hStmt,  25, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_BowFlet,0, &cbValue);
		ret = SQLGetData(hStmt,  26, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_Alchemist,0, &cbValue);
		ret = SQLGetData(hStmt,  27, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_Candlemaker,0, &cbValue);
		ret = SQLGetData(hStmt,  28, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Job_Merchant,0, &cbValue);
		ret = SQLGetData(hStmt,  29, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Age_Min,0, &cbValue);
		ret = SQLGetData(hStmt,  30, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Age_Max,0, &cbValue);
		ret = SQLGetData(hStmt,  31, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Lv_min,0, &cbValue);
		ret = SQLGetData(hStmt,  32, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Lv_Max,0, &cbValue);
		ret = SQLGetData(hStmt,  33, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Tactics,0, &cbValue);
		ret = SQLGetData(hStmt,  34, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Spell,0, &cbValue);
		ret = SQLGetData(hStmt,  35, SQL_C_ULONG,		&NPC_Gen_Ref[c].Money_min,0, &cbValue);
		ret = SQLGetData(hStmt,  36, SQL_C_ULONG,		&NPC_Gen_Ref[c].Money_Max,0, &cbValue);
		ret = SQLGetData(hStmt,  37, SQL_C_ULONG,		&NPC_Gen_Ref[c].Bear_Peoriod,0, &cbValue);
		ret = SQLGetData(hStmt,  38, SQL_C_ULONG,		&NPC_Gen_Ref[c].Bear_amount,0, &cbValue);
		ret = SQLGetData(hStmt,  39, SQL_C_ULONG,		&NPC_Gen_Ref[c].Bear_Succes,0, &cbValue);
		ret = SQLGetData(hStmt,  40, SQL_C_ULONG,		&NPC_Gen_Ref[c].Bear_Do,0, &cbValue);
		ret = SQLGetData(hStmt,  41, SQL_C_ULONG,		&NPC_Gen_Ref[c].Bear_Probability,0, &cbValue);
		ret = SQLGetData(hStmt,  42, SQL_C_ULONG,		&NPC_Gen_Ref[c].Bear_Checktime,0, &cbValue);
		ret = SQLGetData(hStmt,  43, SQL_C_ULONG,		&NPC_Gen_Ref[c].Moderation,0, &cbValue);
		ret = SQLGetData(hStmt,  44, SQL_C_ULONG,		&NPC_Gen_Ref[c].royal,0, &cbValue);
		ret = SQLGetData(hStmt,  45, SQL_C_ULONG,		&NPC_Gen_Ref[c].Courage,0, &cbValue);
		ret = SQLGetData(hStmt,  46, SQL_C_ULONG,		&NPC_Gen_Ref[c].Faith,0, &cbValue);
		ret = SQLGetData(hStmt,  47, SQL_C_ULONG,		&NPC_Gen_Ref[c].Truth,0, &cbValue);
		ret = SQLGetData(hStmt,  48, SQL_C_ULONG,		&NPC_Gen_Ref[c].Justice,0, &cbValue);
		ret = SQLGetData(hStmt,  49, SQL_C_ULONG,		&NPC_Gen_Ref[c].Mercy,0, &cbValue);
		ret = SQLGetData(hStmt,  50, SQL_C_ULONG,		&NPC_Gen_Ref[c].Muder,0, &cbValue);
		ret = SQLGetData(hStmt,  51, SQL_C_ULONG,		&NPC_Gen_Ref[c].Robery,0, &cbValue);
		ret = SQLGetData(hStmt,  52, SQL_C_ULONG,		&NPC_Gen_Ref[c].Betrayal,0, &cbValue);
		ret = SQLGetData(hStmt,  53, SQL_C_ULONG,		&NPC_Gen_Ref[c].Disroyal,0, &cbValue);
		ret = SQLGetData(hStmt,  54, SQL_C_ULONG,		&NPC_Gen_Ref[c].Greed,0, &cbValue);
		ret = SQLGetData(hStmt,  55, SQL_C_ULONG,		&NPC_Gen_Ref[c].idol,0, &cbValue);
		ret = SQLGetData(hStmt,  56, SQL_C_ULONG,		&NPC_Gen_Ref[c].Reputaion,0, &cbValue);
		ret = SQLGetData(hStmt,  57, SQL_C_ULONG,		&NPC_Gen_Ref[c].Reputaion_range,0, &cbValue);
		ret = SQLGetData(hStmt,  58, SQL_C_ULONG,		&NPC_Gen_Ref[c].SpiritValue,0, &cbValue);
		ret = SQLGetData(hStmt,  59, SQL_C_ULONG,		&NPC_Gen_Ref[c].SpiritValue_Range,0, &cbValue);
		ret = SQLGetData(hStmt,  60, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[0],0, &cbValue);
		ret = SQLGetData(hStmt,  61, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[1],0, &cbValue);
		ret = SQLGetData(hStmt,  62, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[2],0, &cbValue);
		ret = SQLGetData(hStmt,  63, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[3],0, &cbValue);
		ret = SQLGetData(hStmt,  64, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[4],0, &cbValue);
		ret = SQLGetData(hStmt,  65, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[5],0, &cbValue);
		ret = SQLGetData(hStmt,  66, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[6],0, &cbValue);
		ret = SQLGetData(hStmt,  67, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[7],0, &cbValue);
		ret = SQLGetData(hStmt,  68, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[8],0, &cbValue);
		ret = SQLGetData(hStmt,  69, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[9],0, &cbValue);
		ret = SQLGetData(hStmt,  70, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[10],0, &cbValue);
		ret = SQLGetData(hStmt,  71, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[11],0, &cbValue);
		ret = SQLGetData(hStmt,  72, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[12],0, &cbValue);
		ret = SQLGetData(hStmt,  73, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[13],0, &cbValue);
		ret = SQLGetData(hStmt,  74, SQL_C_ULONG,		&NPC_Gen_Ref[c].PS[14],0, &cbValue);
		ret = SQLGetData(hStmt,  75, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Dice,0, &cbValue);
		ret = SQLGetData(hStmt,  76, SQL_C_ULONG,		&NPC_Gen_Ref[c].QuantityperLv,0, &cbValue);
		ret = SQLGetData(hStmt,  77, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[0],0, &cbValue);
		ret = SQLGetData(hStmt,  78, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[1],0, &cbValue);
		ret = SQLGetData(hStmt,  79, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[2],0, &cbValue);
		ret = SQLGetData(hStmt,  80, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[3],0, &cbValue);
		ret = SQLGetData(hStmt,  81, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[4],0, &cbValue);
		ret = SQLGetData(hStmt,  82, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[5],0, &cbValue);
		ret = SQLGetData(hStmt,  83, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[6],0, &cbValue);
		ret = SQLGetData(hStmt,  84, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[7],0, &cbValue);
		ret = SQLGetData(hStmt,  85, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[8],0, &cbValue);
		ret = SQLGetData(hStmt,  86, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[9],0, &cbValue);
		ret = SQLGetData(hStmt,  87, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[10],0, &cbValue);
		ret = SQLGetData(hStmt,  88, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[11],0, &cbValue);
		ret = SQLGetData(hStmt,  89, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[12],0, &cbValue);
		ret = SQLGetData(hStmt,  90, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[13],0, &cbValue);
		ret = SQLGetData(hStmt,  91, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS[14],0, &cbValue);
		ret = SQLGetData(hStmt,  92, SQL_C_ULONG,		&NPC_Gen_Ref[c].Sel_Dice1,0, &cbValue);
		ret = SQLGetData(hStmt,  93, SQL_C_ULONG,		&NPC_Gen_Ref[c].QuantityperLv1,0, &cbValue);
		ret = SQLGetData(hStmt,  94, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leathal_weapon1,0, &cbValue);
		ret = SQLGetData(hStmt,  95, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leathal_weapon2,0, &cbValue);
		ret = SQLGetData(hStmt,  96, SQL_C_ULONG,		&NPC_Gen_Ref[c].Damage_weapon,0, &cbValue);
		ret = SQLGetData(hStmt,  97, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leathal_attackws[0],0, &cbValue);
		ret = SQLGetData(hStmt,  98, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leathal_attackws[1],0, &cbValue);
		ret = SQLGetData(hStmt,  99, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leathal_attackws[2],0, &cbValue);
		ret = SQLGetData(hStmt,  100, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leathal_attackws[3],0, &cbValue);
		ret = SQLGetData(hStmt,  101, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leathal_attackws[4],0, &cbValue);
		ret = SQLGetData(hStmt,  102, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leathal_attackws[5],0, &cbValue);
		ret = SQLGetData(hStmt,  103, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leathal_attackws[6] ,0, &cbValue);
		ret = SQLGetData(hStmt,  104, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leathal_attackws[7] ,0, &cbValue);
		ret = SQLGetData(hStmt,  105, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leathal_attackws[8],0, &cbValue);
		ret = SQLGetData(hStmt,  106, SQL_C_ULONG,		&NPC_Gen_Ref[c].Damage_WP,0, &cbValue);
		ret = SQLGetData(hStmt,  107, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leathal_WS,0, &cbValue);
		ret = SQLGetData(hStmt,  108, SQL_C_ULONG,		&NPC_Gen_Ref[c].Success,0, &cbValue);
		ret = SQLGetData(hStmt,  109, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leathal_ps,0, &cbValue);
		ret = SQLGetData(hStmt,  110, SQL_C_ULONG,		&NPC_Gen_Ref[c].DamagePercent_ps,0, &cbValue);
		ret = SQLGetData(hStmt,  111, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[0],0, &cbValue);
		ret = SQLGetData(hStmt,  112, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[1],0, &cbValue);
		ret = SQLGetData(hStmt,  113, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[2],0, &cbValue);
		ret = SQLGetData(hStmt,  114, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[3],0, &cbValue);
		ret = SQLGetData(hStmt,  115, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[4],0, &cbValue);
		ret = SQLGetData(hStmt,  116, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[5],0, &cbValue);
		ret = SQLGetData(hStmt,  117, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[6],0, &cbValue);
		ret = SQLGetData(hStmt,  118, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[7],0, &cbValue);
		ret = SQLGetData(hStmt,  119, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[8],0, &cbValue);
		ret = SQLGetData(hStmt,  120, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[9],0, &cbValue);
		ret = SQLGetData(hStmt,  121, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[10],0, &cbValue);
		ret = SQLGetData(hStmt,  122, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[11],0, &cbValue);
		ret = SQLGetData(hStmt,  123, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[12],0, &cbValue);
		ret = SQLGetData(hStmt,  124, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[13],0, &cbValue);
		ret = SQLGetData(hStmt,  125, SQL_C_ULONG,		&NPC_Gen_Ref[c].Inventory[14],0, &cbValue);
		ret = SQLGetData(hStmt,  126, SQL_C_ULONG,		&NPC_Gen_Ref[c].Amount_Dice,0, &cbValue);
		ret = SQLGetData(hStmt,  127, SQL_C_ULONG,		&NPC_Gen_Ref[c].Righthand,0, &cbValue);
		ret = SQLGetData(hStmt,  128, SQL_C_ULONG,		&NPC_Gen_Ref[c].Lefthand,0, &cbValue);
		ret = SQLGetData(hStmt,  129, SQL_C_ULONG,		&NPC_Gen_Ref[c].Body,0, &cbValue);
		ret = SQLGetData(hStmt,  130, SQL_C_ULONG,		&NPC_Gen_Ref[c].Helmet,0, &cbValue);
		ret = SQLGetData(hStmt,  131, SQL_C_ULONG,		&NPC_Gen_Ref[c].leg,0, &cbValue);
		ret = SQLGetData(hStmt,  132, SQL_C_ULONG,		&NPC_Gen_Ref[c].Leg_Probability,0, &cbValue);
		ret = SQLGetData(hStmt,  133, SQL_C_ULONG,		&NPC_Gen_Ref[c].neck,0, &cbValue);
		ret = SQLGetData(hStmt,  134, SQL_C_ULONG,		&NPC_Gen_Ref[c].neck_Probability	,0, &cbValue);
		ret = SQLGetData(hStmt,  135, SQL_C_ULONG,		&NPC_Gen_Ref[c].unique1,0, &cbValue);
		ret = SQLGetData(hStmt,  136, SQL_C_ULONG,		&NPC_Gen_Ref[c].Unique1_probalbility,0, &cbValue);
		ret = SQLGetData(hStmt,  137, SQL_C_ULONG,		&NPC_Gen_Ref[c].Unique2,0, &cbValue);
		ret = SQLGetData(hStmt,  138, SQL_C_ULONG,		&NPC_Gen_Ref[c].unique2_probability	,0, &cbValue);
		ret = SQLGetData(hStmt,  139, SQL_C_ULONG,		&NPC_Gen_Ref[c].Crapple,0, &cbValue);
		ret = SQLGetData(hStmt,  140, SQL_C_ULONG,		&NPC_Gen_Ref[c].swordmanship,0, &cbValue);
		ret = SQLGetData(hStmt,  141, SQL_C_ULONG,		&NPC_Gen_Ref[c].Archery,0, &cbValue);
		ret = SQLGetData(hStmt,  142, SQL_C_ULONG,		&NPC_Gen_Ref[c].Fencing,0, &cbValue);
		ret = SQLGetData(hStmt,  143, SQL_C_ULONG,		&NPC_Gen_Ref[c].Mace_fighting,0, &cbValue);
		ret = SQLGetData(hStmt,  144, SQL_C_ULONG,		&NPC_Gen_Ref[c].Pierce,0, &cbValue);
		ret = SQLGetData(hStmt,  145, SQL_C_ULONG,		&NPC_Gen_Ref[c].Whirl,0, &cbValue);
		ret = SQLGetData(hStmt,  146, SQL_C_ULONG,		&NPC_Gen_Ref[c].Hurl,0, &cbValue);
		ret = SQLGetData(hStmt,  147, SQL_C_ULONG,		&NPC_Gen_Ref[c].Parrying,0, &cbValue);
		ret = SQLGetData(hStmt,  148, SQL_C_ULONG,		&NPC_Gen_Ref[c].Double_Swordmanship	,0, &cbValue);
		ret = SQLGetData(hStmt,  149, SQL_C_ULONG,		&NPC_Gen_Ref[c].Double_MaceFighting	,0, &cbValue);
		ret = SQLGetData(hStmt,  150, SQL_C_ULONG,		&NPC_Gen_Ref[c].Magery,0, &cbValue);
		ret = SQLGetData(hStmt,  151, SQL_C_ULONG,		&NPC_Gen_Ref[c].Orison,0, &cbValue);
		ret = SQLGetData(hStmt,  152, SQL_C_ULONG,		&NPC_Gen_Ref[c].LV_Str,0, &cbValue);
		ret = SQLGetData(hStmt,  153, SQL_C_ULONG,		&NPC_Gen_Ref[c].Con,0, &cbValue);
		ret = SQLGetData(hStmt,  154, SQL_C_ULONG,		&NPC_Gen_Ref[c].Dex,0, &cbValue);
		ret = SQLGetData(hStmt,  155, SQL_C_ULONG,		&NPC_Gen_Ref[c].Wis,0, &cbValue);
		ret = SQLGetData(hStmt,  156, SQL_C_ULONG,		&NPC_Gen_Ref[c].Int,0, &cbValue);
		ret = SQLGetData(hStmt,  157, SQL_C_ULONG,		&NPC_Gen_Ref[c].Movp,0, &cbValue);
		ret = SQLGetData(hStmt,  158, SQL_C_ULONG,		&NPC_Gen_Ref[c].Char,0, &cbValue);
		ret = SQLGetData(hStmt,  159, SQL_C_ULONG,		&NPC_Gen_Ref[c].Endu,0, &cbValue);
		ret = SQLGetData(hStmt,  160, SQL_C_ULONG,		&NPC_Gen_Ref[c].Mor,0, &cbValue);
		ret = SQLGetData(hStmt,  161, SQL_C_ULONG,		&NPC_Gen_Ref[c].Luck,0, &cbValue);
		ret = SQLGetData(hStmt,  162, SQL_C_ULONG,		&NPC_Gen_Ref[c].WS_PS,0, &cbValue);
		ret = SQLGetData(hStmt,  163, SQL_C_ULONG,		&NPC_Gen_Ref[c].Fullpoint,0, &cbValue);
    //< CSD-010907
    /*
		ret = SQLGetData(hStmt,  164, SQL_C_ULONG,		&NPC_Gen_Ref[c].Suplus_Resist_Death	,0, &cbValue);
		ret = SQLGetData(hStmt,  165, SQL_C_ULONG,		&NPC_Gen_Ref[c].Suplus_Resist_Ston	,0, &cbValue);
		ret = SQLGetData(hStmt,  166, SQL_C_ULONG,		&NPC_Gen_Ref[c].Suplus_Resist_Magic	,0, &cbValue);
		ret = SQLGetData(hStmt,  167, SQL_C_ULONG,		&NPC_Gen_Ref[c].Suplus_Resist_Fire	,0, &cbValue);
		ret = SQLGetData(hStmt,  168, SQL_C_ULONG,		&NPC_Gen_Ref[c].Suplus_Resist_Ice	,0, &cbValue);
		ret = SQLGetData(hStmt,  169, SQL_C_ULONG,		&NPC_Gen_Ref[c].Suplus_Resist_Light	,0, &cbValue);
    */
    ret = SQLGetData(hStmt,  164, SQL_C_ULONG,		&NPC_Gen_Ref[c].nPoison	,0, &cbValue);
		ret = SQLGetData(hStmt,  165, SQL_C_ULONG,		&NPC_Gen_Ref[c].nCurse	,0, &cbValue);
		ret = SQLGetData(hStmt,  166, SQL_C_ULONG,		&NPC_Gen_Ref[c].nHoly	  ,0, &cbValue);
		ret = SQLGetData(hStmt,  167, SQL_C_ULONG,		&NPC_Gen_Ref[c].nFire	  ,0, &cbValue);
		ret = SQLGetData(hStmt,  168, SQL_C_ULONG,		&NPC_Gen_Ref[c].nIce	  ,0, &cbValue);
		ret = SQLGetData(hStmt,  169, SQL_C_ULONG,		&NPC_Gen_Ref[c].nElect	,0, &cbValue);
    //> CSD-010907
		ret = SQLGetData(hStmt,  170, SQL_C_ULONG,		&NPC_Gen_Ref[c].DivideLv,0, &cbValue);
		ret = SQLGetData(hStmt,  171, SQL_C_ULONG,		&NPC_Gen_Ref[c].Resist_Range,0, &cbValue);
		ret = SQLGetData(hStmt,  172, SQL_C_ULONG,		&NPC_Gen_Ref[c].Tamingable,0, &cbValue);
		ret = SQLGetData(hStmt,  173, SQL_C_ULONG,		&NPC_Gen_Ref[c].Taming_min,0, &cbValue);
		ret = SQLGetData(hStmt,  174, SQL_C_ULONG,		&NPC_Gen_Ref[c].Taming_max,0, &cbValue);
		ret = SQLGetData(hStmt,  175, SQL_C_ULONG,		&NPC_Gen_Ref[c].Talkanimal_min,0, &cbValue);
		ret = SQLGetData(hStmt,  176, SQL_C_ULONG,		&NPC_Gen_Ref[c].Talkanimal_max,0, &cbValue);
		ret = SQLGetData(hStmt,  177, SQL_C_ULONG,		&NPC_Gen_Ref[c].Resist,0, &cbValue);
		ret = SQLGetData(hStmt,  178, SQL_C_ULONG,		&NPC_Gen_Ref[c].Resist_range1,0, &cbValue);
		ret = SQLGetData(hStmt,  179, SQL_C_ULONG,		&NPC_Gen_Ref[c].ValueHP,0, &cbValue);
		ret = SQLGetData(hStmt,  180, SQL_C_ULONG,		&NPC_Gen_Ref[c].ValueSP,0, &cbValue);
		ret = SQLGetData(hStmt,  181, SQL_C_ULONG,		&NPC_Gen_Ref[c].Rely_value,0, &cbValue);
		ret = SQLGetData(hStmt,  182, SQL_C_ULONG,		&NPC_Gen_Ref[c].nor_range,0, &cbValue);
		ret = SQLGetData(hStmt,  183, SQL_C_ULONG,		&NPC_Gen_Ref[c].att_range,0, &cbValue);
		ret = SQLGetData(hStmt,  184, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[0],0, &cbValue);
		ret = SQLGetData(hStmt,  185, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[1],0, &cbValue);
		ret = SQLGetData(hStmt,  186, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[2],0, &cbValue);
		ret = SQLGetData(hStmt,  187, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[3],0, &cbValue);
		ret = SQLGetData(hStmt,  188, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[4],0, &cbValue);
		ret = SQLGetData(hStmt,  189, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[5],0, &cbValue);
		ret = SQLGetData(hStmt,  190, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[6],0, &cbValue);
		ret = SQLGetData(hStmt,  191, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[7],0, &cbValue);
		ret = SQLGetData(hStmt,  192, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[8],0, &cbValue);
		ret = SQLGetData(hStmt,  193, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[9],0, &cbValue);
		ret = SQLGetData(hStmt,  194, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[10],0, &cbValue);
		ret = SQLGetData(hStmt,  195, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[11],0, &cbValue);
		ret = SQLGetData(hStmt,  196, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[12],0, &cbValue);
		ret = SQLGetData(hStmt,  197, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[13],0, &cbValue);
		ret = SQLGetData(hStmt,  198, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[14],0, &cbValue);
		ret = SQLGetData(hStmt,  199, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[15],0, &cbValue);
		ret = SQLGetData(hStmt,  200, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[16],0, &cbValue);
		ret = SQLGetData(hStmt,  201, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[17],0, &cbValue);
		ret = SQLGetData(hStmt,  202, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[18],0, &cbValue);
		ret = SQLGetData(hStmt,  203, SQL_C_ULONG,		&NPC_Gen_Ref[c].offset[19],0, &cbValue);
		ret = SQLGetData(hStmt,  204, SQL_C_ULONG,		&NPC_Gen_Ref[c].neglect_attack,0, &cbValue);
		ret = SQLGetData(hStmt,  205, SQL_C_ULONG,		&NPC_Gen_Ref[c].neglect_avoid,0, &cbValue);
		ret = SQLGetData(hStmt,  206, SQL_C_ULONG,		&NPC_Gen_Ref[c].check_pass,0, &cbValue);
		ret = SQLGetData(hStmt,  207, SQL_C_ULONG,		&NPC_Gen_Ref[c].party,0, &cbValue);
		ret = SQLGetData(hStmt,  208, SQL_C_ULONG,		&NPC_Gen_Ref[c].enemy_no,0, &cbValue);
		ret = SQLGetData(hStmt,  209, SQL_C_ULONG,		&NPC_Gen_Ref[c].levelgap,0, &cbValue);
		ret = SQLGetData(hStmt,  210, SQL_C_ULONG,		&NPC_Gen_Ref[c].apgap,0, &cbValue);
		ret = SQLGetData(hStmt,  211, SQL_C_ULONG,		&NPC_Gen_Ref[c].vpgap,0, &cbValue);
		ret = SQLGetData(hStmt,  212, SQL_C_ULONG,		&NPC_Gen_Ref[c].opendoor,0, &cbValue);
		ret = SQLGetData(hStmt,  213, SQL_C_ULONG,		&NPC_Gen_Ref[c].lockdoor,0, &cbValue);
		ret = SQLGetData(hStmt,  214, SQL_C_ULONG,		&NPC_Gen_Ref[c].closedoor,0, &cbValue);
		ret = SQLGetData(hStmt,  215, SQL_C_ULONG,		&NPC_Gen_Ref[c].breakdoor,0, &cbValue);
		ret = SQLGetData(hStmt,  216, SQL_C_ULONG,		&NPC_Gen_Ref[c].openobj,0, &cbValue);
		ret = SQLGetData(hStmt,  217, SQL_C_ULONG,		&NPC_Gen_Ref[c].lockbj,0, &cbValue);
		ret = SQLGetData(hStmt,  218, SQL_C_ULONG,		&NPC_Gen_Ref[c].closeobj,0, &cbValue);
		ret = SQLGetData(hStmt,  219, SQL_C_ULONG,		&NPC_Gen_Ref[c].breakobj,0, &cbValue);
		ret = SQLGetData(hStmt,  220, SQL_C_ULONG,		&NPC_Gen_Ref[c].act_month,0, &cbValue);
		ret = SQLGetData(hStmt,  221, SQL_C_ULONG,		&NPC_Gen_Ref[c].act_time,0, &cbValue);
		ret = SQLGetData(hStmt,  222, SQL_C_ULONG,		&NPC_Gen_Ref[c].act_bi,0, &cbValue);
		ret = SQLGetData(hStmt,  223, SQL_C_ULONG,		&NPC_Gen_Ref[c].act_chun,0, &cbValue);
		ret = SQLGetData(hStmt,  224, SQL_C_ULONG,		&NPC_Gen_Ref[c].act_nun		,0, &cbValue);

		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nError!!! (%d)", ret) ;
			return -1 ;
		}
		c++ ;
		ret= SQLFetch(hStmt) ;
	}
	
//	printf("\n<<<<<< %d Rows.>>>>>>>>", c) ;
	nNPC_Type= c ;
	SQLFreeStmt(hStmt, SQL_DROP) ;
	printf("	  .NPC Info   %3d data Loaded !\n", c) ;

//	for(i=0 ; i<nNPC_Type; i++) {
//		printf("\n %s %d", NPC_Ref[i].Name, NPC_Ref[i].SprNo) ;
//	}

	return c ;
}

/*
SprNO
han_name
Name
Selectable
Sel_gender
Sel_FirstName
Sel_LastName
Sel_race
Sel_Class_Warrior
Sel_Class_Thief
Sel_Class_Archery
Sel_Class_Wizard
Sel_Class_Priest
Sel_Job_Farmer
Sel_Job_Miner
Sel_Job_FishHooker
Sel_Job_Lumberjack
Sel_Job_Butcher
Sel_Job_Herbdigger
Sel_Job_Herdman
Sel_Job_Carpenter
Sel_Job_Blacksmith
Sel_Job_Cooker
Sel_Job_Tailor
Sel_Job_BowFlet
Sel_Job_Alchemist
Sel_Job_Candlemaker
Sel_Job_Merchant
Sel_Age_Min
Sel_Age_Max
Sel_Lv_min
Sel_Lv_Max
Sel_Tactics
Sel_Spell
Money_min
Money_Max
Bear_Peoriod
Bear_amount
Bear_Succes
Bear_Do
Bear_Probability
Bear_Checktime
Moderation
royal
Courage
Faith
Truth
Justice
Mercy
Muder
Robery
Betrayal
Disroyal
Greed
idol
Reputaion
Reputaion_range
SpiritValue
SpiritValue_Range
PS1
PS2
PS3
PS4
PS5
PS6
PS7
PS8
PS9
PS10
PS11
PS12
PS13
PS14
PS15
Sel_Dice
QuantityperLv
WS1
WS2
WS3
WS4
WS5
WS6
WS7
WS8
WS9
WS10
WS11
WS12
WS13
WS14
WS15
Sel_Dice1
QuantityperLv1
Leathal_weapon1
Leathal_weapon2
Damage_weapon
Leathal_attackws1
Leathal_attackws2
Leathal_attackws3
Leathal_attackws4
Leathal_attackws5
Leathal_attackws6
Leathal_attackws7
Leathal_attackws8
Leathal_attackws9
Damage_WP
Leathal_WS
Success
Leathal_ps
DamagePercent_ps
Inventory1_order
Inventory2_order
Inventory3_order
Inventory4_order
Inventory5_Order
Inventory6_order
Inventory7_order
Inventory8_order
Inventory9_order
Inventory10_order
Inventory11_order
Inventory12_order
Inventory13_order
Inventory14_order
Inventory15_order
Amount_Dice
Righthand
Lefthand
Body
Helmet
leg
Leg_Probability	int	
neck
neck_Probability	
unique1
Unique1_probalbility
Unique2
unique2_probability	
Crapple
swordmanship
Archery
Fencing
Mace_fighting
Pierce
Whirl
Hurl
Parrying
Double_Swordmanship	
Double_MaceFighting	
Magery
Orison
LV_Str
Con
Dex
Wis
Int
Movp
Char
Endu
Mor
Luck
WS_PS
Fullpoint
Suplus_Resist_Death	
Suplus_Resist_Ston	
Suplus_Resist_Magic	
Suplus_Resist_Fire	
Suplus_Resist_Ice	
Suplus_Resist_Light	
DivideLv
Resist_Range
Tamingable
Taming_min
Taming_max
Talkanimal_min
Talkanimal_max
Resist
Resist_range1
ValueHP
ValueSP
Rely_value
nor_range
att_range
offset1
offset2
offset3
offset4
offset5
offset6
offset7
offset8
offset9
offset10
offset11
offset12
offset13
offset14
offset15
offset16
offset17
offset18
offset19
offset20
neglect_attack
neglect_avoid
check_pass
party
enemy_no
levelgap
apgap
vpgap
opendoor
lockdoor
closedoor
breakdoor
openobj
lockbj
closeobj
breakobj
act_month
act_time
act_bi
act_chun
act_nun		



*/