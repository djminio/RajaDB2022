#include "StdAfx.h"
//#include <Windows.h>
#include <Stdio.h>
#include <MmSystem.h>
#include "Direct.h"


#define __HONG_SUB_H__
#include "Hong_Sub.h"




//////////////////////////////////////////////////////////////////////
//
//   User Variables...
//
int debug_makemode;
int debug_pc_neverdie; 


/////////////////////////////////////////////////////////////////////
//
//  User Functions...
//

int InitGameMakeModeSetting( char *filename )
{	
	debug_makemode = GetPrivateProfileInt( "debug", "makemode", 0, filename );
	debug_pc_neverdie = GetPrivateProfileInt( "debug", "pc_neverdie", 0, filename );
	
	return 1;
}




char* EatRearWhiteChar( char* pStr )
{	
	char*	szWhite = " \t\n\r";
	char*	pRear;
	
	pRear = pStr + strlen( pStr ) - 1;
	if ( pRear )
	{
		while ( pStr <= pRear )
		{
			if ( strchr( szWhite, *pRear ) )
			{
				*pRear-- = 0;
			}
			else
			{
				break;
			}
		}
	}
	
	return	pStr;
}	



int writedebug;


void Debug( char *s, ... )
{	
    char temp[ 1000]={0,};
    va_list arg;
    va_start( arg, s );
    vsprintf( (char *)temp, s, arg );
    va_end( arg );
	
//	if( !writedebug ) return;
	
	FILE *fp = fopen( "./login_server_check_time.txt", "at+" );
	if( fp )
	{
		fprintf( fp, "%s", temp );
		fclose(fp);
	}
	
	OutputDebugString( temp );
}	



int ViewCheckRoutine( int t )
{
	static int TimeCheckCount;
	static int TickCount, OldTickCount, TickFlag;
	static int currentfps;
	
	if( t == 0 ) TickFlag = 0;
	if( TickFlag == 0 )	{	OldTickCount = TickCount = timeGetTime();	TickFlag = 1; 	}
	else
	{
		OldTickCount= TickCount;
		TickCount	= timeGetTime();
		
	}
	char temp[ FILENAME_MAX];
	sprintf( temp, "%d : %d \n", t, TickCount - OldTickCount );
	OutputDebugString( temp );

//	if( TickCount - OldTickCount )
//	if ( t == 9999 )
//	{
//		FILE *fp = fopen( "000_check_time.txt", "at+" );
//		if( fp ) 
//		{
//			fprintf( fp, temp );
//			fclose(fp);
//		}
//	}

	return TickCount - OldTickCount;
}					


void JustMsg( char *s, ... )
{	
    char temp[ FILENAME_MAX];
    va_list arg;
    va_start( arg, s );
    vsprintf( temp, s, arg );
    va_end( arg );
	HWND hwnd = GetActiveWindow();
	
	MessageBox( hwnd, temp, "Information", MB_OK | MB_ICONINFORMATION );
}	


void ErrMsg( char *s, ... )
{	
    char temp[ FILENAME_MAX];
    va_list arg;
    va_start( arg, s );
    vsprintf( temp, s, arg );
    va_end( arg );
	HWND hwnd = GetActiveWindow();
	
	MessageBox( hwnd, temp, "Error", MB_OK | MB_ICONSTOP  );
}	

int YesOrNo( char *s, char *title )
{	
    char temp[ FILENAME_MAX];
    va_list arg;
    va_start( arg, s );
    vsprintf( temp, s, arg );
    va_end( arg );
	
	HWND hwnd = GetActiveWindow();
	return MessageBox( hwnd, temp, title, MB_YESNO | MB_ICONQUESTION );
}	



// 오늘 접속한 사람들의 모임 
void Log_LogIn( int mon, int day, int hour, int min, int sec, char *id )
{	
/*	Finito - Old code shown below
	char temp[ FILENAME_MAX];
	char dir[ FILENAME_MAX];
	FILE *fp;
	int c;

	// 010322 KHS
	return;
	
	sprintf( dir, "Connected IDs at %02d.%02d", mon, day );

	sprintf( temp, "%s/%s.txt", dir, id );
		
	c = 0;
		
AGAIN_:	

	fp = fopen( temp, "at+" );
	if( fp == NULL )
	{	
		if( c == 0 ) // 처음 들어왔다. 
		{
			_mkdir( dir );
			c = 1;
			goto AGAIN_;
		}
		else
		{
			return;
		}
	}

	fprintf( fp, "%02d.%02d  %02d:%02d:%02d  Latest Access.\n", mon, day, hour, min,sec );

	fclose(fp);
*/
}





