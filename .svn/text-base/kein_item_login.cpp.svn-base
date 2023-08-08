#include "StdAfx.h"
#include "main.h"
#include "CItem.h"



extern int GetBoxItemId_SQL( );
extern struct CItem_List Item_Ref ;
extern void getItemIndex(int, int &, int &) ;

extern void SendCharInfoBasic( int cn, short int kind, DWORD data );



extern CItem_Plant			CPlant		[];
extern CItem_Mineral		CMineral	[];
extern CItem_Herb			CHerb		[];
extern CItem_Cook			CCook		[];
extern CItem_Potion			CPotion		[];
extern CItem_Tool			CTool		[];
extern CItem_Weapon			CWeapon		[];
extern CItem_Disposable		CDisposable	[];
extern CItem_Armor			CArmor		[];
extern CItem_Accessory		CAccessory	[];
extern CItem_Etc			CEtc		[];


DWORD CreateItemDuration( int type, int itemno )
{
	static int bonus = 0;
	
	CItem *t;

	t = ItemUnit( type, itemno );
	if( t == NULL ) return 0;

	DWORD basic_dur;

	if( t->GetRbutton() == DIVIDE_ITEM ) basic_dur = t->GetDuration();
	else basic_dur = MAKELONG( t->GetDuration(), t->GetDuration() );

	return basic_dur;
}

void DeleteItem( ItemAttr *item )
{
	int type, num;
	if( !item ) return;		// NULL일 경우 
	getItemIndex( item->item_no, type, num );

	CItem *t = ItemUnit( type, num );
	if( !t ) return;

	//if( t->GetItemKind() == IK_BOX ) DeleteBoxItem_SQL( item->attr[IATTR_ID] );
	t->ThisMapValue--;
	//if( !t->m_Much ) t->m_Much = 0;
	memset( item, 0, sizeof( ItemAttr ) );
	return;
}


/////////////////////////////////////////////////////////////////////////////////////
//
//		아이템에 의한 매직 공격력...
//
//		파라메타	:	아이템 넘버로 매직 클레스 값을 가져오고 비교해서
//		리턴값		:	매직 공격력을 넘겨 준다.
//
//////////////////////////////////////////////////////////////////////////////////////
int MagicByItem( int item_no, int magic_class )
{
	int type, num;
	getItemIndex( item_no, type, num );

	CItem *t = ItemUnit( type, num );
	if( !t ) return 0;

	if( t->GetKindOfMagic() == magic_class )
	{	
		return t->GetIncrDamage();
	}	
		
	return 0;
}		
		
///////////////////////////////////////////////////////////////////////////////
//		
//		시간에 의한 캐릭터의 배고픔 수치 줄이기	//###1213_2 수정
//		
///////////////////////////////////////////////////////////////////////////////
void HungryMuchAdd( CHARLIST *ch, double type )
{		
	double plus = 1.0f; // 캐릭터의 상태에 따라 변화가 있을 경우 이 값을 변화 시킨다.
		
	if( ch->bAlive != ALIVE_ ) return;

//	if( ch->condition == CON_NOMAL )
	ch->Hungry_much += (float )(type*plus);
}		
		
int GetWeight( ItemAttr item )
{
	int type, num;
	getItemIndex( item.item_no, type, num );

	CItem *t = ItemUnit( type, num );
	if( !t ) return 0;

	int weight = t->GetWeight();

	if( t->GetRbutton() == DIVIDE_ITEM )
	{
		int dur = t->GetItemDuration();
		if( dur > 0 ) 
			weight *= item.attr[IATTR_MUCH] / dur;
		else weight *= item.attr[IATTR_MUCH];
	}

	return weight;
}

int GetTotalItemWeight( CHARLIST *ch )
{
	int weight = 0;
	int a, b, c;
	for(a=0;a<3;a++)
		for(b=0;b<3;b++)
			for(c=0;c<8;c++)
				if(ch->inv[a][b][c].item_no) 
					weight += GetWeight( ch->inv[a][b][c] );
	for(a=0;a<6;a++)
		if(ch->quick[a].item_no)	weight += GetWeight(ch->quick[a]);
	for(a=0;a<8;a++)
		if(ch->equip[a].item_no)	weight += GetWeight(ch->equip[a]);
	if( ch->handheld.item_no ) weight += GetWeight( ch->handheld );

	return weight;
}




//////////////////////////// Item POS Set /////////////////////////////////
void SetItemPos(int type, POS* IP_set)
{
	IP_set->type = (char)type;
	IP_set->p1 = 0;
	IP_set->p2 = 0;
	IP_set->p3 = 0;
}

void SetItemPos(int type, int p, POS* IP_set)
{
	IP_set->type = (char)type;
	IP_set->p1 = 0;
	IP_set->p2 = 0;
	IP_set->p3 = (short int)p;
}

void SetItemPos(int type, int p1, int p2, int p3, POS* IP_set)
{
	IP_set->type = ( char )type;
	IP_set->p1 = (short int)p1;
	IP_set->p2 = (short int)p2;
	IP_set->p3 = (short int)p3;
}

DWORD GetMoneyByItem( CHARLIST *ch )
{
	DWORD money=0;

	int type, num;
	CItem *t;

	for( int i=0; i<3; i++ )
		for( int j=0; j<3; j++ )
			for( int k=0; k<8; k++ )
			{
				ItemAttr &item = ch->inv[i][j][k];
				if( item.item_no )
				{
					getItemIndex( item.item_no, type, num );
					t = ItemUnit( type, num );
					if( t && t->GetItemKind() == IK_MONEY )
					{
						if( item.item_no == IN_COIN && item.attr[IATTR_MUCH] > 5)	// 동전
						{
							item.item_no = IN_COINS;		// 돈 더미로 바꿈
						}
						else if( item.item_no == IN_COINS && item.attr[IATTR_MUCH] <= 5 ) // 동전 더미
						{
							item.item_no = IN_COIN;
						}
						money += item.attr[IATTR_MUCH];
					}
				}
			}

	if( ch->handheld.item_no ) // 핸드 부분에 있는 돈 계산
	{
		ItemAttr &item = ch->handheld;
		getItemIndex( item.item_no, type, num );
		t = ItemUnit( type, num );
		if( t && t->GetItemKind() == IK_MONEY )
		{
			if( item.item_no == IN_COIN && item.attr[IATTR_MUCH] > 5) item.item_no = IN_COINS;	
			else if( item.item_no == IN_COINS && item.attr[IATTR_MUCH] <= 5 ) item.item_no = IN_COIN;
			money += item.attr[IATTR_MUCH];
		}
	}

	return money;
}

/////////////////////////////////////////////////////////////////////
//
// 돈 아이템에 관련한 메소드들 ( 돈 빼고 더하기 함수 )
//
////////////////////////////////////////////////////////////////////
int SubtractMoney( DWORD money, CHARLIST *ch )
{
	if(ch->Money < money ) return -1;	// 돈이 부족함

	if( !money ) return 1;
	ItemAttr *item = SearchItemOfInvByKind( IK_MONEY, ch );
	if( !item ) return -1;		// 돈 아이템이 하나도 없음. -->SCharacterData.nMoney = 0;		==> 문제 있음...

	if( item->attr[IATTR_MUCH] < money )
	{
		money -= item->attr[IATTR_MUCH];
		DeleteItem( item );
		SubtractMoney( money, ch );
	}
	else 
	{
		item->attr[IATTR_MUCH] -= money;
		return 1;
	}
	return 1;
}
int AddMoney( DWORD money, CHARLIST *ch )
{
	if( !money ) return 1;
	ItemAttr *item = SearchItemOfInvByKind( IK_MONEY, ch );
	if( !item )	// 돈 아이템이 하나도 없을때 새로 생성
	{
		ItemAttr *new_item = SearchInv( ch );
		if( !new_item ) return -1;

		memset( new_item, 0, sizeof( ItemAttr ) );
		if( money > 5 )
			new_item->item_no = IN_COINS;
		else new_item->item_no = IN_COIN;
		new_item->attr[IATTR_MUCH] = money;
		item = new_item;
	}
	else item->attr[IATTR_MUCH] += money;
	
	CheckAutoDivideMoney( item, ch->server_id );

	return 1;
}
int SearchItemPosByNumber(int num, int &a, int &b, int &c, CHARLIST *ch)
{
	for(a=0;a<3;a++)
		for(b=0;b<3;b++)
			for(c=0;c<8;c++)
				if(ch->inv[a][b][c].item_no == num)
					return 1;
	return 0;
}
int SearchCoinItem( int &a, int &b, int &c, CHARLIST *ch )
{
	for(a=0;a<3;a++)
		for(b=0;b<3;b++)
			for(c=0;c<8;c++)
				if( ch->inv[a][b][c].item_no == IN_COIN || ch->inv[a][b][c].item_no == IN_COINS )
					return 1;
	return 0;
}
ItemAttr *SearchItemOfInvByKind( int kind, CHARLIST *ch )
{
	int type, num;
	CItem * t;
	for( int i=0; i<3; i++ )
		for( int j=0; j<3; j++ )
			for( int k=0; k<8; k++ )
			{
				ItemAttr &item = ch->inv[i][j][k];
				if( item.item_no )
				{
					getItemIndex( item.item_no, type, num );
					t = ItemUnit( type, num );
					if( t && t->GetItemKind() == kind ) return &item;
				}
			}
	return NULL;
}

ItemAttr *SearchInv( CHARLIST *ch )
{
	for( int a=0; a<3; a++ )
		for( int b=0; b<3; b++ )
			for( int c=0; c<8; c++ )
			{
				if( !ch->inv[a][b][c].item_no ) return &ch->inv[a][b][c];
			}
	return NULL;
}


int IsEqualPosByPos( POS first, POS second )
{
	if( first.type	!= second.type	|| 
		first.p1	!= second.p1	||
		first.p2	!= second.p2	||
		first.p3	!= second.p3 )		return 0;

	return 1;
}

void CheckItem( short int cn ) // 잘못된 아이템을 가지고 있는지 
{
	bool fResendItem = false;
	CHARLIST *ch = &connections[cn].chrlst;
	if( !ch ) return;

	int a, b, c;
	for( a=0; a<3; a++ )
		for( b=0; b<3; b++ )
			for( c=0; c<8; c++ )
				if( ch->inv[a][b][c].item_no )
				{
					ItemAttr *item = &ch->inv[a][b][c];
					CheckAutoDivideMoney( item, cn ) ;

					int type, num;
					getItemIndex( item->item_no, type, num );
					CItem *t = ItemUnit(type, num);
					if( !t ) 
					{
						memset( item, 0, sizeof( ItemAttr ) );
						continue;
					}
					if( !t->GetItemImage() || !t->GetObjectNumber() ) 
					{
						memset( item, 0, sizeof( ItemAttr ) );
						continue;
					}
				}

	for( c=0; c<8; c++ )
		if( ch->equip[c].item_no )
		{
			ItemAttr *item = &ch->equip[c];
			int type, num;
			getItemIndex( item->item_no, type, num );
			CItem *t = ItemUnit(type, num);
			if( !t ) 
			{
				memset( item, 0, sizeof( ItemAttr ) );
				continue;
			}
			if( !t->GetItemImage() || !t->GetObjectNumber() ) 
			{
				memset( item, 0, sizeof( ItemAttr ) );
				continue;
			}
		}

	for( c=0; c<7; c++ )
		if( ch->quick[c].item_no )
		{
			if(c >= 5)continue;//soto-030514 심볼 아이템은 체크 하지 않는다.

			ItemAttr *item = &ch->quick[c];
			int type, num;
			getItemIndex( item->item_no, type, num );
			CItem *t = ItemUnit(type, num);
			if( !t ) 
			{
				memset( item, 0, sizeof( ItemAttr ) );
				continue;
			}
			if( !t->GetItemImage() || !t->GetObjectNumber() ) 
			{
				memset( item, 0, sizeof( ItemAttr ) );
				continue;
			}
		}
		
	return;
}

void GetItemDuration( ItemAttr item, WORD &d_curr, WORD &d_max )
{
	d_curr = LOWORD( item.attr[IATTR_DURATION] );
	d_max = HIWORD( item.attr[IATTR_DURATION] );
}


int CheckAutoDivideMoney( ItemAttr *item, short int cn )		// 100000을 넘은 아이템 처리
{

	CItem *t = ItemUnit( *item );
	if( !t ) return 0 ;

	if( t->GetItemKind() != IK_MONEY ) return 0;

	CHARLIST *ch = &connections[cn].chrlst;
	if( !ch ) return 0 ; 

	if( item->attr[IATTR_DURATION] > MAX_MONEY ) 
	{
		ItemAttr *new_item = SearchInv( ch );
		if( !new_item )
		{
			item->attr[IATTR_MUCH] = MAX_MONEY;
		}
		else
		{
			memcpy(new_item , item , sizeof( ItemAttr ) );
			new_item->attr[IATTR_MUCH] = item->attr[IATTR_DURATION] - MAX_MONEY;
			item->attr[IATTR_MUCH] = MAX_MONEY;
			if( new_item->attr[IATTR_MUCH] > MAX_MONEY ) CheckAutoDivideMoney( new_item, cn );

			return 1;
		}
	}
	return 0;
}



#ifndef _GAME_SERVER_
/////////////////////////////////////////////////////////////////////////////
	int CItem_Plant::use(int t, t_chr_status_info *p, POS s, POS d ) { return 0; }
	int CItem_Mineral::use(int t, t_chr_status_info *p, POS s, POS d ) { return 0; }
	int CItem_Herb::use(int t, t_chr_status_info *p, POS s, POS d ) { return 0; }
	int CItem_Cook::use(int t, t_chr_status_info *p, POS s, POS d ) { return 0; }
	int CItem_Potion::use(int t, t_chr_status_info *p, POS s, POS d ) { return 0; }
	int CItem_Tool::unequip(int,struct chr_status_info *,struct t_POS,struct t_POS)		 { return 0; }
	int CItem_Tool::is_equipable(int,struct chr_status_info *,struct t_POS,struct t_POS) { return 0; }
	int CItem_Weapon::unequip(int,struct chr_status_info *,struct t_POS,struct t_POS)	 { return 0; }
	int CItem_Weapon::is_equipable(int,struct chr_status_info *,struct t_POS,struct t_POS) { return 0; }
	int CItem_Disposable::unequip(int,struct chr_status_info *,struct t_POS,struct t_POS) { return 0; }
	int CItem_Disposable::is_equipable(int,struct chr_status_info *,struct t_POS,struct t_POS) { return 0; }
	int CItem_Armor::unequip(int,struct chr_status_info *,struct t_POS,struct t_POS) { return 0; }
	int CItem_Armor::is_equipable(int,struct chr_status_info *,struct t_POS,struct t_POS) { return 0; }
	int CItem_Accessory::unequip(int,struct chr_status_info *,struct t_POS,struct t_POS) { return 0; }
	int CItem_Accessory::is_equipable(int,struct chr_status_info *,struct t_POS,struct t_POS) { return 0; }
	int CItem_Etc::unequip(int,struct chr_status_info *,struct t_POS,struct t_POS) { return 0; }
	int CItem_Etc::is_equipable(int,struct chr_status_info *,struct t_POS,struct t_POS) { return 0; }
	int CItem_Plant::EatItem(CHARLIST *ch )	{ return 0; }
	int CItem_Herb::EatItem(CHARLIST *ch )	{ return 0; }
	int CItem_Herb::UseItem(CHARLIST *ch )	{ return 0; }
	int CItem_Cook::EatItem(CHARLIST *ch )	{ return 0; }
	int CItem_Cook::UseItem(CHARLIST *ch )	{ return 0; }
	int CItem_Potion::EatItem(CHARLIST *ch )	{ return 0; }
	int CItem_Potion::UseItem(CHARLIST *ch )	{ return 0; }
	int CItem_Potion::is_equipable(int,struct chr_status_info *,struct t_POS,struct t_POS) { return 0; }
	int CItem_Weapon::ReleaseItem(struct tagCHARLIST *) { return 0; }

	int CItem_Weapon::CurrEquip(struct tagCHARLIST *)			{ return 0; }
	int CItem_Weapon::EquipItem(struct tagCHARLIST *)			{ return 0; }
	int CItem_Armor::ReleaseItem(struct tagCHARLIST *)			{ return 0; }
	int CItem_Armor::CurrEquip(struct tagCHARLIST *)			{ return 0; }
	int CItem_Armor::EquipItem(struct tagCHARLIST *)			{ return 0; }
	int CItem_Accessory::ReleaseItem(struct tagCHARLIST *)		{ return 0; }
	int CItem_Accessory::CurrEquip(struct tagCHARLIST *)		{ return 0; }
	int CItem_Accessory::EquipItem(struct tagCHARLIST *)		{ return 0; }
	int CItem_Etc::ReleaseItem(struct tagCHARLIST *)			{ return 0; }
	int CItem_Etc::CurrEquip(struct tagCHARLIST *)				{ return 0; }
	int CItem_Etc::EquipItem(struct tagCHARLIST *)				{ return 0; }
	

/////////////////////////////////////////////////////////////////////////////
#endif






