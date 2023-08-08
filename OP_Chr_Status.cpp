#include "StdAfx.h"

#include <vector>

#include "main.h"
#include "CItem.h"
#include "Map.h"
#include "scrp_exe.h"
#ifdef _GAME_SERVER_
#include "OP_Magic.h"
#endif
#include "dragonLoginServer2.h" // For ConvertQueryString

#define NUM_OF_RACE	9
#define NUM_OF_KIND 8

//struct PeopleInSQuest //Eleval 10/08/09 - To bring ppl back in quest
//{
//	char charname[32];
//	int questfloor;
//	int nbMap;
//	int nY;
//	int nX;
//};

//std::vector<PeopleInSQuest> g_PeopleInUndeadQuest; //Eleval 10/08/09 - To bring ppl back in quest
//std::vector<PeopleInSQuest> g_PeopleInAbyssQuest; //Eleval 10/08/09 - To bring ppl back in quest
//std::vector<PeopleInSQuest> g_PeopleInBigmazeQuest; //Eleval 10/08/09 - To bring ppl back in quest

extern CItem_Weapon			CWeapon[] ;

//////////////////////////////////////////////////////////////
///
///
extern int  calcAC( CHARLIST *ch );

#ifdef _GAME_SERVER_
extern int IsHePK( int id );
#endif



//////////////////////////////////////////////////////////////
///
///

// SP 소비 관련 테이블
// 종족별, 상태(전투, 비전투, 잠 등의 상태에 따라)
char sp_consume_tbl[NUM_OF_RACE][NUM_OF_KIND]= { -5, -3, 1, 15, -8, -5, 1, 20,
-6, -3, 1, 15, -6, -2, 2, 18,
-4, -2, 1, 15, -6, -3, 1, 15,
-8, -5, 1, 20, -5, -3, 1, 15,
-4, -4, 2, 15, -4, -4, 3, 15,
-5, -3, 1, 20, -6, -4, 3, 25,
-1, -1, 1,  5, -1, -1, 1,  6,
-3,  0, 2, 10, -4,  0, 2, 10,
-1,  0, 1,  3, -1,  0, 1,  3 	} ;						



// SP보정 관련 테이블
char sp_ttt_corr_tbl[11]= {6, 8, 1, 13, 16, 19, 22, 25, 28, 31, 34 } ; // use the result of divide it by 10
char sp_weight_corr_tbl[10]= {1, 1, 1, 1, 1, 12, 14, 16, 18, 2 } ; // use the result of divide it by 10

// 마법의 캐스팅 보정 테이블 DAMAGE(%)
// 캐스팅 시간 - 현레벨 + 요구레벨
char spell_efficent_tbl[10]= {6, 7, 8, 9, 10, 11, 12, 13, 14, 15 } ; // use the result of divide it by 10

// 책으로 습득가능한 마법 개수.
// index= (int)(INT-10) / 8
char spell_per_int_tbl[9]= {8, 17, 37, 48, 60, 73, 87, 102, 116 } ;

// 문열기
char break_lock_tbl[20]= {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 } ;
// 쇠창살 휘기
char break_bar_tbl[20]= {0, 0, 0, 1, 2, 3, 7, 9, 10, 12, 18, 24, 30, 36, 42, 48, 54, 60, 66, 72 } ;

// 이동속도 0~25, 26~50, 51~75, 76~99 
// index= (int)((MoveP-1) / 25)
char walk_per_round[4]= {2, 3, 4, 5 } ;
char run_per_round[4]= {4, 5, 6, 7 } ;




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///		User Functions Declaration...
///
int InitPartyMemberServerToServer( CHARLIST *ch );		//  이름만 디비에 저장하고 이름만 꺼내온다.
int EndsetPartyMenberForUpdate( CHARLIST *ch );
int SetMySkill( CHARLIST *ch );		// 일단 기본적으로 알아야하는 스킬 셋

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///		User Functions.
///

void SendLevelUpMsgAndPoint( CHARLIST *chr )		// 1217
{
	t_packet p;
	
	p.h.header.type= CMD_LEVELUP_POINT;
	{
		//< CSD-010907
		p.u.server_levelup_point.idServer	= chr->server_id;
		p.u.server_levelup_point.nPoint	= (BYTE )chr->reserved_point;
		p.u.server_levelup_point.nLife = chr->Hp;
		//> CSD-010907
	}
	p.h.header.size= sizeof( t_server_levelup_point );
	QueuePacket(connections, chr->server_id, &p, 1);
	
	
	
#ifdef _GAME_SERVER_
	CastMe2Other( chr->server_id, &p );
#endif
	
}

// 시간당 1번 호출
void calcHungry(CHARLIST *chr)
{
	double lev_corr, disease_corr, t;
	int h= 0, weight_index ;
	
	if(chr->Peacests) { // 전투시
		if(chr->Level < 20) {
			lev_corr= 1 + (chr->Level - 20) * 0.02 ;
		}
		else {
			lev_corr= 1 + (chr->Level - 20) * 0.03 ;
		}
		
		weight_index= (int)chr->Weight / chr->MaxWeight * 10 ;
		
		disease_corr= 1.0 ;
		
		t = sp_consume_tbl[chr->Race][0] * lev_corr * sp_weight_corr_tbl[weight_index] / 10 + disease_corr ;
		
		chr->Hungry-= (short)t;
		if( chr->Hungry < 0 )  chr->Hungry = 0;
		
	}
	else { // 기술사용? 휴식? 수면?
	}
}	


int calcMovP( CHARLIST *ch )
{
	int t = ch->MoveP;
	
	return t;
}

// 나이에 따른 각 무기기술별 스킬 숙련도의 상승속도의 차이 10으로 나누어 사용
char tac_inc_by_age_tbl[12][37]= {	1, 13, 12, 13, 13, 12, 12, 14, 13, 15, 14, 12, 10, 12, 10, 10, 10, 10, 11, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 10, 1,
1, 10, 10, 11, 11, 12, 12, 13, 13, 12, 14, 13, 11, 10, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 11, 12, 12, 11, 13, 11, 14, 10, 10, 10, 10, 10, 1,
1, 10, 10, 10, 10, 11, 13, 14, 15, 15, 15, 11, 12, 10, 10, 13, 10, 10, 10, 11, 10, 11, 10, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 10, 10, 1,
1, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 10, 11, 15, 13, 12, 14, 11, 11, 12, 10, 10, 10, 10, 10, 13, 11, 12, 10, 10, 10, 11, 10, 10, 10, 10, 1,
1, 10, 10, 10, 10, 12, 10, 10, 10, 10, 10, 10, 10, 15, 14, 11, 13, 10, 12, 11, 10, 10, 10, 10, 10, 14, 10, 13, 10, 10, 10, 10, 10, 11, 11, 10, 1,
1, 12, 10, 10, 11, 13, 12, 10, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 12, 14, 10, 12, 13, 12, 12, 13, 13, 12, 10, 10, 10, 10, 10, 11, 10, 1,
1, 10, 11, 10, 11, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 12, 10, 10, 10, 14, 15, 14, 15, 15, 14, 14, 15, 10, 10, 10, 11, 10, 10, 10, 10, 10, 1,
1, 10, 11, 10, 10, 10, 10, 10, 11, 10, 12, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10, 10, 11, 10, 12, 13, 15, 14, 14, 15, 15, 11, 10, 10, 10, 11, 1,
1, 10, 10, 11, 10, 10, 10, 10, 11, 10, 13, 13, 12, 15, 14, 12, 10, 10, 10, 10, 10, 10, 11, 10, 10, 11, 13, 12, 12, 11, 10, 10, 11, 10, 10, 10, 1,
1, 10, 10, 10, 10, 11, 10, 10, 11, 10, 10, 14, 12, 13, 14, 15, 14, 13, 12, 11, 10, 10, 10, 11, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 10, 1,
1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10, 10, 11, 12, 13, 12, 12, 14, 13, 12, 11, 12, 13, 11, 10, 10, 10, 10, 11, 11, 10, 11, 10, 1,
1, 10, 10, 10, 10, 11, 10, 10, 10, 11, 10, 10, 13, 12, 14, 13, 14, 11, 10, 10, 10, 10, 10, 12, 13, 12, 13, 14, 12, 10, 10, 10, 10, 11, 10, 10, 1
} ;

// 직업에 따른 무기기술별 숙련도 상승정도 (10으로 나누어 사용)

char tac_inc_by_class_tbl[5][12]= { 15, 15, 15, 15, 1, 1, 1, 1, 15, 15, 15, 1,
8, 10, 8, 8, 8, 8, 15, 15, 8, 8, 1, 8,
1, 1, 8, 8, 15, 15, 15, 15, 1, 8, 8, 1,
8, 8, 8, 8, 15, 1, 1, 8, 8, 8, 8, 1,
5, 8, 5, 5, 15, 1, 1, 8, 5, 5, 5, 5
} ;

void increaseTacticsSkill(CHARLIST *chr)
{
	int skill_index ;
	int k ;
	int age_index, weapon_type_index ;
	double skill_corr ;
	
	k= 1 ;
	skill_index= 0 ;
	
	// 스킬선택 보정
	if(chr->Tactics == skill_index) skill_corr= 1.2 ;
	else skill_corr= 1.0 ;
	
	if(chr->Age < 15) {
		age_index= 0 ;
	} else age_index= chr->Age-15;
	
	if(CWeapon[chr->equip[0].item_no].Item_kind < 0)
	{
		weapon_type_index= 0;
	} else weapon_type_index= CWeapon[chr->equip[0].item_no].Item_kind;
	
	double t = k * tac_inc_by_age_tbl[skill_index][age_index] 
		* tac_inc_by_class_tbl[chr->Race][weapon_type_index] * skill_corr;
	
	chr->tac_skillEXP[skill_index]+= (int)t;
}



void increaseJobSkill(CHARLIST *chr)
{	
	
}	

void decreaseJobSkill(CHARLIST *chr)
{	
	
}	

void decreaseClassSkill(CHARLIST *chr)
{	
	
}	

void increaseClassSkill(CHARLIST *chr)
{	
	
}	

int increaseAbility(CHARLIST *chr, t_packet *packet)
{
	if(packet->h.header.size < packet->u.mass_data.num * 3 + 1) {
		printf("\n increase ability: Size doesn't matching!") ;
		return -1 ;
	}
	int total_inc= 0 ;	
	int i= 0 ;
	
	for(i= 0 ; i < packet->u.mass_data.num ; i++) 
		total_inc+= packet->u.mass_data.elements[i].value ;
	// 클라이언트가 봬온 증가값들의 총합이 현재 남아있는 분배점수보다 많으면 에러
	if(total_inc > chr->reserved_point) return -1 ;
	
	for(i= 0 ; i < packet->u.mass_data.num ; i++)
		switch(packet->u.mass_data.elements[i].var_kind) {
		case STR:
			chr->Str+= packet->u.mass_data.elements[i].value ;
			break ;
		case CON:
			chr->Con+= packet->u.mass_data.elements[i].value ;
			break ;
		case DEX:
			chr->Dex+= packet->u.mass_data.elements[i].value ;
			break ;
		case WIS:
			chr->Wis+= packet->u.mass_data.elements[i].value ;
			break ;
		case INT:
			chr->Int+= packet->u.mass_data.elements[i].value ;
			break ;
		case MOVP:
			chr->MoveP+= packet->u.mass_data.elements[i].value ;
			break ;
		case CHA:
			chr->Char+= packet->u.mass_data.elements[i].value ;
			break ;
		case ENDU:
			chr->Endu+= packet->u.mass_data.elements[i].value ;
			break ;
		case MOR:
			chr->Moral+= packet->u.mass_data.elements[i].value ;
			break ;
		case LUCK:
			chr->Luck+= packet->u.mass_data.elements[i].value ;
			break ;
		case WSPS:
			chr->wsps+= packet->u.mass_data.elements[i].value ;
			break ;
	}
	
	chr->reserved_point-= total_inc ;
	return total_inc ;
}


int SetItemEmpty( CHARLIST *ch,  int item_no )		// 빈 인벤토리에 아이템을 생성해서 집어 넣는다. //1215
{
	ItemAttr *item = SearchInv( ch );
	if( item ) *item = GenerateItem( item_no ) ;
	else return 0;
	
	return 1;
}

extern int SetTactics( int spell_type, int sex, int tac_type );	// 1101 YGI
// 최초 캐릭터의  생성위치, 기본수치, Item들을 Setting한다. 
void CreateCharacter( t_connection c[], int cn, t_packet *packet)		// 001215 YGI
{
	CHARLIST *ch = &c[cn].chrlst;
	t_client_create_char *p = &packet->u.client_create_char;
	
	memset( ch->Ws,			0,	SIZE_OF_WS			);	//	마법
	memset( ch->Ps,			0,	SIZE_OF_PS			);				//	신법
	memset( ch->Skill,		0,	SIZE_OF_SKILL		);
	memset( ch->skillexp,	0,	SIZE_OF_SKILL_EXP	);
	memset( ch->tac_skillEXP,0, SIZE_OF_TAC_SKILL_EXP );
	
	memset( var[ cn],       0, SIZE_OF_SCRIPT_VAR	); // 0819 KHS
	memset( ch->inv,		0, SIZE_OF_INV			);	// 인벤토리
	memset( ch->equip,		0, SIZE_OF_EQUIP		);		// 장착
	memset( ch->quick,		0, sizeof( ItemAttr ) * 7 );		// 퀵 
	memset( ch->bank,		0, SIZE_OF_BANKITEM );
	
	memset( ch->party,		0, SIZE_OF_PARTY		);
	memset( ch->relation,	0, SIZE_OF_RELATION		);
	memset( ch->employment,	0, SIZE_OF_EMPLOYMENT	);
	memset( ch->Item,		0, SIZE_OF_ITEMINDEX );
	
	memset( &ch->handheld,	0, sizeof( ItemAttr ));		// 손(마우스)에 들고 있는
	memset( &ch->name_status, 0 ,sizeof( DWORD ) );		// 001219 YGI
	
	memcpy( ch->Name, p->name, 20 );
	
	ch->bAlive				= ALIVE_;
	
	ch->Level		=  1;
	ch->LvUpPoint	=  0;
	ch->Exp			=  0;
	
	ch->LastLoan = 0;		// 010608 YGI
	
	ch->Gender				= p->gender;						// 0:여자 1 : 남자	
	ch->Face				= p->face;												
	ch->nGuildCode 			= 0; // CSD-030324
	ch->Job					= p->job;						// 0:전사 1:궁수 2:도적 3:성직자 4:마법사
	ch->Class				= p->Class;													
	
	int nation = GetNationById(c[cn].id);					// 1004 YGI
	if( nation < 0 ) nation = 0;
	ch->name_status.nation	= nation;
	ch->Race				= 0;	// 종족
	ch->Tactics			=  p->tactics;		
	ch->Condition		=	0;
	strcpy(ch->MapName, "SCHOLIUM" );
	
	ch->Peacests		=	0;
	ch->Sight			=	12;
	ch->BodyR	= p->body_r,	ch->BodyG	= p->body_g,	ch->BodyB	= p->body_b;		// 몸 색깔 R.G.B
	ch->ClothR	= p->cloth_r,	ch->ClothG	= p->cloth_g,	ch->ClothB	= p->cloth_b;		// 띠 색깔 R.G.B
	ch->Age				=	p->age;
	// 010531 KHS
	ch->nk[3]			=	0;					// NK로 사용된다.
	ch->nk[4]			=	0;
	ch->nk[6]			=	0;
	
	
	ch->killmon			=	0;					// 1계열몬스터 킬링스
	ch->killanimal 		=	0;					// 동물 킬링수
	ch->killpc  		=	0;					// 사람,NPC 킬링수
	ch->nPoison =	0;
	ch->nCurse =	0;
	ch->nFire =	0;
	ch->nIce	=	0;
	ch->nElect =	0;
	ch->nHoly	=	0;
	ch->Spell				= p->spell;			// 0 : Ws   1 : Ps
	
	//////////////////////////////////////////////////////////////////////////////////						
	// 내가 가지고 있는 아이템..	//0101
	
	if(LocalMgr.IsChangeMoney())//021007 lsw
	{
		ch->inv[0][0][0] = GenerateItem( 10123, 400);
	}
	else
	{
		ch->inv[0][0][0] = GenerateItem( 10029, 400);			
	}
	
	if(ch->Gender ){ch->equip[WT_ARMOR] = GenerateItem( 8037);}
	else{ch->equip[WT_ARMOR] = GenerateItem( 8038);}
	
	ch->accessory[0] = 96;//GetItemView( ch->equip[WT_ARMOR].item_no, ch->Gender ); // 갑옷.
	ch->accessory[1] = 0;// 투구..
	ch->accessory[2] = GetItemView( ch->equip[WT_WEAPON].item_no, ch->Gender ); // 칼..
	ch->accessory[3] = 0; // 방패...
	ch->mantle		 = 0; // 011018 KHS 망또 
	
	int a, b, c1;
	int i;
	for( i=0; i<2; i++ )	// 포션 
	{
		SearchInv( ch->inv, a, b, c1 );
		ch->inv[a][b][c1] = GenerateItem( 4001);
	}
	for( i=0; i<2; i++ )	// 빵 
	{
		SearchInv( ch->inv, a, b, c1 );
		ch->inv[a][b][c1] = GenerateItem( 3007);
	}
	
	switch( ch->Class )				// 001215 YGI
	{
	case WARRIOR:
		{
			SetItemEmpty( ch, 4001 );
			SetItemEmpty( ch,  4001 );
			SetItemEmpty( ch,  6143 );
			SetItemEmpty( ch,  6146 );
			SetItemEmpty( ch,  6001 );
			SetItemEmpty( ch,  6076 );
			SetItemEmpty( ch,  6062 );
			SetItemEmpty( ch,  6063 );
			SetItemEmpty( ch,  6067 );
			SetItemEmpty( ch,  6138 );
			if(ch->Gender )
			{
				SetItemEmpty( ch, 6142);
				SetItemEmpty( ch, 6214);
				SetItemEmpty( ch, 6019);
				SetItemEmpty( ch, 6234);
			}
			else
			{
				SetItemEmpty( ch, 6141);
				SetItemEmpty( ch, 6224);
			}
			SetItemEmpty( ch, 8066 );
			SetItemEmpty( ch, 8008 );
			SetItemEmpty( ch, 8014 );
			break;
		}
	case THIEF	:
		{
			for( i=0; i<5; i++ )
			{
				SetItemEmpty( ch,  10032 );
			}
			ItemAttr *item = SearchInv( ch );
			*item = GenerateItem( 7001, 1000);
			
			item = SearchInv( ch );
			*item = GenerateItem( 7002, 1000);
			SetItemEmpty( ch, 8066 );
			break;
		}
	case ARCHER	:
		{
			for( i=0; i<5; i++ )
			{
				SetItemEmpty( ch,  10033 );
			}
			SetItemEmpty( ch,  6028 );
			SetItemEmpty( ch,  6029 );
			SetItemEmpty( ch,  8008 );
			ItemAttr *item = SearchInv( ch );
			*item = GenerateItem( 7005, 1000);
			item = SearchInv( ch );
			*item = GenerateItem( 7045, 1000);
			break;
		}
	case WIZARD	:
		{
			for( i=0; i<3; i++ )
			{
				SetItemEmpty( ch,  4002 );
			}
			SetItemEmpty( ch,  6024);				// 001219_2 YGI
			SetItemEmpty( ch,  6046);
			SetItemEmpty( ch,  8101);
			SetItemEmpty( ch,  8120);
			ch->Ws[1] = true;
			ch->Ws[2] = true;
			ch->Ws[30] = true;
			break;
		}
	case PRIEST	:
		{
			for( i=0; i<2; i++ )
			{
				SetItemEmpty( ch,  4001 );
			}
			SetItemEmpty( ch,  6024 );			// 001219_2 YGI
			SetItemEmpty( ch,  6046 );
			SetItemEmpty( ch,  8103 );
			SetItemEmpty( ch,  8120 );
			ch->Ps[1] = true;
			ch->Ps[12] = true;
			ch->Ps[27] = true;
			break;
		}
	}
	ch->Money = 400;
	if( ch->Spell == WIZARD_SPELL )
	{
		SetItemEmpty( ch,  10025 );				// 마법책
	}													// 001215 YGI -----------------------------------------
	SetMySkill( ch );
	
	//  Client을 위한 Data
	ch->SprNo			=	ch->Gender;
	ch->SprType			=	0;	
	
	ch->Direction		=	DIRECTION_SAME;
	ch->IDWhoImAttacked	=	0;	// 나를 친놈이 누구냐..
	ch->nCurrentAction	=	0;
	
	ch->BankMoney		=	0;
	
	
	ch->MoveSx			=	134;
	ch->MoveSy			=	 60;
	ch->MoveGox = ch->X	=	ch->MoveSx * TILE_SIZE + 16;
	ch->MoveGoy = ch->Y	=	ch->MoveSy * TILE_SIZE + 16;	
	ch->MovePathCount	=	0;
	ch->MoveLength		=	0;
	ch->MoveType		=	0;
	memset( ch->MoveDirTbl, 0 , MAX_DIR_TABLE );
	
	// 최초의 Skill Exp 적용 
	for( i = 0 ; i <  45 ; i ++)	ch->skillexp[i] = 5;
	
	//< CSD-011006
	/*
	calcNewAbility(ch) ;
	ch->Hp		= ch->HpMax ;
	ch->Mana	= ch->ManaMax ;
	ch->HungryMax= getMaxHungry (ch) ;
	ch->Hungry= ch->HungryMax;
	*/
	const int nCon = ch->Con/5;
	ch->HpMax	= ch->Hp = (86 + (111 + (nCon - 1)*(15 + nCon)))*2;
	ch->ManaMax	= ch->Mana = int((ch->wsps)*5.3);		// 0910 YGI
	ch->HungryMax = ch->Hungry = (ch->Con*20 + ch->Level*100 + 3000)/100;
	//> CSD-011006
	
	ch->social_status	= 100;	// 신분 : 평민.
	ch->fame			= 0;
	ch->fame_pk			= 0;	// 010915 LTS		//Fame_PK -> NWCharacter로 교체 DB에는 실제로 NWCharacter의 값이 들어갑니다.		
	memset(&ch->NWCharacter,0,sizeof(DWORD));	// 010915 LTS
	ch->viewtype		= 0;
	ch->reserved_point	= 0;
	
	//< CSD-011006
	memset(ch->aStepInfo, 1, sizeof(ch->aStepInfo));//전투스킬 초기에 -1 되어 있는 버그.
	//> CSD-011006
	
	ch->openhouse = -1; // 최초에 집밖에서 시작하므로  닫혀있는것으로 시작해야지...
}


// 게임서버에서 사용.....
void UserAddBasicData(  t_connection c[], int i, t_server_user_add *p )
{
	CHARLIST *ch = &c[i].chrlst;
	
	p->server_id	= i;
	
	memcpy(p->name, c[i].name, NM_LENGTH);
	
	//	p->killpc		= (char) ch->killpc;
	p->spr_no		= (unsigned char)ch->SprNo;
	p->spell		= (char )ch->Spell;
	p->face			= (char )ch->Face;
	
	p->body_r		= (unsigned char)ch->BodyR;
	p->body_g		= (unsigned char)ch->BodyG;
	p->body_b		= (unsigned char)ch->BodyB;
	p->cloth_r		= (unsigned char)ch->ClothR;
	p->cloth_g		= (unsigned char)ch->ClothG;
	p->cloth_b		= (unsigned char)ch->ClothB;
	
	p->equip[0]		= ch->accessory[0];
	p->equip[1]		= ch->accessory[1];
	p->equip[2]		= ch->accessory[2];
	p->equip[3]		= ch->accessory[3];
	
	p->peacests		= ch->Peacests;
	
	p->hp			= ch->Hp;
	
	p->x			= ch->MoveSx * TILE_SIZE + 16;
	p->y			= ch->MoveSy * TILE_SIZE + 16;
	
	p->viewtype		= ch->viewtype;
	
#ifdef _GAME_SERVER_
	p->fame_pk		= IsHePK( ch->server_id );
#endif
}	


// 클라이언트가 접속할때, 기본정보를 클라이언트로 보내준다
void PutPacketCharDB( t_connection c[], int cn, t_packet *packet )
{	
	t_server_user_db_data *p;
	
	CHARLIST *ch = &c[cn].chrlst;
	p = &packet->u.server_user_db_data;
	
	p->lev				= ch->Level;
	p->exp				= ch->Exp;
	
	p->Attr[0]			= ch->Gender;
	p->Attr[1]			= ch->Face;
	p->Attr[2]			= ch->nGuildCode; // CSD-030324
	p->Attr[3]			= ch->Class;
	p->Attr[4]			= ch->Spell;
	p->Attr[5]			= ch->Tactics;
	
	p->Avility[STR ]	= ch->Str;		// 1118
	p->Avility[CON ]	= ch->Con;
	p->Avility[DEX ]	= ch->Dex;
	p->Avility[WIS ]	= ch->Wis;
	p->Avility[INT ]	= ch->Int;
	p->Avility[MOVP]	= ch->MoveP;
	p->Avility[CHA ]	= ch->Char;
	p->Avility[ENDU]	= ch->Endu;
	p->Avility[MOR ]	= ch->Moral;
	p->Avility[LUCK]	= ch->Luck;
	p->Avility[WSPS]	= ch->wsps;
	
	p->money			= ch->Money;
	//< CSD-010907	
	/*
	p->hp				= ch->Hp;
	p->hpmax			= ch->HpMax;
	p->mp				= ch->Mana;
	p->mpmax			= ch->ManaMax;
	p->hungry			= ch->Hungry;
	p->hungrymax		= ch->HungryMax;
	*/
	p->nLife	= ch->Hp;
	p->nMaxHp = ch->HpMax;
	p->nMana = ch->Mana;
	p->nMaxMp = ch->ManaMax;
	p->nHungry	= ch->Hungry;
	p->nMaxHungry = ch->HungryMax;
	//> CSD-010907
	p->condition		= ch->Condition;
	
	
	p->sprno			= ch->SprNo;
	p->x				= ch->X;
	p->y				= ch->Y;
	
	p->acc_equip1		= ch->accessory[0] ;
	p->acc_equip2		= ch->accessory[1] ;
	p->acc_equip3		= ch->accessory[2] ;
	p->acc_equip4		= ch->accessory[3] ;
	
	
	
	/*	
	short int		Str   ;				//  힘
	short int		Con   ;				//  건강
	short int		Dex   ;				//	민첩성
	short int		Wis   ;				//	지혜
	short int		Int   ;				//	지능
	short int		MoveP ;				//	이동력
	short int		Char  ;				//	매력
	short int		Endu  ;				//  저향력
	short int		Health;				//	체력
	short int		Moral ;				//	사기
	short int		Luck  ;				//	행운
	short int		wsps  ;
	
	*/	
	/*	
	p->nCharacterData[GENDER]		= ch->Gender   ;
	p->nCharacterData[FACE]			= ch->Face   ;
	p->nCharacterData[ARIGENENT]		= ch->   ;
	p->nCharacterData[CLASS]			= ch->Wis   ;
	p->nCharacterData[SPELL]			= ch->Int   ;
	p->nCharacterData[TACTICS_MAN]	= ch->MoveP ;
	p->nCharacterData[TACTICS_WOMAN] = ch->Ch]			= ch->Endu  ;
	*/								
	ch->MoveSx = ch->X / TILE_SIZE;
	ch->MoveSy = ch->Y / TILE_SIZE;
	
	memcpy(p->mapname, ch->MapName, 20);
	
	//	 p->peacests		= (unsigned char)ch->Peacests;		// 0410  사용하지 않음...
	p->sight			=				 ch->Sight;
	
	p->bodyr			= (unsigned char)ch->BodyR;
	p->bodyg			= (unsigned char)ch->BodyG;
	p->bodyb			= (unsigned char)ch->BodyB;
	
	p->clothr			= (unsigned char)ch->ClothR;
	p->clothg			= (unsigned char)ch->ClothG;
	p->clothb			= (unsigned char)ch->ClothB;
	
	p->Age				= (unsigned char)ch->Age;			// 1118
	
	p->openhouse		= ch->openhouse;
	p->reserved_point	= ch->reserved_point;				// 1221
	
	p->viewtype			= ch->viewtype;
	
	p->social_status	= ch->social_status;
	memcpy( &p->nation, &ch->name_status, sizeof( DWORD));				// 1004 YGI
	p->fame				= ch->fame;
	p->nk3				= ch->nk[ N_VYSEUS];
	p->nk4				= ch->nk[ N_ZYPERN];
	p->nk6				= ch->nk[ N_YILSE];
	p->NWCharacter		= ch->NWCharacter;			// 010915 LTS
	//< CSD-011006
	memcpy(p->aStepInfo, ch->aStepInfo, sizeof(p->aStepInfo));
	//< CSD-011006
}	

/*#define CMD_CHAR_INFO_MAGIC				5004
typedef struct char_info_magic{	
unsigned char magic[ 200 ];
}t_char_info_magic;

  #define CMD_CHAR_INFO_SKILL				5003
  
	typedef struct char_info_skill{	
	unsigned char skill[ 200 ];
	}t_char_info_skill;
	*/
	
	
	void SendItemInventory( int count, t_connection c[], int cn )		//1218
	{
		int i = count /3,j=count %3;
		
		t_packet packet;
		packet.h.header.type = CMD_CHR_ITEM_INFO_0;
		packet.h.header.size = sizeof(t_chr_item_info0 );
		
		packet.u.chr_item_info0.ar0 = i;
		packet.u.chr_item_info0.ar1 = j;
		memcpy( (unsigned char *)packet.u.chr_item_info0.inv, 
			(unsigned char *)c[ cn].chrlst.inv[i][j],	sizeof( ItemAttr ) * 8 );
		
		QueuePacket( c, cn, &packet, 1);
	}
	
	// 8개..
	void SendItemEquip( t_connection c[], int cn )
	{
		t_packet packet;
		
		packet.h.header.type = CMD_CHR_ITEM_INFO_1;
		{
			memcpy( (unsigned char *)packet.u.chr_item_info1.equip, 
				(unsigned char *)c[ cn].chrlst.equip,	sizeof( ItemAttr ) * 8 );
		}
		packet.h.header.size = sizeof(t_chr_item_info1 );
		QueuePacket( c, cn, &packet, 1);
	}
	
	void SendItemQuick( t_connection c[], int cn )
	{
		t_packet packet;
		
		packet.h.header.type = CMD_CHR_ITEM_INFO_2;
		{
			memcpy( (unsigned char *)packet.u.chr_item_info2.quick, 
				(unsigned char *)c[ cn].chrlst.quick,	sizeof( ItemAttr ) * 6 );
		}
		packet.h.header.size = sizeof(t_chr_item_info2 );
		QueuePacket( c, cn, &packet, 1);
	}
	/*#define CMD_CHAR_INFO_MAGIC				5004
	typedef struct char_info_magic{	
	unsigned char magic[ 200 ];
	}t_char_info_magic;
	
	  #define CMD_CHAR_INFO_SKILL				5003
	  
		typedef struct char_info_skill{	
		unsigned char skill[ 200 ];
		}t_char_info_skill;
	*/
	
	void SendCharInfoMagic( t_connection c[], int cn )
	{
		t_packet packet;
		
		packet.h.header.type = CMD_CHAR_INFO_MAGIC;
		{
			if( c[cn].chrlst.Spell == 0 ) // Wizard Spell..
				memcpy( packet.u.char_info_magic.magic, c[ cn].chrlst.Ws, 200 );
			else 
				memcpy( packet.u.char_info_magic.magic, c[ cn].chrlst.Ps, 200 );
		}
		packet.h.header.size = sizeof( t_char_info_magic );
		QueuePacket( c, cn, &packet, 1);
	}
	
	void SendCharInfoSkill( t_connection c[], int cn )
	{
		t_packet packet;
		
		packet.h.header.type = CMD_CHAR_INFO_SKILL;
		{
			memcpy( packet.u.char_info_skill.skill, c[ cn].chrlst.Skill, 200 );
		}
		packet.h.header.size = sizeof( t_char_info_skill);
		QueuePacket( c, cn, &packet, 1);
	}
	
	
	
	void SendCharInfotac_skillEXP( t_connection c[], int cn )
	{
		t_packet packet;
		
		packet.h.header.type = CMD_CHAR_INFO_TAC_SKILL_EXP;
		{
			memcpy( packet.u.char_info_tac_skillexp.tac_skillEXP, c[ cn].chrlst.tac_skillEXP, 13 * sizeof( DWORD ) );
		}
		packet.h.header.size = sizeof( t_char_info_tac_skillexp );
		QueuePacket( c, cn, &packet, 1);
	}
	
	
	void SendCharInfoBasic( int cn, short int kind, DWORD data )
	{
		t_packet packet;
		
		/*	if( cn == 0 || cn == 1 )
		{
		FILE *fp;
		fp = fopen( "SendCharInfoBasic에 01이 들어왔다.txt", "at+" );
		if( fp )
		{
		fprintf( fp, "%d  %d \n", kind, data );
		fclose(fp);
		}
		}
		*/
		/////////////////////////////////////////////////////////////////////////////////////
		//	if( cn == 0 ||  cn == 1 || cn >= 10000 ) return;
		/////////////////////////////////////////////////////////////////////////////////////cn
		packet.h.header.type = CMD_CHAR_INFO_BASIC;
		{
			packet.u.char_info_basic.kind = kind;
			packet.u.char_info_basic.data = data;
		}
		packet.h.header.size = sizeof( t_char_info_basic );
		QueuePacket( connections, cn, &packet, 1);
	}
	
	
	
	
	int InitPartyMemberServerToServer( CHARLIST *ch )		//  이름만 디비에 저장하고 이름만 꺼내온다.
	{
		int i;
		for( i=0; i<6; i++ )
		{
			strcpy( ch->party[i].Name, ch->party_str[i] );
		}
		for( i=0; i<3; i++ )
		{
			strcpy( ch->relation[i].Name, ch->relation_str[i] );
		}
		for( i=0; i<6; i++ )
		{
			strcpy( ch->employment[i].Name, ch->employment_str[i] );
		}
		return 1;
	}
	
	int EndsetPartyMenberForUpdate( CHARLIST *ch )
	{
		int i;
		for( i=0; i<6; i++ )
		{
			strcpy( ch->party_str[i] ,ch->party[i].Name );
		}
		for( i=0; i<3; i++ )
		{
			strcpy( ch->relation_str[i], ch->relation[i].Name );
		}
		for( i=0; i<6; i++ )
		{
			strcpy( ch->employment_str[i], ch->employment[i].Name );
		}
		return 1;
	}
	
	
	
	
	
	
	//######################## login server 용 ##########################
	
	void SendItemIndex( t_connection c[], int cn )		// 배운 아이템 보내주기
	{
		CHARLIST *ch = &c[cn].chrlst;
		t_packet packet;
		packet.h.header.type = CMD_ITEM_INDEX;
		{
			memcpy( packet.u.kein.server_item_index.item, ch->Item, c[cn].chrlst.ItemMax  * sizeof( short int ) );
		}
		packet.h.header.size = sizeof(k_server_item_index);
		QueuePacket(c, cn, &packet, 1);
	}
	void SendDiesease( t_connection c[], int cn )		// diesease 보내주기 
	{		
		CHARLIST *ch = &c[cn].chrlst;
		t_packet packet;
		packet.h.header.type = CMD_SEND_CHAR_DISEASE;
		{	
			for( int i=0; i<6; i++ )
			{
				packet.u.kein.server_disease.disease[i] = ch->disease[i];
			}
		}	
		packet.h.header.size = sizeof(k_server_disease);
		QueuePacket(c, cn, &packet, 1);
	}
	void SendEmployment( t_connection c[], int cn )		// employment 보내주기 //1229
	{
		return;
		/*
		CHARLIST *ch = &c[cn].chrlst;
		int Level, Face, Str, Class, Gender;
		t_packet packet;
		int ret; 
		
		  memset( &packet, 0, sizeof( t_packet ) );
		  packet.h.header.type = CMD_EMPLOYMENT;
		  {	
		  for( int i=0; i<6; i++ ) 
		  {
		  if( ch->employment[i][0] ) ret = GetPartyChar_SQL( ch->employment[i], &Level, &Face, &Str, &Class, &Gender  );
		  if( ret == 1 )
		  {
		  packet.u.kein.server_party.Level[i]	= Level;
		  packet.u.kein.server_party.Gender[i]= Gender;
		  packet.u.kein.server_party.Face[i]	= Face;
		  packet.u.kein.server_party.Str[i]	= Str;
		  packet.u.kein.server_party.Class[i]	= Class;
		  memcpy( packet.u.kein.server_party.name[i], ch->employment[i], sizeof( char ) *31 );
		  }
		  }
		  }	
		  packet.h.header.size = sizeof(k_server_party );
		  QueuePacket(c, cn, &packet, 1);
		*/
		
		
	}
	
	void SendRelation( t_connection c[], int cn )		// 사제 관계보내주기		//1229
	{
		return;
		/*
		CHARLIST *ch = &c[cn].chrlst;
		int Level, Face, Str, Class, Gender;
		t_packet packet;
		int ret; 
		
		  memset( &packet, 0, sizeof( t_packet ) );
		  packet.h.header.type = CMD_RELATION;
		  {
		  for( int i=0; i<3; i++ )
		  {
		  if( ch->relation[i][0] ) ret = GetPartyChar_SQL( ch->relation[i], &Level, &Face, &Str, &Class, &Gender );
		  if( ret == 1 )
		  {
		  packet.u.kein.server_relation.Level[i]	= Level;
		  packet.u.kein.server_relation.Gender[i]	= Gender;
		  packet.u.kein.server_relation.Face[i]	= Face;
		  packet.u.kein.server_relation.Str[i]	= Str;
		  packet.u.kein.server_relation.Class[i]	= Class;
		  memcpy( packet.u.kein.server_relation.name[i], ch->relation[i], sizeof( char ) *31 );
		  }
		  }
		  }
		  packet.h.header.size = sizeof(k_server_relation);
		  QueuePacket(c, cn, &packet, 1);
		*/
	}
	void SendParty( t_connection c[], int cn )			// 파티원 보내주기	//0213 YGI
	{
		CHARLIST *ch = &c[cn].chrlst;
		t_packet packet;
		
		memset( &packet, 0, sizeof( t_packet ) );
		packet.h.header.type = CMD_PARTY;
		{
			for( int i=0; i<6; i++ )
			{
				if( ch->party[i].On ) 
				{
					packet.u.kein.server_party.Level[i]	= ch->party[i].Level;
					packet.u.kein.server_party.Gender[i]= ch->party[i].Gender;
					packet.u.kein.server_party.Face[i]	= ch->party[i].Face;
					packet.u.kein.server_party.Str[i]	= ch->party[i].Str;
					packet.u.kein.server_party.Class[i]	= ch->party[i].Class;
					memcpy( packet.u.kein.server_party.name[i], ch->party[i].Name, sizeof( char ) *31 );
				}
			}
		}
		packet.h.header.size = sizeof(k_server_party );
		QueuePacket(c, cn, &packet, 1);
	}
	
	
	
	
	
	/// 0212 YGI
	int SetMySkill( CHARLIST *ch )		// 일단 기본적으로 알아야하는 스킬 셋
	{
		int i;
		switch( ch->Class ) 
		{
		case WARRIOR :	for(  i=0; i<MAX_SKILLMAIN;i++ )	
							if( SkillTbl[i].Class_Warrior == 1 )
								ch->Skill[i] = 1;
							break;
		case THIEF :	for(  i=0; i<MAX_SKILLMAIN;i++ )
							if( SkillTbl[i].Class_Thief == 1 )
								ch->Skill[i] = 1;
							break;
		case ARCHER :	for(  i=0; i<MAX_SKILLMAIN;i++ )
							if( SkillTbl[i].Class_Archery == 1 )
								ch->Skill[i] = 1;
							break;
		case WIZARD :	for(  i=0; i<MAX_SKILLMAIN;i++ )
							if( SkillTbl[i].Class_Wizard == 1 )
								ch->Skill[i] = 1;
							break;
		case PRIEST :	for(  i=0; i<MAX_SKILLMAIN;i++ )
							if( SkillTbl[i].Class_Priest == 1 )
								ch->Skill[i] = 1;
							break;
		}
		
		switch( ch->Job )
		{
		case J_FAMER		:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_Farmer		== 1 ) ch->Skill[i] = 1; break;
		case J_MINNER		:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_miner		== 1 ) ch->Skill[i] = 1; break;
		case J_FISHER		:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_fisher		== 1 ) ch->Skill[i] = 1; break;
		case J_LUMBERJACK	:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_Lumberjack	== 1 ) ch->Skill[i] = 1; break;
		case J_BUTCHER		:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_Butcher		== 1 ) ch->Skill[i] = 1; break;
		case J_HERB_DIGGER	:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_Herbdigger	== 1 ) ch->Skill[i] = 1; break;
		case J_HERDSMAN		:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_herdman		== 1 ) ch->Skill[i] = 1; break;
		case J_CARPENTER	:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_Carpenter	== 1 ) ch->Skill[i] = 1; break;
		case J_BLACKSMITH	:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_Blacksmith	== 1 ) ch->Skill[i] = 1; break;
		case J_COOKER		:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_Cooking		== 1 ) ch->Skill[i] = 1; break;
		case J_TAILOR		:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_Tailoring	== 1 ) ch->Skill[i] = 1; break;
		case J_BOWCRAFT		:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_Bowcraft_Fletcher == 1 ) ch->Skill[i] = 1; break;
		case J_ALCHEMIST	:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_Alchemy		== 1 ) ch->Skill[i] = 1; break;
		case J_CANDLEMAKER	:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_Candlemaker	== 1 ) ch->Skill[i] = 1; break;
		case J_MERCHANT		:	for(  i=0; i<MAX_SKILLMAIN;i++ ) if( SkillTbl[i].Select_Merchant	== 1 ) ch->Skill[i] = 1; break;
		}
		return 1;
	}
	
	// 0213 YGI
	//int SendPartyInforForGameserver( short int server_id, char para, t_connection c[], short int cn )
	int SendPartyInforForGameserver( short int server_id, char para, char *name, t_connection c[], short int cn )
	{
		t_packet packet;
		int Level, Face, Str, Class, Gender;
		int ret = 0; 
		
		char szName[31];
		ConvertQueryString(name, szName, 31); // Finito prevents sql injection
		
		memset( &packet, 0, sizeof( t_packet ) );
		packet.h.header.type = CMD_PARTY_ACCESS;
		{
			if( name ) ret = GetPartyChar_SQL( name, &Level, &Face, &Str, &Class, &Gender );
			if( ret == 1 )
			{
				packet.u.kein.server_server_party_info.Server_id= server_id;
				packet.u.kein.server_server_party_info.ct		= para;
				packet.u.kein.server_server_party_info.Level	= Level;
				packet.u.kein.server_server_party_info.Gender	= Gender;
				packet.u.kein.server_server_party_info.Face		= Face;
				packet.u.kein.server_server_party_info.Str		= Str;
				packet.u.kein.server_server_party_info.Class	= Class;
			}
			else return 0;
		}
		packet.h.header.size = sizeof( k_server_server_party_info );
		QueuePacket(c, cn, &packet, 1);
		
		return 1;
	}
	
	
	
	// 0218 YGI
	extern void SendOhMyParty( char *my_name, char *party_name );			// 0620 YGI
	int SendPartyInfoOfOtherCharToGameserver( char *other_name, char *my_name, short int server_id, t_connection c[], short int cn )
	{
		char you_party[6][31];
		get_BinaryData_Party( (UCHAR **)you_party, other_name );
		
		int j;
		for( j=0; j<6; j++ )
		{
			if( !strcmp( my_name, you_party[j] ) ) 
				break;
		}
		int ret = 0;
		if( j == 6 ) ret = 0;
		else ret = 1;
		
		if( ret )
		{
			t_packet packet;
			memset( &packet, 0, sizeof( t_packet ) );
			packet.h.header.type = CMD_REQ_PARTY_TOGETHER;
			{
				packet.u.kein.rep_party_together.server_id  = server_id;
				strcpy( packet.u.kein.rep_party_together.party_name, other_name); 
			}
			packet.h.header.size = sizeof( k_rep_party_together );
			QueuePacket(c, cn, &packet, 1);
			
			SendOhMyParty( my_name, other_name );							// 0620 YGI
		}
		
		return 1;
	}
	
	
	
	
	
	// 0224 YGI
	void SendCreateAbility( short int cn )
	{
		CHARLIST *ch = &connections[cn].chrlst;
		if( !ch ) return;
		
		t_packet p;
		p.h.header.type = CMD_CREATE_ABILITY;
		{
		/*
		for( int i=STR; i<= LUCK; i++ )
		{
		plus[i] = rand() % 4;
		}
		p.u.kein.start_create_ability.str  = plus[STR];
		p.u.kein.start_create_ability.dex  = plus[DEX];
		p.u.kein.start_create_ability.con  = plus[CON];
		p.u.kein.start_create_ability.wis  = plus[WIS];
		p.u.kein.start_create_ability.inte = plus[INT];
		p.u.kein.start_create_ability.cha  = plus[CHA];
		p.u.kein.start_create_ability.movp = plus[MOVP];
		p.u.kein.start_create_ability.endu = plus[ENDU];
		p.u.kein.start_create_ability.mor  = plus[MOR];
		p.u.kein.start_create_ability.wsps = plus[WSPS];
		p.u.kein.start_create_ability.luck = plus[LUCK];
			*/
		}
		p.h.header.size = 0  ;
		QueuePacket(connections, cn, &p, 1);
	}
	
	
	
	
	// 0410
	int GetDiceAbility( int DiceNumber )		// 다이스 돌리기
	{
		int dice_count, dice_max;
		dice_count = DiceNumber / 1000;
		dice_max = DiceNumber % 1000;
		
		int ret = 0;
		for( int i=0; i<dice_count ; i++ )
		{
			ret += rand()%dice_max + 1;
		}
		return ret;
	}
	
	// 0410 YGI
	void SendThrowDice( char type, short int cn )
	{
		if( type < 0 || type > 5 ) return;
		
		CHARLIST *ch = &connections[cn].chrlst;
		if( !ch ) return;
		
		ch->Class = type;
		int nAbility[LUCK+1] = {0,};
		
		int num_to_rate[2] = { 1003, 1002 };
		int	class_ability[5][5] = { 
			{ STR,	CON }, 
			{ DEX,	MOVP},
			{ DEX,	CON },
			{ INT,	WSPS},
			{ WIS,	WSPS} 
		};
		
		for( int i=0; i<2; i++ )
		{
			int ability = GetDiceAbility( num_to_rate[i] );		
			nAbility[ class_ability[ch->Class][i] ] = ability;
		}
		
		t_packet p = {0,};
		
		p.h.header.type = CMD_THROW_DICE;
		{
			p.u.kein.start_throw_dice.ability1 = nAbility[ class_ability[ch->Class][0] ];
			p.u.kein.start_throw_dice.ability2 = nAbility[ class_ability[ch->Class][1] ];
		}
		p.h.header.size = sizeof( k_start_throw_dice );
		QueuePacket(connections, cn, &p, 1);
		
		
		int basic_ability[5][11] = 
		{
			{ 50, 10, 30, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 40, 20, 10, 10, 10, 20, 10, 10, 10, 20 },
			{ 10, 50, 20, 10, 10, 10, 20, 10, 10, 10, 10 },
			{ 10, 10, 15, 10, 40, 10, 10, 20, 10, 25, 10 },
			{ 10, 10, 20, 35, 10, 10, 10, 20, 10, 25, 10 },
		};
		
		ch->Str		= basic_ability[type][STR];			// 0229 YGI
		ch->Con		= basic_ability[type][CON];
		ch->Dex		= basic_ability[type][DEX];
		ch->Wis		= basic_ability[type][WIS];
		ch->Int		= basic_ability[type][INT];
		ch->MoveP	= basic_ability[type][MOVP];
		ch->Char	= basic_ability[type][CHA];
		ch->Endu	= basic_ability[type][ENDU];
		ch->Moral	= basic_ability[type][MOR];
		ch->Luck	= basic_ability[type][LUCK];
		ch->wsps	= basic_ability[type][WSPS];
		
		ch->Str		+= nAbility[STR];			// 0229 YGI
		ch->Con		+= nAbility[CON];
		ch->Dex		+= nAbility[DEX];
		ch->Wis		+= nAbility[WIS];
		ch->Int		+= nAbility[INT];
		ch->MoveP	+= nAbility[MOVP];
		ch->Char	+= nAbility[CHA];
		ch->Endu	+= nAbility[ENDU];
		ch->Moral	+= nAbility[MOR];
		ch->Luck	+= nAbility[LUCK];
		ch->wsps	+= nAbility[WSPS];
	}

	//void CheckIfBringableInSQuest(int nbMap, char *charname, short int ClientNumber, short int cn) //Eleval 10/08/09 - To bring ppl back in quest
	//{
	//	int QuestMapID = 0;
	//	if(nbMap == 77 || nbMap == 78)
	//		QuestMapID = 1;
	//	else if(nbMap == 72 || nbMap == 74)
	//		QuestMapID = 2;
	//	else if(nbMap == 75 || nbMap == 76)
	//		QuestMapID = 3;

	//	switch(QuestMapID)
	//	{
	//	case 0:
	//		t_packet packet;
	//		packet.h.header.type = CMD_ASK_SQUEST_TELEPORT;
	//		packet.h.header.size = sizeof(t_ask_squest_tp);
	//		packet.u.ask_squest_tp.questfloor = -1;
	//		packet.u.ask_squest_tp.cn = ClientNumber;

	//		QueuePacket(connections, cn, &packet, 1);

	//		return;
	//		break;
	//	case 1:
	//		if(!g_PeopleInUndeadQuest.empty())
	//		{
	//			for(int i = 0; i < g_PeopleInUndeadQuest.size() ; i++)
	//			{
	//				if(stricmp(charname, g_PeopleInUndeadQuest.at(i).charname) == 0)
	//				{
	//					t_packet packet;
	//					packet.h.header.type = CMD_ASK_SQUEST_TELEPORT;
	//					packet.h.header.size = sizeof(t_ask_squest_tp);
	//					packet.u.ask_squest_tp.questfloor = g_PeopleInUndeadQuest.at(i).questfloor;
	//					packet.u.ask_squest_tp.nbMap = g_PeopleInUndeadQuest.at(i).nbMap;
	//					packet.u.ask_squest_tp.nX = g_PeopleInUndeadQuest.at(i).nX;
	//					packet.u.ask_squest_tp.nY = g_PeopleInUndeadQuest.at(i).nY;
	//					packet.u.ask_squest_tp.cn = ClientNumber;

	//					QueuePacket(connections, cn, &packet, 1);

	//					return;
	//				}
	//			}
	//		}
	//		break;
	//	case 2:
	//		if(!g_PeopleInAbyssQuest.empty())
	//		{
	//			for(int i = 0; i < g_PeopleInAbyssQuest.size() ; i++)
	//			{
	//				if(stricmp(charname, g_PeopleInAbyssQuest.at(i).charname) == 0)
	//				{
	//					t_packet packet;
	//					packet.h.header.type = CMD_ASK_SQUEST_TELEPORT;
	//					packet.h.header.size = sizeof(t_ask_squest_tp);
	//					packet.u.ask_squest_tp.questfloor = g_PeopleInAbyssQuest.at(i).questfloor;
	//					packet.u.ask_squest_tp.nbMap = g_PeopleInAbyssQuest.at(i).nbMap;
	//					packet.u.ask_squest_tp.nX = g_PeopleInAbyssQuest.at(i).nX;
	//					packet.u.ask_squest_tp.nY = g_PeopleInAbyssQuest.at(i).nY;
	//					packet.u.ask_squest_tp.cn = ClientNumber;

	//					QueuePacket(connections, cn, &packet, 1);

	//					return;
	//				}
	//			}
	//		}
	//		break;
	//	case 3:
	//		if(!g_PeopleInBigmazeQuest.empty())
	//		{
	//			for(int i = 0; i < g_PeopleInBigmazeQuest.size() ; i++)
	//			{
	//				if(stricmp(charname, g_PeopleInBigmazeQuest.at(i).charname) == 0)
	//				{
	//					t_packet packet;
	//					packet.h.header.type = CMD_ASK_SQUEST_TELEPORT;
	//					packet.h.header.size = sizeof(t_ask_squest_tp);
	//					packet.u.ask_squest_tp.questfloor = g_PeopleInBigmazeQuest.at(i).questfloor;
	//					packet.u.ask_squest_tp.nbMap = g_PeopleInBigmazeQuest.at(i).nbMap;
	//					packet.u.ask_squest_tp.nX = g_PeopleInBigmazeQuest.at(i).nX;
	//					packet.u.ask_squest_tp.nY = g_PeopleInBigmazeQuest.at(i).nY;
	//					packet.u.ask_squest_tp.cn = ClientNumber;

	//					QueuePacket(connections, cn, &packet, 1);

	//					return;
	//				}
	//			}
	//		}
	//		break;
	//	}

	//	t_packet packet;
	//	packet.h.header.type = CMD_ASK_SQUEST_TELEPORT;
	//	packet.h.header.size = sizeof(t_ask_squest_tp);
	//	packet.u.ask_squest_tp.questfloor = -1;
	//	packet.u.ask_squest_tp.cn = ClientNumber;

	//	QueuePacket(connections, cn, &packet, 1);
	//}

	//void UpdateSQuestFloor(int nbMap, char *charname, int QuestFloor, int nX, int nY, short int cn) //Eleval 10/08/09 - To bring ppl back in quest
	//{
	//	if(QuestFloor == -5)
	//	{
	//		g_PeopleInUndeadQuest.clear();
	//		g_PeopleInAbyssQuest.clear();
	//		g_PeopleInBigmazeQuest.clear();

	//		return;
	//	}
	//	else if(QuestFloor == -99)
	//	{
	//		int QuestMapID = 0;
	//		if(nbMap == 77 || nbMap == 78)
	//			QuestMapID = 1;
	//		else if(nbMap == 72 || nbMap == 74)
	//			QuestMapID = 2;
	//		else if(nbMap == 75 || nbMap == 76)
	//			QuestMapID = 3;

	//		switch(QuestMapID)
	//		{
	//		case 0:
	//			return;
	//			break;
	//		case 1:
	//			if(!g_PeopleInUndeadQuest.empty())
	//			{
	//				for(int i = 0 ; i < g_PeopleInUndeadQuest.size() ; i++)
	//				{
	//					if(stricmp(charname, g_PeopleInUndeadQuest.at(i).charname) == 0)
	//					{
	//						g_PeopleInUndeadQuest.at(i).questfloor = -99;
	//					}
	//				}
	//			}
	//			break;
	//		case 2:
	//			if(!g_PeopleInAbyssQuest.empty())
	//			{
	//				for(int i = 0 ; i < g_PeopleInAbyssQuest.size() ; i++)
	//				{
	//					if(stricmp(charname, g_PeopleInAbyssQuest.at(i).charname) == 0)
	//					{
	//						g_PeopleInAbyssQuest.at(i).questfloor = -99;
	//					}
	//				}
	//			}
	//			break;
	//		case 3:
	//			if(!g_PeopleInBigmazeQuest.empty())
	//			{
	//				for(int i = 0 ; i < g_PeopleInBigmazeQuest.size() ; i++)
	//				{
	//					if(stricmp(charname, g_PeopleInBigmazeQuest.at(i).charname) == 0)
	//					{
	//						g_PeopleInBigmazeQuest.at(i).questfloor = -99;
	//					}
	//				}
	//			}
	//			break;
	//	}
	//	else
	//	{
	//		PeopleInSQuest newComer;
	//		newComer.questfloor = QuestFloor;
	//		newComer.nbMap = nbMap;
	//		newComer.nX = nX;
	//		newComer.nY = nY;
	//		sprintf(newComer.charname, charname);

	//		int QuestMapID = 0;
	//		if(nbMap == 77 || nbMap == 78)
	//			QuestMapID = 1;
	//		else if(nbMap == 72 || nbMap == 74)
	//			QuestMapID = 2;
	//		else if(nbMap == 75 || nbMap == 76)
	//			QuestMapID = 3;

	//		switch(QuestMapID)
	//		{
	//		case 0:
	//			return;
	//			break;
	//		case 1:
	//			g_PeopleInUndeadQuest.push_back(newComer);
	//			break;
	//		case 2:
	//			g_PeopleInAbyssQuest.push_back(newComer);
	//			break;
	//		case 3:
	//			g_PeopleInBigmazeQuest.push_back(newComer);
	//			break;
	//		}
	//	}
	//}