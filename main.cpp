#include "stdafx.h"
#include "network_base.h"
#include "monitor.h"
#include "mainheader.h"
#include "servertable.h"
#include "servertable2.h"
#include "MyLog.h"
#include "network.h"
#include "LottoDBMgr.h"//soto-030505
#include "ShopDemon.h"//soto-HK-030921
#include "DragonLoginserver2.h"
				
//2001/02/19 zhh
//2001/01/29 zhh
#include <afx.h>
#include "Main.h" 
#include <process.h>

			
bool g_bTaiwanMainOn = true;		// 한국이회의 프로그램에서 종료시킬때 false 한다.
void diethread(void *a);
HANDLE hIn;
#include "./China/QueryDBSocket.h"
extern int Sendz(char* msg,int len);
extern int InitAsync( void );
extern CQueryDBSocket *ConQ;
extern void CloseForChina();
//acer7
extern int ReleaseAsync();


//acer7
void ProcessEnd(const int iDestroyType)
{
	g_pServerTable->DestroyServer( iDestroyType );
	MyLog( LOG_NORMAL, "-- DBDemon ShutDown :: Now Release INetwork Module, ServerTable" );
	// acer7
	exit( 0 );
}

bool InitDynamicData()
{	//< CSD-040127
	char szNationName[100] = {0,} ;
	if( GetPrivateProfileString( "nation_set", "nation_name", "" , szNationName, 50,DB_DEMON_INI_ ) )
	{
		const bool bIsFree = static_cast<bool>(GetPrivateProfileInt( "NATION_SET", "BETA_SERVER", 0, DB_DEMON_INI_ ));
		if(!LocalMgr.InitVersion(szNationName,bIsFree)){return false;}
	}
	else
	{
		MyLog(0,"Nation_Set Data Fault!!");
		return false;
	}
	
	char szFreeLevel[50] = {0, };

	if (GetPrivateProfileString("option", "FREE_LEVEL", "" , szFreeLevel, 50, DB_DEMON_INI_) > 0)
	{
		FREE_LEVEL_ = atoi(szFreeLevel);
	}

	LocalMgr.SetRookieLv( GetPrivateProfileInt("NATION_SET", "RookieAbleLevel", 0, DB_DEMON_INI_ ) );//021230 Rookie Server
	LocalMgr.SetDoubtUserTableLimitDay( GetPrivateProfileInt("NATION_SET", "DoubtUserTableLimitDay", 60, DB_DEMON_INI_ ) );//021230 Rookie Server
	return true;
}	//> CSD-040127

TKeinMap< CGuildMarkImage > g_GuildMarkImage;

int main()
{		
	INPUT_RECORD	irBuffer;
	memset(&irBuffer,0,sizeof(INPUT_RECORD));
	DWORD	dwResult;
	EXCEPTION_POINTERS* pException = NULL;//020508 lsw

	AllocConsole();
	
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	g_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetMonitorSize( SCREEN_TEXT_SIZE_X, SCREEN_TEXT_SIZE_Y );
	
	InitMyLog();
	
	MyLog( LOG_NORMAL, "Initialize DRAGON RAJA DB Server Datas ...... OK!" );

//<soto-030828
	if(!InitDynamicData())
	{
		MyLog(0,"InitDynamicData Fault!!");
		return false;
	}

/*
	char szNationName[100] = {0,} ;
	if( GetPrivateProfileString( "nation_set", "nation_name", "" , szNationName, 50,DB_DEMON_INI_ ) )
	{
		const bool bIsFree = (bool)GetPrivateProfileInt( "NATION_SET", "BETA_SERVER", 0, DB_DEMON_INI_ );
		if(!LocalMgr.InitVersion(szNationName,bIsFree)){return false;}
		if(!InitDynamicData())
		{
			MyLog(0,"Nation_Set Data Fault!!");
			return false;
		}
		
	}
	else
	{
		MyLog(0,"Nation_Set Data Fault!!");
		return false;
	}
*/
//>soto-030828
	InitDBDemon();
	
	if (init_login_main() != 0)
	{		
		MyLog( LOG_FATAL, "init_login_main() Failed.....!" );
		goto ServerStartFailed;
	}
	
	g_pINet->ResumeTimer( 0 );
	
	__try//020508 lsw
	{	
		if(LocalMgr.IsAbleNation(TAIWAN|CHINA|HONGKONG))//021007 lsw
		{
			InitAsync();

			_beginthread( diethread, 0, NULL );
			
			MSG msg;
			while( GetMessage(&msg,NULL,0,0) )
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			while (g_pServerTable->IsServerRunning())
			{
				ReadConsoleInput(hIn,&irBuffer,1,&dwResult);
				
				if (irBuffer.EventType == KEY_EVENT)
				{
					if (irBuffer.Event.KeyEvent.bKeyDown)
					{	
						switch(irBuffer.Event.KeyEvent.wVirtualKeyCode)
						{
						case VK_ESCAPE:
							{
								if( IDYES == MessageBox( NULL, "Are you sure to DESTROY this DB Demon?", "DB Demon", MB_YESNO ) )
								{
									MyLog( LOG_IMPORTANT, "<<<<<<<  DB Demon is Closing  >>>>>>" );
									g_pServerTable->DestroyServer( FINISH_TYPE_NORMAL );
								}
							}break;
						case VK_F1:
							{
								// 021118 YGI
								//extern void CheckCrash();
								//CheckCrash();
								SetEvent( hKeyEvent );
							}break;
						case VK_F5://030102 lsw
							{
								if( IDYES == ::MessageBox( NULL,	"ReSetData", "Re-Load Data", MB_YESNO ) )
								{
									InitDynamicData();
									MyLog( LOG_IMPORTANT, "------ReSetData OK------" );
								}								
							}break;
						default:
							{
							}break;
						}
					}	
				}
			}
			goto __FREE;
		}
	}
	__except(reinterpret_cast<int>(pException = GetExceptionInformation()))//020508 lsw
	{
		DumpException( pException, "Exception Raised on main()" );
		goto __ErrorExit;
	}
ServerStartFailed:
	{
		ProcessEnd(FINISH_TYPE_NORMAL);
		goto __FREE;
	}
	return 0;
__ErrorExit:
	{
		ProcessEnd(FINISH_TYPE_UNKNOWN_ERROR);
		goto __FREE;
	}
	return 0;
__FREE:
	{
		CloseForChina();
		
		::Release_SQL();
		::Release_TotalDB_SQL();
		::Release_ChrLogDB_SQL();

		CLottoDBMgr::Destroy();
		CShopDemon::Destroy();//soto-031112
		
		if(LocalMgr.IsAbleNation(JAPAN))
		{
			::Release_NGCDB_SQL();
		}

		//acer
		ReleaseAsync();

		MyLog( LOG_NORMAL, "-- DBDemon ShutDown :: Now Release SQL" );
		MyLog( LOG_NORMAL, "-- DBDemon Shutdown :: Now Release Console and Log Resources" );

		//acer7 -----------------
		EndDBDemon();//020730 lsw

		FreeMyLog();
		FreeConsole();
		// --------------------------
	}
	return 0;
}	

INPUT_RECORD	irBuffer;
extern void SendQuit();
void diethread( void *TEMP )//020901 lsw
{	
	while (g_pServerTable->IsServerRunning())
	{
		DWORD dwResult;
		ReadConsoleInput(hIn,&irBuffer,1,&dwResult);		
		if (irBuffer.EventType == KEY_EVENT)
		{		
			if (irBuffer.Event.KeyEvent.bKeyDown)
			{	
				switch(irBuffer.Event.KeyEvent.wVirtualKeyCode)
				{
				case VK_ESCAPE:
					{
						if( MessageBox( NULL, "Are you sure to DESTROY this DB Demon?", "DB Demon", MB_YESNO ) == IDYES )
						MyLog( LOG_IMPORTANT, "<<<<<<<  DB Demon is Closing  >>>>>>" );
					//	g_pServerTable->DestroyServer( FINISH_TYPE_NORMAL );
						SendQuit();
					}break;
				case VK_F1:
					{
						SetEvent( hKeyEvent );
					}break;
				case VK_F9:
					{
						InitAsync();
					}
				default:
					{
					}break;
				}
			}
		}
	}
}
