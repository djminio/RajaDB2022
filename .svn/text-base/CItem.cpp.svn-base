//#include <winerror.h>
#include "StdAfx.h"
#include "main.h"
#include "CItem.h"

#include "Mylog.h"
const int  MAX_DIVIDE_ITEM	= 1000000;

extern CItem *ItemUnit( int type, int item_no );
extern DWORD CreateItemDuration( int type, int itemno );
extern int GetBoxItemId_SQL( );


extern HENV hEnv ;
extern HDBC hDBC ;
struct CItem_List Item_Ref ;


CItem_Plant			CPlant		[MAX_ITEM_NUM];
CItem_Mineral		CMineral	[MAX_ITEM_NUM];
CItem_Herb			CHerb		[MAX_ITEM_NUM];
CItem_Cook			CCook		[MAX_ITEM_NUM];
CItem_Potion		CPotion		[MAX_ITEM_NUM];
CItem_Tool			CTool		[MAX_ITEM_NUM];
CItem_Weapon		CWeapon		[MAX_ITEM_NUM];
CItem_Disposable	CDisposable	[MAX_ITEM_NUM];
CItem_Armor			CArmor		[MAX_ITEM_NUM];
CItem_Accessory		CAccessory	[MAX_ITEM_NUM];
CItem_Etc			CEtc		[MAX_ITEM_NUM];



ItemAttr TItem; // 임시로 사용하는..


// 아이템 참조 테이블을 DB에서 읽어와 생성하는 함수.
int initItem(void)		
{
	int i, c ;
	int check[20] = {0,};
	if(hEnv == NULL || hDBC == NULL) return -1 ;

	// set the number of items					
	/*
	Item_Ref.nItem[0]= Num_Of_CItem_Plant		;
	Item_Ref.nItem[1]= Num_Of_CItem_Mineral		;
	Item_Ref.nItem[2]= Num_Of_CItem_Herb		;
	Item_Ref.nItem[3]= Num_Of_CItem_Cook		;
	Item_Ref.nItem[4]= Num_Of_CItem_Potion		;
	Item_Ref.nItem[5]= Num_Of_CItem_Tool		;
	Item_Ref.nItem[6]= Num_Of_CItem_Weapon		;
	Item_Ref.nItem[7]= Num_Of_CItem_Disposable	;
	Item_Ref.nItem[8]= Num_Of_CItem_Armor		;
	Item_Ref.nItem[9]= Num_Of_CItem_Accessory	;
	Item_Ref.nItem[10]= Num_Of_CItem_Etc		;*/
	
	c= CPlant[0].getAllData() - 1 ;
	if( c <= 0  ){ JustMsg( " Fail to Read Plant Item "); return -1; }
	Item_Ref.nItem[0]= c;
	MyLog( LOG_NORMAL, "    .Plant Item		%4d data Loaded", c) ;
	
	c= CMineral[0].getAllData() - 1 ;
	if( c <= 0  ){ JustMsg("  Fail to Read Mineral Item "); return -1; }
	Item_Ref.nItem[1]= c;
	MyLog( LOG_NORMAL, "    .Mineral Item		%4d data Loaded", c) ;
	
	c= CHerb[0].getAllData() - 1 ;
	if( c <= 0  ){ JustMsg("  Fail to Read Herb Item "); return -1; }
	Item_Ref.nItem[2]= c;
	MyLog( LOG_NORMAL, "    .Herb Item		%4d data Loaded", c) ;
	
	c= CCook[0].getAllData() - 1 ;
	if( c <= 0  ){ JustMsg("  Fail to Read Cook Item "); return -1; }
	Item_Ref.nItem[3]= c;
	MyLog( LOG_NORMAL, "    .Cook Item		%4d data Loaded", c) ;
	
	c= CPotion[0].getAllData() - 1 ;
	if( c <= 0  ){ JustMsg("  Fail to Read Potion Item "); return -1; }
	Item_Ref.nItem[4]= c;
	MyLog( LOG_NORMAL, "    .Potion Item		%4d data Loaded", c) ;
	
	c= CTool[0].getAllData() - 1 ;
	if( c <= 0  ){ JustMsg("  Fail to Read Tool Item "); return -1; }
	Item_Ref.nItem[5]= c;
	MyLog( LOG_NORMAL, "    .Tool Item		%4d data Loaded", c) ;
	
	c= CWeapon[0].getAllData() - 1 ;
	if( c <= 0  ){ JustMsg("  Fail to Read Weapon Item "); return -1; }
	Item_Ref.nItem[6]= c;
	MyLog( LOG_NORMAL, "    .Weapon Item		%4d data Loaded", c) ;
	
	c= CDisposable[0].getAllData() - 1 ;
	if( c <= 0  ){ JustMsg("  Fail to Read Disposable Item "); return -1; }
	Item_Ref.nItem[7]= c;
	MyLog( LOG_NORMAL, "    .Disposable Item	%4d data Loaded", c) ;
	
	c= CArmor[0].getAllData() - 1 ;
	if( c <= 0 ){ JustMsg("  Fail to Read Armor Item "); return -1; }
	Item_Ref.nItem[8]= c;
	MyLog( LOG_NORMAL, "    .Armor Item		%4d data Loaded", c) ;
	
	c= CAccessory[0].getAllData() - 1 ;
	if( c <= 0 ){ JustMsg("  Fail to Read Accessory Item "); return -1; }
	Item_Ref.nItem[9]= c;
	MyLog( LOG_NORMAL, "    .Accessory Item	%4d data Loaded", c) ;
	
	c= CEtc[0].getAllData() - 1 ;
	if( c <= 0 ){ JustMsg("  Fail to Read Etc  Item "); return -1; }
	Item_Ref.nItem[10]= c;
	MyLog( LOG_NORMAL, "    .Etc Item		%4d data Loaded", c) ;

	
	// 0번 인덱스는 사용하지 않음. 
	// item번호가 1번부터 시작(0번은 NULL아이템, 즉 아이템 없음의 상태를 나타낸다)
	for(i= 1 ; i <= Item_Ref.nItem[0] ; i++) Item_Ref.Item_Info[0][i]= &CPlant[i] ;
	for(i= 1 ; i <= Item_Ref.nItem[1] ; i++) Item_Ref.Item_Info[1][i]= &CMineral[i] ;
	for(i= 1 ; i <= Item_Ref.nItem[2] ; i++) Item_Ref.Item_Info[2][i]= &CHerb[i] ;
	for(i= 1 ; i <= Item_Ref.nItem[3] ; i++) Item_Ref.Item_Info[3][i]= &CCook[i] ;
	for(i= 1 ; i <= Item_Ref.nItem[4] ; i++) Item_Ref.Item_Info[4][i]= &CPotion[i] ;
	for(i= 1 ; i <= Item_Ref.nItem[5] ; i++) Item_Ref.Item_Info[5][i]= &CTool[i] ;
	for(i= 1 ; i <= Item_Ref.nItem[6] ; i++) Item_Ref.Item_Info[6][i]= &CWeapon[i] ;
	for(i= 1 ; i <= Item_Ref.nItem[7] ; i++) Item_Ref.Item_Info[7][i]= &CDisposable[i] ;
	for(i= 1 ; i <= Item_Ref.nItem[8] ; i++) Item_Ref.Item_Info[8][i]= &CArmor[i] ;
	for(i= 1 ; i <= Item_Ref.nItem[9] ; i++) Item_Ref.Item_Info[9][i]= &CAccessory[i] ;
	for(i= 1 ; i <= Item_Ref.nItem[10] ; i++) Item_Ref.Item_Info[10][i]= &CEtc[i] ;

	InitSkillTable( )	;
	return 1 ;
	

}


/////////////////////////////////////////////////////////////////////////////
//
// 함수설명: DB에서 해당 아이템의 수치를 읽어오는 함수.
//				virtual 함수이다.
//				해당 아이템 배열의 1번부터 읽어오기 시작한다.
//				Num_Of_CItem_XXXXX로 define된 개수만큼 읽어온다.
//				DB에 있는 아이템의 개수가 Num_Of_CItem_XXXXX보다 작다면
//				DB에 있는 아이템 재수만 읽어온다.
// 
// 리턴값: DB에서 실제로 읽어온 아이템 개수
//
/////////////////////////////////////////////////////////////////////////////

int CItem_Plant::getAllData(void)
{
	if(Num_Of_CItem_Plant <= 0) {
		//fprintf(stdout, "\n	No item's available ") ;
		return -4 ; // No item's available
	}
	HSTMT hStmt= NULL ;
	RETCODE ret ;
	SWORD nCols ;
	char query_stmt[80]= {0, } ;
	char col_name[60]= {0, } ;
	//UWORD i ;
	SDWORD cbValue ;
	int *tmp= NULL ;
	int c= 1 ;
	int i= 4 ;
	
  SQLAllocStmt(hDBC, &hStmt);
  /////////////////////////////////////////////////////////////////////////////
  //strcpy(query_stmt, "select * from Item_Plant order by item_id") ;
  strcpy(query_stmt, "EXEC up_get_item_plant");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;
	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nItem PLAnt: ExecDirect Error ") ;
		return -1 ;
	}

	SQLNumResultCols(hStmt, &nCols) ;
	
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
			printf("\nItem7: Fetch Error ") ;
		return -1 ;
	}

	while(ret == SQL_SUCCESS)
	{
		ret= SQLGetData(hStmt, 1, SQL_C_SLONG, &c, sizeof(int), &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nError!!! (%d)", ret) ;
			return -1 ;
		}
		CPlant[c].Item_id = c;
		ret= SQLGetData(hStmt, 2, SQL_C_CHAR, &CPlant[c].Name, sizeof(Name), &cbValue) ;

		ret= SQLGetData(hStmt, 3, SQL_C_CHAR, &CPlant[c].Han_Name, sizeof(Han_Name), &cbValue) ;
		EatRearWhiteChar( CPlant[c].Han_Name );
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}

		tmp = &CPlant[c].lv;
		for(i=4; i <= nCols; i++) {
			ret= SQLGetData(hStmt, i, SQL_C_SLONG, tmp, sizeof(int), &cbValue) ;
			tmp++ ;
		}
		c++ ;
		ret= SQLFetch(hStmt) ;			
		m_Much = 0;
	}
	SQLFreeStmt(hStmt, SQL_DROP) ;
	return c ;
}


int CItem_Mineral::getAllData(void)
{
	if(Num_Of_CItem_Mineral <= 0) {
		return -4 ; // No item's available
	}
	HSTMT hStmt= NULL ;
	RETCODE ret ;
	SWORD nCols ;
	char query_stmt[80]= {0, } ;
	SDWORD cbValue ;
	int *tmp ;
	int c= 1, i ;
	
	SQLAllocStmt(hDBC, &hStmt);
  /////////////////////////////////////////////////////////////////////////////
  //strcpy(query_stmt, "select * from Item_Mineral order by item_id") ;
  strcpy(query_stmt, "EXEC up_get_item_mineral");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;
	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nItem Mineral: ExecDirect Error ") ;
		return -1 ;
	}

	SQLNumResultCols(hStmt, &nCols) ;
	
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
			printf("\nItem7: Fetch Error ") ;
		return -1 ;
	}
		
	//tmp= &Nead2_Level ;
	//tmp= &lv ;
	while( ret == SQL_SUCCESS)
	{
		// Accquire the DATA
		ret= SQLGetData(hStmt, 1, SQL_C_SLONG, &c, sizeof(int), &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nError!!! (%d)", ret) ;
			return -1 ;
		}
		CMineral[c].Item_id = c;

		ret= SQLGetData(hStmt, 2, SQL_C_CHAR, &CMineral[c].Name, sizeof(Name), &cbValue) ;
		ret= SQLGetData(hStmt, 3, SQL_C_CHAR, &CMineral[c].Han_Name, sizeof(Han_Name), &cbValue) ;
		EatRearWhiteChar( CMineral[c].Han_Name );
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}


		tmp = &CMineral[c].lv;
		for(i=4; i <= nCols; i++) {
			ret= SQLGetData(hStmt, i, SQL_C_SLONG, tmp, sizeof(int), &cbValue) ;
			tmp++ ;
		}
		c++ ;
		
		ret= SQLFetch(hStmt) ;
		m_Much  = 0;
	}
	SQLFreeStmt(hStmt, SQL_DROP) ;
	return c ;
}


int CItem_Herb::getAllData(void)
{
	if(Num_Of_CItem_Herb <= 0) {
		return -4 ; // No item's available
	}
	HSTMT hStmt= NULL ;
	RETCODE ret ;
	SWORD nCols ;
	char query_stmt[80]= {0, } ;
	SDWORD cbValue ;
	int *tmp ;
	int c= 1, i ;
	SQLAllocStmt(hDBC, &hStmt);
  /////////////////////////////////////////////////////////////////////////////
  //strcpy(query_stmt, "select * from Item_Herb order by item_id") ;
  strcpy(query_stmt, "EXEC up_get_item_herb");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;
	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nItem Herb: ExecDirect Error ") ;
		return -1 ;
	}

	SQLNumResultCols(hStmt, &nCols) ;
	
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
			printf("\nItem7: Fetch Error ") ;
		return -1 ;
	}	
		
	while( ret == SQL_SUCCESS)
	{	
		// Accquire the DATA
		ret= SQLGetData(hStmt, 1, SQL_C_SLONG, &c, sizeof(int), &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nError!!! (%d)", ret) ;
			return -1 ;
		}
		CHerb[c].Item_id = c;

		ret= SQLGetData(hStmt, 2, SQL_C_CHAR, &CHerb[c].Name, sizeof(Name), &cbValue) ;
		ret= SQLGetData(hStmt, 3, SQL_C_CHAR, &CHerb[c].Han_Name, sizeof(Han_Name), &cbValue) ;
		EatRearWhiteChar( CHerb[c].Han_Name );
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}
		
		tmp = &CHerb[c].lv;
		for(i=4; i <= nCols; i++) {
			ret= SQLGetData(hStmt, i, SQL_C_SLONG, tmp, sizeof(int), &cbValue) ;
			tmp++ ;
		}
		c++ ;
		
		ret= SQLFetch(hStmt) ;
		m_Much  = 0;
	}
	SQLFreeStmt(hStmt, SQL_DROP) ;
	return c ;
}

int CItem_Cook::getAllData(void)
{
	if(Num_Of_CItem_Cook <= 0) {
		return -4 ; // No item's available
	}
	HSTMT hStmt= NULL ;
	RETCODE ret ;
	SWORD nCols ;
	char query_stmt[80]= {0, } ;
	SDWORD cbValue ;
	int *tmp ;
	int c= 1, i ;
	SQLAllocStmt(hDBC, &hStmt);
  /////////////////////////////////////////////////////////////////////////////
  //strcpy(query_stmt, "select * from Item_Cook order by item_id") ;
  strcpy(query_stmt, "EXEC up_get_item_cook");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;

	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nItem Cook: ExecDirect Error ") ;
		return -1 ;
	}

	SQLNumResultCols(hStmt, &nCols) ;
	
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
			printf("\nItem7: Fetch Error ") ;
		return -1 ;
	}
		
	while(ret == SQL_SUCCESS)
	{
		// Accquire the DATA
		ret= SQLGetData(hStmt, 1, SQL_C_SLONG, &c, sizeof(int), &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nError!!! (%d)", ret) ;
			return -1 ;
		}
		CCook[c].Item_id = c;
		ret= SQLGetData(hStmt, 2, SQL_C_CHAR, &CCook[c].Name, sizeof(Name), &cbValue) ;
		ret= SQLGetData(hStmt, 3, SQL_C_CHAR, &CCook[c].Han_Name, sizeof(Han_Name), &cbValue) ;
		EatRearWhiteChar( CCook[c].Han_Name );
				
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}

		tmp = &CCook[c].lv;
		for(i=4; i <= nCols; i++) {
			ret= SQLGetData(hStmt, i, SQL_C_SLONG, tmp, sizeof(int), &cbValue) ;
			tmp++ ;
		}
		c++ ;
		
		ret= SQLFetch(hStmt) ;
		m_Much  = 0;					//1215
	}
	SQLFreeStmt(hStmt, SQL_DROP) ;
	return c ;
}

int CItem_Potion::getAllData(void)
{
	if(Num_Of_CItem_Potion <= 0) {
		return -4 ; // No item's available
	}
	HSTMT hStmt= NULL ;
	RETCODE ret ;
	SWORD nCols ;
	char query_stmt[80]= {0, } ;
	SDWORD cbValue ;
	int *tmp ;
	int c= 1, i ;
	SQLAllocStmt(hDBC, &hStmt);
  /////////////////////////////////////////////////////////////////////////////
  //strcpy(query_stmt, "select * from Item_Potion order by item_id") ;
  strcpy(query_stmt, "EXEC up_get_item_potion");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;

	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nItem Potion: ExecDirect Error ") ;
		return -1 ;
	}

	SQLNumResultCols(hStmt, &nCols) ;
	
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
		printf("\nItem7: Fetch Error ") ;
		return -1 ;
	}
		
	while(ret == SQL_SUCCESS)
	{
		// Accquire the DATA
		ret= SQLGetData(hStmt, 1, SQL_C_SLONG, &c, sizeof(int), &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nError!!! (%d)", ret) ;
			return -1 ;
		}
		CPotion[c].Item_id = c;
		ret= SQLGetData(hStmt, 2, SQL_C_CHAR, &CPotion[c].Name, sizeof(Name), &cbValue) ;
		ret= SQLGetData(hStmt, 3, SQL_C_CHAR, &CPotion[c].Han_Name, sizeof(Han_Name), &cbValue) ;
		EatRearWhiteChar(CPotion[c].Han_Name );
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}

		tmp = &CPotion[c].lv;
		for(i=4; i <= nCols; i++) {
			ret= SQLGetData(hStmt, i, SQL_C_SLONG, tmp, sizeof(int), &cbValue) ;
			tmp++ ;
		}
		c++ ;
		
		ret= SQLFetch(hStmt) ;
		m_Much  = 0;
	}
	SQLFreeStmt(hStmt, SQL_DROP) ;
	return c ;
}


int CItem_Tool::getAllData(void)
{
	if(Num_Of_CItem_Tool <= 0) {
		return -4 ; // No item's available
	}
	HSTMT hStmt= NULL ;
	RETCODE ret ;
	SWORD nCols ;
	char query_stmt[80]= {0, } ;
	SDWORD cbValue ;
	int *tmp ;
	int c= 1, i ;
	SQLAllocStmt(hDBC, &hStmt);
  /////////////////////////////////////////////////////////////////////////////
  //strcpy(query_stmt, "select * from Item_Tool order by item_id") ;
  strcpy(query_stmt, "EXEC up_get_item_tool");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;

	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nItem Tool: ExecDirect Error ") ;
		return -1 ;
	}

	SQLNumResultCols(hStmt, &nCols) ;
	
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
		printf("\nItem7: Fetch Error ") ;
		return -1 ;
	}
		
	while( ret == SQL_SUCCESS)
	{
		// Accquire the DATA
		ret= SQLGetData(hStmt, 1, SQL_C_SLONG, &c, sizeof(int), &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nError!!! (%d)", ret) ;
			return -1 ;
		}
		CTool[c].Item_id = c;
		ret= SQLGetData(hStmt, 2, SQL_C_CHAR, &CTool[c].Name, sizeof(Name), &cbValue) ;
		ret= SQLGetData(hStmt, 3, SQL_C_CHAR, &CTool[c].Han_Name, sizeof(Han_Name), &cbValue) ;
		EatRearWhiteChar( CTool[c].Han_Name );
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}

		tmp = &CTool[c].lv;
		for(i=4; i <= nCols; i++) {
			ret= SQLGetData(hStmt, i, SQL_C_SLONG, tmp, sizeof(int), &cbValue) ;
			tmp++ ;
		}
		c++ ;
		
		ret= SQLFetch(hStmt) ;
		m_Much  = 0;
	}
	SQLFreeStmt(hStmt, SQL_DROP) ;
	return c ;
}

int CItem_Weapon::getAllData(void)
{
	if(Num_Of_CItem_Weapon <= 0) {
		return -4 ; // No item's available
	}
	HSTMT hStmt= NULL ;
	RETCODE ret ;
	SWORD nCols ;
	char query_stmt[80]= {0, } ;
	SDWORD cbValue ;
	int *tmp ;
	int c= 1, i ;
	SQLAllocStmt(hDBC, &hStmt);
  /////////////////////////////////////////////////////////////////////////////
  //strcpy(query_stmt, "select * from Item_Weapon order by item_id") ;
  strcpy(query_stmt, "EXEC up_get_item_weapon");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;

	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nItem Weapon: ExecDirect Error ") ;
		return -1 ;
	}

	SQLNumResultCols(hStmt, &nCols) ;
	
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
			printf("\nItem7: Fetch Error ") ;
		return -1 ;
	}
		
	while(ret == SQL_SUCCESS)
	{
		// Accquire the DATA
		ret= SQLGetData(hStmt, 1, SQL_C_SLONG, &c, sizeof(int), &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nError!!! (%d)", ret) ;
			return -1 ;
		}
		CWeapon[c].Item_id = c;
		ret= SQLGetData(hStmt, 2, SQL_C_CHAR, &CWeapon[c].Name, sizeof(Name), &cbValue) ;
		ret= SQLGetData(hStmt, 3, SQL_C_CHAR, &CWeapon[c].Han_Name, sizeof(Han_Name), &cbValue) ;
		EatRearWhiteChar( CWeapon[c].Han_Name );
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}

		tmp = &CWeapon[c].lv;
		for(i=4; i <= nCols; i++) {
			ret= SQLGetData(hStmt, i, SQL_C_SLONG, tmp, sizeof(int), &cbValue) ;
			tmp++ ;
		}
		c++ ;
		
		ret= SQLFetch(hStmt) ;
		m_Much  = 0;
	}
	SQLFreeStmt(hStmt, SQL_DROP) ;
	return c ;
}

int CItem_Disposable::getAllData(void)
{
	if(Num_Of_CItem_Disposable <= 0) {
		return -4 ; // No item's available
	}
	HSTMT hStmt= NULL ;
	RETCODE ret ;
	SWORD nCols ;
	char query_stmt[80]= {0, } ;
	SDWORD cbValue ;
	int *tmp ;
	int c= 1, i ;
	SQLAllocStmt(hDBC, &hStmt);
  /////////////////////////////////////////////////////////////////////////////
  //strcpy(query_stmt, "select * from Item_Disposable order by item_id") ;
  strcpy(query_stmt, "EXEC up_get_item_disposable");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;

	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nItem Disposable: ExecDirect Error ") ;
		return -1 ;
	}

	SQLNumResultCols(hStmt, &nCols) ;
	
	ret= SQLFetch(hStmt) ;
	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,    NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,    0,    NULL );// Process any inserts in lpMsgBuf.
			printf("\nLast Error: %s", (LPCTSTR)lpMsgBuf) ;
			LocalFree( lpMsgBuf );
			printf("\nItem7: Fetch Error ") ;
		return -1 ;
	}
		
	while(ret == SQL_SUCCESS)
	{
		// Accquire the DATA
		ret= SQLGetData(hStmt, 1, SQL_C_SLONG, &c, sizeof(int), &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nError!!! (%d)", ret) ;
			return -1 ;
		}
		CDisposable[c].Item_id = c;
		ret= SQLGetData(hStmt, 2, SQL_C_CHAR, &CDisposable[c].Name, sizeof(Name), &cbValue) ;
		ret= SQLGetData(hStmt, 3, SQL_C_CHAR, &CDisposable[c].Han_Name, sizeof(Han_Name), &cbValue) ;
		EatRearWhiteChar( CDisposable[c].Han_Name );
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}

		tmp = &CDisposable[c].lv;
		for(i=4; i <= nCols; i++) {
			ret= SQLGetData(hStmt, i, SQL_C_SLONG, tmp, sizeof(int), &cbValue) ;
			tmp++ ;
		}
		c++ ;
		
		ret= SQLFetch(hStmt) ;
		m_Much  = 0;
	}
	SQLFreeStmt(hStmt, SQL_DROP) ;
	return c ;
}

int CItem_Armor::getAllData(void)
{
	if(Num_Of_CItem_Armor <= 0) {
		return -4 ; // No item's available
	}
	HSTMT hStmt= NULL ;
	RETCODE ret ;
	SWORD nCols ;
	char query_stmt[80]= {0, } ;
	SDWORD cbValue ;
	int *tmp ;
	int c= 1, i ;
	SQLAllocStmt(hDBC, &hStmt);
	/////////////////////////////////////////////////////////////////////////////
  //strcpy(query_stmt, "select * from Item_Armor order by item_id") ;
  strcpy(query_stmt, "EXEC up_get_item_armor");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;

	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nItem Armor: ExecDirect Error ") ;
		return -1 ;
	}

	SQLNumResultCols(hStmt, &nCols) ;
	
	ret= SQLFetch(hStmt) ;
	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) 
	{
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
			printf("\nItem7: Fetch Error ") ;
		return -1 ;
	}
		
	while(ret == SQL_SUCCESS)
	{
		// Accquire the DATA
		ret= SQLGetData(hStmt, 1, SQL_C_SLONG, &c, sizeof(int), &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nError!!! (%d)", ret) ;
			return -1 ;
		}
		CArmor[c].Item_id = c;
		ret= SQLGetData(hStmt, 2, SQL_C_CHAR, &CArmor[c].Name, sizeof(Name), &cbValue) ;
		ret= SQLGetData(hStmt, 3, SQL_C_CHAR, &CArmor[c].Han_Name, sizeof(Han_Name), &cbValue) ;
		EatRearWhiteChar( CArmor[c].Han_Name );
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}

		tmp = &CArmor[c].lv;
		for(i=4; i <= nCols; i++) {
			ret= SQLGetData(hStmt, i, SQL_C_SLONG, tmp, sizeof(int), &cbValue) ;
			tmp++ ;
		}
		c++ ;
		
		ret= SQLFetch(hStmt) ;
		m_Much  = 0;
	}
	SQLFreeStmt(hStmt, SQL_DROP) ;
	return c ;
}

int CItem_Accessory::getAllData(void)
{
	if(Num_Of_CItem_Accessory <= 0) {
		//fprintf(stdout, "\n	No item's available ") ;
		return -4 ; // No item's available
	}
	HSTMT hStmt= NULL ;
	RETCODE ret ;
	SWORD nCols ;
	char query_stmt[80]= {0, } ;
	SDWORD cbValue ;
	int *tmp ;
	int c= 1, i ;
	SQLAllocStmt(hDBC, &hStmt);
  /////////////////////////////////////////////////////////////////////////////
  //strcpy(query_stmt, "select * from Item_Accessory order by item_id") ;
  strcpy(query_stmt, "EXEC up_get_item_accessory");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;

	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nItem Accessory: ExecDirect Error ") ;
		return -1 ;
	}

	SQLNumResultCols(hStmt, &nCols) ;
	
	ret= SQLFetch(hStmt) ;
	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,    NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,    0,    NULL );// Process any inserts in lpMsgBuf.
			printf("\nLast Error: %s", (LPCTSTR)lpMsgBuf) ;
			LocalFree( lpMsgBuf );
			printf("\nItem7: Fetch Error ") ;
		return -1 ;
	}
		
	while(ret == SQL_SUCCESS)
	{
		// Accquire the DATA
		ret= SQLGetData(hStmt, 1, SQL_C_SLONG, &c, sizeof(int), &cbValue) ;
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nError!!! (%d)", ret) ;
			return -1 ;
		}
		CAccessory[c].Item_id = c;

		ret= SQLGetData(hStmt, 2, SQL_C_CHAR, &CAccessory[c].Name, sizeof(Name), &cbValue) ;
		ret= SQLGetData(hStmt, 3, SQL_C_CHAR, &CAccessory[c].Han_Name, sizeof(Han_Name), &cbValue) ;
		EatRearWhiteChar( CAccessory[c].Han_Name );
		if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
			printf("\nString GET Error!!! (%d)", ret) ;
			return -1 ;
		}
	
		tmp = &CAccessory[c].lv;
		for(i=4; i <= nCols; i++) {
			ret= SQLGetData(hStmt, i, SQL_C_SLONG, tmp, sizeof(int), &cbValue) ;
			tmp++ ;
		}
		c++ ;
		
		ret= SQLFetch(hStmt) ;
		m_Much  = 0;		// 그 아이템이 얼마나 있나 초기화 1215
	}
	SQLFreeStmt(hStmt, SQL_DROP) ;
	return c ;
}	
	
int CItem_Etc::getAllData(void)
{	
	if(Num_Of_CItem_Etc <= 0) {
		return -4 ; // No item's available
	}
	HSTMT hStmt= NULL ;
	RETCODE ret ;
	SWORD nCols ;
	char query_stmt[80]= {0, } ;
	SDWORD cbValue ;
	int *tmp ;
	int c= 1, i ;
	SQLAllocStmt(hDBC, &hStmt);
  /////////////////////////////////////////////////////////////////////////////
  //strcpy(query_stmt, "select * from Item_Etc order by item_id") ;
  strcpy(query_stmt, "EXEC up_get_item_etc");
  /////////////////////////////////////////////////////////////////////////////
	ret= SQLExecDirect(hStmt, (UCHAR *)query_stmt, SQL_NTS) ;
	
	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		printf("\nItem Etc: ExecDirect Error ") ;
		return -1 ;
	}
	
	SQLNumResultCols(hStmt, &nCols) ;
	
	ret= SQLFetch(hStmt) ;
	if(ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS) {
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,    NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,    0,    NULL );// Process any inserts in lpMsgBuf.
			printf("\nLast Error: %s", (LPCTSTR)lpMsgBuf) ;
			LocalFree( lpMsgBuf );
			printf("\nItem7: Fetch Error ") ;
		return -1 ;
	}
		
	while(ret == SQL_SUCCESS)
	{
		// Accquire the DATA
		ret= SQLGetData(hStmt, 1, SQL_C_SLONG, &c, sizeof(int), &cbValue) ;
		CEtc[c].Item_id = c;
		ret= SQLGetData(hStmt, 2, SQL_C_CHAR, &CEtc[c].Name, sizeof(Name), &cbValue) ;
		ret= SQLGetData(hStmt, 3, SQL_C_CHAR, &CEtc[c].Han_Name, sizeof(Han_Name), &cbValue) ;
		EatRearWhiteChar( CEtc[c].Han_Name );
		tmp = &CEtc[c].lv;
		for(i=4; i <= nCols; i++) {
			ret= SQLGetData(hStmt, i, SQL_C_SLONG, tmp, sizeof(int), &cbValue) ;
			tmp++ ;
		}
		c++ ;
		
		ret= SQLFetch(hStmt) ;
		m_Much  = 0;
	}
	SQLFreeStmt(hStmt, SQL_DROP) ;
	return c ;
}





// *****************************************************************************************
// *****************************************************************************************
// *****************************************************************************************
//    Item 생성 
//	  Item 생성 
// *****************************************************************************************
// *****************************************************************************************
// *****************************************************************************************

int ItemGen_successrate( t_connection c[], int cn, int type, int tableno, int itemtype, int itemno )
{
	CHARLIST *ch;

	if( cn >= LOGIN_MAX_CONNECTIONS ) return 0;
	if( cn < 0 ) return 0;

	ch = &c[cn].chrlst;
	if( ch->bAlive != ALIVE_ ) return 0;
//----------------------------------------------------  Check Variables 범위...
	return 100;
}

/*
#define IATTR_DURATION			0
#define IATTR_LIMIT				1	
#define IATTR_ATTR				2
#define IATTR_ID				3
#define IATTR_RESERVED0			4
#define IATTR_RESERVED1			5

#define IA2_HIDE			0x00000001
#define IA2_NOTMOVE			0x00000002
#define IA2_POISONED		0x00000004
#define IA2_OPENED			0x00000008
#define IA2_BROKEN			0x00000010
#define IA2_HOUSE			0x00000020
#define IA2_MAGIC			0x00000040
#define IA2_CANNOTUSE		0x00000080
#define IA2_NOIDENTIFIED	0x00000100
#define IA2_DOOR			0x00000200
#define IA2_BOX				0x00000400
#define IA2_CHAIR			0x00000800
#define IA2_TABLE			0x00001000


#define	PLANT			0
#define	MINERAL			1
#define	HERB			2
#define	COOK			3 
#define	POTION			4
#define	TOOL			5
#define	WEAPON			6
#define	DISPOSABLE		7
#define	ARMOR			8
#define	ACCESSORY		9
#define	ETC				10
#define MAP				11	
*/



unsigned int ItemGen_Duration( int type, int no )
{
	return 0;
}

unsigned int ItemGen_Limit( int type, int no )
{
	return 0;
}

unsigned int ItemGen_Attr( int type, int no )
{
	return 0;
}

unsigned int ItemGen_DbId( int type, int no )
{
	return 0;
}


#define GetAttr2( attr2, a )		((attr2) & (a))
#define SetAttr2( attr2, b )		{(attr2) |=(b);}




void RecvItemDoorOpenClose( int cn, t_item_door_open_close *p )
{
	LPITEMLIST i;
	int item_id = p->item_id;

	if( item_id < 0 ) return;
	if( item_id >= MAX_ITEM_LIST ) return;

	i = &ItemList[ item_id ];

	if( (i->attr[ IATTR_ATTR] & IA2_DOOR) == 0 ) return; // 문이 아니네...

	if( p->openclose == 0 ) // 열어주세요..
	{
		if( i->attr[ IATTR_ATTR] & IA2_OPENED ) return; // 열려 있으면 리턴.
		//
		// 여기서 connections[cn].chrslt가  열수 있는지 검사한다.
		//
		i->attr[ IATTR_ATTR] |= IA2_OPENED;

		SetArea( CHANGE_IA2_ATTR_ITEM_AREA, item_id );
	}
	else // 닫아주세요.
	{
		if( (i->attr[ IATTR_ATTR] & IA2_OPENED) == 0 ) return; // 닫혀 있으면 리턴.
		//
		// 여기서 connections[cn].chrslt가  닫을수 있는지 검사한다.
		//
		i->attr[ IATTR_ATTR] &= (~(IA2_OPENED) );

		SetArea( CHANGE_IA2_ATTR_ITEM_AREA, item_id );
	}
}


void SendItemAttrChange( t_connection c[], int cn, int id, int attr )
{	
	t_packet packet;
	
	packet.h.header.type = CMD_ITEM_ATTR_CHANGE;
	{
		packet.u.item_attr_change.item_id = id;	// ####
		packet.u.item_attr_change.array = attr;
		packet.u.item_attr_change.attr  = ItemList[id].attr[ attr];
	}
	packet.h.header.size = sizeof( item_attr_change );
	
	QueuePacket(c, cn, &packet, 1);
}	


void SendItemFoot_On_Trap0( t_connection c[], int cn, int item_id ) // ####
{	
}	
	
// 1209 KHS
void SendItemFoot_On_Trap1( t_connection c[], int cn, int item_id ) // ####
{	
}	
		
	
// 1207 KHS	
void CheckItemTimeElapsed( void )
{	
	static DWORD time;
	static int count;
	int s,e;

	
	if( g_curr_time < time )  return;
	time = g_curr_time + 3;
	
	if( count >= MAX_ITEM_LIST ) count = 0;
	s = count;
	count += ( MAX_ITEM_LIST/ 10 );
	e = count;
	if( e >= MAX_ITEM_LIST ) e = MAX_ITEM_LIST;		// 한번에 MAX_ITEM_LIST/3정도만 Check한다. 서버 부담을 줄이기 위해.
	
	for( int m = s ; m < e ; m ++)
	{
		if( ItemList[m].bAlive == 0 ) continue;
	
		unsigned int attr2 = ItemList[m].attr[ IATTR_ATTR];
		if( (attr2 & IA2_BOX) | (attr2 & IA2_DOOR) )
		{
			if( GetAttr2( attr2, IA2_BOX ) && GetAttr2( attr2, IA2_OPENED ) ) 
			{
				if( time > ItemList[m].attr[ IATTR_LIMIT] ) // 깨진뒤 얼마간의 시간이 지났다. 
				{
					ItemList[m].attr[ IATTR_ATTR] = IA2_BOX;
					SetArea( CHANGE_IA2_ATTR_ITEM_AREA, m );
					continue;
				}
			}
		}
	
		if( attr2 & IA2_FARM0 )
		{
			if( ItemList[m].attr[IATTR_DURATION] < g_curr_time )
			{
				ItemList[m].attr[IATTR_ATTR ] &= ~(IA2_FARM0);
				ItemList[m].attr[IATTR_ATTR ] |= IA2_FARM1;
				ItemList[m].attr[IATTR_DURATION ] = g_curr_time + 60;
				SetArea( CHANGE_IA2_ATTR_ITEM_AREA, m );
				SetArea( CHANGE_IA2_DURATION_ITEM_AREA, m );
			}
		}

		if( attr2 & IA2_FARM1 )
		{
			if( ItemList[m].attr[IATTR_DURATION] < g_curr_time )
			{
				ItemList[m].attr[IATTR_ATTR ] &= ~(IA2_FARM1);
				ItemList[m].attr[IATTR_ATTR ] |= IA2_FARM2;
				ItemList[m].attr[IATTR_DURATION ] = g_curr_time + 60;
				SetArea( CHANGE_IA2_ATTR_ITEM_AREA, m );
				SetArea( CHANGE_IA2_DURATION_ITEM_AREA, m );
			}
		}

		if( attr2 & IA2_FARM2 )
		{
			if( ItemList[m].attr[IATTR_DURATION] < g_curr_time )
			{
				ItemList[m].attr[IATTR_ATTR ] &= ~(IA2_FARM2);
				ItemList[m].attr[IATTR_ATTR ] |= IA2_FARM3;
				ItemList[m].attr[IATTR_DURATION ] = g_curr_time + 60;
				SetArea( CHANGE_IA2_ATTR_ITEM_AREA, m );
				SetArea( CHANGE_IA2_DURATION_ITEM_AREA, m );
			}
		}

		if( attr2 & IA2_FARM2 )
		{
			if( ItemList[m].attr[IATTR_DURATION] < g_curr_time )
			{
				ItemList[m].attr[IATTR_ATTR ] &= ~(IA2_FARM2);
				ItemList[m].attr[IATTR_ATTR ] |= IA2_FARM3;
				ItemList[m].attr[IATTR_DURATION ] = g_curr_time + 60;
				SetArea( CHANGE_IA2_ATTR_ITEM_AREA, m );
				SetArea( CHANGE_IA2_DURATION_ITEM_AREA, m );
			}
		}

		if( attr2 & IA2_FARM3 )
		{
			if( ItemList[m].attr[IATTR_DURATION] < g_curr_time )
			{
				ItemList[m].attr[IATTR_ATTR ] &= ~(IA2_FARM3);
				ItemList[m].attr[IATTR_ATTR ] |= IA2_FARM4;
				ItemList[m].attr[IATTR_DURATION ] = g_curr_time + 60;
				SetArea( CHANGE_IA2_ATTR_ITEM_AREA, m );
				SetArea( CHANGE_IA2_DURATION_ITEM_AREA, m );
			}
		}


		if( attr2 & IA2_FIRE )
		{
			if( ItemList[m].attr[IATTR_DURATION] < g_curr_time )
			{
				ItemList[m].bAlive = REMOVE_;
				SetArea( REMOVE_ITEM_AREA, m );
			}
		}
	}
}





//-----------------------------------------------------------------------
// 아이템 생성 함수 ( 10/24 )
//-----------------------------------------------------------------------
/*
DWORD ItemAttr_Make_First( int type, int itemno, int success_rate )
{
	switch( type )
	{
		case	PLANT			:	return global_time + (21600 * 60);
		case	MINERAL			:
		case	HERB			:	
		case	COOK			:	return global_time + (21600 * 60);
		case	POTION			:
		case	TOOL			:	
		case	WEAPON			:
		case	DISPOSABLE		:
		case	ARMOR			:
		case	ACCESSORY		:
		case	ETC				:
		break;
	}
	return 0L;
}
*/



//////////////////////////////////////////////////////////////////////////
// 캐릭터 인벤토리에서 빈곳 찾기, 없으면 0을 리턴

int SearchInv( ItemAttr inv[3][3][8], int &a, int &b, int &c )
{
	for( a=0; a<3; a++)
	for( b=0; b<3; b++)
	for( c=0; c<8; c++)
	{
		if( !inv[a][b][c].item_no )
			return 1;
	}

	return 0;	
}

int SearchInv_invert( ItemAttr inv[3][3][8], int &a, int &b, int &c )
{
	for( a=2; a >=0; a--)
	for( b=2; a >=0; b--)
	for( c=7; c >=0; c--)
	{
		if( !inv[a][b][c].item_no )
			return 1;
	}

	return 0;	
}

/////////////////////////////////// //0101 //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//	아이템 번호와 타입이 허용된 값을 넘었는지를 판단하는 함수
//
//		파라메터는 타입과 번호를 입력 받고
//		포인터로 리턴한다.	잘 못 됐을 경우 NULL리턴
//
////////////////////////////////////////////////////////////////////////////////
void getItemIndex(int item_no, int &type, int &index)		// 0415_2	// 위치를 바꿈
{
	type= item_no / 1000 ;
	index= item_no % 1000 ;
}

CItem *ItemUnit( ItemAttr item )		// 0415_2
{
	int type, num;
	getItemIndex( item.item_no, type, num );
	return ItemUnit( type, num );
}

CItem *ItemUnit( int item_no )
{
	return ItemUnit( item_no/1000, item_no%1000);
}

CItem *ItemUnit( int type, int item_no )
{
	if( (type<0) || (type>10) ) return NULL;
	if( (item_no<=0) || (item_no > Item_Ref.nItem[type]) ) return NULL;

	switch( type )
	{
		case 	PLANT		:	return &CPlant		[item_no];	break;
		case 	MINERAL		:	return &CMineral	[item_no];	break;
		case 	HERB		:	return &CHerb		[item_no];	break;
		case 	COOK		:	return &CCook		[item_no];	break;
		case 	POTION		:	return &CPotion		[item_no];	break;
		case 	TOOL		:	return &CTool		[item_no];	break;
		case 	WEAPON		:	return &CWeapon		[item_no];	break;
		case 	DISPOSABLE	:	return &CDisposable	[item_no];	break;
		case 	ARMOR		:	return &CArmor		[item_no];	break;
		case 	ACCESSORY	:	return &CAccessory	[item_no];	break;
		case 	ETC			:	return &CEtc		[item_no];	break;
	}
	return NULL;
//	return Item_Ref.Item_Info[type][item_no];
}



///////////////////////////////////////////////
// 장착 이미지를 가져온다
/////////////////////////////////////////////////
int GetItemView( int item_no, int is_man )
{
	CItem *t;
	int type, num;
	getItemIndex( item_no, type, num );
	
	t = ItemUnit( type, num );
	if( !t ) return 0;
	else return t->GetItemShow( is_man );
}

ItemAttr GenerateItem( const int item_no, DWORD dur)
{
	ItemAttr item = {0, };
	CItem *t = ItemUnit( item_no );
	if( !t ) {return item;}
	if(!t->GetItemImage() || !t->GetObjectNumber()){return item;}//오브젝트 이미지 넘버 없으면 지워짐

	item.item_no = item_no;
	
	if( !dur ) 
	{
		item.attr[IATTR_DURATION] = CreateItemDuration( item_no/1000 , item_no%1000 );
	}
	else
	{
		if( t->GetRbutton() == DIVIDE_ITEM ) 
		{
			item.attr[IATTR_DURATION] = dur;
		}
		else 
		{
			item.attr[IATTR_DURATION] = MAKELONG( dur, dur );
		}
	}
	item.attr[IATTR_LIMIT] = g_curr_time;

	return item;
}

SItemchange itemchange[MAX_CHANGE_ITEM_COUNT];//010708 lsw
int ichangeItemCount=0;
int LoadChangeItem()//010708 lsw
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;

	SQLAllocStmt(hDBC, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)"Select * from item_change order by original", SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{		
		int i = 0;
		retCode = SQLFetch(hStmt);
		while( retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		{
			if(i >= MAX_CHANGE_ITEM_COUNT)//020730 lsw
			{
				SQLFreeStmt(hStmt, SQL_DROP);
				return 0;
			}

			retCode = SQLGetData(hStmt, 1, SQL_C_LONG,	&itemchange[i].origin_item_no		, 0, &cbValue);
			retCode = SQLGetData(hStmt, 2, SQL_C_LONG,	&itemchange[i].will_change_item_no	, 0, &cbValue);
			retCode = SQLGetData(hStmt, 3, SQL_C_LONG,	&itemchange[i].add_soksung			, 0, &cbValue);
			retCode = SQLGetData(hStmt, 4, SQL_C_LONG,	&itemchange[i].add_grade			, 0, &cbValue);
			
			ichangeItemCount=i;			
			i++;

			retCode = SQLFetch(hStmt);
			if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
			{
			}
			else if( retCode == SQL_NO_DATA ) 
			{
				break;
			}
			else
			{
				SQLFreeStmt(hStmt, SQL_DROP);
				return 0;
			}
		}	
	}		


	SQLFreeStmt(hStmt, SQL_DROP);		// 0308 YGI
	return(1);
}




