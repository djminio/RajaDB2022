// LottoDBMgr.h: interface for the CLottoDBMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOTTODBMGR_H__44A61846_F832_4D75_A699_801C981954F9__INCLUDED_)
#define AFX_LOTTODBMGR_H__44A61846_F832_4D75_A699_801C981954F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLottoDBMgr  
{
	static	CLottoDBMgr*	m_pClass;
//	LOTTO_EVENT_INFO		m_Lotto_Info;	
	int						m_anWinNumbers[10];
public:
	int GetLottoCount(const char* pCharName,int nLottoID);
	void RecvLottoSeek(t_LOTTOPAPER_SEEK *pLotto_Seek,int cn);
	int GetLottoPay();
	int m_nLottoPay;
	int m_anWinNumberCount4Grade[5];
	int m_anItemCount4Grade[5];
	int m_nLottoNumberCount;
//	int m_nGiveItemNumber;
	int	m_anGiveItemNumber[5];

	void RecvCheckOpenWinnerMenu(t_WINNER_MENU* pWinnerMenu,int cn);
	void RecvLottery(LOTTO_EVENT_INFO* pLottery,int cn);
	int CheckTwoLottos(int anTarget[],int anSource[],int count);
	void RecvDelUser(t_CHECK_WINNER* pDelUser, int cn);		// BBD 040127 인자 추가
	void RecvWinnerCheck(t_CHECK_WINNER* pCheckWinner,int cn);
	void RecvLottoBuy(t_BUY_LOTTO* pBuyLotto);
	void GetUserIDFromName(const char* pName,char strID[]);
	int ExistLottoNumber(int anNumber[],char *pUserID, int nLottoID);//soto-LottoADD
	int GetBuyCountByUser(char *pUserID, int nLottoID);
	void RecvCanBuyLotto(t_BUY_LOTTO* pCanBuy,int cn);
	bool InsertToTabeInfo(LOTTO_EVENT_INFO* pInfo);
	void SendNewEvent(LOTTO_EVENT_INFO* pInfo,int cn);
	HDBC m_hDragonDB;
	bool LoadTable(HDBC hDBC);
	void RecvNewEvent(LOTTO_EVENT_INFO* pInfo,int cn);
	void Clear();
	static	CLottoDBMgr*	GetClass(){return m_pClass;}
	static	bool Create(){if(m_pClass)return false;new CLottoDBMgr;return true;}
	static	void Destroy(){if(m_pClass){delete m_pClass;m_pClass = NULL;}}
	CLottoDBMgr();
	virtual ~CLottoDBMgr();

};

extern inline CLottoDBMgr* LottoDBMgr(){return CLottoDBMgr::GetClass();}

#endif // !defined(AFX_LOTTODBMGR_H__44A61846_F832_4D75_A699_801C981954F9__INCLUDED_)
