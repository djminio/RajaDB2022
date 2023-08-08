#include "StdAfx.h"

#include "MAIN.H"

#define _ID_CPP_
#include "Id.h"


#include "ServerTable.h"


typedef struct IdCertificate
{
	int     mapport;
	char	id[ ID_LENGTH];
	int		delay;
}t_IdCertificate;
	
	
t_IdCertificate *IdC;
	
// port가 5000번일때만 인증서버의 기능을 처리한다. 
void InitIDCertificate( int port )
{		
	if( port != CERTIFICATE_SERVER_PORT ) return;
	
	IdC = ( t_IdCertificate *)malloc( MAX_ID_IN_GAME  * sizeof( t_IdCertificate ) );
}	
	
void EndIDCertificate( void )
{
	if( IdC )	free( IdC );
}

void InsertIdC( char *id )
{
}

void DeleteIdC( char *id )
{
}


////////////////////////////////////////////////////////////////////////////
bool SendRemoveUserToAgent( char *szID, WORD wPort, DWORD dwID )
{	
	char szMsg[128+1];
	t_packet *p = (t_packet*)(szMsg+1+4);
	int len;
	
	if( (szID == NULL) || (*szID == 0) || ((len = strlen( szID )) <= 0) )
		return false;
	
	szMsg[0] = (BYTE)PTCL_DB_ANSWER;
	memcpy( szMsg+1, &dwID, sizeof(DWORD) );
	
	p->h.header.type = CMD_CLOSE_LOGIN_ID;
	strcpy( p->u.login_close_login_id.id, strupr(szID) );
	
	p->h.header.size = sizeof( t_login_close_login_id );

	return g_pServerTable->Send( wPort, szMsg, sizeof(PTCL)+sizeof(DWORD)+sizeof(t_header)+p->h.header.size );
}














