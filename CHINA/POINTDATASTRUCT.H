#ifndef _POINTDATASTRUCT_H_
#define _POINTDATASTRUCT_H_


#define  CHECK_LOGIN 150
#define  CHECK_LOGOUT 151
#define  RETURN_USERDATA 152

//acer7
#define DEBUGMODE


typedef struct _tagchecklogin
{
	//int protocol; //confirm the protocol must=150(CHECK_LOGIN)
	//2001/02/23 zhh
	char ID[20]; //user'ID
}CheckLogin;

typedef struct _tagcheckloginWithIP//021007 lsw
{
	//int protocol; //confirm the protocol must=150(CHECK_LOGIN)
	//2001/02/23 zhh
	char ID[20]; //user'ID
	char IP[20];
}CheckLoginWithIP;

typedef struct _tagchecklogout
{
	//int protocol; //must =151(CHECK_LOGOUT)
	char ID[20]; // user'ID
	char logintime[15];   //User's logout time EX:20001220145056 
	char logouttime[15];  //User's login time EX:20001220152359
	char IP[20]; //login ip,such as 210.241.157.145
}CheckLogout;

typedef struct _taguserdata
{
	//int protocol; //must =151(CHECK_LOGOUT) or 150(CHECK_LOGIN)
	//must=RETURN_USERDATA
	//2001/02/23 zhh
	char ID[20]; //user'ID
	char type[2]; //type=P or M
	long point; //user's Points(using in type=P)
	char expiredata[9];  //User's expire data(using in type=M) EX:20001220
	BOOL success; //if login or logout success
}UserData;

///////////////////////Shop System 관련 디파인 및 구조체 정의 부분 ///////////////////////
#define LOTTO_SYSTEM	1

#define SHOP_OK 1 //return lotto deduct ok
#define FAIL_DB 2 //return lotto deduct fail , because query db error
#define FAIL_POINT 3 //return lotto deduct fail , because point no enough 

#define SHOP_SYSTEM_POINT_INFO	500				
#define  SHOP_SYSTEM_POINT_INFO_RETURN	501

typedef struct tag_SHOP_SYSTEM_POINT
{
	char	szID[20];
	int	nPoint;       //(Raja ==> PointServer : -1)  (PointServer ==> Raja: User Have Point)
	int	nShoppingType; //LOTTO_SYSTEM, and After we will Added
	int	nSuccess; //query or deduct is success or 
}st_SHOP_SYSTEM_POINT;


#define SHOP_SYSTEM_DEDUCT_POINT 502
#define	SHOP_SYSTEM_DEDUCT_POINT_RETURN 503

typedef	struct tag_SHOP_SYSTEM_POINT_REDUCT
{
	st_SHOP_SYSTEM_POINT	stShopSystemPoint;	
	int		nDeductPoint; //the point need to deduct
	char	szKey[10]; 	//for double check, it maybe lotto's number, or item's number, it will write to transation db
}st_SHOP_SYSTEM_POINT_REDUCT;

///////////////////////끝//////////////////////////////////////////////////////////////////



extern void DebugPrintf(const char *fmt, ...);
void DebugPrintf(const char *fmt, ...);
#endif //_POINTDATASTRUCT_H_