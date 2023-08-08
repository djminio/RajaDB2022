#include "StdAfx.h"
#include "packed.h"
#include "servertable.h"
#include "MAIN.H"
#include "Scrp_exe.H"
#include "ID.h"
#include "SealStone.h"
#include "Debug.h"
#include "mainheader.h"
#include "monitor.h"
#include "Citem.h"
#include "Pay.h"
#include "ChrLog.h"
#include "dragonloginserver2.h"		// 010406 YGI
#include "network.h"
#include "LottoDBMgr.h"
#include "ShopDemon.h"

t_connection	connections[LOGIN_MAX_CONNECTIONS] = {0,};

extern bool CheckRookieServerAble(const int iLv);
extern int CheckIDAutherizing(t_packet &packet, const int cn);

extern HWND g_hWnd;

extern int CheckHandleByKein( t_packet *p, t_connection c[], int cn );		// 0308 YGI

extern int CheckHandleByNationWar(t_packet *p, t_connection c[], int cn );		// 010915 LTS

extern void SendThrowDice( char type, short int cn );	// op_chr_status.cpp
extern void SendCreateAbility( short int cn );
extern void CheckStartMap( t_connection c[], short int cn, int &StartPosition );		// 1004 YGI
extern int	CheckGameMakeTool(char *id, char ip[IP_LENGTH]);	// 020830 YGI

extern int GetUserAge(const char* szID);	// 030929 kyo 
extern bool IsLimitedTime();				// 030929 kyo 

/////////////////////////////////////////////////////////////////////////////////
//
//				User Functions..
//
char	g_LogFName[255];
char	Queue_Out_Buffer[MAX_SERVER_QUEUE_OUT_BUFFER];
char	MapName[ NM_LENGTH];
/////////////////////////////////////////////////////////////////////////////////
//
//				User Functions....
//
//-----------------------------------------------------------------------------

#define MAX_MSG_COUNT   25

static int Msg[ MAX_MSG_COUNT][ MAX_PATH];            
int    MsgCount;

//---------------------------------------------------------------------------------
int QueuePacket( t_connection c[], int cn, t_packet *packet, int type )
{
	char temp[MM_MAX_PACKET_SIZE+6] = {0,};
 	DWORD dwUserID = c[cn].dwUserID;
	DWORD dwLength = HEADER_SIZE + packet->h.header.size;
	
	temp[0] = (BYTE)PTCL_DB_ANSWER;
	memcpy(temp+1,&dwUserID,4);
	memcpy(temp+1+4,packet,dwLength);
	
	if( 1+4+dwLength >= MM_MAX_PACKET_SIZE )
	{
		// it's a big bug.. 
//		_asm int 3;
	}
	else 
	{
		temp[ 1+4+dwLength ]=0;
	}

	g_pServerTable->Send( c[cn].dwConIndex, temp, dwLength+5);
	return true;
}

//---------------------------------------------------------------------------------
int DequeuePacket(t_connection c[], int cn, t_packet *packet, int type)
{
	return 1;
}

//---------------------------------------------------------------------------------


void closeconnection(t_connection c[], int cn, const eCloseConnectionType errnum)
{								
	char temp[5] = {0,};

 	DWORD dwUserID = c[cn].dwUserID;
	
	temp[0] = (BYTE)PTCL_DB_TO_AGENT_REQUEST_DISCONNECT_USER_BY_ID;
	memcpy(temp+1,&dwUserID,4);

	switch( errnum )
	{
	case CCT_ID_NOT_EXIST: 
	case CCT_WRONG_PASSWORD: 
	case CCT_ID_USING_NOW: 
	case CCT_PAYMENT_NEED:
		break;
	case CCT_FORCED:
		{
			::MyLog(LOG_NORMAL, "Forced disconnect [ %s ]", c[cn].id);
		}
		break;
	case CCT_INVALID_CLIENT :	
		{
			::MyLog( LOG_NORMAL, "Invalid Client Version[ %d ]", dwUserID );
		}break;
	case CCT_NORMAL : 
		{
			::MyLog( LOG_NORMAL, "Normal Disconnection[ %d ]", dwUserID );
		}break;
	case CCT_AGENT_ORDER :  
		{
			::MyLog( LOG_NORMAL, "Agent order : Disconnection[ %d ]", dwUserID );
		}break;
	}

	if( !g_pServerTable->Send( c[cn].dwConIndex, temp, 5) )
	{
		MyLog( LOG_NORMAL,"SEND: Failed(to %d)", c[cn].dwConIndex);
	}
}		
		
//---------------------------------------------------------------------------------
int HandleAccepting(t_connection c[], SOCKET lsock)
{		
	return(1);
}		
		
//---------------------------------------------------------------------------------
int HandleReading(t_connection c[], int cn)
{		
	return(1);
}

//---------------------------------------------------------------------------------
int HandleCommand(t_connection c[], DWORD dwIndex, t_packet *packet, DWORD dwUserID, int cn)
{
	const int ttype	= packet->h.header.type;
	switch(ttype)
	{
	case CMD_NONE :
		break;
	case CMD_PING :
		break;
	case CMD_LOST_CONNECTION : 
		closeconnection(c, cn, CCT_NORMAL);
		break;
	case CMD_IM_GAME_SERVER :
		break;
	case CMD_ACCESS_CHAR_DB :		// 010613 YGI
		{
			const int server_id = packet->u.server_access_char_db.server_id;
			char szId[20];
			char szName[20];
			ConvertQueryString(packet->u.server_access_char_db.id, szId, ID_LENGTH); // Finito prevents sql injection
			ConvertQueryString(packet->u.server_access_char_db.name, szName, NM_LENGTH); // Finito prevents sql injection

			memcpy(c[cn].id, szId, ID_LENGTH);
			memcpy(c[cn].name, szName, NM_LENGTH);

			if(GetCharDB_SQL(c, cn) != 1) break;
			if(GetCharGameDB_SQL(c, cn) != 1 )  break;
			LPCHARLIST ch = &c[cn].chrlst;
			if(!CheckRookieServerAble(ch->Level))//021230 lsw
			{
				break;
			}
			ch->server_id = cn;
			// 030923 HK YGI
			int ret = get_BinaryData_from_Chr_Info(	(UCHAR *)ch->Ws, 
											(UCHAR *)ch->Ps, 
											(UCHAR *)ch->Skill, 
											(UCHAR *)ch->skillexp, 
											(UCHAR *)ch->tac_skillEXP, 
											(UCHAR *)var[cn], 						
											(UCHAR *)ch->inv, 
											(UCHAR *)ch->equip, 
											(UCHAR *)ch->quick, 
											(UCHAR *)ch->party, 
											(UCHAR *)ch->relation, 
											(UCHAR *)ch->employment, 
											(UCHAR *)ch->Item, 
											c[cn].id, c[cn].name ) ;
			if( ret != 1 ) break;

			ret = get_BinaryData_from_Chr_Info2 ( (UCHAR *)c[cn].chrlst.bank,  c[cn].id, c[cn].name ) ;
			if( ret != 1 ) break;
			/////////////////////////////
			ResetCharInfo(var[cn], ch);

//			PutEventItem( 2, &c[cn] );		// 이벤트용 아이템 넣어 주기	// BBD 040308	Map서버가 주기로 했음

			int refresh_inventory = CheckEventITem( ch );

			CheckEventJoin(&c[cn].chrlst);			// 020115 LTS

			/////////////////////////////////////////////////////////////////////////////////////
			memset(packet, 0, sizeof(t_packet));

			packet->h.header.type = CMD_ACCEPT_CHAR_DB;
			packet->h.header.size = sizeof(t_server_accept_char_db);
			t_server_accept_char_db *tp = &(packet->u.server_accept_char_db);

			strcpy( tp->name, c[cn].name );// 030923 HK YGI
			tp->server_id	= server_id;
			tp->Level		= ch->Level;
			tp->Exp			= ch->Exp;

			tp->Gender		= ch->Gender;
			tp->Face		= ch->Face;
			tp->nGuildCode	= ch->nGuildCode; // CSD-030324
			tp->Class		= ch->Class;
			tp->Spell		= ch->Spell;
			tp->Job			= ch->Job;		// 0212 YGI

			tp->Str			= ch->Str;
			tp->Con			= ch->Con;
			tp->Dex			= ch->Dex;
			tp->Wis			= ch->Wis;
			tp->Int			= ch->Int;
			tp->MoveP		= ch->MoveP;
			tp->Char		= ch->Char;
			tp->Endu		= ch->Endu;
			tp->Moral		= ch->Moral;

			tp->Money		= ch->Money;
			tp->nLife	= ch->Hp;
			tp->nMaxHp = ch->HpMax;
			tp->nMana = ch->Mana;
			tp->nMaxMp = ch->ManaMax;
			tp->nHungry	= ch->Hungry;
			tp->nMaxHungry	= ch->HungryMax;
			tp->Condition	= ch->Condition;
			tp->SprNo		= ch->SprNo;
			tp->X			= ch->X;
			tp->Y			= ch->Y;
			memcpy( tp->MapName, ch->MapName, NM_LENGTH);
			tp->Peacests	= ch->Peacests;
			tp->Sight		= ch->Sight;

			tp->BodyR		= ch->BodyR;
			tp->BodyG		= ch->BodyG;
			tp->BodyB		= ch->BodyB;

			tp->ClothR		= ch->ClothR;
			tp->ClothG		= ch->ClothG;
			tp->ClothB		= ch->ClothB;

			tp->Age			= ch->Age;
			tp->Luck		= ch->Luck;
			tp->wsps		= ch->wsps;
			memcpy( &tp->nation, &ch->name_status, sizeof( DWORD ) );			// 1004 YGI

			tp->accessory[0]	= ch->accessory[0];
			tp->accessory[1]	= ch->accessory[1];
			tp->accessory[2]	= ch->accessory[2];
			tp->accessory[3]	= ch->accessory[3];
			
			ch->mantle =   ch->equip[ WT_NECK].item_no;
			tp->mantle = ch->mantle;

			tp->bAlive			= ch->bAlive;
			tp->openhouse		= ch->openhouse;
			tp->disease[0]		= ch->disease[0];
			tp->disease[1]		= ch->disease[1];
			tp->disease[2]		= ch->disease[2];
			tp->disease[3]		= ch->disease[3];
			tp->disease[4]		= ch->disease[4];
			tp->disease[5]		= ch->disease[5];
			tp->total_id		= ch->total_id;

			tp->nPoison	= ch->nPoison;
			tp->nCurse = ch->nCurse;
			tp->nFire = ch->nFire;
			tp->nIce = ch->nIce;
			tp->nElect = ch->nElect;
			tp->nHoly = ch->nHoly;
			tp->viewtype		= ch->viewtype;		// 0212 YGI
			tp->social_status	= ch->social_status;
			tp->fame			= ch->fame;
			tp->fame_pk			= ch->fame_pk;		// 010915 LTS		//Fame_PK -> NWCharacter로 교체 DB에는 실제로 NWCharacter의 값이 들어갑니다.		
			tp->NWCharacter		= ch->NWCharacter;	// 010915 LTS
			tp->EventJoin		= ch->EventJoin;	// 020115 LTS
			tp->nUserAge		= 0; //GetUserAge(c[cn].id); // 030929 kyo
  			memcpy(tp->aStepInfo, ch->aStepInfo, sizeof(ch->aStepInfo));
  			if(!QueuePacket(c, cn, packet, 1)){break;}

			/////////////////////////////////////////////////////////////////////////
			memset(packet, 0, sizeof(t_packet));
			t_server_accept_char_game_db *tsac = &(packet->u.server_accept_char_game_db);

			packet->h.header.type = CMD_ACCEPT_CHAR_GAME_DB;
			packet->h.header.size = sizeof(t_server_accept_char_game_db);

			strcpy( tsac->name, c[cn].name );// 030923 HK YGI
			tsac->server_id		= server_id;
			tsac->BankMoney		= ch->BankMoney;	
			memcpy( &tsac->win_defeat, &ch->WinLoseScore, sizeof( DWORD ) );
			tsac->LadderScore = ch->LadderScore;
			tsac->LastLoan		= ch->LastLoan;
			tsac->nk3			= ch->nk[N_VYSEUS];
			tsac->nk4			= ch->nk[N_ZYPERN];
			tsac->nk6			= ch->nk[N_YILSE];
			tsac->killmon		= ch->killmon;
			tsac->killanimal	= ch->killanimal;
			tsac->killpc		= ch->killpc;
			tsac->reserved_point= ch->reserved_point;
			tsac->Tactics		= ch->Tactics;

			if(!QueuePacket(c, cn, packet, 1)) break;

			///////////////////////////////////////////////////////////////////////
			memset(packet, 0, sizeof(t_packet));

			packet->h.header.type = CMD_ACCEPT_BINARY_DATA;
			packet->h.header.size = sizeof(t_server_accept_binary_data);

			packet->u.server_accept_binary_data.server_id = server_id;
			strcpy( packet->u.server_accept_binary_data.name, c[cn].name );// 030923 HK YGI

			memcpy((UCHAR *)packet->u.server_accept_binary_data.Ws, (UCHAR *)ch->Ws, SIZE_OF_WS);
			memcpy((UCHAR *)packet->u.server_accept_binary_data.Ps, (UCHAR *)ch->Ps, SIZE_OF_PS);
			memcpy((UCHAR *)packet->u.server_accept_binary_data.Skill, (UCHAR *)ch->Skill, SIZE_OF_SKILL);
			memcpy((UCHAR *)packet->u.server_accept_binary_data.skillexp, (UCHAR *)ch->skillexp, SIZE_OF_SKILL_EXP);
			memcpy((UCHAR *)packet->u.server_accept_binary_data.tac_skillEXP, (UCHAR *)ch->tac_skillEXP, SIZE_OF_TAC_SKILL_EXP);
			memcpy((UCHAR *)packet->u.server_accept_binary_data.equip, (UCHAR *)ch->equip, SIZE_OF_EQUIP);
			memcpy((UCHAR *)packet->u.server_accept_binary_data.quick, (UCHAR *)ch->quick, SIZE_OF_QUICK);
			memcpy((UCHAR *)packet->u.server_accept_binary_data.party, (UCHAR *)ch->party, SIZE_OF_PARTY);
			memcpy((UCHAR *)packet->u.server_accept_binary_data.relation, (UCHAR *)ch->relation, SIZE_OF_RELATION);
			memcpy((UCHAR *)packet->u.server_accept_binary_data.employment, (UCHAR *)ch->employment, SIZE_OF_EMPLOYMENT);

			if(!QueuePacket(c, cn, packet, 1)) break;

			///////////////////////////////////////////////////////////////////////
			memset(packet, 0, sizeof(t_packet));

			packet->h.header.type = CMD_ACCEPT_SCRIPT_DATA;
			packet->h.header.size = sizeof(t_server_accept_script_data);

			packet->u.server_accept_script_data.server_id = server_id;
			strcpy( packet->u.server_accept_script_data.name, c[cn].name );// 030923 HK YGI
			memcpy((UCHAR *)packet->u.server_accept_script_data.script_var, (UCHAR *)var[cn], SIZE_OF_SCRIPT_VAR);

			if(!QueuePacket(c, cn, packet, 1)) break;

			///////////////////////////////////////////////////////////////////////
			memset(packet, 0, sizeof(t_packet));

			packet->h.header.type = CMD_ACCEPT_INV_DATA;
			packet->h.header.size = sizeof(t_server_accept_inv_data);

			packet->u.server_accept_inv_data.server_id = server_id;
			strcpy( packet->u.server_accept_inv_data.name, c[cn].name );// 030923 HK YGI
			memcpy((UCHAR *)packet->u.server_accept_inv_data.inv, (UCHAR *)ch->inv, SIZE_OF_INV);
			//021030 YGI
			packet->u.server_accept_inv_data.refresh_inventory = refresh_inventory;


			if(!QueuePacket(c, cn, packet, 1)) break;

			///////////////////////////////////////////////////////////////////////
			memset(packet, 0, sizeof(t_packet));

			packet->h.header.type = CMD_ACCEPT_ITEM_DATA;
			packet->h.header.size = sizeof(t_server_accept_item_data);

			packet->u.server_accept_item_data.server_id = server_id;

			strcpy( packet->u.server_accept_item_data.name, c[cn].name );// 030923 HK YGI
			memcpy((UCHAR *)packet->u.server_accept_item_data.Item, (UCHAR *)c[cn].chrlst.Item, SIZE_OF_ITEMINDEX);

			if(!QueuePacket(c, cn, packet, 1)) break;
			
			///////////////////////////////////////////////////////////////////////
			memset(packet, 0, sizeof(t_packet));

			packet->h.header.type = CMD_ACCEPT_BANKITEM_DATA;
			packet->h.header.size = sizeof(t_server_accept_bankitem_data);

			packet->u.server_accept_bankitem_data.server_id = server_id;
			strcpy( packet->u.server_accept_bankitem_data.name, c[cn].name );// 030923 HK YGI
			memcpy((UCHAR *)packet->u.server_accept_bankitem_data.bankitem, (UCHAR *)c[cn].chrlst.bank, SIZE_OF_BANKITEM);
			if(!QueuePacket(c, cn, packet, 1)) break;

			// finito 25/08/07 do not send friend status message if character is GM
			if (c[cn].chrlst.name_status.counselor)
			{
				break;
			}

			// finito 09/08/07 friend status to all maps
			t_packet friendpacket;
			memset(friendpacket.u.FriendStatus.name1, 0, sizeof(friendpacket.u.FriendStatus.name1));
			memset(friendpacket.u.FriendStatus.name2, 0, sizeof(friendpacket.u.FriendStatus.name2));
			ConvertQueryString(c[cn].name, friendpacket.u.FriendStatus.name2, 20); // Finito prevents sql injection
			friendpacket.h.header.type = CMD_FRIEND_STATUS;
			friendpacket.h.header.size = sizeof(t_FriendStatus);
			friendpacket.u.FriendStatus.online = true;

			for( int i=0; i<30; i++ )
			{
				HSTMT		hStmt = NULL;
				RETCODE		retCode;
				SDWORD		cbValue;

				::SQLAllocStmt(hDBC, &hStmt);

				char szQuerry[256];
				sprintf(szQuerry, "select name from friend_list where friend%d = '%s'", i+1, friendpacket.u.FriendStatus.name2);
				retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);
				if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
				{		
					int i = 0;
					retCode = SQLFetch(hStmt);
					while( retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
					{
						retCode = SQLGetData(hStmt, 1, SQL_C_CHAR,	&friendpacket.u.FriendStatus.name1	, 20, &cbValue);
						EatRearWhiteChar(friendpacket.u.FriendStatus.name1);
						g_pServerTable->BroadCastToEveryServer( (char *)&friendpacket, (sizeof(t_header)+friendpacket.h.header.size ), SERVER_TYPE_MAP );
						retCode = SQLFetch(hStmt);
						if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
						{
							continue;
						}
						else if( retCode == SQL_NO_DATA ) 
						{
							continue;
						}
					}	
				}		
				SQLFreeStmt(hStmt, SQL_DROP);		// 0308 YGI
			}			

		}break;
	case CMD_ACCESS_LOGIN :
		{
			::CheckIDAutherizing(*packet,cn);
		}break;
	case CMD_PARTY_ACCESS : 
		{
			::SendPartyInforForGameserver( packet->u.kein.server_req_party_db.server_id, packet->u.kein.server_req_party_db.ct, packet->u.kein.server_req_party_db.name, c, cn );
		}break;
	case CMD_REQ_PARTY_TOGETHER : 
		{
			::SendPartyInfoOfOtherCharToGameserver( packet->u.kein.server_req_party_together.party_name, packet->u.kein.server_req_party_together.my_name, packet->u.kein.server_req_party_together.server_id, c, cn );
		}break;

case CMD_CONNECT_INFO :							// 4개중의 하나의 캐릭터를 선택했다
	{	
		// 캐릭터초기화이후실행 0405 KHS 
		// 0405 YGI	new char
		int is_new_char = 0;
		if( ::GetCharNew(is_new_char, packet->u.client_connect_info.name ) )			// 4월 1일 새롭게 만든 캐릭터 인가?
		{
			if( is_new_char )
			{
				break;
			}// 1: 예전 캐릭터	0: 새로운 캐릭터
		}
		else 
		{
			break;
		}

		if( !CheckIsRealName( connections[cn].id, packet->u.client_connect_info.name ) )
		{
			break;
		}

		// 010301 khs  probide to hacking..
		memset(c[cn].name, 0, NM_LENGTH);
		char szName[20];
		ConvertQueryString(packet->u.client_connect_info.name, szName, 20); // Finito prevents sql injection 
		strcpy(c[cn].name, szName);

		StartMap		= packet->u.client_connect_info.startmap;	
		StartPosition	= packet->u.client_connect_info.startposition;
		
		if( StartMap < 0 || StartMap > 1 )				StartMap = 0;

		if( StartPosition == 99 ) 
		{			
		}			
		else if( StartPosition < 1 || StartPosition > 20 )
		{
			StartPosition = 1;
		}
					
		c[cn].chrlst.startmap		= StartMap;
		c[cn].chrlst.startposition	= StartPosition;
						
		memset(packet, 0, sizeof(t_packet));
		int ret = GetCharDB_SQL(c, cn);
		if( ret )		
		{				
			CheckStartMap( c, cn, StartPosition );		// 1004 YGI
			ret = GetCharGameDB_SQL(c,cn);
		}
		if( c[cn].chrlst.Hp == 0 )
		{	
			c[cn].chrlst.bAlive		= DEAD_; 
			c[cn].chrlst.Condition	= CON_DEATH;
			c[cn].chrlst.viewtype	= VIEWTYPE_GHOST_;
		}	
		else 
		{	
			c[cn].chrlst.bAlive 	= ALIVE_;
			c[cn].chrlst.Condition	= CON_NORMAL;
			c[cn].chrlst.viewtype	= VIEWTYPE_NORMAL_;
		}		
			
		if( c[cn].chrlst.startposition != 99 ) // 원래의 위치에 들어간다. 
		{	
			strcpy( c[cn].mapname, StartMapPosition[ StartMap][ StartPosition ] );
			strcpy( c[cn].chrlst.MapName, StartMapPosition[ StartMap][ StartPosition ] );
		}	
			
		if(ret == 1)
		{	
			//< CSD-030324
			extern void CheckNewGuildCode( CHARLIST *ch );
			CheckNewGuildCode( &c[cn].chrlst );
			//> CSD-030324
			packet->h.header.type = CMD_USER_DB;
			{
				PutPacketCharDB( c, cn, packet );
			}
			packet->h.header.size = sizeof(t_server_user_db_data);
			if(!QueuePacket(c, cn, packet, 1)) break;
		}	
		else // Invalid DB
		{	
			::MyLog(1, "Invalid DB [%s]", c[cn].name);

			packet->h.header.type = CMD_INVALID_DB;
			packet->h.header.size = 0;
			QueuePacket(c, cn, packet, 1);
			break;				
		}					
		break;				
	}
							
	case CMD_CHR_ITEM_INFO_0 :
		{					
			//------------------------------------------------------------
			// Send Char Binary Data
			//------------------------------------------------------------
			get_BinaryData_from_Chr_Info(	(UCHAR *)c[cn].chrlst.Ws, 
											(UCHAR *)c[cn].chrlst.Ps, 
											(UCHAR *)c[cn].chrlst.Skill, 
											(UCHAR *)c[cn].chrlst.skillexp, 
											(UCHAR *)c[cn].chrlst.tac_skillEXP, 
											(UCHAR *)var[c[cn].chrlst.server_id], 						
											(UCHAR *)c[cn].chrlst.inv, 
											(UCHAR *)c[cn].chrlst.equip, 
											(UCHAR *)c[cn].chrlst.quick, 
											(UCHAR *)c[cn].chrlst.party, 
											(UCHAR *)c[cn].chrlst.relation, 
											(UCHAR *)c[cn].chrlst.employment, 
											(UCHAR *)c[cn].chrlst.Item, 
											c[cn].id, c[cn].name ) ;
//			PutEventItem( 1, &c[cn] );		// 이벤트용 아이템 넣어 주기	// BBD 040308	Map서버가 주기로 했음
			SendItemQuick( c, cn ); 

			// 마법을 배우지 않고 모든 마법을 사용하려면 이곳에서  Ws/Ps를 Setting해주면 된다. 
			int i;
			for( i = 0 ; i < 1000 ; i ++)
			{
				if( c[cn].chrlst.Item[i] == 0) break;
			}
			c[cn].chrlst.ItemMax = i;
			SendLearnedItem( c, cn );		// 0730 YGI										
			break;			
		}					
								
	case CMD_CHR_ITEM_INFO_1 : SendItemEquip( c, cn ); break;
	case CMD_CHR_ITEM_INFO_2 : SendItemInventory( packet->u.client_item_inv.count, c, cn ); break;
			
	case CMD_CHAR_INFO_MAGIC : SendCharInfoMagic( c, cn ); break;
	case CMD_CHAR_INFO_SKILL : 
		{
			SendCharInfoSkill( c, cn ); 
			::MyLog(0, "Send [%s]Info to [%s]", c[cn].name, c[cn].id);
		}break;
			
	case CMD_CHAR_INFO_TAC_SKILL_EXP : SendCharInfotac_skillEXP( c, cn ); break;
				
	case CMD_CONNECT_INFO1 :	
		{
			char *map_name = 0;
			int ret = 0;
			if( c[cn].chrlst.startposition == 99 )
			{
				ret = GetMapName_SQL( c, cn); // 001126 KHS
				if( ret == 1 ) map_name = c[cn].mapname;
			}
			else
			{
				map_name = StartMapPosition[ c[cn].chrlst.startmap][c[cn].chrlst.startposition];
			}

			if( map_name )
			{
				ret = 0;
				int port = MapPort( map_name );
				if( port )
				{
					ret = 1;
					packet->u.kein.server_connect_info_kein.data1.port = port;
					ret += CheckEventObject( map_name, &packet->u.kein.server_connect_info_kein.u.data3);
					ret += CheckEventSound( map_name, &packet->u.kein.server_connect_info_kein.u.data3);
				}
			}

			if( ret )
			{	
				//-----------------------------------------------------------------
				//-----------------------------------------------------------------
				packet->h.header.type = CMD_CONNECT_INFO;
				packet->h.header.size = sizeof(t_server_connect_info);
				if( ret == 4 ) // object + sound
				{
					packet->h.header.size += sizeof(k_event_object_sound);
				}
				else if( ret == 3 )		// sound
				{
					packet->h.header.size += sizeof(k_event_sound);
					int sound_no = packet->u.kein.server_connect_info_kein.u.data3.sound_no;
					packet->u.kein.server_connect_info_kein.u.data4.sound_no = sound_no;
				}
				else if( ret == 2 )		// object
				{
					packet->h.header.size += sizeof(k_event_object);
				}
				packet->u.server_connect_info.startposition = c[cn].chrlst.startposition;
				if(!QueuePacket(c, cn, packet, 1))
				{
					break;
				}
			
				//-----------------------------------------------------------------
				c[cn].state = CONNECT_JOIN;
			}
			else // Invalid DB
			{
				::MyLog(0, "Invalid User DB [%s]", c[cn].name);

				packet->h.header.type = CMD_INVALID_DB;
				packet->h.header.size = 0;
				QueuePacket(c, cn, packet, 1);
				break;
			}	
			break;
		}
			
	case CMD_CREATE_CHAR :
	{		
		int ret = CreateChar_SQL(c, cn, packet);
		if(ret == 1)
		{	
			packet->h.header.type = CMD_ACCEPT_CREATE;
			packet->h.header.size = 1;
			packet->u.data[0]= 0 ;
			QueuePacket(c, cn, packet, 1);
			
			::MyLog( 0, "%s (ID:%s) is Generated !", c[cn].id, c[cn].chrlst.Name );
			break;
		}	
		else
		{	
			int is_delete = 1;
			switch( ret )
			{
			case -100 : ::MyLog( 0, "Fail:Character Generation ( Already character %s, ID:%s :%d)", packet->u.client_create_char.name, c[cn].id, ret );
						RecvHackingUser( c[cn].id, packet->u.client_create_char.name, 20009, " ", "Not his Char" );
						is_delete = 0;		// 지우지 않는다.
				break;
			case -30 : ::MyLog( 0, "Fail : Try to make Character but NO ID in chr_log_info ( %s, ID:%s )", packet->u.client_create_char.name, c[cn].id );
				break;
			default  : ::MyLog( 0, "Fail : Character Generation( %s, ID:%s :%d)", packet->u.client_create_char.name, c[cn].id, ret );
				break;
			}

			if(is_delete) 
			{
				delete_char_create_fail( packet->u.client_create_char.name );
			}
		
			packet->h.header.type = CMD_INVALID_DB;
			packet->h.header.size = 1;
			packet->u.data[0]= 0 ;
			QueuePacket(c, cn, packet, 1);

			break;
		}	
		break;
	}		
	case CMD_DELETE_CHAR :
	{	
		const char* szName = packet->u.client_delete_char.szName;
		int ret = DeleteChar_SQL( c[cn].id, szName ,packet->u.client_delete_char.szSecretKeyCode );
		if(ret == 1)
		{	
			MyLog( LOG_NORMAL, "Success : Character Deleted (%s, ID:%s)", szName, c[cn].id );
			RecvHackingUser( c[cn].id, szName, HACKING_DELETE_CHAR_NORMAL_, c[cn].ip_address, "Character Deleted !! Normally.." );
									
			packet->h.header.type = CMD_ACCEPT_DELETE;
			packet->h.header.size = 1;
			packet->u.data[0]= 0 ;
			QueuePacket(c, cn, packet, 1);
			break;
		}	
		else
		{		
			MyLog( LOG_NORMAL, "Delete Fail !");
			
			packet->h.header.type = CMD_INVALID_DB;
			packet->h.header.size = 1;
			packet->u.data[0]= 0 ;
			QueuePacket(c, cn, packet, 1);
			break;
		}		
			
		break;
	}		
	case CMD_ISTHERE_CHARNAME : RecvIsThereCharName( cn, packet->u.client_isthere_charname.name );
		break;
			
	case CMD_CHECK_BETA_TEST : CheckBetaIdTest( cn, packet->u.kein.beta_check_id.id ); break;
	
	case  CMD_SPECIAL_ITEM		:
		RecvUpdateSpecial( &(packet->u.server_special_item)  );					break;
	
	case  CMD_UPDATE_CHAR_DB:	
		{
			int iRet = RecvUpdateCharDB( &(packet->u.update_char_db)  );					
			if(iRet != 1)
			{
				MyLog(0,"RecvUpdateCharDB Failed");
			}
		}break;
	case  CMD_UPDATE_BINARY_DATA0	:	
		{
			int iRet = RecvUpdateBinaryData( &(packet->u.server_update_binary_data0)  );	
			if(iRet != 1)
			{
				MyLog(0,"RecvUpdateBinaryData Failed");
			}
		}break;
	case  CMD_UPDATE_BINARY_DATA1	:	
		{
			int iRet = RecvUpdateBinaryData1( &(packet->u.server_update_binary_data1)  );	
			if(iRet != 1)
			{
				MyLog(0,"RecvUpdateBinaryData1 Failed");
			}
		}break;
	case  CMD_UPDATE_SCRIPT_DATA	:	
		{
			int iRet = RecvUpdateScriptData( &(packet->u.server_update_script_data)  );	
			if(iRet != 1)
			{
				MyLog(0,"RecvUpdateScriptData Failed");
			}
		}break;
	case  CMD_UPDATE_INV_DATA		:	
		{
			int iRet = RecvUpdateInvData( &(packet->u.server_update_inv_data)  );			
			if(iRet != 1)
			{
				MyLog(0,"RecvUpdateInvData Failed");
			} 
		}break;
	case  CMD_UPDATE_ITEM_DATA		:	
		{
			int iRet = RecvUpdateItemData( &(packet->u.server_update_item_data ) );		
			if(iRet != 1)
			{
				MyLog(0,"RecvUpdateItemData Failed");
			}
		}break;
	case  CMD_UPDATE_BANKITEM_DATA	:	
		{
			int iRet = RecvUpdateBankItemData( c, cn, &(packet->u.server_update_bankitem_data));	
			if(iRet != 1)
			{
				MyLog(0,"RecvUpdateBankItemData Failed");
			}
		}break;

	case CMD_REQ_DELETE_USERID :
		onepass.DeleteUsedID_SQL_ForPay( packet->u.gs_req_delete_userid.mapname, packet->u.gs_req_delete_userid.id, 0 ); 
		break;
			
	case CMD_REQ_INSERT_USERID : 
		{
			if(!::CheckIsRealName(packet->u.gs_req_insert_userid.id, packet->u.gs_req_insert_userid.name ) )
			{
				break;
			}
			
			t_packet tp;
			gs_req_insert_userid* pGRIU = &packet->u.gs_req_insert_userid;
			if( ::UpdateLogintablebyChangeMap( pGRIU->id, pGRIU->mapname ))	// LoginTable에 없음.. 즉, 들어갈수 있음..
			{	
				tp.h.header.type = CMD_JOINABLE;
				tp.u.ls_joinable.server_id = packet->u.gs_req_insert_userid.server_id;
				tp.h.header.size = sizeof( t_ls_joinable );
			}	
			else	
			{	
				tp.h.header.type = CMD_UPDATING;
				tp.u.ls_updating.server_id = packet->u.gs_req_insert_userid.server_id;
				tp.h.header.size = sizeof( t_ls_updating );
			}
			::QueuePacket( c, cn, &tp, 1 );
		}break;		
			
	///////////// network2.h을 위해..  0224 YGI ///////////////
	case CMD_CREATE_ABILITY :	SendCreateAbility( cn ); break;
	case CMD_THROW_DICE		:	SendThrowDice( packet->u.kein.client_throw_dice.type, cn ); break;
			
	case CMD_HOW_MANY_IN_MAP :	UpdateTotalMapConnections( packet->u.how_many_in_map.map, packet->u.how_many_in_map.how );
		break;
			
	case CMD_UPDATE_VERY_IMPORTANT_STATUS	:	RecvUpdateCharacterVeryImportantStatus( &(packet->u.update_very_important_status) );
		break;
			
	case CMD_UPDATE_VERY_IMPORTANT_TACTICS  :	RecvUpdateTacticSkillExpData( &(packet->u.update_very_important_tactics ));
		break;
			
	case CMD_ITEM_DURATION_CHANGE :
	case CMD_TACTICS_PARRYING_EXP :
	case CMD_REQ_PARTY_MEMBER	  : 
	case CMD_LEVELUP_POINT		  :
	case CMD_DELETE_ITEM		  : 
		
				MyLog( LOG_NORMAL,  "No Useful Protocol...%d from %d", packet->h.header.type, cn) ;
				
		break;
		
	case CMD_SEALSTONEFROMKING	:
				RecvSealStoneFromKing( packet->u.sealstone_fromking.nation );
		break;
		
	case CMD_SEALSTONE_STATUS	:
				RecvSealStoneStatus( packet );
		break;
		
	case CMD_NATION2NATION_RELATION :
				RecvNation2NationRelation( cn, &(packet->u.nation2nation_relation) );
		break;



	case CMD_HACKING_USER :
		{
				t_hacking_user *tp = &(packet->u.hacking_user );
				RecvHackingUser( tp->id, tp->name, tp->type, tp->ip, tp->cause );
		}
		break;

	case CMD_RARE_ITEM_MAKE_LOG :
		{
				RecvRareItemMakeLog( &packet->u.rare_item_make_log );
		}
		break;
	case CMD_SET_COMMANDER :						// 010915 LTS
	case CMD_SET_WARFIELD_POSSESSION :
	case CMD_DELETE_EVENT_JOIN :					// 020115 LTS
	case CMD_SAVE_WARNO :							// LTS NEW NATIONWAR
		CheckHandleByNationWar(packet,c,cn);
		break;
//<soto-030504
	case CMD_NEW_EVENT: if(LottoDBMgr())LottoDBMgr()->RecvNewEvent(&packet->u.Lotto_Info,cn);
		break;
	case CMD_WINNER_CHECK: if(LottoDBMgr())LottoDBMgr()->RecvWinnerCheck(&packet->u.Check_Winner,cn);
		break;
	case CMD_DEL_LOTTO_USER:
		{
			if (LottoDBMgr())
			{
				LottoDBMgr()->RecvDelUser(&packet->u.Check_Winner, cn);	// BBD 040127 인자추가
			}

			break;
		}
	case CMD_LOTTERY_INFO: if(LottoDBMgr())LottoDBMgr()->RecvLottery(&packet->u.Lotto_Info,cn);
		break;
	case CMD_CHECK_WINNER_MENU: if(LottoDBMgr())LottoDBMgr()->RecvCheckOpenWinnerMenu(&packet->u.Lotto_Winner_Menu,cn);
		break;
//>soto-030504
//<soto-HK
	case CMD_CAN_BUY: if(LottoDBMgr())
					  {
						  if(LocalMgr.IsAbleNation(TAIWAN | HONGKONG | CHINA))
						  {
							  if(GetShopDemon() != NULL)
							  {
								  DebugPrintf("GetShopDemon() Request CMD_CAN_BUY");
								  GetShopDemon()->RecvCanBuyLotto(&packet->u.Lotto_Buy,cn);
							  }
							  else
							  {
								  DebugPrintf("GetShopDemon() is NULL =====> 	 CMD_CAN_BUY");
							  }
						  }
						  else
						  {
								LottoDBMgr()->RecvCanBuyLotto(&packet->u.Lotto_Buy,cn);
						  }
					  }
		break;
	case CMD_LOTTO_BUY: if(LottoDBMgr())
						{
							if(LocalMgr.IsAbleNation(TAIWAN | HONGKONG | CHINA))
							{
								if(GetShopDemon() != NULL)
								{
									DebugPrintf("GetShopDemon() Request CMD_LOTTO_BUY");
									GetShopDemon()->RecvLottoBuy(&packet->u.Lotto_Buy,cn);
								}
								else
								{
									DebugPrintf("GetShopDemon() is NULL =====> 	 CMD_LOTTO_BUY");								
								}
							}
							else
							{
								
								LottoDBMgr()->RecvLottoBuy(&packet->u.Lotto_Buy);
							}
						}
						else
						{
														
						}
		break;
//>soto-HK
//<soto-Lotto추가
	case CMD_LOTTO_SEEK:
		{
			if(LottoDBMgr())
			{
				LottoDBMgr()->RecvLottoSeek(&packet->u.Lotto_Seek,cn);
			}
		}
		break;
//>soto-Lotto추가.
	default : 
		{		// 0308 YGI
			int msg = CheckHandleByKein( packet, c, cn );
			if(msg == 1)
			{
				break;
			}
			else 
			{	
				if(HandleCommand2(c, dwIndex, packet, dwUserID, cn))//020505 lsw 
				{
					break;
				}
				else
				{
					MyLog( LOG_NORMAL,  "ERROR : Unknown Protocol(%d) dwIndex:%d, dwUserID:%d, cn:%d ", packet->h.header.type, dwIndex, dwUserID, cn );
					return msg;
				}
			}
		}
	}		
				
			if( debug_SavePacketExeTimeIng() )
			{
				if( ttype != CMD_NONE )
				{		
					{	
						DWORD t = ViewCheckRoutine( 9999 );
						if( t < 30 )
						{
							Debug( "%2d:%d:%d %20s[%20s] Recv : %5d- %3d\n", g_hour,g_min,g_sec, c[cn].id, c[cn].name, ttype, t );
						}
						else if( t < 100 )
						{
							Debug( "%2d:%d:%d %20s[%20s] Recv : %5d--- %3d\n", g_hour,g_min,g_sec, c[cn].id, c[cn].name, ttype, t );
						}
						else if( t  < 200 )
						{
							Debug( "%2d:%d:%d %20s[%20s] Recv : %5d------ %3d\n",  g_hour,g_min,g_sec,c[cn].id, c[cn].name, ttype, t );
						}
						else
						{
							Debug( "%2d:%d:%d %20s[%20s] Recv : %5d---------- %3d\n", g_hour,g_min,g_sec, c[cn].id, c[cn].name, ttype, t );
						}
					}
				}
			}
	
	
	return(1);
}

//-----------------------------------------------------------------------------
//acer7
int CheckMyCode( int code, char *mystring )
{
	static int count = strlen( MY_STRING );

	//::MyLog( 0, "MY_CODE : [ %d ] - MY_STRING[ %s ] ", code, mystring ); 
	if(!LocalMgr.IsAbleMyCode(code)) {return false;}//021007 lsw
	if( strncmp( MY_STRING, mystring, count ) != 0 ) return false;

	return true;
}

void SendCMD_ACCEPT_LOGIN(const int cn, const int iRemainDay)
{
	if( cn < 0 || cn >= LOGIN_MAX_CONNECTIONS){return;}

	t_connection *pCN = &connections[cn];

	t_packet packet;
	packet.h.header.type = CMD_ACCEPT_LOGIN;
	packet.h.header.size = sizeof(t_server_accept_login);

	packet.u.server_accept_login.server_id		= cn;
	packet.u.server_accept_login.remained_day	= iRemainDay;
	::strcpy( packet.u.server_accept_login.id, pCN->id );
	GetCharactersBasicInfoInID_SQL( pCN->id, &packet );

	pCN->state = CONNECT_LOGIN;
	
	//::Log_LogIn( g_mon+1, g_day, g_hour, g_min, g_sec, pCN->id );
	::Log_LogIn( pCN->id, pCN->ip_address );
	::QueuePacket(connections, cn, &packet, 1);
}

void SendCMD_USED_ID(const int cn, const int iCallType)
{
	if( cn < 0 || cn >= LOGIN_MAX_CONNECTIONS){return;}

	t_connection *pCN = &connections[cn];

	t_packet packet;
	
	packet.h.header.type = CMD_USED_ID;
	packet.h.header.size = 0;
	
	::MyLog( 0, "ID('%s'):IP('%s') is Using Now!! (CallType = %d)", pCN->id, pCN->ip_address, iCallType);
	::QueuePacket(connections, cn, &packet, 1);
			
	WORD wPort = 0;	
	DWORD dwID = 0;	
	DWORD dwServerSetNum = 0;
	if( CheckUsedID_SQL(pCN->id, &wPort, &dwID, &dwServerSetNum ) == 1 )
	{	//	Modified by chan78 at 2000/02/19 :: 서버세트가 일치하는 경우에만 에이전트로 접속종료를 요구한다.
		//	서버세트가 일치하지 않는 경우에는 그 사용자가 다른 서버세트에서 나갈때까지 접속이 불가능해진다.
		if( dwServerSetNum == g_pServerTable->GetServerSetNum() )
		{
			if( !SendRemoveUserToAgent( pCN->id, wPort, dwID )  )
			{
				::MyLog(0, "FAILED : SendRemoveUserToAgent  %d, %d, %d", pCN->id, wPort, dwID);
			}
		}
	}
	::closeconnection( connections, cn, CCT_ID_USING_NOW ); // Try to Access with Using ID..
}

int CheckIDAutherizing(t_packet &packet, const int cn)
{
	if(cn >= LOGIN_MAX_CONNECTIONS){return 0;}//커넥션

	t_connection *pCN = &connections[cn];

	const int code		= packet.u.ClientAccessLogin.mycode;
	char *szMyString	= packet.u.ClientAccessLogin.mystring;
	const int version	= packet.u.ClientAccessLogin.version;
	const WORD port		= packet.u.ClientAccessLogin.wPort;

	::memcpy(pCN->id,	packet.u.ClientAccessLogin.id, ID_LENGTH);
	::memcpy(pCN->pw,	packet.u.ClientAccessLogin.pw, PW_LENGTH);
	
	::strcpy(pCN->ip_address,	packet.u.ClientAccessLogin.ip);
	pCN->myconnectedagentport	= port;

	//MyLog(LOG_NORMAL, "GM_TOOL_VERSION : [%d]", version);

	const bool bIsGMTool = ((version != GM_TOOL_VERSION)?true:false);
	if(bIsGMTool)
	{
		if(!::CheckGameMakeTool(pCN->id, pCN->ip_address))	// 020830 YGI
		{
			packet.h.header.type = CMD_INVALID_VERSION;
			packet.h.header.size = 0;
			::QueuePacket(connections, cn, &packet, 1);

			::closeconnection( connections, cn, CCT_INVALID_CLIENT );
			MyLog( 0, "Not GM_TOOL ip MY_CODE : ID[ %s ] - IP[ %s ] ", pCN->id, pCN->ip_address );
			return 0;
		}
	}

	if( !::CheckMyCode( code, szMyString ) ) 
	{
		packet.h.header.type = CMD_INVALID_VERSION;
		packet.h.header.size = 0;
		::QueuePacket(connections, cn, &packet, 1);
		::closeconnection( connections, cn, CCT_INVALID_CLIENT );

		::MyLog( 0, "Not match MY_CODE : ID[ %s ] - IP[ %s ] ", pCN->id, pCN->ip_address ); 
		return 0;
	}
	
	if(packet.u.ClientAccessLogin.Foo != 0x03)
	{
		packet.h.header.type = CMD_INVALID_VERSION;
		packet.h.header.size = 0;
		::QueuePacket(connections, cn, &packet, 1);
		::closeconnection( connections, cn, CCT_INVALID_CLIENT );

		return 0;
	}

	DWORD id_index = 0;
	LoginInfoPay in ={0,};

	in.index		=	id_index;		

	::memcpy(in.UserID, packet.u.ClientAccessLogin.User_ID ,ID_LENGTH);
	::strcpy(in.id,		pCN->id);
	::strcpy(in.pw,		pCN->pw);
	::strcpy(in.ip,		pCN->ip_address);

	// 030929 kyo << 
	if( LocalMgr.IsAbleNation(THAI) )
	{
		if( onepass.CheckLimitedAgeAndTime(in.id) )
		{// he is underage.
			::MyLog(0, "ID Is Not permited. ID:('%s') AGE:('%d')", in.id, ::GetUserAge(in.id) );

			packet.h.header.type = CMD_INVALID_AGE;
			packet.h.header.size = 0;
			::QueuePacket(connections, cn, &packet, 1);
			::closeconnection( connections, cn, CCT_AGE_NOT_PERMIT ); 
			return 0;
		}
	}
	// 030929 kyo >>
	
	OUTPUT Output		=	onepass.OnePassID(cn,in,bIsGMTool);
	int ret				=	Output.nRet;//로그인 할 수 있다 없다의 판별
	const int iBillType	=	Output.nType;
	
	//if(LocalMgr.IsFreeBeta())//021007 lsw
	//{
		if(COnePass::BT_NEED_PAY == ret)
		{
			ret = COnePass::BT_FREE;
		}
	//}
	
	switch(ret)
	{
	case COnePass::BT_WRONG_ID:
		{
			::MyLog(0, "ID Is Not Exist. ID:('%s') PW:('%s')", pCN->id, pCN->pw);

			packet.h.header.type = CMD_INVALID_ID;
			packet.h.header.size = 0;
			::QueuePacket(connections, cn, &packet, 1);
			::closeconnection( connections, cn, CCT_ID_NOT_EXIST ); 
		}break;
	case COnePass::BT_WRONG_PW:
		{
			::MyLog(0, "User Enter Wrong PassWord ID:('%s') PW:('%s')", pCN->id, pCN->pw);

			packet.h.header.type = CMD_INVALID_PW;
			packet.h.header.size = 0;
			::QueuePacket(connections, cn, &packet, 1);
			::closeconnection( connections, cn, CCT_WRONG_PASSWORD ); 
		}break;
	case COnePass::BT_NEED_PAY: // -3 : 돈내!...		//2001/01/28 ZHH
		{
			::MyLog(0, "User Payment Need!! ID:('%s') PW:('%s') Called by CheckIDAutherizing()", pCN->id, pCN->pw);

			packet.h.header.type = CMD_INVALID_PAY;
			packet.h.header.size = 0;
			::QueuePacket(connections, cn, &packet, 1);

			::closeconnection( connections, cn, CCT_PAYMENT_NEED );
		}break;
	case COnePass::BT_WAIT_BILLING_MSG:
		{	//빌링 메세지를 기다립니다. 아무 처리도 하지 않습니다.
			break;
		}
	case COnePass::BT_FREE:
	default:
		{
			const int ret_checkusedid = onepass.SelectUsedID_SQL_ForPay(in.id);
			if( ret_checkusedid )//사용중인 유저
			{			
				::SendCMD_USED_ID(cn,0);
				return 0;
			}
			else
			{	
				onepass.InsertUsedID_SQL_ForPay(" ", in.id, in.ip, in.UserID, iBillType, port, pCN->dwUserID);
				::SendCMD_ACCEPT_LOGIN(cn,ret);
				return 1;
			}
		}break;
	}
	return 0;
}

int	SendYesorNo( char *ID,			//[11]; //user'ID
				 char *type,		//[2]; //type=P or M
				 long point,		//user's Points(using in type=P)
				 char *expiredata,	//[9];  //User's expire data(using in type=M) EX:20001220
				 int success)		//if login or logout success
{
	t_packet packet;
	char UserID[20]= {0,};
	::strcpy(UserID,ID);
	
	int cn,ret=10;

	for(cn=2;cn<LOGIN_MAX_CONNECTIONS;cn++)
	{
		if(strlen(connections[cn].id)>0)
		{
			if(!strcmp(connections[cn].id,UserID))
			{
				break;
			}
		}
	}
	
	if(cn==LOGIN_MAX_CONNECTIONS)
	{
		return 0;
	}

	t_connection *pCN = &connections[cn];

	if(success==1)		//로그인 성공.( 누군가 쓰지 않는다면)
	{
		const int port = pCN->myconnectedagentport;
		const int ret_checkusedid = onepass.InsertUsedID_SQL_ForPay(" ", pCN->id, pCN->ip_address , "  " , (int)type, port, pCN->dwUserID );
		
		if( !ret_checkusedid ) 
		{
			::SendCMD_USED_ID(cn,1);
			return 0;
		}
		else	
		{	
			::SendCMD_ACCEPT_LOGIN(cn,ret);
			return 1;	
		}
	}
	else//로그인 실패. 아이디와 패스워드는 맞으므로 남은것은 돈내는 것 뿐.
	{			
		::MyLog(0, "User Payment Need!! ID:('%s') PW:('%s') Cause = '%d' Called by SendYesorNo()", pCN->id, pCN->pw, success);
		
		packet.h.header.type = CMD_LOGIN_FAIL_MASSAGE;
		packet.h.header.size = sizeof( client_login_fail_reason );
		packet.u.client_login_fail_reason.cPaytype = memicmp("P",type,2) == 0 ? 0 : 1;	//Point면 0 정액이면 1
		packet.u.client_login_fail_reason.cReserverdData = 0;
		packet.u.client_login_fail_reason.dwType = success;
		packet.u.client_login_fail_reason.dwPoint = point;
		
		::sprintf( packet.u.client_login_fail_reason.szExpireDate, expiredata);
		::QueuePacket(connections, cn, &packet, 1);
		::closeconnection( connections, cn, CCT_PAYMENT_NEED ); // 돈 안냈음 
		return 0;
	}
}

