// Auction.cpp: implementation of the CAuction class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "packed.h"
#include "servertable.h"
#include "MAIN.H"
#include "Scrp_exe.H"
#include "ID.h"
#include "SealStone.h"
#include "Debug.h"
#include "mainheader.h"
#include "monitor.h"
#include "Citem.h"
#include "Pay.h"
#include "ChrLog.h"
#include "dragonloginserver2.h"		// 010406 YGI
#include "hong_sub.h"
#include "Auction.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern HDBC		hDBC_ChrLogDB;
extern HDBC		hDBC_TotalDB;
extern HENV		hEnv ;
extern HDBC		hDBC ;
extern int	g_wday;

CAuction Auction;
CAuction::CAuction()
{
	Clear();
}

CAuction::~CAuction()
{
	Clear();
}

void CAuction::Clear()
{
}

//soto-030514
int CAuction::SearchAuctionItem(SEARCHRESULTLIST *List, const char* szQuery)
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	::SQLAllocStmt(hDBC, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuery, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{		
		int i = 0;
		retCode = SQLFetch(hStmt);
		while( retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		{
			if(i > MAX_SEARCH_RESULT_LIST) 
			{
				goto __FAIL;
			}
			int column = 0;
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&List->ResultList[i].iIndex	,	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_CHAR,	List->ResultList[i].szSellerName,	20, &cbValue);
			::EatRearWhiteChar(List->ResultList[i].szSellerName);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_CHAR,	List->ResultList[i].szBuyerName,	20, &cbValue);
			::EatRearWhiteChar(List->ResultList[i].szBuyerName);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&List->ResultList[i].iIsEnd,	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&List->ResultList[i].iSellerTake,	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&List->ResultList[i].iBuyerTake,	0, &cbValue);
			
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&List->ResultList[i].iSellValue,	0, &cbValue);

			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&List->ResultList[i].m_ResultItem.item_no,	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&List->ResultList[i].m_ResultItem.attr[0],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&List->ResultList[i].m_ResultItem.attr[1],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&List->ResultList[i].m_ResultItem.attr[2],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&List->ResultList[i].m_ResultItem.attr[3],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&List->ResultList[i].m_ResultItem.attr[4],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&List->ResultList[i].m_ResultItem.attr[5],	0, &cbValue);
			i++;
			retCode = SQLFetch(hStmt);
			if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO){}
			else if( retCode == SQL_NO_DATA ) 
			{
				break;
			}
			else
			{
				goto __FAIL;
			}
		}
		goto __SUCCESS;
	}
	goto __FAIL;

__FAIL:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		return false;
	}
__SUCCESS:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);		// 0308 YGI
		return true;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 검색 하기 시작 (구매자
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//soto-030514
int CAuction::RecvCMD_MERCHANT_BUY_LIST_REQUEST(const int iCn, t_packet &p)//리스트 요청(구매자가 보는것//검색기가 호출
{
	SEARCHRESULTLIST FindResult;
	memset(&FindResult ,0, sizeof(SEARCHRESULTLIST));
	FindResult.iCn = p.u.SearchPacketServer.iCn;
	FindResult.iKey = p.u.SearchPacketServer.ClientMsg.iKey;//021113 lsw
	int	iIndex = p.u.SearchPacketServer.ClientMsg.iIndex;
	memcpy(FindResult.szName,p.u.SearchPacketServer.szName,20);
	char szQuery[1000] ={0,};
	char szKeyWord[21] = {NULL,};
	char szMerchant[21] = {NULL,};

	int nDay  = 0;

	switch(p.u.SearchPacketServer.ClientMsg.nPeriod)
	{
	case 0:
		nDay = 2;//1일.
		break;
	case 1:
		nDay = 4;//3일
		break;
	case 2:
		nDay = 8;//1주일
		break;
	}

	ConvertQueryString(p.u.SearchPacketServer.ClientMsg.szKeyWord,szKeyWord, 20);
	ConvertQueryString(p.u.SearchPacketServer.ClientMsg.szMerchant,szMerchant, 20);
//	memcpy(szKeyWord,p.u.SearchPacketServer.ClientMsg.szKeyWord,20);szKeyWord[20] = 0;
//	memcpy(szMerchant,p.u.SearchPacketServer.ClientMsg.szMerchant,20);szMerchant[20] = 0;
	
	if(FindResult.iKey)
	{
		if(strlen(szKeyWord))//키워드가 있으면.
		{
			if(strlen(szMerchant))//상인 이름이 있으면.
			{
				//여기는 키워드와 상인 이름과 기간이 조건이다.
				sprintf(szQuery,"EXEC MerchantItemSearch_Key_Merchant_Day '%s', '%s', %d, %d, %d, %d, %d",
					szKeyWord,szMerchant,nDay,
					IS_END_ALL_RIGHT, 0, 0,iIndex);
			}
			else
			{
				//여기는 키워드와 기간 만이 조건이다.
				sprintf(szQuery,"EXEC MerchantItemSearch_Key_Day '%s', %d, %d, %d, %d, %d",
					szKeyWord,nDay,
					IS_END_ALL_RIGHT, 0, 0,iIndex);

			}
		}
		else//키워드가 없으면.
		{
			if(strlen(szMerchant))//상인 이름이 있으면.
			{
				//여기는 상인이름과 기간이 조건이다.
				sprintf(szQuery,"EXEC MerchantItemSearch_Merchant_Day '%s',%d, %d, %d, %d, %d",
					szMerchant,nDay,
					IS_END_ALL_RIGHT, 0, 0,iIndex);

			}
			else//여기는 단순히 기간만이 조건이다.
			{
				sprintf(szQuery,"EXEC MerchantItemSearch_Day %d, %d, %d, %d, %d",
					nDay,
					IS_END_ALL_RIGHT, 0, 0,iIndex);
			}
		}	
	}
	else
	{
		if(strlen(szKeyWord))//키워드가 있으면.
		{
			if(strlen(szMerchant))//상인 이름이 있으면.
			{
				//여기는 키워드와 상인 이름과 기간이 조건이다.
				sprintf(szQuery,"EXEC MerchantItemSearch_Key_Merchant_Day_Inverse '%s', '%s', %d, %d, %d, %d, %d",
					szKeyWord,szMerchant,nDay,
					IS_END_ALL_RIGHT, 0, 0,iIndex);
			}
			else
			{
				//여기는 키워드와 기간 만이 조건이다.
				sprintf(szQuery,"EXEC MerchantItemSearch_Key_Day_Inverse '%s', %d, %d, %d, %d, %d",
					szKeyWord,nDay,
					IS_END_ALL_RIGHT, 0, 0,iIndex);

			}
		}
		else//키워드가 없으면.
		{
			if(strlen(szMerchant))//상인 이름이 있으면.
			{
				//여기는 상인이름과 기간이 조건이다.
				sprintf(szQuery,"EXEC MerchantItemSearch_Merchant_Day_Inverse '%s',%d, %d, %d, %d, %d",
					szMerchant,nDay,
					IS_END_ALL_RIGHT, 0, 0,iIndex);

			}
			else//여기는 단순히 기간만이 조건이다.
			{
				sprintf(szQuery,"EXEC MerchantItemSearch_Day_Inverse %d, %d, %d, %d, %d",
					nDay,
					IS_END_ALL_RIGHT, 0, 0,iIndex);
			}
		}		
	}


/*
	if(iKey)
	{
	sprintf(szQuery,"EXEC MerchantItemSearchBuyerSide %d, %d, %d, %d,	%d, %d, %d, %d",
		iRareType, iItemLevel, iTacticType, iWearType,
		IS_END_ALL_RIGHT, 0, 0,iIndex);
	}
	else
	{
	
	sprintf(szQuery,"EXEC MerchantItemSearchBuyerSideInverse %d, %d, %d, %d,	%d, %d, %d, %d",
		iRareType, iItemLevel, iTacticType, iWearType,
		IS_END_ALL_RIGHT, 0, 0,iIndex);
	}
*/
	if(SearchAuctionItem(&FindResult,szQuery))
	{
		t_packet rp;
		rp.h.header.type = CMD_MERCHANT_BUY_ITEM_SEARCH_RESULT;
		rp.h.header.size = sizeof(SEARCHRESULTLIST);
		rp.u.SearchResultList= FindResult;
		::QueuePacket(connections,iCn,&rp,1);
	}
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 검색 하기 끝 (구매자
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 구매 하기 시작(구매자)
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAuction::RecvCMD_MERCHANT_ITEM_BUY_COMFORM(const int iCn,t_packet &p)
{
/*
	CREATE PROC MerchantItemBuyComform
	(
	@No	int,
	@SellerName char(20),
	@BuyerName char(20),
	@SetIsEnd int,
	@BeforeIsEnd int,
	@ItemNo int,
	@ItemAttr1 int,
	@ItemAttr2 int,
	@ItemAttr3 int,
	@ItemAttr4 int,
	@ItemAttr5 int,
	@ItemAttr6 int
	)
	as

	UPDATE MerchantSeller SET [IsEnd] = @SetIsEnd, [BuyerName] = @BuyerName WHERE   ([SellerName] =@SellerName) AND ([No] = @No)AND ([IsEnd] = @BeforeIsEnd)
	SELECT   count(*)FROM      MerchantSeller WHERE 
	([No] = @No)AND 
	([SellerName] =@SellerName) AND 
	([IsEnd ]=@SetIsEnd ) AND 
	([SellItemNo ]=@ItemNo) AND 
	([SellItemAttr1]= @ItemAttr1) AND 
	([SellItemAttr2 ]=@ItemAttr2) AND 
	([SellItemAttr3 ]=@ItemAttr3) AND 
	([SellItemAttr4 ]=@ItemAttr4) AND 
	([SellItemAttr5 ]=@ItemAttr5) AND 
	([SellItemAttr6 ]=@ItemAttr6) 


	MerchantItemBuyComform 1,'화랑상우', 3,1
*/
	//isend 를 거래중으로 해준다
	//구매 가능 한가? //인덱스,파는놈,아이템,isEnd == 0(구매가능) 으로 검색한다
	//카운트를 받아서 검사 하자 0 이면 안판다고 1 이면 판다 겠지.

	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	::SQLAllocStmt(hDBC, &hStmt);
	char szQuery[255] ={0,};
	MERCHANT_ITEM_BUY *pMIB = &p.u.MerchantItemBuy;
	MERCHANT_ITEM_BUY QueryResult = *pMIB;//받은걸로 초기화를 시킨다

	char szSellerName[21];
	char szBuyerName[21];
	ConvertQueryString(pMIB->szSellerName, szSellerName, 21); // Finito prevents sql injection
	ConvertQueryString(pMIB->szBuyerName, szBuyerName, 21); // Finito prevents sql injection
 
	sprintf(szQuery,"EXEC MerchantItemBuyComform %d, '%s' , '%s', "//인덱스,이름,바꿀값,이전값
		" %d, %d, "
		"%d, %d, %d, %d, %d, %d, %d",
	pMIB->iIndex,
	szSellerName,
	szBuyerName,
	IS_END_BUYING,//구매중 상태로 만든다
	IS_END_ALL_RIGHT,
	pMIB->SellItem.item_no,
	pMIB->SellItem.attr[0],
	pMIB->SellItem.attr[1],
	pMIB->SellItem.attr[2],
	pMIB->SellItem.attr[3],
	pMIB->SellItem.attr[4],
	pMIB->SellItem.attr[5]);

	//IS_END_ALL_RIGHT 상태에서만 지울 수 있다 여러번 지우는건 불가능 하다
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuery, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{
		retCode = SQLFetch(hStmt);
		if( retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		{
			int column = 0;
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iIndex,			0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_CHAR,	QueryResult.szSellerName,		20, &cbValue);
			::EatRearWhiteChar(QueryResult.szSellerName);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iKey,				0, &cbValue);//IsEnd값이 들어온다
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.dwSellValue,		0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.item_no,	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[0],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[1],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[2],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[3],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[4],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[5],	0, &cbValue);

			if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
			{	//여기 왔음은 데이타가 멀쩡하다는 증거.(업데이트에 성공 했다.
				if(QueryResult.dwSellValue != pMIB->dwSellValue)
				{
					MyLog(0,"Auction Critical Warning!! Type => CMD_MERCHANT_ITEM_BUY_COMFORM SellValue NotMatch = DB %d, Client %d",QueryResult.dwSellValue, pMIB->dwSellValue);
					pMIB->dwSellValue = QueryResult.dwSellValue;
					MyLog(0,"Auction Critical Warning!! Type => CMD_MERCHANT_ITEM_BUY_COMFORM Force Change Value = %d ",QueryResult.dwSellValue);
				}
				goto __SUCCESS;
			}
			else //모든 예외 상황은 없다.
			{	//이런 말도 안되는 상황
				goto __FAIL;
			}
		}
		else
		{
COMMENT		MyLog(0,"Update Failed");
			goto __FAIL;
		}
	}

	goto __FAIL;

__FAIL:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		return;
	}
__SUCCESS:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);		
		p.h.header.type = CMD_MERCHANT_ITEM_BUY_COMFORM_RESULT;//타입을 교체 한다
		(*pMIB) = QueryResult;//보낼 패킷에 결과물을 실어 보낸다////구매중 상태로 만들어 졌을 것이다 아니라면 맵서버에서 구입 불가능이라고 처리 하라
		::QueuePacket(connections,iCn,&p,1);	
		return;
	}
}

void CAuction::RecvCMD_MERCHANT_ITEM_BUY_COMFORM_RESULT(const int iCn,t_packet &p)
{	//isend 를 거래 종료로 해준다 입금 완료다
	const int iKey = p.u.MerchantItemBuy.iKey;
	if(	IS_END_WAIT_TAKE	!= iKey//돈 뺏았으면 
	&&	IS_END_ALL_RIGHT	!= iKey)//돈 없으면
	{//이거 두개가 아니다
		MyLog(0,"Auction Critical Error!! Type => CMD_MERCHANT_ITEM_BUY_COMFORM_RESULT");
		return;
	}
	//isend 를 거래끝으로 해준다
	//구매 가능 한가? //인덱스,파는놈,아이템,isEnd == 0(구매가능) 으로 검색한다
	//카운트를 받아서 검사 하자 0 이면 안판다고 1 이면 판다 겠지.
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	::SQLAllocStmt(hDBC, &hStmt);
	char szQuery[255] ={0,};
	MERCHANT_ITEM_BUY *pMIB = &p.u.MerchantItemBuy;
	MERCHANT_ITEM_BUY QueryResult = *pMIB;//받은걸로 초기화를 시킨다

	char szSellerName[21];
	char szBuyerName[21];
	ConvertQueryString(pMIB->szSellerName, szSellerName, 21); // Finito prevents sql injection
	ConvertQueryString(pMIB->szBuyerName, szBuyerName, 21); // Finito prevents sql injection

	sprintf(szQuery,"EXEC MerchantItemBuyComform %d, '%s' , '%s', "//인덱스,이름,바꿀값,이전값
		" %d, %d, "
		"%d, %d, %d, %d, %d, %d, %d",
	pMIB->iIndex,
	szSellerName,
	szBuyerName,
	iKey,//맵서버가 셋팅한 값으로 해준다
	IS_END_BUYING,//구매중 상태여야 하고
	pMIB->SellItem.item_no,
	pMIB->SellItem.attr[0],
	pMIB->SellItem.attr[1],
	pMIB->SellItem.attr[2],
	pMIB->SellItem.attr[3],
	pMIB->SellItem.attr[4],
	pMIB->SellItem.attr[5] );

	//IS_END_ALL_RIGHT 상태에서만 지울 수 있다 여러번 지우는건 불가능 하다
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuery, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{
		retCode = SQLFetch(hStmt);
		if( retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		{
			int column = 0;
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iIndex,			0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_CHAR,	QueryResult.szSellerName,		20, &cbValue);
			::EatRearWhiteChar(QueryResult.szSellerName);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iKey,				0, &cbValue);//IsEnd값이 들어온다
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.dwSellValue,		0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.item_no,	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[0],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[1],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[2],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[3],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[4],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[5],	0, &cbValue);
			if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
			{	//여기 왔음은 데이타가 멀쩡하다는 증거.(업데이트에 성공 했다.
				if(QueryResult.dwSellValue != pMIB->dwSellValue)
				{
					MyLog(0,"Auction Critical Warning!! Type => CMD_MERCHANT_ITEM_BUY_COMFORM_RESULT SellValue NotMatch = DB %d, Client %d",QueryResult.dwSellValue, pMIB->dwSellValue);
					pMIB->dwSellValue = QueryResult.dwSellValue;
					MyLog(0,"Auction Critical Warning!! Type => CMD_MERCHANT_ITEM_BUY_COMFORM_RESULT Force Change Value = %d ",QueryResult.dwSellValue);
				}
				goto __SUCCESS;
			}
			else //모든 예외 상황은 없다.
			{	//이런 말도 안되는 상황
				goto __FAIL;
			}
		}
		else
		{
COMMENT		MyLog(0,"Non Select Result");
			goto __FAIL;
		}
	}

	goto __FAIL;
	
__FAIL:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		return;
	}
__SUCCESS:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		p.h.header.type = CMD_MERCHANT_ITEM_BUY_RESULT;//타입을 교체 한다
		(*pMIB) = QueryResult;//보낼 패킷에 결과물을 실어 보낸다
		::QueuePacket(connections,iCn,&p,1);
		return;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 구매 하기 끝(구매자)
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 검색 하기 시작(판매자
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAuction::RecvCMD_MERCHANT_SELL_LIST_REQUEST(const int iCn,t_packet &p)//리스트 요청(판매자가 보는것
{
	const char* szName = p.u.SellerItemRequest.szName;
	char szName2[20];
	ConvertQueryString(szName, szName2, 20); // Finito prevents sql injection
	
	SEARCHRESULTLIST FindResult;
	memset(&FindResult ,0, sizeof(SEARCHRESULTLIST));
	FindResult.iCn = p.u.SellerItemRequest.iCn;
	FindResult.iKey = p.u.SellerItemRequest.iKey;//021113 lsw

	ConvertQueryString(p.u.SellerItemRequest.szName, FindResult.szName, 20); // Finito prevents sql injection
	//memcpy(FindResult.szName,p.u.SellerItemRequest.szName,20);
	char szQuery[1000] ={0,};
	if(p.u.SellerItemRequest.iKey)
	{
	sprintf(szQuery,"EXEC MerchantItemSearchSellerSide %d, '%s',%d",
		p.u.SellerItemRequest.iIndex, szName2,IS_END_ALL_RIGHT);//인덱스 보다 크고 이름과 IsEnd 는 0 인것을 가져옵니다.
	}
	else
	{
	sprintf(szQuery,"EXEC MerchantItemSearchSellerSideInverse %d, '%s',%d",
		p.u.SellerItemRequest.iIndex, szName2,IS_END_ALL_RIGHT);//인덱스 보다 크고 이름과 IsEnd 는 0 인것을 가져옵니다.
	}

	if(SearchAuctionItem(&FindResult,szQuery))
	{
		t_packet rp;
		rp.h.header.type = CMD_MERCHANT_SELL_LIST_REQUEST_RESULT;
		rp.h.header.size = sizeof(SEARCHRESULTLIST);
		rp.u.SearchResultList= FindResult;
		::QueuePacket(connections,iCn,&rp,1);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 검색 하기 끝 (판매자
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 삭제 하기 시작(판매 취소)
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAuction::RecvCMD_MERCHANT_SELL_ITEM_DELETE_COMFORM(const int cn,t_packet &p)//판매 아이템을 삭제
{	//이름및 인덱스와 그에따른 아이템을 받아오도록 한다.
	//아이템이 있을 경우 그 정보를 비교 해봐야 한다
/*	
CREATE PROC MerchantItemCancelComform
(
@No	int,
@SellerName char(20),
@SetIsEnd int,
@BeforeIsEnd int
)
as

UPDATE MerchantSeller SET [IsEnd] = @SetIsEnd WHERE   ([SellerName] =@SellerName) AND ([No] = @No)AND ([IsEnd] = @BeforeIsEnd)
SELECT   [No], [SellerName], [IsEnd],[SellItemNo],[SellItemAttr1],[SellItemAttr2],[SellItemAttr3],[SellItemAttr4],[SellItemAttr5],[SellItemAttr6] FROM      MerchantSeller WHERE  ([SellerName] =@SellerName) AND ([No] = @No)
MerchantItemCancelComform 1,'화랑상우', 1,1 //자동으로 값 체크해서 결과 받아오는것이당.. ^^ IsEnd가 반드시 리턴된다.
*/// 한번 셋팅 되면 두번째 하더라도 셋팅이 불가능 하다
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	::SQLAllocStmt(hDBC, &hStmt);
	char szQuery[255] ={0,};
	SELLERITEMDELETE *pSID = &p.u.SellerItemDelete;
	SELLERITEMDELETE QueryResult = *pSID;//받은걸로 초기화를 시킨다
	sprintf(szQuery,"EXEC MerchantItemCancelComform %d, '%s' , %d , %d ",//인덱스,이름,바꿀값,이전값
	pSID->iIndex ,pSID->szName ,IS_END_DELETING,IS_END_ALL_RIGHT );//이름으로 카운트를 받는다
	//IS_END_ALL_RIGHT 상태에서만 지울 수 있다 여러번 지우는건 불가능 하다
	int iSellerCount = 0;
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuery, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{
		retCode = SQLFetch(hStmt);
		if( retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		{
			int column = 0;
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iIndex,			0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_CHAR,	QueryResult.szName,				20, &cbValue);
			::EatRearWhiteChar(QueryResult.szName);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iKey,				0, &cbValue);//IsEnd값이 들어온다
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.item_no,	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[0],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[1],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[2],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[3],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[4],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[5],	0, &cbValue);
			if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
			{	//여기 왔음은 데이타가 멀쩡하다는 증거.(업데이트에 성공 했다.
				goto __SUCCESS;
			}
			else //모든 예외 상황은 없다.
			{	//이런 말도 안되는 상황
				goto __FAIL;
			}
		}
		else
		{
			QueryResult.iKey = -1;
			goto __FAIL;
		}
	}
	else 
	{
		QueryResult.iKey = -1;
		goto __FAIL;
	}

__FAIL:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		return;
	}
__SUCCESS:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		p.h.header.type = CMD_MERCHANT_SELL_ITEM_DELETE_COMFORM_RESULT;//타입을 교체 한다
		*pSID = QueryResult;//보낼 패킷에 결과물을 실어 보낸다
		::QueuePacket(connections,cn,&p,1);	
		return;
	}	
}

void CAuction::RecvCMD_MERCHANT_SELL_ITEM_DELETE_COMFORM_RESULT(const int cn,t_packet &p)//판매 아이템을 삭제
{	//맵서버가 지급 했으면 IS_END_DELETE_COMPLETE 가 체크 되어 있을 것이고 
	//아니면 IS_END_ALL_RIGHT가 체크 되어 있을 것이다
	const int iKey = p.u.SellerItemDelete.iKey;
	if(	IS_END_DELETE_COMPLETE  != iKey
	&&	IS_END_ALL_RIGHT		!= iKey)
	{//이거 두개가 아니다
		MyLog(0,"Auction Critical Error!! Type => CMD_MERCHANT_SELL_ITEM_DELETE_COMFORM_RESULT");
		return;
	}

	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	::SQLAllocStmt(hDBC, &hStmt);
	char szQuery[255] ={0,};
	SELLERITEMDELETE *pSID = &p.u.SellerItemDelete;
	SELLERITEMDELETE QueryResult = *pSID;//받은걸로 초기화를 시킨다
	sprintf(szQuery,"EXEC MerchantItemCancelComform %d, '%s' , %d , %d ",//인덱스,이름,바꿀값,이전값
	pSID->iIndex,pSID->szName ,p.u.SellerItemDelete.iKey, IS_END_DELETING );//이름으로 카운트를 받는다
	int iSellerCount = 0;
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuery, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{
		retCode = SQLFetch(hStmt);
		if( retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		{
			int column = 0;
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iIndex,			0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_CHAR,	QueryResult.szName,				20, &cbValue);
			::EatRearWhiteChar(QueryResult.szName);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iKey,				0, &cbValue);//IsEnd값이 들어온다
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.item_no,	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[0],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[1],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[2],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[3],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[4],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[5],	0, &cbValue);
			
			if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
			{	//여기 왔음은 데이타가 멀쩡하다는 증거.(업데이트에 성공 했다.
				goto __SUCCESS;
			}
			else //모든 예외 상황은 없다.
			{	//이런 말도 안되는 상황
				goto __FAIL;
			}
		}
			goto __FAIL;
	}		

	goto __FAIL;

__FAIL:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		return;
	}
__SUCCESS:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		p.h.header.type = CMD_MERCHANT_SELL_ITEM_DELETE_RESULT;//타입을 교체 한다
		*pSID = QueryResult;//보낼 패킷에 결과물을 실어 보낸다
		::QueuePacket(connections,cn,&p,1);	
		return;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 삭제 하기 끝(판매 취소)
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 등록 하기
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAuction::RecvCMD_MERCHANT_SELL_ITEM_REGISTER_COMFORM(const int iCn,t_packet &p)//판매 아이템을 등록
{	//갯수를 체크하고 //결과값을 맵으로 보낸다
	//등록 할 수 있는지 자신이 등록한 갯수 체크
/*
CREATE PROC MerchantItemRegistCountComform
(
@SellerName char(20)
)
as

select count(*) FROM      MerchantSeller where SellerName = @SellerName

MerchantItemRegistCountComform '이름'
*/
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	::SQLAllocStmt(hDBC, &hStmt);
	char szQuery[255] ={0,};

	char szName[21];
	ConvertQueryString(p.u.SellerItemRegister.szName, szName, 21); // Finito prevents sql injection

	sprintf(szQuery,"EXEC MerchantItemRegistCountComform '%s'", szName);//이름으로 카운트를 받는다
	int iSellerCount = 0;
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuery, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{
		retCode = SQLFetch(hStmt);
		if( retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		{
			int column = 0;
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&iSellerCount	,	0, &cbValue);
			goto __SUCCESS;
		}
		else
		{
			goto __FAIL;
		}
	}		

	goto __FAIL;

__FAIL:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		return;
	}
__SUCCESS:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		p.h.header.type	= CMD_MERCHANT_SELL_ITEM_REGISTER_COMFORM_RESULT;//컴폼 결과다
		p.u.SellerItemRegister.iKey = (iSellerCount <MAX_SEARCH_RESULT_LIST)?1:0;//팔 수 있으면 1 아니면 0//MAX_SEARCH_RESULT_LIST 바꾸지 말고 값을 다른거 넣어라
		::QueuePacket(connections,iCn,&p,1);//받은 맵서버로 다시 전송
		return;//파는 갯수 문제
	}
}

void CAuction::RecvCMD_MERCHANT_SELL_ITEM_REGISTER_COMFORM_RESULT(const int iCn,t_packet &p)//판매 아이템을 등록
{
	//등록을 하고 IsEnd를 거래종료로 만든다. 이거 코딩도 넣을 것
	//	p.u.SellerItemRegister.	//Key를 조절 합시다 
	//판매물품 등록
/*
	CREATE PROC MerchantItemRegist
(
@SellerName char(20),
@ExchangeMoney numeric,
@RareType 	int,
@ItemLevel 	 int,
@TacticType 	 int,
@WearKind  	int,
@ItemNo		int,
@ItemAttr1	numeric,
@ItemAttr2	numeric,
@ItemAttr3	numeric,
@ItemAttr4	numeric,
@ItemAttr5	numeric,
@ItemAttr6	numeric
)
as

INSERT into  MerchantSeller(
	SellerName,	
	ExchangeMoney,
	RareType	,
	ItemLevel	,
	TacticType	 ,
	WearKind	 ,
	SellItemNo	 ,
	SellItemAttr1 ,
	SellItemAttr2 ,
	SellItemAttr3 ,
	SellItemAttr4 ,
	SellItemAttr5 ,
	SellItemAttr6 
) VALUES ( @SellerName, @ExchangeMoney, @RareType, @ItemLevel, @TacticType, @WearKind, 
@ItemNo, @ItemAttr1,@ItemAttr2,@ItemAttr3,@ItemAttr4,@ItemAttr5,@ItemAttr6 )

실행방법.
exec MerchantItemRegist '사람이름',돈,클래스,레어,아이템레벨,택틱,입는장소,아이템 ,attr1~6

*/
	lpSELLERITEMREGISTER lpSIR = &p.u.SellerItemRegister;
	char szQuery[500] = {0,};

	char szName[21];
	ConvertQueryString(lpSIR->szName, szName, 21); // Finito prevents sql injection

	sprintf(szQuery,"EXEC MerchantItemRegist '%s', "
		"%d,	"
		"%d,%d,%d,%d,"
		"%d, %d,%d,%d,%d,%d,%d",
	szName,
	
	(int)lpSIR->dwSellValue,

	lpSIR->iFKRareType,
	lpSIR->iFKLevel,
	lpSIR->iFKTacticType,
	lpSIR->iFKWearType,

	lpSIR->SellItem.item_no,
	(int)lpSIR->SellItem.attr[0],
	(int)lpSIR->SellItem.attr[1],
	(int)lpSIR->SellItem.attr[2],
	(int)lpSIR->SellItem.attr[3],
	(int)lpSIR->SellItem.attr[4],
	(int)lpSIR->SellItem.attr[5]
	);
		
	if( 1 == ::Querry_SQL(szQuery,hDBC))//드래곤 디비로 날림
	{//성공//등록 완료
		p.u.SellerItemRegister.iKey = 1;
	}
	else
	{//실패
		p.u.SellerItemRegister.iKey = 0;
	}
	p.h.header.type = CMD_MERCHANT_SELL_ITEM_REGISTER_RESULT;//결과를 날린다
	::QueuePacket(connections,iCn,&p,1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 등록 하기 끝
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 거래 결과 리스트 받기 시작
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAuction::RecvCMD_MERCHANT_RESULT_LIST_REQUEST(const int iCn,t_packet &p)
{
	const char* szName = p.u.SellerItemRequest.szName;
	char szName2[20];
	ConvertQueryString(szName, szName2, 20); // Finito prevents sql injection
	
	SEARCHRESULTLIST FindResult;
	memset(&FindResult ,0, sizeof(SEARCHRESULTLIST));
	FindResult.iCn = p.u.SellerItemRequest.iCn;
	FindResult.iKey = p.u.SellerItemRequest.iKey;//021113 lsw

	ConvertQueryString(p.u.SellerItemRequest.szName,FindResult.szName,20); // Finito prevents sql injection
	//memcpy(FindResult.szName,p.u.SellerItemRequest.szName,20);
	char szQuery[255] ={0,};

	if(p.u.SellerItemRequest.iKey)
	{
		sprintf(szQuery,"EXEC MerchantResultItemSearch %d,'%s',%d",
			p.u.SellerItemRequest.iIndex, szName2,IS_END_WAIT_TAKE);//이름과 IsEnd 는 0 인것을 가져옵니다.
	}
	else
	{
		sprintf(szQuery,"EXEC MerchantResultItemSearchInverse %d,'%s',%d",
			p.u.SellerItemRequest.iIndex, szName2,IS_END_WAIT_TAKE);//이름과 IsEnd 는 0 인것을 가져옵니다.
	}
	if(SearchAuctionItem(&FindResult,szQuery))
	{
		t_packet rp;
		rp.h.header.type = CMD_MERCHANT_RESULT_LIST_REQUEST_RESULT;
		rp.h.header.size = sizeof(SEARCHRESULTLIST);
		rp.u.SearchResultList= FindResult;
		::QueuePacket(connections,iCn,&rp,1);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 거래 결과 리스트 받기 끝
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 거래 결과물 가져가기 시작
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAuction::RecvCMD_MERCHANT_RESULT_TAKE_COMFORM(const int iCn,t_packet &p)
{	//이름및 인덱스와 그에따른 아이템을 받아오도록 한다.
	//아이템이 있을 경우 그 정보를 비교 해봐야 한다
	//SellerTake BuyerTake 체크를 한다
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	char szQuery[255] ={0,};
	MERCHANTRESULTTAKE *pMRT = &p.u.MerchantResultTake;
	MERCHANTRESULTTAKE QueryResult = *pMRT;//받은걸로 초기화를 시킨다

COMMENT	::MyLog(0,"O Index %d ItemNo %d",pMRT->iIndex , pMRT->SellItem);
COMMENT	::MyLog(0,"N Index %d ItemNo %d",QueryResult.iIndex , QueryResult.SellItem);

	char szName[21];
	ConvertQueryString(pMRT->szMyName, szName, 21); // Finito prevents sql injection

	if(pMRT->iKey)//판매자 이면
	{
		sprintf(szQuery,"EXEC MerchantResultItemTakeSellerSideComform %d, '%s' , %d , %d, %d ",//인덱스,이름,바꿀값,이전값
		pMRT->iIndex, szName, IS_END_WAIT_TAKE,IS_END_DELETING, IS_END_ALL_RIGHT );//이름으로 카운트를 받는다
	}
	else
	{
		sprintf(szQuery,"EXEC MerchantResultItemTakeBuyerSideComform %d, '%s' , %d , %d , %d",//인덱스,이름,바꿀값,이전값
		pMRT->iIndex, szName, IS_END_WAIT_TAKE,IS_END_DELETING, IS_END_ALL_RIGHT );//이름으로 카운트를 받는다
	}
COMMENT	MyLog(0,"RecvCMD_MERCHANT_RESULT_TAKE_COMFORM %s",szQuery);

	::SQLAllocStmt(hDBC, &hStmt);
	//IS_END_ALL_RIGHT 상태에서만 지울 수 있다 여러번 지우는건 불가능 하다
	int iSellerCount = 0;
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuery, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{
		retCode = SQLFetch(hStmt);
		if( retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		{
			int column = 0;
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iIndex,			0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_CHAR,	QueryResult.szSellerName,		20, &cbValue);
			::EatRearWhiteChar(QueryResult.szSellerName);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_CHAR,	QueryResult.szBuyerName,		20, &cbValue);
			::EatRearWhiteChar(QueryResult.szBuyerName);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iSellerTake,		0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iBuyerTake,		0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.dwSellValue,		0, &cbValue);//IsEnd값이 들어온다
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.item_no,	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[0],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[1],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[2],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[3],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[4],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[5],	0, &cbValue);
			
			if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
			{	//여기 왔음은 데이타가 멀쩡하다는 증거.(업데이트에 성공 했다.
COMMENT			MyLog(0,"Update Complete");
				goto __SUCCESS;
			}
			else //모든 예외 상황은 없다.
			{	//이런 말도 안되는 상황
COMMENT			MyLog(0,"Update Failed");
				goto __FAIL;
			}
		}
		else
		{
COMMENT		MyLog(0,"Non Select Result");
			QueryResult.iKey = -1;//주면 안된다!!
			goto __SUCCESS;
		}
	}
	else 
	{
COMMENT	::MyLog(0,"Query Failed");
		goto __FAIL;
	}

__FAIL:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		return;	
	}
__SUCCESS:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		p.h.header.type = CMD_MERCHANT_RESULT_TAKE_COMFORM_RESULT;//타입을 교체 한다
		*pMRT = QueryResult;//보낼 패킷에 결과물을 실어 보낸다
COMMENT	::MyLog(0,"O Index %d ItemNo %d",pMRT->iIndex , pMRT->SellItem);
COMMENT	::MyLog(0,"N Index %d ItemNo %d",QueryResult.iIndex , QueryResult.SellItem);
		::QueuePacket(connections,iCn,&p,1);
		return;
	}
}

void CAuction::RecvCMD_MERCHANT_RESULT_TAKE_COMFORM_RESULT(const int iCn,t_packet &p)
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	char szQuery[255] ={0,};
	MERCHANTRESULTTAKE *pMRT = &p.u.MerchantResultTake;
	MERCHANTRESULTTAKE QueryResult = *pMRT;//받은걸로 초기화를 시킨다

COMMENT	::MyLog(0,"O Index %d ItemNo %d",pMRT->iIndex , pMRT->SellItem);
COMMENT	::MyLog(0,"N Index %d ItemNo %d",QueryResult.iIndex , QueryResult.SellItem);

	char szMyName[21];
	ConvertQueryString(pMRT->szMyName, szMyName, 21); // Finito prevents sql injection

	switch(pMRT->iKey)
	{
	case 101://판매자 지급 성공
		{
			sprintf(szQuery,"EXEC MerchantResultItemTakeSellerSideComform %d, '%s' , %d , %d , %d",//인덱스,이름,바꿀값,이전값
			pMRT->iIndex, szMyName, IS_END_WAIT_TAKE,IS_END_DELETE_COMPLETE,IS_END_DELETING );//이름으로 카운트를 받는다
		}break;
	case 100://구매자 지급 성공
		{
			sprintf(szQuery,"EXEC MerchantResultItemTakeBuyerSideComform %d, '%s' , %d , %d , %d ",//인덱스,이름,바꿀값,이전값
			pMRT->iIndex, szMyName, IS_END_WAIT_TAKE,IS_END_DELETE_COMPLETE,IS_END_DELETING );//이름으로 카운트를 받는다
		}break;
	case 11://판매자 지급 실패
		{
			sprintf(szQuery,"EXEC MerchantResultItemTakeSellerSideComform %d, '%s' , %d , %d ",//인덱스,이름,바꿀값,이전값
			pMRT->iIndex, szMyName, IS_END_WAIT_TAKE,IS_END_ALL_RIGHT ,IS_END_DELETING);//이름으로 카운트를 받는다
			::Querry_SQL(szQuery);
			return;
		}break;
	case 10://구매자 지급 실패
		{
			sprintf(szQuery,"EXEC MerchantResultItemTakeBuyerSideComform %d, '%s' , %d , %d ",//인덱스,이름,바꿀값,이전값
			pMRT->iIndex, szMyName, IS_END_WAIT_TAKE,IS_END_ALL_RIGHT,IS_END_DELETING );//이름으로 카운트를 받는다
			::Querry_SQL(szQuery);
			return;
		}break;
	default:
		{
			MyLog(0,"Auction Critical Error!! Type => RecvCMD_MERCHANT_RESULT_TAKE_COMFORM_RESULT Query Make Fail %d",pMRT->iKey);
			return;
		}break;
	}
	::SQLAllocStmt(hDBC, &hStmt);
	
COMMENT	::MyLog(0,"RecvCMD_MERCHANT_RESULT_TAKE_COMFORM_RESULT %s",szQuery);

	int iSellerCount = 0;
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuery, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{
		retCode = SQLFetch(hStmt);
		if( retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		{
			int column = 0;
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iIndex,			0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_CHAR,	QueryResult.szSellerName,		20, &cbValue);
			::EatRearWhiteChar(QueryResult.szSellerName);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_CHAR,	QueryResult.szBuyerName,		20, &cbValue);
			::EatRearWhiteChar(QueryResult.szBuyerName);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iSellerTake,		0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.iBuyerTake,		0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.dwSellValue,		0, &cbValue);//IsEnd값이 들어온다
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.item_no,	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[0],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[1],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[2],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[3],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[4],	0, &cbValue);
			retCode = ::SQLGetData(hStmt, ++column, SQL_C_LONG,	&QueryResult.SellItem.attr[5],	0, &cbValue);
			if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
			{	//여기 왔음은 데이타가 멀쩡하다는 증거.(업데이트에 성공 했다.
COMMENT			MyLog(0,"Update Complete");				
				goto __SUCCESS;
			}
			else //모든 예외 상황은 없다.
			{	//이런 말도 안되는 상황
COMMENT			MyLog(0,"Non Select Result");
				goto __FAIL;
			}
		}
		else
		{
COMMENT		MyLog(0,"Non Select Result");
			goto __FAIL;
		}
	}
	else 
	{
COMMENT	MyLog(0,"Query Failed");
		goto __FAIL;
	}

__FAIL:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		return;
	}
__SUCCESS:
	{
		::SQLFreeStmt(hStmt, SQL_DROP);
		
		p.h.header.type = CMD_MERCHANT_RESULT_TAKE_RESULT;//타입을 교체 한다
		*pMRT = QueryResult;//보낼 패킷에 결과물을 실어 보낸다

COMMENT	::MyLog(0,"RO Index %d ItemNo %d",pMRT->iIndex , pMRT->SellItem);
COMMENT	::MyLog(0,"RN Index %d ItemNo %d",QueryResult.iIndex , QueryResult.SellItem);

		::QueuePacket(connections,iCn,&p,1);	
		return;
	}	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 거래 결과물 가져가기 끝
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//개인적 거래 리스트 시작
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAuction::RecvCMD_MERCHANT_DIRECT_EXCHANGE_LIST_REQUEST(const int iCn,t_packet &p)
{
	SEARCHRESULTLIST FindResult;
	memset(&FindResult ,0, sizeof(SEARCHRESULTLIST));
	FindResult.iCn = p.u.MerchantExchangeRequest.iCn;
	FindResult.iKey = p.u.MerchantExchangeRequest.iKey;//021113 lsw

	char szMyName[20];
	char szSellerName[20];
	ConvertQueryString(p.u.MerchantExchangeRequest.szMyName, szMyName, 20); // Finito prevents sql injection
	ConvertQueryString(p.u.MerchantExchangeRequest.szSellerName, szSellerName, 20); // Finito prevents sql injection

	memcpy(FindResult.szName,szMyName,20);
	char szQuery[1000] ={0,};

	if(p.u.MerchantExchangeRequest.iKey)//인덱스 위인가 아래인가.
	{
	sprintf(szQuery,"EXEC MerchantItemSearchDirectExchage '%s', %d, %d, %d, %d",
		szSellerName,
		IS_END_ALL_RIGHT,
		IS_END_ALL_RIGHT,
		IS_END_ALL_RIGHT,
		p.u.MerchantExchangeRequest.iIndex);
	}
	else
	{
	sprintf(szQuery,"EXEC MerchantItemSearchDirectExchageInverse '%s', %d, %d, %d, %d",
		szSellerName,
		IS_END_ALL_RIGHT,
		IS_END_ALL_RIGHT,
		IS_END_ALL_RIGHT,
		p.u.MerchantExchangeRequest.iIndex);
	}
	if(SearchAuctionItem(&FindResult,szQuery))
	{
		t_packet rp;
		rp.h.header.type = CMD_MERCHANT_DIRECT_EXCHANGE_LIST_REQUSET_RESULT;
		rp.h.header.size = sizeof(SEARCHRESULTLIST);
		rp.u.SearchResultList= FindResult;
		::QueuePacket(connections,iCn,&rp,1);
	}
	return;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//개인적 거래 리스트 끝
////////////////////////////////////////////////////////////////////////////////////////////////////////////


//<! BBD 040226	거래가 종료되거나 등록취소로 필요없는 레코드를 삭제하는 기능 추가
void CAuction::RecvCMD_MERCHANT_RECORD_DEL_CANCLE(const int iCn,t_packet &p)
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	char szQuery[255] ={0,};
	SELLERITEMDELETE *pSID = &p.u.SellerItemDelete;
	// 다음 인자를 매개변수로 하는 저장프로시저를 발동하여 지운다
	// (No, name = 파는놈, IsEnd = IS_END_DELETE_COMPLETE)
	::SQLAllocStmt(hDBC, &hStmt);
	::memset(szQuery, 0L, sizeof(szQuery));

	char szName[21];
	ConvertQueryString(pSID->szName, szName, 21); // Finito prevents sql injection

	sprintf(szQuery,"EXEC MerchantDelbyCancel %d, '%s' , %d", pSID->iIndex, szName , IS_END_DELETE_COMPLETE);

	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuery, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{
		// 쿼리 성공
		// 지워진건지 아닌지에 따라 지워졌으면 맵서버한테 알려야 한다
		retCode = SQLFetch(hStmt);
		if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		{
			int count;
			retCode = ::SQLGetData(hStmt, 1, SQL_C_LONG,	&count,			0, &cbValue);

			if(count == 1)		// 1개의 레코드가 삭제 되었다
			{
				// 혹 삭제했다고 맵서버에게 알려야 할까? 로그도 남기고 왔는데?
//				p.h.header.type = CMD_MERCHANT_RECORD_DEL_CANCLE; //레코드 삭제했다고 알린다
//				::QueuePacket(connections,cn,&p,1);
			}
			else
			{
				// 해당 레코드가 없다 BBD가 추가하기 이전부분에서 이미 문제가 발생했다
				// 판매취소하다가 나갔다거나 기타등등의 이유로 제대로 취소가 않됬다
			}

			::SQLFreeStmt(hStmt, SQL_DROP);
			return;
		}
	}
	else
	{
		// 이상황은 쿼리 에러
		MyLog(0,"Query Failed");
		::SQLFreeStmt(hStmt, SQL_DROP);
		return;
	}


}

void CAuction::RecvCMD_MERCHANT_RECORD_DEL_COMPLETE(const int iCn,t_packet &p)
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	char szQuery[255] ={0,};
	MERCHANTRESULTTAKE *pMRT = &p.u.MerchantResultTake;

	// 다음 인자를 매개변수로 하는 저장프로시저를 발동하여 지운다
	// (No, name = 파는놈이나 사는놈, IsEnd = IS_END_WAIT_TAKE, SellerTake = IS_END_DELETE_COMPLETE, BuyerTake = IS_END_DELETE_COMPLETE)
	if(pMRT->iKey == 100|| pMRT->iKey == 101)
	{
		::SQLAllocStmt(hDBC, &hStmt);
		::memset(szQuery, 0L, sizeof(szQuery));

		char szMyName[21];
		ConvertQueryString(pMRT->szMyName, szMyName, 21); // Finito prevents sql injection

		sprintf(szQuery,"EXEC MerchantDelbyComplete %d, '%s', %d, %d, %d"//인덱스,이름, 
			,pMRT->iIndex, szMyName, IS_END_WAIT_TAKE, IS_END_DELETE_COMPLETE, IS_END_DELETE_COMPLETE);

        retCode = SQLExecDirect(hStmt, (UCHAR *)szQuery, SQL_NTS);
		if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		{
			// 쿼리 성공
			retCode = SQLFetch(hStmt);
			if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
			{
				int count;
				retCode = ::SQLGetData(hStmt, 1, SQL_C_LONG,	&count,			0, &cbValue);

				if(count == 1)		// 1개의 레코드가 삭제 되었다
				{
					// 혹 삭제했다고 맵서버에게 알려야 할까? 로그도 남기고 왔는데?
//					p.h.header.type = CMD_MERCHANT_RECORD_DEL_COMPLETE; //레코드 삭제했다고 알린다
//					::QueuePacket(connections,cn,&p,1);
				}
				else
				{
					// 해당 레코드가 없다
					// 아직 지우기에는 조건이 충분치 못하다
				}

				::SQLFreeStmt(hStmt, SQL_DROP);
				return;
			}
			else
			{
				// 이상황은 쿼리 에러
				MyLog(0,"Query Failed");
				::SQLFreeStmt(hStmt, SQL_DROP);
				return;
			}
		}
		else
		{
			// 이상황은 쿼리 에러
			MyLog(0,"Query Failed");
			::SQLFreeStmt(hStmt, SQL_DROP);
			return;
		}
	}

}
//> BBD 040226	거래가 종료되거나 등록취소로 필요없는 레코드를 삭제하는 기능 추가
//<!  BBD 040303 백업테이블의 아이템 리스트 요청
void CAuction::RecvCMD_MERCHANT_BACKUP_LIST_REQUEST(const int iCn,t_packet &p)
{
	short int server_id = p.u.kein.send_db_direct_map.server_id;
	SELLERITEMREQUEST *pData = (SELLERITEMREQUEST*)p.u.kein.send_db_direct_map.data;
	

	SEARCHRESULTLIST FindResult;
	memset(&FindResult ,0, sizeof(SEARCHRESULTLIST));
	FindResult.iCn = pData->iCn;
	FindResult.iKey =pData->iKey;

	ConvertQueryString(pData->szName, FindResult.szName, 20); // Finito prevents sql injection
	//memcpy(FindResult.szName,pData->szName,20);

	char szQuery[255] ={0,};
	if(FindResult.iKey)
	{
		sprintf(szQuery,"Exec MerchantBackupListSearch %d, %s", FindResult.iKey, FindResult.szName);
			
	}
	else
	{
//		sprintf(szQuery,"EXEC MerchantResultItemSearchInverse %d,'%s',%d",
//			p.u.SellerItemRequest.iIndex, szName,IS_END_WAIT_TAKE);//이름과 IsEnd 는 0 인것을 가져옵니다.
	}
	if(SearchAuctionItem(&FindResult,szQuery))
	{
		DirectClient( CMD_MERCHANT_BACKUP_LIST_RESPONSE, server_id, iCn, &FindResult, sizeof( SEARCHRESULTLIST ) );
	}
}
//>  BBD 040303 백업테이블의 아이템 리스트 요청
//<! BBD 040303 백업테이블의 아이템 지급 요청
void CAuction::RecvCMD_MERCHANT_BACKUP_TAKE_REQUEST(const int iCn,t_packet &p)
{
	short int server_id = p.u.kein.send_db_direct_map.server_id;
	t_MerchantResultTake *pData = (t_MerchantResultTake*)p.u.kein.send_db_direct_map.data;
	MERCHANTRESULTTAKE *pMRT = &p.u.MerchantResultTake;

	char szQuery[255] ={0,};

	char szMyName[21];
	ConvertQueryString(pData->szMyName, szMyName, 21); // Finito prevents sql injection

	sprintf(szQuery,"Exec MerchantBackupByNoName %d, %s", pData->iIndex, szMyName);

	SEARCHRESULTLIST FindResult;
	memset(&FindResult, 0L, sizeof(FindResult));

	if(!SearchAuctionItem(&FindResult,szQuery))	// 받은 정보중 index넘버와 이름에 의존하여 검색한뒤
	{
		MyLog(0,"This Query Failed : %s", szQuery);		// 이상황은 쿼리 에러
		return;	// 쿼리 실패다
	}
	SEARCHRESULT * pRecord = &(FindResult.ResultList[0]);

	// 등록취소가능도 아니고 물건찾기 대기상태도 아니라면
	if(pRecord->iIsEnd != IS_END_ALL_RIGHT && pRecord->iIsEnd != IS_END_WAIT_TAKE)
	{
		return;		// 이런놈이 어케 여까지 왔나?
	}

	pMRT->iKey = pRecord->iIsEnd;	// 이때는 iKey를 IsEnd용도로 쓰자

	memset(szQuery, 0L, sizeof(szQuery));
	if(strcmp(pData->szMyName, pRecord->szSellerName))		// 이름으로 buyer인자 seller인지 구분하고
	{		// Buyer군...
		if(pRecord->iBuyerTake != IS_END_ALL_RIGHT)
		{
			return;			// 쓰벌 먹구 또 쳐먹으려구?
		}
		sprintf(szQuery, "Exec MerchantBackupTakeUpdate %d, 1, %d", pRecord->iIndex, IS_END_GIVIING);
	}
	else
	{		// Seller군...
		if(pRecord->iSellerTake != IS_END_ALL_RIGHT)
		{
			return;			// 쓰벌 먹구 또 쳐먹으려구?
		}
		sprintf(szQuery, "Exec MerchantBackupTakeUpdate %d, 0, %d", pRecord->iIndex, IS_END_GIVIING);
	}
	// 필드를 업데이트 시켜놓자	...Take 필드에 IS_END_GIVIING로 이놈이 지급중이라는 표시 셋팅후
	{
		HSTMT		hStmt = NULL;
		RETCODE		retCode;
		::SQLAllocStmt(hDBC, &hStmt);
		retCode = SQLExecDirect(hStmt, (UCHAR *)szQuery, SQL_NTS);
		if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		{
		}
		else
		{
			MyLog(0,"This Query Failed : %s", szQuery);		// 이상황은 쿼리 에러
		}
		::SQLFreeStmt(hStmt, SQL_DROP);
	}
	// 데이타 셋팅후
	pMRT->dwSellValue = pRecord->iSellValue;
	pMRT->iBuyerTake = pRecord->iBuyerTake;
	pMRT->iCn = pData->iCn;
	pMRT->iIndex = pRecord->iIndex;
	pMRT->iSellerTake = pRecord->iSellerTake;
	memcpy(&pMRT->SellItem, &pRecord->m_ResultItem, sizeof(ItemAttr));
	memcpy(pMRT->szBuyerName , pRecord->szBuyerName, sizeof(pMRT->szBuyerName));
	memcpy(pMRT->szMyName , pData->szMyName, sizeof(pMRT->szMyName));
	memcpy(pMRT->szSellerName , pRecord->szSellerName, sizeof(pMRT->szMyName));

	// 맵서버로 지급하라고 알린다
	p.h.header.type = CMD_MERCHANT_BACKUP_TAKE_REQUEST;
	p.h.header.size	= sizeof(MERCHANTRESULTTAKE);		// BBD 040308
	::QueuePacket(connections,iCn,&p,1);
	
}

void CAuction::RecvCMD_MERCHANT_BACKUP_TAKE_RESPONSE(const int iCn,t_packet &p)
{
	MERCHANTRESULTTAKE *pMRT = &p.u.MerchantResultTake;

	char szQuery[255] ={0,};
	switch(pMRT->iKey)
	{
	case 101://판매자 지급 성공
		{
			sprintf(szQuery, "Exec MerchantBackupTakeUpdate %d, 0, %d", pMRT->iIndex, IS_END_DELETE_COMPLETE);
		}break;
	case 100://구매자 지급 성공
		{
			sprintf(szQuery, "Exec MerchantBackupTakeUpdate %d, 1, %d", pMRT->iIndex, IS_END_DELETE_COMPLETE);
		}break;
	case 11://판매자 지급 실패
		{
			sprintf(szQuery, "Exec MerchantBackupTakeUpdate %d, 0, %d", pMRT->iIndex, IS_END_ALL_RIGHT);
		}break;
	case 10://구매자 지급 실패
		{
			sprintf(szQuery, "Exec MerchantBackupTakeUpdate %d, 1, %d", pMRT->iIndex, IS_END_ALL_RIGHT);
		}break;
	default:
		{
		}break;
	}

	// 어찌되었건 쿼리는 실행하고
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	::SQLAllocStmt(hDBC, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuery, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{
	}
	else
	{
		MyLog(0,"This Query Failed : %s", szQuery);		// 이상황은 쿼리 에러
	}
	::SQLFreeStmt(hStmt, SQL_DROP);

	if(pMRT->iKey >= 100)	// 이놈들은 성공한놈들 레코드확인이 필요하다
	{
		// 이 레코드가 지울수 있는지 확인한다
		MerchantBackup_Check_and_Delete(pMRT->iIndex);
	}

	// 클라이언트에게 리스트 다시보게 날리고
	SELLERITEMREQUEST data;
	data.iCn = pMRT->iCn;

	char szMyName[21];
	ConvertQueryString(pMRT->szMyName, szMyName, 21); // Finito prevents sql injection

	strcpy(data.szName, szMyName);
	data.iIndex = 0;
	data.iKey = 1;
	p.u.kein.send_db_direct_map.server_id = pMRT->iCn;

	memcpy(&(p.u.kein.send_db_direct_map.data), &data, sizeof(SELLERITEMREQUEST));

	RecvCMD_MERCHANT_BACKUP_LIST_REQUEST(iCn, p);
}

void CAuction::MerchantBackup_Check_and_Delete(int iIndex)
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	char szQuery[255] ={0,};

	sprintf(szQuery, "MerchantBackupRecordDelete %d", iIndex);
	::SQLAllocStmt(hDBC, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuery, SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{
	}
	else
	{
		MyLog(0,"This Query Failed : %s", szQuery);		// 이상황은 쿼리 에러
	}
	::SQLFreeStmt(hStmt, SQL_DROP);
}


//> BBD 040303 백업테이블의 아이템 지급 요청
