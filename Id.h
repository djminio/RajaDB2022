

#define MAX_ID_IN_GAME				10000

#define CERTIFICATE_SERVER_PORT		 5000	

#ifndef __ID_CPP__
#define __ID_CPP__


	extern void InitIDCertificate( void );

	extern bool SendRemoveUserToAgent( char *szID, WORD wPort, DWORD dwID );


#else




#endif
