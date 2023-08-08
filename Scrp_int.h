#ifndef __SCRIPT_INT_H__
#define __SCRIPT_INT_H__

const int SCRIPT_OLD = 0;
const int SCRIPT_NEW = 1;

enum 
{
    goto_     =  0xe0,
    if_       =  0xe1,
    call_     =  0xe2,
    add_      =  0xe3,
    sub_      =  0xe4,
    mul_      =  0xe5,
    div_      =  0xe6,
    rest_     =  0xe7,
    equal_    =  0xe8,
    end_      =  0xe9,
    ifequal_  =  0xea,
    or_       =  0xeb,
    and_      =  0xec,
    variable_ =  0xed,
    value_    =  0xee,
    add2_     =  0xef,
    sub2_     =  0xf0,
    mul2_     =  0xf1,
    div2_     =  0xf2,
    rest2_    =  0xf3,
    or2_      =  0xf4,
    and2_     =  0xf5,
};


#ifndef __SCRIPT_C__

    
	extern int  NScriptNo;    //SCRIPT_NO;
    extern int  CLoadScript;  //LOAD_SCRIPT;
    
	extern int  TotalFunction;

#endif

void Incode( char *s );

/* ������������������������������������
 �Լ��� : GetByte
 ��  �� : ����
 ���ϰ� : 1����Ʈ�� ��
 ��  �� : prog�� ��ϵ� ���뿡�� 1����Ʈ�� �����ϰ� prog�����͸� 1����
������������������������������������ */
BYTE GetByte( void );


/* ������������������������������������
 �Լ��� : GetInt
 ��  �� : ����
 ���ϰ� : 4����Ʈ�� ��
 ��  �� : prog�� ��ϵ� ���뿡�� 4����Ʈ�� �����ϰ� prog�����͸� 4����
������������������������������������ */
int GetInt( void );


/* ������������������������������������
 �Լ��� : GetString
 ��  �� :
 ���ϰ� : ���ڿ��� �����ϰ� �ִ� �迭�� ���� ������
 ��  �� : ��ũ��Ʈ ����Ÿ���� ���ڿ��� �о���δ�.
������������������������������������ */
void GetString( char *buf );


/* ������������������������������������
 �Լ��� : Script
 ��  �� : ����
 ���ϰ� : ����
 ��  �� : ��ũ��Ʈ �� �����
������������������������������������ */
void Script( int num );


/* ������������������������������������
 �Լ��� : LoadScript
 ��  �� : name - �о���̰��� �ϴ� ��ũ��Ʈ ����Ÿ ȭ�ϸ��� �ƴ϶� �Ϸù�ȣ.
 ���ϰ� :
 ��  �� : ���������� �о���̸� 1�� �����Ѵ�.
������������������������������������ */
int LoadScript( char *scriptname );
int LoadScriptText( char *scrname );




#endif


