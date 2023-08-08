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
	CLS_STEP = 0,  // ��� Ŭ���� �ܰ�
		DUAL_CLS = 1,  // ��� Ŭ���� ����
		EXP_STEP = 2,  // ����ġ �ܰ�
		T01_STEP = 3,  // ��ƽ ����ġ �ܰ�
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
		CSP_STEP = 16, // ������ų ������
		MAX_STEP = 17  // �ִ� ����Ÿ��
};	//> CSD-TW-030620

enum
{ 
	// ������ ���� 
	PHYSICAL = 0,                  
		// ����
		LIFE_UP = 1,                   // ü��ȸ�� 
		PROTECTION = 2,                // ��ȣ
		SHIELD = 3,                    // ��ȣ��
		DECIPHER = 4,                  // �ص� ����
		HEAL_DISEASE = 5,              // ����ġ��
		GREAT_HEAL = 6,                // ��ü��ȸ��
		SLOW = 10,                     // �ӵ�����
		CONFUSION = 11,                // ȥ��
		INTOXICATION = 12,             // �ߵ�
		STONELY =	13,                  // ��ȭ
		ABSOLUTE_PARALYSIS = 14,       // ���븶��
		TOXIC_CLOUD = 15,              // ������  
		DISEASE_INDUCE = 16,           // �������� 
		VAMPIRE_TOUCH = 17,            // �����̾��� �ձ�
		SPIDER_WEB = 19,               // �Ź���  
		MAGICAL_TRAP = 20,             // ����Ʈ��
		ENCHANT_WEAPON = 21,           // ��þƮ����
		TRANSPARENCY = 22,             // �����ֹ�
		NULLITY_MAGIC = 24,            // ������ȿȭ  
		MINOR_AMPLIFY = 25,            // ������
		MAGIC_AMPLIFY = 26,            // ��������
		FIRE_RESIST = 28,              // �ҿ� ���� ����  
		FIRE_ARROW = 29,               // ȭ��ȭ�� 
		FIRE_BALL= 30,                 // ȭ����
		SCORCHER = 31,                 // ȭ����(ȭ�����)
		CIRCLE_FLAME= 33,              // ���ȭ��
		FIRE_WALL = 34,                // ȭ����
		FLAME_WAVE = 35,               // �����̴� ȭ����
		APOCALYPSE = 36,               // ������ ��
		ICE_RESIST = 37,               // ���� ����
		ICE_ARROW = 38,                // ����ȭ��
		ICE_BALL = 39,                 // ������ 
		FREEZE_5TILE_RADIUS = 41,      // �ݰ� 5Ÿ�� ��	
		ICE_WALL = 42,                 // ������  	
		CIRCLE_ICE = 43,               // �������� ����
		ICE_STORM = 44,                // ������ǳ
		FREEZE_9TILE_RADIUS = 45,      // �ݰ� 9Ÿ�� �󸮱�	
		LIGHT = 46,                    // ��
		ELECT_RESIST = 47,             // ���ݿ� ���� ����
		LIGHTNING_BOLT = 48,           // ����
		CHAIN_LIGHTNING = 50,          // ���� ����
		CIRCLE_LIGHTNING = 51,         // ���� ���� 
		LIGHTNING = 52,                // ���� ����
		TWINKLE_STAR = 53,             // ��ȣ��
		LIGHTNING_5TILE_RADIUS = 54,   // �ݰ� 5Ÿ�� ����
		LOW_MONSTER_RECALL = 55,       // ���� ���� ��ȯ
		MIDDLE_MONSTER_RECALL = 58,    // �߱� ���� ��ȯ
		PHASING = 64,                  // ����̵�
		MEMORIZING_LOCATION = 65,      // �̵���ұ��
		TELEPORT = 66,                 // �����̵�
		MULTI_PORT = 67,               // ���������̵�
		TOWN_PORTAL = 68,              // �����̵�
		MAGIC_DETECT = 75,             // ����Ž��
		REMOVE_CURSE = 78,             // ��������
		PROTECT_RANGE_WEAPON = 79,     // ��Ÿ� ����κ��� ��ȣ
		LOST_SIGHT = 82,               // �÷»��   
		SPEED_UP = 83,                 // �ӵ�����
		GREAT_THUNDER_BOLT = 84,       // ������
		GREAT_METEOR = 85,             // �� 
		DRAGON_SCALE = 86,             // �巡���� ���
		DEATH_FIRE = 87,               // �������̾�
		SUMMONING_SKELETON = 88,       // ��������Ʈ ��ȯ
		FLYING_SPARK = 89,             // �ö��� ����ũ
		VAMPIRE_POISON = 90,           // �����̾��� ��
		VAMPIRE_DODGE = 91,            // �����̾� ȸ��
		SUMMONING_UNDEAD = 92,         // �𵥵� ��ȯ
		FEATHER_OF_CURSE = 93,         // ������ ����
		CURSE_OF_HELL = 94,            // ���� ����
		RECALL_FOLLOW = 95,            // ���� ��ȯ
		FIRE_EXPLOSION = 96,           // ȭ������
		FIRE_STORM = 97,               // ���̾��
		SHADOW_OF_EVIL = 98,           // ���� �׸���
		FREEZING = 99,                 // ���� ��
		BLITZ_SPEAR = 100,             // ����â
		LIGHTNING_CLOUD = 101,         // ���� ����
		FIRE_BREATH = 102,             // ȭ�� �극��
		ICE_BREATH = 103,              // ���� �극��
		LIGHTNING_BREATH = 104,        // ���� �극��
		FLAME_PILLAR = 105,            // ȭ�� ���
		FLAME_POUR = 106,              // ȭ�� ��ǳ 
		OCTA_LIGHTNING = 107,          // ��� ����
		BLOOD_SPRINKLE = 108,          // �ǻѸ��� 
		PHEONIX = 109,                 // �һ�
		METEOR_STRIKE = 110,           // �
		AREA_BAT_ATTACK = 111,         // ���� �������
		AREA_PARALYSIS = 112,          // ���� ����
		AREA_POISON = 113,             // ���� �ߵ�
		AREA_CONFUSION = 114,          // ���� ȥ��
		AREA_SLOW = 115,               // ���� �ӵ�����
		RESTORE_AUTHORITY = 151,       // ȸ���ǱǴ�  
		PROTECT_DANGER = 152,          // �������κ��� ��ȣ
		BLESS = 153,                   // ���� �ູ
		RECOVER_POISON = 154,          // �ص��� �Ǵ�
		CURE_DISEASE = 155,            // ����ġ���� �Ǵ�
		MIRACLE_RECOVER = 156,     		 // ��ġ�� ����
		PERFECT_PROTECT = 157,         // ������ ���  
		GREAT_SHIELD = 158,            // ��ȣ�� ����
		CANCEL_DIVINE = 159,           // �ݽŷ� ��ȿȭ
		RECURRENCE_DIVINE = 160,       // ȸ���� �Ǵ�
		PRAY_POWER = 161,              // �⵵�� ����
		HOLY_LIGHT = 162,              // �������� ��  
		ANTHEM = 163,                  // ����
		RELIEF_AUTHORITY = 164,        // ������ �� 
		HOLY_FIRE = 165,               // �������� ��
		GREAT_PRAY = 166,              // ������ �⵵  
		APPRECIATE = 167,              // �ٸ� ������
		INFLUENCE_DIVINE = 168,        // �ſ��� ��ȭ
		VOICE_SOUL = 169,              // ��ȥ�� �Ҹ�
		HOLY_RAGE = 170,               // ������ �г�
		TURN_UNDEAD = 171,             // �� �𵥵�
		CURSE = 172,                   // ���� ���� 
		AUTHORITY_RECOVER_SIGHT = 173, // �÷�ȸ���� �Ǵ�	
		DIVINE_POWER = 174,            // ����� �Ŀ�
		AUTHORITY_LUCK = 175,          // ���� ����� �Ǵ�	
		AUTHORITY_LOST_SIGHT = 177,    // �÷»���� �Ǵ�
		AUTHORITY_SIMUNIAN = 181,      // �ù��Ͼ��� �Ǵ�
		RAGE_STONE = 189,              // ������ �г�
		LIFE_DRAIN = 190,              // ����� Ż��  
		RAGE_BLAST = 191,              // ȭ���� �г�
		RAGE_LIGHT_BALL = 192,         // ������ �г�	
		THROW_SNOW = 193,              // ����ġ  
		THROW_ARROW = 194,             // ȭ��
		THROW_KNIFE = 195,             // ��  
		// ������ų
		LIGHTNING_BOOM = 215,          // ���� �Ӽ�
		THUNDER_BLOW = 216,
		LIGHTNING_SHOCK = 217,
		THUNDER_STRIKE = 218,
		LIGHTNING_SHIELD = 219,
		LIGHTNING_EXTREME = 220,
		BLOOD_EARTH = 221,             // ���� �Ӽ�
		GROUND_ATTACK = 222, 
		BLOOD_WILL = 223,
		STONE_ARMOR = 224,
		SIMUNIAN_BOSOM = 225,
		EARTH_EXTREME = 226,
		SWORD_N_ROSES = 227,           // ȭ�� �Ӽ� 
		MULTIPLE_FIRE = 228, 
		FLEET_MISSILE = 229,
		CONVERTING_ARMOR = 230, 
		CRITICAL_FIRE = 231, 
		FIRE_EXTREME = 232,
		POISONING_NOVA = 233,          // ��� �Ӽ�
		CHERROY_SHADE = 234, 
		DARK_BLADE = 235, 
		TYBERN_GIFT = 236,
		DARK_ARMOR = 237,
		DARK_EXTREME = 238,
		ICING_BLAST = 239,             // ���� �Ӽ�
		CRITICAL_HIDING = 240, 
		SHARK_MISSILE = 241, 
		HORN_OF_ICEBERG = 242, 
		ICE_SHIELD = 243,
		ICE_EXTREME = 244,
		CHARGING = 245,                // �ٶ� �Ӽ�
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
// job define		0909 YGI		//  ���� �ʱ�ȭ ������ 20�� ���� ���� �̿��Ѵ�.
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
//		 ������ ��� ������				//####1213

#define		BLACKSMITH		0		// ���尣
#define		FARM			1		// ����
#define		RESTAURANT		2		// ������
#define		HERBSHOP		3		// ������
#define		SHAMBLES		4		// Ǫ�ְ�
#define		CANDLE			5		// ������
#define		SLOPSHOP		6		// �ʰ��� 
#define		ALCHEMY			7		// Ȱ ȭ��
#define		WOODWORKING		8		// �����
#define		BOWCRAFT		9		// Ȱ ȭ��
#define		SHIPYARD		10		// ������
#define		PUB				11		// ����
#define		HOSPITAL		12		// ����
#define		STORE			13		// ��ȭ��
#define		INN				14		// ����
#define     MAGIC_GUILD		15

#define		STORE_TOTAL		17


///////////////////// ĳ���� ���� ���� ///////////////////		// 0108
// Status������ set...      CS_ : Charater Status
#define		CS_NOMAL			0	// ���� ����
#define		CS_REST				1	// �޽� ����
#define		CS_SLEEP/*_DAY*/	2	// ���� �ڱ� ����
// #define		CS_SLEEP_NIGHT		3	// �㿡 �ڱ� ����





////////////////// ����� ��ġ def 0102 /////////////////
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
	DWORD nation	  :3;  // ���ѳ��� - 0:����, 1, 2, 3:���̼���, 4:������, 5:��Ը�Ͼ�, 6:�Ͻ�
	DWORD guild_master:3;  // ��� ������
	DWORD king		  :1;  // ���� ��
	DWORD dwReserved  :9;  // ������ ����
	DWORD counselor	  :2;  // 0 : ����, 1: ȸ�� ���, 2: ���ӳ� ���
	DWORD ultra_nk3	  :1;  // �ؾ�������	1004 YGI
	DWORD ultra_nk4	  :1;  // �ؾ�������	1004 YGI
	DWORD ultra_nk6	  :1;  // �ؾ�������	1004 YGI
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
	DWORD		WarNo						:	7;	//	�����ȣ
	DWORD		WarfieldNo					:	3;	//	������ ��ȣ
	DWORD		SquadNo						:	3;	//	�δ��ȣ
	DWORD		isSquadLeader				:	1;	//	�δ����ΰ�?	
	DWORD		isCommander					:	1;	//	��ɰ��ΰ�?
	DWORD		isCommanderCanidater		:	1;	//	��ɰ��ĺ� �ΰ�?
	DWORD		DoWarJoinVote				:	1;	//	������ ���� ��ǥ�� �߳�?
	DWORD		DoCommanderVote				:	1;	//	��ɰ� ��ǥ�� �ߴ�
	DWORD		YL_JoinNation				:	4;	//	�Ͻ��ΰ�� �����ݿ��߳�? ���̼����� �߳�?  //������ȣ 
	DWORD		Reserved					:	10;	//	����..
};

struct Event_Join							// 020115 LTS
{
	unsigned char Event1 : 1;				// �̺�Ʈ 1�� ��������	
	unsigned char Event2 : 1;				// �̺�Ʈ 2�� ��������	
	unsigned char Event3 : 1;				// �̺�Ʈ 3�� ��������	
	unsigned char Event4 : 1;				// �̺�Ʈ 4�� ��������	
	unsigned char Event5 : 1;				// �̺�Ʈ 5�� ��������	
	unsigned char Event6 : 1;				// �̺�Ʈ 6�� ��������	//�麴�� �̺�Ʈ
	unsigned char Event7 : 1;				// �̺�Ʈ 7�� ��������	
	unsigned char Event8 : 1;				// �̺�Ʈ 8�� ��������	
};


typedef struct tagCHARLIST
{	
	BYTE			bAlive;					// ĳ������ ���翩��(	REMOVE_:0 / ALIVE_:1 / DEAD_:2 / BUFE_:3)
	int				deadcount;					// ĳ���Ͱ� ������ ���� ������������� count
	
	short			server_id;
	DWORD			total_id;
	short			eventno;
	short			generationpos;		// NPC�ϰ�� �߻� ��ġ Table�� Index���� ����ϰ� �ִ´�.
	
	char			Name[20];
	
	short int		Level;
	short int       LvUpPoint;
	DWORD			Exp;
	DWORD			addexp;		// AttackMapper���� �����Ǵ� ��ġ�� ����д�. ( Ballance�� )
	
	DWORD			oldExp;
	short int		oldLevel;
	
	short int		Gender;						// 0:���� 1 : ����
	short int		Face;						
	short int		nGuildCode; // CSD-030324
	short int		Class;						// 0:���� 1:�ü� 2:���� 3:������ 4:������
	//	short int		Class_Sprituality;	
	//	short int		Class_Poisioning;	
	//	short int		Class_Bombplay;		
	//	short int		Class_Entrapment;	
	//	short int		Class_Scrolling;	
	//	short int		Class_Cunning1;	
	//	short int		Class_Cunning2;	
	//	short int		Class_Cunning3;	
	//	short int		Class_Stealing;	
	short int		Spell;					// ������:0 / ������:1
	
	
	short int		fame;
	short int       fame_pk;			// 010915 LTS	Fame_PK -> NWCharacter�� ��ü DB���� ������ NWCharacter�� ���� ���ϴ�.
	NW_Character	NWCharacter;		// 010915 LTS
	short int       social_status;
	// 0212 YGI
	unsigned char	Tactics ;						// ������ ������� (�����ֱ� ����)
	unsigned char	Tactics_para;					// ���� skill�� ������ �Ķ���Ͱ��� ������ ����...
	
	short int		Race;						// ����
	
	short int		Str  ;				//  ��
	short int		Con  ;				//  �ǰ�
	short int		Dex  ;				//	��ø��
	short int		Wis  ;				//	����
	short int		Int  ;				//	����
	short int		MoveP;				//	�̵���
	short int		Char ;				//	�ŷ�
	short int		Endu ;				//  �����
	short int		Moral;				//	���
	short int		Luck ;				//	���
	short int		wsps ;				//  ������->���� �޸������
	
	short int		Strp;				//  ��
	short int		Conp;				//  �ǰ�
	short int		Dexp;				//	��ø��
	short int		Wisp;				//	����
	short int		Intp;				//	����
	short int		MovePp;				//	�̵���
	short int		Charp;				//	�ŷ�
	short int		Endup;				//  �����
	short int		Moralp;				//	���
	short int		Luckp;				//	���
	short int		wspsp;
	
	unsigned int		StrTp;				//  ��
	unsigned int		ConTp;				//  �ǰ�
	unsigned int		DexTp;				//	��ø��
	unsigned int		WisTp;				//	����
	unsigned int		IntTp;				//	����
	unsigned int		MovePTp;				//	�̵���
	unsigned int		CharTp;				//	�ŷ�
	unsigned int		EnduTp;				//  �����
	unsigned int		MoralTp;				//	���
	unsigned int		LuckTp;				//	���
	unsigned int		wspsTp;
	
	short int		Strm;				//  ��
	short int		Conm;				//  �ǰ�
	short int		Dexm;				//	��ø��
	short int		Wism;				//	����
	short int		Intm;				//	����
	short int		MovePm;				//	�̵���
	short int		Charm;				//	�ŷ�
	short int		Endum;				//  �����
	short int		Moralm;				//	���
	short int		Luckm;				//	���
	short int		wspsm;
	
	unsigned int		StrTm;				//  ��   g_curr_time + 60
	unsigned int		ConTm;				//  �ǰ�
	unsigned int		DexTm;				//	��ø��
	unsigned int		WisTm;				//	����
	unsigned int		IntTm;				//	����
	unsigned int		MovePTm;				//	�̵���
	unsigned int		CharTm;				//	�ŷ�
	unsigned int		EnduTm;				//  �����
	unsigned int		MoralTm;				//	���
	unsigned int		LuckTm;				//	���
	unsigned int		wspsTm;
	
	
	//����, Armor, �Ǽ��縮 ,ETC �� ���� 	
	short int		Strw;				//  ��
	short int		Conw;				//  �ǰ�
	short int		Dexw;				//	��ø��
	short int		Wisw;				//	����
	short int		Intw;				//	����
	short int		MovePw;				//	�̵���
	short int		Charw;				//	�ŷ�
	short int		Enduw;				//  �����
	short int		Moralw;				//	���
	short int		Luckw;				//	���
	short int		wspsw;
	
	BYTE			item_Hit_Rate;
	BYTE			item_Deffence_Rate;
	
	
	// ��ü��ġ, �ð�(�๰). �ð�(����), ���. 
	// Magic.
	
	CCharRank		name_status;		// 0927 YGI
	
	
	short int		Ac;			// â AC( ���� )
	short int		AcDex;		// 0129 KHS
	short int		Att;		// ���ݷ�..
	short int		defence_rate;
	
	short int		Job;
	DWORD			Money;
	
	int		Hp;
	int		HpMax ;
	
	int		Mana;						// ������
	int		ManaMax;
	
	int		Hungry;	
	int		HungryMax;
	
	DWORD			mpmin;
	DWORD			hpmin;
	
	
	char			MapName[20];
	
	unsigned char	Peacests;
	int		Sight;		// YGI 020418
	
	
	short int		BodyR, BodyG, BodyB;		// �� ���� R.G.B
	short int		ClothR, ClothG, ClothB;		// �� ���� R.G.B
	
	short int		Age;
	
	// 010531 KHS	
	short int		nk[ MAX_NATION];							// ������ ��ȣ��(NK)
	
	
	DWORD			killmon;					// 1�迭���� ų����
	DWORD			killanimal;					// ���� ų����
	DWORD			killpc;						// ���,NPC ų����
	char			KillerName[ 31];
	//////////////////// 0117 lkh (�ڷ���) //////////////////////////
	//< CSD-010907
	/*
	float     	Resis_Poison;		//	��/���� ���׷�  _poinsion�� _poinson���� ���� 
	float				Resis_Stone	;		//	��ȭ ���� ���׷�
	float				Resis_Magic	;		//	�������׷�
	float				Resis_Fire	;			//	�� ���׷�
	float				Resis_Ice	;			//	�������׷�
	float				Resis_Elect	;		//	���������
	*/
	__int16 nPoison; // ���ְ迭 ������ ���� ���׷�
	__int16 nCurse;  // ���ְ迭 ������ ���� ���׷�	
	__int16 nFire;	 // �Ұ迭 ���� ������ ���� ���׷�
	__int16 nIce;		 // �����迭 ���� ������ ���� ���׷�
	__int16 nElect;	 // ���ݰ迭 ���� ������ ���� �����
	__int16 nHoly;	 // �ŷ°迭 ���� ������ ���� ���׷�
	//> CSD-010907
	////////////////////////////////////////////////////////////////
	
	
	DWORD			time_maintain1;		//  ����ȿ�����ӽð�
	DWORD			time_maintain2;		//  �ɷ�ȿ�����ӽð�
	DWORD			time_maintain3;		//	���º�ȯ����ȿ�� 
	unsigned char	Ws[200];			//	����
	unsigned char	Ps[200];			//	�Ź�
	
	unsigned char   Skill[200];
	DWORD			skillexp[45];		// 1219 YGI ����ġ
	
	
	
	
	
	
	// ���� ������ �ִ� ������..
	// �κ��丮
	ItemAttr	inv[3][3][8] ;
	// ����
	ItemAttr	equip[8] ;
	// �� 
	ItemAttr	quick[7] ;
	// �տ� ��� �ִ�
	ItemAttr	handheld ;
	// ���࿡ ����ǰ
	ItemAttr	bank[5][3][6];		//1225
	
	short int	Item[MAX_LEARN_ITEM];		// ����� �ִ� ������		1220
	short int	ItemMax;					// ���� ����� �ִ� ������ �ִ�ġ 1220
	
	int			itemweight;
	POS			SkillWork[ 20];
	
	//  Client�� ���� Data
	
	short int		SprNo;
	short int		SprType;	
	
	BYTE			accessory[4];
	short int		mantle;		// 011018 KHS ���� 
	DIRECTION		Direction;
	DWORD			IDWhoImAttacked;	// ���� ģ���� ������..
	short int		nCurrentAction;
	
	short int       ox, oy;		// �ڽ��� �¾���..
	short int		X, Y;
	short int		MovePathCount;
	short int		MoveLength;
	unsigned char	MoveType;
	short int		OldMoveSx,MoveSx;
	short int		OldMoveSy,MoveSy;
	unsigned char   MoveDirTbl[MAX_DIR_TABLE];
	short int		MoveGox;
	short int		MoveGoy;
	short int		Tox, Toy; // Ÿ���� ������ �и���. 
	
	
	int				path[ MAX_SHORTPATH][2];		// PathBuild()�� ���� ����..
	int				pathcount;
	
	// --------------  NPC Pattern---------- NPC������ ����..-
	short 			patterntype;
	short 			oldpatterntype;
	int				targetid;
	int				bossid;
	short			attackcount;
	DWORD 			aitimedelay;
	DWORD			aidelayhowmuch;
	int				tx, ty, how;// �̵��� ���õȻ���.
	int				attacked;
	bool			notcomeinside; // ���ȿ� ���� ����. 
	
	
	// 1207 khs �߰�.
	//  ------------------------------------- NPC�� ������ ������ �ִ� �͵�...
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
	DWORD					viewtype_treet;		// ������ ���� �ð�.
	DWORD					viewtype_cameleont;	// ī�᷹��    �ð�.
	DWORD					viewtype_catt;		// ����̰���  �ð�.
	
	short int				openhouse;
	short int				tame;				// tame��ġ...
	bool					tamed;
	short int				tamingable;
	short int				tamingcountdown;
	BYTE					tame_cmd;
	char					HostName[ 21]; // ������ �̸�...
	short int				HostId;
	char					TargetName[ 31]; // ������ ���� �������� �̸�.
	
	//	DWORD					pk;			// pk�� �ߴٸ� ����ð����� ū���� ������ �ִ� ! 
	short					pkid;		//
	short					pkcount;	// �� ��ġ�� 3�̻��̸� PK�� �Ѱ��̴� ! 
	DWORD					cast_pk;	// BroadCast�� �ð�.
	
	
	//------------------------   ���������� ����ϴ� para...
	DWORD			WalkTime;
	DWORD			desttime;
	
	// ********************************* �߰��� �׸��..
	// ��������.	
	//short int		Dam_Min, Dam_Max ;
	//short int		Def_Rate ;
	//short int		Hit_Rate ;
	char			disease[6];					
	
	
	//-----------------------------------------
	//short int		skillno;
	short int		cur_skillno; // ���� ����Ǳ� ���� �������� Skill...
	short int		cur_skillx;
	short int		cur_skilly;
	short int		cur_skilltargettype;
	short int		cur_skilltarget_id;
	POS				cur_skillPOS;
	DWORD			exetime_skill; // ����� Skill�� �ð�.
	
	
	
	
	
	short int		MaxWizardSpell ;
	short int		MaxPriestSpell ;
	
	short int		Weight, MaxWeight ;
	
	//	short int		Def_Correction ;				// ������ �� ��. ������ ������ ���⿡ �����ȴ�.
	//	bool			class_item_corr_flag ;			// Ŭ���� ����
	
	
	DWORD			tac_skillEXP[13] ;
	char			cur_tac_skill;					// ���� ������� �̷��������� Setting�Ǹ� ������� Index�� ����. ( TACTICS_Crapple....�� ���� )
	
	
	short	int 	reserved_point ;
	int				nAbilityPlusOfPotion[20];		//�Դ°ſ� ���� �Ŀ���
	DWORD			dwAbiliityPlusTime[20];
	//	int				nAbilityPlusOfWeapon[20];		//�����ۿ� ���ۿ� ���� �Ŀ���
	DWORD			DontDiseaseTime[6];             //������ �ɸ��� ���� �ð� 
	
	
	DWORD			BankMoney;
	DWORD			LastTotal;
	DWORD			LastLoan;
	DWORD			LastLoan_time;
	
	ItemAttr		box_item[MAX_BIX_ITEM];			// SQL�� ������ �ʿ� ����.. ���� ����..
	DWORD			box_id;							// ���� ���� �ִ� �ڽ��� ���� ID
	
	int				Defence;						// ����
	int				Aboidance;						// ȸ����
	DWORD			Ignore;							// ���� ȸ��...
	
	short int		Hungry_t;						// ���ʿ� �ѹ��� ������ ���ΰ�.. ����Ʈ 10��
	short int		Hungry_turn;					// 1�ʿ� �ѹ��� �� �Ҷ�.... ���
	float			Hungry_much;					// �ѹ� �������� �󸶳� ������ ���ΰ�.. ����Ʈ 5
	bool			HungryChangeFlag;
	
	
	
	
	
	
	
	// Chatting���� ���� ----------------
	char			chatname[ 31];
	char			chattype;
	short int		whisperid;
	// ----------------------------------
	
	
	/// ######### 0218 YGI ################
	// Party / Relation / Employment.........................	0213 YGI
	CharacterParty party[6];			
	CharacterParty relation[3];				
	CharacterParty employment[6];				
	
	//////////////////////////////////////// up_date��			
	char party_str[6][31];
	char relation_str[3][31];
	char employment_str[6][31];
	//############################################
	
	int partyrequestflag;
	
	
	//////////////////////// 0331 ���� ��ü���� LKH /////////////////////
	BYTE			Condition;			// 0����->CON_NORMAL, 1Ȱ����->CON_ACTIVE, 2�����->CON_SLUGGISH, 3���ο�->CON_SLOW, 4ȥ��->CON_DAZE, 5�ߵ�->CON_POISON, 6��ȭ->CON_STONE, 7����->CON_DEATH 
	DWORD			Condition_Time[8];	// ���� ���� �ð�;	
	
	BYTE			Status;				// ĳ������ �޽� ���� 0�� nomal		//0108
	
	
	//DWORD			doing_CheckTime;	// Ư�� ȿ���� �߻��ϴµ� �ɸ��� �ð�
	//short int		doing_Type;			// Ư��ȿ�� ������ȣ:1->����
	
	DWORD			DontPoison;			// �ߵ� ���¸� ������ ����
	DWORD			DontDaze;			// ȥ�� ���¸� ������ ����
	DWORD			DontSlow;			// �ӵ����� ���¸� ������ ����
	DWORD			Miner50Damage;		// ���������� 50% ����
	DWORD			Miner30Damage;		// ���������� 30% ����
	DWORD			Miner50Fire;		// �Ҹ��� �������� 50% ����
	DWORD			Miner30Fire;		// �Ҹ��� �������� 30% ����
	DWORD			Miner50Ice;			// ������ �������� 50% ����
	DWORD			Miner30Ice;			// ������ �������� 30% ����
	DWORD			Miner50Elect;		// ���ݸ��� �������� 50% ����
	DWORD			Miner30Elect;		// ���ݸ��� �������� 30% ����
	DWORD			Miner100Elect;		// ���ݸ��� ���� ���
	
	DWORD			DontCasting;		// ���� �Ұ�
	DWORD			DeathTime;			// �������� �̸��� �ð� ����
	DWORD			MinerSight;			// �þ߸� 2Ÿ�Ϸ� ����
	DWORD			Plus50Defence;		// ����� 50% ����
	DWORD			Plus50Avoid;		// ȸ���� 50% ����(����� ���� ����Ȯ���� ������)
	DWORD			DontDisease;		// ��� ������ �ɸ��� �ʴ´�.
	DWORD			DontEvilMagic;		// ��� ���� ������ ƨ�ܳ�
	DWORD			EvilToProtect;		// ����� ���(����)���κ��� ��ȣ(random�ϰ� 50~80% ��ȣ ����) & ��� ���� ��ġ���� ���� ������ ȿ���� ���� ����
	DWORD			Plus50AP;			// ���ݷ� 50% ����
	DWORD			Plus50Agility;		// ��ø�� 50% ����
	DWORD			AllSuccess;			// ��� �ൿ(���) ����
	
	DWORD			Plus50MagicHD;																
	DWORD			Plus100MagicHD;																
	
	DWORD			Plus100Ac;			// ������ ���� ��� ���� 100% ����
	DWORD			Miner30AP;			// ������(���ݷ�)30%����				*
	DWORD			Plus50Ac;			// ��������(ac)50%����	
	DWORD			Plus50Luck;			// ���ġ50%����
	DWORD			Plus100Defence;		// ��ü ����� 100% ����
	/////////////////////////// ������� ///////////////////////////////
	
	////////////// 0410 lkh �߰� //////////////
	DWORD		ReturnMagic;		//	������ ȿ���� �����ڿ��� �ǵ���
	
	
	//////////// 0125 YGI ///////////// ������ �ŷ�
	K_ITEM		give[20];		// ���� ��� �ϴ� ������
	K_ITEM		recv[20];		// ���� �޾ƾ� �ϴ� ������ 
	short int	target_id;		// �ŷ� ���
	bool		trade_on;		// �ŷ��ϰ� �ִ��� ������...
	
	DWORD		timetoupdate;	
	
	char		updatable;		
	int			balancingtest;
	
	DWORD		DontDamage;		
	
	
#ifdef _GAME_SERVER_
	AREA		area_tbl[MAX_AREA_BUFFER];
#endif
	
	
	bool		counseler;		// counseler�� Ÿ���� ���� �ʴ´�. 
	
	int			ctrlpc;			// NPC�ϰ�� ���� �����ϴ� NPC�� ID, ���� ��� -1�� ������ �ִ�.
	int			ctrlnpc[MAX_PC_CONTROL_NPC];		
	
	
	
	/////////////// 0315 lkh �߰� ////////////////
	DWORD		DontAttack;			// �Ϲݰ��ݺҰ�
	DWORD		AmplifyMagic;		// ���ݸ����� �������� 1.5�� �þ
	DWORD		Transparency;		// �����ΰ� ���ӽð�
	
	DWORD		AllCanCleMagic;		//	��� ������ ƨ�ܳ�
	DWORD		RangeWeaponProtect; //	��� ��Ÿ�(�񹫱�)�� ���� ���� ��ȣ
	DWORD		SpeedUp;			//  ���� �ӵ��� 1/2��ŭ �� ������
	int			ProtectField_X;		//	���� ����� Ÿ���߽���ǥ
	int			ProtectField_Y;		//             "
	DWORD		ProtectField;		//	���� ����� ����ó��
	///////////////////////////////////////////////
	
	// 0405 YGI
	char		believe_god;		// ���� �ϴ� ��
	short int	faith;				// �žӽ�
	char		preach_name[20];	// ������ ����� �̸�
	
	short int	god_cast_level;		// ���� �ֹ� �н� �ܰ�	// 0410	YGI	// sql ���� �ʿ�
	bool		in_temple;			// �����ȿ� �ִ�		// 0410	YGI	// sql ���� �ʿ� ����
	int			is_god_meeting;		// ���� �������̴�		// 0410	YGI	// sql ���� �ʿ� ����
	DWORD		god_meeting_start_time;	// ���� ������ �ð�	// 0410	YGI	// sql ���� �ʿ� ����
	bool		i_go_year_meeting;		// ���� ���迡 ����.// 0410	YGI	// sql ���� �ʿ� ����
	bool		i_go_month_meeting;		// ���� ���迡 ����.// 0410	YGI	// sql ���� �ʿ� ����
	bool		i_go_day_meeting;		// ���� ���迡 ����.// 0410	YGI	// sql ���� �ʿ� ����
	
	DWORD		can_memorize_time;		// ������ �ð�	// ������ �ʿ� ����  0414 YGI
	
	short int		startposition;
	short int		startmap;
	
	//////////////////////////////////  ���� �ý���...
	
	char        dualname[20];
	char        dualstatus;	// 0: No Dual    1: ��û�ѻ���..   2: ������.
	
	DWORD		dualvictory;	
	DWORD		dualfail;	
	DWORD		dualdraw;	
	
	// 010406 YGI
	DWORD			LadderScore;		// �ݷμ��� ���� ����
	WINLOSEPOINT	WinLoseScore;		// �ݷμ��� ����
	//< CSD-010907
	char aStepInfo[20];
	//> CSD-010907
	int				nUserAge;			// 030923 kyo
	Event_Join		EventJoin;			// 020115 LTS
} CHARLIST, *LPCHARLIST;		

#define		HUNGRY_TIME		60		// 1��  //###1213_2 ����
#define		HUNGRY_MUCH		1.0	



// ���� ���̺�	//0104
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



//////////////// 0405 YGI	���� ���̺�
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


