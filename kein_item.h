#define MAX_MONEY	1000000


#define IN_COIN		10029
#define IN_COINS	10030


#define WIZARD_SPELL 0
#define PRIEST_SPELL 1

//###########################################################
#define CIA_DURATION		101		// 아이템 속성 바꾸기 
#define CIA_VIEW_CHANGE		102
#define CIA_MUCH			103




extern void DeleteItem( ItemAttr *item );
extern void CheckChracterTimeElapsed_Kein( CHARLIST *ch, int cn );
extern void killCharacter(CHARLIST *a, CHARLIST *d );
extern int GetItemView( int item_no, int is_man );
extern void HungryMuchAdd( CHARLIST *ch, double type );
extern void SetItemPos(int type, POS* IP_set);
extern void SetItemPos(int type, int p, POS* IP_set);
extern void SetItemPos(int type, int p1, int p2, int p3, POS* IP_set);
extern DWORD GetMoneyByItem( CHARLIST *ch );
extern int DropItem( int x, int y, ItemAttr *item );


extern int SearchItemPosByNumber(int num, int &a, int &b, int &c, CHARLIST *ch);
extern int SearchCoinItem( int &a, int &b, int &c, CHARLIST *ch );
extern ItemAttr *SearchItemOfInvByKind( int kind, CHARLIST *ch );
extern int SubtractMoney( DWORD money, CHARLIST *ch );
extern int AddMoney( DWORD money, CHARLIST *ch );
extern ItemAttr *SearchInv( CHARLIST *ch );
extern int IsEqualPosByPos( POS first, POS second );
extern void SendServerKillMon( short int cn );		// op_battle 에서 사용
extern int GetTotalItemWeight( CHARLIST *ch );
extern int calcAttackPowerMax( CHARLIST *a );

extern void CheckItem( short int cn ); // 잘못된 아이템을 가지고 있는지 
extern int CheckAutoDivideMoney( ItemAttr *item, short int cn );		// 100000을 넘은 아이템 처리
extern void GetItemDuration( ItemAttr item, WORD &d_curr, WORD &d_max );