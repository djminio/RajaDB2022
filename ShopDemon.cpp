// ShopDemon.cpp: implementation of the CShopDemon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShopDemon.h"

#include "./China/QueryDBSocket.h"
#include "LottoDBMgr.h"

extern CQueryDBSocket *ConQ;
extern int GetLoginIdByName( char *name, char *login_id );
extern char* EatRearWhiteChar( char* pStr );

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CShopDemon*	CShopDemon::m_pClass = NULL;
CShopDemon::CShopDemon()
{
	m_pClass = this;
}

CShopDemon::~CShopDemon()
{
	m_pClass = NULL;
}

//샵시스템은. 유저의 복권사기 요청정보를 과금 시스템의 인증을 기다리기 위해 임시 보관 해둔다.
//이메세지는 멥서버에서 받는다.
void CShopDemon::RecvCanBuyLotto(t_BUY_LOTTO *pCanBuy, int cn)
{

	t_LottoBuySave LottoBuySave = {0,};
	char LogInID[20] = {NULL,};
	
	memcpy(&LottoBuySave.Buy_Lotto,pCanBuy,sizeof(t_BUY_LOTTO));
	LottoBuySave.cn = cn;
	if(!::GetLoginIdByName(pCanBuy->strCharName,LogInID))
	{
		DebugPrintf("CShopDemon::RecvCanBuyLotto() Error ==> GetLoginIdByName: CharName = %s",pCanBuy->strCharName);
		return;
	}
	
	memcpy(LottoBuySave.szUserID,LogInID,sizeof(char)*20);
	::EatRearWhiteChar(LottoBuySave.szUserID);
	

	DebugPrintf("ShopSytem Push LottoUser char : %s , UserID : %s",LottoBuySave.Buy_Lotto.strCharName,LottoBuySave.szUserID);
	m_ltLottoBuySaveList.push_back(LottoBuySave);//임시리스트에 저장.
	

	//여기서 과금 서버로 얼마나 돈이 있는지 알아 보기 위해 보낸다.
	//사용자 아이디와 돈을 담을수 있는 변수와 어떤 품목을 사기위한 정보인지 담을수 있는 변수를 만들어야지.^^
	st_SHOP_SYSTEM_POINT stPoint = {0,};
	stPoint.nPoint = -1;
	stPoint.nShoppingType = LOTTO_SYSTEM;
	stPoint.nSuccess = 0;
	memcpy(stPoint.szID,LogInID,sizeof(char)*20);
	::EatRearWhiteChar(stPoint.szID);

	
	//여기서 과금 서버로 보낸다.
	if(ConQ != NULL)
	{
		DebugPrintf("ShopSystem Send : ConQ->Send_Data_To_Server ======> RecvCanBuyLotto()");
		ConQ->Send_Data_To_Server(SHOP_SYSTEM_POINT_INFO,&stPoint,sizeof(st_SHOP_SYSTEM_POINT));
	}
	else
	{
		DebugPrintf("CShopDemon::RecvCanBuyLotto() ======> ConQ is NULL");
	}	
}

void CShopDemon::RecvShopProcess(int nProtocol, void *data, int datasize)
{
	switch(nProtocol)
	{
	case SHOP_SYSTEM_POINT_INFO_RETURN:
		{
			st_SHOP_SYSTEM_POINT stPoint = {0,};
			memcpy(&stPoint,data,datasize);
			::EatRearWhiteChar(stPoint.szID);

			if(stPoint.nSuccess == SHOP_OK)//성공 했다.
			{
				switch(stPoint.nShoppingType)
				{
				case LOTTO_SYSTEM:
					{
						for(ITOR_BUYSAVE i = m_ltLottoBuySaveList.begin();i != m_ltLottoBuySaveList.end();++i)
						{
							if(strcmp((*i).szUserID,stPoint.szID) == 0)//리스트에 있다.
							{
								if( stPoint.nPoint >= LottoDBMgr()->GetLottoPay() )//돈은 충분하다.
								{
									t_packet p;
									p.h.header.type = CMD_CAN_BUY;
									p.h.header.size = sizeof(t_BUY_LOTTO);

									strcpy(p.u.Lotto_Buy.strCharName,(*i).Buy_Lotto.strCharName);
									p.u.Lotto_Buy.nLottoID = (*i).Buy_Lotto.nLottoID;
	
									int nBuyCount = LottoDBMgr()->GetBuyCountByUser((*i).szUserID, (*i).Buy_Lotto.nLottoID);
									
	
									if(nBuyCount == 0)//무조건 살수 있다.
									{
										memcpy(p.u.Lotto_Buy.anLottoNumber,(*i).Buy_Lotto.anLottoNumber,sizeof(int)*10);
									}
									else//soto-Lotto추가 if(nBuyCount < 5)// 중복 번호 검사를 해야한다.
									{
										if(!LottoDBMgr()->ExistLottoNumber((*i).Buy_Lotto.anLottoNumber,(*i).szUserID,(*i).Buy_Lotto.nLottoID))//중복 되지 않았다.
										{
											memcpy(p.u.Lotto_Buy.anLottoNumber,(*i).Buy_Lotto.anLottoNumber,sizeof(int)*10);
										}
										else//중복 되는 번호가 있다.
										{
											p.u.Lotto_Buy.anLottoNumber[0] = -3; // -3 중복 되는 번호.
										}
									}
//soto-Lotto 추가
/*
									else//살수 있는 만큼 다샀다.
									{
										p.u.Lotto_Buy.anLottoNumber[0] = -2; // -2 복권을 많이 샀다.
									}
*/

									QueuePacket(connections,(*i).cn,&p,1);
								}
								else// 돈이 모자라다.
								{
									DebugPrintf("ShopSystem : Less Money");
									t_packet p2;
									p2.h.header.type = CMD_CAN_BUY;
									p2.h.header.size = sizeof(t_BUY_LOTTO);
									strcpy(p2.u.Lotto_Buy.strCharName,(*i).Buy_Lotto.strCharName);
									p2.u.Lotto_Buy.nLottoID = (*i).Buy_Lotto.nLottoID;

									p2.u.Lotto_Buy.anLottoNumber[0] = 0;//번호의 맨앞이 0이면 돈이 모자라다.
									QueuePacket(connections,(*i).cn,&p2,1);
								}
								
								m_ltLottoBuySaveList.erase(i);
								break;//for 문을 빠져 나간다.
							}
							
						}
					}
					break;
				}
			}
			else
			{
				
			}
		}
		break;
	case SHOP_SYSTEM_DEDUCT_POINT_RETURN:
		{

			st_SHOP_SYSTEM_POINT_REDUCT stRecvPointReturn;
			memcpy(&stRecvPointReturn,data,datasize);

			if(stRecvPointReturn.stShopSystemPoint.nSuccess == SHOP_OK)
			{
/*				switch(stRecvPointReturn.stShopSystemPoint.nShoppingType)
				{
				case LOTTO_SYSTEM:
					{
						for(ITOR_BUYSAVE i = m_ltLottoBuySaveList.begin();i != m_ltLottoBuySaveList.end();++i)
						{
							
						}
					}
					break;
				}
*/
			}
			else//성공 하지 못했다. //point DB 에 없거나..//돈이 모자라다.
			{
				switch(stRecvPointReturn.stShopSystemPoint.nShoppingType)
				{
				case LOTTO_SYSTEM:
					{
						DebugPrintf("ShopSystem Deduct failed : ID = %s, DeductPoint = %d,",stRecvPointReturn.stShopSystemPoint.szID,
							stRecvPointReturn.nDeductPoint);
					}
					break;
				}				
			}

		}
		break;
		
	}

}

void CShopDemon::RecvLottoBuy(t_BUY_LOTTO *pBuyLotto, int cn)
{
	LottoDBMgr()->RecvLottoBuy(pBuyLotto);//디비에 기록을 한다.

	char LogInID[20] = {NULL,};

	::GetLoginIdByName(pBuyLotto->strCharName,LogInID);
	
	st_SHOP_SYSTEM_POINT_REDUCT stLottoBuy = {0,};
	memcpy(stLottoBuy.stShopSystemPoint.szID,LogInID,sizeof(char)*20);
	::EatRearWhiteChar(stLottoBuy.stShopSystemPoint.szID);
	stLottoBuy.stShopSystemPoint.nPoint = -1;
	stLottoBuy.stShopSystemPoint.nShoppingType = LOTTO_SYSTEM;
	stLottoBuy.stShopSystemPoint.nSuccess = 0;
	stLottoBuy.nDeductPoint = LottoDBMgr()->GetLottoPay();
	stLottoBuy.szKey[0] = (char)pBuyLotto->anLottoNumber[0];//여기에 로또 번호가 들어간다.
	stLottoBuy.szKey[1] = (char)pBuyLotto->anLottoNumber[1];
	stLottoBuy.szKey[2] = (char)pBuyLotto->anLottoNumber[2];
	stLottoBuy.szKey[3] = (char)pBuyLotto->anLottoNumber[3];
	stLottoBuy.szKey[4] = (char)pBuyLotto->anLottoNumber[4];
	stLottoBuy.szKey[5] = (char)pBuyLotto->anLottoNumber[5];
	stLottoBuy.szKey[6] = (char)pBuyLotto->anLottoNumber[6];
	stLottoBuy.szKey[7] = (char)pBuyLotto->anLottoNumber[7];
	stLottoBuy.szKey[8] = (char)pBuyLotto->anLottoNumber[8];
	stLottoBuy.szKey[9] = (char)pBuyLotto->anLottoNumber[9];

	if(ConQ)
	{
		DebugPrintf("ShopSytem Send: ConQ->Send_Data_To_Server() =====> RecvLottoBuy()");
		ConQ->Send_Data_To_Server(SHOP_SYSTEM_DEDUCT_POINT,&stLottoBuy,sizeof(st_SHOP_SYSTEM_POINT_REDUCT));
	}
	else
	{
		DebugPrintf("CShopDemon::RecvLottoBuy() ======> ConQ is NULL");
	}
}
