


#define NPC_PATTERN_NO_MOVE_			 0		// ������ �ִ´�.
#define NPC_PATTERN_HOSTILE_			10		// ���������� �ٲ��. 
#define NPC_PATTERN_PEACE_				20		// ��ȭ������ �ٲ��.
#define NPC_PATTERN_FIND_CLOSE_PC_		30		// ����� pc�� ã�´�.(������ �ٶ󺻴�. )
#define NPC_PATTERN_FIND_WEAK_PC_		40		// ����  pc�� ã�´�.(������ �ٶ󺻴�. )
#define NPC_PATTERN_FIND_STRONG_PC_		50		// ����  pc�� ã�´�.(������ �ٶ󺻴�. )
#define NPC_PATTERN_ACCESS_PC_			60		// ã�� PC�� �����Ѵ�. ( Hostile�ϰ�� ���ݹ����� ������ �����Ѵ�. peace�ϰ�� �����ص� ������ �����ϴ³��� �ٶ󺻴�.  
#define NPC_PATTERN_ACCESS_PC_ATTACKED_	70		// ���� ������ Pc�� �����Ѵ�. 
#define NPC_PATTERN_ATTACK_PC_			71
#define NPC_PATTERN_WANDER_RANGE_1_		80		// ��ȸ�Ѵ�. ( 1�� ��ȸ������ 1�̴�. )
#define NPC_PATTERN_WANDER_RANGE_2_		90		// ��ȭ�Ѵ�. ( 1�� ��ȸ������ 2�̴�. )
#define NPC_PATTERN_WANDER_RANGE_3_		100  	// ��ȭ�Ѵ�. ( 1�� ��ȸ������ 3�̴�. )
#define NPC_PATTERN_ESCAPE_PC_			110		// ã�� PC�� ���� ��������. 
#define NPC_PATTERN_ESCAPE_BATTLE_PC_	120		// ��ó�� ���� PC�� ������ �ָ� ��������. 
#define NPC_PATTERN_RETURN_				130		// patterntype�� 0���� Setting�Ѵ�.



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















