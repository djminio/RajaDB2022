#include "StdAfx.h"
#include "MAIN.H"

ITEMLIST ItemList[MAX_ITEM_LIST];


typedef struct t_StoreItemList
{	int no;
	ITEM item[ 100];
	ITEM unique[10];
}STOREITEMLIST, *LPSTOREITEMLIST;

#define MAX_STORE 10
STOREITEMLIST  StoreItemList[ MAX_STORE];



//--------------------------------------------------------
void InitItemList(void)
{
	int i;

	  for(i = 0; i < MAX_ITEM_LIST; i ++)
			ItemList[i].bAlive = REMOVE_;
};

//--------------------------------------------------------
int  GetAliveItemList(void)
{
	int i;

	  for(i = 0; i < MAX_ITEM_LIST; i ++)
		{
			if(ItemList[i].bAlive == FALSE)
				return(i);
		}

		return(-1);
};

//--------------------------------------------------------
int  AddItemList(int item_no, unsigned int attr[6], int x, int y, int offx, int offy )
{		
	int Num;

	Num = GetAliveItemList();
	if(Num < 0)
			return(-1);
		

	ITEMLIST *i = &ItemList[Num];

	i->item_no		= item_no;
	i->attr[0]		= attr[0];
	i->attr[1]		= attr[1];
	i->attr[2]		= attr[2];
	i->attr[3]		= attr[3];
	i->attr[4]		= attr[4];
	i->attr[5]		= attr[5];
	i->x			= x;
	i->y			= y;
	i->offx			= offx;
	i->offy			= offy;
	i->bAlive		= ALIVE_;

	SetArea(ADD_ITEM_AREA, Num);

	return(Num);
};
		
//--------------------------------------------------------
void RemoveItemList(int Num)
{		
		ItemList[Num].bAlive = FALSE;
		SetArea(REMOVE_ITEM_AREA, Num);
};

//--------------------------------------------------------




void InitStoreListFromSQL( char *tablename )
{
		
}







//--------------------------------------------------------





























				






