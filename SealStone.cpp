#include "StdAfx.h"
#include "MAIN.H"
#include "MyLog.H"

	
	
#define __SEALSTONE__
#include "SealStone.h"
	
	
	
//--------------------------------------------------------------------
//	
//   User Functions..
//	
	
/*---------------------------------------------------------------------
	���� �����ǰų� 
    ���� �μ����� ���Ӽ������� �����ش�. 
	
  status : 0 --> �μ���   1 : ������..
---------------------------------------------------------------------*/
void RecvSealStoneStatus( t_packet *p )
{	
	t_sealstone_status *tp;
	int status = 0;
	int i;
	
	tp = &p->u.sealstone_status ;

	switch( tp->status )
	{
		// Ÿ���� �޾Ҵ�. 
	case 2 :		
		// �׾���. 
	case 0 :		status = 0;		break;
		// �ǻ�Ƴ���. 
	case 1 :		status = 1;		break;
	}

	switch( tp->sealstonesprno )
	{
		// ���̼���
	case 98 :	SealStone[ N_VYSEUS].status[tp->id] = status;
		break;
		// ������
	case 99 :	SealStone[ N_ZYPERN].status[tp->id] = status;
		break;
	}

	if( status == 0 )
	{
		for(i = 0; i < LOGIN_MAX_CONNECTIONS; ++ i)
				if( connections[i].server_check )
					QueuePacket( connections, i, p, 1 );

		::MyLog(0,"RecvSealStoneStatus");

	}
}	
	
/*---------------------------------------------------------------------
	���� �������� �ߴ�.	->  ��輮�� �����ɶ����� �Ҽ� ������
	�����ϸ� �������� �ߴٴ� �޽����� ���
---------------------------------------------------------------------*/
void RecvSealStoneFromKing( int nation )
{	
	if( SealStone[ nation].regentime ||  SealStone[ nation].waraftertime ) return; // �����ϴµ��ȿ��� �ٽ� �������� ���� �ʴ´�. 
	SealStone[ nation].warlefttime = g_curr_time + SEALSTONE_WARTIME_;
	
	t_packet p;
	int i;
	
	p.h.header.type = CMD_SEALSTONE_WAR_START;
	p.h.header.size = sizeof( t_sealstone_war_start);
	p.u.sealstone_war_start.nation = nation;
	
	for(i = 0; i < LOGIN_MAX_CONNECTIONS; ++ i)
			if( connections[i].server_check )
				QueuePacket( connections, i, &p, 1 );
}	
	
	
void SendResultNationWar( int aresult, int anation, int bresult, int bnation )
{	
	t_packet p;
	int i;
	
	p.h.header.type = CMD_SEALSTONE_RESULT;
	p.h.header.size = sizeof( t_sealstone_result );
		p.u.sealstone_result.aresult = aresult;
		p.u.sealstone_result.anation = anation;
		p.u.sealstone_result.bresult = bresult;
		p.u.sealstone_result.bnation = bnation;
	for(i = 0; i < LOGIN_MAX_CONNECTIONS; ++ i)
			if( connections[i].server_check )
				QueuePacket( connections, i, &p, 1 );
}	
	
// ���� ��輮�� �����ɰ��̰� ��а� ��輮�� �μ��� ����. 
void SendSealStoneReGenStart( void )
{	
	int i;		
	t_packet p;	
				
	p.h.header.type = CMD_SEALSTONE_START_RE_GENTIME;
	p.h.header.size = 0;
	
	for(i = 0; i < LOGIN_MAX_CONNECTIONS; ++ i)
			if( connections[i].server_check )
				QueuePacket( connections, i, &p, 1 );
}	
	
	
// ���� �������� �Ҽ� ������ Client���� �˸���. 	
void SendEndOfReGenTime( void )
{	
	int i;		
	t_packet p;	
	
	p.h.header.type = CMD_SEALSTONE_END_RE_GENTIME;
	p.h.header.size = 0;
	
	for(i = 0; i < LOGIN_MAX_CONNECTIONS; ++ i)
			if( connections[i].server_check )
				QueuePacket( connections, i, &p, 1 );
}	
	
//	���� ���� �ð��� Client���� �ѷ��ش�.
void SendWarLeftTime_sub( int nation )
{				
	int i;		
	t_packet p;	
				
	p.h.header.type = CMD_SEALSTONE_WAR_LEFTTIME;
	p.h.header.size = sizeof( t_sealstone_warlefttime );
		p.u.sealstone_warlefttime.nation = nation;
		p.u.sealstone_warlefttime.lefttime = SealStone[ nation].warlefttime - g_curr_time;
	for(i = 0; i < LOGIN_MAX_CONNECTIONS; ++ i)
			if( connections[i].server_check )
				QueuePacket( connections, i, &p, 1 );
}				

// int nation�� ���� ����� ��Լ��� ��� �μ̴°�?
// 1 : ��� �μ̴�. 
// 0 : ���� ������ �ִ�. 
int CheckVictory( int nation )
{	
	int i;
	
	for( i = 0 ; i < MAX_SEALSTONE_NATION_ ; i ++)
	{
		if( SealStone[ antination[nation]].status[i] ) break;
	}
	if( i == MAX_SEALSTONE_NATION_ )
	{	
		return 1;	// ���� �μ�����. 
	}	

	return 0; // ���� ������ �ִ�. 

}	
	

				
void CheckWarLeftTime( void )
{				
	static DWORD t;
	int nation;
				
	if( g_curr_time - t > 6 )
	{			
		t = g_curr_time;
	}	
	else return;

	for( nation = N_VYSEUS ; nation <= N_ZYPERN ; nation ++ )
	{
		if( SealStone[ nation].warlefttime == 0) continue;
				
		if( SealStone[ nation].warlefttime - g_curr_time  < SEALSTONE_WARTIME_ )
		{		
			SendWarLeftTime_sub( nation );
		}		
		else	
		{		
			SealStone[				nation].warlefttime	= 0;
			SealStone[	antination[nation]].warlefttime	= 0;
			SealStone[				nation].waraftertime	= g_curr_time + SEALSTONE_WAR_AFTERTIME_;
			SealStone[	antination[nation]].waraftertime	= g_curr_time + SEALSTONE_WAR_AFTERTIME_;
				
			if( CheckVictory( nation ) == 1 ) // nation�� �̰��. 
			{	
				SendResultNationWar( SSR_VICTORY, nation, SSR_FAIL, antination[ nation]  );
			}	
			else	//�νºδ�. 
			{	
				SendResultNationWar( SSR_DRAW, nation, SSR_DRAW, antination[ nation]  );				
			}	
		}		
	}			
}				
				
				
// ������ ������ ��������� �ð��� ���´�.
void CheckSealStoneWarAfterTime( void )
{
	int nation;	
	static DWORD t;
		
	if( g_curr_time - t > 10 )
	{	
		t = g_curr_time;
	}	
	else return;

	for( nation = N_VYSEUS ; nation <= N_ZYPERN ; nation ++ )
	{			
		if( SealStone[ nation].waraftertime == 0) continue;
				
		if( SealStone[ nation].waraftertime - g_curr_time  < SEALSTONE_WAR_AFTERTIME_ )
		{			
		}			
		else		
		{			
			SealStone[				nation].waraftertime = 0;
			SealStone[	antination[nation]].waraftertime = 0;
			SealStone[				nation].regentime	 = g_curr_time + SEALSTONE_RE_GENTIME_;
			SealStone[	antination[nation]].regentime	 = g_curr_time + SEALSTONE_RE_GENTIME_;

			SendSealStoneReGenStart();
		}	
	}	
}

// �̽ð��� ������ �ٽ� ������� �μ��� �ִ�. 
void CheckReGenTime( void )
{	
	static DWORD t;
	int    nation;

	if( g_curr_time - t > 6 )
	{						
		t = g_curr_time;
	}			
	else return;	
				
	for( nation = N_VYSEUS ; nation <= N_ZYPERN ; nation ++ )
	{			
		if( SealStone[ nation].regentime == 0) continue;
				
		if( SealStone[ nation].regentime - g_curr_time  > SEALSTONE_RE_GENTIME_)
		{			
		}			
		else		
		{			
			SealStone[				nation].regentime  = 0;
			SealStone[	antination[nation]].regentime  = 0;
			SealStone[				nation].warlefttime= 0;
			SealStone[	antination[nation]].warlefttime= 0;
			SealStone[				nation].regentime  = 0;
			SealStone[	antination[nation]].regentime  = 0;

			SendEndOfReGenTime();
		}	
	}
}	
	
//	�������� �ȵڿ� ,��� ��輮�� �����°�?
void CheckSealStoneStatus( void )
{		
	int nation, j;	
	static DWORD t;
		
	if( g_curr_time - t > 10 )
	{	
		t = g_curr_time;
	}	
	else return;
		
	for( nation = N_VYSEUS ; nation <= N_ZYPERN ; nation ++ )
	{			
		if( SealStone[ nation].warlefttime ) // ���Ｑ���� �ѻ��¿��� .
		{		
			for( j = 0 ; j < MAX_SEALSTONE_NATION_ ; j ++)
			{	
				if( SealStone[ antination[ nation]].status[ j] ) break;
			}	
			if( j == MAX_SEALSTONE_NATION_ ) // ������ ��輮�� ��� �μ����ٸ�.
			{	
				// �¸�...
				SendResultNationWar( SSR_VICTORY, nation, SSR_FAIL, antination[ nation]  );

				SealStone[				nation].warlefttime	= 0;
				SealStone[	antination[nation]].warlefttime	= 0;
				SealStone[				nation].waraftertime = g_curr_time + SEALSTONE_WAR_AFTERTIME_;
				SealStone[	antination[nation]].waraftertime = g_curr_time + SEALSTONE_WAR_AFTERTIME_;
			}	
		}		
	}	
}		
		
		
void SendSealStoneBlock( void )
{										
	t_packet p;						
	int i;						
	int ret;					
						
	ret = ReturnNation2NationRelation( N_VYSEUS, N_ZYPERN );
								
	switch( ret )					
	{												
		// ������..							
	case NATION_RELATION_ENEMY_ :	p.h.header.type = CMD_STEALSTONE_BREAKABLE;
									
								
		break;							
		// ���Ͱ��迡���� ���� �վ�� ����. 
	case NATION_RELATION_FRIEND_:	if( g_hour >= 22 || g_hour < 2 ) p.h.header.type = CMD_STEALSTONE_NON_BREAKABLE_PEACE;
									else p.h.header.type = CMD_STEALSTONE_NON_BREAKABLE;
		break;								
													
	default :	return;				
	}													
											
	p.h.header.size = 0;									
											
	for(i = 0; i < LOGIN_MAX_CONNECTIONS; ++ i)
			if( connections[i].server_check )					
				QueuePacket( connections, i, &p, 1 );
}											
											
										
// 20�и���.. �ѷ��ش�.					
void CheckSealStoneBlock( void )		
{								
	static DWORD t;				
	static int   oldh;						
					
	if( g_curr_time	- t > 20*60 || oldh != g_hour )
	{									
		t = g_curr_time;			
		oldh = g_hour;	
	}							
	else return;			
								
	SendSealStoneBlock();				
}				
 		
		
void CheckNationWar( void )
{		
	CheckSealStoneBlock();

	//CheckReGenTime();		
	CheckSealStoneStatus();	
	//CheckWarLeftTime();		
}		

//////////////////////////////////////////////////////////////////////////////

/******************************************************************************************************
�� �� : �ּ��� �������¸� �����Ѵ�.  �⺻������ ��籹���� ���뱹���̴�.
�� �� : ����
�� �� : 
*******************************************************************************************************/
int InitNationRelation( void )
{
	int i,j;

	for( i = 0 ; i < MAX_NATION_ ; i ++)
	{
		for( j = 0 ; j < MAX_NATION_ ; j ++)
		{
			if( i == j ) NationRelation[i][j].relation = NATION_RELATION_NO_; 
			else NationRelation[i][j].relation = NATION_RELATION_ENEMY_;
		}
	}

	return 1;
}				
				
				
/******************************************************************************************************
��	�� : ���� �������� ���踦 �����Ѵ�. 
��	�� : int a_nation, b_nation : ���踦 ������ ���� ( �����ڵ�,  3: ���̼���, 4:������ ... )
			
��	�� : 0 : ������    1: �������     2: ���°���    3: ��������( a:�� b:��)
*******************************************************************************************************/
int ReturnNation2NationRelation( int anation, int bnation )
{		
	if( anation > MAX_NATION_ ) return 0;
	if( bnation > MAX_NATION_ ) return 0;
		
	t_NationRelation *ta, *tb;
	ta = &NationRelation[anation][bnation];
	tb = &NationRelation[bnation][anation];
		
	if( ta->year &&
	  ( (double)ta->year* 365*24*60*60 +	(double)ta->yday* 24*60*60 +	(double)ta->hour* 60*60 +	ta->howlong <
		(double)g_year	* 365*24*60*60 +	(double)g_yday	* 24*60*60 +	(double)g_hour	* 60*60 ) )	
	{	
		ta->relation = ta->oldrelation;
		tb->relation = tb->oldrelation;
		tb->year = 0;
		ta->year = 0;
	}	
	else
	{	
		if( g_hour >= 22 || g_hour < 2 ) 
		{			
			return	ta->relation;
		}			
		else
		{	
			return NATION_RELATION_FRIEND_;
		}	
	}		
				
	return ta->relation;
}		
		
		
int SetNation2NationRelation( int a_nation, int b_nation, int relation, int year, int yday, int hour, DWORD howlong )
{		
	if( a_nation > MAX_NATION_ ) return NATION_RELATION_FAIL_NO_NATION_;
	if( b_nation > MAX_NATION_ ) return NATION_RELATION_FAIL_NO_NATION_;
		
	switch( relation )
	{	
		case NATION_RELATION_ENEMY_			:	
			break;		
		
		case NATION_RELATION_FRIEND_		:	
					if( relation == NationRelation[a_nation][b_nation].relation )
					{
						return NATION_RELATION_SAME_FAIL_;
					}
					if( g_hour >= 22 || g_hour < 2 )	// ����� �������̱� ������ �̽ð����� ������ ���踦 �����Ҽ� ����. 
					{
						return NATION_RELATION_FAIL_;
					}	
			break;		
		case NATION_RELATION_MASTER_SERVANT_:
			break;		
	}					
						
	t_NationRelation *t;
	t = &NationRelation[a_nation][b_nation];
					
	t->oldrelation	= t->relation;
	t->relation		= relation; 
	t->year			= year; 
	t->yday			= yday;	
	t->hour			= hour; 
	t->howlong		= howlong; 
						
	t = &NationRelation[b_nation][a_nation];
	t->oldrelation	= t->relation;
	t->relation		= relation; 
	t->year			= year; 
	t->yday			= yday;	
	t->hour			= hour;	
	t->howlong		= howlong; 
						
	return NATION_RELATION_SUCCESS_;
}


/********************************************************************************************�׼�(�ʼ�)���� ����ϴ� �Լ�
��	�� :	�������� ���踦 Loginserver�� ���� ���Ӽ����� ������ ��� ���Ӽ�(�ʼ�)�� �˰� �Ѵ�. 
			
��	�� : int a_nation, b_nation : ���踦 ������ ���� ( �����ڵ�,  3: ���̼���, 4:������ ... )
		int relation           : 0 : ������    1: �������     2: ���°���    3: ��������( a:�� b:��)
		DWORD relationstart		:	���ʵڿ� �����Ұ��ΰ�
		DWORD relationhowlong	:	���ʵ��� �����ɰ��ΰ�? ( 0�̸� ���� )
			
��	�� : LoginServer�� ��������, �ٽ� ���Ӽ�(�ʼ�)���� ��������, �ٽ� Client���� ����� �����ְ� �ȴ�. 
*******************************************************************************************************/
int SendNation2NationRelation( int a_nation, int b_nation, int relation, int year = 0, int yday = 0, int hour = 0, DWORD howlong = 0 )
{			
	t_packet p;
			
	if( relation == NATION_RELATION_FRIEND_ )
	{		
		if( year == 0 ) // �������� 1�ϰ��� ������ �Ѵ�. 
		{	
			year = g_year;
			yday = g_yday;
			hour = g_hour;

			int shour = 24 - g_hour + 2;
			int smin  = 60 - g_min;
			
			howlong = 60*60*shour + smin * 60;
		}	
	}		
			
	p.h.header.type = CMD_NATION2NATION_RELATION;
	p.h.header.size = sizeof( t_nation2nation_relation );
			
		p.u.nation2nation_relation.a		= a_nation;
		p.u.nation2nation_relation.b		= b_nation;
		p.u.nation2nation_relation.relation = relation;
		p.u.nation2nation_relation.year		= year;
		p.u.nation2nation_relation.yday		= yday;
		p.u.nation2nation_relation.hour		= hour;
		p.u.nation2nation_relation.howlong	= howlong;
			
	QueuePacket( connections, LOGIN_SERVER_CONNECT, &p, 1 );

	return 1;
}			
			
/********************************************************************************************�׼�(�ʼ�)���� ����ϴ� �Լ�
��	�� : �������� ���踦 Loginserver�� ���� ���Ӽ����� ������ ��� ���Ӽ�(�ʼ�)�� �˰� �Ѵ�. 
		  
��	�� : int a_nation, b_nation : ���踦 ������ ���� ( �����ڵ�,  3: ���̼���, 4:������ ... )
		int relation           : 0 : ������    1: �������     2: ���°���    3: ��������( a:�� b:��)
		DWORD relationstart		:	���ʵڿ� �����Ұ��ΰ�
		DWORD relationhowlong	:	���ʵ��� �����ɰ��ΰ�? ( 0�̸� ���� )

��	�� : LoginServer�� ��������, �ٽ� ���Ӽ�(�ʼ�)���� ��������, �ٽ� Client���� ����� �����ְ� �ȴ�. 
*******************************************************************************************************/
void RecvNation2NationRelation( int cn, t_nation2nation_relation *tp )
{										
	t_packet p;
	int i;
	int ret;

	ret = SetNation2NationRelation( tp->a, tp->b, tp->relation, tp->year, tp->yday, tp->hour, tp->howlong );

	p.h.header.type = CMD_NATION2NATION_RELATION_RESULT;
	p.h.header.size = sizeof( t_nation2nation_relation_result );
			
	p.u.nation2nation_relation_result.why = ret;
			
	for( i = 0 ; i < LOGIN_MAX_CONNECTIONS ; i ++)
			if( connections[i].server_check )
				QueuePacket( connections, i, &p, 1 );
}
	







