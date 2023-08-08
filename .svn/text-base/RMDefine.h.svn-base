#pragma once

#define MSG_SHUT_DOWN				100	//ShutDown
#define MSG_RELOAD_GAMESERVER_DATA  101 //Reload Gameserver data
#define MSG_CHANGE_WEATHER			102
#define MSG_ECHO					103


#pragma pack (push,1)
struct PACKET_SHUT_DOWN
{
	BYTE bPtcl;
	BYTE bHeader;
};


struct PACKET_RELOAD_GAMESERVER_DATA
{
	BYTE bPtcl;
	BYTE bHeader;
};

struct PACKET_CHANGE_WEATHER
{
	BYTE bPtcl;
	BYTE bHeader;
	BYTE bWeather;
	BYTE bStopWeather;
	DWORD dwAmount;
};



#pragma pack(pop)