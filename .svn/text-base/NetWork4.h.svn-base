#ifndef NW_PACKET_DEFINE_
#define NW_PACKET_DEFINE_
/*****************************************************************************/
/* 국가전 관련 패킷 
/* // 010725 LTS
/*****************************************************************************/

// 추후 분류 및 추가

#define		CMD_REQUEST_CHECK_VOTE					26001
#define		CMD_ANSWER_CHECK_VOTE					26002
#define		CMD_WARFIELD_STATUS						26003
#define		CMD_WAR_BBS								26004
#define		CMD_REQUEST_WARFIELD_STATUS				26005
#define		CMD_ANSWER_WARFIELD_STATUS				26006
#define		CMD_REQUEST_VOTE_DATA					26007
#define		CMD_ANSWER_VOTE_DATA					26008
#define		CMD_VOTING_DATA							26009
#define		CMD_REQUEST_VOTE_RESULT					26010
#define		CMD_ANSWER_VOTE_RESULT					26011
#define		CMD_REQUEST_SQUAD_INFO					26012
#define		CMD_ANSWER_SQUAD_INFO					26013
#define		CMD_REQUEST_COMMANDER_VOTE_DATA			26014
#define		CMD_ANSWER_COMMANDER_VOTE_DATA			26015
#define		CMD_REQUEST_COMMANDER_VOTING_RESULT		26016
#define		CMD_ANSWER_COMMANDER_VOTING_RESULT		26017
#define		CMD_COMMANDER_VOTING_DATA				26018
#define		CMD_COMMANDER_DATA						26019
#define		CMD_CHANGE_SQUAD						26020
#define		CMD_FAME_DATA							26021
//#define		CMD_WARFIELD_STATUS_CHANGE_RESULT		26022
#define     CMD_CHECK_WARFIELD_STATUS				26023
#define		CMD_CHECK_WARFIELD_STATUS_RESULT		26024
#define		CMD_REQUEST_DELIVERY					26029
#define		CMD_ANSWER_DELIVERY						26030
#define		CMD_REQUEST_COMMANDER_REG_DATA			26031
#define		CMD_JOIN_SQUAD							26032
#define		CMD_SET_SQUAD_LOADING_POINT				26033
#define		CMD_ANSWER_COMMANDER_REG_DATA			26034
#define		CMD_YOU_ARE_SQUAD_COMMANDER				26035
#define		CMD_YOU_ARE_SQUAD_LEADER				26036
#define		CMD_CHANGE_LOADING_POINT				26037
#define     CMD_REQUEST_NATION_WAR_COUNT			26038			// Compare Nation War Count For Dirty Player
#define     CMD_ANSWER_NATION_WAR_COUNT				26039
#define		CMD_NW_MAP_MOVE							26040
#define		CMD_CHANGED_WARFIELD_STATUS				26041			// ManageServer to Other MapServer 
#define		CMD_NW_MAP_MOVE_FAIL					26042
#define		CMD_MAP_NATION_CODE_CHANGED				26043
#define		CMD_REQUEST_TILE_DONT					26044
#define		CMD_ANSWER_TILE_DONT					26045
#define		CMD_TILE_DONT_CHANGED					26046
#define		CMD_SQUAD_CHAT							26047
#define		CMD_CLEAR_SQUAD_DATA					26048			// 부대속성 클리어 
#define		CMD_REQUEST_WARFIELD_INFO				26049			// 공격자와 방어자의 확인 
#define		CMD_ANSWER_WARFIELD_INFO				26050
#define		CMD_WAR_BEGIN							26051			// 전쟁맵에 있는 사람의 전쟁시작 메세지..
#define		CMD_WAR_END								26052			// 방송도 있지만.. 안된다.
#define		CMD_REG_SQUAD_LEADER					26053			// 서버간 
#define		CMD_REQUEST_CHECK_WARFIELD_POSSESSION	26054
#define		CMD_ANSWER_CHECK_WARFIELD_POSSESSION	26055
#define		CMD_FREELANCER_SQUAD_JOIN				26056
#define		CMD_REQUEST_WARFIELD_POSSESSION			26057
#define		CMD_ANSWER_WARFIELD_POSSESSION			26058
#define		CMD_REQUEST_WARFIELD_WAR_DATA			26059
#define		CMD_WARFIELD_WAR_DATA1					26060			// 성문 수호석 데이타
#define		CMD_WARFIELD_WAR_DATA2					26061			// 남은시간, 멤버카운트 
#define		CMD_WARFIELD_WAR_DATA3					26062			// 방어부대 정보
#define		CMD_WARFIELD_WAR_DATA4					26063			// 공격부대 정보
#define		CMD_WARFIELD_WAR_DATA5					26064			// 지원군 부대 정보
#define		CMD_REQUEST_CHECK_WARNO					26065			// 전쟁번호를 판단한다.
#define		CMD_ANSWER_CHECK_WARNO					26066
#define		CMD_CLEAR_WAR_CHARACTER_DATA			26067			// 클라이언트
#define		CMD_SET_COMMANDER						26068			// DB데몬 
#define		CMD_STARTUP_NATION_CODE_CHANGE			26069			// 전쟁서버->관리서버->맵서버
#define		CMD_ANSWER_SQUAD_INFO2					26070			// 부대정보 파트2
#define		CMD_ANSWER_COMMANDER_VOTE_DATA2			26071
#define		CMD_SET_WARFIELD_POSSESSION				26072
#define		CMD_DELETE_EVENT_JOIN					26335			// 020115 LTS

#define		CMD_SAVE_WARNO							26364			// LTS NEW NATIONWAR


#define		CMD_INSERT_LOTTO_INFO					26404 //soto-030503 //DB데몬으로.
#define		CMD_DELETE_LOTTO_ALL_USER				26405 //soto-030503 //DB데몬으로.
#define		CMD_CUR_LOTTO_INFO						26406 //soto-030503 //DB데몬에서.
#define		CMD_LOTTERY_INFO						26407 //soto-030503 //DB데몬
#define		CMD_NEW_EVENT							20408 //soto-030504 //DB데몬
#define		CMD_LOTTO_BUY							20409 //soto-030504
#define		CMD_CAN_BUY								20410 //soto-030504
#define		CMD_WINNER_CHECK						20411 //soto-030505
#define		CMD_CHECK_OK							20412 //soto-030505
#define		CMD_DEL_LOTTO_USER						20413 //soto-030505

#define		CMD_CHECK_WINNER_MENU					20414 //soto-030505

#define		CMD_OPEN_LOTTOMENU						20415 //soto-030520
#define		CMD_LOTTERY_BROADCAST					20416 //soto-HK030924
#define		CMD_LOTTO_SEEK							20417 //soto-Lotto추가

#define		CMD_DEL_LOTTO_USER_OK					20418	// BBD 040127	로또프로세스 변경

//<soto-HK030924
typedef struct	tag_LOTTERY_INFO
{
	int	nLottoID;
	int nWinNumCount;
	int	anWinNumbers[10]; // 당첨 번호.
}t_LOTTERY_INFO;
//>soto-HK030924

//<soto-Lotto추가.
typedef	struct tag_OPEN_LOTTO_MENU
{
	int	nMaxNumberCount; //몇자리의 수로 로또를  만드느냐.
//	int	nCurrentLottoCount; //현지 로또를 몇장 가지고 있는냐?
}t_OPEN_LOTTO_MENU;
//>soto-Lotto추가.

struct LOTTO_EVENT_INFO
{	//< CSD-030804
	int		nLottoID;
	tm		StartDate;
	tm		LotteryDate;
	int		nWinNumCount;
	int		anWinNumbers[10]; // 10개 지만 현재는 4개만 쓰인다.
};	//> CSD-030804

typedef struct tag_CHECK_WINNER
{
	int		nLottoID;//soto-LottoADD
	char	strCharName[21];
	int		nWinItemCount;// 0이면 당첨 되지 않았슴. -1이면 빈곳이 충분치 않음.//토탈아이템 갯수.
	int		anWinNumbers[10];
	int		anWinItemsCount[5];//여기에 등수별 지급 되는 아이템 갯수가 들어간다./soto-Lotto추가
}t_CHECK_WINNER;
//<! BBD 040127	로또 유저 테이블에서 잘 지웠음을 알림
typedef struct tag_DEL_LOTTO_USER_OK
{
	bool	bIsDelOK;

}t_DEL_LOTTO_USER_OK;
//> BBD 040127	로또 유저 테이블에서 잘 지웠음을 알림

//<! BBD 040308		이벤트 레어 아이템 지급용 구조체
typedef struct tag_EVENT_RARE_ITEM_LIST
{
	int			nCn;
	char		szChrName[21];
	char		szLoginID[21];
	int			nIndex[10];
	ItemAttr	item[10];

}t_EVENT_RARE_ITEM_LIST;
//> BBD 040308		이벤트 레어 아이템 지급용 구조체

typedef	struct tag_BUY_LOTTO
{
	int	nLottoID;//soto-LottoADD
	char strCharName[21];
	int	anLottoNumber[10];
	int	m_nLottoPay;//Lotto에 지불 되는 돈.
}t_BUY_LOTTO;

//<soto-Lotto추가.
typedef struct tag_WINNER_MENU
{
	int	nLottoID;//soto-LottoADD
	int	 nMaxLottoCount;//몇자리 까지 로또 번호를 쓸것이냐?	
	char strCharName[21];
	int	anWinNumbers[10];
	int	nViewCount;//현재 화면에 나오는 로또의 카운트. 0초과.
	int	anLottoNumber[5][10];
	int	nTotalLottoCount;//녀석이 가지고 있는 로또의 총수가 들어간다.
}t_WINNER_MENU;
//>soto-Lotto추가.

//<soto-Lotto추가.
typedef struct tag_LOTTOPAPER_SEEK
{
	char	strChrName[20];
	int		nPage;//원하는 페이지가 들어간다.
	int		nViewCount;//현재 출력되는 복권의 갯수.
	int		anLottoNumber[5][10];//리스트에 있는 로또 번호들이 들어간다.
	int		nLottoID;//로또의 회차가 들어간다.
}t_LOTTOPAPER_SEEK;
//>soto-Lotto추가.

// Maximum Packet String Definition

#define		MAX_STRING_PK							100
#define     NW_NAME_MAX								31

#define		NW_NATION_COUNT							3
#define		NW_SQUAD_MAX							4


typedef struct CommonDataC_P
{
	BYTE	Data;
}	t_CommonDataC;

typedef struct CommonDataDw_P
{
	DWORD	Data;
}	t_CommonDataDw;


typedef struct CheckVote_P
{
	char	WarfieldNo;
	char	Status;
}	t_CheckVote;

typedef struct WarfieldStatusChange_P
{
	WORD	WarfieldNo;
	char	Status;
}	t_WarfieldStatusChange;

typedef struct WarBBS_P
{
	char	WarfieldNo;
	char	BBSType;
	char	LanNo;				//랭귀지팩 번호
	char	Size;
	char	Arg[MAX_STRING_PK];
}	t_WarBBS;

typedef struct WarfieldStatus_P
{
	BYTE	PacketStatus;
	char	Status[NW_NATION_COUNT];
}	t_WarfieldStatus;

typedef struct WarfieldStatusM_P
{
	char	Status[NW_NATION_COUNT];
	char	Possession[NW_NATION_COUNT];
}	t_WarfieldStatusM;

typedef struct VoteData_P
{
	char	WarfieldNo;
	char	VoteCount;				//워드나 정수형으로 변환 필요 
}	t_VoteData;

typedef struct RequestSquadInfo_P
{
	char	Nation;
	char	WarfieldNo;
	char	SquadNo;
}	t_RequestSquadInfo;

typedef struct SquadInfo_P
{
	char	SquadNo;
	int		ChipID;
	char	ChipName[NW_NAME_MAX];
	int		SoldierCount;
	char	Sok;					//레어속성 //비트연산	
	char	LoadingPoint;
}	t_SquadInfo;

typedef struct RegSquadLeader_P			// 서버간 패킷 
{
	char	Nation;
	char	WarfieldNo;
	char	SquadNo;
	int		ChipID;
	char	ChipName[NW_NAME_MAX];
}	t_RegSquadLeader;

typedef struct RequestCommanderVoteData_P
{
	char	Nation;
	char	WarfieldNo;
	char	CandidaterNo;
}	t_RequestCommanderVoteData;

typedef struct CommanderVoteData_P
{
	char	VoteNo;
	int		CandidaterID;
	char	Name[NW_NAME_MAX];
	char	Level;
	short	Fame;
	char	VoteCount;				//워드나 정수형으로 변환 필요
}	t_CommanderVoteData;

typedef struct RequestCommanderRegData_p
{
	char	Nation;
	char	WarfieldNo;
	char	CandidaterNo;
	int		CandidaterID;
	char	Name[NW_NAME_MAX];
	char	Level;
	short	Fame;
}	t_RequestCommanderRegData;

typedef struct CommanderVotingResult_P
{
	char	Type;	// Attacker, Defender, Reinforce
	int		ID;
	char	Name[NW_NAME_MAX];
	char	Level;
	char	Fame;
}	t_CommanderVotingResult;

typedef	struct ChangeSquad_P
{
	char	Nation;
	char	WarfieldNo;
	char	OldSquadNo;
	char	NewSquadNo;
}	t_ChangeSquad;

typedef	struct JoinSquad_P
{
	char	Nation;
	char	WarfieldNo;
	char	SquadNo;
}	t_JoinSquad;

typedef struct SetLoadingPoint_P
{
	char	Nation;
	char	WarfieldNo;
	char	SquadNo;
	char	LoadingPoint;
}	t_SetLoadingPoint;

typedef struct FameData_P
{
	signed char	Fame;
}	t_FameData;

typedef struct Delivery_P
{
	WORD	Port;
	DWORD	UserID;
	WORD	Size;
	char	Data[MAX_STRING_PK];
}	t_Delivery_R;

typedef struct Delivery_K
{
	DWORD	UserID;
	WORD	Size;
	char	Data[MAX_STRING_PK];
}	t_Delivery_A;

typedef struct NWMapMove_P
{
	char	WarfieldNo;
	char	SquadNo;
}	t_NWMapMove;

typedef struct TileDont_P
{
	char	TypeNumber;
	char	Value;
}	t_TileDont;

typedef struct SquadChat_P
{
	char	Type;
	char	Size;
	char	Message[MAX_STRING_PK];
}	t_SquadChat;

typedef struct WarfieldInfo_P
{
	char	AttackWarfieldNo;
	char	DefenceWarfieldNo;
}	t_WarfieldInfo;

typedef struct WarfieldPossession_P
{
	char	RequestType;
	char	Possession[NW_NATION_COUNT];
}	t_WarfieldPossession;

typedef struct WarfieldData1_P			//성문, 수호석 
{
	char	GuardStoneCount;
	char*   GuardStoneStatus;
	char	CastleGateWayCount;
	char*	CastleGateWayStatus;
}	t_WarfieldData1;

typedef struct WarfieldData2_P			// 전쟁 남은 시간, 방어,공격,지원군 수
{
	DWORD	RemainTime;
	WORD	DefencerCount;
	WORD	AttackerCount;
	WORD	ReinforceCount;
}	t_WarfieldData2;

typedef struct WarfieldData3_P			//부대정보 
{
	char	Type;						// Attacker, Defencer, Reinforce
	WORD	MemberCount[NW_SQUAD_MAX];
	WORD	SurvivorCount[NW_SQUAD_MAX];
}	t_WarfieldData3;

typedef	struct RequestCheckWarNo_P
{
	//char	Size;
	WORD	Port;
	int		ServerID;
}	t_RequestCheckWarNo;

typedef struct AnswerCheckWarNo_P
{
	BYTE	WarNo;
	int		ServerID;
}	t_AnswerCheckWarNo;

typedef struct SetCommander_P
{
	char	CommanderName[NW_NAME_MAX];
}	t_SetCommander;

typedef struct SWarfieldPossession_P
{
	char	WarfieldNo;
	char	Possession;
}	t_SWarfieldPossession;

typedef struct DeleteEventJoin_				// 020115 LTS
{
	char	UserName[20];
	char	EventNo;
}	t_DeleteEventJoin;


typedef union NationWar_P
{
	t_CommonDataC				CommonDataC;
	t_CommonDataDw				CommonDataDw;
	t_CheckVote					CheckVote;
	t_WarfieldStatusChange		WarfieldStatusChange;
	t_WarBBS					WarBBS;
	t_WarfieldStatus			WarfieldStatus;
	t_WarfieldStatusM			WarfieldStatusM;
	t_VoteData					VoteData;
	t_RequestSquadInfo			RequestSquadInfo;
	t_SquadInfo					SquadInfo;
	t_RequestCommanderVoteData	RequestCommanderVoteData;
	t_RequestCommanderRegData	RequestCommanderRegData;
	t_CommanderVoteData			CommanderVoteData;
	t_CommanderVotingResult		CommanderVotingResult;
	t_ChangeSquad				ChangeSquad;
	t_JoinSquad					JoinSquad;
	t_SetLoadingPoint			SetLoadingPoint;
	t_FameData					FameData;
	t_Delivery_R				Delivery_R;
	t_Delivery_A				Delivery_A;
	t_NWMapMove					NWMapMove;
	t_TileDont					TileDont;
	t_SquadChat					SquadChat;
	t_WarfieldInfo				WarfieldInfo;
	t_RegSquadLeader			RegSquadLeader;			//서버간 패킷 
	t_WarfieldPossession		WarfieldPossession;
	t_WarfieldData1				WarfieldData1;
	t_WarfieldData2				WarfieldData2;
	t_WarfieldData3				WarfieldData3;
	t_RequestCheckWarNo			RequestCheckWarNo;
	t_AnswerCheckWarNo			AnswerCheckWarNo;
	t_SetCommander				SetCommander;
	t_SWarfieldPossession		SWarfieldPossession;
	t_DeleteEventJoin			DeleteEventJoin;			// 020115 LTS

} t_NationWar;

#endif

