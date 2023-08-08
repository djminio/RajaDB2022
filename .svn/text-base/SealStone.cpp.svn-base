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
	돌이 리젠되거나 
    돌이 부서지면 게임서버에서 보내준다. 
	
  status : 0 --> 부서짐   1 : 리젠됨..
---------------------------------------------------------------------*/
void RecvSealStoneStatus( t_packet *p )
{	
	t_sealstone_status *tp;
	int status = 0;
	int i;
	
	tp = &p->u.sealstone_status ;

	switch( tp->status )
	{
		// 타격을 받았다. 
	case 2 :		
		// 죽었다. 
	case 0 :		status = 0;		break;
		// 되살아났다. 
	case 1 :		status = 1;		break;
	}

	switch( tp->sealstonesprno )
	{
		// 바이서스
	case 98 :	SealStone[ N_VYSEUS].status[tp->id] = status;
		break;
		// 자이펀
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
	왕이 선전포고를 했다.	->  결계석이 리젠될때에는 할수 없으며
	설공하면 선전포고 했다는 메시지가 뜬다
---------------------------------------------------------------------*/
void RecvSealStoneFromKing( int nation )
{	
	if( SealStone[ nation].regentime ||  SealStone[ nation].waraftertime ) return; // 리젠하는동안에는 다시 선전포고가 되지 않는다. 
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
	
// 이제 결계석을 리젠될것이고 당분간 결계석을 부술수 없다. 
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
	
	
// 이제 선전포고를 할수 있음을 Client까지 알린다. 	
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
	
//	현재 남은 시간을 Client까지 뿌려준다.
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

// int nation의 나라가 상대의 결게석을 모두 부셨는가?
// 1 : 모두 부셨다. 
// 0 : 아직 남은게 있다. 
int CheckVictory( int nation )
{	
	int i;
	
	for( i = 0 ; i < MAX_SEALSTONE_NATION_ ; i ++)
	{
		if( SealStone[ antination[nation]].status[i] ) break;
	}
	if( i == MAX_SEALSTONE_NATION_ )
	{	
		return 1;	// 모든게 부셔졌다. 
	}	

	return 0; // 아직 남은게 있다. 

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
				
			if( CheckVictory( nation ) == 1 ) // nation이 이겼다. 
			{	
				SendResultNationWar( SSR_VICTORY, nation, SSR_FAIL, antination[ nation]  );
			}	
			else	//부승부다. 
			{	
				SendResultNationWar( SSR_DRAW, nation, SSR_DRAW, antination[ nation]  );				
			}	
		}		
	}			
}				
				
				
// 전쟁이 끝나고 잠시조용한 시간을 갖는다.
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

// 이시간이 지나면 다시 결계적을 부술수 있다. 
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
	
//	전전포고가 된뒤에 ,모든 결계석이 깨졌는가?
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
		if( SealStone[ nation].warlefttime ) // 전쟁선포를 한상태에서 .
		{		
			for( j = 0 ; j < MAX_SEALSTONE_NATION_ ; j ++)
			{	
				if( SealStone[ antination[ nation]].status[ j] ) break;
			}	
			if( j == MAX_SEALSTONE_NATION_ ) // 상대방의 결계석이 모두 부셔졌다면.
			{	
				// 승리...
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
		// 적국가..							
	case NATION_RELATION_ENEMY_ :	p.h.header.type = CMD_STEALSTONE_BREAKABLE;
									
								
		break;							
		// 동맹관계에서는 맵을 먼어갈수 없다. 
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
											
										
// 20분마다.. 뿌려준다.					
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
기 능 : 최소의 국가상태를 설정한다.  기본적으로 모든국가는 적대국가이다.
인 자 : 없음
결 과 : 
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
기	능 : 현재 국가간의 관계를 리턴한다. 
인	자 : int a_nation, b_nation : 관계를 설정할 국가 ( 국가코드,  3: 바이서스, 4:자이펀 ... )
			
결	과 : 0 : 무관계    1: 적대관계     2: 협력관계    3: 주종관계( a:주 b:종)
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
					if( g_hour >= 22 || g_hour < 2 )	// 현재는 전쟁중이기 때문에 이시간에는 국구간 관계를 설정할수 없다. 
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


/********************************************************************************************겜섭(맵섭)에서 사용하는 함수
기	능 :	국가간의 관계를 Loginserver로 보내 게임서버에 보내어 모든 게임섭(맵섭)이 알게 한다. 
			
인	자 : int a_nation, b_nation : 관계를 설정할 국가 ( 국가코드,  3: 바이서스, 4:자이펀 ... )
		int relation           : 0 : 무관계    1: 적대관계     2: 협력관계    3: 주종관계( a:주 b:종)
		DWORD relationstart		:	몇초뒤에 시작할것인가
		DWORD relationhowlong	:	몇초동안 유지될것인가? ( 0이면 무한 )
			
결	과 : LoginServer에 보내지면, 다시 게임섭(맵섭)으로 보내지며, 다시 Client까지 결과를 보내주게 된다. 
*******************************************************************************************************/
int SendNation2NationRelation( int a_nation, int b_nation, int relation, int year = 0, int yday = 0, int hour = 0, DWORD howlong = 0 )
{			
	t_packet p;
			
	if( relation == NATION_RELATION_FRIEND_ )
	{		
		if( year == 0 ) // 국가간의 1일간의 휴전을 한다. 
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
			
/********************************************************************************************겜섭(맵섭)에서 사용하는 함수
기	능 : 국가간의 관계를 Loginserver로 보내 게임서버에 보내어 모든 게임섭(맵섭)이 알게 한다. 
		  
인	자 : int a_nation, b_nation : 관계를 설정할 국가 ( 국가코드,  3: 바이서스, 4:자이펀 ... )
		int relation           : 0 : 무관계    1: 적대관계     2: 협력관계    3: 주종관계( a:주 b:종)
		DWORD relationstart		:	몇초뒤에 시작할것인가
		DWORD relationhowlong	:	몇초동안 유지될것인가? ( 0이면 무한 )

결	과 : LoginServer에 보내지면, 다시 게임섭(맵섭)으로 보내지며, 다시 Client까지 결과를 보내주게 된다. 
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
	







