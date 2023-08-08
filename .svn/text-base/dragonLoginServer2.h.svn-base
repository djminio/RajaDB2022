
#ifndef __dragonloginserver2_h__
#define __dragonloginserver2_h__


/////////////////// var 변수를 이용하기 위한
#define VAR_RESET		47		// 캐릭터의 변수를 초기화 할대


///////////////////////////////////////////


extern void RecvGetBoxItem( DWORD box_id, short int server_id, short int gameserver_id, t_connection c[] );
extern void RecvPreachName( k_loginserver_preach_name *data,  short int gameserver_id, t_connection c[] );
extern void RecvPreachNameOk( int plus, k_loginserver_preach_name *data );		// 전도한 사람 신앙심 올려주거나 깍기
extern void SendNewCharResult( char *name, short int cn );
extern void SendGodTable( short int cn );
extern void RecvUpdateCharByKein( k_char_update_data *p );		// 캐릭터 신앙심등의 업데이트
extern void SendGetCharInfoByKein( k_req_chr_info_etc *p, short int cn );		// 게임서버로 신앙심등을 보내준다.
extern void SendEachGameServerForEarMessage( k_login_send_ear_message *p, short int game_server );
extern void RecvEarMessageOk( k_send_ear_message_ok_to_login *p );		// 어떤 게임서버에서 성공적으로 메시지를 보냈다는 회신
extern void RecvEarMessageResult( k_send_ear_message_result *p );
extern void RecvCheckName( char *name, short int server_id, short int cn );
extern void CheckMoveItem( k_moving_item *p );
extern void RecvChangeMapData1( t_packet *pPacket );
extern void RecvChangeLogintableByChangemap( char *user_id, char *map_name, short int server_id, short int cn );
extern void ReSendBoxItemEach( k_login_put_box_item *box );
extern void RecvDoubleBoxFind( DWORD box_id, short int server_id, short int gameserver_id );
extern void RecvFaithUp( char *name, short int point );
extern void SendOhMyParty( char *my_name, char *party_name );
extern void RecvStartGameMail( char *name, int guild_code, int server_id, int game_cn );
extern void SendPublicBbsEach( short int server_id, short int game_id );
extern void RecvHunterRegist( k_hunter_regist2 *p );
extern void RecvGetHunterList( int list_id, short int server_id, short int game_id);
extern void RecvKillHunter( int list_id, char *hunter_name, short int server_id, short int game_id );
extern void RecvResetJob( t_packet *p, short int cn );
extern void CheckSkillExp_kein( int index, DWORD skillexp[], DWORD &exp );
extern void RecvSelectNation( t_packet *p, short int cn );

extern int GetCharacterNameInID( LPSTR id, char name[4][20] );
extern void CheckInitData();
extern void CheckStartMap( t_connection c[], short int cn, int &StartPosition );		// 1004 YGI
extern void RecvExistName( t_packet *p, short int cn );
extern void RecvExistNameForNation( t_packet *p, short int cn );
extern void RecvRegistCandidate( t_packet *p, short int cn );
extern void isThisManCandidate( t_packet *p, short int cn );
extern void CheckVote( t_packet *p, short int game_id );
extern void GetVoteValue( short int cn );
extern void CheckAndUpdateVote( t_packet *p, short int cn );

extern void RecvVoteScore( t_packet *p, short int cn );

extern void RecvNationMsg( t_packet *p, short int cn );

extern void SendYouAreKingLog2Log( char *name, short int cn );
extern void SendYouAreKingLog2Client( char *name, int type );
extern void CheckGuildJoin( t_packet *p, short int cn );
extern void SendGuildAllMsg( t_packet *p, short int cn );
extern void RecvReturnGameServer( t_packet *p, int type = 0 );
extern void RecvGmRegist( t_packet *p );
extern void RecvRepStopWarRefusal( t_packet *p );

extern void RecvReqStopWar( t_packet *p, short int cn );	// 다른 맵에 요청할 나라왕이 있는지 보내준다.
extern void RecvRepStopWar( t_packet *p, short int cn );	// 거절 한 경우
extern void RecvRepStopWarAccept( t_packet *p );
extern void RecvReqSalvationMoney( packet *p, short int cn );
extern void RecvInsertSalvation( packet *p, short int cn );

extern void SendServerEachItem( int item_no, short int server_id, short int game_id );
extern void RecvEatChocolate( t_packet *p, DWORD cn );
extern void RecvCheckChocolate( t_packet *p, DWORD cn );
extern void RecvSaveOpenSchoolEvent( t_packet *p, short int cn );
extern void RecvExitGiild( t_packet *p, short int cn );

extern void RecvCheckCandy( t_packet *p );
extern void ResetCharInfo(int *var, CHARLIST *ch); // age 변수를 이용하여 char_info 필드값을 재설정
extern void RecvUpdateLadderScore( t_packet *p );
extern void DirectClient( short int type, short int server_id, short int cn, void *msg, int size );
extern void RecvReqRankLadder( t_packet *p, short int cn );
extern void RecvSearchRankLadder( t_packet *p, short int cn );

extern int isPosableGuildJoinById( int guild_code, char *id );
extern int isPosableGuildJoinByName( int guild_code, char *name );
extern void RecvRegistGuild_DB( t_packet *p, short int cn );
extern void RecvReqGuildExplain( t_packet *p, short int cn );
extern void RecvRegistGuildMark( t_packet *p, short int cn );
extern void SendGuildImage( t_packet *p, short int cn );
extern void RecvRegistGuild( t_packet *p, short int cn );
extern void RecvSaveGuildMemberList( t_packet *p );
extern void SendGuildMailOk( int guild_code );
extern void RecvGuildMailTitle( int guild_code, short int server_id, short int game_id );
extern void RecvUpdateGuildMailId( t_packet *p );
extern void RecvGuildMasterAndSubMaster( t_packet *p, short int cn );

extern void RecvRegistGuildCheck( t_packet *p, short int cn );
extern void RecvCheckSubMaster( t_packet *p, short int cn );

extern void RecvChangeGuildDegree( t_packet *p, short int cn );
extern void RecvChangeDeleteGuild( t_packet *p );
extern void RecvDeleteGuildMemberList( t_packet *p, short int cn );
extern void RecvChangeColor( t_packet *p );
extern void CheckSalvationName( t_packet *p, short int cn );

extern int CheckSalvationNameBasic( char *name );// 020826 YGI
extern int CheckSalvationNameBasic2( char *name );// 020826 YGI

extern int PutEventItem( const int turn, t_connection *c );
extern int PutEventItemByMapReq(const int iCn,t_packet &p);		// BBD 040308
extern void RecvGetNameOfGuildMemberList( t_packet *p, short int cn );
extern void RecvGetGuildNotice( t_packet *p, short int cn );
extern void RecvRegistGuildNotice( t_packet *p, short int cn );
extern void RecvRegistFriend( t_packet *p, short int cn );
extern int RecvGetFriend( t_packet *p, short int cn );
extern void RecvLogout( t_packet *p );
extern bool IsConnectName( char *name );		// 캐릭명으로 접속해 있는지 알아 보는 함수
extern void RecvCheckFriend( int server_id, int cn, char *name );
extern void DeleteFriend( t_packet *p, short int cn );
extern void RecvCheckGuildName( t_packet *p, short int cn );
extern void RecvCheckGuildOthercharacter( t_packet *p, short int cn );
extern void RecvAddEventItem( t_packet *p, short int cn );
extern void RecvGetGuildItemFirst( t_packet *p, short int cn );
extern void RecvGetGuildItem( t_packet *p, short int cn );
extern void RecvPutGuildItem( t_packet *p );



#define KM_INFO	0
#define KM_FAIL	1
#define KM_OK	2
#define KM_BBS	3

extern void RecvGetGuildItemMap( t_packet *p, short int cn );
extern void SendPutMenuString( short int game_server_id, int type, int str_num, int user_id ) ;
extern int DeleteGuildBoxMoney( DWORD &box_money, short int guild_code );
extern DWORD CheckGuildItemPay( short int guild_code );
extern void RecvGetGuildBoxMoney( t_packet *p, short int cn );
extern void RecvCheckGuildBoxMoney( t_packet *p, short int cn );
extern void RecvUpdateGuildBoxMoney();
extern void RecvGetGuildItemCount( t_packet *p, short int cn );
extern int GetMoneyItemNumber();
extern void RecvChangeGuildMaster( t_packet *p, short int cn );
extern void RecvChangeGuildMasterBySubMaster( t_packet *p, short int cn );
extern void RecvRegistSubMaster( t_packet *p, short int cn );
extern void RecvGuildHouseInfo( t_packet *p, short int cn );
extern void RecvChangeGuildHouseInfo( t_packet *p, short int cn );
extern void RecvCheckGuildHouse();
extern DWORD SendDb2AllMap( int type, void *msg = 0, int size = 0 );
extern bool IsExitRecordOfDB( char *table, char *condition );
extern void RecvDeleteSalvation();

// 021008 YGI
extern void SaveGuildLog( int guild_code, int type1, int type2, char *master = 0, char *guild_name = 0 );
extern void SaveGuildLog2( int guild_code, int type, char *name );

//021030 YGI
extern void RecvSaveAmountEventNpcItem( t_packet *p );

//021107 YGI
extern void RecvCheckEventScriptItem( t_packet *p, short int cn );
extern void RecvCheckEventMoveMap( t_packet *p, short int cn );
extern void RecvSaveEventMapMoveNow( t_packet *p, short int cn );

// 030221 YGI
extern void CheckOutSideMail();
// 040105 YGI
extern void RecvGetTreasureMapAttr( t_packet* p, short int cn );

extern void RecvCheckCharGuild( t_packet *p, short int cn);//Eleval 12/06/09
extern void RecvSexChange( t_packet *p, short int cn); //Eleval 12/06/09 - Sex Change
//extern void RecvAskSQuestTeleport( t_packet *p, short int cn); //Eleval 10/08/09 - To bring ppl back in quest

//Thralas
extern void ConvertQueryString(const char* szStr, char* szResult, const int iMaxString = MAX_STEP);

struct k_image_header
{	//< CSD-030324
	DWORD size;
	short int xl;
	short int yl;
};	//> CSD-030324

class CGuildMarkImage
{	//< CSD-030324
public :
	bool faile;
	int total_size;
	char *data;


public : 
	CGuildMarkImage() { InitData(); }
	~CGuildMarkImage() { FreeData(); }

	int InitData();
	int FreeData();
	int Setting( DWORD size, int xl, int yl );
	int SaveImage( int subCount, char *img, int size );
};  //> CSD-030324

template <typename T> class TKeinMap
{	//< CSD-030324
public :
	typedef map<short, T* > GUILDHASH;
	typedef typename map<short, T* >::iterator LPGUILDHASHUNIT;
private :

	GUILDHASH	m_mpBank;	
public :
	T& operator[](int nIndex)
	{
		if( !m_mpBank[nIndex] )
		{
			T* pT = new T;
			m_mpBank[nIndex] = pT;
		}
		return *m_mpBank[nIndex];
	}
	TKeinMap() {}
	~TKeinMap()
	{
		m_mpBank.clear();
	}
	LPGUILDHASHUNIT Start()
	{
		return m_mpBank.begin();
	}
	bool IsEnd( LPGUILDHASHUNIT target )
	{
		return ((target == m_mpBank.end() )?1:0);
	}
	void Reset()
	{
		for( LPGUILDHASHUNIT i = Start(); !IsEnd( i ); i++ )
		{
			delete i->second;
		}
		m_mpBank.clear();
	}
};	//> CSD-030324


#endif // #ifndef __dragonloginserver2_2__
