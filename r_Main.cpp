#include "StdAfx.h"
#define __MAIN_H__
#include "MAIN.H"
#include "SealStone.h"
#include "MyLog.h"
#include <MMSystem.h>
#include "ChrLog.h"
#include "CItem.h"//010708 lsw 
#include "network.h"
#include "LottoDBMgr.h"//soto-030505
#include "ShopDemon.h"

SOCKET lsock = 0;
struct sockaddr_in laddr;

DWORD global_time		= 0;
DWORD g_start_time		= 0;
DWORD g_alive_time		= 0;
DWORD g_curr_time		= 0;

int g_total_gameserver, g_current_gameserver;	// 현재 접속된 게임서버의 수..
int g_gameserver_check_start; // 1되면 게임서버수를 Check하기 시작한다. 
int g_closed_gameserver;
int g_year				= 0;
int g_mon				= 0;
int g_yday				= 0;
int g_day				= 0;
int g_hour				= -1;
int g_min				= 0;
int g_sec				= 0;
int g_OldDay			= 0;
int g_wday				= 0;//020410 lsw
int g_count_ok;
int		GameServerVersion;
int     StartMap, StartPosition;
// 010221_3 YGI
//020822 lsw
char	StartMapPosition[ 5][20][20] = {	{ "", "k_sung2","ma-in", "Source",  "Gray",  "color","bis_i", "Renes_c", "","iramus","dep","SCHOLIUM", "tynen", "barantan","SCHOLIUM2", },	// 헾턴트....
{ "", "k_sung2","ma-in", "Source",  "Gray",  "color","bis_i", "Renes_c", "","iramus","dep","SCHOLIUM", "tynen", "barantan","SCHOLIUM2", },	// 헾턴트....		// 010414 YGI
{ "", "k_sung2","ma-in", "Hu_Vm",  "Gray",  "color","","Renes_c", },	// 헾턴트....
{ "", "k_sung2","ma-in", "source", "ma-in", "ma-in","","ma-in", },};



extern HWND g_hWnd;

extern int initItem(void) ;

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------

void prepare(t_connection c[])
{
	global_time = ::timeGetTime();
	
	time_t lTime = {0,};
	time(&lTime);
	struct tm *today = localtime(&lTime);
	
	g_year = today->tm_year + 1900;
	g_mon  = today->tm_mon;
	g_yday = today->tm_yday;
	g_wday = today->tm_wday;
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
	
	g_curr_time = ( (g_year-1999 ) * 31536000) 
		+ (g_yday* 86400) 
		+ (g_hour* 3600) 
		+ (g_min * 60) 
		+ g_sec;
}
//---------------------------------------------------------------------------------
// 020808 YGI
struct ID_PASS
{
	char m_szID1[30];		// dragon id
	char m_szPASS1[30];
	char m_szID2[30];		// totaldb id
	char m_szPASS2[30];
	char m_szID3[30];		// chrlogdb id
	char m_szPASS3[30];
	
	ID_PASS()
	{
		m_szID1[0] = 0;
		m_szPASS1[0] = 0;
		m_szID2[0] = 0;
		m_szPASS2[0] = 0;
		m_szID3[0] = 0;
		m_szPASS3[0] = 0;
	}
};
#include "hsel.h"
bool DecoadFile( char *filename, void *pData, int size )
{
	CHSEL_STREAM m_hsel;
	FILE *fp = fopen( filename, "rb" );
	if( !fp ) return false;
	
	int nVersion = 0;
	fread( (void*)(&nVersion), sizeof(int), 1, fp ); 
	if (m_hsel.GetVersion() != nVersion)  return false;
	HselInit deinit;
	fread( (void*)(&deinit), sizeof(HselInit), 1, fp );
	if (!m_hsel.Initial(deinit))  return false;
	fread( pData, 1, size, fp );
	m_hsel.Decrypt((char *)pData, size);
	fclose( fp );
	return true;
}
bool IncordFile( char *filename, void *pData, int size )
{
	CHSEL_STREAM m_hsel;
	FILE *fp = fopen( filename, "wb" );
	if( !fp ) return false;
	
	HselInit eninit;
	eninit.iEncryptType	=	HSEL_ENCRYPTTYPE_RAND;
	eninit.iDesCount	=	HSEL_DES_TRIPLE;
	eninit.iCustomize	=	HSEL_KEY_TYPE_DEFAULT;
	eninit.iSwapFlag	=	HSEL_SWAP_FLAG_ON;
	
	if (!m_hsel.Initial(eninit)) 
	{
		return false;
	}
	
	HselInit deinit;
	deinit = m_hsel.GetHSELCustomizeOption();
	const int nVersion = m_hsel.GetVersion();
	fwrite((void *)(&nVersion), sizeof(nVersion), 1, fp ); 
	fwrite((void *)(&deinit), sizeof(HselInit), 1, fp ); 
	m_hsel.Encrypt((char*)pData, size);
	fwrite( pData, 1, size, fp );
	fclose( fp );
	return true;
}
//---------------------------------------------------------------------------------

// 020808 YGI - 주의사항 참조
int init_login_main( void )
{
	char path[MAX_PATH];
	ID_PASS id_password;
	int bIdPassword = 0;		// 정확히 암호를 읽어 왔는가?
	int size = GetPrivateProfileString( "option", "path", "", path, 50, DB_DEMON_INI_ );//021007 lsw
	if( size )
	{
		sprintf( path, "%s/data/IdPassword.bin", path );
		
		bIdPassword = DecoadFile( path, (char *)&id_password, sizeof( ID_PASS ) );
	}
	
	ID_PASS IdPassWord;
	strcpy( IdPassWord.m_szID1,		LocalMgr.GetDBAccount(DRAGON_DB,ID));
	strcpy( IdPassWord.m_szPASS1,	LocalMgr.GetDBAccount(DRAGON_DB,PASS) );
	strcpy( IdPassWord.m_szID2,		LocalMgr.GetDBAccount(TOTAL_DB,ID) );
	strcpy( IdPassWord.m_szPASS2,	LocalMgr.GetDBAccount(TOTAL_DB,PASS) );
	strcpy( IdPassWord.m_szID3,		LocalMgr.GetDBAccount(CHRLOG_DB,ID) );
	strcpy( IdPassWord.m_szPASS3,	LocalMgr.GetDBAccount(CHRLOG_DB,PASS) );
		
	if( bIdPassword )
		IdPassWord = id_password;
	
	if( (Init_SQL("DragonRajaDB", IdPassWord.m_szID1, IdPassWord.m_szPASS1) ) == 0)
	{
		ErrMsg( "'DragonRajaDB' Table Initializing Fail !" );
		return(-1);
	}
	MyLog( LOG_NORMAL, "SQL server( DragonDB ) connect OK!");
	
	if( (Init_TotalDB_SQL( "TotalDB", IdPassWord.m_szID2, IdPassWord.m_szPASS2) ) == 0 ) 
	{
		ErrMsg( "'TotalDB' Table Initializing Fail !" );
		return(-1);
	}
	MyLog( LOG_NORMAL, "SQL server( Total DB ) connect OK!");
	
	if( (Init_ChrLogDB_SQL( "ChrLogDB", IdPassWord.m_szID3, IdPassWord.m_szPASS3) ) == 0 ) 
	{
		ErrMsg( "'ChrLogDB' Table Initializing Fail !" );
		return(-1);
	}
	/*
	if( (Init_SQL("DragonRajaDB", "dragonraja", "cisco677") ) == 0)
	{
		ErrMsg( "'DragonRajaDB' Table Initializing Fail !" );
		return(-1);
	}
	MyLog( LOG_NORMAL, "SQL server( DragonDB ) connect OK!");
	
	if( (Init_TotalDB_SQL( "TotalDB", "dragonraja", "cisco677") ) == 0 ) 
	{
		ErrMsg( "'TotalDB' Table Initializing Fail !" );
		return(-1);
	}
	MyLog( LOG_NORMAL, "SQL server( Total DB ) connect OK!");
	
	if( (Init_ChrLogDB_SQL( "ChrLogDB", "dragonraja", "cisco677") ) == 0 ) 
	{
		ErrMsg( "'ChrLogDB' Table Initializing Fail !" );
		return(-1);
	}

	MyLog( LOG_NORMAL, "SQL server( ChrLogDB ) connect OK!");
*/
	if(LocalMgr.IsAbleNation(JAPAN))
	{
		if((Init_NGCDB_SQL( "NgcDB", "terradragon", "xpfkemforhs"))  == 0 )
		{
			ErrMsg( "'NGCDB' Table Initializing Fail !" );
			return(-1);
		}
		MyLog( LOG_NORMAL, "SQL server( NGCB ) connect OK!");
	}	
	
	InitHackingLog();
	InitRareItemMakeResultLog();
	InitAccountLock();
	InitBanlist();
	LoadNoName_SQL();		// 010117 YGI
	InitItemList();
	
	CShopDemon::Create(); // soto-HK-030931
	CLottoDBMgr::Create();

	auto hDBC_ = hDBC;

	LottoDBMgr()->LoadTable(hDBC);
	
	if(initItem() < 0) 	
	{	
		ErrMsg( "'initItem()' Fail !" );return(-2);
	}
	
	hDBC = hDBC_;

	if( LoadChangeItem() != 1 )
	{	
		ErrMsg( "'LoadChangeItem()' Fail !" );return(-2);
	}
	if(!LoadEventRareItem())//020815-2 lsw
	{
		ErrMsg( "'LoadEventRareItem()' Fail !" );return(-2);
	}
	
	if	(LoadNPCLevTable() < 0)
	{	//< CSD-030306
		ErrMsg("'LoadNPCLevTable()' Fail !");
		return(-2);
	}	//> CSD-030306
				
	// 001126 KHS
	GetMapInfo( MapInfo );		
	memset(connections,0,sizeof(t_connection)*LOGIN_MAX_CONNECTIONS);
	
	if( !CheckWorstDBTable() )	// 010322 KHS
	{	
		return -1;
	}	
	
	return 0;
}		

//---------------------------------------------------------------------------------
