#ifndef _DRAGON_ITEMLIST_
#define _DRAGON_ITEMLIST_

#define MAX_ITEM_LIST 10000


enum ITEM_STRUCT_INDEX
{
	IATTR_DURATION		=0,
	IATTR_LIMIT			=1,
	IATTR_ATTR			=2,
	IATTR_ID			=3,
	IATTR_RESERVED0		=4,
	IATTR_RESERVED1		=5,
};
const int IATTR_MUCH			= IATTR_DURATION;
const int IATTR_SEAL_STONE_NO	= IATTR_LIMIT; 
const int IATTR_SPRITE_TYPE		= IATTR_LIMIT;
const int IATTR_RARE_MAIN		= IATTR_ID;


typedef struct tagITEMLIST
{ 
	BOOL bAlive;

	short			item_no;
	unsigned int	attr[6];
	short int		x, y;
	short int		offx, offy;
} ITEMLIST, *LPITEMLIST;


typedef struct t_item
{
	short int itemno;
	unsigned int status[3];
}ITEM, *LPITEM;


extern ITEMLIST ItemList[MAX_ITEM_LIST];

extern void InitItemList(void);
extern int	GetAliveItemList(void);
extern int  AddItemList(int itemno, unsigned int attr[6], int x, int y, int offx, int offy );
extern void RemoveItemList(int Num);

#endif
