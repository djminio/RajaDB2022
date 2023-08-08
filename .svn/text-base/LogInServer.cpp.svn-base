// LogInServer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Main.h"
#include "Debug.h"
#include <MmSystem.h>



/////////////////////////////////////////////////////////////////////////////////////////////////////


void SendPbs( char *temp )
{
	t_packet p;
	int len;
	

	if( temp == NULL )return;
	if( *temp == 0 ) return;

	len = strlen( temp );

	p.h.header.type = CMD_LOGIN_BBS;
		strcpy( p.u.login_bbs.bbs, temp );
	p.h.header.size = sizeof( t_login_bbs ) - MAX_PATH + len;

	for(  int i = 0 ; i < LOGIN_MAX_CONNECTIONS ; i ++)
	{
		if( connections[i].server_check )
		{
			QueuePacket( connections, i, &p, 1 );
		}
	}
}


