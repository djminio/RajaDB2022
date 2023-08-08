// ShopDemon.h: interface for the CShopDemon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOPDEMON_H__A3445CC4_59F9_42E0_8204_D86099CC0261__INCLUDED_)
#define AFX_SHOPDEMON_H__A3445CC4_59F9_42E0_8204_D86099CC0261__INCLUDED_

#if _MSC_VER > 1000
#pragma once

#endif // _MSC_VER > 1000

#include "Network.h"
#include "./china/pointdatastruct.h"



typedef struct tag_LottoBuySave
{
	t_BUY_LOTTO Buy_Lotto;//사용자의 로또구입을 위한 정보.
	char	szUserID[20]; //유저 아이디가 저장된다.
	int cn; //사용자가 있는 맵의핸들.
}t_LottoBuySave;



#include <list>
using namespace std;

class CShopDemon  
{
private:
	static CShopDemon* m_pClass;
	list<t_LottoBuySave>				m_ltLottoBuySaveList;
	typedef list<t_LottoBuySave>::iterator		ITOR_BUYSAVE;
	

public:
	static CShopDemon* GetClass(){return m_pClass;}
	static bool Create()
	{
		if(NULL == m_pClass)
		{
			new CShopDemon;
			return true;
		}
		return false;
	}
	static bool Destroy()
	{
		if(m_pClass)
		{
			delete m_pClass;
			return true;
		}
		return false;
	}
	CShopDemon();
	virtual ~CShopDemon();
public:
	void RecvLottoBuy(t_BUY_LOTTO *pBuyLotto, int cn);
	void RecvShopProcess(int nProtocol,void* data,int datasize);
	void RecvCanBuyLotto(t_BUY_LOTTO *pCanBuy,int cn);

};

inline CShopDemon*	GetShopDemon(){return CShopDemon::GetClass();}

#endif // !defined(AFX_SHOPDEMON_H__A3445CC4_59F9_42E0_8204_D86099CC0261__INCLUDED_)
