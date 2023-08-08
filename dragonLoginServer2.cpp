#include "StdAfx.h"

#include "MAIN.H"
#include "Scrp_exe.H"
#include "Citem.h"
#include "dragonloginserver2.h"
#include "map.h"
#include <direct.h>	// 021008 YGI
#include "Id.h" //Thralas
#include "ServerTable.h"
#include "MailMgr.h"


/////////////////////////////////////////////////////////////////////////////////////////
char *public_bbs;

extern NPCLev_to_Exp NPC_Lev_Ref[]; // CSD-030306
t_mapinfo MapInfo[ MAX_MAP_];
extern TKeinMap< CGuildMarkImage > g_GuildMarkImage;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int CheckHandleByKein( t_packet *p, t_connection c[], int cn )
{
	switch( p->h.header.type )
	{
	case CMD_LOGIN_GET_BOX_ITEM			:	RecvGetBoxItem( p->u.kein.req_login_server_box_open.box_id, p->u.kein.req_login_server_box_open.server_id, cn, c ); break;
	case CMD_PUT_BOX_ITEM				:	ReSendBoxItemEach( &p->u.kein.login_put_box_item ); break;
		
	case CMD_LOGIN_PREACH_NAME			:	RecvPreachName( &p->u.kein.loginserver_preach_name, cn, c ); break;
	case CMD_LOGIN_PREACH_NAME_OK		:	RecvPreachNameOk( +10, &p->u.kein.loginserver_preach_name ); break;
	case CMD_LOGIN_PREACH_NAME_CANCEL	:	RecvPreachNameOk( -10, &p->u.kein.loginserver_preach_name ); break;
	case CMD_LOGIN_EVANGELIST_CREATE	:	UpdateEvaName( p->u.kein.login_sql_evangelist_create.my_name , p->u.kein.login_sql_evangelist_create.eva_name ); break;
	case CMD_LOGIN_EVANGELIST_DELETE	:	UpdateEvaName( p->u.kein.login_sql_evangelist_delete.my_name, "" ); break;
	case CMD_CHECK_NEW_CHAR				:	SendNewCharResult( p->u.kein.check_new_char.name, cn ); break;
		
	case CMD_GET_GOD_TABLE				:	SendGodTable( cn ); break;
	case CMD_CHAR_UPDATE_DATA_BY_KEIN	:	RecvUpdateCharByKein( &p->u.kein.char_update_data ); break;
	case CMD_GET_CHARINFO_BY_KEIN		:	SendGetCharInfoByKein( &p->u.kein.req_chr_info_etc, cn ); break;
	case CMD_SEND_EAR_MESSAGE_OTHER		:	SendEachGameServerForEarMessage( &p->u.kein.login_send_ear_message, cn );	break;	// ±Ó¼Ó¸»À» À§ÇØ °¢ °ÔÀÓ ¼­¹ö·Î Àü¼Û ÇØº»´Ù.
	case CMD_SEND_EAR_MESSAGE_OK		:	RecvEarMessageOk( &p->u.kein.send_ear_message_ok_to_login ); break;
	case CMD_SEND_EAR_MESSAGE_RESULT	:	RecvEarMessageResult( &p->u.kein.send_ear_message_result ); break;
	case CMD_GAME2LOGIN_CHECK_NAME		:	RecvCheckName( p->u.kein.loginserver_to_gameserver_ear_message.name, p->u.kein.loginserver_to_gameserver_ear_message.server_id, cn ); break;		// ±¸Á¶Ã¼ º°·Á¾¸
		
	case CMD_GAME2LOGIN_MOVING_ITEM		:	CheckMoveItem( &p->u.kein.moving_item ); break;
	
	case CMD_CHANGE_MAP_DATA1			:
	case CMD_CHANGE_MAP_DATA2			:
	case CMD_CHANGE_MAP_DATA3			:
	case CMD_CHANGE_MAP_DATA4			:
	case CMD_CHANGE_MAP_DATA5			:
	case CMD_CHANGE_MAP_DATA6			:
	case CMD_CHANGE_MAP_DATA7			:
	case CMD_CHANGE_MAP_DATA8			:
	case CMD_CHANGE_MAP_DATA9			:	RecvChangeMapData1( p ); break;
		
	case CMD_ACCESS_JOIN_KEIN			:	RecvChangeLogintableByChangemap( p->u.gs_req_insert_userid.id, p->u.gs_req_insert_userid.mapname, p->u.gs_req_insert_userid.server_id, cn ); break;
	case CMD_IF_DOUBLE_BOX_THEN_DELETE	:	RecvDoubleBoxFind( p->u.kein.game2login_recall_box_item.box_id,p->u.kein.game2login_recall_box_item.server_id, cn ); break;
	case CMD_REQ_FAITH_UP				:	RecvFaithUp( p->u.kein.req_faith_up.name, p->u.kein.req_faith_up.up_point ); break;
		
	case CMD_CALL_PUBLIC_BBS			:	SendPublicBbsEach( p->u.kein.server_id.server_id, cn ); break;
	case CMD_HUNTER_REGIST				:	RecvHunterRegist( &p->u.kein.hunter_regist2 ); break;
	case CMD_GET_HUNTER_LIST			:	RecvGetHunterList( p->u.kein.game_login_hunter_list.list_id, p->u.kein.game_login_hunter_list.server_id, cn); break;
	case CMD_KILL_HUNTER_LIST			:	RecvKillHunter( p->u.kein.kill_hunter_list_login.list_id, p->u.kein.kill_hunter_list_login.hunter_name, p->u.kein.game_login_hunter_list.server_id, cn );break;
		
	case CMD_DELETE_BOX_ITEM			:	DeleteBox( p->u.kein.default_dword ); break;
		
	case CMD_RESET_JOB					:	RecvResetJob( p, cn ); break;
	case CMD_SELECT_NATION				:	RecvSelectNation( p, cn ); break;
	case CMD_EXIST_NAME					:	RecvExistName( p, cn ); break;
	case CMD_ISSAME_MY_NATION			:	RecvExistNameForNation( p, cn ); break;
		
	case CMD_REGIST_CANDIDATE			:	RecvRegistCandidate( p, cn ); break;
	case CMD_IS_THIS_MAN_CANDIDATE		:	isThisManCandidate( p, cn ); break;	// ÈÄº¸ µî·Ï°¡´ÉÇÑ Ä³¸¯ÅÍÀÎÁö ¾Æ´ÑÁö
	case CMD_CHECK_VOTE					:	CheckVote( p, cn ); break;
		
	case CMD_SET_VALUE_OF_VOTE			:	GetVoteValue( cn ); break;
	case CMD_VOTE_GAME2LOGIN			:	CheckAndUpdateVote( p, cn ); break;
		
	case CMD_REQ_VOTE_SCORE				:	RecvVoteScore( p, cn ); break;
	case CMD_SEND_ALL_MSG				:	RecvNationMsg( p, cn ); break;
		
	case CMD_YOU_ARE_KING_LOG2LOG		:	SendYouAreKingLog2Client( p->u.kein.default_name, CMD_YOU_ARE_KING_LOG2CLIENT ); break;
	case CMD_YOU_ARE_NO_KING_LOG2LOG	:	SendYouAreKingLog2Client( p->u.kein.default_name, CMD_YOU_ARE_NO_KING_LOG2CLIENT ); break;
		
	case CMD_GUILD_JOIN_SERVER			:	CheckGuildJoin( p, cn ); break;
	case CMD_GUILD_ALL_MSG				:	SendGuildAllMsg( p, cn ); break;
	case CMD_GM_REGIST					:	RecvGmRegist( p ); break;
	case CMD_BBS_ALL					:	RecvReturnGameServer( p ); break;		// °í´ë·Î °ÔÀÓ¼­¹ö·Î ¸ðµÎ µ¹·ÁÁà¹ö¸°´Ù.
	case CMD_REP_STOP_WAR_REFUSAL_TO_LOGIN	:	RecvRepStopWarRefusal( p ); break;	// ÈÞÀü ¿äÃ» °ÅÀý
	case CMD_REQ_STOP_WAR_TO_LOGIN			:	RecvReqStopWar( p, cn ); break;	// ÈÞÀü ¿äÃ»
	case CMD_REP_STOP_WAR_ACCEPT_TO_LOGIN	:	RecvRepStopWarAccept( p ); break;
		
	case CMD_REQ_SALVATION_MONEY			:	RecvReqSalvationMoney( p, cn ); break;		// ±âºÎ±Ý ¿äÃ»
	case CMD_SALVATION_MONEY				:	RecvInsertSalvation(p, cn ); break;			// ±âºÎÇÑ°É ÀúÁ¤
		
	case CMD_EAT_CHOCOLATE					:	RecvEatChocolate( p, cn ); break;
	case CMD_PAY_RUMOR						:	RecvCheckChocolate( p, cn ); break;
	case CMD_OPENSCHOOL_DATA				:	RecvSaveOpenSchoolEvent( p, cn ); break;
		
	case CMD_GUILD_EXIT_COMMAND_GLOBAL		:	RecvExitGiild( p, cn ); break;
		
	case CMD_EAT_CANDY						:	RecvCheckCandy( p ); break;
		
	case CMD_UPDATE_LADDER_SCORE			:	RecvUpdateLadderScore( p ); break;
	case CMD_REQ_RANK_LADDER				:	RecvReqRankLadder( p, cn ); break;
		
		
	case CMD_REQ_SEARCH_RANK_LADDER			:	RecvSearchRankLadder( p, cn ); break;
	case CMD_SAVE_NATION_INFO				:	SaveNationInfo_SQL( &p->u.kein.save_nation_info ); break;
		
		// Å×½ºÆ® ¿ë ÆÐÅ¶..
	case CMD_SAVE_GUILD_MARK_IMAGE			:	UpdateGuildMark( 1, p->h.header.size-2, (BYTE *)p->u.kein.send_db_direct_map.data ); break;
		
		// ½ÇÁ¦ ÀÌ¹ÌÁö ÀúÀå ÆÐÅ¶
	case CMD_REGIST_GUILD_MARK				:	RecvRegistGuildMark( p, cn ); break;
	case CMD_REGIST_GUILD_IMSI				:	RecvRegistGuild_DB( p, cn ); break;
	case CMD_REQ_GUILD_EXPLAIN				:	RecvReqGuildExplain( p, cn ); break;
		
	case CMD_REGIST_GUILD					:	RecvRegistGuild( p, cn ); break;
	case CMD_REQ_GUILD_IMAGE				:	SendGuildImage( p, cn ); break;
		
	case CMD_SAVE_GUILD_MEMBER_LIST			:	RecvSaveGuildMemberList( p ); break;
	case CMD_UPDATE_GUILD_MAIL_ID			:	RecvUpdateGuildMailId( p ); break;
	case CMD_GUILD_MASTER_AND_SUBMASTER		:	RecvGuildMasterAndSubMaster(p, cn ); break;
		
	case CMD_REGIST_GUILD_CHECK				:	RecvRegistGuildCheck( p, cn ); break;
	case CMD_CHECK_SUB_MASTER				:	RecvCheckSubMaster( p, cn ); break;
	case CMD_CHANGE_GUILD_DEGREE			:	RecvChangeGuildDegree( p, cn ); break;
	case CMD_DELETE_GUILD					:	RecvChangeDeleteGuild( p ); break;
		
	case CMD_CHANGE_COLOR					:	RecvChangeColor( p ); break;
	case CMD_CHECK_SALVATION_NAME			:	CheckSalvationName( p, cn ); break;
	case CMD_REFRESH_SALVATION_NAME			:	RecvDeleteSalvation( ); break;
	case CMD_GET_NAME_GUILD_MEMBER_LIST		:	RecvGetNameOfGuildMemberList( p, cn ); break;
	case CMD_GET_GUILD_NOTICE				:	RecvGetGuildNotice( p, cn ); break;
	case CMD_SEND_GUILD_NOTICE				:	RecvRegistGuildNotice( p, cn );break;
		
	case CMD_REGIST_FRIEND					:	RecvRegistFriend( p, cn );break;
	case CMD_GET_FRIEND						:	RecvGetFriend( p, cn ); break;
	case CMD_SERVER_EXIT_GAME				:	RecvLogout( p ); break;
	case CMD_DELETE_FRIEND					:	DeleteFriend( p, cn ); break;
		
	case CMD_CHECK_GUILD_NAME				:	RecvCheckGuildName( p, cn ); break;
	case CMD_CHECK_GUILD_OTHER_CHARACTER	:	RecvCheckGuildOthercharacter( p, cn ); break;
		
	case CMD_ADD_EVENT_ITEM					:	RecvAddEventItem( p, cn ); break;
		
	case CMD_GET_GUILD_ITEM_FIRST			:	RecvGetGuildItemFirst( p, cn ); break;	// ±æµå ¾ÆÀÌÅÛ ¸ñ·Ï
	case CMD_GET_GUILD_ITEM					:	RecvGetGuildItem( p, cn ); break;		// ±æµå ¾ÆÀÌÅÛ ¸ñ·Ï °¡Á®¿À±â
	case CMD_PUT_GUILD_ITEM					:	RecvPutGuildItem( p ); break;
	case CMD_GET_GUILD_ITEM_MAP				:	RecvGetGuildItemMap( p, cn ); break;		// ½ÇÁ¦ ¾ÆÀÌÅÛÀ» °¡Á®¿Â´Ù.
		
	case CMD_GET_GUILD_BOX_MONEY			:	RecvGetGuildBoxMoney( p, cn ); break;
	case CMD_CHECK_GUILD_BOX_MONEY			:	RecvCheckGuildBoxMoney( p, cn ); break;
		
	case CMD_ADD_GUILD_BOX_MONEY			:	RecvUpdateGuildBoxMoney(); break;
		
	case CMD_GET_GUILD_ITEM_COUNT			:	RecvGetGuildItemCount( p, cn ); break;
		
	case CMD_CHANGE_GUILD_MASTER			:	RecvChangeGuildMaster( p, cn ); break;
	case CMD_CHANGE_GUILD_MASTER_SUB		:	RecvChangeGuildMasterBySubMaster(p, cn ); break;
	case CMD_REGIST_SUB_GUILD_MASTER		:	RecvRegistSubMaster( p, cn ); break;
	case CMD_GUILD_HOUSE_INFO				:	RecvGuildHouseInfo( p, cn ); break;
	case CMD_CHANGE_GUILDHOUSE_INFO			:	RecvChangeGuildHouseInfo( p, cn ); break;
	case CMD_CHECK_GUILD_HOUSE				:	RecvCheckGuildHouse(); break;		// ÇÏ·ç¿¡ ÇÑ¹ø
		
		//021030 YGI
	case CMD_SAVE_AMOUNT_EVENT_NPC_ITEM		:	RecvSaveAmountEventNpcItem( p ); break;
		
		//021107 YGI
	case CMD_CHECK_EVENT_SCRIPT_ITEM		:	RecvCheckEventScriptItem( p, cn ); break;
	case CMD_CHECK_EVENT_MOVE_MAP			:	RecvCheckEventMoveMap( p, cn ); break;
		
	case CMD_SAVE_EVENT_MAPMOVE_NOW			:	RecvSaveEventMapMoveNow( p, cn ); break;
	case CMD_GET_TREASURE_MAP_DETAIL_DB:
		{	// 040105 YGI
			RecvGetTreasureMapAttr( p, cn );
			break;		
		}
	case CMD_SERVER_KILLPC:	break;

	case CMD_CHECK_GUILDS			:	RecvCheckCharGuild( p, cn ); break;
	case CMD_SEX_CHANGE				:	RecvSexChange( p, cn ); break; //Eleval - Sex Change
	//case CMD_ASK_SQUEST_TELEPORT	:	RecvAskSQuestTeleport( p, cn ); //Eleval 10/08/09 - To bring ppl back in quest
		
		break;
	default	:
		{
			return(-31);
		}
	}
	return 1;
}






/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
void RecvGetBoxItem( DWORD box_id, short int server_id, short int gameserver_id, t_connection c[] )
{
	t_packet packet = {0, };
	
	packet.h.header.type = CMD_LOGIN_GET_BOX_ITEM ;
	{
		packet.u.kein.login_server_box_open.server_id = server_id;
		for( int i=0; i<MAX_BOX_ITEM; i++ )
		{
			int ret = GetBoxItem_SQL( box_id, i, &packet.u.kein.login_server_box_open.box_item[i] );		// °ª °¡Áö°Ü¿À ½ÇÆÐ¸¦ ÇØµµ Àü¼ÛÇØÁà¾ß ÇÑ´Ù.
		}
		packet.u.kein.login_server_box_open.box_id= box_id;
		//AccessBoxData( box_id );
	}
	packet.h.header.size = sizeof( k_login_server_box_open );
	QueuePacket( c, gameserver_id, &packet, 1 );
}

void RecvDoubleBoxFind( DWORD box_id, short int server_id, short int gameserver_id )
{
	t_packet packet;
	packet.h.header.type = CMD_IF_DOUBLE_BOX_THEN_DELETE ;		// ¶È°°Àº ¹Ú½º°¡ ÀÖ´Â °æ¿ì ÇÏ³ª¸¦ Áö¿ö¹ö¸°´Ù.
	packet.u.kein.game2login_recall_box_item.box_id= box_id;	
	packet.u.kein.game2login_recall_box_item.server_id= server_id;	
	packet.h.header.size = sizeof( k_game2login_recall_box_item );
	
	g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
}

void RecvPreachName( k_loginserver_preach_name *data,  short int gameserver_id, t_connection c[] )
{
	int ret;
	t_packet packet = {0, };
	
	if( CheckName_SQL( data->name ) )
	{
		int believe, faith;
		ret = GetBelieveAndFaith_SQL( believe, faith, data->name );
		if( ret )
		{
			if( believe == data->believe_god ) packet.u.kein.loginserver_preach_name_result.result = 1;		// ¼º°ø
			else packet.u.kein.loginserver_preach_name_result.result = 3; // ±× »ç¶÷Àº ±× ½ÅÀü¿¡ µî·ÏµÇ¾î ÀÖÁö ¾Ê´Ù.
		}
		else packet.u.kein.loginserver_preach_name_result.result = 4;		// Äõ¸®¹®ÀÌ ½ÇÇàÀÌ ¾È µÈ»óÅÂ
	}
	else
		packet.u.kein.loginserver_preach_name_result.result = 2;	// ±×·± »ç¶÷ ¾ø´Ù.
	
	packet.h.header.type = CMD_LOGIN_PREACH_NAME ;
	{
		packet.u.kein.loginserver_preach_name_result.server_id= data->server_id;
		//		packet.u.kein.loginserver_preach_name_result.result= data->server_id;
		packet.u.kein.loginserver_preach_name_result.believe_god= data->believe_god;
		sprintf( packet.u.kein.loginserver_preach_name_result.name ,data->name );
	}
	packet.h.header.size = sizeof( k_loginserver_preach_name_result);
	QueuePacket( c, gameserver_id, &packet, 1 );
}

void RecvPreachNameOk( int plus, k_loginserver_preach_name *data )		// ÀüµµÇÑ »ç¶÷ ½Å¾Ó½É ¿Ã·ÁÁÖ±â
{
	int ret;
	int faith, believe;
	
	ret = GetBelieveAndFaith_SQL( believe, faith, data->name );
	if( ret )
	{
		if( believe == data->believe_god ) 
		{
			faith += plus; // ´õÇØÁÖ´Â ±âº» ¼öÄ¡
			if( faith > 1000 ) faith = 1000;
			if( faith < 0 ) faith = 0 ;
			UpdateFaith_SQL( (short int )faith, data->name );
		}
	}
	return;
}

void SendNewCharResult( char *name, short int cn )	
{
	int is_new;
	int ret;
	
	ret = GetCharNew( is_new, name );
	
	t_packet packet;
	if( is_new || ret == 0)							// 1Àº ±¸ Ä³¸¯ÅÍ, 0Àº »õ·Î¿î Ä³¸¯ÅÍ
		packet.h.header.type = CMD_CHECK_NEW_CHAR_NOT;
	else 
		packet.h.header.type = CMD_CHECK_NEW_CHAR_OK;
	
	packet.h.header.size = 0;
	QueuePacket( connections, cn, &packet, 1 );
}

void SendGodTable( short int cn )
{
	t_packet packet;
	
	packet.h.header.type = CMD_GET_GOD_TABLE ;
	packet.h.header.size = sizeof( k_get_god_table );
	{
		for( int i=0; i<MAX_GOD; i++ )
		{
			int ret;
			ret = GetGodMeetingTime( packet.u.kein.get_god_table.day,  
				packet.u.kein.get_god_table.month,
				packet.u.kein.get_god_table.year, i );
			
			if( ret ) QueuePacket( connections, cn, &packet, 1 );
		}
	}
}

void RecvUpdateCharByKein( k_char_update_data *p )
{
	UpdateCharStatusByKein( p );
}

void SendGetCharInfoByKein( k_req_chr_info_etc *p, short int cn )
{
	k_get_char_info t;
	
	GetCharDataStatusByKein( &t, p->name );
	
	t_packet packet;
	packet.h.header.type = CMD_GET_CHARINFO_BY_KEIN;
	{
		strcpy( packet.u.kein.get_char_info.name, p->name );	// 030923 HK YGI
		packet.u.kein.get_char_info.server_id		= p->server_id;
		packet.u.kein.get_char_info.believe_god		= t.believe_god;
		packet.u.kein.get_char_info.faith			= t.faith;
		packet.u.kein.get_char_info.god_cast_level	= t.god_cast_level;
	}
	
	packet.h.header.size = sizeof( k_get_char_info );
	QueuePacket( connections, cn, &packet, 1 );
}

void SendEachGameServerForEarMessage( k_login_send_ear_message *p, short int game_server )
{
	if( !CheckName_SQL( p->recv_name ) ) return;		// ±×·± ³ð Á¸ÀçÇÏÁö ¾ÊÀ½.
	
	t_packet packet;
	packet.h.header.type = CMD_SEND_EAR_MESSAGE_OTHER;
	{
		packet.u.kein.login_to_gameserver_ear_message.server_id = p->server_id;
		packet.u.kein.login_to_gameserver_ear_message.nation = p->nation;
		strcpy( packet.u.kein.login_to_gameserver_ear_message.recv_name, p->recv_name );
		strcpy( packet.u.kein.login_to_gameserver_ear_message.send_name, p->send_name );
		strcpy( packet.u.kein.login_to_gameserver_ear_message.message, p->message );
		packet.u.kein.login_to_gameserver_ear_message.game_server = connections[game_server].server_check;
	}
	packet.h.header.size = sizeof( k_login_to_gameserver_ear_message ) - 200 + strlen( p->message );
	g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
}

void RecvEarMessageOk( k_send_ear_message_ok_to_login *p )		// ¾î¶² °ÔÀÓ¼­¹ö¿¡¼­ ¼º°øÀûÀ¸·Î ¸Þ½ÃÁö¸¦ º¸³Â´Ù´Â È¸½Å
{
	if( !p->gameserver_port ) return;
	for(int i = 0; i < LOGIN_MAX_CONNECTIONS; i ++)		
	{
		if( connections[i].server_check == p->gameserver_port )
		{
			t_packet packet;
			packet.h.header.type = CMD_SEND_EAR_MESSAGE_OK;
			{
				packet.u.kein.loginserver_to_gameserver_ear_message.server_id = p->server_id;
				strcpy( packet.u.kein.loginserver_to_gameserver_ear_message.name, p->name );
			}
			packet.h.header.size = sizeof( k_loginserver_to_gameserver_ear_message );
			//			QueuePacket( connections, p->gameserver_port, &packet, 1 );
			QueuePacket( connections, i, &packet, 1 );
			break;
		}
	}
}

void RecvEarMessageResult( k_send_ear_message_result *p )
{
	t_packet packet;
	packet.h.header.type = CMD_LOGIN2GAME_EAR_MESSAGE_RESULT;
	{
		packet.u.kein.login2game_ear_message_result.send_server_id = p->send_server_id;
		packet.u.kein.login2game_ear_message_result.ret = p->ret;
	}
	packet.h.header.size = sizeof( k_login2game_ear_message_result );
	
	for(int i = 0; i < LOGIN_MAX_CONNECTIONS; i ++)
	{
		if(connections[i].server_check == p->send_game_server )
		{
			QueuePacket( connections, i, &packet, 1 );
			return;
		}
	}
}

void RecvCheckName( char *name, short int server_id, short int cn )
{
	int ret_type;
	if( CheckName_SQL( name ) ) {ret_type = CMD_THEREIS_CHARNAME ;}
	else {ret_type = CMD_THEREIS_NO_CHARNAME;}
	
	t_packet packet;
	packet.h.header.type = CMD_GAME2LOGIN_CHECK_NAME;
	{
		packet.u.kein.login2game_ear_message_result.send_server_id= server_id;
		packet.u.kein.login2game_ear_message_result.ret = ret_type;
	}
	packet.h.header.size = sizeof( k_login2game_ear_message_result );
	QueuePacket( connections, cn, &packet, 1 );
}


void CheckMoveItem( k_moving_item *p )
{
	char *pos_type[20] = { "HAND", "INV", "EQUIP", "QUICK", "BANK", "BOX", "MAKE", "OTHER_CH", "CHARACTER", "GROUND", "USE", "BUY", "SELL", "DELETE", "EXCHANGE" };
	
	FILE *fp;
	char temp[MAX_PATH];
	sprintf( temp, ".\\logout_item\\%s_¾ÆÀÌÅÛÀÌµ¿.txt", p->name );
	fp = fopen( temp, "at+" );
	if( !fp ) return;
	
	CItem *t = ItemUnit( p->item );
	if( !t ) 
	{
		fclose( fp );
		return;
	}
	
	if( t->GetRbutton() == DIVIDE_ITEM )
		fprintf( fp, "¾ÆÀÌÅÛ:%s, ¼ö·®:%9ld, À§Ä¡:[%8s] ===> À§Ä¡:[%8s]     µ·:[%8ld]\n", t->GetHanName(), p->item.attr[IATTR_MUCH], pos_type[p->source_type], pos_type[p->dest_type], p->money );
	else
	{
		WORD dur_curr, dur_max;
		GetItemDuration( p->item, dur_curr, dur_max );
		fprintf( fp, "¾ÆÀÌÅÛ:%s, Dur :%4d/%4d, À§Ä¡:[%8s] ===> À§Ä¡:[%8s]     µ·:[%8ld]\n", t->GetHanName(), dur_curr, dur_max, pos_type[p->source_type], pos_type[p->dest_type], p->money );
	}
	
	fclose( fp );
}

void RecvGuildMailTitle( int guild_code, short int server_id, short int game_id )
{
	k_guild_mail mail[12] = {0, };
	
	int max = GetGuildMailTitle(guild_code, mail );
	if( max > 0 )
	{
		t_packet packet;
		packet.h.header.type = CMD_REP_RECV_GUILD_MAIL_TITLE;
		{
			packet.u.kein.login_to_game_mail_title.server_id = server_id;
		}
		for( int i=0; i<max; i++ )
		{
			packet.u.kein.login_to_game_guild_mail_title.degree = mail[i].degree;
			packet.u.kein.login_to_game_guild_mail_title.mail_id = mail[i].mail_id;
			packet.u.kein.login_to_game_guild_mail_title.mail_year = mail[i].year;
			packet.u.kein.login_to_game_guild_mail_title.mail_month = mail[i].month;
			packet.u.kein.login_to_game_guild_mail_title.mail_day = mail[i].day;
			strcpy( packet.u.kein.login_to_game_guild_mail_title.mail_name, mail[i].send_name );
			strcpy( packet.u.kein.login_to_game_guild_mail_title.mail_title, mail[i].mail_title );
			
			packet.h.header.size = sizeof( k_login_to_game_guild_mail_title ) - 60 + strlen( mail[i].mail_title );
			QueuePacket( connections, game_id, &packet, 1 );
		}
	}
}

// 020808 YGI --------------------------

extern CServerTable*	g_pServerTable;
void RecvChangeMapData1( t_packet *pPacket )
{
	// CMD_CHANGE_MAP_DATA1
	for(int i = 0; i < LOGIN_MAX_CONNECTIONS; i ++)
	{
		if(connections[i].server_check == pPacket->u.kein.change_map1.game_port )
		{
			QueuePacket( connections, i, pPacket, 1 );
			return;
		}
	}
}


// 010218
void RecvChangeLogintableByChangemap( char *user_id, char *map_name, short int server_id, short int cn )
{
	if( ::UpdateLogintablebyChangeMap( user_id, map_name ))
	{
		t_packet tp;
		tp.h.header.type = CMD_JOINABLE;
		tp.u.ls_joinable.server_id = server_id;
		tp.h.header.size = sizeof( t_ls_joinable );
		
		::QueuePacket( connections, cn, &tp, 1 );
	}
}


void ReSendBoxItemEach( k_login_put_box_item *box )
{
	PutBoxItem_SQL( box->box_id, box->para, &box->item  );
	
	/*	t_packet p;
	p.h.header.type = CMD_RECALL_BOX_ITEM;
	p.u.kein.login_put_box_item = *box;
	p.h.header.size = sizeof( k_login_put_box_item );
	
	  
		for(int i = 0; i < LOGIN_MAX_CONNECTIONS; i ++)
		{
		if( connections[i].socket && connections[i].server_check )
		{
		QueuePacket( connections, i, &p, 1 );
		}
}*/
}


// ÀüµµÇÑ»ç¶÷ÀÌ °ÔÀÓ ¼­¹ö¿¡ ÀÖ´ÂÁö Ã¼Å©ÇØ¼­ Å¬¶óÀÌ¾ðÆ®·Î º¸³»ÁØ´Ù.
void RecvFaithUp( char *name, short int point )
{
	t_packet p;
	p.h.header.type = CMD_REQ_FAITH_UP;
	strcpy( p.u.kein.req_faith_up.name, name );
	p.u.kein.req_faith_up.up_point = point;
	p.h.header.size = sizeof( k_req_faith_up );
	
	g_pServerTable->BroadCastToEveryServer( (char *)&p, (sizeof(t_header)+p.h.header.size ), SERVER_TYPE_MAP );
}

void SendOhMyParty( char *my_name, char *party_name )
{
	t_packet p;
	p.h.header.type = CMD_OH_MY_PARTY;
	
	strcpy( p.u.kein.oh_my_party.my_name, my_name );
	strcpy( p.u.kein.oh_my_party.party_name, party_name );
	
	p.h.header.size = sizeof( k_oh_my_party );
	g_pServerTable->BroadCastToEveryServer( (char *)&p, (sizeof(t_header)+p.h.header.size ), SERVER_TYPE_MAP );
	
}


//////////////////////////////////////////////////////////
//	°øÁö »çÇ×À» µðºñ¿¡¼­ ÀÐ¾î¼­ ÀüÃ¼·Î »Ñ·ÁÁØ´Ù.

void SendLoginToGameServerMessage( int type, char *szTemp )
{
	if( !szTemp ) return;
	t_packet p;
	int len=strlen( szTemp );
	int max = (len / 512)+1;
	
	p.h.header.type = type;
	for( int i=0; i<max; i++ )
	{
		char *temp = szTemp+512*i;
		strncpy( p.u.kein.server_text_default.text, temp ,512 );
		p.u.kein.server_text_default.len = len;
		
		p.h.header.size = sizeof( k_server_text_default );
		g_pServerTable->BroadCastToEveryServer( (char *)&p, (sizeof(t_header)+p.h.header.size ), SERVER_TYPE_MAP );
	}
}

void SendPublicBbs()
{
	GetPublicBbs( &public_bbs );
	SendLoginToGameServerMessage( CMD_LOGIN_TO_GAME_PUBLIC_BBS, public_bbs );
}

void SendLearnedItem( t_connection c[], short int cn )	
{
	t_packet packet;
	
	packet.h.header.type = CMD_SEND_LEARN_ITEM_INDEX;
	{
		packet.u.kein.server_learn_item.item_count = c[cn].chrlst.ItemMax;
		memcpy( packet.u.kein.server_learn_item.item, c[ cn].chrlst.Item,	sizeof( short int ) * c[cn].chrlst.ItemMax );
	}
	packet.h.header.size = sizeof( k_server_learn_item );
	QueuePacket( c, cn, &packet, 1);
}

void SendPublicBbsEach( short int server_id, short int game_id )
{
	GetPublicBbs( &public_bbs );
	if( !public_bbs  ) return;
	
	t_packet p;
	int len=strlen( public_bbs  );
	int max = (len / 512)+1;
	
	p.h.header.type = CMD_CALL_PUBLIC_BBS_ONLY_ONE;
	for( int i=0; i<max; i++ )
	{
		char *temp = public_bbs +512*i;
		strncpy( p.u.kein.server_text_only_one.text, temp ,512 );
		p.u.kein.server_text_only_one.len = len;
		p.u.kein.server_text_only_one.server_id = server_id;
		
		p.h.header.size = sizeof( k_server_text_only_one );
		QueuePacket( connections, game_id, &p, 1 );
	}
}

void RecvHunterRegist( k_hunter_regist2 *p )
{
	int ret = InsertHunterList( p->target_name, p->regist_name, p->money, p->text );
}

void RecvGetHunterList( int list_id, short int server_id, short int game_id)
{
	k_hunter_list list;
	int ret = GetHunterList( list_id, &list, 1 );		// ¾ÆÀÌµð ¹Ù·Î ¹ØÀÇ ³»¿ëÀ» °¡Á®¿Â´Ù.
	if( ret != 1 ) return;
	
	t_packet p;
	p.h.header.type = CMD_SEND_HUNTER_LIST;
	p.u.kein.login_game_hunter_list.server_id = server_id;
	p.u.kein.login_game_hunter_list.list = list;
	p.h.header.size = sizeof( k_login_game_hunter_list )-1000+(strlen(list.text ));
	QueuePacket( connections, game_id, &p, 1 );
}

void RecvKillHunter( int list_id, char *hunter_name, short int server_id, short int game_id )
{
	t_packet p;
	k_hunter_list list;
	int ret = GetHunterList( list_id, &list, 0 );		// ¾ÆÀÌµð·Î ¾ï¼¼½º ÇÑ´Ù.
	if( ret != 1 || !list.index )		// Äõ¸®¹®¿¡ ½ÇÆÐÇß°Å³ª ¸®½ºÆ®ÀÇ ÀÎµ¦½º°¡ ¾øÀ» °æ¿ì 
	{
		p.h.header.type = CMD_KILL_HUNTER_LIST_CANCEL;
		p.u.kein.server_id.server_id = server_id;
		p.h.header.size = sizeof( k_server_id );
		QueuePacket( connections, game_id, &p, 1 );
	}
	else 
	{
		DeleteHunterList( list_id );		// ³»¿ëÀ» »èÁ¦ÇÑ´Ù.
		// °ÔÀÓ¼­¹ö·Î µ·ÇÏ°í ³»¿ëÀ» º¸³»ÁØ´Ù.	// Ã³¸®ÇÑ »ç¶÷¿¡°Ô Á¤º¸¸¦ º¸³»ÁØ´Ù.
		p.h.header.type = CMD_KILL_HUNTER_LIST_OK;
		//			strcpy( p.u.kein.send_kill_hunter_list.target_name, list.target_name);
		//			strcpy( p.u.kein.send_kill_hunter_list.regist_name, list.regist_name);
		p.u.kein.send_kill_hunter_list.money = list.money;
		p.u.kein.send_kill_hunter_list.server_id = server_id;
		p.h.header.size = sizeof( k_send_kill_hunter_list );
		QueuePacket( connections, game_id, &p, 1 );
		
		// °á°ú¸¦ Çö»ó¹ü °Ç »ç¶÷¿¡°Ô ¸ÞÀÏ·Î ¾Ë·Á ÁØ´Ù.
		EatRearWhiteChar( list.regist_name );
		EatRearWhiteChar( list.target_name);
		k_game_to_login_send_mail result;
		//< CSD-030324
		char ini_from[20];
		char ini_title[60];
		char ini_body[1000];

		ini_from[0] = 0;
		ini_title[0] = 0;
		ini_body[0] = 0;

// thai YGI
		if(GetPrivateProfileString("hunter_mail","from","",ini_from,20,MapServerConfigFileName) > 0)
		{
			GetPrivateProfileString("hunter_mail","title","",ini_title,60,MapServerConfigFileName);
			GetPrivateProfileString("hunter_mail","body","",ini_body,1000,MapServerConfigFileName);
		}

		if( ini_from[0] && ini_title[0] && ini_body[0] )
		{
			strcpy( result.send_name, ini_from ); 
			strcpy( result.uni.recv_name, list.regist_name );
			strcpy( result.title, ini_title );
			sprintf( result.body, ini_body, list.target_name, hunter_name, list.target_name, list.regist_name, list.money );
		}
		else
		{		
			if(LocalMgr.IsAbleNation(CHINA))//021007 lsw
			{
				strcpy( result.send_name, "Ó¶±ø¾üÍÅ" ); 
				strcpy( result.uni.recv_name, list.regist_name );
				strcpy( result.title, "[¹«¸æ] ×¥µ½Í¨¼©·¸£¡" );
				sprintf( result.body, 	"×¥µ½ÁËÄúÏë×¥µÄÐüÉÍ·¸ '%s'¡£\n"
					"[%s] ×¥µ½ÁË '%s'£¬ËùÒÔµÃµ½ÁË %s Éè¶¨µÄÐüÉÍ½ð %d¡£\n"
					"ÒÔºóÎÒÃÇÓ¶±ø¾üÍÅ»¹ÊÇ»á¾¡Á¦×½ÄÃÐüÉÍ·¸¡£"
					, list.target_name, hunter_name, list.target_name, list.regist_name, list.money );
				
			}
			else if(LocalMgr.IsAbleNation(TAIWAN|HONGKONG))//021007 lsw
			{
				strcpy( result.send_name, "¶Ä§L­x¹Î" ); 
				strcpy( result.uni.recv_name, list.regist_name );
				strcpy( result.title, "[¤½§i] §ì¨ì³q½r¥Ç¡I" );
				sprintf( result.body, 	"§ì¨ì¤F±z·Q§ìªºÄa½à¥Ç '%s'¡C\n"
					"[%s] §ì¨ì¤F '%s'¡A©Ò¥H±o¨ì¤F %s ?©wªºÄa½à? %d¡C\n"
					"¥H«á§Ú?¶Ä§L­x¹ÎÁÙ¬O?ºÉ¤O??Äa½à¥Ç¡C"
					, list.target_name, hunter_name, list.target_name, list.regist_name, list.money );
			}
			else
			{
				strcpy( result.send_name, "¿ëº´±æµå Àå" );
				strcpy( result.uni.recv_name, list.regist_name );
				strcpy( result.title, "[°øÁö] Çö»ó¹ü °Ë°Å!" );
				sprintf( result.body, "´Ô²²¼­ ¿äÃ»ÇÏ½Å Çö»ó¹ü \"%s\" ¸¦ °Ë°ÅÇÏ¿´½À´Ï´Ù.\n"
					"[%s]´Ô²²¼­ \"%s\"´ÔÀ» °Ë°ÅÇÔÀ¸·Î½á %s ´Ô²²¼­ °É¾îµÐ Çö»ó±Ý %d¸¦ È¹µæÇÏ¼Ì½À´Ï´Ù.\n"
					"´ÙÀ½¿¡µµ ¿ì¸® ¿ëº´ ±æµå¿¡¼­´Â ÃÖ¼±À» ´ÙÇØ Çö»ó¹üµéÀ» Àâµµ·Ï ÇÏ°Ú½À´Ï´Ù."
					, list.target_name, hunter_name, list.target_name, list.regist_name, list.money );
				
			}
		}
		//> CSD-030324
		if( g_MailMgr.InsertMail(CMailMgr::GUILD_MAIL, result.uni.recv_name, result.title, result.body, result.send_name ) ) 
		{

		}
	}
}

void DeleteBoxByDeleteCharacter( const char *szName )		// Ä³¸¯ÅÍ¸¦ Áö¿ï¶§ ¹Ú½ºµµ Áö¿î´Ù.//020725 lsw
{
	ItemAttr inv[3][3][8];
	ItemAttr bank[5][3][6];
	int ret = SearchBoxAndDelete( (UCHAR**)inv, (UCHAR**)bank, szName );
	if( ret == 1 )
	{
		int a = 0;
		for( a=0; a<3; a++ )				// inventory
			for( int b=0; b<3; b++)
				for( int c=0; c<8; c++ )
				{
					ItemAttr item = inv[a][b][c];
					if( item.item_no ) 
					{
						CItem *t = ItemUnit( item );
						if( t && t->GetItemKind() == IK_BOX ) 
						{
							DeleteBox( item.attr[IATTR_ID] );
						}
					}
				}
				
				for( a=0; a<5; a++ )				// bank
					for( int b=0; b<3; b++)
						for( int c=0; c<6; c++ )
						{
							ItemAttr item = bank[a][b][c];
							if( item.item_no ) 
							{
								CItem *t = ItemUnit( item );
								if( t && t->GetItemKind() == IK_BOX ) 
								{
									DeleteBox( item.attr[IATTR_ID] );
								}
							}	
						}
	}
}

void RecvResetJob( t_packet *p, short int cn )
{
	int job = p->u.kein.reset_job.job;
	int cls = p->u.kein.reset_job.cls;
	char *name = p->u.kein.reset_job.name;
	
	unsigned char   Skill[200] = {0, };
	DWORD			skillexp[45];
	int var[ _SCRIPT_VARABLE_POINT_ ];
	
	if( job < J_FAMER || job > J_HERB_DIGGER ) return;		// Á÷¾÷¼±ÅÃÀº 6°¡Áö¸¸ °¡´É
	if( cls < WARRIOR || cls > PRIEST )  return;			// Å¬·¹½º Á÷¾÷ ½ºÅ³ ¹è¿ì±â¿¡ °üÇØ...
	
	if( UpdateResetJob_SQL( job, name ) )
	{
		int ret = get_Skill_BinaryData( (UCHAR**)&skillexp, (UCHAR**)&var, name );
		
		//int skill_of_job[15];
		DWORD exp = 0;
		int i;
		for( i=0; i<MAX_SKILLMAIN;i++ ) 
		{
			if(
				( SkillTbl[i].Select_Farmer		== 1 )	||( SkillTbl[i].Select_miner		== 1 )	
				||( SkillTbl[i].Select_fisher		== 1 )	||( SkillTbl[i].Select_Lumberjack	== 1 )	
				||( SkillTbl[i].Select_Butcher		== 1 )	||( SkillTbl[i].Select_Herbdigger	== 1 )	
				||( SkillTbl[i].Select_herdman		== 1 )	||( SkillTbl[i].Select_Carpenter	== 1 )	
				||( SkillTbl[i].Select_Blacksmith	== 1 )	||( SkillTbl[i].Select_Cooking		== 1 )	
				||( SkillTbl[i].Select_Tailoring	== 1 )	||( SkillTbl[i].Select_Bowcraft_Fletcher == 1 )
				||( SkillTbl[i].Select_Alchemy		== 1 )	||( SkillTbl[i].Select_Candlemaker	== 1 )
				||( SkillTbl[i].Select_Merchant		== 1 )	||( SkillTbl[i].MotherSkillType == 27 ) )		// Å×¹ÖÀÏ °æ¿ì¿¡µµ Ã³¸®..
				CheckSkillExp_kein( SkillTbl[i].MotherSkillType, skillexp, exp );
		}
		exp *= 0.4;		// 40 %¸¸ °¡Á® °£´Ù.
		if( exp < 50000 ) exp = 50000;
		switch( job )
		{
		case J_FAMER		:	for(  i=0; i<MAX_SKILLMAIN;i++ ) 
									if( SkillTbl[i].Select_Farmer== 1 ) 
									{
										Skill[i] = 1;
										skillexp[ SkillTbl[i].MotherSkillType ] = exp;
									}
									break;
		case J_MINNER		:	for(  i=0; i<MAX_SKILLMAIN;i++ ) 
									if( SkillTbl[i].Select_miner== 1 ) 
									{
										Skill[i] = 1; 
										skillexp[ SkillTbl[i].MotherSkillType ] = exp;
									}										
									break;
		case J_FISHER		:	for(  i=0; i<MAX_SKILLMAIN;i++ ) 
									if( SkillTbl[i].Select_fisher== 1 ) 
									{
										Skill[i] = 1; 
										skillexp[ SkillTbl[i].MotherSkillType ] = exp;
									}
									break;
		case J_LUMBERJACK	:	for(  i=0; i<MAX_SKILLMAIN;i++ ) 
									if( SkillTbl[i].Select_Lumberjack== 1 ) 
									{
										Skill[i] = 1;
										skillexp[ SkillTbl[i].MotherSkillType ] = exp;
									}
									break;
		case J_BUTCHER		:	for(  i=0; i<MAX_SKILLMAIN;i++ ) 
									if( SkillTbl[i].Select_Butcher== 1 ) 
									{
										Skill[i] = 1; 
										skillexp[ SkillTbl[i].MotherSkillType ] = exp;
									}
									break;
		case J_HERB_DIGGER	:	for(  i=0; i<MAX_SKILLMAIN;i++ ) 
									if( SkillTbl[i].Select_Herbdigger== 1 ) 
									{
										Skill[i] = 1; 
										skillexp[ SkillTbl[i].MotherSkillType ] = exp;
									}
									break;
		}
		
		switch( cls ) 
		{
		case WARRIOR :	for(  i=0; i<MAX_SKILLMAIN;i++ )	
							if( SkillTbl[i].Class_Warrior == 1 ) Skill[i] = 1;
							break;
		case THIEF :	for(  i=0; i<MAX_SKILLMAIN;i++ )
							if( SkillTbl[i].Class_Thief == 1 ) Skill[i] = 1;
							break;
		case ARCHER :	for(  i=0; i<MAX_SKILLMAIN;i++ )
							if( SkillTbl[i].Class_Archery == 1 ) Skill[i] = 1;
							break;
		case WIZARD :	for(  i=0; i<MAX_SKILLMAIN;i++ )
							if( SkillTbl[i].Class_Wizard == 1 ) Skill[i] = 1;
							break;
		case PRIEST :	for(  i=0; i<MAX_SKILLMAIN;i++ )
							if( SkillTbl[i].Class_Priest == 1 ) Skill[i] = 1;
							break;
		}
		
		
		var[51] = 0; var[52] = 0; var[53] = 0;
		ret = Update_Skill_BinaryData( (UCHAR**)&Skill, (UCHAR**)&skillexp, (UCHAR**)&var, name );
	}
}

void CheckSkillExp_kein( int index, DWORD skillexp[], DWORD &exp )
{
	if( skillexp[index] >= 50000 )
	{
		if( exp < skillexp[index] ) exp = skillexp[index];
		skillexp[index] = 6;
	}
}

void RecvSelectNation( t_packet *p, short int cn )
{
	int nation = p->u.kein.default_char;

	if(nation != 3 && nation != 4 && nation != 6) return;
	
	char name[4][20]={0,};
	GetCharacterNameInID( connections[cn].id, name );
	
	int i;
	for(i = 0; i < 4; i++)
	{
		if( name[i][0] )
		{
			unsigned long curnation;
			GetNationByName(name[i], &curnation);
			/*if(curnation != 0)
			{
				MyLog(LOG_NORMAL, "Nationhack (%s) (%s)!", connections[cn].id, connections[cn].ip_address);
				closeconnection(connections, cn, CCT_FORCED); //CTT_FORCED
				return;
			}*/ //Disabled temporary
		}	
	}
	for( i = 0; i< 4; i++ )
	{
		if( name[i][0] )
		{
			int ret = UpdateSelectNation( nation, name[i] );
		}
	}
}

void CheckInitData()
{
	int size;
	
	size = sizeof( CCharRank );
	if( size > sizeof(DWORD ) ) JustMsg( "Size of 'CCharRank' is %d Bytes ", size );
}


///////////////////////////////////////////////////////////////////////////////
inline int GetIndexByMapName( char *mapname )
{
	EatRearWhiteChar( mapname );
	strupr( mapname );
	
	for( int i=0; i<MAX_MAP_;i++ )
	{
		if( MapInfo[i].mapfile[0] ) 
		{
			if( ::stricmp( MapInfo[i].mapfile, mapname) ==  0 )
			{
				return i;
			}
		}
	}
	return -1;
}

int GetNationByMapName( char *mapname )
{
	int index = GetIndexByMapName( mapname );
	if( index == -1 ) return -1;
	else
	{
		return MapInfo[index].nation;
	}
}

WORD GetPortByMapName( char *mapname )
{
	int index = GetIndexByMapName( mapname );
	if( index == -1 ) return 0;
	else
	{
		return MapInfo[index].port;
	}
}
///////////////////////////////////////////////////////////////////////////////


enum eSelectMap
{
	SC_HELTERNT_CASTLE	=1,
	SC_HELTERNT_VILLAGE	=2,
	SC_HUDAIN_RIVER		=3,
	SC_GRAY_MOUNTAIN	=4,
	SC_CALAHIL			=5,
	SC_BAISUS_IMPEL		=6,
	SC_RENUS		 	=7,
	SC_DEL_HAPPA		=8,
	SC_IRAMUS			=9,
	SC_DIPH_UBEN		=10,
	SC_SCHOLIUM			=11,
	SC_TYREN			=12,
	SC_BARANTAN			=13,	
	SC_SCHOLIUM2		=14,		// Ãß°¡½Ã StartMapPositionµµ Ãß°¡ÇÑ´Ù.	// 20°³ ±îÁö´Ù..//020815-2 lsw
	SC_RECENT_LOGOUT	= 99,
};

int GetStartPostionByNation( CHARLIST *ch, int StartPosition )
{
	switch( ch->name_status.nation )
	{
	case N_VYSEUS:	
		{
			switch( StartPosition )
			{
			case SC_BAISUS_IMPEL :	if( ch->Level >= 41 ) return StartPosition;	break;
			case SC_IRAMUS :		if( ch->Level >= 31 ) return StartPosition;	break;
			}
			return SC_HELTERNT_VILLAGE;		// ÇïÅÏÆ®
		}
	case N_ZYPERN:	
		{
			switch( StartPosition )
			{
			case SC_DIPH_UBEN:	if( ch->Level >= 41 ) return StartPosition;	break;
			case SC_TYREN:		if( ch->Level >= 31 ) return StartPosition;	break;
			}
			return SC_RENUS;		// ·¹³Ê½º
		}
	case N_YILSE: 	
		{
			return SC_BARANTAN;
		}
	}
	return 99;	
}


bool IsPossibleRecent( char *map_name, int &index )		// recent ÇÒ ¼ö ÀÖ´Â ¸ÊÀÎ°¡ ¾Æ´Ñ°¡?
{	//< CSD-030804
	static const int impossible_map[] =
	{	
			25, // event2
			39, // evnetlw
			69, // nation1
			70, // nation2
			71, // nation3
			73,	// abyss_1		// 020702 YGI
			74,	// abyss_2
			75,	// undead_1
			76,	// undead_2
			77,	// bigmaze_1
			78,	// bigmaze_2
			81, // gm_event	
			86,	// Nation4
			90,	// semenys_d1
			91,	// semenys_d2
			// Ãß°¡ ÇÏ°í ½ÍÀ¸¸é ¹ØÀ¸·Î °è¼Ó Ãß°¡..
	};

	static const int max = sizeof(impossible_map)/sizeof(int);
	
	index = GetIndexByMapName(map_name);

	if (index == -1)
	{
		return false;		// recent ÇÒ ¼ö ¾ø´Ù. 
	}

	for (int i = 0; i < max; ++i)
	{
		if (index == impossible_map[i])
		{
			return false;
		}
	}

	if (LocalMgr.IsAbleNation(KOREA))
	{	
		// 030624 YGI : Á×À¸¸é ÆÃ±â´Â ¸ÊÀ¸·Ð ¸®¼¾Æ® Á¢¼Ó ÇÒ ¼ö ¾ø´Ù.
		int nRow = 0;
		char query[256];
		sprintf( query, "mapname = '%s'", map_name );
		GetRowLineOfSQL( "Event_MoveWhenDie", "*", &nRow, query );
		if(nRow>0) return false;
	}	

	return true;
}	//> CSD-030804

//020823 lsw
void CheckStartMap( t_connection c[], short int cn, int &StartPosition )		// 1004 YGI
{
	// ½ÃÀÛ À§Ä¡¸¦ ÀúÀåµÈ À§Ä¡¸¦ »ç¿ëÇÏ´ÂÁö¸¦ ÆÇ´ÜÇÑ´Ù.
	CHARLIST *ch = &c[cn].chrlst;
	//1			ÃÊº¸ÀÚ1 ÃÊº¸ÀÚ2
	//2-7		ÃÊº¸ÀÚ1 ÃÊº¸ÀÚ2 ¸¶À»
	//7¿À¹ö		¸¶À»(¸®¼¾Æ® ÇØµµ ¾ÈµÊ)
	switch(ch->Level)
	{
	case 0:
	case 1:
		{
			if(ch->startposition == SC_SCHOLIUM || ch->startposition == SC_SCHOLIUM2)//ÀÌ°Å Àú°Å µÑÁß ÇÏ³ª¸é
			{
				return;
			}
			if(ch->startposition != SC_SCHOLIUM && ch->startposition == SC_SCHOLIUM2)//·¹º§ 1 ÁÖÁ¦¿¡ ´Ù¸¥µ¥ Á¢¼Ó ÇÏ·ÁÇÏ¸é
			{
				if(ch->startposition = StartPosition = SC_SCHOLIUM)//ÃÊº¸ÀÚ·Î ¼ÂÆÃ
				{
					return;
				}
			}
		}break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		{
			if(ch->startposition == SC_SCHOLIUM || ch->startposition == SC_SCHOLIUM2)//ÀÌ°Å Àú°Å µÑÁß ÇÏ³ª¸é
			{
				//	if(ch->startposition = StartPosition = SC_SCHOLIUM)//ÃÊº¸ÀÚ·Î ¼ÂÆÃ
				{
					return;
				}
			}
		}//±×°Ô ¾Æ´Ï¶ó ¾û¶×ÇÑ°Å¸é ¾Æ·¡·Î ³»·Á°¨
	default:
		{	// Recent·Î Á¢¼ÓÇÏ·Á°í ÇÒ¶§, ±×¸ÊÀÌ Ä³¸¯ÅÍÀÇ ³ª¶óÀÌ°Å³ª, Áß¸³¸ÊÀÌ¸é µé¾î°¥¼ö ÀÖ´Ù. 
			if( ch->startposition == 99 )
			{
				int index;
				if( IsPossibleRecent( ch->MapName, index ) )		// ¸®¼¾Æ® ºÒ°¡´É Áö¿ªÀÌ ¾Æ´Ï¸é
				{
					// ±¹°¡¸¦ È®ÀÎÇÏ¿© Ã³¸®ÇÑ´Ù.
					int nation = MapInfo[index].nation;
					if( !ch->name_status.nation || !nation || ch->name_status.nation == nation ) // Áß¸³µµ »ý°¢
					{
						return;		// ¸®¼¾Æ® °¡´ÉÇÏ´Ù.
					}
				}
			}
		}break;
	}
	// recent ºÒ°¡´É Áö¿ªÀÌ¶ó¸é
	// Ä³¸¯ÀÇ ³ª¶ó¸ÊÀ¸·Î ½ÃÀÛ¸Ê,½ÃÀÛÁÂÇ¥¸¦ º¸Á¤ÇÑ´Ù. 
	ch->startposition = StartPosition = GetStartPostionByNation( ch, StartPosition );
	
	switch( ch->startposition )
	{
	case SC_HELTERNT_VILLAGE :	switch( rand()%3 )	// ma-in..
								{
	case 0 :  ch->X = 247 * 32, ch->Y = 107 * 32; break;
	case 1 :  ch->X = 232 * 32, ch->Y =  97 * 32; break;
	default : ch->X = 266 * 32, ch->Y = 122 * 32; break;
								}
								break;
								
	case SC_BAISUS_IMPEL:	switch( rand()%3 )
							{
	case 0:		ch->X = 253 * 32, ch->Y = 449 * 32;	break;
	case 1:		ch->X = 292 * 32, ch->Y = 456 * 32;	break;
	default :	ch->X = 274 * 32, ch->Y = 472 * 32;	break;
							}
		break;					
	case SC_IRAMUS		:	switch( rand()%2 )
							{
	case 0:		ch->X = 92 * 32, ch->Y = 67 * 32;	break;
	default :	ch->X = 135 * 32, ch->Y = 74 * 32;	break;
							}
		break;
	case SC_DIPH_UBEN	:	switch( rand()%3 )
							{
	case 0:		ch->X = 276 * 32, ch->Y = 360 * 32;	break;
	case 1:		ch->X = 289 * 32, ch->Y = 369 * 32;	break;
	default :	ch->X = 302 * 32, ch->Y = 381 * 32;	break;
							}
		break;
	case SC_TYREN		:	switch( rand()%2 )
							{
	case 0:		ch->X = 445 * 32, ch->Y = 260 * 32;	break;
	default :	ch->X = 494 * 32, ch->Y = 305 * 32;	break;
							}
		break;
	case SC_BARANTAN	:	switch( rand()%2 )
							{
	case 0:		ch->X = 445 * 32, ch->Y = 260 * 32;	break;
	default :	ch->X = 494 * 32, ch->Y = 305 * 32;	break;
							}
		break;
	}
}

void RecvExistName( t_packet *p, short int cn )
{
	k_exist_name *t = &p->u.kein.exist_name;
	
	t_packet packet;
	int ret = CheckName_SQL( t->name );
	if( ret )		// Á¸Àç ÇÑ´Ù.
	{
		packet.h.header.type = CMD_THEREIS_CHARNAME;
	}
	else			// ÀÌ¸§ÀÌ ¾øÀ¸¸é..
	{
		packet.h.header.type = CMD_THEREIS_NO_CHARNAME;
	}
	packet.u.kein.default_short_int = t->server_id;
	packet.h.header.size = sizeof( short int );
	
	QueuePacket( connections, cn, &packet, 1 );
}

void RecvExistNameForNation( t_packet *p, short int cn )
{
	k_exist_name_and_nation *t= &p->u.kein.exist_name_and_nation;
	t_packet packet;
	
	DWORD name_status;
	int ret = GetNationByName( t->name, &name_status );		// 1018 YGI
	if( !ret ) return;
	
	CCharRank target;
	memcpy( &target, &name_status, sizeof( DWORD ) );
	
	if( target.counselor || target.nation == 0 || target.nation == t->nation )
	{
		packet.h.header.type = CMD_THEREIS_CHARNAME;
	}
	else
	{
		packet.h.header.type = CMD_THEREIS_NO_CHARNAME;
	}
	packet.u.kein.default_short_int = t->server_id;
	packet.h.header.size = sizeof( short int );
	
	QueuePacket( connections, cn, &packet, 1 );
}

void CheckAndUpdateVote( t_packet *p, short int cn )
{
	char *login_id	= p->u.kein.vote_game2login.login_id;
	int server_id	= p->u.kein.vote_game2login.server_id;
	int vote		= p->u.kein.vote_game2login.vote;			// ¼±°Å ¹øÈ£
	int nation		= p->u.kein.vote_game2login.nation;			// ³ª¶ó
	int support		= p->u.kein.vote_game2login.support;		// ÅÃÇÑ ÈÄº¸
	
	int check_vote = GetVoteById_SQL( login_id );
	if( check_vote < 0 ) return;
	
	t_packet packet;
	if( check_vote < vote )
	{
		SetPlusScoreVote( support, vote, nation );	// ¼±°Å Å×ÀÌºí¿¡ Ç¥ÇÏ³ª ++ ÇØÁØ´Ù.
		SetVote_SQL( login_id, vote );		// ¼±°Å¸¦ Ä¡·é »ç½ÇÀ» µî·Ï
		
		packet.h.header.type = CMD_VOTE_OK;	// ¼±°Å Çß´Ù.
	}
	else 
	{
		packet.h.header.type = CMD_VOTE_NOT;	// ¼±°Å¸¦ ÇÒ¼ö ¾ø´Ù.
	}
	packet.u.kein.default_short_int = server_id;
	packet.h.header.size = sizeof( short int );
	QueuePacket( connections, cn, &packet, 1 );
	
}

void RecvRegistCandidate( t_packet *p, short int cn )
{
	short int server_id = p->u.kein.regist_candidate.server_id;
	k_candidate *target = &p->u.kein.regist_candidate.candidate;
	
	t_packet packet;
	int ret = RegistCandidate_SQL( target );
	if( ret < 1 )
	{
		packet.h.header.type = CMD_REGIST_CANDIDATE_NOT;
		packet.u.kein.login2game_ear_message_result.send_server_id = server_id;
		packet.u.kein.login2game_ear_message_result.ret = ret;
		packet.h.header.size = sizeof( k_login2game_ear_message_result );		
	}
	else
	{
		packet.h.header.type = CMD_REGIST_CANDIDATE_OK;
		packet.u.kein.default_short_int = server_id;
		packet.h.header.size = sizeof( short int );
	}
	QueuePacket( connections, cn, &packet, 1 );
}

void isThisManCandidate( t_packet *p, short int cn )
{
	char *name = p->u.kein.is_this_man_candidate.name;
	short int server_id = p->u.kein.is_this_man_candidate.server_id;
	short int vote_num =  p->u.kein.is_this_man_candidate.vote_num;
	
	if( vote_num <= 0 ) return;
	
	int RowCount = 0;
	char condition[255];

	char szName[20];
	ConvertQueryString(name, szName, 20); // Finito prevents sql injection
	
	t_packet packet;
	sprintf( condition, "name = '%s' AND number = %d", szName, vote_num );
	int ret = GetRowLineOfSQL( "vote", "name", &RowCount, condition );
	
	if( ret < 0 || RowCount )		// ÀÌ¹Ì µî·ÏÇß´Ù.
	{
		packet.h.header.type = CMD_THIS_MAN_IS_CANDIDATE_NOT;
		packet.u.kein.default_short_int = server_id;
		packet.h.header.size = sizeof( short int );
		QueuePacket( connections, cn, &packet, 1 );
		return;
	}
	
	sprintf( condition, "name = '%s'", szName );
	ret = GetRowLineOfSQL( "vote_regist", "name", &RowCount, condition );
	
	
	if( RowCount )
	{
		// ÈÄº¸ÀÚ ¸í´Ü¿¡ ÀÖ´Ù.
		packet.h.header.type = CMD_THIS_MAN_IS_CANDIDATE_OK;
	}
	else 
	{
		// ÈÄº¸ÀÚ ¸í´Ü¿¡ ¾ø´Ù.
		packet.h.header.type = CMD_THIS_MAN_IS_CANDIDATE_NOT;
	}
	packet.u.kein.default_short_int = server_id;
	packet.h.header.size = sizeof( short int );
	QueuePacket( connections, cn, &packet, 1 );
}
void CheckVote( t_packet *p, short int game_id )
{
	short int server_id = p->u.kein.check_vote.server_id;
	short int vote_num	= p->u.kein.check_vote.vote_num;
	short int nation = p->u.kein.check_vote.nation;
	char	*login_id = p->u.kein.check_vote.login_id;
	
	
	int check_vote = GetVoteById_SQL( login_id );
	if( check_vote < 0 ) return;
	
	t_packet packet;
	if( vote_num <= check_vote )
	{
		// ÀÌ¹Ì ¼±°Å¸¦ Çß´Ù.
		packet.h.header.type = CMD_CHECK_VOTE_NOT;
		packet.u.kein.default_short_int = server_id;
		packet.h.header.size = sizeof( short int );
		QueuePacket( connections, game_id, &packet, 1 );
	}
	else
	{
		packet.h.header.type = CMD_CHECK_VOTE_OK;
		int count = GetCandidate_SQL( vote_num, nation, packet.u.kein.check_vote_ok.candidate );
		if( count > 0 && count <= 3 )
		{
			packet.u.kein.check_vote_ok.server_id = server_id;
			packet.u.kein.check_vote_ok.candidate_count = count;
			
			packet.h.header.size = sizeof( k_check_vote_ok ) - sizeof( k_candidate )*(3-count);
			QueuePacket( connections, game_id, &packet, 1 );
		}
		else
		{
			// ÈÄº¸ÀÚ°¡ ÇÏ³ªµµ ¾ø´Ù.
		}
	}
}

// ¼±°Å °á°ú ·çÆ¾ 3-2
// ·Î±×ÀÎ ¼­¹ö·Î º¸³» ¸ðµç °ÔÀÓ¼­¹ö·Î º¸³¾¼ö ÀÖ°Ô ÇÑ´Ù.
void SendYouAreKingLog2Log( char *name, short int cn, int type )
{
	t_packet packet;
	packet.h.header.type = type;
	strcpy( packet.u.kein.default_name, name);
	packet.h.header.size = strlen( name )+1;
	QueuePacket( connections, cn, &packet, 1 );
}

// ¼±°Å °á°ú ·çÆ¾ 3-3
// Å¬¶ó¾ðÆ®±îÁö °¡µµ·Ï ¸ðµç °ÔÀÓ ¼­¹ö¿¡ »Ñ¸°´Ù.
void SendYouAreKingLog2Client( char *name, int type )
{
	t_packet packet;
	packet.h.header.type = type;
	strcpy( packet.u.kein.default_name, name);
	packet.h.header.size = strlen( name )+1;
	g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
}

void GetVoteValue( short int cn )
{
	t_packet packet;
	int ret = GetVoteInfo( &packet.u.kein.set_value_of_vote );
	
	char *is_voting = packet.u.kein.set_value_of_vote.is_voting;
	char *vote_num = packet.u.kein.set_value_of_vote.vote_num;
	
	for( int i=0; i<6; i++ )
	{
		if( is_voting[i] == 10 )		// ¼±°Å ¿Ï·á
		{
			//	¼±°Å ¿Ï·á ·çÆ¾
			char the_king[20];
			int ret = GetVoteNumberOne( i, vote_num[i], the_king );		// 1: ´ç¼±ÀÚ ÀÌ¸§ ¾Ë¾Æ¿À±â
			UpdateYouAreKing( the_king, 1 );							// 2: ´ç¼±ÀÚ db°íÃÄÁÖ±â (¿ÕÀ¸·Î ¸¸µé¾î ÁØ´Ù )
			SendYouAreKingLog2Log( the_king, cn, CMD_YOU_ARE_KING_LOG2LOG );						// 3: ´ç¼±ÀÚ Ã£±â
			SetVoteEndFlag( i, 1 );										// 4: ¼±°Å ¿Ï·á ÇÃ·¹±×¸¦ ¼ÂÆÃÇÏ±â
			CheckDbTable( i, the_king );								// 5: ¿Õ µî·ÏÇÏ°í ÈÄº¸ ´Ù Áö¿î´Ù.
		}
		else if( is_voting[i] == 20 )		// ¿ÕÀÇ ÀÓ±â ¿Ï·á	// ¿ÕÀ» ÇØÁ¦ ½ÃÅ²´Ù.
		{
			char the_king[20];
			GetKingOfNation_SQL( i, the_king );		// ¿ÕÀÇ ÀÌ¸§À» °¡Á®¿À°í
			UpdateYouAreKing( the_king, 0 );		// ¿ÕÀ» ÇØÀÓ ½ÃÅ²´Ù.
			SendYouAreKingLog2Log( the_king, cn, CMD_YOU_ARE_NO_KING_LOG2LOG );						// 3: ´ç¼±ÀÚ Ã£±â
			SetVoteEndFlag( i, 0 );										// 4: ¼±°Å ¿Ï·á ÇÃ·¹±×¸¦ ¼ÂÆÃÇÏ±â
		}
	}
	if( ret == 1 )
	{
		packet.h.header.type = CMD_SET_VALUE_OF_VOTE;
		packet.h.header.size = sizeof( k_set_value_of_vote );
		QueuePacket( connections, cn, &packet, 1 );
	}
}
void RecvVoteScore( t_packet *p, short int cn )
{
	int server_id = p->u.kein.req_vote_score.server_id;
	int vote_num = p->u.kein.req_vote_score.vote_num;
	int nation = p->u.kein.req_vote_score.nation;
	
	t_packet packet;
	int ret = GetCurrentVoting( vote_num, nation, &packet.u.kein.rep_vote_score );
	if( ret >= 1 )
	{
		packet.h.header.type = CMD_REP_VOTE_SCORE;
		packet.u.kein.rep_vote_score.server_id = server_id;
		packet.u.kein.rep_vote_score.max = ret;
		packet.h.header.size = sizeof( k_rep_vote_score ) - sizeof( k_score_and_name )*(3-ret);
		QueuePacket( connections, cn, &packet, 1 );
	}
}

void RecvNationMsg( t_packet *p, short int cn )
{
	p->h.header.type = CMD_RECV_ALL_MSG;
	g_pServerTable->BroadCastToEveryServer( (char *)p, (sizeof(t_header)+p->h.header.size ), SERVER_TYPE_MAP );
}

void CheckGuildJoin( t_packet *p, short int cn )
{
	int target_id	= p->u.kein.guild_join_server.target_id;
	int server_id	= p->u.kein.guild_join_server.server_id;
	int guild_code	= p->u.kein.guild_join_server.guild_code;
	char *id		= p->u.kein.guild_join_server.id;
	
	int is_possible = 1;
	
	// °°Àº °èÁ¤ÀÇ ´Ù¸¥ Ä³¸¯ÅÍ°¡ ´Ù¸¥ ±æµå¿¡µç°Å ¾Æ´Ñ°¡?
	is_possible = isPosableGuildJoinById( guild_code, id );
	
	t_packet packet;
	if( is_possible )		// ±æµå °¡ÀÔÀÌ °¡´ÉÇÏ´Ù.
		packet.h.header.type = CMD_GUILD_JOIN_SERVER_OK;
	else
		packet.h.header.type = CMD_GUILD_JOIN_SERVER_NOT;
	
	packet.u.kein.guild_join_result.server_id = server_id;
	packet.u.kein.guild_join_result.target_id = target_id;
	packet.h.header.size = sizeof( k_guild_join_result );
	QueuePacket( connections, cn, &packet, 1 );
}

void SendGuildAllMsg( t_packet *p, short int cn )
{
	p->h.header.type = CMD_GUILD_ALL_MSG_RECV;
	g_pServerTable->BroadCastToEveryServer( (char *)p, (sizeof(t_header)+p->h.header.size ), SERVER_TYPE_MAP );
}

void RecvReturnGameServer( t_packet *p, int type )
{
	if( type ) p->h.header.type = type;
	g_pServerTable->BroadCastToEveryServer( (char *)p, (sizeof(t_header)+p->h.header.size ), SERVER_TYPE_MAP );
}

void RecvGmRegist( t_packet *p )
{
	int total_gm_count=0, gm_count=0;
	char condition[100];
	
	int gm_list = p->u.kein.gm_regist_db.gm_list;
	char *name = p->u.kein.gm_regist_db.name;
	char szName[20];
	ConvertQueryString(name, szName, 20); // Finito prevents sql injection
	sprintf( condition, "job = %d AND name = '%s'", gm_list, szName );		// °°Àº Á÷Á¾À¸·Î ¶È°°Àº ³ðÀÌ ÀúÀåµÇ´Â°É ¸·±â À§ÇØ
	int ret = GetRowLineOfSQL( "GM_TABLE", "*", &gm_count, condition );
	if( gm_count == 0 ) 
	{
		ret = InsertGmRegist( &p->u.kein.gm_regist_db );
		if( !ret ) return;
	}
	
	sprintf( condition, "job = %d", gm_list);		// °°Àº Á÷Á¾À¸·Î ¶È°°Àº ³ðÀÌ ÀúÀåµÇ´Â°É ¸·±â À§ÇØ
	ret = GetRowLineOfSQL( "GM_TABLE", "*", &gm_count, condition );		// ±× Á÷¾÷ÀÇ gm ¼ö
	ret = GetRowLineOfSQL( "GM_TABLE", "*", &total_gm_count, NULL);		// total gm ¼ö
	
	t_packet packet;
	packet.h.header.type = CMD_COME_OUT_GM_FROM_LOGIN;		// ¸ðµç »ç¶÷¿¡°Ô ¾Ë¸°´Ù.
	packet.u.kein.send_gm_regist_ok.gm_index = gm_list;
	packet.u.kein.send_gm_regist_ok.gm_rank= gm_count;
	packet.u.kein.send_gm_regist_ok.total_gm_rank= total_gm_count;
	strcpy( packet.u.kein.send_gm_regist_ok.name, szName );
	packet.h.header.size = sizeof(k_send_gm_regist_ok) - 20 +strlen( szName )+1;
	g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
}

void RecvRepStopWarRefusal( t_packet *p )
{
	int game_id = p->u.kein.rep_stop_war_login.game_id;		// gameserver_port;
	int server_id = p->u.kein.rep_stop_war_login.server_id;
	
	t_packet packet;
	packet.h.header.type = CMD_REP_STOP_WAR_REFUSAL_TO_CLIENT;
	packet.u.kein.default_short_int = server_id;
	packet.h.header.size = sizeof( short int );
	
	for(int j = 0; j < LOGIN_MAX_CONNECTIONS; j ++)
	{
		if(connections[j].server_check == game_id )
		{
			QueuePacket( connections, j, &packet, 1 );
		}
	}
}

void RecvReqStopWar( t_packet *p, short int cn )		// ´Ù¸¥ ¸Ê¿¡ ¿äÃ»ÇÒ ³ª¶ó¿ÕÀÌ ÀÖ´ÂÁö º¸³»ÁØ´Ù.
{
	t_packet packet;
	packet.h.header.type = CMD_REQ_STOP_WAR_TO_CLIENT;
	packet.u.kein.send_game_server_req_stop_war.target_nation = p->u.kein.send_login_req_stop_war.target_nation;
	packet.u.kein.send_game_server_req_stop_war.send_nation = p->u.kein.send_login_req_stop_war.send_nation;
	packet.u.kein.send_game_server_req_stop_war.server_id = p->u.kein.send_login_req_stop_war.server_id;
	packet.u.kein.send_game_server_req_stop_war.game_id = connections[cn].server_check;
	packet.h.header.size = sizeof( k_send_game_server_req_stop_war );
	
	g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
	
}

void RecvRepStopWarAccept( t_packet *p )
{
	p->h.header.type = CMD_REP_STOP_WAR_ACCEPT_TO_CLIENT;		// ÀÚ ¸ðµÎ¿¡°Ô »Ñ·ÁÁà º¸ÀÚ
	
	g_pServerTable->BroadCastToEveryServer( (char *)p, (sizeof(t_header)+p->h.header.size ), SERVER_TYPE_MAP );
}

/// YGI /////////
int SetTactics( int spell_type, int sex, int tac_type )		// Ä³¸¯ÅÍ ¸ÞÀÌÅ©ÇÒ°æ¿ì ¼±ÅÃÇÑ ÅÃÆ½½º¸¦ ½ÇÁ¦ ¹è¿­Ã·ÀÚ·Î ¹Ù²Ù´Â ·çÆ¾..
{
	int tac_con[2][12] = { 
		{ CRAPPLE_, SWORD_, ARCHERY_, FENCING_, MACE_, PIERCE_, WHIRL_, HURL_, PARRYING_, MAGERY_, },		 // ¿©ÀÚ
		{ CRAPPLE_, SWORD_, ARCHERY_, PARRYING_, MACE_, PIERCE_, WHIRL_, HURL_, MAGERY_, D_SWORD_, D_MACE_ },	// ³²ÀÚ
	};
	
	int ret = tac_con[sex][tac_type];
	if( spell_type == PRIEST_SPELL && ret == MAGERY_ ) ret = ORISON_;
	return ret;
}







/*

  ////////////////////// for ServerViewer //////////////////////
  void SendConnectServerCount( short int cn )
  {
  t_packet packet;
  packet.h.header.type = CMD_SV_CONNECT_SERVER_COUNT;
		packet.u.kein.default_char = g_current_gameserver;
		packet.h.header.size = sizeof( char );
		QueuePacket( connections, cn, &packet, 1 );
		
		  }
		  
			void SendCurrServerPort( short int cn )
			{
			t_packet packet;
			packet.h.header.type = CMD_SV_GET_CONNECT_SERVER_PORT;
			
			  short int &count = packet.u.kein.server_port.count;
			  count = 0;
			  for(int j = 0; j < LOGIN_MAX_CONNECTIONS; j ++)
			  {
			  if( connections[j].socket && connections[j].server_check )
			  {
			  packet.u.kein.server_port.port[count++] = connections[j].server_check;
			  }
			  }
			  
				packet.h.header.size = sizeof( short int ) + sizeof( short int )*count;
				
				  char *temp = ( char *)&packet.u.kein.server_port;
				  QueuePacket( connections, cn, &packet, 1 );
				  }
				  
					void RecvSVMessageAll( t_packet *p )
					{
					SendPbs( p->u.kein.default_msg );
					}
					
*/

void SendReqSalvationMoney( short int server_id, DWORD money, short int cn )
{
	t_packet packet;
	packet.h.header.type = CMD_DB2GAME_SALVATION;
	packet.u.kein.db2game_salvation_money.server_id = server_id;
	packet.u.kein.db2game_salvation_money.money = money;
	packet.h.header.size = sizeof( k_db2game_salvation_money );
	QueuePacket( connections, cn, &packet, 1 );
}
void RecvReqSalvationMoney( packet *p, short int cn )
{
	short int server_id = p->u.kein.req_salvation_money.server_id;
	char *name = p->u.kein.req_salvation_money.name;
	char szName[20];
	ConvertQueryString(name, szName, 20); // Finito prevents sql injection
	DWORD money;
	int ret = GetSalvation( szName, money );
	if( ret == 1 )
	{
		SendReqSalvationMoney( server_id, money, cn );
	}
}
// 020826 YGI
void RecvInsertSalvation( packet *p, short int cn )
{
	short int server_id = p->u.kein.db_salvation_money.server_id;
	DWORD money = p->u.kein.db_salvation_money.money;
	int nation = p->u.kein.db_salvation_money.nation;		// ³ª¶ó
	char *name = p->u.kein.db_salvation_money.name;
	DWORD old_money;

	char szName[20];
	ConvertQueryString(name, szName, 20); // Finito prevents sql injection
	
	/*
	int ret = CheckSalvationNameBasic( name );
	if( ret )	
	{
	char result = ret;
	DirectClient( CMD_CHECK_SALVATION_NAME, server_id, cn, &result, sizeof( char ) );
	return; // ÀÌ¹Ì ±âºÎÇÑÀûÀÌ ÀÖ´Ù.
}*/
	if(!CheckSalvationNameBasic2(szName))
	{
		WORD wPort;
		DWORD dwID, dwServerSetNum;
		if(CheckUsedID_SQL(connections[cn].id, &wPort, &dwID, &dwServerSetNum ) == 1)
		{
			if(dwServerSetNum == g_pServerTable->GetServerSetNum())
			{
				if(!SendRemoveUserToAgent(connections[cn].id, wPort, dwID))
				{
					MyLog(LOG_NORMAL, "Famehack - SendRemoveUserToAgent failed: %d, %d, %d", connections[cn].id, wPort, dwID);
				}
			}
		}
		MyLog(LOG_NORMAL, "Famehack - (%s) (%s)", connections[cn].id, connections[cn].ip_address);
		closeconnection(connections, cn, CCT_FORCED);
		return;
	}
	
	int ret = GetSalvation( szName, old_money );
	if( ret != 1 )		// ½ÇÆÐ
	{
		return;
	}
	DWORD total_money = money+old_money;
	if( old_money < 3000000 )// ¾ÆÀÌÅÛÀ» ÁÙ °æ¿ìÀÎÁö Ã¼Å©
	{
		if( total_money >= 3000000 ) 
		{
			SendServerEachItem( 9047, server_id, cn );		// Àû½ÊÀÚ ºñÆ® ÇãÆ®¸¦ ÁØ´Ù.
		}
	}
	char szQuerry[255];
	sprintf(szQuerry, "UPDATE chr_info2 SET salvation=%u WHERE name = '%s'", total_money, szName );
	// ÅäÅ» ±âºÎ¾× ´õ ÇØÁØ´Ù.
	ret = Querry_SQL( szQuerry );
	if( ret >= 0 )
	{
		// salvation¿¡ ÀúÀåÇÑ´Ù.
		
		if( CheckSalvationNameBasic( szName ) )
		{
			sprintf(szQuerry, "UPDATE salvation_name SET date = getdate() WHERE name = '%s'", szName );
			if( Querry_SQL( szQuerry ) < 0 )
			{
				MyLog( 0, "UPDATE salvation_name table error, then user will contribute to money again...!!!" );
			}
		}
		else
		{
			sprintf(szQuerry, "INSERT INTO salvation_name ( name, date ) VALUES ( '%s', getdate() )", szName );
			if( Querry_SQL( szQuerry ) < 0 )
				MyLog( 0, "Insert salvation_name table error, then user will contribute to money again...!!!" );
		}
		/*
		SendReqSalvationMoney( server_id, money+old_money, cn );
		double Total_Money = 0;
		ret = PlusMoneyRedClose( Total_Money, money );
		if( ret == 1 )	// ¸ðµÎ¿¡°Ô »Ñ·ÁÁØ´Ù.
		{
		t_packet packet;
		packet.h.header.type = CMD_MSG_ALL_SALVATION_TOTAL_MONEY;
		packet.u.kein.total_salvation_all_msg.nation = nation;
		packet.u.kein.total_salvation_all_msg.money = money;
		packet.u.kein.total_salvation_all_msg.total_money = Total_Money;
		strcpy( packet.u.kein.total_salvation_all_msg.name, name );
		packet.h.header.size = sizeof( k_total_salvation_all_msg ) - 20 + strlen(name)+1;
		g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
	}*/		
	}
	
	//	else SQLerror( szQuerry );
}

// °ÔÀÓ¼­¹ö·Î ¾ÆÀÌÅÛÀ» ¸¸µé¶ó°í ¸Þ½ÃÁö¸¦ º¸³½´Ù.
void SendServerEachItem( int item_no, short int server_id, short int game_id )
{
	t_packet packet;
	packet.h.header.type = CMD_SERVER_EACH_ITEM;
	packet.u.kein.send_db2map_each_item.server_id = server_id;
	packet.u.kein.send_db2map_each_item.item_no = item_no;
	packet.h.header.size = sizeof( k_send_db2map_each_item );
	QueuePacket( connections, game_id, &packet, 1 );
}

void SaveItemAndLimit( int nItemNumber, char *szCharName, DWORD dwItemLimit )		// ÃÊÄÝ·¿ ¸®¹ÌÆ® ¹øÈ£ ÀúÀå..
{
	char filename[MAX_PATH];
	sprintf( filename, "%d.txt", nItemNumber );
	FILE *fp;
	fp = fopen( filename, "at+" );
	if( !fp ) return ;
	
	fprintf( fp, "%s	%u\n", szCharName, dwItemLimit );
	fclose( fp );
}

void RecvEatChocolate( t_packet *p, DWORD cn )
{
	char *name = p->u.kein.eat_chocolate.name;
	DWORD limit = p->u.kein.eat_chocolate.limit;
	DWORD server_id = p->u.kein.eat_chocolate.server_id;
	
	int count = 0;
	int ret = SetChocolateCount( name, count );
	SaveItemAndLimit( 3052, name, limit );
	if( ret != 1 ) return;
	
	t_packet packet;
	packet.h.header.type = CMD_EAT_CHOCOLATE_OK;
	packet.u.kein.eat_chocolate_ok.server_id = server_id;
	packet.u.kein.eat_chocolate_ok.chocolate_count= count;
	packet.h.header.size = sizeof( k_eat_chocolate_ok );
	QueuePacket( connections, cn, &packet, 1 );
}

void RecvCheckChocolate( t_packet *p, DWORD cn )
{
	DWORD server_id = p->u.kein.default_dword;
	
	t_packet packet;
	packet.h.header.type = CMD_PAY_RUMOR_OK;
	packet.u.kein.login_check_chocolate.server_id = cn;

	if (GetTopGivenChocolate( packet.u.kein.login_check_chocolate.name, packet.u.kein.login_check_chocolate.count ) != 1);
	{
		DirectClient( CMD_PAY_RUMOR_NOT, server_id, cn, NULL, 0 );
		return;
	}

	packet.h.header.size = sizeof( k_login_check_chocolate) - 20 + strlen( packet.u.kein.login_check_chocolate.name ) + 1;
	QueuePacket( connections, cn, &packet, 1 );
}

void RecvSaveOpenSchoolEvent( t_packet *p, short int cn )
{
	char *name = p->u.kein.openschool_data.name;
	int item_no = p->u.kein.openschool_data.item_no;
	int server_id = p->u.kein.openschool_data.server_id;
	int nation = p->u.kein.openschool_data.nation;
	int npc_id = p->u.kein.openschool_data.npc_id;
	
	int number;
	t_packet packet;
	int ret = SaveOpenSchoolItem( name, nation, item_no, number );
	if( number > 10 ) number = 10;
	switch( ret )
	{
	case 1  :		// Á¦´ë·Î ¼º°ø number °ªÀ» ÀÌ¿ë
		packet.u.kein.openschool_data_ok.number = number;
		break;
		
	case -1 :		// ÀÌ¹Ì ÀÖ´Â ³ðÀÌ ¶Ç ÀúÀåÇÏ·Á°í ÇÑ´Ù.
		packet.u.kein.openschool_data_ok.number = -1;
		break;
	case -2 :	return;  // Äõ¸® ½ÇÆÐ
	}
	
	packet.h.header.type = CMD_OPENSCHOOL_DATA_OK;
	packet.u.kein.openschool_data_ok.server_id = server_id;
	packet.u.kein.openschool_data_ok.item_no= item_no;
	packet.u.kein.openschool_data_ok.npc_id= npc_id;
	packet.h.header.size = sizeof( k_openschool_data_ok );
	QueuePacket( connections, cn, &packet, 1 );
}

// 030602 YGI
void RecvExitGiild( t_packet *p, short int cn )
{	//< CSD-030326
	short int server_id = p->u.kein.guild_exit_global.server_id;
	short int guild_code = p->u.kein.guild_exit_global.guild_code;
	char *name = p->u.kein.guild_exit_global.name;
	
	CCharRank name_status;
	DWORD status;
	GetNationByName( name, &status );		// ´ë»óÀÇ ±æµå³» µî±Þ°ª °¡Á®¿À±â
	memcpy( &name_status, &status, sizeof(DWORD ) );

	int target_guild_code = 0;				// ´ë»óÀÇ ±æµå ÄÚµå°ª °¡Á®¿À±â
	GetGuildCode( name, target_guild_code );

	t_packet packet;
	
	// °°Àº ±æµå¿øÀÌ ¾Æ´Ï°Å³ª ´ë»óÀÌ ±æ¸¶ÀÎ °æ¿ì	// 020702 YGI
	if(target_guild_code != guild_code || name_status.guild_master == 1)
	{
		packet.h.header.type = CMD_GUILD_EXIT_COMMAND_GLOBAL_NOT;
		packet.u.kein.default_short_int = server_id;
		packet.h.header.size = sizeof( short int );
		QueuePacket( connections, cn, &packet, 1 );	
		return;	
	}

	SetGuildCode( name, 0 );
	name_status.guild_master = 0;
	memcpy( &status, &name_status, sizeof( DWORD ) );
	SetNationByName( status, name );
	
	packet.h.header.type = CMD_GUILD_EXIT_COMMAND_GLOBAL_OK;		// guild Å»Åð		// ±æµåÂ¯¿¡°Ô ¼º°øÇß´Ù°í ¾Ë¸°´Ù.
	packet.u.kein.default_short_int = server_id;
	packet.h.header.size = sizeof( short int );
	QueuePacket( connections, cn, &packet, 1 );
	
	
	packet.h.header.type = CMD_GUILD_EXIT_COMMAND_GLOBAL_LET;		// guild Å»Åð		// ±æµåÂ¯¿¡°Ô ¼º°øÇß´Ù°í ¾Ë¸°´Ù.
	strcpy( packet.u.kein.default_name, name );
	packet.h.header.size = strlen( name )+1;
	
	g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
	
	ChangeGuildMemberList( name, 0, 0 );		// guild_member_list ¿¡¼­ »èÁ¦ ½ÃÅ²´Ù.
}	//> CSD-030326

void RecvCheckCandy( t_packet *p )
{
	DWORD total_id = p->u.kein.eat_candy.total_id;	// ¿©ÀÚ ¾ÆÀÌµð
	DWORD limit = p->u.kein.eat_candy.candy_limit;	// »çÅÁÀ» ÁØ ³²ÀÚ ¾ÆÀÌµð
	char *name = p->u.kein.eat_candy.name;		// »çÅÁÀ» ¹ÞÀº ¿©ÀÚ
	
	char target_name[20];		// ÃÊÄÝ·¿À» ¹ÞÀº ³²ÀÚ
	char target_name2[20];		// »çÅÁÀ» ÁØ ³²ÀÚ ÀÌ¸§
	
	int ret = GetChocolateEatName( target_name, total_id );
	if( ret != 1 ) return;		// ÃÊÄÝ·¿À» ÁÖÁö ¾Ê¾Ò´Ù.
	
	ret = GetNameByTotalId( target_name2, limit );
	if( ret != 1 ) return;		// ¾ø´Â ÅäÅ»¾ÆÀÌµð
	
	if( strcmp( target_name, target_name2 ) == 0 )		// ÃÊÄÝ·¿À» ¹ÞÀº ³²ÀÚ¿Í »çÅÁÀ» ÁØ ³²ÀÚ°¡ µ¿ÀÏÀÎÀÌ´Ù.
	{
		// ÀÌº¥Æ® ¼º°ø
		SaveWhiteDayEvent( target_name, name );
		// ¸ðµç ¸Ê¿¡ ¾Ë¸°´Ù.
		
		t_packet packet;
		packet.h.header.type = CMD_EAT_CANDY_OK;		// guild Å»Åð		// ±æµåÂ¯¿¡°Ô ¼º°øÇß´Ù°í ¾Ë¸°´Ù.
		strcpy( packet.u.kein.name2.name1, target_name );
		strcpy( packet.u.kein.name2.name2, name );
		packet.h.header.size = sizeof( k_name2 );
		g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
		
	}
}
SItemAttr3 Soksungattr3;
extern SItemchange itemchange[MAX_CHANGE_ITEM_COUNT];
DWORD addSokSung(int SokSung,int NowGrade)
{
	DWORD lastsok=0;
	Soksungattr3.grade = NowGrade;
	Soksungattr3.soksung1= SokSung;
	memcpy(&lastsok,&Soksungattr3,sizeof(Soksungattr3));
	return lastsok;
	
}
//010708 lsw
void ChangeOldRareToNewRare(ItemAttr *item)
{
	
	int no = item->item_no;
	
	int mid ; 
	int left = 0;
	int right = ichangeItemCount;
	
	if( no < itemchange[left].origin_item_no || no > itemchange[right].origin_item_no)
		return;//¾È°É¸° ¾ÆÅÛÀÏ °æ¿ì
	
	while( right >=left)
	{
		mid = (right+left)/2;
		if( no == itemchange[mid].origin_item_no)
		{
			item->item_no = itemchange[mid].will_change_item_no;
			item->attr[IATTR_SOKSUNG] = addSokSung(itemchange[mid].add_soksung,itemchange[mid].add_grade);
			return;
		}
		if( no < itemchange[mid].origin_item_no)
			right = mid-1;
		else
			left = mid +1;
	}
	return;	
}

// 010613 YGI
void ResetCharDB( int *var, CHARLIST *ch )		// var º¯¼ö¸¦ ÀÌ¿ëÇÏ¿© db¸¦ ÃÊ±âÈ­ÇÑ´Ù.	// °ÔÀÓ¼­¹ö¿¡¼­ ¿äÃ»ÇÒ¶§
{
	// 2°¡ÁöÀÇ Á¦¾àÀÌ ÀÖ´Ù.
	// 1. gameserver·Î º¸³¾¶§¸¸ »ç¿ëÇÑ´Ù. Áï, Å¬¶óÀÌ¾ðÆ®´Â ´Ù¸¥ ³»¿ëÀÌ º¸³»Áú¼ö ÀÖ´Ù´Â ¶æÀÌ´Ù.
	int ret = 0;
	if( var[VAR_RESET] < 2 )
	{
		memset( &ch->WinLoseScore, 0, sizeof( DWORD ) );
		ch->LadderScore = 1000;
		var[VAR_RESET] = 2;
	}
	
	//this4 lsw //¿¹ÀüÀÇ ¹ö±× ¾ÆÀÌÅÛÀÇ ¼Ó¼º°ªÀÇ ÃÊ±âÈ­
	if( var[VAR_RESET] < 3 )
	{
		// ³»°¡ °¡Áö°í ÀÖ´Â ¾ÆÀÌÅÛ..
		
		for(int iInv1 = 0;iInv1<3;iInv1++)
		{
			for(int iInv2 = 0;iInv2<3;iInv2++)
				for(int iInv3 = 0;iInv3<8;iInv3++)
				{	
					if(ch->inv[iInv1][iInv2][iInv3].item_no)	ch->inv[iInv1][iInv2][iInv3].attr[3]=0;
				}
		}
		
		for(int iEquip = 0;iEquip<8;iEquip++)
		{	
			if(ch->equip[iEquip].item_no)
				ch->equip[iEquip].attr[3]=0;	
		}
		
		for(int iQuick = 0;iQuick<7;iQuick++)
		{	
			if(ch->quick[iQuick].item_no)
				ch->quick[iQuick].attr[3]=0;
		}
		if(ch->handheld.item_no)
			ch->handheld.attr[3]=0;
		
		
		for(int iBank = 0;iBank<5;iBank++)
		{
			for(int iBank = 0;iBank<3;iBank++)
				for(int iBank = 0;iBank<6;iBank++)
				{
					if(ch->bank[iBank][iBank][iBank].item_no)
						ch->bank[iBank][iBank][iBank].attr[3]=0;
				}
		}
		var[VAR_RESET] = 3;
	}
	
	// 010531 KHS
	// ÀÏ½ºÃß°¡µÇ¸é¼­ nut1,nut2,nut3ÀÇ °ªÀ» ÃÊ±âÈ­ ÇÑ´Ù. 
	if( var[VAR_RESET] < 5 )
	{	
		ch->nk[N_VYSEUS] = 0;
		ch->nk[N_ZYPERN] = 0;
		ch->nk[N_YILSE] = 0;
		var[VAR_RESET] = 5;
	}	
	
	if( var[VAR_RESET] < 6 )			// 010608 YGI
	{
		if( ch->LastLoan > 10000000 )
		{
			ch->LastLoan = 0;
		}
		var[VAR_RESET] = 6;
	}
	
	
	if( var[VAR_RESET] < 12 )
	{	//< CSD-030326
		if( ch->name_status.dwReserved )
		{
			int make_num = 0;
			int ret = GetGuildMakeNumber( ch->name_status.dwReserved, make_num );
			if( ret == 1 )
			{
				if( make_num )		// ÀÌ¹Ì ¹Ù²ïÀûÀÌ ÀÖ´Â ±æµå´Ù.
				{
					ch->name_status.dwReserved = 0;
					ch->name_status.guild_master = 0;
				}
				else
				{
					ChangeGuildMemberList( ch->Name, ch->name_status.dwReserved, ch->name_status.guild_master );
				}
				var[VAR_RESET] = 12;
			}
			else 
			{
				MyLog( LOG_NORMAL, " Warning!!! guild_list table Querry fail... Path ResetCharDB function" );
			}
		}
		else var[VAR_RESET] = 12;
	}	//> CSD-030326
	
	
	if (var[VAR_RESET]<13)
	{
		ch->fame=1000;
		var[VAR_RESET]=13;
	}
	
	//< CSD-011022
	if (var[VAR_RESET] < 14)
	{
		// ±âÁ¸¿¡ ³ª´©±â 3À¸·Î ÀÖ´ø °ªÀ» ¿ø»óÅÂ·Î º¯È¯
		ch->Hp *= 3;
		ch->HpMax *= 3;
		// ÀúÇ×·ÂÀ» 100À¸·Î ÃÊ±âÈ­
		ch->nPoison = 100;
		ch->nCurse = 100;
		ch->nFire = 100;
		ch->nIce = 100;
		ch->nElect = 100;
		ch->nHoly = 100;
		var[VAR_RESET] = 14;
	}
	
	//< CSD-011024
	if (var[VAR_RESET] < 20)
	{
		// Å¬·¡½º ´Ü°è¿¡ °üÇÑ Á¤º¸ ÃÊ±âÈ­
		memset(ch->aStepInfo, 0, sizeof(ch->aStepInfo));
		// °æÇèÄ¡ ÀçºÐ¹è
		if (ch->Level >= 99)
		{
			const int nOffset = ch->Exp - 1917766395;
			
			if (nOffset > 0)
			{
				int nBouns = nOffset/10000000;
				if (nBouns > 24)  nBouns = 24;
				ch->reserved_point += nBouns;
				ch->Exp = 1917766395;
				ch->Level = 99;
			}
		}
		// ÅÃÆ½ °æÇèÄ¡ ÀçºÐ¹è
		for (int i = 0; i < 13; ++i)
		{
			const int nOffset = ch->tac_skillEXP[i] - 1917766395;
			
			if (nOffset > 0)
			{
				ch->tac_skillEXP[i] = 1917766395;
			}
		}
		var[VAR_RESET] = 20;
	}
	
	if( var[VAR_RESET] < 22 )
	{	/*
		if( ch->name_status.guild_code )
		{
		if( ch->name_status.guild_master == 1 )
		{
		char querry[256];
		sprintf( querry, "UPDATE guild_list SET master = '%s' WHERE code = %d", ch->Name,  ch->name_status.guild_code );
		Querry_SQL( querry );
		}
		}
		else
		{
		ChangeGuildMemberList( ch->Name, 0, 0 );
	}*/
		var[VAR_RESET] = 22;
	}
	if (var[VAR_RESET] < 23)//030701 LSW
	{
		ch->nPoison		= 70;
		ch->nCurse		= 70;
		ch->nFire		= 70;
		ch->nIce		= 70;
		ch->nElect		= 70;
		ch->nHoly		= 70;
		var[VAR_RESET]	= 23;
	}

}

//< CSD-030306
struct LEVEL_INFO
{
	int nLevel;
	int nStep;
	int nMinExp;
	int nMaxExp;
};

LEVEL_INFO g_aLevelInfo[] =
{
	{0,	  0, 0	,0},
	{1,   0, 0	,259},
	{2	, 0, 260	,1131},
	{3	, 0, 1132	,3066},
	{4	, 0, 3067	,6570},
	{5	, 0, 6571	,12238},
	{6	, 0, 12239	,20768},
	{7	, 0, 20769	,32994},
	{8	, 0, 32995	,49905},
	{9	, 0, 49906	,72669},
	{10	, 0, 72670	,102659},
	{11	, 0, 102660	,141475},
	{12	, 0, 141476	,190970},
	{13	, 0, 190971	,253272},
	{14	, 0, 253273	,330811},
	{15	, 0, 330812	,426338},
	{16	, 0, 426339	,542955},
	{17	, 0, 542956	,684133},
	{18	, 0, 684134	,853742},
	{19	, 0, 853743	,1056070},
	{20	, 0, 1056071	,1295850},
	{21	, 0, 1295851	,1578282},
	{22	, 0, 1578283	,1909058},
	{23	, 0, 1909059	,2294389},
	{24	, 0, 2294390	,2741021},
	{25	, 0, 2741022	,3256269},
	{26	, 0, 3256270	,3848031},
	{27	, 0, 3848032	,4524821},
	{28	, 0, 4524822	,5295788},
	{29	, 0, 5295789	,6170740},
	{30	, 0, 6170741	,7160170},
	{31	, 0, 7160171	,8275278},
	{32	, 0, 8275279	,9527997},
	{33	, 0, 9527998	,10931015},
	{34	, 0, 10931016	,12497802},
	{35	, 0, 12497803	,14242629},
	{36	, 0, 14242630	,16180598},
	{37	, 0, 16180599	,18327660},
	{38	, 0, 18327661	,20700645},
	{39	, 0, 20700646	,23317281},
	{40	, 0, 23317282	,26196220},
	{41	, 0, 26196221	,29357064},
	{42	, 0, 29357065	,32820385},
	{43	, 0, 32820386	,36607752},
	{44	, 0, 36607753	,40741752},
	{45	, 0, 40741753	,45246020},
	{46	, 0, 45246021	,50145254},
	{47	, 0, 50145255	,55465248},
	{48	, 0, 55465249	,61232911},
	{49	, 0, 61232912	,67476291},
	{50	, 0, 67476292	,74224601},
	{51	, 0, 74224602	,81508241},
	{52	, 0, 81508242	,89358824},
	{53	, 0, 89358825	,97809198},
	{54	, 0, 97809199	,106893473},
	{55	, 0, 106893474	,116647040},
	{56	, 0, 116647041	,127106601},
	{57	, 0, 127106602	,138310187},
	{58	, 0, 138310188	,150297188},
	{59	, 0, 150297189	,163108372},
	{60	, 0, 163108373	,176785912},
	{61	, 0, 176785913	,191373408},
	{62	, 0, 191373409	,206915912},
	{63	, 0, 206915913	,223459955},
	{64	, 0, 223459956	,241053563},
	{65	, 0, 241053564	,259746291},
	{66	, 0, 259746292	,279589237},
	{67	, 0, 279589238	,300635075},
	{68	, 0, 300635076	,322938074},
	{69	, 0, 322938075	,346554122},
	{70	, 0, 346554123	,371540752},
	{71	, 0, 371540753	,397957164},
	{72	, 0, 397957165	,425864251},
	{73	, 0, 425864252	,455324621},
	{74	, 0, 455324622	,486402624},
	{75	, 0, 486402625	,519164371},
	{76	, 0, 519164372	,553677763},
	{77	, 0, 553677764	,590012514},
	{78	, 0, 590012515	,628240171},
	{79	, 0, 628240172	,668434143},
	{80	, 0, 668434144	,710669722},
	{81	, 0, 710669723	,755024110},
	{82	, 0, 755024111	,801576439},
	{83	, 0, 801576440	,850407798},
	{84	, 0, 850407799	,901601254},
	{85	, 0, 901601255	,955241881},
	{86	, 0, 955241882	,1011416780},
	{87	, 0, 1011416781	,1070215102},
	{88	, 0, 1070215103	,1131728077},
	{89	, 0, 1131728078	,1196049033},
	{90	, 0, 1196049034	,1263273423},
	{91	, 0, 1263273424	,1333498847},
	{92	, 0, 1333498848	,1406825078},
	{93	, 0, 1406825079	,1483354084},
	{94	, 0, 1483354085	,1563190055},
	{95	, 0, 1563190056	,1646439422},
	{96	, 0, 1646439423	,1733210887},
	{97	, 0, 1733210888	,1823615441},
	{98	, 0, 1823615442	,1917766394},
	{99	, 0, 1917766395	,2015779394},
	{100, 0, 2015779395	,2115779395},
	{101, 1, 0	,105737093},
	{102, 1, 105737094	,215336234},
	{103, 1, 215336235	,328797422},
	{104, 1, 328797423	,446120657},
	{105, 1, 446120658	,567305939},
	{106, 1, 567305940	,692353268},
	{107, 1, 692353269	,821262644},
	{108, 1, 821262645	,954034067},
	{109, 1, 954034068	,1090667537},
	{110, 1, 1090667538	,1231163054},
	{111, 1, 1231163055	,1375520618},
	{112, 1, 1375520619	,1523740229},
	{113, 1, 1523740230	,1675821887},
	{114, 1, 1675821888	,1831765592},
	{115, 1, 1831765593	,1991571344},
	{116, 2, 0	,163667798},
	{117, 2, 163667799	,331197644},
	{118, 2, 331197645	,502589537},
	{119, 2, 502589538	,677843477},
	{120, 2, 677843478	,856959464},
	{121, 2, 856959465	,1039937498},
	{122, 2, 1039937499	,1226777579},
	{123, 2, 1226777580	,1417479707},
	{124, 2, 1417479708	,1612043882},
	{125, 2, 1612043883	,1810470104},
	{126, 2, 1810470105	,2012758373},
	{127, 3, 0	,206150315},
	{128, 3, 206150316	,416162678},
	{129, 3, 416162679	,630037088},
	{130, 3, 630037089	,847773545},
	{131, 3, 847773546	,1069372049},
	{132, 3, 1069372050	,1294832600},
	{133, 3, 1294832601	,1524155198},
	{134, 3, 1524155199	,1757339843},
	{135, 3, 1757339844	,1994386535},
	{136, 4, 0	,240908738},
	{137, 4, 240908739	,485679524},
	{138, 4, 485679525	,734312357},
	{139, 4, 734312358	,986807237},
	{140, 4, 986807238	,1243164164},
	{141, 4, 1243164165	,1503383138},
	{142, 4, 1503383139	,1767464159},
	{143, 4, 1767464160	,2035407227},
	{144, 5, 0	,271805114},
	{145, 5, 271805115	,547472276},
	{146, 5, 547472277	,827001485},
	{147, 5, 827001486	,1110392741},
	{148, 5, 1110392742	,1397646044},
	{149, 5, 1397646045	,1688761394},
	{150, 5, 1688761395	,1983738791},
	{151, 6, 0	,298839443},
	{152, 6, 298839444	,601540934},
	{153, 6, 601540935	,908104472},
	{154, 6, 908104473	,1218530057},
	{155, 6, 1218530058	,1532817689},
	{156, 7, 0	,318149678},
	{157, 7, 318149679	,640161404},
	{158, 7, 640161405	,966035177},
	{159, 7, 966035178	,1295770997},
	{160, 7, 1295770998	,1629368864},
	{161, 7, 1629368865	,1966828778},
	{162, 8, 0	,341321960},
	{163, 8, 341321961	,686505968},
	{164, 8, 686505969	,1035552023},
	{165, 8, 1035552024	,1388460125},
	{166, 8, 1388460126	,1745230274},
	{167, 8, 1745230275	,2105862470},
	{168, 9, 0	,364494242},
	{169, 9, 364494243	,732850532},
	{170, 9, 732850533	,1105068869},
	{171, 9, 1105068870	,1481149253},
	{172, 10, 0	,379942430},
	{173, 10, 379942431	,763746908},
	{174, 10, 763746909	,1151413433},
	{175, 10, 1151413434	,1542942005},
	{176, 10, 1542942006	,1938332624},
	{177, 11, 0	,399252665},
	{178, 11, 399252666	,802367378},
	{179, 11, 802367379	,1209344138},
	{180, 11, 1209344139	,1620182945},
	{181, 11, 1620182946	,2034883799},
	{182, 12, 0	,418562900},
	{183, 12, 418562901	,840987848},
	{184, 12, 840987849	,1267274843},
	{185, 12, 1267274844	,1697423885},
	{186, 12, 1697423886	,2131434974},
	{187, 13, 0	,437873135},
	{188, 13, 437873136	,879608318},
	{189, 13, 879608319	,1325205548},
	{190, 13, 1325205549	,1774664825},
	{191, 14, 0	,453321323},
	{192, 14, 453321324	,910504694},
	{193, 14, 910504695	,1371550112},
	{194, 14, 1371550113	,1836457577},
	{195, 15, 0	,468769511},
	{196, 15, 468769512	,941401070},
	{197, 15, 941401071	,1417894676},
	{198, 15, 1417894677	,1898250329},
	{199, 16, 0	,484217699},
	{200, 16, 484217700	,972297446}
};
//> CSD-030306

void ReadjustExpLevel(CHARLIST* pTarget)
{	//< CSD-030306 : ·¹º§ °æÇèÄ¡¸¦ Àç¼³Á¤ÇÏ¸é¼­ ±âÁ¸ÀÇ °æÇèÄ¡, ´Ü°è°ª ÀçÁ¶Á¤
	const int nLevel = pTarget->Level;
	
	if (nLevel >= 101)
	{
		if (nLevel <= MAX_EXP_LEVEL)
		{
			pTarget->Exp = NPC_Lev_Ref[nLevel].nMaxExp;
			pTarget->aStepInfo[EXP_STEP] = NPC_Lev_Ref[nLevel].nStep;
		}
		else
		{
			pTarget->Level = MAX_EXP_LEVEL;
			pTarget->Exp = NPC_Lev_Ref[MAX_EXP_LEVEL].nMaxExp;
			pTarget->aStepInfo[EXP_STEP] = NPC_Lev_Ref[MAX_EXP_LEVEL].nStep;
		}
	}
}

void ReadjustTacLevel(CHARLIST* pTarget, BYTE nKind)
{	//< CSD-030306 : ÅÃÆ½ °æÇèÄ¡¸¦ Àç¼³Á¤ÇÏ¸é¼­ ±âÁ¸ÀÇ °æÇèÄ¡, ´Ü°è°ª ÀçÁ¶Á¤
	for (int i = 1; i <= MAX_TAC_LEVEL; ++i)
	{
		if (pTarget->aStepInfo[T01_STEP + nKind] == g_aLevelInfo[i].nStep && 
			pTarget->tac_skillEXP[nKind] <= g_aLevelInfo[i].nMaxExp)
		{
			const int nTactic = i;

			if (nTactic > 100)
			{
				pTarget->tac_skillEXP[nKind] = NPC_Lev_Ref[i].nMaxExp;
				pTarget->aStepInfo[T01_STEP + nKind] = NPC_Lev_Ref[i].nStep;
			}

			return;
		}
	}

	pTarget->tac_skillEXP[nKind] = NPC_Lev_Ref[MAX_TAC_LEVEL].nMaxExp;
	pTarget->aStepInfo[T01_STEP + nKind] = NPC_Lev_Ref[MAX_TAC_LEVEL].nStep;
}	//> CSD-030306

void CheckNewGuildCode( CHARLIST *ch )
{	//< CSD-030324
	if( ch->Age < 136 )
	{
		ch->nGuildCode = ch->name_status.dwReserved;
		ch->Age = 136;
	}
	//> CSD-030324
}

void ResetCharInfo(int *var, CHARLIST *ch)
{ 
	if (ch->Age <= 100 || var[VAR_RESET] < 22)
	{	//< CSD-TW-030606
		ResetCharDB(var, ch);
		ch->Age = var[VAR_RESET] + 100;
	}	//> CSD-TW-030606

	char querry[256];
	
	if(ch->Age < 124)
	{	//< CSD-030326
		if( ch->name_status.dwReserved )
		{
			if( IsExistGiuildMember( ch->Name ) == 0 )		// ±æµå¿¡ ¼ÓÇØ ÀÖÁö ¾ÊÀ»¶§..
			{
				ch->name_status.dwReserved = 0;
				ch->name_status.guild_master = 0;
			}
			else if( ch->name_status.guild_master == 1 )
			{
				sprintf( querry, "UPDATE guild_list SET master = '%s' WHERE code = %d", ch->Name,  ch->name_status.dwReserved );
				Querry_SQL( querry );
			}
		}

		ch->Age = 124;
	}	//> CSD-030326
	
	if( ch->Age  < 125 )
	{
		for(int iInv1 = 0;iInv1<3;iInv1++)
		{
			for(int iInv2 = 0;iInv2<3;iInv2++)
				for(int iInv3 = 0;iInv3<8;iInv3++)
				{	
					if(ch->inv[iInv1][iInv2][iInv3].item_no)
						ChangeOldRareToNewRare( &ch->inv[iInv1][iInv2][iInv3] );
				}
		}
		
		for(int iEquip = 0;iEquip<8;iEquip++)
		{	
			if(ch->equip[iEquip].item_no)
				ChangeOldRareToNewRare( &ch->equip[iEquip] );
		}
		
		for(int iQuick = 0;iQuick<7;iQuick++)
		{	
			if(ch->quick[iQuick].item_no)
				ChangeOldRareToNewRare( &ch->quick[iQuick] );
		}
		
		if(ch->handheld.item_no)
			ChangeOldRareToNewRare( &ch->handheld );
		
		
		for(int iBank1 = 0;iBank1<5;iBank1++)
		{
			for(int iBank2 = 0;iBank2<3;iBank2++)
				for(int iBank3 = 0;iBank3<6;iBank3++)
				{
					if(ch->bank[iBank1][iBank2][iBank3].item_no)
						ChangeOldRareToNewRare( &ch->bank[iBank1][iBank2][iBank3]);
				}
		}
		ch->Age  = 125;
	}
	
	if( ch->Age  < 126 )
	{
		ch->Sight = 0;
		ch->Age  = 126;
	}
	
	if (ch->Age < 129)
	{
		ch->aStepInfo[CSP_STEP] = 0;
		
		for (int i = LIGHTNING_BOOM; i <= WIND_EXTREME; ++i)
		{
			ch->Skill[i - 100] = 0;
		}
		
		ch->Age = 129;
	}
	
	if (ch->Age < 130)
	{
		ch->aStepInfo[CSP_STEP] = 0;
		
		for (int i = LIGHTNING_BOOM; i <= WIND_EXTREME; ++i)
		{
			ch->Skill[i - 100] = 0;
		}
		
		ch->Age = 130;
	}
	
	if (ch->Age < 132)
	{	//< CSD-020724 : ÀüÅõ½ºÅ³ Æ÷ÀÎÅÍ ÀçºÐ¹è
		int nSum = ch->aStepInfo[CSP_STEP];
		
		for (int i = LIGHTNING_BOOM; i <= WIND_EXTREME; ++i)
		{
			nSum += ch->Skill[i - 100];
			ch->Skill[i - 100] = 0;
		}
		
		ch->aStepInfo[CSP_STEP] = nSum;
		ch->Age = 132;
	}	//> CSD-020724
	
	if (ch->Age < 133)
	{	//< CSD-020724 : ÀüÅõ½ºÅ³ Æ÷ÀÎÅÍ ÀçºÐ¹è  
		const int nPoint = GetSkillPoint(ch->Name);
		// ÀüÅõ½ºÅ³ Æ÷ÀÌÅÍ ÃÑÇÕ
		int nTotal = ch->aStepInfo[CSP_STEP] + nPoint;
		
		if (ch->Level >= 1 && ch->Level <= 10)
		{
			if (nTotal > 1)  nTotal = 1;
		}
		else if (ch->Level >= 11 && ch->Level <= 15)
		{
			if (nTotal > 2)  nTotal = 2;
		}
		else if (ch->Level >= 16 && ch->Level <= 20)
		{
			if (nTotal > 3)  nTotal = 3;
		}
		else if (ch->Level >= 21 && ch->Level <= 25)
		{
			if (nTotal > 4)  nTotal = 4;
		}
		else if (ch->Level >= 26 && ch->Level <= 30)
		{
			if (nTotal > 5)  nTotal = 5;
		}
		else if (ch->Level >= 31 && ch->Level <= 35)
		{
			if (nTotal > 6)  nTotal = 6;
		}
		else if (ch->Level >= 36 && ch->Level <= 40)
		{
			if (nTotal > 7)  nTotal = 7;
		}
		else if (ch->Level >= 41 && ch->Level <= 45)
		{
			if (nTotal > 8)  nTotal = 8;
		}
		else if (ch->Level >= 46 && ch->Level <= 50)
		{
			if (nTotal > 9)  nTotal = 9;
		}
		else if (ch->Level >= 51 && ch->Level <= 55)
		{
			if (nTotal > 10)  nTotal = 10;
		}
		else if (ch->Level >= 56 && ch->Level <= 60)
		{
			if (nTotal > 11)  nTotal = 11;
		}
		else if (ch->Level >= 61 && ch->Level <= 65)
		{
			if (nTotal > 12)  nTotal = 12;
		}
		else if (ch->Level >= 66 && ch->Level <= 70)
		{
			if (nTotal > 13)  nTotal = 13;
		}
		else if (ch->Level >= 71 && ch->Level <= 75)
		{
			if (nTotal > 14)  nTotal = 14;
		}
		else if (ch->Level >= 76 && ch->Level <= 80)
		{
			if (nTotal > 15)  nTotal = 15;
		}
		else if (ch->Level >= 81 && ch->Level <= 85)
		{
			if (nTotal > 16)  nTotal = 16;
		}
		else if (ch->Level >= 86 && ch->Level <= 90)
		{
			if (nTotal > 17)  nTotal = 17;
		}
		else if (ch->Level >= 91 && ch->Level <= 95)
		{
			if (nTotal > 18)  nTotal = 18;
		}
		else if (ch->Level >= 96 && ch->Level <= 100)
		{
			if (nTotal > 19)  nTotal = 19;
		}
		else
		{
			if (nTotal > 20)  nTotal = 20;
		}
		
		ch->aStepInfo[CSP_STEP] = nTotal;
		ClearSkillPoint(ch->Name);
		
		ch->Age = 133;
	}	//> CSD-020724
	
	if(LocalMgr.IsAbleNation(KOREA))//021007 lsw// ÇÑ±¹¸¸ ÀçºÐ¹è ÇØÁØ´Ù.
	{
		if (ch->Age < 134)
		{ //< CSD-020930 : ÀüÅõ½ºÅ³ Æ÷ÀÎÅÍ ÀçºÐ¹è
			int nSum = ch->aStepInfo[CSP_STEP];
			
			for (int i = LIGHTNING_BOOM; i <= WIND_EXTREME; ++i)
			{
				nSum += ch->Skill[i - 100];
				ch->Skill[i - 100] = 0;
			}
			ch->aStepInfo[CSP_STEP] = nSum;
			ch->Age = 134;
		} //> CSD-020930
	}

	if (ch->Age < 135)
	{	//< CSD-030326
		ch->nGuildCode = ch->name_status.dwReserved;
		ch->Age = 135;
	}	//> CSD-030326

	if (ch->Age < 136)
	{	//< CSD-030306
		// ·¹º§ °æÇèÄ¡¸¦ Àç¼³Á¤ÇÏ¸é¼­ ±âÁ¸ÀÇ °æÇèÄ¡, ´Ü°è°ª ÀçÁ¶Á¤
		ReadjustExpLevel(ch);
		// ÅÃÆ½ °æÇèÄ¡¸¦ Àç¼³Á¤ÇÏ¸é¼­ ±âÁ¸ÀÇ °æÇèÄ¡, ´Ü°è°ª ÀçÁ¶Á¤
		for (int i = 0; i < 13; ++i)
		{
			ReadjustTacLevel(ch, i);
		}

		ch->Age = 136;
	}	//> CSD-030306
	
	if (ch->Age < 137)
	{	//< CSD-TW-030620
		for (int i = T01_STEP; i <= T13_STEP; ++i)
		{
			if (ch->aStepInfo[i] >= 31)
			{
				++ch->aStepInfo[i];
			}

			if (ch->aStepInfo[i] >= 38)
			{
				++ch->aStepInfo[i];
			}

			if (ch->aStepInfo[i] > NPC_Lev_Ref[MAX_TAC_LEVEL].nStep)
			{
				ch->aStepInfo[i] = NPC_Lev_Ref[MAX_TAC_LEVEL].nStep;
			}
		}

		ch->Age = 137;
	}	//> CSD-TW-030620

	if (LocalMgr.IsAbleNation(CHINA))
	{	//< CSD-HK-030829
		if (ch->Age < 138)
		{	// Áß±¹¿¡¼­¸¸ ¿äÃ»ÇÑ 1Â÷ °æÇèÄ¡ º¸»ó
			const int nLevel = ch->Level;
			ch->Exp = NPC_Lev_Ref[nLevel].nMaxExp;
			ch->aStepInfo[EXP_STEP] = NPC_Lev_Ref[nLevel].nStep;

			ch->Age = 138;
		}

		if (ch->Age < 139)
		{	// Áß±¹¿¡¼­¸¸ ¿äÃ»ÇÑ 2Â÷ °æÇèÄ¡ º¸»ó
			const int nLevel = ch->Level;
			ch->Exp = NPC_Lev_Ref[nLevel].nMaxExp;
			ch->aStepInfo[EXP_STEP] = NPC_Lev_Ref[nLevel].nStep;

			ch->Age = 139;
		}
	}	//> CSD-HK-030829

	if (LocalMgr.IsAbleNation(HONGKONG))
	{	//<soto-031031
		if (ch->Age < 140)
		{	// È«Äá¿¡¼­¸¸ ¿äÃ»ÇÑ 1Â÷ °æÇèÄ¡ º¸»ó
			const int nLevel = ch->Level;
			ch->Exp = NPC_Lev_Ref[nLevel].nMaxExp;
			ch->aStepInfo[EXP_STEP] = NPC_Lev_Ref[nLevel].nStep;

			ch->Age = 140;
		}		
	}	//>soto-031031

	if (!IsConnectName(ch->Name))
	{ // Ä³¸¯ÅÍ ·Î±×ÀÎ ÇÒ ¶§ ±× Á¤º¸ ÀÔ·Â
		sprintf(querry, "INSERT INTO login_name (name) VALUES ('%s')", ch->Name);
		Querry_SQL(querry);
	}
	// ±æµå ÄÚµå°ªÀÌ ÀÖ´Âµ¥ guild_member_list ¿¡ °ªÀÌ ¾øÀ»¶§
	if( ch->nGuildCode )
	{	//< CSD-030324
		if( IsExistGiuildMember( ch->Name ) == 0 )		// ±æµå¿¡ ¼ÓÇØ ÀÖÁö ¾ÊÀ»¶§..
		{
			ch->nGuildCode = 0;
			ch->name_status.guild_master = 0;
		}
		if( ch->name_status.guild_master == 1 )		// ±æ¸¶ ÀÏ °æ¿ì ±æ¸¶ µé¾î ¿Â ½Ã°£À» °»½ÅÇÑ´Ù.
		{
			sprintf( querry, "UPDATE guild_list SET master = '%s', master_last_connect = getdate() WHERE code = %d", 
				ch->Name, 
				ch->nGuildCode );
			Querry_SQL( querry );
		}
	}	//> CSD-030324
}

void RecvUpdateLadderScore( t_packet *p )
{
	k_update_ladder_score *t = &p->u.kein.update_ladder_score;
	UpdateLadderScore(t->score, t->name, t->nation, t->cls, t->btLevel); // CSD-030806
}

void RecvReqRankLadder( t_packet *p, short int cn )
{
	k_db_get_ladder_score_rank rank_data;
	int page = p->u.kein.req_rank_ladder_to_db.page;
	short int server_id = p->u.kein.req_rank_ladder_to_db.server_id;
	int ret = GetLadderScoreRank( page*10+1, &rank_data );
	if( ret == 2 )		// refresh Çß´Ù..
		ret = GetLadderScoreRank( page*10+1, &rank_data );
	
	if( ret != 1 ) // °ªÀÌ ¾ø´Ù.
	{
		DirectClient( CMD_REP_RANK_LADDER_FINISH, server_id, cn, NULL, 0 );
	}
	else
	{
		DirectClient( CMD_REP_RANK_LADDER, server_id, cn, &rank_data, sizeof( k_db_get_ladder_score_rank ) );
	}
}

void DirectClient( short int type, short int server_id, short int cn, void *msg, int size )
{
	t_packet packet;
	packet.h.header.type = CMD_DIRECT_CLIENT;
	packet.u.kein.direct_client.server_id = server_id;
	packet.u.kein.direct_client.type = type;
	if( msg )
		memcpy( packet.u.kein.direct_client.data, msg, size );
	packet.h.header.size = sizeof( int ) + size;
	QueuePacket( connections, cn, &packet, 1 );
}

void RecvSearchRankLadder( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	char *name = p->u.kein.send_db_direct_map.data;
	
	int rank = GetRankLadderByName( name );			// 010514 YGI
	if( rank>0 )
	{
		t_packet packet;
		packet.u.kein.req_rank_ladder_to_db.page = rank/10;
		packet.u.kein.req_rank_ladder_to_db.server_id = server_id;
		
		RecvReqRankLadder( &packet, cn );
	}
	else
	{
		DirectClient( CMD_REQ_SEARCH_RENK_LADDER_FAIL, server_id, cn, NULL, 0 );
	}
}

int isPosableGuildJoinById( int guild_code, char *id )
{	//< CSD-030326
	int is_possible = 1;
	char name[4][20];
	memset(name, 0, sizeof(char)*4*20);

	if (GetCharacterNameInID(id, name) == 1)
	{
		for( int i=0; i<4 ; i++ )
		{
			if (name[i][0])
			{
				int nGuildCode = 0;

				if (GetGuildCode(name[i], nGuildCode))
				{
				
					if (nGuildCode > 0 && nGuildCode != guild_code) // ´Ù¸¥ ±æµå¿¡ µé¾î ÀÖÀ¸¸é
					{
						return 0;
					}
				}
			}
		}
	}

	return 1;
}	//> CSD-030326

int isInAGuildById( char *id ) //Eleval 13/06/09, to check if the player is guildless
{
	int is_possible = 1;
	char name[4][20];
	memset(name, 0, sizeof(char)*4*20);

	if (GetCharacterNameInID(id, name) == 1)
	{
		for( int i=0; i<4 ; i++ )
		{
			if (name[i][0])
			{
				int nGuildCode = 0;

				if (GetGuildCode(name[i], nGuildCode))
				{
				
					if (nGuildCode != 0)
					{
						return 0;
					}
				}
			}
		}
	}

	return 1;
}

int isPosableGuildJoinByName( int guild_code, char *name )
{
	char id[20];
	int ret = GetLoginIdByName( name, id );
	if( ret != 1 ) return -1;
	
	return isPosableGuildJoinById( guild_code, id );
}

void RecvRegistGuild_DB( t_packet *p, short int cn )
{
	short int server_id	= p->u.kein.regist_guild_imsi_db.server_id;
	char *master = p->u.kein.regist_guild_imsi_db.guild_ma;
	char guild_name[40];
	ConvertQueryString(p->u.kein.regist_guild_imsi_db.guild_name, guild_name, 20);

	int nation = p->u.kein.regist_guild_imsi_db.nation;
	int code, ret;	
	k_set_guild_info guild_info;
	t_packet packet;
	
	char fail_type = 0;
	int nRowCount = 0;
	char conditon[512];

	memset(&guild_info, 0, sizeof(k_set_guild_info)); // finito 070707
	
	
	// ´Ù¸¥ ±æµå¿¡ µé¾î ÀÖ´ÂÁö¸¦ Ã¼Å©
	if( !isPosableGuildJoinByName( 0, master ) ) 
	{
		// ±æµå ¸¶½ºÅÍ°¡ ´Ù¸¥ Ä³¸¯À¸·Î ±æµå¿¡ °¡ÀÔÇØ ÀÖ´Â °æ¿ì
		fail_type = 1;
		goto is_fail_;
	}
	ret = GetEmptyGuildCode( code );
	if( ret != 1 ) 
	{
		fail_type = 2;		// ±æµå°¡ ²Ë Ã¡À» °æ¿ì
		goto is_fail_;
	}
	
	sprintf( conditon, "name = '%s'", guild_name);
	ret = GetRowLineOfSQL( "guild_list", "name", &nRowCount, conditon );
	if( nRowCount > 0 )
	{
		// ¶È°°Àº ÀÌ¸§ÀÇ ±æµå°¡ Á¸ÀçÇÑ´Ù.
		fail_type = 4;			// db ÀúÀå¿¡ ½ÇÆÐÇß´Ù.
		goto is_fail_;
	}
	
	ret = SaveGuildRegistImsi( code, &p->u.kein.regist_guild_imsi_db, &guild_info );
	if( ret != 1 ) 
	{
		fail_type = 3;			// db ÀúÀå¿¡ ½ÇÆÐÇß´Ù.
		goto is_fail_;
	}
	else
	{
		// ¸ðµç ¼­¹ö¿¡ ÀÓ½Ã ±æµå µî·Ï»ç½ÇÀ» ¾Ë¸°´Ù.
		packet.h.header.type = CMD_REGIST_GUILD_IMSI_OK_ALL;
		packet.u.kein.set_guild_info = guild_info;
		//if( guild_info.guild_degree[0][0] )
			packet.h.header.size = sizeof( k_set_guild_info );
		//else
		//	packet.h.header.size = sizeof( k_set_guild_info ) - 100;// char degree[5][20];
		
		g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
		
		// ±× Ä³¸¯ÅÍ¿¡°Ô ¼º°ø »ç½ÇÀ» ¾Ë¸°´Ù.
		packet.h.header.type = CMD_REGIST_GUILD_IMSI_OK;
		packet.u.kein.regist_guild_imsi_ok.server_id = server_id;
		packet.u.kein.regist_guild_imsi_ok.guild_code = code;
		packet.h.header.size = sizeof( k_regist_guild_imsi_ok );
		QueuePacket( connections, cn, &packet, 1 );
		// ±æµå ¸â¹ö Å×ÀÌºí¿¡ ¸¶½ºÅÍ¸¦ ÀúÀå½ÃÅ²´Ù.
		ChangeGuildMemberList( master, code, 1 );
		SaveGuildLog( code, 0, 1, master, guild_name );		// 021008 YGI
		return;
	}
	
is_fail_ :
	// ½ÇÆÐ Àü¼Û 
	DirectClient( CMD_REGIST_GUILD_IMSI_FAIL, server_id, cn, &fail_type, 1 );
	SaveGuildLog( code, 0, 1, master, guild_name );		// 021008 YGI
	return;
	
}

void RecvReqGuildExplain( t_packet *p, short int cn )
{
	short int guild_code;
	memcpy( &guild_code, p->u.kein.send_db_direct_map.data, sizeof( short int ) );
	int server_id = p->u.kein.send_db_direct_map.server_id;
	
	int len = 0;
	k_guild_explain guild_info;
	guild_info.guild_code = guild_code;
	if( GetGuildExplain( guild_code, len, guild_info.explain ) == 1 )
	{
		DirectClient( CMD_REQ_GUILD_EXPLAIN, server_id, cn, &guild_info, 2+len );
	}
}

int CGuildMarkImage::InitData()
{
	data = NULL;
	faile = 0;
	total_size = 0;
	return 1;
}
int CGuildMarkImage::FreeData()
{
	if( data ) delete [] data;
	InitData();
	return 1;
}

int CGuildMarkImage::Setting(DWORD size, int xl, int yl )
{
	FreeData();		// ÀÌ¹Ì ÇÒ´çµÈÀûÀÌ ÀÖÀ¸¸é Áö¿ì°í ´Ù½Ã ÇÒ´ç.
	
	total_size = size+sizeof(k_image_header);
	data = new char[total_size];		// ½ÇÁ¦ ÀÌ¹ÌÁö¿¡ Çì´õ±îÁö ÇÒ´çÇÑ´Ù.
	k_image_header *img_header;
	img_header = (k_image_header *)data;
	img_header->size = size;
	img_header->xl = xl;
	img_header->yl = yl;
	
	return 1;
}

int CGuildMarkImage::SaveImage( int subCount, char *img, int size )
{
	if( !data ) return 0;		//ÃÊ±â ¼¼ÆÃÀ» ¾ÈÇÑ »óÅÂÀÌ´Ù.
	
	k_image_header *img_header;
	img_header = (k_image_header *)data;
	
	int headerSize = sizeof( k_image_header );
	int start_point = (subCount-1)*IMAGE_UNIT_SIZE+headerSize;
	if( start_point+size > total_size ) return 0;
	
	char *real_data = data+start_point ;
	memcpy( real_data, img, size );
	
	return 1;
}
///////////////////////////////////////////////////////////////////////////////

void RecvRegistGuildMark( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;

	k_regist_guild_mark	*pRegistGuildMark;
	pRegistGuildMark = (k_regist_guild_mark *)p->u.kein.send_db_direct_map.data;
	short int guildCode = pRegistGuildMark->guild_code;
	
	if (guildCode < 0) 
	{	//< CSD-030324
		return;
	}	//> CSD-030324
	
	if( pRegistGuildMark->sub_count == 1 )	// ¸ÇÃ³À½ ¹ÞÀº°ÍÀÌ¹Ç·Î µ¥ÀÌÅ¸¸¦ ¼¼ÆÃÇÑ´Ù.
	{
		if( pRegistGuildMark->size<= 0 || pRegistGuildMark->size > 1000000 ) 
		{
			g_GuildMarkImage[guildCode].faile = 1;
			return;// 1M ÀÌ»óÀÏ °æ¿ì
		}
		g_GuildMarkImage[guildCode].Setting( 
			pRegistGuildMark->size, pRegistGuildMark->xl, pRegistGuildMark->yl );
	}
	else
	{
		// Àü¿¡ ½ÇÆÐ ÇßÀ» °æ¿ì
		if( g_GuildMarkImage[guildCode].faile ) return;
	}
	
	int sub_size;
	if( pRegistGuildMark->sub_count == pRegistGuildMark->total )
	{
		sub_size = pRegistGuildMark->size % IMAGE_UNIT_SIZE;
	}
	else sub_size = IMAGE_UNIT_SIZE;
	
	// ÀÌ¹ÌÁö¸¦ ÀúÀåÇÏ°í
	if( g_GuildMarkImage[guildCode].SaveImage( 
		pRegistGuildMark->sub_count, 
		pRegistGuildMark->img, 
		sub_size ) != 1 )
	{
		g_GuildMarkImage[guildCode].faile = true;
		return;
	}
	
	// ÀÌ¹ÌÁö¸¦ ¸ðµÎ ¹Þ¾Ò´Ù¸é µðºñ¼­¹ö¿¡ ÀúÀåÇÑ´Ù.
	if( pRegistGuildMark->sub_count == pRegistGuildMark->total && !g_GuildMarkImage[guildCode].faile )
		// ½ÇÆÐ°¡ ¾ø¾úÀ»¶© DB¿¡ ÀúÀåÇÑ´Ù.
	{
		int ret = UpdateGuildMark( guildCode, pRegistGuildMark->size+sizeof( k_image_header ), 
			(UCHAR *)g_GuildMarkImage[guildCode].data );
		
		BYTE number;
		if( ret == 1 ) 
		{
			ret = IncreaseNumberOfGuildList( guildCode, 0, number );		// ÀÌ¹ÌÁö ¹øÈ£¸¦ Áõ°¡½ÃÄÑÁØ´Ù.
			if( ret == 1 )
			{
				// ÀÌ¹ÌÁö ¹øÈ£ Áõ°¡ »ç½ÇÀ» ¸ðµç ¸Ê ¼­¹ö¿¡°Ô ¾Ë·ÁÁØ´Ù.
				t_packet packet;
				packet.h.header.type = CMD_GUILD_NUMBER_INFO_DB_TO_MAP;
				packet.u.kein.set_guild_number_info.type = 0;		// ÀÌ¹ÌÁö ¹øÈ£
				packet.u.kein.set_guild_number_info.number = number;
				packet.u.kein.set_guild_number_info.guild_code = guildCode;
				packet.h.header.size = sizeof( k_set_guild_number_info );
				
				g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
				
				DirectClient( CMD_REFRESH_GUILD_CODE, server_id, cn, &guildCode, sizeof( short int ) );
			}
		}
		g_GuildMarkImage[guildCode].FreeData();
	}
}

void SendGuildImage( t_packet *p, short int cn )
{
	int guildCode = p->u.kein.regist_guild_imsi_ok.guild_code;
	int serverId = p->u.kein.regist_guild_imsi_ok.server_id;
	
	char *image;
	
	int size = GetGuildImageSize( guildCode );
	if( size <= 0 ) return;
	
	int mark_num;
	image = new char[size];
	int ret = GetGuildMarkImage( guildCode, image, size, mark_num );
	if( ret != 1 )
	{
		delete [] image;
		return;
	}
	
	int total = size / IMAGE_UNIT_SIZE + 1;
	
	k_guild_image guildImage;
	
	guildImage.guild_code = guildCode;
	guildImage.total = total;
	guildImage.mark_num = mark_num;
	
	int subSize;
	for( int i=1; i<=total; i++ )
	{
		if( i== total ) subSize = size % IMAGE_UNIT_SIZE;
		else subSize = IMAGE_UNIT_SIZE;
		
		guildImage.sub_count = i;
		memcpy( guildImage.img, (image+IMAGE_UNIT_SIZE*(i-1)), subSize );
		int packetSize = sizeof( k_guild_image)-IMAGE_UNIT_SIZE+subSize;
		DirectClient( CMD_GUILD_MARK_IMAGE, serverId, cn, &guildImage, packetSize );
	}
	//YGI 020523
	delete [] image;
}

// Á¤½Ä ±æµå µî·Ï
void RecvRegistGuild( t_packet *p, short int cn )
{	//< CSD-030324
	int server_id = p->u.kein.send_db_direct_map.server_id;
	k_guild_regist* pGuildRegist = (k_guild_regist*)p->u.kein.send_db_direct_map.data;
	int guildCode = pGuildRegist->guild_code;
	
	int	cCount = 0;	
	GetRowLineOfSQL( "guild_list", "*", &cCount, NULL );
	if( cCount <= 0 )
	{
		return;
	}
	
	vector<int> vtGuild;
	vtGuild.reserve(cCount);
	int ret = DeleteImsiGuild(&vtGuild, cCount);	// 20ÀÏ Áö³­ ÀÓ½Ã ±æµå¸¦ Ã£´Â´Ù.
	if( ret == 1 )
	{
		if( cCount )
		{
			t_packet packet;
			for( int i=0; i<cCount; i++ )
			{
				// 021118 YGI
				packet.u.kein.guild_instroduction_basic.guild_code = vtGuild[i];
				packet.u.kein.guild_instroduction_basic.guild_name[0] = 0;
				RecvChangeDeleteGuild( &packet );				
			}
		}
	}
	//////////////////////////////////////////////////////////////////////
	
	const int nCount = CheckGuildMemberForRegistGuild( guildCode );		// ±× ±æµå¿ø¿¡ ¼ÓÇØ ÀÖ´Â Ä³¸¯ÅÍ°¡ ¸î¸íÀÌ³Ä?
	
	if (nCount < MIN_GUILD_COUNT)
	{	//< CSD-030320 : Á¤½Ä ±æµå°¡ µÇ±â À§ÇÑ ÀÎ¿øÀ» 10¸íÀÌ»óÀ¸·Î º¯°æ
		// ±æµå¿ø ¼ö°¡ ºÎÁ·ÇÏ´Ù.
		SaveGuildLog( guildCode, 1, -1 );		// 021008 YGI
		return;
	}	//> CSD-030320
	
	int info_num;
	ret = SaveGuildRegist( pGuildRegist, info_num );
	if( ret != 1 ) 
	{
		SaveGuildLog( guildCode, 1, -2 );		// 021008 YGI
		return;
	}
	else
	{
		SaveGuildLog( guildCode, 1, 1 );		// 021008 YGI
	}
	
	t_packet packet;
	packet.h.header.type = CMD_GUILD_DEGREE_INFO;
	packet.u.kein.guild_degree_info.guild_code = guildCode;
	packet.u.kein.guild_degree_info.info_num = info_num;
	memcpy( packet.u.kein.guild_degree_info.guild_degree, pGuildRegist->guild_degree, sizeof( char)*5*20 );
	packet.h.header.size = sizeof( k_guild_degree_info );
	g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
	
	DirectClient( CMD_REFRESH_GUILD_CODE, server_id, cn, &guildCode, sizeof( short int ) );
}	//> CSD-030324

void RecvChangeGuildDegree( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	k_guild_change_degree *pGuildRegist;
	pGuildRegist = (k_guild_change_degree *)p->u.kein.send_db_direct_map.data;
	
	int guildCode = pGuildRegist->guild_code;
	int info_num;
	int ret = SaveChangeGuildDegree( pGuildRegist, info_num );
	if( ret != 1 ) return;
	
	t_packet packet;
	packet.h.header.type = CMD_GUILD_DEGREE_INFO2;
	packet.u.kein.guild_degree_info.guild_code = guildCode;
	packet.u.kein.guild_degree_info.info_num = info_num;
	memcpy( packet.u.kein.guild_degree_info.guild_degree, pGuildRegist->guild_degree, sizeof( char)*5*20 );
	packet.h.header.size = sizeof( k_guild_degree_info );
	g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
}

void RecvSaveGuildMemberList( t_packet *p )
{
	int guild_code = p->u.kein.save_guild_member_list.guild_code;
	int old_guild_code = p->u.kein.save_guild_member_list.old_guild_code;
	int degree = p->u.kein.save_guild_member_list.degree;
	char *name = p->u.kein.save_guild_member_list.name;
	
	ChangeGuildMemberList( name, guild_code, degree );
	if( !guild_code )
	{
		// È¤½Ã ºÎ ±æ¸¶ ÀÌ¸é guild_list µµ ¼öÁ¤½ÃÄÑÁØ´Ù.
		char master[20];
		char submaster[20];
		int ret = GetGuildMasterAndsubMaster( old_guild_code, master, submaster);
		if( ret == 1 )
		{
			if( strcmp( name, submaster ) == 0 )
			{
				char querry[1024];
				sprintf( querry, "UPDATE guild_list SET sub_master = NULL WHERE code = %d", old_guild_code );
				Querry_SQL( querry );
			}
		}
	}	
}

void RecvUpdateGuildMailId( t_packet *p )
{
	DWORD mail_id = p->u.kein.guild_mail_id.guild_mail_id;
	char *name = p->u.kein.guild_mail_id.name;
	
	UpdateGuildMailId( name, mail_id );
}

void RecvGuildMasterAndSubMaster( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	k_req_guild_master_and_sub_master *guild_info;
	guild_info = (k_req_guild_master_and_sub_master *)p->u.kein.send_db_direct_map.data;
	
	int guild_code = guild_info->guild_code;
	int type = guild_info->type;
	
	if	(guild_code < 0) 
	{	//< CSD-030324
		return;
	}	//> CSD-030324
	
	k_req_guild_master_and_sub_master data ={0,};
	data.type = type;
	data.guild_code = guild_code;
	
	int ret = GetGuildMasterAndsubMaster( guild_code, data.name1, data.name2 );
	if( ret != 1 ) return;
	
	switch( type )
	{
	case 2 : strcpy( data.name1, data.name2 );  // ¼­ºê ±æ¸¶¸¸
	case 1 : DirectClient(						// ±æ¸¶¸¸
				 CMD_GUILD_MASTER_AND_SUBMASTER, 
				 server_id, 
				 cn,
				 &data, 
				 sizeof( k_req_guild_master_and_sub_master )- 40 + strlen( data.name1 ) );
		break;
	case 3 : DirectClient(						// µÑ´Ù
				 CMD_GUILD_MASTER_AND_SUBMASTER, 
				 server_id, 
				 cn,
				 &data, 
				 sizeof( k_req_guild_master_and_sub_master ) - 20+ strlen( data.name2 ) );
		break;
	}
}

void RecvRegistGuildCheck( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	int nGuildCode = *((short int*)p->u.kein.send_db_direct_map.data);
	
	const int nCount = CheckGuildMemberForRegistGuild( nGuildCode );		// ±× ±æµå¿ø¿¡ ¼ÓÇØ ÀÖ´Â Ä³¸¯ÅÍ°¡ ¸î¸íÀÌ³Ä?
	
	if (nCount >= MIN_GUILD_COUNT)
	{	//< CSD-030320 : Á¤½Ä ±æµå°¡ µÇ±â À§ÇÑ ÀÎ¿øÀ» 10¸íÀÌ»óÀ¸·Î º¯°æ
		DirectClient( CMD_REGIST_GUILD_CHECK_OK, server_id, cn, NULL, 0 );
	}	//> CSD-030320
	else 
	{
		char ret = nCount/(-100);
		if( ret )
		{
			DirectClient( CMD_REGIST_GUILD_CHECK_FAIL, server_id, cn, &ret, sizeof( char ) );
		}
		else
		{
			char data[2];
			data[0] = 5;
			data[1] = nCount;
			DirectClient( CMD_REGIST_GUILD_CHECK_FAIL, server_id, cn, data, sizeof( char )*2 );
		}
	}
}

void RecvCheckSubMaster( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;

	k_check_sub_master *check_info = (k_check_sub_master *)p->u.kein.send_db_direct_map.data;
	k_char_data_basic2 data;
	char result = 0;
	
	char szName[40];
	ConvertQueryString(check_info->name, szName, 20);

	char conditon[128];
	sprintf( conditon, "guild_code = %d AND name = '%s'", check_info->guild_code, szName );
	int nRowCount =0;
	int ret = GetRowLineOfSQL( "guild_member_list", "*", &nRowCount, conditon );
	if( nRowCount <= 0 ) 
	{
		result = 1;			// °°Àº ±æµå¿ø »ç¶÷ÀÌ ¾Æ´Ï´Ù.
		goto fail_;
	}
	
	GetDataBasic2ByName( &data, szName );
	if( data.lv < 30 )
	{
		result = 2;			// ºÎ±æ¸¶ ·¹º§ÀÌ ³Ê¹« ³·´Ù.
		goto fail_;
	}
	DirectClient( CMD_CHECK_SUB_MASTER_OK, server_id, cn, check_info->name, strlen( check_info->name ) );
	return;
	
fail_ : 
	DirectClient( CMD_CHECK_SUB_MASTER_FAIL, server_id, cn, &result, sizeof( char ) );
	return;
}

// 021008 YGI
void RecvChangeDeleteGuild( t_packet *p )
{
	// ÆÐÅ¶ ±¸Á¶¸¦ ¼öÁ¤ÇÏ°Ô µÇ¸é ±æµå µî·ÏÇÏ´Â ºÎºÐµµ Ã¼Å©ÇØºÁ¾ß ÇÑ´Ù. 
	// Á¤½Ä ±æµå µî·ÏÇÏ´Â ºÎºÐ¿¡ ÀÓ½Ã ±æµå Áö¿ì´Â ºÎºÐÀÌ ÀÖ°í ¿©±â¼­ ÀÌ ÇÔ¼ö¸¦ È£ÃâÇÑ´Ù.!!!
	int guild_code = p->u.kein.guild_instroduction_basic.guild_code;
	char *name = p->u.kein.guild_instroduction_basic.guild_name;		// Áö¿î ³ð
	int ret = DeleteGuild( guild_code );
	if( ret == 1 )
	{
		// ±æµå ¸â¹ö Å×ÀÌºí¿¡¼­ Áö¿öÁØ´Ù.
		DeleteGuildMemberList( guild_code );
		
		// ¿¥Æ÷¸®¾Æ°¡ ÀÖ´Ù¸é Áö¿öÁØ´Ù.
		char querry[512];
		sprintf( querry, "UPDATE guild_house SET guild_code = 0 WHERE guild_code = %d", guild_code );
		Querry_SQL( querry );
		
		// 021128 YGI------------
		// ±æµå ¸ÞÀÏÀ» Áö¿öÁØ´Ù.
		sprintf(querry, "DELETE guild_mail WHERE guild_code = %d ", guild_code );
		Querry_SQL( querry );
		
		// ±æµå ¾ÆÀÌÅÛÀ» Áö¿î´Ù.
		sprintf(querry, "DELETE guild_item WHERE guild_code = %d ", guild_code );
		Querry_SQL( querry );
		//--------------------------
		
		t_packet packet;
		packet.h.header.type = CMD_DELETE_GUILD_OK;
		packet.u.kein.default_short_int = guild_code;
		packet.h.header.size = sizeof( short int );
		g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
		
		if( name[0] )	// Á¤½Ä ±æµå »èÁ¦
			SaveGuildLog2( guild_code, 1, name );	// ±æµå »èÁ¦½Ã ·Î±×·Î ³²±ä´Ù.		// 021008 YGI
		else			// ½Ã°£ÀÌ Áö³­ ÀÓ½Ã ±æµå »èÁ¦
			SaveGuildLog2( guild_code, 0, NULL);
	}	
}

void RecvChangeColor( t_packet *p )
{
	int type = p->u.kein.change_color_db.type;
	int r= p->u.kein.change_color_db.r;
	int g= p->u.kein.change_color_db.g;
	int b= p->u.kein.change_color_db.b;
	char *name = p->u.kein.change_color_db.name;
	
	char querry[512];
	char szName[20];
	ConvertQueryString(name, szName, 20); // Finito prevents sql injection

	if( type )
		sprintf( querry, "update chr_info set bodyr = %d, bodyg = %d, bodyb=%d where name = '%s'"
		, r, g, b, szName );
	else 
		sprintf( querry, "update chr_info set clothr = %d, clothg = %d, clothb=%d where name = '%s'"
		, r, g, b, szName );
	
	Querry_SQL( querry );
}

// 020826 YGI
void CheckSalvationName( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	char *name = (char *)p->u.kein.send_db_direct_map.data;
	
	int ret = CheckSalvationNameBasic2( name );	// ±âºÎ °¡´É ÇÏ´Â°¡?
	char result = 1;
	if( ret == 1 )
	{
		result = 0;		// ±âºÎ °¡´É
	}
	DirectClient( CMD_CHECK_SALVATION_NAME, server_id, cn, &result, sizeof( char ) );
}

// 020826 YGI
int CheckSalvationNameBasic( char *name )
{
	int nRowCount = 0;
	char condition[256];
	sprintf( condition, "name = '%s'", name );
	GetRowLineOfSQL( "salvation_name", "name", &nRowCount, condition );
	return nRowCount?1:0;
}


extern int SetEventItemEmpty( CHARLIST *ch,  const int iIndex, ItemAttr &GiveItem );

int PutEventItem( const int turn, t_connection *c )
{	//< CSD-040120
	CHARLIST *ch = &c->chrlst;

	if (ch == NULL)
	{
		MyLog(0,"PutEventItem Error : ch is NULL turn: %d - by soto",turn);//soto-cn031205
		return 0;
	}

	if (!LocalMgr.IsAbleNation(TAIWAN|CHINA|HONGKONG))
	{
		return 0;
	}
	
	const int MAX_EVENT_USER_FILED = 10;
	int iIndex[MAX_EVENT_USER_FILED] ={0,};	
	::GetEventItemNumber( iIndex, c->id );
	
	k_item_log log_data;
	log_data.lv = 1;
	log_data.type = -1;
	log_data.port = g_pServerTable->GetOwnServerData()->wPort;
	strcpy( log_data.name1, "DB_DEMON" );
	strcpy( log_data.name2, ch->Name );
	
	for(int ct = 0 ; MAX_EVENT_USER_FILED > ct; ct++)
	{
		if( iIndex[ct] )
		{
			ItemAttr give_item = {0,};
			int reset = SetEventItemEmpty( ch, iIndex[ct], give_item );
			//<soto-cn031205
			if( turn == 2 && reset )//turn ÀÌ 2¸é Áö¿ì¶ó´Â ÀÌ¾ß±â
			{
				//event%n ÀÌ´Ï±î +1À» ÇØÁØ´Ù
				if(DeleteEventItemNumber( c->id, ct+1 ))
				{
					log_data.item = give_item;
					SaveItemLog( &log_data );
				}
				else
				{
					MyLog(0,"DeleteEventItemNumber Faild. - by soto");
				}
				
			}
			else
			{
				if(!reset)
				{
					MyLog(0,"SetEventItemEmpt() Faild!! - by soto");
				}
			}
			//>soto-cn031205
		}
	}

	return 1;
}	//> CSD-040120

//<! BBD 040308	¸ÊÀ¸·ÎºÎÅÍ ÀÌº¥Æ®¾ÆÀÌÅÛ Áö±Þ¿äÃ»À» ¹Þ¾ÒÀ»¶§ ÄÝµÇ´Â ÇÔ¼ö±º
extern ItemAttr MakeEventItem(int nIndex);
// ÇØ´çÀ¯Àú¾ÆµÚÀÇ Event0 - 10ÇÊµå¸¦ È®ÀÎÇØ ¾ÆÀÌÅÛÀ» »ý¼ºÇØÁØ´Ù
// But ½ÇÁ¦·Î Áö±ÞÇØÁÖ´Â°ÍÀº ¸Ê¼­¹öÀÌ´Ù
int PutEventItemByMapReq(const int iCn,t_packet &p)
{

	if (!LocalMgr.IsAbleNation(TAIWAN|CHINA|HONGKONG)) // Å¸±¹°¡¿¡¼­ »ç¿ëÀ» ¿øÇÏ¸é ÇÊÈ÷ ¼öÁ¤ÇÒ°÷
	{
		return 0;
	}
	const int MAX_EVENT_USER_FILED = 10;
	int iIndex[MAX_EVENT_USER_FILED];	
	memset(iIndex, 0L, sizeof(iIndex));
	::GetEventItemNumber( iIndex, p.u.Event_Item_List.szLoginID );

	memset(p.u.Event_Item_List.item, 0L, sizeof(ItemAttr) * 10);

	ItemAttr item;

	k_item_log log_data;
	log_data.lv = 1;
	log_data.type = -1;
	log_data.port = g_pServerTable->GetOwnServerData()->wPort;
	strcpy( log_data.name1, "DB_DEMON" );
	strcpy( log_data.name2, p.u.Event_Item_List.szChrName );
	
	// ¾ÈÀü Á¦ÀÏ ÀÓ½Ãº¯¼ö¿¡ ¹Þ¾Æ¼­ ¾²ÀÚ
	for(int ct = 0 ; MAX_EVENT_USER_FILED > ct; ct++)
	{
		memset(&item, 0L, sizeof(item));
		item = MakeEventItem(iIndex[ct]);		// ¸¸µç ¾ÆÀÌÅÛÀ» ¹Ù·Î ¶§·Á ³ÖÀÚ
	
		if(!item.item_no)	// Çä! ¾ÆÀÌÅÛ ³Ñ¹ö°¡ ¾ø´Ù
		{
			continue;
		}

		p.u.Event_Item_List.item[ct] = item;
		
		// ¹Þ¾ÒÀ¸´Ï Áö¿öÁÖ°í ·Î±× ³²±âÀÚ
		if(DeleteEventItemNumber( p.u.Event_Item_List.szLoginID, ct+1 ))
		{
			log_data.item = item;
			SaveItemLog( &log_data );

		}

	}
	

	// °Á ¿Â ÆÐÅ¶ ±×´ë·Î º¸³»ÁÖÀÚ
	p.h.header.type = CMD_EVENTRAREITEM_RES;
	p.h.header.size = sizeof(t_EVENT_RARE_ITEM_LIST);
	memcpy(p.u.Event_Item_List.nIndex, iIndex, sizeof(iIndex));
	::QueuePacket(connections,iCn,&p,1);

	return 1;
}
//> BBD 040308	¸ÊÀ¸·ÎºÎÅÍ ÀÌº¥Æ®¾ÆÀÌÅÛ Áö±Þ¿äÃ»À» ¹Þ¾ÒÀ»¶§ ÄÝµÇ´Â ÇÔ¼ö±º

int GetServerSetNum()
{
	return g_pServerTable->GetServerSetNum();
}

void RecvGetNameOfGuildMemberList( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	k_get_guild_member_list_req *req_data = (k_get_guild_member_list_req *)p->u.kein.send_db_direct_map.data;
	
	k_get_guild_memeber_list data;
	data.degree = req_data->degree;
	int ret = GetCharOfGuildMemberList( req_data->guild_code, &data );
	if( ret >= 0 )
	{
		for( int i=0; i<data.count; i++ )
		{
			data.name[i].is_connect = IsConnectName( data.name[i].name );
		}
		DirectClient( CMD_GET_NAME_GUILD_MEMBER_LIST,server_id, cn, &data, 2+sizeof(k_get_guild_memeber_list_name)*data.count );
	}
}

void RecvGetGuildNotice( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	int guild_code = *(( short int *)p->u.kein.send_db_direct_map.data);
	
	char text[1024] = {0, };
	int ret = GetGuildNotice( guild_code, text );
	if( ret == 1 ) 
		DirectClient( CMD_GET_GUILD_NOTICE, server_id, cn, &text, strlen(text)+1 );
	
}

void RecvRegistGuildNotice( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;

	k_guild_notice *data = ( k_guild_notice *)p->u.kein.send_db_direct_map.data;
	
	char szQuerry[2048];
	char szNotice[2048];

	ConvertQueryString(data->msg, szNotice, 1024);
	sprintf( szQuerry, "UPDATE guild_list SET notice = '%s' WHERE code = %d", szNotice, data->guild_code );
	Querry_SQL( szQuerry );
}

void RecvRegistFriend( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	k_regist_friend *data = (k_regist_friend *)p->u.kein.send_db_direct_map.data;
	
	char result = 0;
	DWORD name_status;
	int ret = GetNationByName( data->name2, &name_status );		// 1018 YGI
	if( !ret ) // ±×·± »ç¶÷ ¾ø´Ù.
	{
		result = 0;
		DirectClient( CMD_REGIST_FRIEND, server_id, cn, &result, 1 );
		return;
	}
	
	CCharRank target;
	memcpy( &target, &name_status, sizeof( DWORD ) );
	
	/*if( target.nation == data->nation )
	{*/
		ret = RegistFriend_SQL( data->name1, data->name2 );
		if( ret == 100 )		// ´õÀÌ»ó µî·Ï ÇÒ ¼ö ¾ø´Ù.
		{
			result = 1;
			DirectClient( CMD_REGIST_FRIEND, server_id, cn, &result, 1 );
			return;
		}
		else if( ret == 1 )
		{
			// µî·Ï ¼º°ø.. ±× »ç¶÷ÀÌ ÇöÀç ¿¬°á »óÅÂÀÎÁö È®ÀÎÇÑ´Ù.
			RecvCheckFriend( server_id, cn, data->name2 );
		}
		else if( ret == 200 )
		{
			result = 3;
			DirectClient( CMD_REGIST_FRIEND, server_id, cn, &result, 1 );
		}
	/*}
	else
	{
		// ³ª¶ó°¡ ´Ù¸£´Ù.
		result = 2;
		DirectClient( CMD_REGIST_FRIEND, server_id, cn, &result, 1 );
		return;
	}*/
}

int RecvGetFriend( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	char *name= p->u.kein.send_db_direct_map.data;
	
	k_get_friend data = {0, };
	
	int ret = GetFriend_SQL( name, data.name );
	if( ret == 1 )
	{
		//DirectClient( CMD_GET_FRIEND, server_id, cn, &data, sizeof( k_get_friend ) );
		for( int i=0; i<30; i++ )
		{
			if( data.name[i][0] )
			{
				RecvCheckFriend( server_id, cn, data.name[i] );
			}
		}
	}
	return 1;
}

void RecvLogout( t_packet *p )
{
	char *name = p->u.data;
	char szQuerry[256];
	char szName[20];
	ConvertQueryString(name, szName, 20); // Finito prevents sql injection
	sprintf( szQuerry, "DELETE login_name WHERE name = '%s'", szName );
	Querry_SQL( szQuerry );

	char gmnames[5][20] = {"GMThralas", "GMFinito", "GMSpherix", "GMGohalien", "DonationGirl"};

	for (int i = 0; i < 5; ++i)
	{
		if (strcmp(gmnames[i], szName) == 0)
		{
			return;
		}
	}

	// finito 09/08/07 friend status to all maps
	t_packet friendpacket;
	memset(friendpacket.u.FriendStatus.name1, 0, sizeof(friendpacket.u.FriendStatus.name1));
	memset(friendpacket.u.FriendStatus.name2, 0, sizeof(friendpacket.u.FriendStatus.name2));	
	ConvertQueryString(szName, friendpacket.u.FriendStatus.name2, 20); // Finito prevents sql injection
	friendpacket.h.header.type = CMD_FRIEND_STATUS;
	friendpacket.h.header.size = sizeof(t_FriendStatus);
	friendpacket.u.FriendStatus.online = false;

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
}

bool IsConnectName( char *name )		// Ä³¸¯¸íÀ¸·Î Á¢¼ÓÇØ ÀÖ´ÂÁö ¾Ë¾Æ º¸´Â ÇÔ¼ö
{
	char querry[256];
	int nRowCount = 0;
	char szName[20];
	ConvertQueryString(name, szName, 20); // Finito prevents sql injection
	sprintf( querry, "name = '%s'", szName );
	GetRowLineOfSQL( "login_name", "name", &nRowCount, querry );
	return (nRowCount == 0) ? false:true;
}

void RecvCheckFriend( int server_id, int cn, char *name )
{
	k_add_friend add_friend;
	add_friend.login = (char)IsConnectName( name );
	strcpy( add_friend.name, name );
	DirectClient( CMD_ADD_FRIEND, server_id, cn, &add_friend, strlen(name)+2 );
}

void DeleteFriend( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	k_delete_friend *names= (k_delete_friend *)p->u.kein.send_db_direct_map.data;
	
	k_get_friend data = {0, };

	char szName1[20];
	char szName2[20];

	ConvertQueryString(names->name1, szName1, 20); // Finito prevents sql injection
	ConvertQueryString(names->name2, szName2, 20); // Finito prevents sql injection	

	int ret = GetFriend_SQL( szName1, data.name );
	if( ret == 1 )
	{
		for( int i=0; i<30; i++ )
		{
			if( data.name[i][0] )
			{
				if( strcmp( data.name[i], szName2 ) == 0 )
				{
					char szQuerry[256];
					sprintf( szQuerry, "UPDATE friend_list SET friend%d = NULL WHERE name = '%s'", i+1, szName1 );
					Querry_SQL( szQuerry );
					return;
				}
			}
		}
		DirectClient( CMD_DELETE_FRIEND, server_id, cn, NULL, 0 );
	}
}


void RecvCheckGuildName( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	char *name= p->u.kein.send_db_direct_map.data;
	
	int nRowCount = 0;
	char conditon[256];
	char szName[20];
	ConvertQueryString(name, szName, 20); // Finito prevents sql injection
	sprintf( conditon, "name = '%s'", szName);
	int ret = GetRowLineOfSQL( "guild_list", "name", &nRowCount, conditon );
	if( nRowCount > 0 )
	{
		// Á¸ÀçÇÑ´Ù.
		DirectClient( CMD_THEREIS_CHARANAME, server_id, cn, NULL, 0 );
	}
	else
	{
		//  Á¸ÀçÇÏÁö ¾Ê´Â´Ù.
		DirectClient( CMD_THEREIS_NO_CHARANAME, server_id, cn, NULL, 0 );		
	}
}

void RecvCheckGuildOthercharacter( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	char *name= p->u.kein.send_db_direct_map.data;
	
	if( !isPosableGuildJoinByName( 0, name ) )
	{
		DirectClient( CMD_THEREIS_CHARANAME, server_id, cn, NULL, 0 );
	}
	else
	{
		DirectClient( CMD_THEREIS_NO_CHARANAME, server_id, cn, NULL, 0 );		
	}
}

void RecvAddEventItem( t_packet *p, short int cn )
{
	char *name = p->u.kein.save_event_item.name;
	int item_no = p->u.kein.save_event_item.item_no;
	int count = p->u.kein.save_event_item.count;
	
	char szName[20];
	ConvertQueryString(name, szName, 20); // Finito prevents sql injection

	SaveEventItem( szName, item_no, count );
}

// ÃÊ±â ÇØ´ç ±æµå ¾ÆÀÌÅÛÀÇ ÀÎµ¦°ª¸¸ º¸³»ÁØ´Ù.
void RecvGetGuildItemFirst( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	short int *pGuildCode = ( short int *)p->u.kein.send_db_direct_map.data;
	
	k_get_guild_item_first data;
	int max = 0;
	
	int ret = GetGuildItemIndexAndCount( *pGuildCode, max, data.item_index );
	if( ret == 1 )
	{
		data.max = max;
		DirectClient( CMD_GET_GUILD_ITEM_FIRST, server_id, cn, &data, 
			sizeof( k_get_guild_item_first )-sizeof( int )*200+sizeof( int )*max );		
	}
}

void RecvGetGuildItemCount( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	short int *pGuildCode = ( short int *)p->u.kein.send_db_direct_map.data;
	
	char condition[256];
	int RowCount = 0;
	sprintf( condition, "guild_code = %d", *pGuildCode );
	GetRowLineOfSQL( "guild_item", "cn", &RowCount, condition );
	if( RowCount >= 0 )
	{
		if( RowCount>150 ) RowCount = 150;
		BYTE data = (BYTE)RowCount;
		DirectClient( CMD_GET_GUILD_ITEM_COUNT, server_id, cn, &data, sizeof( BYTE ));
	}
}

// Æ¯Á¤ ÀÎÅØ½º °ª¿¡¼­ ÇØ´ç ±æµå ¾ÆÀÌÅÛÀÇ ´ÙÀ½ 10°³ÀÇ ¾ÆÀÌÅÛÀ» º¸³»ÁØ´Ù.
void RecvGetGuildItem( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	k_req_guild_item *pGuildItem= ( k_req_guild_item * )p->u.kein.send_db_direct_map.data;
	
	int count;
	k_get_guild_item data;
	int ret = GetGuildItem( pGuildItem->guild_code, pGuildItem->index, data.item, count, data.index );
	if( ret == 1 ) 
	{
		if( count )
		{
			data.count = count;
			DirectClient( CMD_GET_GUILD_ITEM, server_id, cn, &data, sizeof( k_get_guild_item ) );
		}
	}
}

// ¾ÆÀÌÅÛ ÀúÀå
void RecvPutGuildItem( t_packet *p )
{
	ItemAttr *pItem = &p->u.kein.put_guild_item.item;
	char *name = p->u.kein.put_guild_item.name;
	int guild_code = p->u.kein.put_guild_item.guild_code;
	if( !pItem->item_no ) return;
	if( !guild_code ) return;
	
	char szName[20];
	ConvertQueryString(name, szName, 20); // Finito prevents sql injection

	InsertGuildItem( guild_code, pItem, name );
}

void RecvGetGuildItemMap( t_packet *p, short int cn )
{
	int guild_code = p->u.kein.get_guild_item_map.guild_code;
	DWORD index =  p->u.kein.get_guild_item_map.index;
	int server_id = p->u.kein.get_guild_item_map.server_id;
	int ret;
	t_packet packet;
	
	if( !guild_code ) return;
	DWORD box_money = 0;
	GetGuildItemPay( guild_code, box_money );
	if( box_money ) return;		// ¼¼±ÝÀÌ ³²¾Æ ÀÖ¾î¼­ »ç¿ëÇÏÁö ¸øÇÑ´Ù.
	
	ItemAttr item;
	ret = GetGuildItemOne( guild_code, index, &item );
	if( ret == 1 )
	{	
		packet.h.header.type = CMD_GET_GUILD_ITEM_MAP;
		packet.u.kein.get_guild_item_db.server_id = server_id;
		packet.u.kein.get_guild_item_db.item = item;
		packet.h.header.size = sizeof( k_get_guild_item_db);
		QueuePacket( connections, cn, &packet, 1 );
		return ;
	}
	
	SendPutMenuString( cn, KM_FAIL, 133, server_id );
}

void SendPutMenuString( short int game_server_id, int type, int str_num, int user_id ) 
{
	k_put_menu_string put_menu_string;
	
	put_menu_string.type = type;
	put_menu_string.str_num = str_num;
	
	DirectClient( CMD_PUT_MENU_STRING, user_id, game_server_id, &put_menu_string, sizeof( k_put_menu_string ) );
}

DWORD CheckGuildItemPay( short int guild_code )
{
	DWORD box_money = 0;
	GetGuildItemPay( guild_code, box_money );
	if( box_money == 0 ) return 1;
	int ret = DeleteGuildBoxMoney( box_money, guild_code );
	if( ret )
	{
		char szQuerry[1024];
		sprintf( szQuerry, "UPDATE guild_list SET box_money = %u WHERE code = %d ",box_money, guild_code );
		Querry_SQL( szQuerry );
	}
	return box_money;
}

int DeleteGuildBoxMoney( DWORD &box_money, short int guild_code )
{
	int item_no = GetMoneyItemNumber();
	ItemAttr item;
	char name[20];
	int ret = GetGuildItemOne( guild_code, item_no, &item, name );
	if( ret == 1 )
	{
		if( box_money >= item.attr[IATTR_MUCH] )
		{
			box_money -= item.attr[IATTR_MUCH];
			DeleteGuildBoxMoney( box_money, guild_code );
			return 1;
		}
		else
		{
			item.attr[IATTR_MUCH] -= box_money;
			box_money = 0;
			// ³²Àº ¾ÆÀÌÅÛÀ» ÀúÀåÇÑ´Ù.
			InsertGuildItem( guild_code, &item, name );
			return 1;
		}
	}
	return 0;
}

void RecvGetGuildBoxMoney( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	short int *pGuildCode = ( short int *)p->u.kein.send_db_direct_map.data;
	
	DWORD box_money = 0;
	int ret = GetGuildItemPay( *pGuildCode, box_money );
	if( ret == 1 )
	{
		DirectClient( CMD_GET_GUILD_BOX_MONEY, server_id, cn, &box_money, sizeof( DWORD ) );
	}
}

void RecvCheckGuildBoxMoney( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	short int *pGuildCode = ( short int *)p->u.kein.send_db_direct_map.data;
	
	DWORD box_money = CheckGuildItemPay( *pGuildCode );
	
	DirectClient( CMD_GET_GUILD_BOX_MONEY, server_id, cn, &box_money, sizeof( DWORD ) );	
}

void RecvUpdateGuildBoxMoney()
{	//< CSD-030324
	int RowCount = 0;
	char condition[255];
	
	int last_code;
	if( GetLastGuildCode(last_code) != 1 ) return;
	int active, ret;
	for( int i=0; i<last_code; i++ )
	{
		active = 0;
		RowCount =0;
		GetActiveByGuildList( i, active );
		if( active )
		{
			sprintf( condition, "guild_code = %d", i );
			ret = GetRowLineOfSQL( "guild_item", "cn", &RowCount, condition );
			if( RowCount > 0 )
			{
				if( RowCount > 150 ) RowCount = 150;
				sprintf( condition, "Update guild_list set box_money = box_money+%d where code = %d", 
					RowCount*1000, i );		// º¸°ü·á = ÃÑº¸°ü ¾ÆÀÌÅÛ * 150;
				Querry_SQL( condition );
				CheckGuildItemPay( i );		// º¸°ü·á Á¤»ê
			}
		}
	}
}	//> CSD-030324

int GetMoneyItemNumber()
{
	return (LocalMgr.IsChangeMoney())?10123:10030;//021007 lsw
}

void RecvChangeGuildMaster( t_packet *p, short int cn )
{
	// ¸ÊÀ» ÅëÇØ¼­ ¿Â´Ù.
	short int guild_code = p->u.kein.default_short_int;
	if (guild_code <= 0) return;
	
	char master[20];
	char submaster[20];
	int ret = GetGuildMasterAndsubMaster( guild_code, master, submaster);
	if( ret != 1 ) return;
	if( !master[0] || !submaster[0] ) return;		// ¼­ºê ±æ¸¶°¡ ¾ø´Ù.
	
	// ±æµå ¸¶½ºÅÍÀÇ guild_degree °ªÀ» ¹Ù²Û´Ù.
	DWORD data;
	CCharRank name_status1;	// master ÀÇ
	CCharRank name_status2; // subMaster ÀÇ
	
	ret = GetNationByName( master, &data );
	if( !ret ) return;
	memcpy( &name_status1, &data, sizeof( DWORD ) );
	
	ret = GetNationByName( submaster, &data );
	if( !ret ) return;
	memcpy( &name_status2, &data, sizeof( DWORD ) );
	
	name_status1.guild_master= 0;
	name_status2.guild_master= 1;
	
	memcpy( &data, &name_status1, sizeof( DWORD ) );
	SetNationByName( data, master );
	
	memcpy( &data, &name_status2, sizeof( DWORD ) );
	SetNationByName( data, submaster );
	
	// guild_member_list ¸¦ ±³Ã¼ÇÑ´Ù.
	ChangeGuildMemberList( master, guild_code, name_status1.guild_master );
	ChangeGuildMemberList( submaster, guild_code, name_status2.guild_master );
	
	// guild_list ¸¦ ¼öÁ¤ÇÑ´Ù.
	char querry[1024];
	char szMaster[40];
	ConvertQueryString(submaster, szMaster, 20);

	sprintf( querry, "UPDATE guild_list SET master = '%s', sub_master = NULL WHERE code = %d", 
		submaster, guild_code );
	Querry_SQL( querry );
	
	// ÀüÃ¼ ¸Ê¼­¹ö¿¡ sub master ÀÇ ÀÌ¸§À» º¸³»ÁØ´Ù.
	
	t_packet packet;
	packet.h.header.type = CMD_CHANGE_GUILD_MASTER_ALL_MAP;
	packet.h.header.size = strlen( submaster )+1;
	strcpy( packet.u.kein.default_name, submaster );
	g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
}


void RecvChangeGuildMasterBySubMaster( t_packet *p, short int cn )
{
	// Å¬¶óÀÌ¾ðÆ®¿¡¼­ Á÷Á¢¿Â´Ù.
	int server_id = p->u.kein.send_db_direct_map.server_id;
	k_guild_notice *info= (k_guild_notice *)p->u.kein.send_db_direct_map.data;
	char *sub_master = info->msg;
	short int guild_code = info->guild_code;
	if( !guild_code ) return;
	
	char master[20];
	char submaster[20];
	int ret = GetGuildMasterAndsubMaster( guild_code, master, submaster);
	if( ret != 1 ) return;
	if( !master[0] || !submaster[0] ) return;		// ¼­ºê ±æ¸¶°¡ ¾ø´Ù.
	if( strcmp( sub_master, submaster ) != 0 ) return;	// ºÎ±æ¸¶ Á¤º¸°¡ Æ²¸®´Ù.
	
	// ³¯ÀÚ¸¦ Ã¼Å©ÇÑ´Ù. ¾ÈµÇ¸é ¸Þ½ÃÁö¸¦ º¸³»ÁØ´Ù.
	ret = CheckGuildMasterLastConnect( guild_code );		// null ÀÏ°æ¿ì 10ÀÏ ÀüÀ¸·Î ¼¼ÆÃÇÑ´Ù.
	if( ret != 1 )		// ±³Ã¼°¡ ºÒ°¡´ÉÇÏ´Ù.
	{
		switch( ret )
		{
		case 2:		// 5ÀÏ ÈÄ¿¡ ´Ù½Ã ½ÃµµÇÏ¼¼¿ä
			SendPutMenuString( cn, KM_FAIL, 140, server_id );
			break;
		case 3:		// ±æµå ¸¶½ºÅÍ°¡ 15ÀÏ ÀÌÀüÀ¸·Î Á¢¼ÓÇÑÀûÀÌ ÀÖ½À´Ï´Ù.
			SendPutMenuString( cn, KM_FAIL, 141, server_id );
			break;
		}
		return;
	}
	
	// º¯°æ ½ÃÀÛ
	// ±æµå ¸¶½ºÅÍÀÇ guild_degree °ªÀ» ¹Ù²Û´Ù.
	DWORD data;
	CCharRank name_status1;	// master ÀÇ
	CCharRank name_status2; // subMaster ÀÇ
	
	ret = GetNationByName( master, &data );
	if( !ret ) return;
	memcpy( &name_status1, &data, sizeof( DWORD ) );
	
	ret = GetNationByName( submaster, &data );
	if( !ret ) return;
	memcpy( &name_status2, &data, sizeof( DWORD ) );
	
	name_status1.guild_master= 0;
	name_status2.guild_master= 1;
	
	memcpy( &data, &name_status1, sizeof( DWORD ) );
	SetNationByName( data, master );
	
	memcpy( &data, &name_status2, sizeof( DWORD ) );
	SetNationByName( data, submaster );
	
	// guild_member_list ¸¦ ±³Ã¼ÇÑ´Ù.
	ChangeGuildMemberList( master, guild_code, name_status1.guild_master );
	ChangeGuildMemberList( submaster, guild_code, name_status2.guild_master );
	
	// guild_list ¸¦ ¼öÁ¤ÇÑ´Ù.
	char querry[1024];
	char szMaster[40];
	ConvertQueryString(submaster, szMaster, 20);

	sprintf( querry, "UPDATE guild_list SET master = '%s', sub_master = NULL WHERE code = %d", 
		szMaster, guild_code );
	Querry_SQL( querry );
	
	// ÀüÃ¼ ¸Ê¼­¹ö¿¡ sub master ÀÇ ÀÌ¸§À» º¸³»ÁØ´Ù.
	
	t_packet packet;
	packet.h.header.type = CMD_CHANGE_GUILD_MASTER_ALL_MAP;
	packet.h.header.size = strlen( submaster )+1;
	strcpy( packet.u.kein.default_name, submaster );
	g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
	
}

void RecvRegistSubMaster( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;

	k_guild_notice *info= (k_guild_notice *)p->u.kein.send_db_direct_map.data;
	char *submaster = info->msg;
	short int guild_code = info->guild_code;
	if( !guild_code ) return;
	
	char querry[1024];
	char szSubMaster[40];
	ConvertQueryString(submaster, szSubMaster, 20);

	sprintf( querry, "UPDATE guild_list SET sub_master = '%s' WHERE code = %d", szSubMaster, guild_code );
	Querry_SQL( querry );
}

void RecvGuildHouseInfo( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	int nation = *p->u.kein.send_db_direct_map.data;
	
	int count = 0;
	k_guild_house_info	guild_house_info;
	
	int ret = GetGuildHouseInfo( &guild_house_info, count, nation );
	if( ret == 1 )
	{
		// ÇØ´ç Á¤º¸¸¦ º¸³»ÁØ´Ù.
		int size = sizeof( k_guild_house_info_unit )*count+sizeof( char );
		if( !size ) return;
		
		guild_house_info.count = count;
		
		DirectClient( CMD_GUILD_HOUSE_INFO, server_id, cn, &guild_house_info, size );
	}
}

DWORD SendDb2AllMap( int type, void *msg, int size )
{
	t_packet packet;
	packet.h.header.type = type;
	if( msg )
	{
		memcpy( packet.u.data, msg, size );
	}
	else size = 0;
	packet.h.header.size = size;
	return g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
}

bool IsExitRecordOfDB( char *table, char *condition )		// Æ¯Á¤ Å×ÀÌºí¿¡ ·¹ÄÚµå°¡ Á¸Àç ÇÏ´Â°¡?
{
	int nRowCount =0;
	
	GetRowLineOfSQL( table, "*", &nRowCount, condition );
	return ( nRowCount > 0 )?true:false;
}

void RecvChangeGuildHouseInfo( t_packet *p, short int cn )
{
	k_change_guild_house_info *pData = (k_change_guild_house_info *)p->u.kein.data;
	
	char szQuerry [512];
	if( pData->day_type == 1 )		// ½Å±Ô
	{
		sprintf( szQuerry , "guild_code = %d", pData->guild_code );
		if( IsExitRecordOfDB( "guild_house", szQuerry ) )
		{
			// °¡Áö°í ÀÖ´Â ±æµå°¡ ÀÕ´Ù.
			SendDb2AllMap( CMD_RELOAD_GUILD_HOUSE );
			return;			
		}
		sprintf(szQuerry, "UPDATE guild_house SET date = getdate()+30, guild_code = %d WHERE id = %d", 
			pData->guild_code, pData->id  );
	}
	else if( pData->day_type == 2 )		// ¿¬Àå
	{
		sprintf( szQuerry , "guild_code = %d AND id = %d ", pData->guild_code, pData->id );
		if( !IsExitRecordOfDB( "guild_house", szQuerry ) )
		{
			// ¿¬ÀåÀ» ÇÒ ¼ö ¾ø´Ù.
			SendDb2AllMap( CMD_RELOAD_GUILD_HOUSE );
			return;
		}
		sprintf(szQuerry, "UPDATE guild_house SET date = date+30 WHERE id = %d", pData->id );
	}
	else return;
	
	Querry_SQL( szQuerry );
	
	t_packet packet;
	k_change_guild_house_info_db2map *guild_house_info = &packet.u.kein.change_guild_house_info_db2map;
	int ret = GetGuildHouseInfoById( guild_house_info, pData->id );
	if( ret == 1)
	{
		// ¸ðµç ¸Ê¿¡ º¸³»ÁÖÀÚ		
		packet.h.header.type = CMD_CHANGE_GUILDHOUSE_INFO;
		guild_house_info->house_id = pData->id;
		packet.h.header.size = sizeof( k_change_guild_house_info_db2map );
		
		g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
	}
}


void RecvCheckGuildHouse()
{
	static int old_day = g_day;
	//if( old_day == g_day )  return;
	
	old_day = g_day;
	
	t_packet packet;
	
	int count;
	char *pHouseId = packet.u.kein.check_guild_house.pHouseId;
	int ret = GetCheckGuildHouse( pHouseId, count );
	if( ret == 1 )
	{
		if( count )
		{
			packet.h.header.type = CMD_CHECK_GUILD_HOUSE;
			packet.u.kein.check_guild_house.count = count;
			packet.h.header.size = sizeof( k_check_guild_house)*count + sizeof( char );		
			g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
		}
		// ½ÇÁ¦·Î Áö¿öÁØ´Ù.
		char querry[512];
		sprintf( querry, "UPDATE guild_house SET guild_code = 0 WHERE getdate() > date" );
		Querry_SQL( querry );
	}
}

// 020826 YGI
void RecvDeleteSalvation()
{
	int ret = Querry_SQL( "DELETE salvation_name WHERE date < getdate()-1" );
	MyLog( 0, "Delete Salvation_name Qurry, result %d", ret );
}

// 021008 YGI ---------------------------------------
void SaveGuildLog( int guild_code, int type1, int type2, char *master, char *guild_name )	// type1 0:imsi_guild, 1:regular guild, type2 <0:falel, >0:success
{
	FILE *fp;
	fp = fopen( "./logout/guild_log.txt", "at+" );
	if( !fp ) 
	{
		mkdir( "logout" );
		fp = fopen( "./logout/guild_log.txt", "at+" );
		if( !fp ) return;
	}
	
	char type1_str[2][50] = { "TEMP", "REGULAR" };
	char why[100];
	strcpy( why, " " );
	switch( type2 )
	{
	case -1 : 
		strcpy( why, "Current guild_member count less than 10" );
		break;
	case -2 :
		strcpy( why, "SQL-DB write error" );
		break;
	case 1 : 
		strcpy( why, "success" );
		break;
	case -100:
		guild_code = 0;		// ¾ÆÁ÷ ±æµå ÄÚµå¸¦ ÇÒ´ç¹Þ±â ÀüÀÌ´Ù.
		strcpy( why, "master already have guild" );
		break;
	case -200:
		guild_code = 0;
		strcpy( why, "don't make more guild ( guild count is 512 )" );
		break;
	case -300:
		strcpy( why, "already exist same guild name" );
		break;
	case -400:
		strcpy( why, "SQL-DB write error" );
		break;
	}
	
	fprintf( fp, "###################################################################################################\n" );
	fprintf( fp, "character name [%s] - guild_name [%s]\n", master?master:"UNKNOWN", guild_name?guild_name:"UNKNOWN" );
	fprintf( fp, "<%d-%02d-%02d %02d:%02d:%02d> : [REGIST %s] guild_type:%s, guild_code:%d (%s)\n", 
		g_year, g_mon+1, g_day, g_hour, g_min, g_sec, (type2<=0)?"fail":"success", type1_str[type1], guild_code, why );
	//fprintf( fp, "###################################################################################################\n" );		
	
	fclose( fp );
}

void SaveGuildLog2( int guild_code, int type, char *name )	// type - 0:½Ã°£ÀÌ Áö³ª¼­, 1:´©±º°¡ Áö¿ï¶§
{
	FILE *fp;
	fp = fopen( "./logout/guild_log.txt", "at+" );
	if( !fp ) 
	{
		mkdir( "logout" );
		fp = fopen( "./logout/guild_log.txt", "at+" );
		if( !fp ) return;
	}
	
	char why[1024];
	if( type == 1 )
	{
		// ´©±º°¡ Áö¿ü´Ù.
		sprintf( why, "Delete by '%s'", name );
	}
	else
	{
		// 20ÀÏÀÌ Áö³ª¼­ ÀÓ½Ã ±æµå´Â »ç¶óÁ³´Ù.
		strcpy( why, "Delete because over 20 day " );
	}
	
	fprintf( fp, "###################################################################################################\n" );
	fprintf( fp, "[GUILD DELETE]\n" );
	fprintf( fp, "<%d-%02d-%02d %02d:%02d:%02d> type:%s, guild_code:%d \n", 
		g_year, g_mon+1, g_day, g_hour, g_min, g_sec, why, guild_code );
	//fprintf( fp, "###################################################################################################\n" );		
	fclose( fp );
}
//---------------------------------------------


//021030 YGI
void RecvSaveAmountEventNpcItem( t_packet *p )
{
	int *data = (int *)p->u.data;
	int event_no = data[0];
	int amount = data[1];
	
	char query[512];
	sprintf( query, "UPDATE event_monsteritem SET amount = %d, reg_date = getdate() "
		" WHERE event_no = %d", amount, event_no );
	Querry_SQL( query );
}


extern void __stdcall ReceivedMsgServer(DWORD dwConnectionIndex,char* pMsg,DWORD dwLength);
void CheckCrash()
{
	int nSize;
	char *pData;
	FILE *fp = fopen( "DBCrash_info.bin", "rb");
	if( !fp ) return;
	fread( &nSize, 4, 1, fp );
	pData = new char[nSize];
	fread( pData, 1, nSize, fp );
	fclose( fp );
	
	ReceivedMsgServer( 1, pData, nSize );
}

void __stdcall GameTimeFunc(DWORD dwValue)
{
	prepare(connections);
	if( g_pServerTable->GetOwnPort() == 4002 )
	{
		CheckOutSideMail(); // 030221 YGI
	}
}

//021107 YGI
void RecvCheckEventScriptItem( t_packet *p, short int cn )
{
	k_event_script_item	*pData = (k_event_script_item	*)p->u.data;
	char condition[512];
	
	int RowCount = 0;
	sprintf( condition, "event_no=%d AND login_id = '%s'", pData->event_no, pData->id );
	int ret = GetRowLineOfSQL( "Event_NpcItem_Recv_Id", "*", &RowCount, condition );
	if( RowCount > 0 || ret != 1 ) // Å×ÀÌºíÀÌ ¾ø°Å³ª ÀÌ¹Ì ¹ÞÀº ÀûÀÌ ÀÖ´Ù¸é
	{
		pData->result = 0;		// ½ÇÆÐ
		QueuePacket( connections, cn, p, 1 );
		return;		// ÀÌ¹Ì ¹ÞÀºÀûÀÌ ÀÖ´Ù. 
	}
	
	// ¿À·¡µÈ µ¥ÀÌÅ¸´Â Áö¿ìÀÚ
	Querry_SQL( "DELETE event_npcitem_recv_id WHERE recv_date < getdate()-30" );
	
	
	pData->result = 1;		// ¼º°ø
	// ¸Ê¼­¹ö·Î °í´ë·Î ´Ù½Ã º¸³»°í ÀúÀåÇÏµµ·Ï ÇÏÀÚ.
	QueuePacket( connections, cn, p, 1 );
	
	sprintf( condition, "INSERT INTO event_npcitem_recv_id (event_no, recv_date, login_id, [character] ) "
		"VALUES ( %d, getdate(), '%s', '%s' ) ", pData->event_no, pData->id, pData->name );
	Querry_SQL( condition );
}

void RecvCheckEventMoveMap( t_packet *p, short int cn )
{
	int server_id = p->u.kein.send_db_direct_map.server_id;
	k_event_move_map_req *pData = (k_event_move_map_req *)p->u.kein.send_db_direct_map.data;
	
	if( pData->sex < 0 || pData->sex > 1 ) return;
	if( pData->class_num < 0 || pData->class_num > 4 ) return;
	if( pData->nation < 0 || pData->nation > 6 ) return;
	
	k_event_move_map_rep map_data;

	int isActive = GetEventMoveMapName( pData, &map_data );
	if( isActive )
	{
		DirectClient( CMD_CHECK_EVENT_MOVE_MAP, server_id, cn, &map_data, sizeof( k_event_move_map_rep ) );
	}
}

void RecvSaveEventMapMoveNow( t_packet *p, short int cn )
{
	k_save_event_move_map *pData = &p->u.kein.save_event_move_map;
	char query[512];
	sprintf( query, "EXEC up_update_event_mapmove_now %d, %d, %d", pData->event_no, pData->max, pData->now );
	Querry_SQL( query );
}
// ¿ÜºÎ¿¡¼­ º¸³½ ¸ÞÀÏÀÌ ÀÖ´ÂÁö È®ÀÎ
// 030221 YGI
extern int GetRecvMailName( int *iRowCount, char recv_name[40][20] );
void CheckOutSideMail()
{
	char recv_name[40][20] = {0,};
	int iRowCount = 0;
	
	if( !GetRecvMailName( &iRowCount, recv_name ) ) 
	{
		return;
	}
	
	t_packet packet;
	
	packet.h.header.type = CMD_CHECK_RECV_MAIL;
	packet.h.header.size = 1+20*iRowCount;
	packet.u.kein.check_recv_mail.count = iRowCount;
	
	for( int i=0; i<iRowCount; i++ )
	{
		strcpy( packet.u.kein.check_recv_mail.name[i], recv_name[i] );
	}
	
	g_pServerTable->BroadCastToEveryServer( (char *)&packet, (sizeof(t_header)+packet.h.header.size ), SERVER_TYPE_MAP );
}
// 040105 YGI
void RecvGetTreasureMapAttr( t_packet* p, short int cn )
{
	k_get_treasure_map_detail_to_db *pData = &p->u.kein.get_treasure_map_detail_to_db;

	int mapnumber, x, y;
	int ret = GetTreasureAttr( mapnumber, x, y );
	if( ret < 0 ) return;

	t_packet packet;
	packet.h.header.type = CMD_GET_TREASURE_MAP_DETAIL_DB;
		packet.u.kein.get_treasure_map_detail_to_map.pos = pData->pos;
		packet.u.kein.get_treasure_map_detail_to_map.cn = pData->cn;
		packet.u.kein.get_treasure_map_detail_to_map.map_number = mapnumber;
		packet.u.kein.get_treasure_map_detail_to_map.x = x;
		packet.u.kein.get_treasure_map_detail_to_map.y = y;
	packet.h.header.size = sizeof( k_get_treasure_map_detail_to_map );
	QueuePacket( connections, cn, &packet, 1 );
}

void RecvCheckCharGuild( t_packet *p, short int cn) //Eleval 12/06/09
{
	int guild_code = p->u.check_guilds.guildCode;
	char *id = p->u.check_guilds.id;
	int is_possible = isInAGuildById( id );	//Checking if the player is in a guild on another character

	t_packet packet;

	if( is_possible )		//If no, then let's tell the mapserver we can do the exile
		packet.h.header.type = CMD_EXILE_OK;
	else //If yes, let's tell the mapserver to tell the client the player is still in a guild with some of his characters
		packet.h.header.type = CMD_EXILE_NOT;
	
	packet.h.header.size = sizeof(t_check_guilds);
	packet.u.check_guilds.idPlayer = p->u.check_guilds.idPlayer;
	packet.u.check_guilds.guildCode = guild_code;
	QueuePacket( connections, cn, &packet, 1 );
}

void RecvSexChange( t_packet *p, short int cn) //Eleval 12/06/09 - Sex Change
{
	WORD id = p->u.sex_change.idUser;
	short int sex = p->u.sex_change.iSex;
	char *cId = p->u.sex_change.cId;
	if(!ChangeSexOfPlayer(sex, cId))
		MyLog(0, "Error when changing sex of '%s' !", cId);

	t_packet packet;
	packet.h.header.type = CMD_SEX_CHANGE_OK;
	packet.h.header.size = sizeof(t_sex_change);
	packet.u.sex_change.idUser = id;

	QueuePacket(connections, cn, &packet, 1);
}

//void RecvAskSQuestTeleport( t_packet *p, short int cn) //Eleval 10/08/09 - To bring ppl back in quest
//{
//	int nbMap;
//	char charname[32];
//	short int ClientNumber = p->u.ask_squest_tp.cn;
//	nbMap = p->u.ask_squest_tp.nbMap;
//	sprintf(charname, "%s", p->u.ask_squest_tp.charname);
//	if(ClientNumber != -5)
//	{
//		CheckIfBringableInSQuest(nbMap, charname, ClientNumber, cn);
//	}
//	else
//	{
//		int QuestFloor = p->u.ask_squest_tp.questfloor;
//		int nX = p->u.ask_squest_tp.nX;
//		int nY = p->u.ask_squest_tp.nY;
//
//		UpdateSQuestFloor(nbMap, charname, QuestFloor, nX, nY, cn);
//	}
//}