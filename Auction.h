// Auction.h: interface for the CAuction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUCTION_H__65C7ED7E_9020_467F_AB76_8528EE975EC8__INCLUDED_)
#define AFX_AUCTION_H__65C7ED7E_9020_467F_AB76_8528EE975EC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAuction  
{
	enum IsEndType
	{
		IS_END_ALL_RIGHT	= 0,	//���� �� �� �ִ� ����
		IS_END_DELETING		= 1,	//������
		IS_END_BUYING		= 3,	//������
		IS_END_WAIT_TAKE	= 4,		//�������⸦ �ٶ�� ����
		IS_END_DELETE_COMPLETE = 5,
		IS_END_GIVIING		= 6,	// BBD 040303 �������μ����� ���ִ�
	};
	enum ItemType
	{
		NORMAL_ITEM	= 0,
		RARE_ITEM	= 1,
		HIGH_ITEM	= 2,
		DYNAMIC_RARE_ITEM	= 3,
		SET_ITEM	= 4
	};

	enum ItemLevelType
	{
		LVMIN		= 0,
		LV10TO20	= 1,
		LV20TO30	= 2,
		LV30TO40	= 3,
		LV40TO50	= 4,
		LV50TO60	= 5,
		LV60TO70	= 6,
		LV70TO80	= 7,
		LV80TO90	= 8,
		LV90TO100	= 9,
		LV100TO110	= 10,
		LV110TO120	= 11,
		LV120TO130	= 12,
		LV130TO140	= 13,
		LV140TO150	= 14,
		LVMAX		= 15
	};
	enum WearTypeGroup
	{
		FK_WT_TYPEMIN	= 0,
		FK_WT_WEAPON	= 1,
		FK_WT_HELMET	= 2,
		FK_WT_ARMOR		= 3,
		FK_WT_SHOE		= 4,
		FK_WT_NECK		= 5,
		FK_WT_UNIQUE	= 6,
		FK_WT_TYPEMAX	= 7
	};
public:
	CAuction();
	virtual ~CAuction();
private://�˻������
	void Clear();
	int SearchAuctionItem(SEARCHRESULTLIST *List, const char* szQuery);
public:
	//<!  BBD 040303 ������̺��� ������� �߰��� �Լ�
	void MerchantBackup_Check_and_Delete(int iIndex);
	void RecvCMD_MERCHANT_BACKUP_TAKE_RESPONSE(const int iCn,t_packet &p);
	void RecvCMD_MERCHANT_BACKUP_TAKE_REQUEST(const int iCn,t_packet &p);
	void RecvCMD_MERCHANT_BACKUP_LIST_REQUEST(const int iCn,t_packet &p);	// ������̺��� ������ ����Ʈ ��û
	//>  BBD 040303 ������̺��� ������� �߰��� �Լ�
	//<! BBD 040226	�ŷ��� ����ǰų� �����ҷ� �ʿ���� ���ڵ带 �����ϴ� ��� �߰�
	void RecvCMD_MERCHANT_RECORD_DEL_CANCLE(const int iCn,t_packet &p);
	void RecvCMD_MERCHANT_RECORD_DEL_COMPLETE(const int iCn,t_packet &p);
	//> BBD 040226	�ŷ��� ����ǰų� �����ҷ� �ʿ���� ���ڵ带 �����ϴ� ��� �߰�

//---->�����ڿ�
	int RecvCMD_MERCHANT_BUY_LIST_REQUEST(const int iCn,t_packet &p);//����Ʈ ��û(�����ڰ� ���°�//�˻��Ⱑ ȣ��

	void RecvCMD_MERCHANT_ITEM_BUY_COMFORM(const int iCn,t_packet &p);//�ʼ����� �̰Ż� �� �ִ��� �����
	void RecvCMD_MERCHANT_ITEM_BUY_COMFORM_RESULT(const int iCn,t_packet &p);//�ʼ����� �Ա��� �Ѵ�
//<----
//---->�Ǹ��ڿ�
	void RecvCMD_MERCHANT_SELL_LIST_REQUEST(const int iCn,t_packet &p);//����Ʈ ��û(�Ǹ��ڰ� ���°�

	void RecvCMD_MERCHANT_SELL_ITEM_DELETE_COMFORM(const int cn,t_packet &p);//�Ǹ� �������� ����
	void RecvCMD_MERCHANT_SELL_ITEM_DELETE_COMFORM_RESULT(const int cn,t_packet &p);//�Ǹ� �������� ����
	
	void RecvCMD_MERCHANT_SELL_ITEM_REGISTER_COMFORM(const int iCn,t_packet &p);//�Ǹ� �������� ���(����üũ)
	void RecvCMD_MERCHANT_SELL_ITEM_REGISTER_COMFORM_RESULT(const int iCn,t_packet &p);//�Ǹ� �������� ���(���� ���)
//<----
//---->�ŷ����
	void RecvCMD_MERCHANT_RESULT_LIST_REQUEST(const int iCn,t_packet &p);

	void RecvCMD_MERCHANT_RESULT_TAKE_COMFORM(const int iCn,t_packet &p);
	void RecvCMD_MERCHANT_RESULT_TAKE_COMFORM_RESULT(const int iCn,t_packet &p);
	void RecvCMD_MERCHANT_DIRECT_EXCHANGE_LIST_REQUEST(const int iCn,t_packet &p);
//<----
};
extern CAuction Auction;
#endif // !defined(AFX_AUCTION_H__65C7ED7E_9020_467F_AB76_8528EE975EC8__INCLUDED_)