
extern int WaitMoveMap ;

#define MAX_BOX_ITEM			15
#define MAX_GOD					4

#define MAX_MSG					200
//#define MAX_GUILD				513

#define MAX_GUILD_HOUSE			200

////////////////////////////////////////////////////////////////////////////////////



#define CMD_RESEND_ITEM			10001		// �κ��丮 Ȯ���� ���� �������� ���� ����
#define CMD_RESEND_CHARLIST		10003       //
#define CMD_MAGIC_STRIKE		10004		// ������ ������ ��,
#define CMD_OTHER_CH_INV		10005		// �ٸ� ����� ������ ����� ����
#define CMD_DIVIDE_ITEM			10006		// ������ ������ �������̽��� ���� ���� ��
#define CMD_CREATE_ITEM			10007		// ������ ����
#define CMD_BOX_OPEN			10008		// �ڽ� ����

#define CMD_RESEND_ITEM_EQUIP	10009		
#define CMD_RESEND_ITEM_QUICK	10010

#define CMD_DELETE_ITEM			10011		// ������ �μ���]
#define CMD_DECREASE_ITEM		10012		// ������ dur ����

#define CMD_LVUP_POINT_EACH		10013		// ������ ������ ��ġ ����

#define REQ_LEVELUP_POINT		10014		// ������ ����Ʈ�� ��û�Ѵ�. �ӽ�
#define CMD_LVDOWN_POINT_EACH	10015		// ������ ������ ��ġ ����
#define CMD_LEVELDOWN_OK		10016		// �����ٿ� ������

#define CMD_LEARN_ITEM			10017		// ������ ���� 
// #define CMD_LEARN_ITEM_OK		10018		// ������ ���� ����
#define CMD_ITEMREPAIR_REQ		10019		// ������ ��ġ��
#define CMD_ITEMREPAIR_OK		10020		// ������ ��ġ�� ����
#define CMD_RESULT				10021		// �������� ���� ������� ��� (�� -1:���� ����)
#define CMD_LEARN_SKILL_OK		10022		
#define CMD_SKILL_EXP			10023
#define CMD_OPEN_STATUS_REQ		10024		// �������ͽ� â�� ������

#define CMD_REQ_CHAR_INFO_PLUS	10025		// ĳ���� �߰� ���� ��û

#define CMD_SEND_CHAR_DISEASE	10026		
#define CMD_PARTY				10028
#define CMD_RELATION			10029
#define CMD_EMPLOYMENT			10030
#define CMD_ITEM_INDEX			10031	
#define CMD_DEFRAYAL			10032
#define CMD_SEND_BANK_INV		10033

#define CMD_DO_PARTY			10034
#define CMD_DELETE_PARTY		10035

#define CMD_REQ_PARTY_MEMBER	10036

#define CMD_REQ_LEARN_MAGIC		10037

#define CMD_CLIENT_CHAR_NAME	10038

#define CMD_LEARN_MAGIC_OK		10039
#define CMD_PREVENTING			10040		// ���� ����	// ���� ������ �� �ֱ⿡ ����� �����ش�.
#define CMD_CURE_DISEASE		10041		// ���� ġ��	// 100%�̱⿡ ����� �������� �ʴ´�.

#define CMD_REQ_ITEM_VALUE				10042
#define CMD_REQ_ITEM_VALUE_SELL			10043
#define CMD_REQ_ITEM_VALUE_REPAIR		10044

#define CMD_SERVER_PARTY				10045
#define CMD_CLIENT_INN					10046
//#define CMD_TAC_SKILL_EACH_EXP			10047

#define CMD_SERVER_WAKE_UP				10048

#define CMD_REQ_JOIN_GAME				10049	// ���ӿ� ���Դٴ� ���� �˸���.
#define CMD_SERVER_EXIT_GAME			10050	// ���ӿ��� �����ٴ� ���� �˸���.
#define CMD_REQ_MY_PARTY				10051

#define CMD_PARTY_JOIN_OK				10052
#define CMD_PARTY_JOIN_RELEASE			10053

#define CMD_SERVER_EACH_ITEM			10054
#define CMD_OPEN_ABILITY				10055
#define CMD_SUBTRACT_MONEY				10056
#define CMD_ADD_MONEY					10057

#define CMD_LEARN_ALL					10058
#define CMD_LEARN_ALL_NOT				10059


#define CMD_EXCHANGE_ITEM_READY			10060		// �ŷ��ϱ� ���� ���� ������ �Ѱ��
#define CMD_EXCHANGE_ITEM_REQ			10061		// ������ ��ſ��� ���� �ŷ��� ��û�ߴ�.
#define CMD_EXCHANGE_ITEM				10062
#define CMD_EXCHANGE_ITEM_RESULT		10063		// �ŷ� ��û�� ���� ��� ����
#define CMD_EXCHANGE_OK_SIGN			10064
#define CMD_EXCHANGE_CANCEL				10065
#define	CMD_EXCHANGE_ITEM_EACH			10066
#define CMD_EXCHANGE_ITEM_DEL			10067

#define	CMD_CHECK_BETA_TEST				10068
#define	CMD_CHECK_BETA_TEST_OK			10069
#define	CMD_CHECK_BETA_TEST_NOT			10070

#define CMD_IATTR_DURATION				10071
#define CMD_IATTR_MUCH					10072
#define CMD_IATTR_LIMIT					10073
#define CMD_IATTR_ATTR					10074
#define CMD_IATTR_ID					10075
#define CMD_IATTR_RESERVED0				10076
#define CMD_IATTR_RESERVED1				10077

#define CMD_REQ_AC						10078
#define CMD_OTHER_GHOST					10079
#define CMD_REQ_DMG						10080
#define CMD_SERVER_KILLMON				10081

#define	CMD_PARTY_ACCESS				10082
#define CMD_REQ_PARTY_TOGETHER			10083		// ���� ������ �ΰ� �ִ��� �˾ƺ��� ���� �α��� ������ ��� ��û�Ѵ�.

#define CMD_PARTY_NO_NAME				10084
#define CMD_RELATION_NO_NAME			10085
#define CMD_EMPLOYMENT_NO_NAME			10086

#define CMD_REQ_MAGERY					10087

#define CMD_THROW_DICE					10088		// �ֻ��� ������...
#define CMD_CREATE_ABILITY				10089		// �⺻��ġ ���� ����

#define	CMD_PUBLIC_NOTICE_BBS_REQ		10090
#define	CMD_RANK_BBS_REQ				10091
#define	CMD_FORUM_BBS_REQ				10092
#define	CMD_EVENT_BBS_REQ				10093	
#define	CMD_MYDIARY_BBS_REQ				10094
#define	CMD_BBS_BBS_REQ					10095
#define	CMD_ETC_BBS_REQ					10096

#define CMD_GET_SERVER_TEXT				10097
#define CMD_LOGIN_GET_BOX_ITEM			10098
#define CMD_PUT_BOX_ITEM				10099		// �α��� ������ ����

#define CMD_PREACH_NAME					10100		// ������ �̸�

#define CMD_GOD_REGIST_OK				10101		// ������ ����Ѵ�.
#define CMD_GOD_REGIST_CANCEL			10102		// ������ϵǾ� �ִ� ���� ��ҽ�Ų��.

#define CMD_LOGIN_PREACH_NAME			10103		// �α��� ������ ���� �������� �����Ѵ�.
#define CMD_LOGIN_PREACH_NAME_OK		10104
#define CMD_LOGIN_PREACH_NAME_CANCEL	10105			
#define CMD_PREACH_NAME_OK				10106		// ���� �� ��� �žӼ�ġ�� �÷� ����

#define CMD_NOW_GOD_MEETING_START		10107		//	���� ���� �ð��̴�
#define CMD_NOW_GOD_MEETING_END			10108		//	���� ���� �ð����̴�. 

#define CMD_TOOL_PASSWORD				10109		// ���� ����ϱ� ���� �н�����

#define CMD_CHECK_NEW_CHAR				10120		// ĳ���� �ʱ�ȭ
#define CMD_CHECK_NEW_CHAR_OK			10121
#define CMD_CHECK_NEW_CHAR_NOT			10122

#define CMD_LOGIN_EVANGELIST_CREATE		10123
#define CMD_LOGIN_EVANGELIST_DELETE		10124

#define CMD_GET_GOD_TABLE				10125
#define CMD_MEETING_TEXT				10126

#define	CMD_CHAR_UPDATE_DATA_BY_KEIN	10127
#define	CMD_GET_CHARINFO_BY_KEIN		10128		// ó�� �žӼ�ġ���� ĳ���� ������ ���Ӽ����� �����ٶ�

#define CMD_SERVER_KILLPC				10129		// 0410 KHS�߰�...

#define CMD_CAN_MEMORIZE				10130		// �޸������ �Ҽ� �ִ°�...
#define CMD_CAN_MEMORIZE_OK				10131		// �޸������ �����ϴ�
#define CMD_CAN_MEMORIZE_NOT			10132		// �޸������ �� �ð��� �ƴϴ�.

#define CMD_SEND_EAR_MESSAGE			10133		// �ӼӸ� ����
#define CMD_SEND_EAR_MESSAGE_OK			10134		
#define CMD_SEND_EAR_MESSAGE_NOT		10135		
#define CMD_SEND_EAR_MESSAGE_OTHER		10136		// �ӼӸ��� �����Ҷ� �ٸ� �ʿ� �ִ��� �˾� ����.
#define CMD_SEND_EAR_MESSAGE_RESULT		10137		// ���� �ӼӸ��� ���� ���
#define	CMD_LOGIN2GAME_EAR_MESSAGE_RESULT	10138	// �α��� ������ ���� �ִ� ���Ӽ����� �����ش�.
#define CMD_GAME2CLIENT_EAR_RESULT			10139	// ���� �ӼӸ��� ���� ȸ��
#define CMD_GAME2LOGIN_CHECK_NAME			10140

#define CMD_GAME2LOGIN_MOVING_ITEM			10141	// ������ �̵��� ĳ���� ���� �����Ѵ�.

#define CMD_CHANGE_MAP_KEIN					10149	// �ٸ� ������ �̵�

#define CMD_ACCESS_JOIN_KEIN				10150	// connections�� ���̵�� �̸��� ����Ѵ�.
#define CMD_LOGOUT_KEIN						10151	// �α׾ƿ��� �����ش�. ( ����ȯ�� ) ������Ʈ�� ���� �ʴ´�.

#define CMD_ACCEPT_JOIN_KEIN				10152

#define CMD_CHANGE_MAP_DATA1				10153	// �ٸ� ������ �̵� ����Ÿ ����1
#define CMD_CHANGE_MAP_DATA2				10154	// �ٸ� ������ �̵� ����Ÿ ����2
#define CMD_CHANGE_MAP_DATA3				10155	// �ٸ� ������ �̵� ����Ÿ ����3
#define CMD_CHANGE_MAP_DATA4				10156	// �ٸ� ������ �̵� ����Ÿ ����4
#define CMD_CHANGE_MAP_DATA5				10157	// �ٸ� ������ �̵� ����Ÿ ����5
#define CMD_CHANGE_MAP_DATA6				10158	// �ٸ� ������ �̵� ����Ÿ ����6
#define CMD_CHANGE_MAP_DATA7				10159	// �ٸ� ������ �̵� ����Ÿ ����7
#define CMD_CHANGE_MAP_DATA8				10160	// �ٸ� ������ �̵� ����Ÿ ����8
#define CMD_CHANGE_MAP_DATA9				10161	// �ٸ� ������ �̵� ����Ÿ ����9

#define CMD_RECALL_BOX_ITEM					10162	// �α��� ������ �ڽ� �������� �ٽ� ��û�Ѵ�.
#define CMD_IF_DOUBLE_BOX_THEN_DELETE		10163	// �Ȱ��� �ڽ��� ���� ��� �����.

#define CMD_CHANGE_MAP_CONFIRM				10164	// �ʰ� �̵��� �ð��������� ������ �߻��ϸ� ������ Ȯ���� ��û�Ѵ�.
#define CMD_CHANGE_MAP_FAIL					10165	// ���̵��� ������ �����.
#define CMD_NOW_CHANGEMAP					10166	// ���̵� ���̴�...

#define	CMD_REQ_SKILL_ALL					10167	// ��ų ����ġ ��û

#define CMD_REQ_FAITH_UP					10168	// �ٸ� �ʿ� ������ �ִ��� Ȯ���ؼ� �žӽ��� �÷��ش�.
#define CMD_DIVINE_UP						10169	// divine�� �÷��ش�. 
#define CMD_DIVINE_DOWN						10170	// divine�� �������� Ŭ���̾�Ʈ�� �˷��ش�.
#define CMD_OPEN_SUPPER						10171	// �������� �����޴� ������ ��û�Ѵ�.

#define CMD_I_GET_ITEM_OF_SUPPER			10172	// �������� ������ ���� �޴´�.

#define CMD_NOTE_MEETING					10173	// ���� �ѽð� ���ΰ��� �˸���.
#define	CMD_NOT_EXIST_GAMESERVER			10174	// ���Ӽ����� �ϳ��� �������� �ʴ´ٸ�...

#define CMD_REQ_CHAR_INFO					10175	// ĳ������ ������ ���۹޴´�.
#define CMD_OH_MY_PARTY						10176	// ���� ��� �Դ�

#define CMD_REQ_PARTY_INFO					10177	// ���� �ΰ� �ִ� ĳ���� ���� ������ �޾� �´�.

#define CMD_LOGIN_TO_GAME_PUBLIC_BBS		10178	// �α��μ������� Ŭ���̾�Ʈ�� ���������� ������ 
#define CMD_CALL_PUBLIC_BBS					10179	// ��������

#define CMD_SEND_MAIL_OK					10180	// ���� ������ ����
#define CMD_SEND_MAIL_FAIL					10181	// ���� ������ ����

#define CMD_START_GAME_MAIL					10182	// ó�� �������� ���� Ȯ��
#define CMD_SEND_LEARN_ITEM_INDEX			10183	// ó�� ��� ������ ���..

#define CMD_CALL_PUBLIC_BBS_ONLY_ONE		10184	// �Ѹ��� �����ִ� ��������..
#define CMD_HUNTER_REGIST					10185
#define CMD_GET_HUNTER_LIST					10186
#define CMD_SEND_HUNTER_LIST				10187

#define	CMD_KILL_HUNTER_LIST				10188	// ������� ��Ҵ�.
#define	CMD_KILL_HUNTER_LIST_OK				10189	// �޽��� ���, �����մϴ�. ����� �󸶸� �޾ҽ��ϴ�...
#define	CMD_KILL_HUNTER_LIST_CANCEL			10190	// ���		// �ʾ����ϴ�. �̹� ������ ���� ������� �޾ҽ��ϴ�.
#define CMD_HUNTER_REGIST_RESULT			10191	// ���������� ��Ų��� ����� �Խ��ǿ� ����� ���������� ���̴µ� �����߽��ϴ�.
#define CMD_KILLED_BY_HUNTER				10192

#define CMD_KILL_WHO						10193	// ���� ���� �׿���.
#define CMD_DANGER_OF_HUNTER				10194	// ������ ���� �븰��.


#define CMD_REQ_QUEST_INDEX					10195
#define CMD_REP_QUEST_INDEX					10196

#define CMD_PARTY_NOT_BY_LEVEL				10197
#define CMD_DO_PARTY_OK						10198

#define	CMD_REQ_MAN_TO_MAN					10199	// 1:1 ���� ��û
#define	CMD_REQ_MAN_TO_MAN_RESULT			10200	// ���� ��û�� ���� ���( ���������� ��û�ߴ�, �ƴ� ������ ���� �����̴�.. ������ �ȵȴ�.. �����.. )
#define CMD_REQ_MAN_TO_MAN_CONSENT			10201	// ���� �³�
#define CMD_REQ_MAN_TO_MAN_REFUSAL			10202	// ���� ����
#define	CMD_DELETE_BOX_ITEM					10203
///////////////////////////////////////////////////////////////////////////////////


#define	CMD_MAN_TO_MAN_ITEM_EACH			10204	// 1:1 ��� �ҷ��� �Ҷ� �ɰ� �Ǵ� ������
#define CMD_FIGHT_MAP_MESSAGE				10205	// ���� �ʿ��� ���� �޽����� ����Ҷ�...
#define CMD_FIGHT_MAP_ADD_OK				10206	// �����ߴ�
#define	CMD_FIGHT_MAP_ADD_WHO				10207	// ������ �����ߴ�.
#define	CMD_FIGHT_MAP_DELETE_WHO			10208	// ������ ������ ������.
#define	CMD_FIGHT_MAP_MEMBER_INFO			10209	// ó������ ��Ʋ���� ����ϸ� �׵��� ����� ����� ������ �����ش�.
#define CMD_FIGHT_MAP_START					10210	// ��ڰ� ��Ʋ�� ��ŸƮ�� �˸���.
#define	CMD_FIGHT_MAP_END					10211	// ��ڰ� ��Ʋ���� �������� ������ �˸���
#define	CMD_FIGHT_MAP_ADD_FULL				10212	// �ο��� �� á��


#define CMD_RESET_JOB						10213	// JOB�� ���� ����
#define	CMD_DELETE_ITEM_BY_DURATION			10214	// �������� ��뿡 ���� �μ��� ���
#define CMD_SELECT_NATION					10215	// ���� ���� 

#define CMD_SCRIPT_CHANGE					10216

#define CMD_CHANGE_DURATION					10217
#define	CMD_SEND_EAR_MESSAGE_RESULT_ETC		10218	// �ӼӸ��� ���� ��� �����
#define CMD_EXIST_NAME						10219	// �����ϴ� �̸��̳�?

#define CMD_ISSAME_MY_NATION				10220	// ���� ���� ������?
#define CMD_EXIST_NAME_AND_NATION			10221

#define	CMD_VOTE_GAME2LOGIN					10223	// ��ǥ���õ� ���� ������ �α��� �������� ��Ŷ..
#define CMD_VOTE_OK							10224	// ���Ÿ� �ߴ�.
#define	CMD_VOTE_NOT						10225	// �����Ҽ� ����.

#define CMD_REGIST_CANDIDATE				10226	// �ĺ� ���
#define CMD_REGIST_CANDIDATE_OK				10233	// �ĺ� ��� ����
#define CMD_REGIST_CANDIDATE_NOT			10234	// �ĺ� ��� ����

#define CMD_IS_THIS_MAN_CANDIDATE			10227	// �ĺ��� ��ܿ� �ִ� ����̳�?
#define CMD_THIS_MAN_IS_CANDIDATE_OK		10228	// ��ܿ� �ִ�.
#define CMD_THIS_MAN_IS_CANDIDATE_NOT		10229	// ��ܿ� ����.

#define CMD_CHECK_VOTE						10230	// ��ǥ�Ҽ� �ִ��� �������� üũ
#define CMD_CHECK_VOTE_NOT					10231	// ��ǥ�Ҽ� �ִ����� ���
#define CMD_CHECK_VOTE_OK					10232	// ��ǥ�Ҽ� �ִ�.

#define CMD_SET_VALUE_OF_VOTE				10235	// ���� �ý��ۿ��� ����� ����Ÿ ��������
#define CMD_RESET_VOTE_VALUE				10236
#define CMD_RETRY							10237	// �ٽ� �õ� �ش޶�� �޽����� �Ѹ��� �Ѵ�.

#define CMD_REQ_VOTE_SCORE					10238	// Ŭ���̾�Ʈ���� ��񵥸�����
#define CMD_REP_VOTE_SCORE					10239	// ��� ���󿡼� Ŭ���̾�Ʈ�� 

#define CMD_GET_SKILL_INFO					10240	// ���콺 ������ ������ �ߴ� ��ų ���� ��û

#define CMD_SEND_ALL_MSG					10241	// ���� ����
#define CMD_RECV_ALL_MSG					10242	

#define CMD_YOU_ARE_KING_LOG2LOG			10243	// �� ���̴�. ( ���󿡼� 5000������ ������. )
#define CMD_YOU_ARE_KING_LOG2CLIENT			10244	// �� ���̴�. ( 5000���� Ŭ���̾�Ʈ�� ������. )

#define CMD_YOU_ARE_NO_KING_LOG2LOG			10245	// �� �տ��� ����. ( ���󿡼� 5000������ ������. )
#define CMD_YOU_ARE_NO_KING_LOG2CLIENT		10246	// �� �տ��� ����. ( 5000���� Ŭ���̾�Ʈ�� ������. )

#define CMD_GUILD_EXIT_COMMAND				10247
#define CMD_GUILD_EXIT_YOU					10248	// �� Ż����ߴ�.
#define CMD_GUILD_EXIT_OK					10249	// Ż���Ű�µ� �����ߴ�. 
#define CMD_GUILD_EXIT_WHO					10250	// Ż����� ��� �ֺ� ����鿡�� �ѷ��ش�.

#define CMD_GUILD_JOIN_SERVER				10251	// ��� ���� ���Ѷ� ( db_demon ���� ������. )
#define CMD_GUILD_JOIN_SERVER_OK			10252	// ��� ���� �����ϴ�.
#define CMD_GUILD_JOIN_SERVER_NOT			10253	// ��� ���� �Ұ����ϴ�.

#define CMD_GUILD_JOIN_CONFIRM				10254	// ����ڿ��� Ȯ���� ���� ����.
#define CMD_GUILD_JOIN_CONFIRM_OK			10255	// ����ߴ�.
#define CMD_GUILD_JOIN_CONFIRM_NOT			10256	// �ź��ߴ�.
#define CMD_SCAN_TARGET						10257	// �渶�� ����ϴ� ����Ʈ

#define CMD_GUILD_ALL_MSG					10258	// ��� ��ü �޽���
#define CMD_GUILD_ALL_MSG_RECV				10259	// ��� ��ü �޽��� // ��������
#define CMD_GUILD_EACH_LEVEL				10260	// ��峻 ����� �ٲٴ� ���

#define CMD_GUILD_JOIN_CONFIRM_GUILMA		10261	// ��� ���� Ȯ���� ���´ٴ� ����� �渶���Ե� �����ش�.

#define CMD_GM_REGIST						10262	// GM ����� ��û
#define CMD_GM_REGIST2						10263	// GM�� ����� �ڰ��� �ȵ����� ����� ���
#define CMD_BBS_ALL							10264	// ����Ʈ ��ī ���� ����

#define CMD_COME_OUT_GM_FROM_LOGIN			10265	// GM ��Ͽ� �����ߴ�.
#define CMD_CHANGE_VIEW_JOB					10266	// change_job
#define CMD_REQ_STOP_WAR_TO_LOGIN			10267	// ���� ��û
#define CMD_REQ_STOP_WAR_TO_CLIENT			10268	// ���� ��û�� Ŭ���̾�Ʈ��

#define CMD_REP_STOP_WAR_REFUSAL_TO_LOGIN	10269	// ���� ����
#define CMD_REP_STOP_WAR_REFUSAL_TO_CLIENT	10270	

#define CMD_REP_STOP_WAR_ACCEPT_TO_LOGIN	10271	// ���� �³�
#define CMD_REP_STOP_WAR_ACCEPT_TO_CLIENT	10272	

#define	CMD_SALVATION_MONEY					10275	// ����Ѵ�.
#define CMD_REQ_SALVATION_MONEY				10276	// ���ݱ��� ����Ѱ�..
#define CMD_DB2GAME_SALVATION				10277	// ���Ӽ����� �����ش�.

#define CMD_GM_REGIST_GAMEMAKEMODE			10278

#define CMD_MSG_ALL_SALVATION_TOTAL_MONEY	10279	// ��α� �Ѿװ�, ���� �̸��� ������ �ش�.

// 010210 YGI
#define CMD_CHANGE_MONEY					10280	// ȯ��
#define CMD_CHANGE_MONEY_OK					10281	// ���� �ٲ��.

#define CMD_EAT_CHOCOLATE					10282	// ���ݷ��� �Ծ���.
#define CMD_EAT_CHOCOLATE_OK				10283	// ��� �Ծ���..

#define CMD_PAY_RUMOR						10284
#define CMD_PAY_RUMOR_OK					10285
#define CMD_PAY_RUMOR_NOT					10286
#define CMD_TEAMBATTLE_INFO					10287

#define CMD_OPENSCHOOL_DATA					10288	// ���� �̺�Ʈ�� ���� ���� ����
#define CMD_OPENSCHOOL_DATA_OK				10289
#define CMD_GUILD_EXIT_COMMAND_GLOBAL		10290

#define CMD_GUILD_EXIT_COMMAND_GLOBAL_NOT	10291	// ���� ������ �ƴϴ�.
#define CMD_GUILD_EXIT_COMMAND_GLOBAL_OK	10292

#define CMD_GUILD_EXIT_COMMAND_GLOBAL_LET	10293	// ��� �ʼ������� ���� �� ���� Ż����Ѷ� ����Ѵ�.

#define CMD_EAT_CANDY						10294
#define CMD_EAT_CANDY_OK					10295

#define CMD_UPDATE_LADDER_SCORE				10319
#define CMD_REQ_RANK_LADDER					10320
#define CMD_REP_RANK_LADDER					10321

#define CMD_DIRECT_CLIENT					10322
#define CMD_REP_RANK_LADDER_FINISH			10323

#define CMD_DIRECT_CLIENT_TO_DB				10324		// Ŭ���̾�Ʈ���� �ٷ� ���� ������ ��Ŷ
#define CMD_REQ_SEARCH_RANK_LADDER			10325
#define CMD_REQ_SEARCH_RENK_LADDER_FAIL		10326		// ã�µ� �����ߴ�.		// 010514 YGI

#define CMD_SEND_EFFECT						10327

#define CMD_REQ_VISA						10328
#define CMD_BUY_VISA						10329
#define CMD_BUY_VISA_OK						10330
#define CMD_BUY_VISA_FAIL					10331

#define CMD_NATION_INFO_MAP_TO_MAP			10332		// �� Ÿ���� ������ ù ����Ʈ�� Ÿ���� �־���� �Ѵ�.
#define CMD_SAVE_NATION_INFO				10333		// ���� ����, �����ؾ��� �����


#define CMD_EXIT_GUILD_SELF					10335		// ��� ���̺��� ������

#define CMD_SAVE_GUILD_MARK_IMAGE			10336		// ��� ��ũ ����
#define CMD_REGIST_GUILD_IMSI				10337
#define CMD_REGIST_GUILD_IMSI_OK			10338		// �ӽ� ��� ��Ͽ� �����Ѱ��
#define CMD_REGIST_GUILD_IMSI_OK_ALL		10339		// ��� �ʼ����� �ӽ� ��� ��ϵ� ����� �˷��ش�.
#define CMD_REQ_GUILD_EXPLAIN				10345		// ����� ������ �˾ƺ���.
#define CMD_REGIST_GUILD_MARK				10346
#define CMD_GUILD_NUMBER_INFO_DB_TO_MAP		10347
#define CMD_GUILD_MARK_IMAGE				10348
#define CMD_REGIST_GUILD					10349

#define CMD_GUILD_DEGREE_INFO				10350

#define CMD_REQ_GUILD_IMAGE					10351

#define CMD_SAVE_GUILD_MEMBER_LIST			10354
#define CMD_SEND_MAIL_GUILD					10355
#define CMD_GUILD_MAIL						10356
#define CMD_REQ_RECV_MAIL_TITLE_GUILD		10357
#define CMD_REP_RECV_GUILD_MAIL_TITLE		10358

#define CMD_REQ_RECV_MAIL_BODY_GUILD		10359	// ��� ���� Ȯ��
#define CMD_UPDATE_GUILD_MAIL_ID			10360
#define CMD_RECV_MAIL_DELETE_GUILD			10361

#define CMD_GUILD_MASTER_AND_SUBMASTER		10362
#define CMD_GUILD_MAIL_DELETE_RESULT		10363

#define CMD_PUT_MENU_STRING					10364
#define CMD_REGIST_GUILD_IMSI_FAIL			10365

#define CMD_REGIST_GUILD_CHECK				10366
#define CMD_REGIST_GUILD_CHECK_OK			10367
#define CMD_REGIST_GUILD_CHECK_FAIL			10368

#define CMD_CHECK_SUB_MASTER				10370
#define CMD_CHECK_SUB_MASTER_OK				10371
#define CMD_CHECK_SUB_MASTER_FAIL			10372
#define CMD_REFRESH_GUILD_CODE				10373

#define CMD_CHANGE_GUILD_DEGREE				10378
#define CMD_DELETE_GUILD					10379
#define CMD_DELETE_GUILD_OK					10380
#define CMD_GUILD_DEGREE_INFO2				10381

#define CMD_CHANGE_COLOR					10384

#define CMD_CHECK_SALVATION_NAME			10388
#define CMD_REFRESH_SALVATION_NAME			10389

#define CMD_GET_NAME_GUILD_MEMBER_LIST		10396
#define CMD_GET_GUILD_NOTICE				10397
#define CMD_SEND_GUILD_NOTICE				10398

#define CMD_REGIST_FRIEND					10399
#define CMD_GET_FRIEND						10400
#define CMD_ADD_FRIEND						10401
#define CMD_DELETE_FRIEND					10402

#define CMD_CHECK_GUILD_NAME				10403
#define CMD_THEREIS_NO_CHARANAME			7541
#define CMD_THEREIS_CHARANAME				7542

#define CMD_CHECK_GUILD_OTHER_CHARACTER		10407

#define	CMD_ADD_EVENT_ITEM					10412

#define CMD_GET_GUILD_ITEM_FIRST			10420
#define CMD_GET_GUILD_ITEM					10421
#define CMD_PUT_GUILD_ITEM					10422		// ��� ������ ����
#define CMD_GET_GUILD_ITEM_CLIENT			10423		// ���� ������ ��������
#define CMD_GET_GUILD_ITEM_MAP				10424		// ���� ������ ��������

#define CMD_GET_GUILD_BOX_MONEY				10425	
#define CMD_CHECK_GUILD_BOX_MONEY			10426


#define CMD_ADD_GUILD_BOX_MONEY				10427
#define CMD_GET_GUILD_ITEM_COUNT			10428


#define CMD_CHANGE_GUILD_MASTER				10429
#define CMD_CHANGE_GUILD_MASTER_ALL_MAP		10430

#define CMD_CHANGE_GUILD_MASTER_SUB			10431
#define CMD_REGIST_SUB_GUILD_MASTER			10432

#define CMD_GUILD_HOUSE_INFO				10446
#define CMD_CHANGE_GUILDHOUSE_INFO			10447
#define CMD_BUY_GUILD_HOUSE					10448
#define	CMD_CHECK_GUILD_HOUSE				10449
#define CMD_RELOAD_GUILD_HOUSE				10450		// ���� ����ȭ�� ���߱� ����


#define CMD_SAVE_AMOUNT_EVENT_NPC_ITEM		10467
#define CMD_CHECK_EVENT_MOVE_MAP			10468
#define CMD_SAVE_EVENT_MAPMOVE_NOW			10469

#define CMD_CHECK_EVENT_SCRIPT_ITEM			10610		// �� ������ �ϳ��� �������� ��� ó��
#define CMD_CHECK_RECV_MAIL					10619 // CSD-030227
// 040105 YGI
#define CMD_GET_TREASURE_MAP_DETAIL				10622
#define CMD_GET_TREASURE_MAP_DETAIL_DB			10623
#define CMD_ITEMREPAIR_HAMMER_REQ				10624		// Add by rogerio
#define CMD_ITEMREPAIR_HAMMER_OK				10625		// Add by rogerio

#define CMD_FRIEND_STATUS						10626		// finito 09/08/07 for friend online / offline message status
#define CMD_MANTLE_DYE							10627		// finito 25/06/08 - dye mantle

#define CMD_APPLICATION_OF_EXILE				10632 //Eleval 12/06/09
#define CMD_CHECK_GUILDS						10633 //Eleval 12/06/09
#define CMD_EXILE_OK							10634 //Eleval 12/06/09
#define CMD_EXILE_NOT							10635 //Eleval 12/06/09

#define CMD_SEX_CHANGE							10636 //Eleval 12/06/09 - Sex Change
#define CMD_SEX_CHANGE_OK						10637 //Eleval 12/06/09 - Sex Change

#define CMD_ASK_SQUEST_TELEPORT					10645	//Eleval 10/08/09 - To bring ppl back in quest



// 040105 YGI
struct k_get_treasure_map_detail_to_map
{
	POS pos;
	short int cn;
	short int map_number;
	short int x;
	short int y;
};

struct k_get_treasure_map_detail_to_db
{
	POS pos;			// ������ ��ġ
	short int cn;		// �������� ������ �ִ� ��
};

struct k_check_recv_mail
{	//< CSD-030227
	char count;
	char name[40][20];
};	//> CSD-030227

struct k_save_event_move_map
{
	int event_no;
	short int max;
	short int now;
};

struct k_event_move_map_req		// Ŭ���̾�Ʈ�� ��񿡰� ��û
{
	char sex;			// ���� ���� 0, ���� 1 
	char class_num;		// Ŭ���� ��ȣ ClassType �� ������.
	char nation;		// ���� ��ȣ define�� ������.
};

struct k_event_move_map_rep		// �̺�Ʈ ���� ������ �˷��ش�.
{
	int event_no;
	char map_name[20];
};

struct k_event_script_item
{
	short int event_no;
	short int server_id;
	short int npc_index;
	short int bag_num;
	char id[20];
	char name[20];			// �ش� ĳ���� �̸� --> Ȥ�� �� ���̿� �α� �ƿ� ���� ��� ���
	char	script_no;		// �ش� �̺�Ʈ ��ũ��Ʈ �̺�Ʈ Ŭ���� �����͸� ������ ����
	char	result;			// ���� ���п� ����
};

struct k_event_object
{
	char active;
	char object_toi[30];
	char object_b[30];
};

struct k_event_sound
{
	char active;
	int  sound_no;
};

struct k_event_object_sound
{
	char active;
	char object_toi[30];
	char object_b[30];
	int	 sound_no;
};

struct k_server_connect_info_kein
{
	t_server_connect_info	data1;
	union 
	{
		k_event_object			data2;
		k_event_object_sound	data3;
		k_event_sound			data4;
	}u;
};


struct k_item_log
{
	ItemAttr item;
	char lv;
	char type;
	WORD port;
	char name1[20];
	char name2[20];

};

struct k_check_guild_house
{
	char count;
	char pHouseId[MAX_GUILD_HOUSE];
};

struct k_change_guild_house_info_db2map
{
	char house_id;
	short int guild_code;
	short int year;
	char month;
	char day;
};

struct k_change_guild_house_info
{
	char id;
	char day_type;		// 1: �ű� ��û, 2 : ����
	short int guild_code;
};

struct k_guild_house_info_unit
{
	char id;				// ��ȣ
	char lv;				// ���
	short int guild_code;			// �������
	char time;				// ���� �Ⱓ // ����
	short int red;
	short int blue;
	char map_name[20];		// ��ġ
};

struct k_guild_house_info
{
	char count;
	k_guild_house_info_unit	data[MAX_GUILD_HOUSE/3];
};

struct k_put_menu_string
{
	char type;
	short int str_num;
};

struct k_get_guild_item_db
{
	short int server_id;
	ItemAttr item;
};
struct k_get_guild_item_map		// ���� ������ ��������
{
	short int server_id;
	short int guild_code;
	DWORD index;	
};

struct k_put_guild_item
{
	ItemAttr item;
	short int guild_code;
	char	name[20];
};

struct k_req_guild_item
{
	short int guild_code;
	DWORD index;
};

struct k_get_guild_item
{
	char count;
	DWORD	index[15];
	ItemAttr item[15];
};

struct k_get_guild_item_first
{
	BYTE max;
	DWORD item_index[200];
};
struct k_save_event_item
{
	short int item_no;
	char count;
	char name[20];
};

struct k_delete_friend
{
	char name1[20];
	char name2[20];
};

struct k_add_friend
{
	char login;
	char name[20];
};

struct k_get_friend
{
	char name[30][20];
};

struct k_regist_friend
{
	char nation;
	char name1[20];
	char name2[20];
};

struct k_guild_notice
{
	short int guild_code;
	char msg[1000];
};
struct k_get_guild_member_list_req		// Ŭ���̾�Ʈ���� ��û�Ҷ�
{
	short int guild_code;
	char degree;
};

struct k_get_guild_memeber_list_name
{
	char name[20];
	char is_connect;
};

struct k_get_guild_memeber_list			// ��񿡼� Ŭ���̾�Ʈ�� �����ٶ�..
{
	char degree;
	char count;
	k_get_guild_memeber_list_name name[100];
};

struct k_change_color_db
{
	char type;
	BYTE r, g, b;
	char name[20];
};

// 021008 YGI
struct k_guild_instroduction_basic
{
	short int guild_code;
	char guild_name[20];
};

struct k_check_sub_master
{
	short int guild_code;
	char name[20];
};

struct k_req_guild_master_and_sub_master
{
	short int guild_code;
	char type;
	char name1[20];
	char name2[20];
};

struct k_delete_guild_mail
{
	short int server_id;
	DWORD	mail_id;
	short int guild_code;	
	char	degree;
};
struct k_guild_mail_id
{
	DWORD guild_mail_id;
	char name[20];
};

struct k_save_guild_member_list
{
	short int guild_code;
	short int old_guild_code;
	char degree;
	char name[20];
};

struct k_guild_degree_info
{
	short int guild_code;
	char info_num;
	char guild_degree[5][20];
};

struct k_guild_regist
{
	short int guild_code;
	char sub_name[20];
	char guild_degree[5][20];
};

struct k_guild_change_degree
{
	short int guild_code;
	char guild_degree[5][20];
};


#define IMAGE_UNIT_SIZE			1000
struct k_guild_image
{
	short int guild_code;
	char mark_num;
	char total;
	char sub_count;
	char img[IMAGE_UNIT_SIZE];
};

struct k_regist_guild_mark
{
	short int guild_code;
	char	total;
	DWORD	size;
	char	xl;
	char	yl;
	char	sub_count;
	char	img[IMAGE_UNIT_SIZE];
};

struct k_guild_explain
{
	short int guild_code;
	char explain[1024];
};

struct k_set_guild_info
{
	short int guild_code;
	char  active;
	char make;
	char first;
	char info_num;
	char mark_num;
	char nation;

	char guild_name[20];
	char guild_degree[5][20];
};

struct k_set_guild_number_info
{
	short int guild_code;
	char type;
	char number;
};

struct k_regist_guild_imsi_ok
{
	short int server_id;
	short int guild_code;
};

struct k_char_data_basic2
{
	int lv;
};

struct k_regist_guild_imsi_db
{
	short int server_id;
	char	nation;
	char guild_name[20];
	char guild_ma[20];
	char guild_explain[1024];
};

struct k_regist_guild_imsi
{
	char guild_name[20];
	char guild_explain[1024];
};

struct k_save_nation_info
{
	char	nation;
	double	nation_money;
	int		king_support;

	int		friend_va;
	int		friend_zy;
	int		friend_ill;

	int		nation_item[20];
};

struct k_nation_info_money		// ���� ��ȭ�� 
{
	char	type;
	char	nation;
	DWORD	money;
};

struct k_visa_buy
{
	short int	item_no;
	char		nation;
};

struct k_visa_item
{
	short int item_no[4];
	DWORD	item_price[4];
};

struct k_send_effect
{
	short int effect_num;
	short int target_id;
};

struct k_send_db_direct_map
{
	short int	server_id;
	char		data[MAX_PACKET_SIZE-2];
};

struct k_send_db_direct_client
{
	short int	type;
	char		data[MAX_PACKET_SIZE-2];
};

struct k_direct_client
{
	short int type;
	short int server_id;
	char data[MAX_PACKET_SIZE-4];
};

struct k_req_rank_ladder_to_db
{
	int page;
	short int server_id;
};

struct k_get_ladder_score_rank_unit
{
	int		rank;		// ����
	DWORD	score;
	char	nation;
	char	cls;
	BYTE	btLevel; // CSD-030806
	char	name[20];
};

struct k_db_get_ladder_score_rank
{
	//short int server_id;
	char	is_end;		// ���Ⱑ ������ �ƴ���...
	k_get_ladder_score_rank_unit	unit[10];
};


struct k_update_ladder_score
{
	DWORD	score;
	
	char	nation;
	char	cls;
	BYTE	btLevel; // CSD-030806

	char	name[20];
};

struct k_name2
{
	char name1[20];
	char name2[20];
};

struct k_eat_candy
{
	DWORD total_id;			// �ڱ� �ڽ��� total_id
	DWORD candy_limit;		// ĵ���� ����Ʈ ��ȣ
	char  name[20];			// �ڱ� �̸�
};

struct k_guild_exit_global		// DB���� ����� ��ο��� ������ ������ �Ѵ�.
{
	short int server_id;
	short int guild_code;
	char name[20];
};
struct k_openschool_data_ok
{
	short int npc_id;
	short int server_id;
	char number;
	short int item_no;
};
struct k_openschool_data
{
	short int npc_id;
	short int item_no;
	short int server_id;
	char nation;
	char name[20];
};

struct k_check_chocolate
{
	int count;
	char name[20];
};

struct k_login_check_chocolate
{
	DWORD server_id;
	int count;
	char name[20];
};

struct k_eat_chocolate_ok
{
	DWORD	server_id;
	int		chocolate_count;
};

struct k_eat_chocolate
{
	DWORD server_id;
	DWORD limit;
	char name[20];
};

struct k_send_db2map_each_item
{
	short int server_id;
	short int item_no;
};

struct k_total_salvation_all_msg
{
	char nation;
	DWORD	money;
	double total_money;
	char name[20];
};

typedef struct tag_db_salvation_money		// ��α��� �����϶�..
{
	short int server_id;
	char	nation;
	DWORD	money;	
	char	name[20];
}k_db_salvation_money;

typedef struct tag_db2game_salvation_money		// ��αݰ��� �����ش�.
{
	short int server_id;
	DWORD	money;
}k_db2game_salvation_money;

typedef struct tag_req_salvation_money		// ����ѱݾ��� �����´�.
{
	short int server_id;
	char	name[20];
}k_req_salvation_money;

typedef struct tag_stop_war_all_msg		// �� ���� �����̶�� ����� ��ο��� �˸���.
{
	char	send_nation;
	char	target_nation;
}k_stop_war_all_msg;

typedef struct tag_rep_stop_war_login
{
	short int server_id;
	short int game_id;
}k_rep_stop_war_login;

typedef struct tag_send_client_req_stop_war
{
	char send_nation;		// ������ ��û�� ����
	short int server_id;	// ������ ��û�� �� ���̵�
	short int game_id;		// ������ ��û�� ���� �ִ� ��Ʈ��ȣ
}k_send_client_req_stop_war;

typedef struct tag_send_game_server_req_stop_war
{
	char target_nation;		// ������ ������ ����
	char send_nation;		// ������ ��û�� ����
	short int server_id;	// ������ ��û�� �� ���̵�
	short int game_id;		// ������ ��û�� ���� �ִ� ��Ʈ��ȣ
}k_send_game_server_req_stop_war;

typedef struct tag_send_login_req_stop_war
{
	char target_nation;			// �������� ������û �Ҳ���?
	char send_nation;			// ��� ���� ������?
	short int server_id;		// � ���� ������?
}k_send_login_req_stop_war;

typedef struct tag_send_gm_regist_ok
{
	char gm_index;				// � ������ gm����
	short int gm_rank;			// �������� ���° gm����
	short int total_gm_rank;		// ��Ż gm�� ���° ����
	char	name[20];
}k_send_gm_regist_ok;

typedef struct tag_bbs_ALL
{
	char type;		// ���� ������ ���� �ľ�
	char name[20];
}k_bbs_all;

typedef struct tag_gm_regist_db
{
	char gm_list;
	char name[20];
}k_gm_regist_db;

typedef struct tag_gm_regist
{
	char gm_list_index;
}k_gm_regist;

typedef struct tag_guild_each_level
{
	short int	target_id;
	char		each_level;
}k_guild_each_level;

typedef struct tag_guild_msg
{
	short int guild_code;
	char	  msg[MAX_MSG];
}k_guild_msg;

typedef struct tag_x_y
{
	char x;
	char y;
}k_x_y;


typedef struct tag_scan_target
{
	char	count;
	k_x_y	xy[50];
}k_scan_target;

typedef struct tag_guild_join_ok
{
	short int guild_code;			// ��� �������
	short int target_id;			// ��� ������ �� ��
}k_guild_join_ok;

typedef struct tag_guild_join_result
{
	short int target_id;
	short int server_id;
}k_guild_join_result;

typedef struct tag_guild_join_server
{
	short int target_id;		// ��带 �ٲܳ�
	short int server_id;		// ����� ������ 
	short int guild_code;
	char id[20];
}k_guild_join_server;

typedef struct tag_send_login_nation_msg
{
	char	nation;
	char	msg[200];
}k_send_login_nation_msg;

typedef struct tag_get_skill_info
{
	short int target_id;
	char	job;
	char	call_lv;
}k_get_skill_info;

typedef struct tag_req_vote_score
{
	short int	server_id;
	short int	vote_num;
	char		nation;
}k_req_vote_score;

typedef struct tag_score_and_name
{
	int score;
	char name[20];
}k_score_and_name;

typedef struct tag_rep_vote_score
{
	short int server_id;
	char	max;
	k_score_and_name	name_score[3];
}k_rep_vote_score;

typedef struct tag_client_rep_vote_score
{
	int score[3];
	char	max;
	k_score_and_name	name_score[3];
}k_client_rep_vote_score;

typedef struct tag_set_value_of_vote
{
	char	vote_num[6];
	char	is_voting[6];	
}k_set_value_of_vote;

typedef struct tag_check_vote
{
	short int	server_id;
	short int	vote_num;
	char		nation;
	char		login_id[20]; 
}k_check_vote;

typedef struct tag_is_this_man_candidate
{
	short int server_id;
	short int vote_num;
	char name[20];
}k_is_this_man_candidate;

typedef struct tag_candidate
{
	short int	number;		// ���� ��ȣ

	DWORD		lv : 7;
	DWORD		class_type : 3;
	DWORD		gender : 1;
	DWORD		nation : 4;

	DWORD		guild_code : 9;
	DWORD		face : 7;

	char		name[20];
}k_candidate;

typedef struct tag_regist_candidate
{
	short int	server_id;
	k_candidate	candidate;
}k_regist_candidate;

typedef struct tag_check_vote_ok
{
	short int server_id;
	char candidate_count;
	k_candidate candidate[3];
}k_check_vote_ok;		// �ĺ� ����

typedef struct tag_check_vote_client_ok
{
	char candidate_count;
	k_candidate candidate[3];
}k_check_vote_client_ok;

typedef struct tag_vote_game2login
{
	short int	server_id;
	short int	vote;
	char		support;
	char		nation;
	char	login_id[20];
}k_vote_game2login;

typedef struct tag_exist_name_nation	// ���� �����⿡ ������ �̸����� Ȯ��
{
	char nation;
	short int server_id;
	char name[20];
}k_exist_name_and_nation;

typedef struct tag_exist_name		// ���� �����⿡ ������ �̸����� Ȯ��
{
	short int server_id;
	char name[20];
}k_exist_name;

typedef struct tag_change_dur
{
	POS			pos;
	DWORD		dur;
}k_change_dur;

typedef struct tag_script_change
{
	short int	script_num;
	int			value;
}k_script_change;

typedef struct tag_reset_job
{
	char	job;
	char	cls;
	char	name[20];
}k_reset_job;

typedef struct tag_team_add_message
{
	char		team_num;
	short int	id;
	char		name[20];
}k_team_add_message;

typedef struct tag_team_battle_msg
{
	char		team_num;
	char		ret;
	char		data;
}k_team_battle_msg;

typedef struct tag_quest_unit
{
	short int index;
	short int ret;
}k_quest_unit;

typedef struct tag_rep_quest_index
{
	char			max;
	k_quest_unit	quest[14];
}k_rep_quest_index;

typedef struct tag_req_man_to_man_result
{
	short int	id;
	char		ret;
}k_req_man_to_man_result;

typedef struct tag_req_man_to_man
{
//	char		name[20];		// ��û�� ĳ���� �̸�
	short int	id;				// ��û�� ĳ������ ���̵�
}k_req_man_to_man;

typedef struct tag_do_party_ok
{
	char name[20];
	short int type;
}k_do_party_ok;

typedef struct t_danger_of_hunter
{
	short int	target_id;
	char		type;		// 1: �þ߾����� ���Դ�.  0: �������.
}k_danger_of_hunter;

typedef struct t_kill_who
{
	char name[20];
}k_kill_who;

//////////////////////////////////////////////////////////////
// ������� ��� ����...
typedef struct t_kill_hunter_ok		// CMD_KILL_HUNTER_LIST_OK
{
	DWORD	money;
}k_kill_hunter_ok;

typedef struct t_kill_who_whom
{
	char hunter_name[20];		// ���λ��
	char target_name[20];		// ���� ���
}k_kill_who_whom;

typedef struct t_kill_who_whom_login
{
	char hunter_name[20];		// ���λ��
	char target_name[20];		// ���� ���
	char regist_name[20];		// �Ƿ��� ���
}k_kill_who_whom_login;

typedef struct t_send_kill_hunter_list
{
//	char target_name[20];
//	char regist_name[20];
	DWORD	money;
	int server_id;
}k_send_kill_hunter_list;

typedef struct t_kill_hunter_list_login
{
	short int server_id;
	int	list_id;
	char hunter_name[20];		// ��ɲ��� �̸�	
}k_kill_hunter_list_login;

///////////////////////////////////////////////////////////////////
// ����� ����Ʈ �����ֱ� ���� ����ü
typedef struct t_get_hunter_list
{
	int list_id;
}k_get_hunter_list;


typedef struct t_hunter_list		// ���ӿ��� Ŭ���̾�Ʈ��
{
	int	 index;
	char target_name[20];
	char regist_name[20];
	DWORD	money;
	char gender;
	short int face;
	char text[1000];
}k_hunter_list;

typedef struct t_login_game_hunter_list		// ��񵥸󿡼� �������� 
{
	short int		server_id;
	k_hunter_list	list;
}k_login_game_hunter_list;

typedef struct t_game_login_hunter_list		// ���ӿ��� �α������� ��û
{
	short int	server_id;
	int			list_id;
}k_game_login_hunter_list;
////////////////////////////////////////////////////////////////////

typedef struct t_hunter_regist
{
	char name[20];
	DWORD money;
	char text[1000];
}k_hunter_regist;

typedef struct t_hunter_regist2
{
	char regist_name[20];
	char target_name[20];
	DWORD money;
	char text[1000];
}k_hunter_regist2;

typedef struct t_server_learn_item
{
	short int item_count;
	short int item[MAX_LEARN_ITEM];
}k_server_learn_item;

typedef struct t_server_id
{
	short int server_id;
}k_server_id;

typedef struct t_start_game_mail
{
	short int server_id;
	short int guild_code;
	char name[20];
}k_start_game_mail;

typedef struct t_req_party_info
{
	char party_name[20];
}k_req_party_info;

typedef struct t_rep_party_info
{
	char party_name[20];
	int			x;
	int			y;
	short int	hp;
}k_rep_party_info;

typedef struct t_oh_my_party
{
	char	my_name[20];		// ���� ���³�
	char	party_name[20];		// ���� ��Ƽ ���� ���
}k_oh_my_party;

typedef struct t_server_req_char_info
{
	short int	id;
//	char		lv;
	int			Hp;
	int			HpMax;
}k_server_req_char_info;

typedef struct tag_note_meeting
{
	char believe_god;
	char meeting_type;
}k_note_meeting;

typedef struct tag_i_get_item_of_supper
{
	short int item_no;
}k_i_get_item_of_supper;

typedef struct tag_server_to_client_open_supper
{
	char much;		// ���� �� �ִ� ���� ����
}k_server_to_client_open_supper;

typedef struct tag_req_faith_up
{
	char name[20];				// �žӽ� �÷��� ���
	short int up_point;			// �žӽ� �÷��� ��
}k_req_faith_up;

typedef struct tag_game2login_recall_box_item
{
	DWORD box_id;
	short int server_id;		// �ڱ� �ڽŰ� ������� ����
}k_game2login_recall_box_item;

typedef struct tag_char_update_data
{
	char		believe_god;
	short int	faith;
	short int	god_cast_level;
	char		name[20];
}k_char_update_data;

///////////////////////////////////////////////////////////
typedef struct tag_change_map9
{
	short int						game_port;
	char							name[20];

	short int						Gender;
	short int						Face;
	short int						Class;
	short int						Job;
	short int						Spell;
	char							GuildName[21];
	short int						SprNo;
	unsigned char					Peacests;
	short int						BodyR;
	short int						BodyG;
	short int						BodyB;
	short int						ClothR;
	short int						ClothG;
	short int						ClothB;

	DWORD							total_id;

	short int						nk3,nk4,nk6;


}k_change_map9;

typedef struct tag_change_map8
{
	short int						game_port;
	k_char_update_data				ch_data;
}k_change_map8;

typedef struct tag_change_map7
{
	short int						game_port;
	t_server_update_bankitem_data	ch_data;
}k_change_map7;

typedef struct tag_change_map6
{
	short int						game_port;
	t_server_update_item_data		ch_data;
}k_change_map6;

typedef struct tag_change_map5
{
	short int						game_port;
	t_server_update_inv_data		ch_data;
}k_change_map5;

typedef struct tag_change_map4
{
	short int						game_port;
	t_server_update_binary_data1	ch_data;
}k_change_map4;

typedef struct tag_change_map3
{
	short int						game_port;
	t_server_update_script_data		ch_data;
}k_change_map3;

typedef struct tag_change_map2
{
	short int						game_port;
	t_server_update_binary_data0	ch_data;
}k_change_map2;
typedef struct tag_change_map1
{
	short int			game_port;
	t_update_char_db	ch_data;
}k_change_map1;
///////////////////////////////////////////////////////////////////////////////

typedef struct tag_send_game_port
{
	short int game_port;
}k_send_game_port;

typedef struct tag_who_send_mail
{
	char name[20];
}k_who_send_mail;

typedef struct tag_game_to_client_rep_recv_mail_body
{
	DWORD mail_id;
	char body[1000];
}k_game_to_client_rep_recv_mail_body;

typedef struct tag_login_to_game_rep_recv_mail_body
{
	short int server_id;
	DWORD mail_id;
	char body[1000];
}k_login_to_game_rep_recv_mail_body;

typedef struct tag_game_to_login_req_recv_mail_body
{
	short int server_id;
	DWORD mail_id;
}k_game_to_login_req_recv_mail_body;

typedef struct tag_req_recv_mail_body
{
	DWORD mail_id;
}k_req_recv_mail_body;

struct k_login_to_game_guild_mail_title
{
	short int	server_id;
	DWORD		mail_id;
	char		degree;
	short int	mail_year;
	char		mail_month;
	char		mail_day;
	char		mail_name[20];
	char		mail_title[60];
};

typedef struct tag_login_to_game_mail_title
{
	short int	server_id;
	DWORD		mail_id;
	short int	mail_year;
	char		mail_month;
	char		mail_day;
	char		mail_name[20];
	char		mail_title[60];
}k_login_to_game_mail_title;

typedef struct tag_req_mail_body
{
	DWORD mail_id;
}k_req_mail_body;

typedef struct tag_mail
{
	DWORD		mail_id;
	short int	year;
	char		month;
	char		day;
	char		send_name[20];
	char		mail_title[60];
	char		mail_body[1000];
}MAIL;

struct k_guild_mail
{
	DWORD		mail_id;
	char		degree;
	short int	year;
	char		month;
	char		day;
	char		send_name[20];
	char		mail_title[60];
	char		mail_body[1000];
};

struct k_guild_mail_unit
{
	short int guild_code;
	char	degree;
};

typedef struct tag_game_to_login_send_mail
{
	char send_name[20];
	union
	{
		char recv_name[20];
		k_guild_mail_unit guild_info;
	}uni;
	char title[60];
	char body[1000];
}k_game_to_login_send_mail;


typedef struct tag_send_mail
{
	char name[20];
	char title[60];
	char body[1000];
}k_send_mail;

typedef struct tag_moving_item
{
	char		name[20];
	char		source_type;
	char		dest_type;
	ItemAttr	item;
	DWORD		money;
}k_moving_item;

typedef struct tag_game2client_ear_result
{
	char ret;
}k_game2client_ear_result;

typedef struct tag_login2game_ear_message_result
{
	short int send_server_id;
	char	ret;									// ret  1 : ok, 2:����, 3:������
}k_login2game_ear_message_result;

typedef struct tag_send_ear_message_result
{
	short int send_game_server;
	short int send_server_id;
	char	ret;									// ret  1 : ok, 2:����, 3:������
}k_send_ear_message_result;

typedef struct tag_loginserver_to_gameserver_ear_message
{
	short int server_id;
	char name[20];
}k_loginserver_to_gameserver_ear_message;

typedef struct tag_send_ear_message_ok_to_login
{
	short int gameserver_port;
	short int server_id;
	char name[20];
	char ret;				// ���
}k_send_ear_message_ok_to_login;

typedef struct tag_login_to_gameserver_ear_message
{
	short int game_server;		// ��������� ���� ���� ����
	short int server_id;		// ��������� ���̵� 
	char nation;				// ���� ���ϱ� ����
	char recv_name[20];				// �������� ������ ��
	char send_name[20];				// ���� �����ǰ�...
	char message[200];			// � �޽��� �ΰ�...
}k_login_to_gameserver_ear_message;

typedef struct tag_login_send_ear_message
{
	short int server_id;
	char nation;			// ���� ���ϱ� ����
	char recv_name[20];		// �޴� ����̸�
	char send_name[20];		// ������ ��� �̸�
	char message[200];
}k_login_send_ear_message;

typedef struct tag_send_ear_message_ok
{
	char name[20];
}k_send_ear_message_ok;

typedef struct tag_send_ear_message
{
	char name[20];
	short int send_game_server;		// ���� ����� ���� ���� ���� ��Ʈ��ȣ
	short int send_server_id;		// ���� ����� ���̵�
	char message[200];
}k_send_ear_message;

typedef struct server_to_client_char_info_plus		// �߰� ĳ���� ������ Ŭ���̾�Ʈ�� �����ش�.
{
	char		believe_god;
	short int	faith;
}k_server_to_client_char_info_plus;


typedef struct server_killpc
{
	short   id;
	DWORD	killpc;
}k_server_killpc;


typedef struct tag_req_chr_info_etc
{
	short int	server_id;
	char		name[20];
}k_req_chr_info_etc;

typedef struct tag_get_char_info	// loginserver -> gameserver
{
	char		name[20];		// 030923 HK YGI
	short int	server_id;
	char		believe_god;
	short int	faith;
	short int	god_cast_level;
}k_get_char_info;

typedef struct tag_server_text_default
{
	char text[512];
	unsigned short int len;			// �� ����
}k_server_text_default;

typedef struct tag_server_text_only_one
{
	char text[512];
	unsigned short int len;			// �� ����
	short int server_id;
}k_server_text_only_one;

typedef struct tag_get_god_table
{
	char				god_idex;
	TIMESTAMP_STRUCT	day;
	TIMESTAMP_STRUCT 	month;
	TIMESTAMP_STRUCT 	year;
}k_get_god_table;

typedef struct tag_check_new_char
{
	char name[20];
}k_check_new_char;

typedef struct tool_password
{
	char password[11];
}k_tool_password;

typedef struct login_sql_evangelist_create
{
	char my_name[20];
	char eva_name[20];
}k_login_sql_evangelist_create;

typedef struct login_sql_evangelist_delete
{
	char my_name[20];
}k_login_sql_evangelist_delete;

typedef struct server_client_preach_name		// ���
{
	char	result;
	char	name[20];
	BYTE	believe_god;
}k_server_client_preach_name;

typedef struct loginserver_result
{
	BYTE type;
	BYTE result;
	short int server_id;
}k_loginserver_result;

typedef struct loginserver_preach_name
{
	short int	server_id;
	char		name[20];
	BYTE		believe_god;
}k_loginserver_preach_name;

typedef struct loginserver_preach_name_result
{
	short int		server_id;
	char			result;
	char			name[20];
	BYTE			believe_god;
}k_loginserver_preach_name_result;

typedef struct client_god_regist_ok
{
	char type;
}k_client_god_regist_ok;

typedef struct server_preach_name
{
	char	name[20];
	BYTE	believe_god;
}k_server_preach_name;

typedef struct login_put_box_item
{
	//	short int server_id;		// Ŭ���̾�Ʈ�� ������ �ʿ䰡 ���� ������
	DWORD		box_id;
	char		para;				//��ġ
	ItemAttr	item;
}k_login_put_box_item;

typedef struct get_server_text
{
	char text[512];		
	char ct;						// Ŭ������ �迭
	unsigned short int len;			// �ѱ���
}k_get_server_text;

typedef struct req_bbs_title
{
	char count;
}k_req_bbs_title;

typedef struct transfer_item		// ������ ���� ����Ʈ
{
	ItemAttr item;
}k_transfer_item;

typedef struct client_throw_dice
{
	char type;
}k_client_throw_dice;

typedef struct start_create_ability
{
	unsigned int str	: 2;
	unsigned int dex	: 2;
	unsigned int con	: 2;
	unsigned int wis	: 2;

	unsigned int inte	: 2;
	unsigned int cha	: 2;
	unsigned int movp	: 2;
	unsigned int endu	: 2;

	unsigned int mor	: 2;
	unsigned int wsps	: 2;
	unsigned int luck	: 2;
}k_start_create_ability;

typedef struct start_throw_dice		// �ֻ��� ���� ��� 0~10 ������ ���ϱ� ��ġ
{
	char ability1;
	char ability2;
	/*
	DWORD str	: 2;
	DWORD dex	: 2;
	DWORD con	: 2;
	DWORD wis	: 2;

	DWORD inte	: 2;
	DWORD cha	: 2;
	DWORD movp	: 2;
	DWORD endu	: 2;

	DWORD mor   : 2;
	DWORD wsps	: 2;
	DWORD luck  : 2;
	*/
}k_start_throw_dice;

typedef struct server_tactics
{
	DWORD	magery;
}k_server_tactics;

typedef struct cmd_party_no_name
{
	short int server_id;
	char name[31];
}k_cmd_party_no_name;

typedef struct rep_party_together
{
	short int server_id;
	char party_name[31];
}k_rep_party_together;

typedef struct server_req_party_together
{
	char		party_name[31];
	char		my_name[31];
	short int	server_id;
}k_server_req_party_together;

typedef struct server_req_party_db
{
	short int	server_id;
	char		name[31];
	char		ct;
}k_server_req_party_db;

typedef struct server_server_party_info
{
	short int	Server_id;		// �̶� ����ϴ� ���� ���̵�� ��û�� Ŭ���̾�Ʈ�� ���̵� �̴�...
	char		ct;				// ��Ƽ ��ȣ

	short int	Face;
	short int	Level;
	short int	Str;
	char 		Gender;
	char		Class;
}k_server_server_party_info;

typedef struct server_killmon
{
	DWORD	killmon;
}k_server_killmon;

typedef struct server_ac
{
	short int ac;
}k_server_ac;

typedef struct server_item_attr
{
	POS		pos;
	DWORD	attr;
}k_server_item_attr;

typedef struct beta_check_id
{
	char			id[ID_LENGTH];
}k_beta_check_id;

typedef struct tag_exchange_item_del
{
	POS			pos;
	short int	you_id;
}k_exchange_item_del;

typedef struct tag_try_item_trade
{
	char result;
}k_try_item_trade;

typedef struct tag_server_money
{
	DWORD money;
}k_server_money;

/*
typedef struct tac_skill_each_exp
{
	unsigned int tac_exp;
}t_tac_skill_each_exp;
*/
typedef struct tag_client_inn
{
	char type;			// ����->3, ���ڱ�->3( ��, ������ ���� )
}k_client_inn;

typedef struct tag_party_info
{
	short int	type;
	char		index;
	char		m_Name[20];
	char		m_Gender;
	short int	m_ImageNo;
	short int	m_Str;
	BYTE		m_btLevel; // CSD-030806	
	char		m_Class;
	char		m_Join;
}k_party_info;
		

typedef struct tag_server_item_money
{
	int item_no;
	int money;
}k_server_item_money;

typedef struct tag_client_item_no
{
	int item_no;
}k_client_item_no;

typedef struct tag_client_disease
{
	short int disease_num;
}k_client_disease;

typedef struct tag_learn_magic_ok
{
	short int magic_num;
}k_learn_magic_ok;

typedef struct tag_client_char_name
{
	char	name[20];
}k_client_char_name;

typedef struct tag_client_learn_magic
{
	short int num;
}k_client_learn_magic;

typedef struct tag_client_delete_party
{
	short int	type;
	char		ct;
}k_client_delete_party;

typedef struct tag_client_do_party
{
	short int	type;
	char		ct;
	char		name[31];
}k_client_do_party;

typedef struct tag_server_bank_item
{
	char	first;
	char	second;
	ItemAttr inv[6];
}k_server_bank_item;

typedef struct tag_server_item_index
{
	short int item[1000];
	short int itemmax;
}k_server_item_index;

typedef struct tag_server_relation
{
	char		name[3][31];
	char		Gender[3];
	char		Level[3];
	short int	Face[3];
	char		Str[3];
	char		Class[3];
}k_server_relation;

typedef struct tag_server_party		// employment�Ͱ��� ����.
{
	char		name[6][31];
	char		Gender[6];
	char		Level[6];
	short int	Face[6];
	int			Str[6];
	char		Class[6];
}k_server_party;

typedef struct tag_server_disease
{
	char disease[6];
}k_server_disease;

typedef struct client_char_info_plus
{
	BYTE	type;
}k_client_char_info_plus;

typedef struct server_status_open
{
	DWORD	killmon;
	short int	ac;
	short int	mov;
}k_server_status_open;

typedef struct server_skill_exp
{
	BYTE	type;
	DWORD   exp;
}k_server_skill_exp;

typedef struct server_learn_skill_ok
{
	short int skill_no;
}k_server_learn_skill_ok;

typedef struct server_result
{
	BYTE	type;
	BYTE	result;
}k_server_result;

typedef struct server_item_repair_ok
{
	short int	item_pos;		// ��ĥ ��ġ ( << 5 | <<3  | ... ��� )
	short int	money;
	DWORD		dur;
}k_server_item_repair_ok;


typedef struct tag_item_no
{
	short int item_no;
}k_item_no;

typedef struct tag_client_learn_item
{
	short int item_no;
	short int join_no;
}k_client_learn_item;

typedef struct client_lvup_point_each
{
	unsigned char type;
}k_client_lvup_point_each;

typedef struct client_other_ch_inv
{
	short int other_ch;					// �������� ����� ���̵�
}kein_client_other_ch_inv;

typedef struct server_other_ch_inv
{
	int target_id;
	int item[15];						// ������ ����� ������ ���
}kein_server_other_ch_inv;

typedef struct client_item_attr_pos		// ������ �Ӽ��� ��ġ
{
	ItemAttr		item_attr;
	POS				item_pos;
	int				much;
}kein_item_attr_pos;

typedef struct client_bank_deposit
{
	DWORD			money;		// �� ������ �ݾ�
} k_client_bank_deposit;

typedef struct client_bank_repayment		
{
	DWORD			loan_money;
	DWORD			last_loan;
	DWORD			last_loan_time;
} k_client_bank_repayment;


typedef struct client_create_item
{
	int type;
	int num;
	DWORD dur;
	int   gennum;
} k_client_create_item;

#ifndef _K_ITEM
typedef struct tag_K_ITEM
{
	ItemAttr	item_attr;
	POS			item_pos;
}K_ITEM, *lpITEM;
#define _K_ITEM
#endif


typedef struct req_login_server_box_open
{
	short int	server_id;
	DWORD		box_id;
}k_req_login_server_box_open;

typedef struct login_server_box_open
{
	short int	server_id;		// Ŭ���̾�Ʈ ���̵�
	ItemAttr	box_item[MAX_BOX_ITEM];
	DWORD		box_id;
}k_login_server_box_open;

typedef struct server_box_open
{
	ItemAttr	box_item[MAX_BOX_ITEM];
}k_server_box_open;

typedef struct server_delete_item
{
	POS				item_pos;
}k_server_delete_item;

typedef struct server_decrease_item
{
	POS				item_pos;
	DWORD			dur;
}k_server_decrease_item;

typedef struct tag_exchange_item_start
{
	K_ITEM		item;
	short int	you_id;
}k_exchange_item_start;





typedef union kein_imsi
{
	char					data[MAX_PACKET_SIZE];

	k_server_result					server_result;

	kein_server_other_ch_inv		server_other_ch_inv;
	kein_client_other_ch_inv		client_other_ch_inv;
	kein_item_attr_pos				item_attr_pos;

	k_client_bank_deposit			client_bank_deposit;
	k_client_bank_repayment			client_bank_repayment;
	k_client_create_item			client_create_item;
	K_ITEM							box_item;
	k_server_box_open				server_box_open;
	k_server_delete_item			server_delete_item;
	k_server_decrease_item			server_decrease_item;
	
	k_client_lvup_point_each		client_lvup_point_each;
	k_client_learn_item				client_learn_item;
	k_item_no						item_no;

	k_server_item_repair_ok			server_item_repair_ok;	
	k_server_learn_skill_ok			server_learn_skill_ok;
	k_server_skill_exp				server_skill_exp;

	k_server_status_open			server_status_open;
	k_client_char_info_plus			client_char_info_plus;
	k_server_party					server_party;
	k_server_relation				server_relation;
	k_server_item_index				server_item_index;
	k_server_disease				server_disease;

	k_server_bank_item				server_bank_item;	
	k_client_do_party				client_do_party;

	k_client_delete_party			client_delete_party;

	k_client_learn_magic			client_learn_magic;

	k_client_char_name				client_char_name;
	k_learn_magic_ok				learn_magic_ok;

	k_client_disease				client_disease;

	k_client_item_no				client_item_no;
	k_server_item_money				server_item_money;

	k_party_info					party_info;
	k_client_inn					client_inn;
//	t_tac_skill_each_exp			tac_skill_each_exp;

	k_server_killpc					server_killpc;
	K_ITEM							server_item;

	k_server_money					server_money;

	K_ITEM							item;
	
	k_exchange_item_start			exchange_item_start;
	k_try_item_trade				try_item_trade;

	k_exchange_item_del				exchange_item_del;

	k_beta_check_id					beta_check_id;
	k_server_item_attr				server_item_attr;

	k_server_ac						server_ac;
	k_server_killmon				server_killmon;
	k_server_server_party_info		server_server_party_info;

	k_server_req_party_db			server_req_party_db;

	k_server_req_party_together		server_req_party_together;
	k_rep_party_together			rep_party_together;
	k_cmd_party_no_name				cmd_party_no_name;

	k_server_tactics							server_tactics;

	k_start_create_ability						start_create_ability;
	k_start_throw_dice							start_throw_dice;
	k_client_throw_dice							client_throw_dice;
	k_transfer_item								transfer_item;
	
	k_req_bbs_title								req_bbs_title;
	
	k_get_server_text							get_server_text;
	k_login_server_box_open						login_server_box_open;

	k_req_login_server_box_open					req_login_server_box_open;
	k_login_put_box_item						login_put_box_item;

	k_server_preach_name						server_preach_name;
	k_client_god_regist_ok						client_god_regist_ok;

	k_loginserver_preach_name					loginserver_preach_name;
	k_loginserver_result						loginserver_result;

	k_server_client_preach_name					server_client_preach_name;
	k_tool_password								tool_password;

	k_check_new_char							check_new_char;

	k_loginserver_preach_name_result			loginserver_preach_name_result;
	
	k_login_sql_evangelist_create				login_sql_evangelist_create;
	k_login_sql_evangelist_delete				login_sql_evangelist_delete;

	k_get_god_table								get_god_table;

	k_server_text_default						server_text_default;

	k_char_update_data							char_update_data;
	k_get_char_info								get_char_info;
	k_req_chr_info_etc							req_chr_info_etc;
	
	k_server_to_client_char_info_plus			server_to_client_char_info_plus;
	k_send_ear_message							send_ear_message;
	k_send_ear_message_ok						send_ear_message_ok;
	k_login_send_ear_message					login_send_ear_message;

	k_login_to_gameserver_ear_message			login_to_gameserver_ear_message;
	k_send_ear_message_ok_to_login				send_ear_message_ok_to_login;
	k_loginserver_to_gameserver_ear_message		loginserver_to_gameserver_ear_message;
	k_send_ear_message_result					send_ear_message_result;

	k_login2game_ear_message_result				login2game_ear_message_result;
	k_game2client_ear_result					game2client_ear_result;

	k_moving_item								moving_item;
	k_send_mail									send_mail;
	k_game_to_login_send_mail					game_to_login_send_mail;
	k_req_mail_body								req_mail_body;

	k_login_to_game_mail_title					login_to_game_mail_title;
	MAIL										mail;

	k_req_recv_mail_body						req_recv_mail_body;
	k_game_to_login_req_recv_mail_body			game_to_login_req_recv_mail_body;
	k_login_to_game_rep_recv_mail_body			login_to_game_rep_recv_mail_body;
	k_game_to_client_rep_recv_mail_body			game_to_client_rep_recv_mail_body;

	k_who_send_mail								who_send_mail;
	
	k_send_game_port							send_game_port;
	k_change_map1								change_map1;
	k_change_map2								change_map2;
	k_change_map3								change_map3;
	k_change_map4								change_map4;
	k_change_map5								change_map5;
	k_change_map6								change_map6;
	k_change_map7								change_map7;
	k_change_map8								change_map8;
	k_change_map9								change_map9;

	k_game2login_recall_box_item				game2login_recall_box_item;

	k_req_faith_up								req_faith_up;
	k_server_to_client_open_supper				server_to_client_open_supper;
	k_i_get_item_of_supper						i_get_item_of_supper;

	k_note_meeting								note_meeting;

	k_server_req_char_info						server_req_char_info;
	k_oh_my_party								oh_my_party;

	k_req_party_info							req_party_info;
	k_rep_party_info							rep_party_info;

	k_start_game_mail							start_game_mail;
	k_server_id									server_id;

	k_server_learn_item							server_learn_item;
	k_hunter_regist								hunter_regist;
	k_hunter_regist2							hunter_regist2;
	k_hunter_list								hunter_list;

	k_server_text_only_one						server_text_only_one;
	k_login_game_hunter_list					login_game_hunter_list;
	k_game_login_hunter_list					game_login_hunter_list;

	k_get_hunter_list							get_hunter_list;
	

	k_kill_hunter_list_login					kill_hunter_list_login;
	k_send_kill_hunter_list						send_kill_hunter_list;
	k_kill_who									kill_who;
	k_kill_hunter_ok							kill_hunter_ok;
	k_kill_who_whom								kill_who_whom;

	k_kill_who_whom_login						kill_who_whom_login;
	k_danger_of_hunter							danger_of_hunter;

	char										default_char;
	short int									default_short_int;
	int											default_int;
	DWORD										default_dword;
	ItemAttr									default_item;
	char										default_name[20];
	char										default_msg[MAX_MSG];


	k_do_party_ok								do_party_ok;

	k_req_man_to_man							req_man_to_man;
	k_req_man_to_man_result						req_man_to_man_result;
	k_rep_quest_index							rep_quest_index;

	k_team_battle_msg							team_battle_msg;
	k_team_add_message							team_add_message;
	k_reset_job									reset_job;

	k_script_change								script_change;
	k_change_dur								change_dur;
	k_exist_name								exist_name;

	k_exist_name_and_nation						exist_name_and_nation;
	k_vote_game2login							vote_game2login;

	k_regist_candidate							regist_candidate;
	k_is_this_man_candidate						is_this_man_candidate;
	k_check_vote								check_vote;
	k_check_vote_ok								check_vote_ok;
	k_check_vote_client_ok						check_vote_client_ok;

	k_set_value_of_vote							set_value_of_vote;

	k_req_vote_score							req_vote_score;
	k_rep_vote_score							rep_vote_score;
	k_client_rep_vote_score						client_rep_vote_score;

	k_get_skill_info							get_skill_info;
	k_send_login_nation_msg						send_login_nation_msg;

	k_guild_join_server							guild_join_server;
	k_guild_join_result							guild_join_result;

	k_guild_join_ok								guild_join_ok;
	k_scan_target								scan_target;

	k_guild_msg									guild_msg;
	k_guild_each_level							guild_each_level;

	k_gm_regist									gm_regist;
	k_gm_regist_db								gm_regist_db;
	k_bbs_all									bbs_all;

	k_send_gm_regist_ok							send_gm_regist_ok;

	k_send_login_req_stop_war					send_login_req_stop_war;
	k_send_client_req_stop_war					send_client_req_stop_war;

	k_send_game_server_req_stop_war				send_game_server_req_stop_war;
	k_rep_stop_war_login						rep_stop_war_login;

	k_db_salvation_money						db_salvation_money;
	k_db2game_salvation_money					db2game_salvation_money;
	k_req_salvation_money						req_salvation_money;

	k_total_salvation_all_msg					total_salvation_all_msg;

	k_send_db2map_each_item						send_db2map_each_item;
	k_eat_chocolate								eat_chocolate;
	k_eat_chocolate_ok							eat_chocolate_ok;

	k_login_check_chocolate						login_check_chocolate;
	k_check_chocolate							check_chocolate;

	k_openschool_data							openschool_data;
	k_openschool_data_ok						openschool_data_ok;

	k_guild_exit_global							guild_exit_global;

	k_eat_candy									eat_candy;
	k_name2										name2;
	k_update_ladder_score						update_ladder_score;
	k_db_get_ladder_score_rank					db_get_ladder_score_rank;

	k_req_rank_ladder_to_db						req_rank_ladder_to_db;
	k_direct_client								direct_client;
	
	k_send_db_direct_client						send_db_direct_client;
	k_send_db_direct_map						send_db_direct_map;

	k_save_nation_info							save_nation_info;

	k_regist_guild_imsi							regist_guild_imsi;
	k_regist_guild_imsi_db						regist_guild_imsi_db;
	k_regist_guild_imsi_ok						regist_guild_imsi_ok;
	k_set_guild_info							set_guild_info;
	k_guild_explain								guild_explain;

	k_regist_guild_mark							regist_guild_mark;
	k_set_guild_number_info						set_guild_number_info;

	k_guild_image								guild_image;
	k_guild_regist								guild_regist;
	k_guild_degree_info							guild_degree_info;

	k_save_guild_member_list					save_guild_member_list;

	k_guild_mail_id								guild_mail_id;
	k_login_to_game_guild_mail_title			login_to_game_guild_mail_title;
	k_delete_guild_mail							delete_guild_mail;

	k_req_guild_master_and_sub_master			req_guild_master_and_sub_master;
	k_change_color_db							change_color_db;
	k_get_guild_memeber_list					get_guild_memeber_list;
	k_get_guild_member_list_req					get_guild_member_list_req;
	k_guild_notice								guild_notice;
	k_get_friend								get_friend;
	k_save_event_item							save_event_item;

	k_get_guild_item_first						get_guild_item_first;
	k_get_guild_item							get_guild_item;
	k_req_guild_item							req_guild_item;
	k_put_guild_item							put_guild_item;
	k_get_guild_item_map						get_guild_item_map;
	k_get_guild_item_db							get_guild_item_db;
	k_guild_change_degree						guild_change_degree;
	k_guild_house_info							guild_house_info;
	k_change_guild_house_info_db2map			change_guild_house_info_db2map;
	k_check_guild_house							check_guild_house;
	k_guild_instroduction_basic					guild_instroduction_basic;
	k_server_connect_info_kein					server_connect_info_kein;
	k_event_object_sound						event_object_sound;
	k_event_sound								event_sound;
	k_save_event_move_map						save_event_move_map;
	k_check_recv_mail							check_recv_mail; // CSD-030227
	// 040105 YGI
	k_get_treasure_map_detail_to_map			get_treasure_map_detail_to_map;
	k_get_treasure_map_detail_to_db				get_treasure_map_detail_to_db;
} t_kein;


