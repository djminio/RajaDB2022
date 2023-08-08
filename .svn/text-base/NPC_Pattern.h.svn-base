


#define NPC_PATTERN_NO_MOVE_			 0		// 가만히 있는다.
#define NPC_PATTERN_HOSTILE_			10		// 적대적으로 바뀐다. 
#define NPC_PATTERN_PEACE_				20		// 평화적으로 바뀐다.
#define NPC_PATTERN_FIND_CLOSE_PC_		30		// 가까운 pc를 찾는다.(그쪽을 바라본다. )
#define NPC_PATTERN_FIND_WEAK_PC_		40		// 약한  pc를 찾는다.(그쪽을 바라본다. )
#define NPC_PATTERN_FIND_STRONG_PC_		50		// 강한  pc를 찾는다.(그쪽을 바라본다. )
#define NPC_PATTERN_ACCESS_PC_			60		// 찾은 PC에 적근한다. ( Hostile일경우 공격범위에 있으면 공격한다. peace일경우 접근해도 가만히 접근하는놈을 바라본다.  
#define NPC_PATTERN_ACCESS_PC_ATTACKED_	70		// 나를 공격한 Pc에 접근한다. 
#define NPC_PATTERN_ATTACK_PC_			71
#define NPC_PATTERN_WANDER_RANGE_1_		80		// 배회한다. ( 1번 배회범위가 1이다. )
#define NPC_PATTERN_WANDER_RANGE_2_		90		// 배화한다. ( 1번 배회범위가 2이다. )
#define NPC_PATTERN_WANDER_RANGE_3_		100  	// 배화한다. ( 1번 배회범위가 3이다. )
#define NPC_PATTERN_ESCAPE_PC_			110		// 찾은 PC로 부터 도망간다. 
#define NPC_PATTERN_ESCAPE_BATTLE_PC_	120		// 근처에 공격 PC가 있으면 멀리 도망간다. 
#define NPC_PATTERN_RETURN_				130		// patterntype을 0으로 Setting한다.



#ifndef __NPC_PATTERN_H__
#define __NPC_PATTERN_H__



/////////////////////////////////////////////////////////////
///  Variables

	extern int NpcPatternTable[20];

/////////////////////////////////////////////////////////////
///  User Function

	extern void InitMoveDelayTable( void );
	extern void CharacterMoving( CHARLIST *c );
	extern void CreateCharacter( t_connection c[], int cn, t_packet *packet);

	extern int  IsInArea( CHARLIST *s, CHARLIST *d );
	extern void UserAddBasicData(  t_connection c[], int i, t_server_user_add * p  );
	extern void NPCAddBasicData(  int i, t_server_npc_add *p );

	extern void NPCGeneratePosition( int npcindex, int x, int y );
	extern void NPC_Create( int Num, int npcindex, int x, int y );


	extern void NPC_AutoCreationProc( void );
#else



#endif















