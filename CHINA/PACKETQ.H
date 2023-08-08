// PacketQ.h: interface for the PacketQ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKETQ_H__6BB76A61_B49B_11D4_966C_0050DAED441D__INCLUDED_)
#define AFX_PACKETQ_H__6BB76A61_B49B_11D4_966C_0050DAED441D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_PACKET_LEN          4096
#define MAX_NAME_LEN    25

//---------------------------------------------------------------------------
typedef struct Query Query;
struct Query{
  unsigned int size;
  char msg[MAX_PACKET_LEN];
  Query *next;
};

typedef  unsigned int    uint;
typedef  unsigned char   uchar;

//---------------------------------------------------------------------------
class PacketQ {
	private:
		//int qsize;
		//char **qptr;
        Query *query;
    //int *qlen;
	public:
		PacketQ();
		~PacketQ();
		int put(char *buf, int len, bool encode);
		int get(char *buf, int *len);
		void clear();
		bool notEmpty();
		uint rotate(uint a,uint rn,int dir);
		void intToBuf(char *cp, int val);
		int bufToInt(unsigned char *cp);
		uint atrandom(uchar *src, uchar *resstr);
		uint derandom(uchar *src, uchar *resstr);

};

#endif // !defined(AFX_PACKETQ_H__6BB76A61_B49B_11D4_966C_0050DAED441D__INCLUDED_)
