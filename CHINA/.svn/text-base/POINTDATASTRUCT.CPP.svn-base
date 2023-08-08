
#include "..\stdafx.h"
#include "PointdataStruct.h"

#include "..\monitor.h"

void DebugPrintf(const char *fmt, ...)
{
	va_list args;
	FILE *stream;
	
#ifndef DEBUGMODE
        return;
#endif
	
	va_start(args, fmt);	

	stream = fopen("dll.log","a+");
    if( stream ) 
	{
	    vfprintf(stream, fmt, args);
		va_end( args );
		fputc('\n',stream);
		fclose(stream);
	}
}