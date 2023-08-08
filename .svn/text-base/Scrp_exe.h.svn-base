

#define _SCRIPT_VARABLE_POINT_      300

#define _SCRIPT_FUNCTION_POINT_     150

#define MAX_STRING_					512



#define EVENT_TYPE_NPC			0
#define EVENT_TYPE_MAPTILE		1

#define SCRIPT_START_SETTING		0
#define SCRIPT_BULLETIN_BOARD		1


#define EVENT_SYSTEM_FUNCTION_TOTAL		10
#define EVENT_NPC_FUNCTION_TOTAL		30


#define EVENT_SYSTEM_FUNCTION_START		0
#define EVENT_NPC_FUCTION_START			( EVENT_SYSTEM_FUNCTION_TOTAL)
#define EVENT_MAPTILE_FUCTION_START		( EVENT_SYSTEM_FUNCTION_TOTAL+EVENT_NPC_FUNCTION_TOTAL)



#define sYES					(var[EventPC][0])
#define sRECALL_SCRP_NO			(var[EventPC][1])
#define sRECALL_CURTIME			(var[EventPC][2])
#define sRECALL_AFTTIME			(var[EventPC][3])
#define sRECALL_SCRIPT_COUNT	(var[EventPC][4])




#ifndef __SCRP_EXE_H__
#define __SCRP_EXE_H__

extern void (*SFunction[ _SCRIPT_FUNCTION_POINT_ ])( void );
extern int var[ DRAGON_MAX_CONNECTIONS][ _SCRIPT_VARABLE_POINT_ ];
extern int EventPC, EventNPC;



extern void ReCallScript( void );





#else


#endif




