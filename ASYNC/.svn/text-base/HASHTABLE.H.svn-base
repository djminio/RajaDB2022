#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "stdafx.h"

struct BUCKET;

struct LIST
{
	LIST*		pNext;
	LIST*		pPrv;
	BUCKET*		pBucket;
	LIST()		{pNext = NULL; pPrv = NULL; pBucket = NULL;}
};

struct BUCKET
{
	DWORD		dwKey;
	void*		pVoid;
	LIST*		pList;
	BUCKET*		pNext;
	BUCKET*		pPrv;
	BUCKET(void* pvoid,DWORD key)	{pVoid = pvoid;dwKey = key; pNext = NULL; pPrv = NULL;}

};

class CHashTable
{
protected:
	DWORD				m_dwDataNum;
	DWORD				m_dwMaxBucketNum;
	BUCKET**			m_ppBucketTable;
	LIST*				m_pListHead;
	LIST*				m_pListTail;
	LIST*				m_pListCur;

	DWORD	inline		GetDataNum() {return m_dwDataNum;}
	bool				Initialize(DWORD dwMaxBucketNum);
	LIST*				AddList(BUCKET* pBucket);
	void				RemoveList(LIST* pList);
	void				Init();
	bool				Add(void* pVoid,DWORD dwKey);
	void*				GetData(DWORD dwKey);
	void*		 		GetData();
	void	inline 		SetPositionHead() {m_pListCur = m_pListHead;}
	void				Remove(DWORD dwKey);
	void				RemoveAll();
public:
	~CHashTable();
};

#endif
