#ifndef _DRAGON_CHARLIST_
#define _DRAGON_CHARLIST_

#define MAX_NATION		7

#define  N_VYSEUS		3
#define  N_ZYPERN		4
#define  N_HEGEMONIA	5
#define  N_YILSE		6 


#define MAX_DIR_TABLE						 256
#define	MAX_SHORTPATH						  50
#define MAX_LEARN_ITEM						1000			//1220

#define REMOVE_								   0
#define ALIVE_								   1	
#define DEAD_								   2
#define BUFE_								   3	


#define  DEADCOUNT_							   20


#define  DEAD_CHARACTER_CHECK_TIME			   5
#define	 MAX_PC_CONTROL_NPC						8

#define VIEWTYPE_NORMAL_	0
#define VIEWTYPE_CAMELEON_	1
#define VIEWTYPE_GHOST_		2
#define VIEWTYPE_TREE_		3
#define VIEWTYPE_CAT_		4
#define VIEWTYPE_CONFUSION_ 5

enum CHAR_STEP_TYPE
{	//< CSD-TW-030620
	CLS_STEP = 0,  // 듀얼 클래스 단계
		DUAL_CLS = 1,  // 듀얼 클래스 종류
		EXP_STEP = 2,  // 경험치 단계
		T01_STEP = 3,  // 택틱 경험치 단계
		T02_STEP = 4,
		T03_STEP = 5,
		T04_STEP = 6,
		T05_STEP = 7,
		T06_STEP = 8,
		T07_STEP = 9,
		T08_STEP = 10,
		T09_STEP = 11,
		T10_STEP = 12,
		T11_STEP = 13,
		T12_STEP = 14,
		T13_STEP = 15,
		CSP_STEP = 16, // 전투스킬 포인터
		MAX_STEP = 17  // 최대 데이타수
};	//> CSD-TW-030620

enum
{ 
	// 물리적 공격 
	PHYSICAL = 0,                  
		// 마법
		LIFE_UP = 1,                   // 체력회복 
		PROTECTION = 2,                // 보호
		SHIELD = 3,                    // 보호막
		DECIPHER = 4,                  // 해독 마법
		HEAL_DISEASE = 5,              // 질병치료
		GREAT_HEAL = 6,                // 대체력회복
		SLOW = 10,                     // 속도저하
		CONFUSION = 11,                // 혼란
		INTOXICATION = 12,             // 중독
		STONELY =	13,                  // 석화
		ABSOLUTE_PARALYSIS = 14,       // 절대마비
		TOXIC_CLOUD = 15,              // 독구름  
		DISEASE_INDUCE = 16,           // 질병유발 
		VAMPIRE_TOUCH = 17,            // 뱀파이어의 손길
		SPIDER_WEB = 19,               // 거미줄  
		MAGICAL_TRAP = 20,             // 마법트랩
		ENCHANT_WEAPON = 21,           // 인첸트웨폰
		TRANSPARENCY = 22,             // 투명주문
		NULLITY_MAGIC = 24,            // 마법무효화  
		MINOR_AMPLIFY = 25,            // 소증폭
		MAGIC_AMPLIFY = 26,            // 마법증폭
		FIRE_RESIST = 28,              // 불에 대한 저항  
		FIRE_ARROW = 29,               // 화염화살 
		FIRE_BALL= 30,                 // 화염구
		SCORCHER = 31,                 // 화염군(화염방사)
		CIRCLE_FLAME= 33,              // 방사화염
		FIRE_WALL = 34,                // 화염벽
		FLAME_WAVE = 35,               // 움직이는 화염벽
		APOCALYPSE = 36,               // 지옥의 불
		ICE_RESIST = 37,               // 빙계 저항
		ICE_ARROW = 38,                // 얼음화살
		ICE_BALL = 39,                 // 얼음구 
		FREEZE_5TILE_RADIUS = 41,      // 반경 5타일 얼림	
		ICE_WALL = 42,                 // 얼음벽  	
		CIRCLE_ICE = 43,               // 원형얼음 공격
		ICE_STORM = 44,                // 얼음폭풍
		FREEZE_9TILE_RADIUS = 45,      // 반경 9타일 얼리기	
		LIGHT = 46,                    // 빛
		ELECT_RESIST = 47,             // 전격에 대한 저항
		LIGHTNING_BOLT = 48,           // 벼락
		CHAIN_LIGHTNING = 50,          // 유도 전격
		CIRCLE_LIGHTNING = 51,         // 원형 전격 
		LIGHTNING = 52,                // 직선 전격
		TWINKLE_STAR = 53,             // 수호성
		LIGHTNING_5TILE_RADIUS = 54,   // 반경 5타일 전격
		LOW_MONSTER_RECALL = 55,       // 저급 몬스터 소환
		MIDDLE_MONSTER_RECALL = 58,    // 중급 몬스터 소환
		PHASING = 64,                  // 장소이동
		MEMORIZING_LOCATION = 65,      // 이동장소기억
		TELEPORT = 66,                 // 순간이동
		MULTI_PORT = 67,               // 복수차원이동
		TOWN_PORTAL = 68,              // 차원이동
		MAGIC_DETECT = 75,             // 마법탐지
		REMOVE_CURSE = 78,             // 저주해제
		PROTECT_RANGE_WEAPON = 79,     // 장거리 무기로부터 보호
		LOST_SIGHT = 82,               // 시력상실   
		SPEED_UP = 83,                 // 속도증가
		GREAT_THUNDER_BOLT = 84,       // 대전격
		GREAT_METEOR = 85,             // 대운석 
		DRAGON_SCALE = 86,             // 드래곤의 비늘
		DEATH_FIRE = 87,               // 데쓰파이어
		SUMMONING_SKELETON = 88,       // 데쓰나이트 소환
		FLYING_SPARK = 89,             // 플라잉 스파크
		VAMPIRE_POISON = 90,           // 뱀파이어의 독
		VAMPIRE_DODGE = 91,            // 뱀파이어 회피
		SUMMONING_UNDEAD = 92,         // 언데드 소환
		FEATHER_OF_CURSE = 93,         // 마비의 깃털
		CURSE_OF_HELL = 94,            // 헬의 저주
		RECALL_FOLLOW = 95,            // 부하 소환
		FIRE_EXPLOSION = 96,           // 화염폭발
		FIRE_STORM = 97,               // 파이어스톰
		SHADOW_OF_EVIL = 98,           // 악의 그림자
		FREEZING = 99,                 // 주위 얼림
		BLITZ_SPEAR = 100,             // 번개창
		LIGHTNING_CLOUD = 101,         // 전격 구름
		FIRE_BREATH = 102,             // 화염 브레쓰
		ICE_BREATH = 103,              // 얼음 브레쓰
		LIGHTNING_BREATH = 104,        // 전격 브레쓰
		FLAME_PILLAR = 105,            // 화염 기둥
		FLAME_POUR = 106,              // 화염 폭풍 
		OCTA_LIGHTNING = 107,          // 방사 전격
		BLOOD_SPRINKLE = 108,          // 피뿌리기 
		PHEONIX = 109,                 // 불새
		METEOR_STRIKE = 110,           // 운석
		AREA_BAT_ATTACK = 111,         // 지역 박쥐공격
		AREA_PARALYSIS = 112,          // 지역 마비
		AREA_POISON = 113,             // 지역 중독
		AREA_CONFUSION = 114,          // 지역 혼란
		AREA_SLOW = 115,               // 지역 속도저하
		RESTORE_AUTHORITY = 151,       // 회복의권능  
		PROTECT_DANGER = 152,          // 위험으로부터 보호
		BLESS = 153,                   // 신의 축복
		RECOVER_POISON = 154,          // 해독의 권능
		CURE_DISEASE = 155,            // 질병치료의 권능
		MIRACLE_RECOVER = 156,     		 // 완치의 기적
		PERFECT_PROTECT = 157,         // 완전한 결계  
		GREAT_SHIELD = 158,            // 보호의 기적
		CANCEL_DIVINE = 159,           // 반신력 무효화
		RECURRENCE_DIVINE = 160,       // 회귀의 권능
		PRAY_POWER = 161,              // 기도의 역사
		HOLY_LIGHT = 162,              // 성스러운 빛  
		ANTHEM = 163,                  // 성가
		RELIEF_AUTHORITY = 164,        // 구원의 빛 
		HOLY_FIRE = 165,               // 성스러운 불
		GREAT_PRAY = 166,              // 위대한 기도  
		APPRECIATE = 167,              // 바른 깨달음
		INFLUENCE_DIVINE = 168,        // 신에의 감화
		VOICE_SOUL = 169,              // 영혼의 소리
		HOLY_RAGE = 170,               // 성스런 분노
		TURN_UNDEAD = 171,             // 턴 언데드
		CURSE = 172,                   // 신의 저주 
		AUTHORITY_RECOVER_SIGHT = 173, // 시력회복의 권능	
		DIVINE_POWER = 174,            // 디바인 파워
		AUTHORITY_LUCK = 175,          // 절대 행운의 권능	
		AUTHORITY_LOST_SIGHT = 177,    // 시력상실의 권능
		AUTHORITY_SIMUNIAN = 181,      // 시무니안의 권능
		RAGE_STONE = 189,              // 대지의 분노
		LIFE_DRAIN = 190,              // 생명력 탈취  
		RAGE_BLAST = 191,              // 화신의 분노
		RAGE_LIGHT_BALL = 192,         // 성령의 분노	
		THROW_SNOW = 193,              // 눈뭉치  
		THROW_ARROW = 194,             // 화살
		THROW_KNIFE = 195,             // 비도  
		// 전투스킬
		LIGHTNING_BOOM = 215,          // 번개 속성
		THUNDER_BLOW = 216,
		LIGHTNING_SHOCK = 217,
		THUNDER_STRIKE = 218,
		LIGHTNING_SHIELD = 219,
		LIGHTNING_EXTREME = 220,
		BLOOD_EARTH = 221,             // 대지 속성
		GROUND_ATTACK = 222, 
		BLOOD_WILL = 223,
		STONE_ARMOR = 224,
		SIMUNIAN_BOSOM = 225,
		EARTH_EXTREME = 226,
		SWORD_N_ROSES = 227,           // 화염 속성 
		MULTIPLE_FIRE = 228, 
		FLEET_MISSILE = 229,
		CONVERTING_ARMOR = 230, 
		CRITICAL_FIRE = 231, 
		FIRE_EXTREME = 232,
		POISONING_NOVA = 233,          // 어둠 속성
		CHERROY_SHADE = 234, 
		DARK_BLADE = 235, 
		TYBERN_GIFT = 236,
		DARK_ARMOR = 237,
		DARK_EXTREME = 238,
		ICING_BLAST = 239,             // 얼음 속성
		CRITICAL_HIDING = 240, 
		SHARK_MISSILE = 241, 
		HORN_OF_ICEBERG = 242, 
		ICE_SHIELD = 243,
		ICE_EXTREME = 244,
		CHARGING = 245,                // 바람 속성
		DOUBLE_ATTACK = 246, 
		WHILWIND = 247,
		TWISTER = 248, 
		GUST = 249, 
		WIND_EXTREME = 250
};

#ifndef _POS
typedef struct t_POS
{
	char type ; 
	short int p1, p2, p3 ;
} POS ;
#define _POS
#endif




typedef struct itemAttr
{
	short int		item_no;
	unsigned int	attr[6];
} ItemAttr;



#ifndef _K_ITEM
typedef struct tag_K_ITEM
{
	ItemAttr	item_attr;
	POS			item_pos;
}K_ITEM, *lpITEM;
#define _K_ITEM
#endif





typedef enum enumDIRECTION
{
	
	DIRECTION_SAME  			=   0,
		DIRECTION_UP				=   4,
		DIRECTION_RIGHTUP			=   5,
		DIRECTION_RIGHT				=   6,
		DIRECTION_RIGHTDOWN			=   7,
		DIRECTION_DOWN				=   0,
		DIRECTION_LEFTDOWN			=   1,
		DIRECTION_LEFT				=   2,
		DIRECTION_LEFTUP			=   3
		
} DIRECTION;


/////////////////////////////////////
// class define 

// class define 
enum ClassType//021008 lsw
{
	CLASSTYPEMIN = -1,
		WARRIOR		= 0,
		THIEF		= 1,
		ARCHER		= 2,
		WIZARD		= 3,
		PRIEST		= 4,
		CLASSTYPEMAX = 5
};
/////////////////////////////////////
// job define		0909 YGI		//  직업 초기화 때문에 20을 더한 값을 이용한다.
#define J_FAMER				20
#define J_MINNER			21
#define J_FISHER			22
#define J_LUMBERJACK		23
#define J_BUTCHER			24
#define J_HERB_DIGGER		25
#define J_HERDSMAN			26
#define J_CARPENTER			27
#define J_BLACKSMITH		28
#define J_COOKER			29
#define J_TAILOR			30
#define J_BOWCRAFT			31
#define J_ALCHEMIST			32
#define J_CANDLEMAKER		33
#define J_MERCHANT			34

#define MAX_BIX_ITEM	15

/////////////////////////////////////////////////////////////////////////// 
//		 상정및 길드 디파인				//####1213

#define		BLACKSMITH		0		// 대장간
#define		FARM			1		// 농장
#define		RESTAURANT		2		// 음식점
#define		HERBSHOP		3		// 약초점
#define		SHAMBLES		4		// 푸주간
#define		CANDLE			5		// 양초점
#define		SLOPSHOP		6		// 옷가게 
#define		ALCHEMY			7		// 활 화살
#define		WOODWORKING		8		// 목공소
#define		BOWCRAFT		9		// 활 화살
#define		SHIPYARD		10		// 조선소
#define		PUB				11		// 주점
#define		HOSPITAL		12		// 병원
#define		STORE			13		// 잡화점
#define		INN				14		// 여관
#define     MAGIC_GUILD		15

#define		STORE_TOTAL		17


///////////////////// 캐릭터 쉬기 상태 ///////////////////		// 0108
// Status변수에 set...      CS_ : Charater Status
#define		CS_NOMAL			0	// 정상 상태
#define		CS_REST				1	// 휴식 상태
#define		CS_SLEEP/*_DAY*/	2	// 낮에 자기 상태
// #define		CS_SLEEP_NIGHT		3	// 밤에 자기 상태





////////////////// 배고픔 수치 def 0102 /////////////////
#define		HT_NORMAL		  (-(HT_WALK * 2.))
#define		HT_WALK				0.084
#define		HT_RUN				(HT_WALK * 3.)
#define		HT_BATTLE_WALK		(HT_WALK * 2.)
#define		HT_BATTLE_RUN		(HT_WALK * 6.)
#define		HT_ATTACK			(HT_WALK * 30.)
#define		HT_MAGIC			(HT_WALK * 10.)
#define		HT_SKILL			(HT_WALK * 70.)



typedef struct tagCharacterParty
{
	short int	On;
	int			Server_id;
	char		Name[ 31];
	int			Face;
	int			Level;
	int			Gender;
	int			Str;
	int			Class;
}CharacterParty, *LpCharacterParty;

struct CCharRank
{	//< CSD-030326
	DWORD nation	  :3;  // 속한나라 - 0:없음, 1, 2, 3:바이서스, 4:자이펀, 5:헤게모니아, 6:일스
	DWORD guild_master:3;  // 길드 마스터
	DWORD king		  :1;  // 나라 왕
	DWORD dwReserved  :9;  // 사용되지 않음
	DWORD counselor	  :2;  // 0 : 없음, 1: 회사 운영자, 2: 게임내 운영자
	DWORD ultra_nk3	  :1;  // 극악피케이	1004 YGI
	DWORD ultra_nk4	  :1;  // 극악피케이	1004 YGI
	DWORD ultra_nk6	  :1;  // 극악피케이	1004 YGI
	DWORD reporter	  :1;
	DWORD imsi		  :10; // 1004 YGI
};	//> CSD-030326

// 010406 YGI
struct WINLOSEPOINT
{
	DWORD win			: 13;
	DWORD defeat		: 12;
	DWORD disconnect	: 7	;
};

struct NW_Character						// 010915 LTS		// LTS CHAR
{
	DWORD		WarNo						:	7;	//	전쟁번호
	DWORD		WarfieldNo					:	3;	//	전쟁터 번호
	DWORD		SquadNo						:	3;	//	부대번호
	DWORD		isSquadLeader				:	1;	//	부대장인가?	
	DWORD		isCommander					:	1;	//	사령관인가?
	DWORD		isCommanderCanidater		:	1;	//	사령관후보 인가?
	DWORD		DoWarJoinVote				:	1;	//	전쟁터 참여 투표를 했나?
	DWORD		DoCommanderVote				:	1;	//	사령관 투표를 했다
	DWORD		YL_JoinNation				:	4;	//	일스인경우 자이펀에했나? 바이서스에 했나?  //국가번호 
	DWORD		Reserved					:	10;	//	예약..
};

struct Event_Join							// 020115 LTS
{
	unsigned char Event1 : 1;				// 이벤트 1의 참여여부	
	unsigned char Event2 : 1;				// 이벤트 2의 참여여부	
	unsigned char Event3 : 1;				// 이벤트 3의 참여여부	
	unsigned char Event4 : 1;				// 이벤트 4의 참여여부	
	unsigned char Event5 : 1;				// 이벤트 5의 참여여부	
	unsigned char Event6 : 1;				// 이벤트 6의 참여여부	//백병전 이벤트
	unsigned char Event7 : 1;				// 이벤트 7의 참여여부	
	unsigned char Event8 : 1;				// 이벤트 8의 참여여부	
};


typedef struct tagCHARLIST
{	
	BYTE			bAlive;					// 캐릭터의 생사여부(	REMOVE_:0 / ALIVE_:1 / DEAD_:2 / BUFE_:3)
	int				deadcount;					// 캐릭터가 죽은후 실제 없어지기까지의 count
	
	short			server_id;
	DWORD			total_id;
	short			eventno;
	short			generationpos;		// NPC일경우 발생 위치 Table의 Index값을 기억하고 있는다.
	
	char			Name[20];
	
	short int		Level;
	short int       LvUpPoint;
	DWORD			Exp;
	DWORD			addexp;		// AttackMapper에서 증가되는 수치를 적어둔다. ( Ballance용 )
	
	DWORD			oldExp;
	short int		oldLevel;
	
	short int		Gender;						// 0:여자 1 : 남자
	short int		Face;						
	short int		nGuildCode; // CSD-030324
	short int		Class;						// 0:전사 1:궁수 2:도적 3:성직자 4:마법사
	//	short int		Class_Sprituality;	
	//	short int		Class_Poisioning;	
	//	short int		Class_Bombplay;		
	//	short int		Class_Entrapment;	
	//	short int		Class_Scrolling;	
	//	short int		Class_Cunning1;	
	//	short int		Class_Cunning2;	
	//	short int		Class_Cunning3;	
	//	short int		Class_Stealing;	
	short int		Spell;					// 마법사:0 / 성직자:1
	
	
	short int		fame;
	short int       fame_pk;			// 010915 LTS	Fame_PK -> NWCharacter로 교체 DB에는 실제로 NWCharacter의 값이 들어갑니다.
	NW_Character	NWCharacter;		// 010915 LTS
	short int       social_status;
	// 0212 YGI
	unsigned char	Tactics ;						// 선택한 전투기술 (보여주기 위함)
	unsigned char	Tactics_para;					// 실제 skill에 적용할 파라메터값을 가지고 있음...
	
	short int		Race;						// 종족
	
	short int		Str  ;				//  힘
	short int		Con  ;				//  건강
	short int		Dex  ;				//	민첩성
	short int		Wis  ;				//	지혜
	short int		Int  ;				//	지능
	short int		MoveP;				//	이동력
	short int		Char ;				//	매력
	short int		Endu ;				//  저향력
	short int		Moral;				//	사기
	short int		Luck ;				//	행운
	short int		wsps ;				//  마법력->마법 메모라이즈
	
	short int		Strp;				//  힘
	short int		Conp;				//  건강
	short int		Dexp;				//	민첩성
	short int		Wisp;				//	지혜
	short int		Intp;				//	지능
	short int		MovePp;				//	이동력
	short int		Charp;				//	매력
	short int		Endup;				//  저향력
	short int		Moralp;				//	사기
	short int		Luckp;				//	행운
	short int		wspsp;
	
	unsigned int		StrTp;				//  힘
	unsigned int		ConTp;				//  건강
	unsigned int		DexTp;				//	민첩성
	unsigned int		WisTp;				//	지혜
	unsigned int		IntTp;				//	지능
	unsigned int		MovePTp;				//	이동력
	unsigned int		CharTp;				//	매력
	unsigned int		EnduTp;				//  저향력
	unsigned int		MoralTp;				//	사기
	unsigned int		LuckTp;				//	행운
	unsigned int		wspsTp;
	
	short int		Strm;				//  힘
	short int		Conm;				//  건강
	short int		Dexm;				//	민첩성
	short int		Wism;				//	지혜
	short int		Intm;				//	지능
	short int		MovePm;				//	이동력
	short int		Charm;				//	매력
	short int		Endum;				//  저향력
	short int		Moralm;				//	사기
	short int		Luckm;				//	행운
	short int		wspsm;
	
	unsigned int		StrTm;				//  힘   g_curr_time + 60
	unsigned int		ConTm;				//  건강
	unsigned int		DexTm;				//	민첩성
	unsigned int		WisTm;				//	지혜
	unsigned int		IntTm;				//	지능
	unsigned int		MovePTm;				//	이동력
	unsigned int		CharTm;				//	매력
	unsigned int		EnduTm;				//  저향력
	unsigned int		MoralTm;				//	사기
	unsigned int		LuckTm;				//	행운
	unsigned int		wspsTm;
	
	
	//무기, Armor, 악세사리 ,ETC 에 의한 	
	short int		Strw;				//  힘
	short int		Conw;				//  건강
	short int		Dexw;				//	민첩성
	short int		Wisw;				//	지혜
	short int		Intw;				//	지능
	short int		MovePw;				//	이동력
	short int		Charw;				//	매력
	short int		Enduw;				//  저향력
	short int		Moralw;				//	사기
	short int		Luckw;				//	행운
	short int		wspsw;
	
	BYTE			item_Hit_Rate;
	BYTE			item_Deffence_Rate;
	
	
	// 자체수치, 시간(약물). 시간(마법), 장비. 
	// Magic.
	
	CCharRank		name_status;		// 0927 YGI
	
	
	short int		Ac;			// 창 AC( 방어력 )
	short int		AcDex;		// 0129 KHS
	short int		Att;		// 공격력..
	short int		defence_rate;
	
	short int		Job;
	DWORD			Money;
	
	int		Hp;
	int		HpMax ;
	
	int		Mana;						// 마법력
	int		ManaMax;
	
	int		Hungry;	
	int		HungryMax;
	
	DWORD			mpmin;
	DWORD			hpmin;
	
	
	char			MapName[20];
	
	unsigned char	Peacests;
	int		Sight;		// YGI 020418
	
	
	short int		BodyR, BodyG, BodyB;		// 몸 색깔 R.G.B
	short int		ClothR, ClothG, ClothB;		// 띠 색깔 R.G.B
	
	short int		Age;
	
	// 010531 KHS	
	short int		nk[ MAX_NATION];							// 국가간 우호도(NK)
	
	
	DWORD			killmon;					// 1계열몬스터 킬링스
	DWORD			killanimal;					// 동물 킬링수
	DWORD			killpc;						// 사람,NPC 킬링수
	char			KillerName[ 31];
	//////////////////// 0117 lkh (자료형) //////////////////////////
	//< CSD-010907
	/*
	float     	Resis_Poison;		//	독/죽음 저항력  _poinsion을 _poinson으로 변경 
	float				Resis_Stone	;		//	석화 마비 저항력
	float				Resis_Magic	;		//	마법저항력
	float				Resis_Fire	;			//	불 저항력
	float				Resis_Ice	;			//	얼음저항력
	float				Resis_Elect	;		//	전기저향력
	*/
	__int16 nPoison; // 저주계열 마법에 대한 저항력
	__int16 nCurse;  // 저주계열 마법에 대한 저항력	
	__int16 nFire;	 // 불계열 공격 마법에 대한 저항력
	__int16 nIce;		 // 얼음계열 공격 마법에 대한 저항력
	__int16 nElect;	 // 전격계열 공격 마법에 대한 저향력
	__int16 nHoly;	 // 신력계열 공격 마법에 대한 저항력
	//> CSD-010907
	////////////////////////////////////////////////////////////////
	
	
	DWORD			time_maintain1;		//  저항효과지속시간
	DWORD			time_maintain2;		//  능력효곽지속시간
	DWORD			time_maintain3;		//	상태변환지속효과 
	unsigned char	Ws[200];			//	마법
	unsigned char	Ps[200];			//	신법
	
	unsigned char   Skill[200];
	DWORD			skillexp[45];		// 1219 YGI 경험치
	
	
	
	
	
	
	// 내가 가지고 있는 아이템..
	// 인벤토리
	ItemAttr	inv[3][3][8] ;
	// 장착
	ItemAttr	equip[8] ;
	// 퀵 
	ItemAttr	quick[7] ;
	// 손에 들고 있는
	ItemAttr	handheld ;
	// 은행에 보관품
	ItemAttr	bank[5][3][6];		//1225
	
	short int	Item[MAX_LEARN_ITEM];		// 만들수 있는 아이템		1220
	short int	ItemMax;					// 현재 만들수 있는 아이템 최대치 1220
	
	int			itemweight;
	POS			SkillWork[ 20];
	
	//  Client을 위한 Data
	
	short int		SprNo;
	short int		SprType;	
	
	BYTE			accessory[4];
	short int		mantle;		// 011018 KHS 망또 
	DIRECTION		Direction;
	DWORD			IDWhoImAttacked;	// 나를 친놈이 누구냐..
	short int		nCurrentAction;
	
	short int       ox, oy;		// 자신이 태어난장소..
	short int		X, Y;
	short int		MovePathCount;
	short int		MoveLength;
	unsigned char	MoveType;
	short int		OldMoveSx,MoveSx;
	short int		OldMoveSy,MoveSy;
	unsigned char   MoveDirTbl[MAX_DIR_TABLE];
	short int		MoveGox;
	short int		MoveGoy;
	short int		Tox, Toy; // 타격을 받으면 밀린다. 
	
	
	int				path[ MAX_SHORTPATH][2];		// PathBuild()를 위한 변수..
	int				pathcount;
	
	// --------------  NPC Pattern---------- NPC공격을 위해..-
	short 			patterntype;
	short 			oldpatterntype;
	int				targetid;
	int				bossid;
	short			attackcount;
	DWORD 			aitimedelay;
	DWORD			aidelayhowmuch;
	int				tx, ty, how;// 이동에 관련된사항.
	int				attacked;
	bool			notcomeinside; // 집안에 들어갈수 없다. 
	
	
	// 1207 khs 추가.
	//  ------------------------------------- NPC가 죽으면 얻을수 있는 것들...
	short int				Get_meat;
	char					Meat_amount;
	short int				Get_skin;
	char					Skin_amount;
	short int				Get_Wool;
	char					Wool_amount;
	short int				Get_beewax;
	char					BeeWax_amount;
	
	// 1207 KHS
	//---------------------------------------- 
	char					viewtype;
	DWORD					viewtype_treet;		// 나무에 숨기 시간.
	DWORD					viewtype_cameleont;	// 카멜레온    시간.
	DWORD					viewtype_catt;		// 고양이걸음  시간.
	
	short int				openhouse;
	short int				tame;				// tame수치...
	bool					tamed;
	short int				tamingable;
	short int				tamingcountdown;
	BYTE					tame_cmd;
	char					HostName[ 21]; // 주인의 이름...
	short int				HostId;
	char					TargetName[ 31]; // 주인이 정한 공격자의 이름.
	
	//	DWORD					pk;			// pk를 했다면 현재시간보다 큰수를 가지고 있다 ! 
	short					pkid;		//
	short					pkcount;	// 이 수치가 3이상이면 PK를 한것이다 ! 
	DWORD					cast_pk;	// BroadCast된 시간.
	
	
	//------------------------   서버에서만 사용하는 para...
	DWORD			WalkTime;
	DWORD			desttime;
	
	// ********************************* 추가된 항목들..
	// 유동적임.	
	//short int		Dam_Min, Dam_Max ;
	//short int		Def_Rate ;
	//short int		Hit_Rate ;
	char			disease[6];					
	
	
	//-----------------------------------------
	//short int		skillno;
	short int		cur_skillno; // 현재 실행되기 위해 시전중인 Skill...
	short int		cur_skillx;
	short int		cur_skilly;
	short int		cur_skilltargettype;
	short int		cur_skilltarget_id;
	POS				cur_skillPOS;
	DWORD			exetime_skill; // 실행될 Skill의 시간.
	
	
	
	
	
	short int		MaxWizardSpell ;
	short int		MaxPriestSpell ;
	
	short int		Weight, MaxWeight ;
	
	//	short int		Def_Correction ;				// 방어보정의 총 합. 아이템 장착시 여기에 누적된다.
	//	bool			class_item_corr_flag ;			// 클래스 보정
	
	
	DWORD			tac_skillEXP[13] ;
	char			cur_tac_skill;					// 현재 어떤공격이 이류어졌을때 Setting되며 전투기술 Index가 들어간다. ( TACTICS_Crapple....과 같은 )
	
	
	short	int 	reserved_point ;
	int				nAbilityPlusOfPotion[20];		//먹는거에 의한 파워업
	DWORD			dwAbiliityPlusTime[20];
	//	int				nAbilityPlusOfWeapon[20];		//아이템에 장작에 의한 파워업
	DWORD			DontDiseaseTime[6];             //질병에 걸리지 않은 시간 
	
	
	DWORD			BankMoney;
	DWORD			LastTotal;
	DWORD			LastLoan;
	DWORD			LastLoan_time;
	
	ItemAttr		box_item[MAX_BIX_ITEM];			// SQL에 저장할 필요 없다.. 공용 버퍼..
	DWORD			box_id;							// 현재 열려 있는 박스의 고유 ID
	
	int				Defence;						// 방어력
	int				Aboidance;						// 회피율
	DWORD			Ignore;							// 마법 회피...
	
	short int		Hungry_t;						// 몇초에 한번씩 떨어질 것인가.. 디폴트 10초
	short int		Hungry_turn;					// 1초에 한번식 콜 할때.... 사용
	float			Hungry_much;					// 한번 떨어질때 얼마나 떨어질 것인가.. 디폴트 5
	bool			HungryChangeFlag;
	
	
	
	
	
	
	
	// Chatting관련 변수 ----------------
	char			chatname[ 31];
	char			chattype;
	short int		whisperid;
	// ----------------------------------
	
	
	/// ######### 0218 YGI ################
	// Party / Relation / Employment.........................	0213 YGI
	CharacterParty party[6];			
	CharacterParty relation[3];				
	CharacterParty employment[6];				
	
	//////////////////////////////////////// up_date용			
	char party_str[6][31];
	char relation_str[3][31];
	char employment_str[6][31];
	//############################################
	
	int partyrequestflag;
	
	
	//////////////////////// 0331 이하 전체수정 LKH /////////////////////
	BYTE			Condition;			// 0정상->CON_NORMAL, 1활동적->CON_ACTIVE, 2무기력->CON_SLUGGISH, 3슬로우->CON_SLOW, 4혼란->CON_DAZE, 5중독->CON_POISON, 6석화->CON_STONE, 7죽음->CON_DEATH 
	DWORD			Condition_Time[8];	// 상태 지속 시간;	
	
	BYTE			Status;				// 캐릭터의 휴식 상태 0은 nomal		//0108
	
	
	//DWORD			doing_CheckTime;	// 특정 효력을 발생하는데 걸리는 시간
	//short int		doing_Type;			// 특정효력 고유번호:1->죽음
	
	DWORD			DontPoison;			// 중독 상태를 완전히 막음
	DWORD			DontDaze;			// 혼란 상태를 완전히 막음
	DWORD			DontSlow;			// 속도저하 상태를 완전히 막음
	DWORD			Miner50Damage;		// 데미지량을 50% 줄임
	DWORD			Miner30Damage;		// 데미지량을 30% 줄임
	DWORD			Miner50Fire;		// 불마법 데미지만 50% 줄임
	DWORD			Miner30Fire;		// 불마법 데미지만 30% 줄임
	DWORD			Miner50Ice;			// 빙마법 데미지만 50% 줄임
	DWORD			Miner30Ice;			// 빙마법 데미지만 30% 줄임
	DWORD			Miner50Elect;		// 전격마법 데미지만 50% 줄임
	DWORD			Miner30Elect;		// 전격마법 데미지만 30% 줄임
	DWORD			Miner100Elect;		// 전격마법 완전 방어
	
	DWORD			DontCasting;		// 마법 불가
	DWORD			DeathTime;			// 죽음으로 이르는 시간 셋팅
	DWORD			MinerSight;			// 시야를 2타일로 좁힘
	DWORD			Plus50Defence;		// 방어율 50% 증가
	DWORD			Plus50Avoid;		// 회피율 50% 증가(상대의 공격 명중확률이 떨어짐)
	DWORD			DontDisease;		// 모든 질병이 걸리지 않는다.
	DWORD			DontEvilMagic;		// 모든 저주 마법을 튕겨냄
	DWORD			EvilToProtect;		// 사악한 기운(마법)으로부터 보호(random하게 50~80% 보호 적용) & 모든 악한 가치관을 지닌 존재의 효과에 대한 저항
	DWORD			Plus50AP;			// 공격력 50% 증가
	DWORD			Plus50Agility;		// 민첩성 50% 증가
	DWORD			AllSuccess;			// 모든 행동(기술) 성공
	
	DWORD			Plus50MagicHD;																
	DWORD			Plus100MagicHD;																
	
	DWORD			Plus100Ac;			// 마법에 의한 장비 방어력 100% 증가
	DWORD			Miner30AP;			// 전투력(공격력)30%감쇠				*
	DWORD			Plus50Ac;			// 물리방어력(ac)50%증가	
	DWORD			Plus50Luck;			// 행운치50%증가
	DWORD			Plus100Defence;		// 전체 방어율 100% 증가
	/////////////////////////// 여기까지 ///////////////////////////////
	
	////////////// 0410 lkh 추가 //////////////
	DWORD		ReturnMagic;		//	마법의 효과를 시전자에게 되돌림
	
	
	//////////// 0125 YGI ///////////// 아이템 거래
	K_ITEM		give[20];		// 내가 줘야 하는 아이템
	K_ITEM		recv[20];		// 내가 받아야 하는 아이템 
	short int	target_id;		// 거래 대상
	bool		trade_on;		// 거래하고 있는지 없는지...
	
	DWORD		timetoupdate;	
	
	char		updatable;		
	int			balancingtest;
	
	DWORD		DontDamage;		
	
	
#ifdef _GAME_SERVER_
	AREA		area_tbl[MAX_AREA_BUFFER];
#endif
	
	
	bool		counseler;		// counseler는 타격을 받지 않는다. 
	
	int			ctrlpc;			// NPC일경우 나를 제어하는 NPC의 ID, 없을 경우 -1를 가지고 있다.
	int			ctrlnpc[MAX_PC_CONTROL_NPC];		
	
	
	
	/////////////// 0315 lkh 추가 ////////////////
	DWORD		DontAttack;			// 일반공격불가
	DWORD		AmplifyMagic;		// 공격마법의 데미지가 1.5배 늘어남
	DWORD		Transparency;		// 투명인간 지속시간
	
	DWORD		AllCanCleMagic;		//	모든 마법을 튕겨냄
	DWORD		RangeWeaponProtect; //	모든 장거리(비무기)에 대한 완전 보호
	DWORD		SpeedUp;			//  현재 속도의 1/2만큼 더 빨라짐
	int			ProtectField_X;		//	마법 결계의 타일중심좌표
	int			ProtectField_Y;		//             "
	DWORD		ProtectField;		//	마법 결계의 지속처리
	///////////////////////////////////////////////
	
	// 0405 YGI
	char		believe_god;		// 내가 믿는 신
	short int	faith;				// 신앙심
	char		preach_name[20];	// 전도한 사람의 이름
	
	short int	god_cast_level;		// 신전 주문 학습 단계	// 0410	YGI	// sql 저장 필요
	bool		in_temple;			// 신전안에 있다		// 0410	YGI	// sql 저장 필요 없음
	int			is_god_meeting;		// 현재 예배중이다		// 0410	YGI	// sql 저장 필요 없음
	DWORD		god_meeting_start_time;	// 예배 시작한 시간	// 0410	YGI	// sql 저장 필요 없음
	bool		i_go_year_meeting;		// 연중 예배에 갔다.// 0410	YGI	// sql 저장 필요 없음
	bool		i_go_month_meeting;		// 월중 예배에 갔다.// 0410	YGI	// sql 저장 필요 없음
	bool		i_go_day_meeting;		// 일일 예배에 갔다.// 0410	YGI	// sql 저장 필요 없음
	
	DWORD		can_memorize_time;		// 가능한 시간	// 저장할 필요 없음  0414 YGI
	
	short int		startposition;
	short int		startmap;
	
	//////////////////////////////////  결투 시스템...
	
	char        dualname[20];
	char        dualstatus;	// 0: No Dual    1: 신청한상태..   2: 대결상태.
	
	DWORD		dualvictory;	
	DWORD		dualfail;	
	DWORD		dualdraw;	
	
	// 010406 YGI
	DWORD			LadderScore;		// 콜로세스 래더 점수
	WINLOSEPOINT	WinLoseScore;		// 콜로세스 승패
	//< CSD-010907
	char aStepInfo[20];
	//> CSD-010907
	int				nUserAge;			// 030923 kyo
	Event_Join		EventJoin;			// 020115 LTS
} CHARLIST, *LPCHARLIST;		

#define		HUNGRY_TIME		60		// 1분  //###1213_2 수정
#define		HUNGRY_MUCH		1.0	



// 질병 테이블	//0104
typedef struct tag_disease_table
{							
	short int	disease_number;
	char		han_name[31];	
	char		name[31];	
	short int	lv;			
	short int	nut1_1;		
	short int	nut2_1;			
	short int	nut3_1;		
	short int	probability_1;
	short int	andor_1;	
	short int	checktime_1;
	short int	contact_char;
	short int	talk_char;	
	short int	fuck_char;	
	short int	contact_obj;
	short int	eat_obj;	
	short int	nut1_2;		
	short int	nut2_2;	
	short int	nut3_2;
	short int	probability_2;
	short int	checktime_2;
	short int	andor_2;
	short int	dec_str;
	short int	dec_dex;
	short int	dec_con;
	short int	dec_wis;
	short int	dec_int;
	short int	dec_movp;
	short int	dec_char;
	short int	dec_endu;
	short int	dec_mor;
	short int	dec_luck;
	short int	dec_ws;
	short int	dec_ps;
	short int	recoverable;
	short int	life	;
	short int	health	;
	short int	mp	;
	short int	dp	;
	short int	max_	;
	short int	damage	;
	short int	att_rate	;
	short int	depen_rate	;
	short int	ac	;
	short int	mad	;
	short int	poison	;
	short int	stony	;
	short int	sluggish	;
	short int	active	;
	short int	paralysis	;
	short int	active_time	;
	short int	maintain_time	;
	short int	natural_recovery	;
	short int	nut1_3	;
	short int	nut2_3	;
	short int	nut3_3	;
	short int	probability_3	;
	short int	checktime_3	;
	short int	andor_3	;
	short int	price_heal	;
	short int	price_prevent	;
	
}DiseaseTable;



//////////////// 0405 YGI	신전 테이블
struct GodTable
{
	char meet_year_month;
	char meet_year_day;
	char meet_year_hour;
	char meet_month_day;
	char meet_month_hour;
	char meet_day_hour;
};

#endif


