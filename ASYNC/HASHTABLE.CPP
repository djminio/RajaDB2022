#include "hashtable.h"

bool CHashTable::Initialize(DWORD dwMaxBucketNum)
{	
	m_dwDataNum = 0;
	m_dwMaxBucketNum = dwMaxBucketNum;
	m_ppBucketTable = NULL;
	m_pListHead = NULL;
	m_pListTail = NULL;
	m_pListCur = NULL;

	m_ppBucketTable = new BUCKET*[m_dwMaxBucketNum];
	
	if (!m_ppBucketTable)
		return false;

	memset(m_ppBucketTable,0,sizeof(BUCKET*)*m_dwMaxBucketNum);
	
	return true;

}
bool CHashTable::Add(void* pVoid,DWORD dwKey)
{
	DWORD index = dwKey % m_dwMaxBucketNum;
	
	BUCKET*	cur = NULL;
	BUCKET*	prv = NULL;
	BUCKET*	next = NULL;


	if (!m_ppBucketTable[dwKey])
	{

		m_ppBucketTable[index] = new BUCKET(pVoid,dwKey);
		m_ppBucketTable[index]->pList = AddList(m_ppBucketTable[index]);

		goto seg_ok;
	}
	else 
	{
		cur = m_ppBucketTable[index];
		while (cur)
		{
			if (cur->dwKey == dwKey)
				return false;

			prv = cur;
			cur = cur->pNext;
			
		}
		cur = prv->pNext = new BUCKET(pVoid,dwKey);
		cur->pPrv = prv;
		cur->pList = AddList(cur);
		
		goto seg_ok;
	
	}
seg_ok:
	m_dwDataNum++;
	
	return true;
}

LIST* CHashTable::AddList(BUCKET* pBucket)
{
	LIST*	cur = NULL;
	LIST*	prv = NULL;
	LIST*	next = NULL;

	if (!m_pListHead)
	{
		m_pListCur = m_pListHead = new LIST;
		m_pListTail = m_pListCur;
		m_pListCur->pBucket = pBucket;
		pBucket->pList = m_pListHead;
		return m_pListHead;
	}
	else 
	{
		cur = m_pListTail->pNext = new LIST;
		cur->pPrv = m_pListTail;
		m_pListTail = cur;
		cur->pBucket = pBucket;
		pBucket->pList = cur;
		return cur;
	}
	return NULL;
}

void CHashTable::Remove(DWORD dwKey)
{
	DWORD dwIndex = dwKey%m_dwMaxBucketNum;

	BUCKET*	cur = m_ppBucketTable[dwIndex];
	BUCKET*	prv = NULL;
	BUCKET*	next = NULL;
	
	while (cur)
	{
		if (cur->dwKey == dwKey)
		{
			prv = cur->pPrv;
			next = cur->pNext;
			if (!prv)
				m_ppBucketTable[dwIndex] = next;
			else 
				prv->pNext = next;
				
			if (next)
				next->pPrv = prv;
				
			RemoveList(cur->pList);
			delete cur;
			cur = NULL;
			m_dwDataNum--;
			return;
		}
		cur = cur->pNext;
	}
}

void CHashTable::RemoveList(LIST* pList)
{
	
	LIST*	cur = pList;
	LIST*	prv = pList->pPrv;
	LIST*	next = pList->pNext;

	

	if (prv)
		prv->pNext = next;
	else 
		m_pListHead = next;

	if (next)
		next->pPrv = prv;
	else
		m_pListTail = prv;
	
	m_pListCur = m_pListHead;
	
	delete pList;
	pList = NULL;

}
void* CHashTable::GetData(DWORD dwKey)
{
	DWORD index = dwKey%m_dwMaxBucketNum;

	BUCKET* pBucket = m_ppBucketTable[index];

	while(pBucket)
	{
		if (pBucket->dwKey == dwKey)
		{
			return pBucket->pVoid;
		}
		pBucket = pBucket->pNext;
	}
	return NULL;

}
void* CHashTable::GetData()
{
	void*	pVoid;
	if (m_pListCur)
	{
		pVoid = m_pListCur->pBucket->pVoid;
		m_pListCur = m_pListCur->pNext;
		return pVoid;
	}
	else 
		return NULL;

	return pVoid;
}
void CHashTable::RemoveAll()
{
	LIST*	cur = m_pListHead;
	LIST*	next = NULL;

	while (cur)
	{
		next = cur->pNext;
		delete cur->pBucket;
		delete cur;
		cur = next;
	}
	m_dwDataNum = 0;
}

CHashTable::~CHashTable()
{
	RemoveAll();
	if (m_ppBucketTable)
	{
		delete m_ppBucketTable;
		m_ppBucketTable = NULL;
	}
}