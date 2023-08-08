//#define _GAME_SERVER_


//#define _SERVER_MAKE_MODE_



#include "stdafx.h"
/*
#include <windows.h>
#include <windowsx.h>
//#include <winsock2.h>

  #include <stdio.h>
  #include <stdlib.h>
  #include <conio.h>
  #include <io.h>
*/
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sqlext.h>
#include <winerror.h>




#ifdef _GAME_SERVER_

#include <ddraw.h>
#include <dsound.h>

#include "DEBUG.H"
#include "CINFO.H"
#include "CSURF.H"
#include "CENGINE.H"
extern CSurface WndSurface;
#endif
#include "map.h"		// 1004 YGI
#include "CHARLIST.H"
#include "NETWORK.H"

#include "ITEMLIST.H"
#include "MYSQL.H"
#include "Hong_Sub.h"
#include "OP_Chr_Status.h"


#ifdef _GAME_SERVER_

#include "NPCLIST.H"
#include "Object.h"
#include "NPC_Pattern.h"
#include "AREA.H"
#include "Skill.h"


#else

#define SetArea(a,b)	

#endif




extern DWORD global_time;
extern DWORD g_start_time;
extern DWORD g_alive_time;
extern DWORD g_curr_time;
extern DWORD g_weather_time;

extern int g_closed_gameserver;
extern int g_year;
extern int g_mon;
extern int g_day;
extern int g_yday;
extern int g_hour;
extern int g_min;
extern int g_sec;

extern int g_count_ok;
extern int g_weatherflag;

extern int g_total_gameserver, g_current_gameserver;
extern int g_gameserver_check_start; 

extern int		StartMap, StartPosition;
extern char		StartMapPosition[ 5][20][20];




/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagMAGICTABLE							//마법 테이블 구조체
{
	//	int				grouping;		//사용가능한 사람 분류(0->누구나/1->마법사계만/2->성직자계만)	
	int				serial_Num;		//고유번호(1~)
	int				order_Type;		//계열(1->생/2->사/3->일반/4->화염/5->얼음/6->전격/7->소환/8->시공/9->신성/10->정동/11->정념/12->특수)
	int				appoint_Type;		//대상 지정방식 타입(0->나자신/1->대상지정(단일대상)/2->대상지정(복수대상)/3->지역마법)
	int				basic_Level;		//사용 기본 레벨(1~9)
	int				point_MS;		//Magic S point 
	int		        before_Magic;		//전 단계 마법(먼저 익혀야 할 마법)
	int				cast_Time;		//캐스팅 시간(절대시간)
	int				cast_Continue;	//캐스팅 지속 시간(절대시간)
	int				continue_Time;	//지속시간(0->영원히/1~절대시간)
	int				avail_Type;		//효용 타입(0->자신/1->자신 아닌 1명/2~->유효범위내 다수)
	int				avail_Range;	//사정거리(타일단위/0->자신/99->무한)
	int				exhaust_MP;		//소모 MP
	int				exhaust_MS;		//소모 MS
	int				require_IT;		//요구 지능
	int				require_WP;		//요구 지혜
	int				point_Hit;		//명중률(0->100%,1~->해당 명중률)
	int				point_Attract;	//매력 포인트(0->not available/1~)
	int				point_WS;		//WS 포인트(0->not available/1~)
	int				point_Move;		//이동포인트(0->not available/1~)
	bool			invalid_MagicZone;	//마력무효지역
	bool			invalid_SpriteZone;	//신력무효지역
	bool			invalid_SummonZone;	//소환불가지역
	bool			invalid_HolyZone;	//신성지역
	int				invalid_TargetIT;	//마법 무효화 대상체 지능치
	int				invalid_TargetWP;	//마법 무효화 대상체 지혜치	
	int				invalid_TargetHP;	//마법 무효화 대상체 건강치
	int				invalid_TargetSP;	//마법 무효화 대상체 SP
	bool			invalid_Night;		//마법 무효화 -> 밤
	bool			invalid_Day;		//마법 무효화 -> 낮
	bool			invalid_Fire;		//마법 무효화 -> 불
	int				difference_IT;		//대상체와의 지능 차이
	int				difference_WP;		//대상체와의 지혜 차이
	bool			invalid_Rain;		//마법 무효화 -> 비
	bool			invalid_Snow;		//마법 무효화 -> 눈
	bool			invalid_Fog;		//마법 무효화 -> 안개
	bool			invalid_IceMagic;	//마법 무효화 -> 얼음마법
	bool			invalid_FireMagic;	//마법 무효화 -> 화염마법
	bool			invalid_BoltMagic;	//마법 무효화 -> 전격마법
	char			startMagic_Word[8];	//마법시동어
	
	int				reserve1;		//예비 맴버 변수
	int				reserve2;		//      "
	bool			flag;			//예비 플레그
	
	int				basic_magery ;		//
	int				Rain_Corr ;			// 보정값들... 단위(%)
	int				Fog_Corr ;
	int				Night_Corr ;
	int				Spell_Type ;		// 0 Wizard, 1~13 priest(God별 type들 때문에 다양
	int				Appoint_Type ;
} MAGICTABLE;

typedef struct tagNPC_Info 
{ // 153개 임.
	short int	sprno ;
	short int	face ;
	short int	race ;
	short int	spritvalue ;
	short int	Class ;
	short int	class_sprituality ;
	short int	class_poisoning ;
	short int	class_bombplay ;
	short int	class_entrapment ;
	short int	class_scrolling ;
	short int	class_cunning1 ;
	short int	class_cunning2 ;
	short int	class_cunning3 ;
	short int	class_stealing ;
	short int	job ;
	short int	age ;
	short int	lev ;
	short int	hd ;
	int	exp ;
	short int	pspow ;
	short int	wspow ;
	short int	divpow ;
	short int	manapow ;
	short int	orsnpow ;
	short int	mjypow ;
	short int	attackpow ;
	short int	vitalpow ;
	short int	hungrymax ;
	short int	money ;
	short int	strold ;
	short int	conold ;
	short int	dexold ;
	short int	wisold ;
	short int	intold ;
	short int	movepold ;
	short int	charold ;
	short int	enduold ;
	short int	healthold ;
	short int	moralold ;
	short int	luckold ;
	short int	condition ;
	__int16 nPoison; // 저주계열 마법에 대한 저항력
	__int16 nCurse; // 저주계열 마법에 대한 저항력	
	__int16 nFire;	 // 불계열 공격 마법에 대한 저항력
	__int16 nIce;		 // 얼음계열 공격 마법에 대한 저항력
	__int16 nElect;	 // 전격계열 공격 마법에 대한 저향력
	__int16 nHoly;	 // 신력계열 공격 마법에 대한 저항력
	short int	ws[10] ;
	short int	ps[10] ;
	int	acc_equip[6] ;
	short int	normal_sight ;
	short int	battle_sight ;
	short int	invtry[15] ;
	short int	tactics ;
	short int	CRAPPLE ;
	short int	SWORDMANSHIP ;
	short int	ARCHERY ;
	short int	FENCING ;
	short int	MACEFIGHTING ;
	short int	PIERCE ;
	short int	WHIRL ;
	short int	HURL ;
	short int	PARRING ;
	short int	DOUBL_SWORDMANSHIP ;
	short int	DOUBL_MACEFIGHTING ;
	short int	cooper ;
	short int	MORDERATION ;
	short int	royal ;
	short int	courage ;
	short int	faith ;
	short int	truth ;
	short int	justice ;
	short int	mercy ;
	short int	murder ;
	short int	robery ;
	short int	betrayal ;
	short int	disroyal ;
	short int	greed ;
	short int	idol ;
	short int	r_fame ;
	short int	r_truth ;
	short int	r_bow ;
	short int	r_propagation ;
	short int	r_service ;
	short int	nor_range ;
	short int	att_range ;
	short int	enemy_no ;
	short int	party ;
	short int	levelgap ;
	short int	offset ;
	short int	apgap ;
	short int	vpgap ;
	short int	attackpattern ;
	short int	partyattack ;
	short int	afterattack ;
	short int	attackend ;
	short int	opendoor ;
	short int	lockdoor ;
	short int	closedoor ;
	short int	breakobj ;
	short int	pickobj ;
	short int	openbox ;
	short int	lockbox ;
	short int	closebox ;
	short int	pathrange ;
	short int	neglect ;
	short int	checklevel ;
	short int	absolattack ;
	short int	stop ;
	short int	backdown ;
	short int	act_month ;
	short int	act_space ;
	short int	act_time ;
	short int	act_weather ;
} NPC_Info ;

typedef struct tagNPCName_by_Gender
{
	char Female[17] ;
	char Male[17] ;
	char Last[17] ;
} NPCName_by_Gender ;

struct NPCLev_to_Exp
{	//< CSD-TW-030606
	int nMinExp;         // 현재 레벨의 최소 경험치
	int nMaxExp;         // 현재 레벨의 최대 경험치
	int nNeedExp;        // 다음 레벨로 올라가기 위해 획득해야될 경험치
	int nTrainingExp;    // 택틱 수련장에서 얻는 경험치
	float fExpReduction; // 사냥시 죽었을 경우 경험치 삭감률
	float fNKReduction;	 // NK에 죽었을 경우 경험치 삭감률
	int nTacRate;		 // 택틱 보정치
	int nMaxTactic;	     // 레벨에 따른 택틱 수련장에서 올릴 수 있는 최대 택틱 레벨
	int	nDyeingPrice;    // 염색 가격
	int nLessRate;       // 낮은 레벨 보정치  
	int nGreatRate;      // 높은 레벨 보정치  
	int nCspMax;         // 최대 전투스킬 포인터 획득수
	int nBaseCP;         // 전투스킬 기본량
	int bank_loan;	     // 010314 YGI
	int nStep;           // 경험치 단계
	int nWarriorLife;    // 전사의 기본 Life
	int nThiefLife;      // 도둑의 기본 Life
	int nArcherLife;     // 궁수의 기본 Life
	int nWizardLife;     // 마법사의 기본 Life
	int nPriestLife;     // 성직자의 기본 Life
	int nWarriorExpRate; // 전사의 경험치 보정률(단위%)
	int nThiefExpRate;   // 도둑의 경험치 보정률(단위%)
	int nArcherExpRate;  // 궁수의 경험치 보정률(단위%)
	int nWizardExpRate;  // 마법사의 경험치 보정률(단위%)
	int nPriestExpRate;  // 성직자의 경험치 보정률(단위%)
};	//> CSD-TW-030606

typedef struct tagNPC_Generation 
{
	short int SprNO;
	char Han_name[31];
	char Name[31];
	short int Selectable;
	short int Sel_gender;
	short int Sel_FirstName[31];
	char Sel_LastName[31] ;
	short int Sel_race;
	short int Sel_Class_Warrior;
	short int Sel_Class_Thief;
	short int Sel_Class_Archery;
	short int Sel_Class_Wizard;
	short int Sel_Class_Priest;
	short int Sel_Job_Farmer;
	short int Sel_Job_Miner;
	short int Sel_Job_FishHooker;
	short int Sel_Job_Lumberjack;
	short int Sel_Job_Butcher;
	short int Sel_Job_Herbdigger;
	short int Sel_Job_Herdman;
	short int Sel_Job_Carpenter;
	short int Sel_Job_Blacksmith;
	short int Sel_Job_Cooker;
	short int Sel_Job_Tailor;
	short int Sel_Job_BowFlet;
	short int Sel_Job_Alchemist;
	short int Sel_Job_Candlemaker;
	short int Sel_Job_Merchant;
	short int Sel_Age_Min;
	short int Sel_Age_Max;
	short int Sel_Lv_min;
	short int Sel_Lv_Max;
	short int Sel_Tactics;
	short int Sel_Spell;
	short int Money_min;
	short int Money_Max;
	short int Bear_Peoriod;
	short int Bear_amount;
	short int Bear_Succes;
	short int Bear_Do;
	short int Bear_Probability;
	short int Bear_Checktime;
	short int Moderation;
	short int royal;
	short int Courage;
	short int Faith;
	short int Truth;
	short int Justice;
	short int Mercy;
	short int Muder;
	short int Robery;
	short int Betrayal;
	short int Disroyal;
	short int Greed;
	short int idol;
	short int Reputaion;
	short int Reputaion_range;
	short int SpiritValue;
	short int SpiritValue_Range;
	short int PS[15] ;
	short int Sel_Dice;
	short int QuantityperLv;
	short int WS[15] ;
	short int Sel_Dice1;
	short int QuantityperLv1;
	short int Leathal_weapon1;
	short int Leathal_weapon2;
	short int Damage_weapon;
	short int Leathal_attackws[9] ;
	short int Damage_WP;
	short int Leathal_WS;
	short int Success;
	short int Leathal_ps;
	short int DamagePercent_ps;
	short int Inventory[15] ;
	short int Amount_Dice;
	short int Righthand;
	short int Lefthand;
	short int Body;
	short int Helmet;
	short int leg;
	short int Leg_Probability;
	short int neck;
	short int neck_Probability	;
	short int unique1;
	short int Unique1_probalbility;
	short int Unique2;
	short int unique2_probability	;
	short int Crapple;
	short int swordmanship;
	short int Archery;
	short int Fencing;
	short int Mace_fighting;
	short int Pierce;
	short int Whirl;
	short int Hurl;
	short int Parrying;
	short int Double_Swordmanship	;
	short int Double_MaceFighting	;
	short int Magery;
	short int Orison;
	short int LV_Str;
	short int Con;
	short int Dex;
	short int Wis;
	short int Int;
	short int Movp;
	short int Char;
	short int Endu;
	short int Mor;
	short int Luck;
	short int WS_PS;
	short int Fullpoint;
	__int16 nPoison; // 저주계열 마법에 대한 저항력
	__int16 nCurse;  // 저주계열 마법에 대한 저항력	
	__int16 nFire;	 // 불계열 공격 마법에 대한 저항력
	__int16 nIce;		 // 얼음계열 공격 마법에 대한 저항력
	__int16 nElect;	 // 전격계열 공격 마법에 대한 저향력
	__int16 nHoly;	 // 신력계열 공격 마법에 대한 저항력
	short int DivideLv;
	short int Resist_Range;
	short int Tamingable;
	short int Taming_min;
	short int Taming_max;
	short int Talkanimal_min;
	short int Talkanimal_max;
	short int Resist;
	short int Resist_range1;
	short int ValueHP;
	short int ValueSP;
	short int Rely_value;
	short int nor_range;
	short int att_range;
	short int offset[20] ;
	short int neglect_attack;
	short int neglect_avoid;
	short int check_pass;
	short int party;
	short int enemy_no;
	short int levelgap;
	short int apgap;
	short int vpgap;
	short int opendoor;
	short int lockdoor;
	short int closedoor;
	short int breakdoor;
	short int openobj;
	short int lockbj;
	short int closeobj;
	short int breakobj;
	short int act_month;
	short int act_time;
	short int act_bi;
	short int act_chun;
	short int act_nun ;
} NPC_Generation ;



//######## tactics 에 사용 #############
#define		CRAPPLE_			0
#define		SWORD_				1
#define		ARCHERY_			2		
#define		FENCING_			3
#define		MACE_				4	
#define		PIERCE_				5		
#define		WHIRL_				6		
#define		HURL_ 				7		
#define		PARRYING_			8	
#define		D_SWORD_			9			
#define		D_MACE_				10		
#define		MAGERY_				11
#define		ORISON_				12




/// CHARLIST ch->type 에서 사용...
#define	SPRITETYPE_NONE				0
#define	SPRITETYPE_CHARACTER		1
#define	SPRITETYPE_NPC				2
#define	SPRITETYPE_MONSTER			3


#define Num_Of_NPC_Type 100
#define	Num_Of_NPC_Name	984
#define	Num_Of_NPC_Lev	256
#define Num_Of_NPC_Generation	90

#define STR		0		//1213_2
#define DEX		1
#define CON		2
#define WIS		3
#define INT		4
#define CHA		5
#define MOVP	6
#define ENDU	7
#define MOR		8
#define WSPS	9
#define LUCK	10

#define HEALTH	11
#define MOV		12
#define AC		13
#define FAME	14
#define DAMAGE	15
#define HIT		16
#define TACTICS	17
#define MONEY	18

#define IMSI	19

#define LEV		20
#define EXP		21
#define HP		22
#define MAX_HP	23

#define MP		24
#define MAX_MP	25
#define SP		26
#define MAX_SP	27
#define CONDI	28
#define R_POI	29
#define R_PAR	30
#define R_MAG	31
#define R_FIR	32
#define R_ICE	33
#define R_ELE	34

#define DAM_MIN	35
#define DAM_MAX	36
#define HIT_RAT	37
#define DEF_RAT	38

#define TAC_S1	39
#define TAC_S2	40
#define TAC_S3	41
#define TAC_S4	42
#define TAC_S5	43
#define TAC_S6	44
#define TAC_S7	45
#define TAC_S8	46
#define TAC_S9	47
#define TAC_S10	48
#define TAC_S11	49
#define TAC_S12	50

#define TAC_E1	51
#define TAC_E2	52
#define TAC_E3	53
#define TAC_E4	54
#define TAC_E5	55
#define TAC_E6	56
#define TAC_E7	57
#define TAC_E8	58
#define TAC_E9	59
#define TAC_E10	60
#define TAC_E11	61
#define TAC_E12	62

// exp inc. decision criteria
#define HIT_FAILED		0
#define HIT_AND_DEAD	1
#define HIT_AND_NOTDEAD	2



#define  N_VYSEUS		3
#define  N_ZYPERN		4
#define  N_HEGEMONIA	5
#define  N_YILSE		6 

///////////////////////// 이규훈 1228 //////////////////////////
/////////////////// 상태를 나타내는 비트 정의 ///////////////////
#define		CON_NORMAL		0x00		//정상상태			0
#define		CON_ACTIVE		0x01		//활동적상태		1
#define		CON_SLUGGISH	0x02		//무기력상태	   10		
#define		CON_SLOW		0x04		//슬로우상태	  100	
#define		CON_DAZE		0x08		//혼란상태		 1000	
#define		CON_POISON		0x10		//중독상태		10000
#define		CON_STONE		0x20		//석화상태	   100000
#define     CON_DEATH		0x40		//죽음상태	  1000000

const int MAX_UPDATE_CHARACTER_	= 30000; // CSD-030320
const int MIN_GUILD_COUNT = 10;  // CSD-030320
//Skill No
enum eSkillNoIndex
{	//< CSD-030306
	SKILL_UNKNOWN							=0,	// 030117 kyo 
	SKILL_DETECT_GHOST						=1,	
	SKILL_TALK_WITH_GHOST					=2,	
	SKILL_POISONING							=3,	
	SKILL_DETECT_POISON						=4,	
	SKILL_FIND_TRAPS						=5,	
	SKILL_REMOVE_TRAPS						=6,	
	SKILL_ENTRAPMENT						=7,	
//	SKILL_MAGIC_SCROLLING					=8,	
//	SKILL_ABILITY_SCROLLING					=9,	
//	SKILL_EMERGENCY_ALRAM					=10,	
//	SKILL_FIRST_AID							=11,	
//	SKILL_FAST_FOOT							=12,	
//	SKILL_SECRETHEAR						=13,	
//	SKILL_WALLCLIMBING						=14,	
//	SKILL_INTUITION							=15,	
	SKILL_DETECT_BOMB						=16,	
	SKILL_BOMB_IN_BOX						=17,	
	SKILL_REMOVE_BOMB						=18,	
	SKILL_STEALING							=19,	
//	SKILL_LOCKPICKING						=20,	
	SKILL_RECLAIM							=21,	
	SKILL_SOW								=22,	
//	SKILL_CULTIVATE							=23,	
	SKILL_HAVEST							=24,	
//	SKILL_DETECT_MINERAL					=25,	
	SKILL_MINING							=26,	
	SKILL_REFINE							=27,	
	SKILL_FISH_HOOKING						=28,	
//	SKILL_BAITMAKING						=29,	
	SKILL_NETTING							=30,	
//	SKILL_SAILING							=31,	
	SKILL_CUTTING							=32,	
	SKILL_LUMBERING							=33,	
	SKILL_BUTCHERING						=34,	
//	SKILL_DETECT_HERB						=35,	
	SKILL_DIGGING							=36,	
	SKILL_MAKEPOWDER						=37,	
//	SKILL_HERDING							=38,	
//	SKILL_MILKING							=39,	
//	SKILL_MIDWIFERY							=40,	
	SKILL_SHEAR								=41,	
	SKILL_CARPENTRY							=42,	
	SKILL_BLACKSMITHY						=43,	
	SKILL_COOKING							=44,	
	SKILL_CLOTHING							=45,	
//	SKILL_DYEING							=46,	
	SKILL_TAILORING							=47,	
	SKILL_BOWCRAFTING						=48,	
	SKILL_FLETCHING							=49,	
	SKILL_MAKEPOTION						=50,	
	SKILL_MAKEMETAL							=51,	
	SKILL_MAKEBOTTLE						=52,	
	SKILL_CANDLEMAKING						=53,	
//	SKILL_WAXING							=54,	
//	SKILL_REPAIRNG							=55,	
//	SKILL_REUTILIZING						=56,	
//	SKILL_PLAYING							=57,	
//	SKILL_PEACEMAKING						=58,	
//	SKILL_PARALYSIS							=59,	
//	SKILL_HALLUCINATION						=60,	
//	SKILL_PROVOCATION						=61,	
//	SKILL_ENTICEMENT						=62,	
//	SKILL_NOISE								=63,	
//	SKILL_TRACKING							=64,	
	SKILL_SNOOPING							=65,	
//	SKILL_SEARCH							=66,	
	SKILL_MERCHANT							=67,	
	SKILL_BLACKSMITHY_MASTER				=68,	//대장장이 기성	
	SKILL_CARPENTRY_MASTER					=69,	//목수 기성	
	SKILL_BOWCRAFTING_MASTER				=70,	//활제작사 기성	
	SKILL_TAILORING_MASTER					=71,	//재단사 기성
//	SKILL_HIDE								=72,	
//	SKILL_CAMPING							=73,	
	SKILL_MAKEFIRE							=74,	
	SKILL_TAMING							=75,	
//	SKILL_COMMUNICATE_WITH_ANIMAL			=76,	
//	SKILL_COMMUNICATE_WITH_OTHER_TRIBE		=77,	
//	SKILL_ANIMAL_LORE						=78,	
//	SKILL_ARMS_LORE							=79,	
	SKILL_EVALUATE_INTELIGENCE				=80,	
	SKILL_EVALUATE_WISDOM					=81,	
	SKILL_ANATOMY_JUDGEMENT					=82,	
	SKILL_ITEM_IDENTIFICATION				=83,	
//	SKILL_TASTE_IDENTIFICATION				=84,	
//	SKILL_APPRAISAL							=85,	
//	SKILL_HEALING							=86,	
	SKILL_TACTICS							=87,//021113 lsw
	TACTICS_Crapple							=88,
	TACTICS_swordmanship					=89,
	TACTICS_Archery							=90,
	TACTICS_Fencing							=91,	
	TACTICS_Mace_fighting					=92,
	TACTICS_Pierce							=93,
	TACTICS_Whirl							=94,
	TACTICS_Hurl							=95,
	TACTICS_Parrying						=96,
	TACTICS_Double_Swordmanship				=97,
	TACTICS_Double_MaceFighting				=98,	
	TACTICS_Magery							=99,
	TACTICS_Orison							=100,
//	SKILL_THREAD							=101,	
//	SKILL_COLORING							=102,	
//	SKILL_JUMP								=103,	
//	SKILL_RIDING							=104,	
	SKILL_GHOST_RESURRECTION				=105,	
	SKILL_GM_CARPENTER						=106,	
	SKILL_GM_BLACKSMITH						=107,	
	SKILL_GM_COOK							=108,	
	SKILL_GM_TAILOR							=109,	
	SKILL_GM_BOWCRAFT						=110,	
	SKILL_GM_ALCHEMIST						=111,	
	SKILL_GM_CANDLEMAKER					=112,	
};	//> CSD-030306

extern int init_login_main( void );
extern int run_login_main(void);
extern void end_login_main( void );
extern void prepare(t_connection c[]);
extern NPCLev_to_Exp NPC_Lev_Ref[Num_Of_NPC_Lev]; // CSD-TW-030606
const int MAX_EXP_LEVEL = 150; // CSD-TW-030606
const int MAX_TAC_LEVEL = 199; // CSD-TW-030606

