// PacketQ.cpp: implementation of the PacketQ class.
//
//////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
//#include "DRPointManger.h"
#include "PacketQ.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#include "../MyLog.h"

// 010309 KHS
int putpacketcount;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------
/*
 * The following functions are used for randomlize packets
 */
#define KEY 120751750

uint PacketQ::rotate(uint a,uint rn,int dir)
{
  uint b,sizeI;
  b=a;
  sizeI=8*sizeof(uint);
/*dir=-1 : left rotate,from lsb to msb*/
  if(dir==1) {
    a=a<<rn;
    b=b>>(sizeI-rn);
  }

/*others : right rotate,from msb to lsb*/
  else if(dir==0) {
    a=a>>rn;
    b=b<<(sizeI-rn);
  }
  return a=a|b;
}

void PacketQ::intToBuf(char *cp, int val)
{
    *cp++ = (char) (val & 0x000000ff);
    *cp++ = (char)((val & 0x0000ff00) >> 8);
    *cp++ = (char)((val & 0x00ff0000) >> 16);
    *cp++ = (char)((val & 0xff000000) >> 24);
}
//---------------------------------------------------------------------------

int PacketQ::bufToInt(unsigned char *cp)
{
    int val;

    val = *cp++;
    val += ((int) *cp++) << 8 ;
    val += ((int) *cp++) << 16;
    val += ((int) *cp++) << 24;
    return(val);
}

uint PacketQ::atrandom(uchar *src, uchar *resstr)
{
  uint sizeI,key,source;

  memcpy((void*)&source,src,sizeof(uint));
//  rn=time(NULL);
  sizeI=8*sizeof(uint);
  source=(~source&KEY)|(source&(~KEY));
  key=rotate(source,KEY%sizeI,1);
  memcpy(resstr,(void*)&key,sizeof(uint));
  resstr[sizeof(uint)]=0;
  return key;
}

uint PacketQ::derandom(uchar *src, uchar *resstr)
{
  uint a,sizeI,data,res;

  memcpy((void*)&data,src,sizeof(uint));
  sizeI=8*sizeof(uint);
  //printf("src=%s,key=%u,data=%u\n",src,key,data);
  a=rotate(data,KEY%sizeI,0);
  res =  (~a&(KEY))|(a&(~(KEY)));
  memcpy(resstr,(void*)&res,sizeof(uint));
  resstr[sizeof(uint)]=0;
  return res;
}
//---------------------------------------------------------------------------

PacketQ::PacketQ()
{
    query=NULL;
}

PacketQ::~PacketQ()
{
    clear();
}

void PacketQ::clear() {
    Query *tempque;

    tempque=query;
    while (tempque!=NULL){
      query=query->next;
      free (tempque);
      tempque=query;
    }
    query=tempque=NULL;
}

int PacketQ::put(char *buf, int len, bool encode)
{
  Query *newque,*tempque;
  unsigned char  code[MAX_PACKET_LEN+1];
  int i;

  //DebugPrintf("alloc queue!");
  newque = (Query *)malloc(sizeof(Query));
  if (newque==NULL)
    return 0;
  //DebugPrintf("en(de)code (%s)",buf);
  if (encode){
    int morespaces;

    memcpy(code,buf+1,len-1);
    morespaces=4-(len-1)%4; /* ¦©±¼'-'«ámode 4 */
    for (i=0;i<morespaces;i++)
        code[len+i]=0;

	memcpy(newque->msg,"-",1);

    intToBuf(newque->msg+1,len-1+morespaces);
    i=0;
    while(i<len-1+morespaces){
      atrandom(code+i,(unsigned char *)(newque->msg+5+i));
      i+=4;
    }
    newque->size=len+4+morespaces;
    /*i=0;
    while (i<len-5) {
       derandom(buf+5+i,code+i);
       i+=4;
    } */
  }else{//need decode
     i=0;
     while (i<len) {
       derandom((unsigned char *)(buf+i),code+i);
       i+=4;
     }
     newque->size=bufToInt(code);
     memcpy(newque->msg,code+4,newque->size);
   }
   //DebugPrintf("en(de)code ok");
  /*newque->msg=(char *)malloc(sizeof(len+1));
  if (newque->msg==NULL)
    return 0;*/

  //newque->msg=(AnsiString)buf+" ";
  newque->next=NULL;
  if (query==NULL)
    query=newque;
  else{
    tempque=query;
    while(tempque->next!=NULL)
      tempque=tempque->next;
    tempque->next=newque;
  }


	// 010309 KHS
//  MyLog( LOG_NORMAL, "put packet %d ", ++putpacketcount );

  return 1;
}

int PacketQ::get(char *buf, int *len)
{
  Query *getque;

  if (query==NULL)
    return 0;
  getque=query;
  query=query->next;
  memcpy(buf,getque->msg,getque->size+1);
  *len=getque->size;
  //free (getque->msg);
  free (getque);


	// 010309 KHS
//  MyLog( LOG_NORMAL, "get packet %d ", --putpacketcount );

  return 1;
}

bool PacketQ::notEmpty(void)
{
  return (query!=NULL);
}


//---------------------------------------------------------------------------