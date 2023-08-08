/*
	-	1998/??/??	Created by canical
*/


#define	VILLAGE_SIZE				540
#define TILE_SIZE					32


#ifndef	__MAP_H__
#define	__MAP_H__


#pragma	pack	(push, 1 )

#define TILE_MAX_   3600

/*
typedef struct	tagTILE
{
	DWORD	back			: 12;
	DWORD	front			: 12;
	DWORD	fronttype		:  1;
	DWORD	rooftype		:  1;
	DWORD	attr_dont		:  1;
	DWORD	attr_map		:  1;
	DWORD	attr_roof		:  1;
	DWORD	attr_door		:  1;
	DWORD	attr_tree		:  1;
	DWORD	attr_music		:  1;

	DWORD	roof			: 12;
	DWORD	show_roof		:  1;
	DWORD	frontoffset		:  9;
	DWORD	attr_scroll		:  1;
	DWORD	attr_padding	:  9;
} TILE, *LPTILE;
*/

typedef struct	tagTILE
{
	DWORD	back			: 12;
	DWORD	front			: 12;
	DWORD	fronttype		:  1;
	DWORD	rooftype		:  1;
	DWORD	attr_dont		:  1;
	DWORD	attr_map		:  1;
	DWORD	attr_room		:  2;
	DWORD	attr_music		:  2;

	DWORD	roof			: 12;
	DWORD	show_roof		:  1;
	DWORD	frontoffset		: 10;
	DWORD	attr_scroll		:  1;
	DWORD	attr_door		:  1;
	DWORD	attr_tree		:  1;
	DWORD	occupied     	:  1;
	DWORD	attr_padding	:  5;
} TILE, *LPTILE;

#pragma	pack	(pop)
#pragma	pack	(push,8)

typedef struct	tagMAPFILE
{
	WORD		wType;
	WORD		wWidth, wHeight;
	char		cOdd, cEven;
} MAPFILE, *LPMAPFILE;

typedef struct	tagMAP
{
	int				x, y;
	WORD			wScreenWidth, wScreenHeight;
	MAPFILE			file;
} MAP, *LPMAP;


// event
typedef struct	tagEVENTLIST
{
	WORD				x, y;
	WORD				index;
	struct tagEVENTLIST	*lpPrev, *lpNext;
} EVENTLIST, *LPEVENTLIST;

typedef struct	tagEVENTLISTHEADER
{
	WORD			wCount;
	LPEVENTLIST		lpFirst, lpLast;
} EVENTLISTHEADER, *LPEVENTLISTHEADER;

// 1003 YGI
#define		MAX_MAP_	100			

typedef struct		
{
	char mapfile[ 30];
	char mapname[30];
	char floor;				// �� ����
	int  x, y;				// ���� ����.
	char daylightcontrol;	// 1: �㳷�� �ִ�.			0: ���̴�.
	char rain;				// 1 :�̸� �� ���°��̴�.	0 : �� ���� �ʴ� �������� ���̴�. 
	char nation;			// 0 : ��������. 1 : 2 : Monster  3:���̼��� 4:������
	bool forrookie;			// �ʺ��ڸ� ���� ��������. : �̰������� �ʺ��ڸ� ���ϼ� ����. 
	int  port;
	
} t_mapinfo;
extern t_mapinfo			MapInfo[ MAX_MAP_];

#pragma	pack	(pop)

extern MAP					g_Map;
extern TILE					TileMap[ VILLAGE_SIZE ][ VILLAGE_SIZE ];
extern EVENTLISTHEADER		g_EventListHeaderMap;
extern EVENTLISTHEADER		g_EventListHeaderRoom;
extern EVENTLISTHEADER		g_EventListHeaderMusic;

extern char					MapName[ 20];
extern LPMAPFILE			g_lpMapFile;

#ifdef __cplusplus
extern "C"
{
#endif

extern BOOL		MapBuild( LPMAP lpMap, char *mapname );
extern void		MapDestroy( LPMAP lpMap );
extern BOOL		MapReadFile( LPMAPFILE lpMapFile, char* pszFileName );

extern BOOL			BuildEventList( char* lpszFileName );
extern void			DestroyEventList( void );
extern LPEVENTLIST	AddEventList( LPEVENTLISTHEADER lpEventListHeader, WORD x, WORD y, WORD wIndex );
extern void			DeleteEventList( LPEVENTLISTHEADER lpEventListHeader, LPEVENTLIST lpEventList );
extern LPEVENTLIST	FindEventList( LPEVENTLISTHEADER lpEventListHeader, WORD x, WORD y );
extern BOOL			ReadEventList( char* lpszFileName );



extern int ReturnEventNo( int mx, int my );
extern int ChangeEventNo( int mx, int my, int eventno  );





#ifdef __cplusplus
}
#endif

#endif	// __MAP_H__
