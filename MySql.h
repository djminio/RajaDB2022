#if !defined(AFX_MYSQL_H__65C7ED7E_9020_467F_AB76_8528EE975EC8__INCLUDED_)
#define AFX_MYSQL_H__65C7ED7E_9020_467F_AB76_8528EE975EC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MAIL_BUF		2048			// 0507

#define MAX_SKILLMAIN 106


typedef struct t_skillmain{
int NO;
char Skill_Minute[31];
int Class_Warrior;
int Class_Thief;
int Class_Archery;
int Class_Wizard;
int Class_Priest;
int Select_Farmer;
int Select_miner;
int Select_fisher;
int Select_Lumberjack;
int Select_Butcher;
int Select_Herbdigger;
int Select_herdman;
int Select_Carpenter;
int Select_Blacksmith;
int Select_Cooking	;
int Select_Tailoring	;
int Select_Bowcraft_Fletcher;
int Select_Alchemy	;
int Select_Candlemaker	;
int Select_Merchant	;
int Howto	;
int mouse_change	;
int Interface1	;
int Interface2	;
int Success_interface	;
int Fail_Interface	;
int Work_target_self	;
int Work_target_othercharacter	;
int Work_target_object	;
int Work_target_Item	;
int Work_target_earth	;
int Work_target_water	;
int Work_target_forest	;
int Work_target_interface	;
int Tool;
int Object_Workshop	;
int Object_target	;
int Obj_Attribute	;
int Resource1	;
int Resource1_quantity	;
int Resourece2	;
int Resource2_quantity	;
int Resource3	;
int Resource3_quantity	;
int Produce_type	;
int Produce_Fix	;
int Ability_Fix	;
int Time_judge	;
int Time_Maintain	;
int Ability_min	;
int Ability_max	;
int Plus_element	;
int Plus_type	;
int Plus_Rate	;
int Plus_min	;
int SP_demand	;
int Success	;
int effectCharobj_status	;
int Change_enermy_status	;
int Change_enermy_status2	;
int charvisible	;
int Effectobj_status	;
int Changeobj_attribute	;
int changeobj_visible	;
int Skill2job	;
int effectChar_hide	;
int Increase_mov	;
int Increse_Life	;
int Increse_mana	;
int Increse_health	;
int Change_mor	;
int Obj_attribute1	;
int ChangeObj_attribute1	;
int Display_LV	;
int DisPlay_Wis	;
int Display_Int	;
int DisPlay_Life	;
int DisPlay_Health	;
int DisPlay_Damage	;
int DisPlay_AC	;
int DisPlay_inventory	;
int Display_Foot	;
int DisPlay_Item_Changeall	;
int DisPlay_royalty	;
int DisPlay_Item_Status	;
int DisPlay_name	;
int DisPlay_item_Price	;
int effect	;
int effect_wave	;
int effect_race	;
int Success_range	;
int Damage	;
int Status_self	;
int Effect1	;
int Effect_wave1	;
int Enemy_status	;
int Range	;
int Enermy_alram	;
int map	;
int Curser1	;
int Curser2	;
int Curser3	;
int point	;
int inclusive;
int money;
int need_exp;
int MotherSkillType;
int MotherSkillExp;

}SkillMain;



extern SkillMain SkillTbl[ MAX_SKILLMAIN];






extern int Init_SQL(LPSTR szDSN, LPSTR szUID, LPSTR szUPW);
extern int Release_SQL(void);
extern int Init_TotalDB_SQL(LPSTR szDSN, LPSTR szUID, LPSTR szUPW);
extern int Release_TotalDB_SQL(void);
extern int Init_ChrLogDB_SQL(LPSTR szDSN, LPSTR szUID, LPSTR szUPW );
extern int Release_ChrLogDB_SQL(void);
extern int Init_NGCDB_SQL(LPSTR szDSN, LPSTR szUID, LPSTR szUPW );//030207 lsw
extern int Release_NGCDB_SQL(void);//030207 lsw

extern int Querry_SQL(LPSTR szQuerry, HDBC hdbc = NULL);
extern int Insert_SQL(LPSTR szUID, LPSTR szUPW);
extern int GetCharInfo_SQL(LPSTR szUID, t_packet *packet);
extern int GetCharDB_SQL(t_connection c[], int cn);
extern int GetCharGameDB_SQL(t_connection c[], int cn);
extern int GetNameCount_SQL(LPSTR szUID);
extern int CheckName_SQL(LPSTR szUNM);
extern int CreateChar_SQL(t_connection c[], int cn, t_packet *packet);
extern int CreateChar2_SQL(t_connection c[], int cn );
extern int DeleteChar_SQL( const char *id, const char *name,const char *szSecretKeyCode);//020725 lsw

extern int MoveDeleteChar_SQL( const char *szName);//020725 lsw

extern int delete_char_create_fail( LPSTR name );

extern int GetCharactersBasicInfoInID_SQL( LPSTR id, t_packet *packet );


extern int get_BinaryData_from_Chr_Info  (UCHAR *ws, UCHAR *ps, UCHAR *skill, UCHAR *skill_exp, UCHAR *tac_skillEXP, UCHAR *script_var, UCHAR *inv, UCHAR *equip, UCHAR *quick,UCHAR *party,UCHAR *relation,UCHAR *employment,UCHAR *itemindex, char *login_id, char *name);
extern int get_BinaryData_from_Chr_Info2 (UCHAR *bankitem,	 char *login_id, char *name);
extern int update_BinaryData_to_Chr_Info (UCHAR *ws, UCHAR *pa,  UCHAR *akill, UCHAR *skill_exp, UCHAR *tac_skill_exp, UCHAR *script_var, UCHAR *inv,  UCHAR *equip, UCHAR *quick, UCHAR *party,UCHAR *relation,UCHAR *employment,UCHAR *itemindex,char *, char *) ;	//1219 YGI
extern int update_BinaryData_to_Chr_Info2(UCHAR *bankitem, char *, char *) ;


extern int  updateCharacterStatus(t_connection [], int) ;

extern void updateCharacterVeryImportantStatusToLoginServer( t_connection c[], int char_id );
extern void updateCharacterVeryImportant_TacticsSkillExp_ToLoginServer( t_connection c[], int char_id );
extern int RecvUpdateCharacterVeryImportantStatus( t_update_very_important_status *tp );
extern void updateCharacterStatusToLoginServer( t_connection c[], int char_id);
extern void updateBinaryDataToLoaginServer( t_connection c[], int id );



extern int GetMapName_SQL(t_connection c[], int cn);
extern int GetConnectInfo_SQL(t_connection c[], int cn, t_packet *packet, char *mapname);
extern int GetChangeMapInfo_SQL(t_connection c[], int cn, t_packet *packet);

extern int CheckUsedID_SQL( LPSTR szUID, WORD *wPort, DWORD *dwID, DWORD *dwServerSetNum );

extern void SendDeleteUsedID( int server_id );
extern int  IsThereLoginTable_SQL( LPSTR szUID );


extern int AddBoxItem_SQL(int id);
extern int DeleteBoxItem_SQL(int id);
extern int PutBoxItem_SQL(int id, int pos, ItemAttr *I);
extern int GetBoxItem_SQL(int id, int pos, ItemAttr *I);


// Party/ Relation/ Employment에 대한 Data릉 DB에서 가져온다. 
extern int GetPartyChar_SQL( char *name, int *Level, int *Face, int *Str, int *Class, int *Gender );	// 0115

extern int UpdateTotalMapConnections( char *mapname, int no );
extern int TotalConnections( void );

extern void RecvIsThereCharName( int cn, char *name );
extern int get_BinaryData_Party( UCHAR **party, const char *name);		// 0116 YGI

extern int CheckBetaId_SQL(LPSTR szUNM);		// 0130 YGI
extern void CheckBetaIdTest( int cn, char *id );			// YGI 0130
extern int CheckNoName_SQL(LPSTR szUNM);			// 0131 YGI
extern bool SearchStrStr( const char *szSource, const char *szWhite );		// 0208 YGI
extern bool SearchStrWord( const char *szSource );		// 0209 YGI
extern void LoadNoNameString();

extern int InitSkillTable( void );








//////////////////////////

//1029 zhh
extern int RecvUpdateSpecial( t_server_special_item *p);

extern int RecvUpdateCharDB( t_update_char_db *p );
extern int RecvUpdateBinaryData( t_server_update_binary_data0 *p );
extern int RecvUpdateTacticSkillExpData( t_update_very_important_tactics *p );
extern int  RecvUpdateScriptData( t_server_update_script_data *p );
extern int RecvUpdateBinaryData1( t_server_update_binary_data1 *p );
extern int RecvUpdateInvData( t_server_update_inv_data *p );
extern int RecvUpdateItemData( t_server_update_item_data *p );
extern int RecvUpdateBankItemData( t_connection c[], int cn, t_server_update_bankitem_data  *p  );

extern int EndsetPartyMenberForUpdate( CHARLIST *ch );		// 0218 YGI

extern int CurrentTotalUserInMap( void );

extern int GetTitleBBS( int count, int ct[10], TIMESTAMP_STRUCT date[10], char name[10][ FILENAME_MAX], char title[10][ FILENAME_MAX] );


//////////////////////////////////		0405 YGI /////////////////////////
extern int GetBelieveAndFaith_SQL( int &believe, int &faith, char *name );		// 0316 YGI
extern int UpdateFaith_SQL( short int faith, char *name );						// 0316 YGI

extern int UpdateEvaName( const char *my_name, char *eva_name );		// 전도한 사람 이름을 디비에 업데이트 한다.//020725 lsw
extern void SubtractFaith( const char *naem );//020725 lsw




extern int GetEvangelist( char *my_name, char *eva_name );

extern bool CheckIsRealName( char *id, char *charname );

extern int GetCharNew( int &is_new, char *name );		// new char
extern int UpdateCharNew( char *name );




extern int GetGodMeetingTime( TIMESTAMP_STRUCT &day, TIMESTAMP_STRUCT &month, TIMESTAMP_STRUCT &year, int god_index );
extern char *GetMeetingMessage( int god_type, int text_type, int text_num );			// 0407 YGI

extern int UpdateCharStatusByKein( k_char_update_data *ch );		// 0410 YGI
extern int GetCharDataStatusByKein( k_get_char_info *ch, char *name );		// 0410 YGI
extern int UpdateCharStatusByKein( t_connection c[], short int cn );		// 0410 YGI

extern int AccessBoxData( int box_id );			// 0420 YGI

extern int GetMailTitle( char *name, MAIL mail[], int start_mail_id );	// 020808 YGI 
extern int GetMailBody( int type, DWORD  mail_id, char *body );
extern int DeleteMail( DWORD  mail_id );


extern bool UpdateLogintablebyChangeMap( char *user_id, char *map_name );


extern int GetRowLineOfSQL( const char *table, const char *field, int *RowCount, const char *condition, HDBC hdbc = NULL );		// 1004 YGI
extern int GetRecentMapName( char *char_name, char *map_name );


extern void GetPublicBbs( char **text );			// 0725 YGI
extern int InsertHunterList( char *target_name, char *wanted_name, DWORD money, char *profile );		// 0802 YGI
extern int GetHunterList( int id, k_hunter_list *hunterlist, int type );//soto-031006
extern int CheckMail( DWORD  mail_id );			// 0808 YGI
extern int DeleteHunterList( int list_id );

extern int DeleteBox( int box_id );		// 0817 YGI
extern int SearchBoxAndDelete( UCHAR **inv, UCHAR **bank, const char *szName );//020725 lsw
extern void DeleteBoxByDeleteCharacter( const char *szname );		// 캐릭터를 지울때 박스도 지운다.//020725 lsw

extern int UpdateResetJob_SQL( int job, char *name );		// 0909 YGI
extern int get_Skill_BinaryData(UCHAR **skill_exp, UCHAR **script_var, char *name);
extern int Update_Skill_BinaryData(UCHAR **skill, UCHAR **skill_exp, UCHAR **script_var, char *name);
extern int UpdateSelectNation( int nation, char *name );	// 0927 YGI
extern int GetNationById( char *login_id );		// 0927 YGI
extern int GetMapInfo( t_mapinfo aMap[] );
extern int MapPort( char *mapname );
extern bool GetGuildCode(const char* szName, int& rGuildCode); // CSD-030326
extern bool SetGuildCode( char * pName, int iGuildCode);	// 030602 YGI
extern int GetNationByName( char *name, DWORD *nation );		// 1027 YGI 국가값만 가지고 오는것이 아니라 네임스테이터스 다 가져온다.
extern int GetVoteById_SQL( char *szUID );
extern int SetVote_SQL( char *id, int vote_num );

extern int SetPlusScoreVote( int candidate, int vote_num, int nation );					// 001031_2 YGI // 득표를 더해준다.
extern int GetScoreVote( int candidate, int vote_num, int nation );		// 001031_2 YGI


extern int RegistCandidate_SQL( k_candidate *p );		// 후보 등록
extern int GetCandidate_SQL( const char *name, short int vote_num, k_candidate *p );		// 후보 정보 가져오기
extern int GetCandidate_SQL( short int vote_num, short int nation, k_candidate p[] );		// 후보 정보 가져오기

extern int GetCurrentVoting( int vote_num, int nation, k_rep_vote_score *target );		// 현재 선거 진행 상황
extern int GetVoteInfo( k_set_value_of_vote *target );	// 선거 번호와 현재 선거 상태
extern int SetVoteEndFlag( int count, int type );		// 득표를 더해준다.
extern int GetVoteNumberOne( int nation, int vote_num, char *name );
extern int UpdateYouAreKing( char *name, int king );
extern int SetVoteEndFlag( int count );
extern int CheckDbTable(int nation, char *name );
extern int GetKingOfNation_SQL( int nation, char *name );
extern int InsertGmRegist( k_gm_regist_db *p );		// 1027 YGI
extern bool IsBadUser(const char* szUserID);
extern int GetSalvation( char * name, DWORD &money );		// 기부한 돈 알아보기// 001214 YGI
extern int PlusMoneyRedClose( double &TotalMoney, DWORD plus_money );

extern int LoadNoName_SQL();		// 010117 YGI
extern int SetChocolateCount( char * name, int &count );		// 010212 YGI
extern int GetTopGivenChocolate( char * name, int &count );		// 누가 가장 많이 가지고 있는가

//010303 YGI
extern int SaveOpenSchoolItem( char *name, int nation, int item_no, int &number );
extern int SetNationByName( DWORD status, char *name );		// 1027 YGI

// 010310 YGI
extern int GetChocolateEatName( char *name, DWORD total_id );
extern int GetNameByTotalId( char *name, DWORD total_id );
extern int SaveWhiteDayEvent( char *name, char *name2 );

// 010314 KHS
extern int CheckLogInTable( int server_set_num );
extern int CheckWorstDBTable( void );

// 010511 YGI
extern int UpdateLadderScore( DWORD ladderscore, char *name, int nation, int cls, int lv );
extern void RefreshColossus_rank_read_table();
extern int GetLadderScoreRank( int rank, k_db_get_ladder_score_rank *rank_data );
extern int GetRankLadderByName( char *name );

//010530 YGI
extern int SaveNationInfo_SQL( k_save_nation_info *p );


// 010801 YGI
extern int UpdateGuildMark( int guild_code, int size, UCHAR *mark );
extern int GetGuildImageSize( int guild_code );
extern int SaveGuildRegistImsi( int guild_code, k_regist_guild_imsi_db *guild, k_set_guild_info *guild_info );
extern int GetLoginIdByName( char *name, char *login_id );
extern int GetDataBasic2ByName( k_char_data_basic2 *data, char *name );

extern int GetEmptyGuildCode( int &guild_code );
extern int GetGuildExplain( int guild_code, int &len, char *explain );
extern int IncreaseNumberOfGuildList( int guild_code, int type, BYTE &number );
extern int GetGuildMarkImage( int guild_code, char *image, int size, int &mark_num );
extern int SaveGuildRegist( k_guild_regist *guild, int &info_num );
extern int SaveChangeGuildDegree( k_guild_change_degree *guild, int &info_num );
extern int ChangeGuildMemberList( char *char_name, int guild_code, int guild_degree );
extern int GetGuildMakeNumber( int guild_code, int &make );
extern int PutGuildMail( int guild_code, char *title, char *body, char *ch_name, int degree );
extern int GetGuildMailTitle( int guild_code, k_guild_mail mail[] );
extern int GetGuildMailBody( DWORD guild_mail, DWORD mail_id, char *body );

extern int UpdateGuildMailId( char *name, DWORD mail_id );
extern int GetGuildMailId( char *name, int &mail_id );
extern int CheckGuildMail( int guild_code, int &mail_id );
extern int GetGuildMailInfo( DWORD mail_id, int &conv_guild_code, int &conv_degree );
extern int DeleteGuildMail( DWORD mail_id );
extern int GetGuildMasterAndsubMaster( int guild_code, char *master, char *sub_master );
extern int IsExistGiuildMember( char *name );		// 길드멤버에 내가 속해 있는가?
extern int CheckGuildMemberForRegistGuild( int nGuildCode );
extern int DeleteGuild( int guild_code );
extern int DeleteGuildMemberList( int guild_code );
extern int DeleteImsiGuild( std::vector<int> *guild_code, int &guild_code_count );
extern int GetEventItemNumber( int *item_no, char *szID);
extern int DeleteEventItemNumber( char *szID, int count );
extern int GetCharOfGuildMemberList( int guild_code, k_get_guild_memeber_list *data );
extern int GetGuildNotice( int guild_code, char *text );
//extern int SetGuildNotice( int guild_code, char *text );
extern int RegistFriend_SQL( char *name1, char *name2 );
extern int GetFriend_SQL( char *name, char data_name[][20] );
extern int SaveEventItem( char *name, int item_no, int count );

extern int GetGuildItemIndexAndCount( int guild_code, int &max, DWORD *index );
extern int GetGuildItem( int guild_code, int cn, ItemAttr *item, int &count, DWORD *index );
extern int InsertGuildItem( int guild_code, ItemAttr *pItem, char *name );
extern int GetGuildItemOne( int guild_code, DWORD index, ItemAttr *pItem );		// 실제 아이템 하나 가져오기
extern int GetGuildItemOne( int guild_code, int item_no, ItemAttr *pItem, char *name );
extern int GetGuildItemPay( int guild_code, DWORD &box_money );
extern int GetLastGuildCode( int &last_guild_code ); // CSD-030324
extern int GetActiveByGuildList( int guild_code, int &active );
extern int CheckGuildMasterLastConnect( int guild_code );
extern int GetGuildHouseInfo( k_guild_house_info *data, int &count, int nation );
extern int GetGuildHouseInfoById( k_change_guild_house_info_db2map *data, int house_id );
extern int GetCheckGuildHouse( char *pHouseId, int &count );
extern bool IsExitRecordOfDB( char *table, char *condition );
extern void displaySQLError(SQLHSTMT hStmt, char *szQuery = NULL);
//< CSD-020724
extern int GetSkillPoint(const char* pName);
extern int ClearSkillPoint(const char* pName);
//> CSD-020724
#define SQLOK( x ) ( (x) == SQL_SUCCESS_WITH_INFO || (x) == SQL_SUCCESS )		//1027 YGI
// 020808 YGI
extern int SaveItemLog( k_item_log *pData );

extern void Log_LogIn( char *id, char *ip ); // finito131006

//021030 YGI
#ifndef __k_startitem_basic__
#define __k_startitem_basic__
struct k_startitem_basic
{
	int m_nEventNo;
	int m_bAll;
	int m_nSex;
	int m_nClass;
	int m_nNation;
	int m_nItem1No;
	int m_nItem1Mutant;
	int m_nItem1Grade;
	int m_nItem2No;
	int m_nItem2Mutant;
	int m_nItem2Grade;
	int m_bAble;		// 다 확인후에 제공할지 안할 지 판단용
	char m_szTable[20]; // 030616 YGI

	k_startitem_basic()
	{
		m_nEventNo = 0;
		m_bAble = 0;
		m_szTable[0] = 0; // 030616 YGI
	}
};
#endif


extern int AddEventItem( CHARLIST *ch, k_startitem_basic* pData );
extern int MakeAndSetItem( CHARLIST *ch, int item_no, int item_mutant, int item_grade );
extern int CheckEventITem( CHARLIST *ch );
extern int CheckEventObject( char *map_name, k_event_object_sound *data );
extern int CheckEventSound( char *map_name, k_event_object_sound *data );
//021107 YGI
extern int GetEventMoveMapName( k_event_move_map_req *pData, k_event_move_map_rep *pMapData );
extern int LoadNPCLevTable(); // CSD-030306
// 040105 YGI
extern int GetMapNameByNumber( char *name );
extern int GetTreasureAttr( int &mapnumber, int &x, int &y );

extern bool ChangeSexOfPlayer(short int sex, const char *cId); //Eleval 12/06/09 - Sex Change

extern HENV  hEnv;
extern HDBC  hDBC;
extern HENV  hEnv_TotalDB;
extern HDBC  hDBC_TotalDB;
extern HENV  hEnv_ChrLogDB;
extern HDBC  hDBC_ChrLogDB;

extern HENV  hEnv_NGCDB;
extern HDBC  hDBC_NGCDB;

extern int FREE_LEVEL_; // CSD-040127

#endif // !defined(AFX_MYSQL_H__65C7ED7E_9020_467F_AB76_8528EE975EC8__INCLUDED_)