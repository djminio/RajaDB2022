﻿
#define GM_TOOL_VERSION 2122
const int MAX_NAME = 21;
extern int	CheckGameMakeTool(char *id, char ip[40]);	// 020830 YGI

//011030 lsw >
#define CMD_RARE_ITEM_MAKE_LOG		9008
typedef struct rare_item_make_log
{
	int map;
	//date; 자동 기록
	char maker[20];

	int itemno;//아이템 자체 넘버

	int today_count;//오늘 몇번 만들었나

	int grade;

	int mutanttype1;
	int mutanttype2;
	int mutanttype3;

	int addeditem1;
	int addeditem1limit;
	int addeditem2;
	int addeditem2limit;

	int resultlimit;
	int resultnowdur;//
	int resultmaxdur;//

	int why;
	int why2;

	int resource1limit;//리밋
	int resource2limit;
	int resource3limit;
	int resource4limit;
	int resource5limit;
	int resource6limit;

}t_rare_item_make_log;

#define CMD_CONFORM_SADONIX		9009
typedef struct CONFORMSADONIX
{
	int		cn;
	char	name[20];
	int		kind;
	ItemAttr item;
	int		x;
	int		y;
}t_ConformSadonix, *LPCONFORMSADONIX;

#define CMD_SADONIX_COUNT_UPDATE		9010//020505 lsw
typedef struct SADONIXCOUNTUPDATE
{
	short nSadTime;
}t_SadonixCountUpdate, *LPSADONIXCOUNTUPDATE;

/*
typedef struct SADONIXCONTROL
{
	int No;
	int Day[7];
}SadonixControl,*LPSadonixControl;

extern SadonixControl	sadonixcontrol[24];//24시간 이니까
*/

//acer7
extern BOOL DumpException(LPEXCEPTION_POINTERS lpExcep, char* szOutMsg, void *pData = NULL, int nSize = 0);
extern int IsBlockedId(const char *cheak_name);
extern void ProcessEnd(const int iDestroyType);
extern int IsSecretKeyCodeOk(const char *log_id, const char *szSecretKeyCode);


typedef struct ITEMRAREMAIN
{
	DWORD	grade : 4;//등급
	DWORD	soksung1 : 8;//속성1
	DWORD	soksung2 : 8;//속성2 멀티 속성
	DWORD	soksung3 : 8;//시간등급
	DWORD	iHighLevel : 3;//플러스 타입 값이 있다면 IsDynamicRare-->는 반드시 0 이어야 한다
	DWORD	IsDynamicRare : 1;//1 이면 기능 아이템 0 이면 레어 아이템
}RareMain, *LPRareMain;

typedef struct EVENTITEM
{
	int iIndex;
	int iEvevntType;
	int iItemNo;
	int iRareKind1;
	int iRareKind2;
	int iRareKind3;
	int iGrade;
	int isDynamic;
	int iHighRare;
}t_EventItem, *LPEVENTITEM;
const int MAX_EVENT_ITEM = 400;

extern int LoadEventRareItem();

#define CMD_COMFORM_RESET_ABILILTY				9020//020820 lsw
typedef struct COMFORMRESETABILILTY
{
	int cn;
	char szName[21];
	int iIsAble;//020821-1 lsw
}t_ComformResetAbililty, *LPCOMFORMRESETABILILTY;


//<soto-030514 수정.
typedef struct SEARCHPACKETCLIENT
{
	char	szKeyWord[21];	//키워드 검색에 들어갈
	char	szMerchant[21]; //상인이름 검색에 들어갈
	int		nPeriod;		//등록 기간 설정.// 0:1일, 1:3일,  2:일주일.
	int		iIndex;
	int		iKey;
}t_SearchPacketClient, *lpSEARCHPACKETCLIENT;

//구매자용 검색 구조체
#define CMD_MERCHANT_BUY_ITEM_SEARCH_SERVER			16002//020815 lsw
typedef struct SEARCHPACKETSERVER
{
	int iCn;
	char szName[21];
	t_SearchPacketClient	ClientMsg;
}t_SearchPacketServer, *lpSEARCHPACKETSERVER;
//>soto-030514 수정.


typedef struct SEARCHRESULT
{
	int			iIndex;
	char		szSellerName[21];
	char		szBuyerName[21];
	int			iSellValue;//판매금액은 20억을 넘기지 않습니다.
	int			iIsEnd;
	int			iSellerTake;
	int			iBuyerTake;
	ItemAttr	m_ResultItem;
}t_SearchResult, *lpSEARCHRESULT;

#define CMD_MERCHANT_BUY_ITEM_SEARCH_RESULT			16001//020815 lsw
#define CMD_MERCHANT_SELL_LIST_REQUEST_RESULT		16004
#define CMD_MERCHANT_RESULT_LIST_REQUEST			16030
#define CMD_MERCHANT_RESULT_LIST_REQUEST_RESULT		16031
const int MAX_SEARCH_RESULT_LIST = 24;
typedef struct SEARCHRESULTLIST
{
	int	 iCn;
	char szName[21];
	int iKey;
	SEARCHRESULT ResultList[MAX_SEARCH_RESULT_LIST];
}t_SearchResultList, *lpSEARCHRESULTLIST;
//
//구매자용 아이템 구입을 하겠다는 패킷
#define CMD_MERCHANT_ITEM_BUY					16005//클라이언트 에게 받고 
#define CMD_MERCHANT_ITEM_BUY_RESULT			16006
#define CMD_MERCHANT_ITEM_BUY_COMFORM			16007//디비와 통신
#define CMD_MERCHANT_ITEM_BUY_COMFORM_RESULT	16008//디비와 통신
typedef struct MERCHANT_ITEM_BUY
{
	int			iIndex;//구입할 아이템의 인덱스 값
	int			iCn;//커넥션 값
	char		szSellerName[21];//판매자 이름
	char		szBuyerName[21];//구매자 이름
	DWORD		dwSellValue;//판매금액은 20억을 넘기지 않습니다.
	ItemAttr	SellItem;
	int			iKey;
}t_MerchantItemBuy, *lpMERCHANTITEMBUY;

//
//판매자용 구조체
#define CMD_MERCHANT_SELL_ITEM_INFO_REQUEST		16003
typedef struct SELLERITEMREQUEST
{
	int iCn;
	int iIndex;
	int iKey;
	char szName[21];//자신의 이름을 보내서 아이템을 검색 합니다.
}t_SellerItemRequest, *lpSELLERITEMREQUEST;

#define CMD_MERCHANT_SELL_ITEM_REGISTER					16009//판매아이템을 등록 합니다.
#define CMD_MERCHANT_SELL_ITEM_REGISTER_RESULT			16010//판매아이템을 등록 합니다.
#define CMD_MERCHANT_SELL_ITEM_REGISTER_COMFORM			16011//판매아이템을 등록 합니다.(디비에 가능한지 요청 합니다.
#define CMD_MERCHANT_SELL_ITEM_REGISTER_COMFORM_RESULT	16012//판매아이템을 등록 합니다.(디비에 돈을 등록 하고 등등 ㅡㅡ;.. 어지러워라..
typedef struct SELLERITEMREGISTER
{
	int			iCn;
	char		szName[21];
	int			iFKRareType;
	int			iFKLevel;
	int			iFKTacticType;
	int			iFKWearType;
	POS			pos;
	DWORD		dwSellValue;
	ItemAttr	SellItem;
	int			iKey;
}t_SellerItemRegister, *lpSELLERITEMREGISTER;

#define CMD_MERCHANT_SELL_ITEM_DELETE					16020//판매를 취소합니다.//클라이언트용
#define CMD_MERCHANT_SELL_ITEM_DELETE_RESULT			16021//판매를 취소합니다.
#define CMD_MERCHANT_SELL_ITEM_DELETE_COMFORM			16022//판매를 취소합니다.//디비에 요청
#define CMD_MERCHANT_SELL_ITEM_DELETE_COMFORM_RESULT	16023//판매를 취소합니다.//디비에 아이템을 지우고 클라이언트에게 지급
#define CMD_MERCHANT_RECORD_DEL_CANCLE					16024	// BBD 040226 판매 취소로 레코드 삭제 요청.
#define CMD_MERCHANT_RECORD_DEL_CANCLE_RESULT			16025	// BBD 040226 판매 취소로 레코드 삭제 결과. 아직 사용치 않음
#define CMD_MERCHANT_RECORD_DEL_COMPLETE				16026	// BBD 040226 거래 종료로 레코드 삭제 요청.
#define CMD_MERCHANT_RECORD_DEL_COMPLETE_RESULT			16027	// BBD 040226 거래 종료로 레코드 삭제 결과. 아직 사용치 않음

typedef struct SELLERITEMDELETE
{
	int			iIndex;//판매물품의 인덱스
	int			iCn;
	char		szSellerName[21];
	char		szName[21];
	DWORD		dwSellValue;
	ItemAttr	SellItem;
	int			iKey;
}t_SellerItemDelete, *lpSELLERITEMDELETE;


#define CMD_MERCHANT_RESULT_TAKE						16032
#define CMD_MERCHANT_RESULT_TAKE_RESULT					16033
#define CMD_MERCHANT_RESULT_TAKE_COMFORM				16034
#define CMD_MERCHANT_RESULT_TAKE_COMFORM_RESULT			16035

#define	CMD_MERCHANT_BACKUP_LIST_REQUEST				16036	// BBD 040303
#define CMD_MERCHANT_BACKUP_LIST_RESPONSE				16037	// BBD 040303
#define	CMD_MERCHANT_BACKUP_TAKE_REQUEST				16038	// BBD 040303
#define	CMD_MERCHANT_BACKUP_TAKE_RESPONSE				16039	// BBD 040303

#define CMD_EVENTRAREITEM_REQ							16300	// BBD 040308
#define CMD_EVENTRAREITEM_RES							16301	// BBD 040308

typedef struct MERCHANTRESULTTAKE
{
	int			iIndex;//판매물품의 인덱스
	int			iCn;
	char		szMyName[21];
	char		szSellerName[21];
	char		szBuyerName[21];
	DWORD		dwSellValue;
	ItemAttr	SellItem;
	int			iSellerTake;
	int			iBuyerTake;
	int			iKey;
}t_MerchantResultTake, *lpMERCHANTRESULTTAKE;

#define CMD_MERCHANT_DIRECT_EXCHANGE_LIST_REQUSET					16090
#define CMD_MERCHANT_DIRECT_EXCHANGE_LIST_REQUSET_RESULT			16091
#define CMD_MERCHANT_EXCHANGE_LIST_REQUSET							16100
#define CMD_MERCHANT_EXCHANGE_LIST_REQUSET_RESULT					16101
typedef struct MERCHANTEXCHANGEREQUEST
{
	int			iIndex;//0으로 날리도록 하고
	int			iCn;
	char		szSellerName[21];
	char		szMyName[21];
	int			iKey;//인덱스 위인가 아래인가.
}t_MerchantExchangeRequest, *lpMERCHANTEXCHANGEREQUEST;

enum eHighLv
{
	H_LV_NO_HIGH_ITEM = 0,
	H_LV_HIGH_ITEM = 1,
	H_LV_LEGEND_ITEM = 2,
};

const int CMD_SELECTED_CHAR_RESULT_CLIENT_BOTH_DB_DEMON = 16103;
typedef struct SELECTEDCHARRESULT
{
	int			iKey;
	char		szName[21];
	int			iLv;
}t_SelectedCharResult, *LPSELECTEDCHARRESULT;

// Mail System //////////////////////////////////////////////////////////////////////////////
const int MAX_MAIL_PAGE = 12;
const int MAX_MAIL_PAGE_COUNT = 5;//최대 페이지수
const int MAX_MAIL_RECEIVER = 5;
const int MAX_MAIL_BODY_LEN = 1000;

typedef struct MAILDATA
{
	int iIndex;

	int iType;
	bool bIsRead;

	char szSender[20];
	char szReceiver[20];

	char szTitle[60];
	TIMESTAMP_STRUCT	date;
	int	iBodyIndex;
}t_MailDdata, *LPMAILDATA;

typedef struct MAILBODY
{
	int iIndex;
	char szBody[MAX_MAIL_BODY_LEN];
}t_MailBody, *LPMAILBODY;

const int CMD_MAIL_REQ_BODY = 16102;//해당 메일의 바디
typedef struct REQESTMAILBODY
{
	//	int iWantMailType;
	int iMailIndex;
	char szName[MAX_NAME];
}t_ReqestMailBody, *LPREQESTMAILBODY;

const int CMD_MAIL_REQ_BODY_RESULT = 16113;//해당 메일의 바디
typedef struct REQESTMAILBODYRESULT
{
	//	int iWantMailType;
	int iMailIndex;
	int iType;
	char szSender[MAX_NAME];
	char szReceiver[MAX_NAME];
	char szTitle[MAX_NAME];
	TIMESTAMP_STRUCT	date;
	char szBody[MAX_MAIL_BODY_LEN];
}t_ReqestMailBodyResult, *LPREQESTMAILBODYRESULT;

const int CMD_MAIL_REQUEST_LIST = 16114;//한페이지 분량의 메일 리스트.
typedef struct REQESTMAILLIST
{
	int iWantMailType;
	int iPageIndex;
	char szName[MAX_NAME];
}t_ReqestMailList, *LPREQESTMAILLIST;

#define CMD_SEND_MAIL_GUILD					10355
#define CMD_REP_RECV_GUILD_MAIL_TITLE		10358

#define CMD_REQ_RECV_MAIL_BODY_GUILD		10359	// 길드 내용 확인
#define CMD_UPDATE_GUILD_MAIL_ID			10360
#define CMD_RECV_MAIL_DELETE_GUILD			10361

const int CMD_MAIL_SEND = 10142;	// 메일 보내기

typedef struct MAILSEND
{
	int iType;
	char szTarget[MAX_NAME * MAX_MAIL_RECEIVER];//5명
	char szSender[MAX_NAME];
	char szTitle[60];
	char szBody[MAX_MAIL_BODY_LEN];
}t_MailSend, *LPMAILSEND;

const int CMD_MAIL_LIST_FROM_DBDEMON = 16100;
typedef struct MAILLISTRESULT
{
	char szName[MAX_NAME];
	int iWantViewType;
	int iWantViewPage;
	MAILDATA MailData[MAX_MAIL_PAGE];
}t_MailListResult, *LPMAILLISTRESULT;

const int CMD_MAIL_DELETE = 10143;	// 메일 삭제
const int CMD_MAIL_REPAIR = 10145;	// 메일 삭제
typedef struct MAILDELETE
{
	int cn;
	char szName[MAX_NAME];
	int aiMailIndex[MAX_MAIL_PAGE];
}t_MailDelete, *LPMAILDELETE;

#define CMD_REQ_RECV_MAIL_BODY				10144	// 메일 내용 요청

#define CMD_REP_RECV_MAIL_TITLE				10145
#define CMD_REP_RECV_MAIL_BODY				10146
#define	CMD_RECV_MAIL_DELETE				10147

const int CMD_MAIL_ALERT = 16400;//메일 얼럿

typedef struct HWOARANG_PACKET
{
	union
	{
		char	data[MAX_PACKET_SIZE];
		t_SelectedCharResult	SelectedCharResult;

		t_ReqestMailList			ReqestMailList;
		t_MailListResult			MailListResult;
		t_MailSend					MailSend;
		t_MailDelete				MailDelete;
		t_ReqestMailBody			ReqestMailBody;
		t_ReqestMailBodyResult		ReqestMailBodyResult;
	}rang;
}t_Hwoarang;