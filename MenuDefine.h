
#define MAX_FIELD			50 //�ϳ��� �޴��� ���� �ִ� �ִ� �������
#define MAX_MENU			200 //�ִ� �޴� ����
#define MAX_STRING			500 //������Ұ� ������ ������ �ִ� ���ڿ� �ִ� ����
#define MAX_CHEAKARRAY		2 //�迭������� üũ�Ҷ� ����ϴ� �迭�� �ִ밹��
#define MAX_SHN				50  //FT_HIDE_NOMAL_  �� ����� ����ü �ִ� ����
#define MAX_SHN_FIELD		15  //FT_HIDE_NOMAL_  �� ����� ����ü�� ������ �ִ� �ִ� ��Ҽ�
#define MAX_CHARACTERDATA	12 //nCharacterData�� �� �ִ� ĳ���� �����ͼ�
#define MAX_MENUDATA		40  //�Ѻ��� �׸� �ִ� ����
#define MAX_FILENAME		100
// #define MAX_MAININTERFACE 100

#define FONTSIZE			6           //���� 1���� ���α���(����) strlen�Լ��� ����Ʈ�� ��� �ű⿡ 6�� ���Ѵ�
#define FONT_COLOR_DEFAULT		(141>>3)<<11 | (144>>3)<<6 | 132>>3		//	���� ���� (�ѱ�, ����)
#define FONT_COLOR_PLUS			(255>>3)<<11 | (61>>3)<<6 | 65>>3		//	�ɷ�ġ���� �÷��� �� ����	(���� ��)
#define FONT_COLOR_NAME			(255>>3)<<11 | (209>>3)<<6 | 86>>3		//	�̸� (�ݻ�����)
#define FONT_COLOR_SPECIAL		(101>>3)<<11 | (169>>3)<<6 | 18>>3		//	Ư���� ��� ( �������)
#define FONT_COLOR_NUMBER		(221>>3)<<11 | (230>>3)<<6 | 206>>3		//	���� ����

/////////////////////////////////////////////////////////////////////////////////
//�޴� ��ȣ ����


#define MN_MAINSTART_BACK				MAX_MENU-1
#define MN_MAKECHARACTER_BASIC             0     //�ɸ��� ����� �޴����� ���� �ٴڿ� �򸮴� �κ�
#define MN_MAINSTART_BASIC                 1     //���� ��ŸƮ �޴��� ���ۺκ�
#define MN_MAINSTART_START                 2     //���� ��ŸƮ �޴����� START��ư�� ������ ������ �޴�

#define MN_MAKECHARACTER_CHEAK1            3     //ĳ���� ����� �޴����� ����Ȯ��â 1��
#define MN_MAKECHARACTER_CHEAK3            4     //ĳ���� ����� �޴����� ����Ȯ��â 3��
#define MN_MAKECHARACTER_GENDER            5     //ĳ���� ����� �޴����� ���������޴�
#define MN_MAKECHARACTER_NAME              6     //ĳ���� ����� �޴����� �̸������޴�
#define MN_MAKECHARACTER_FACE              7     //ĳ���� ����� �޴����� �󱼼����޴�
#define MN_MAKECHARACTER_ARIGEMENT         8     //ĳ���� ����� �޴����� ��ġ�������޴�
#define MN_MAKECHARACTER_CLASS             9     //ĳ���� ����� �޴����� Ŭ���������޴�
#define MN_MAKECHARACTER_SPELL             10    //ĳ���� ����� �޴����� ���������޴�
#define MN_MAKECHARACTER_COLOR             11    //ĳ���� ����� �޴����� �������޴�
#define MN_MAKECHARACTER_TACTICS_MAN       12    //ĳ���� ����� �޴����� ���� ������������޴�
#define MN_MAKECHARACTER_TACTICS_WOMAN     13    //ĳ���� ����� �޴����� ���� ������������޴�
#define MN_MAKECHARACTER_JOB               14    //ĳ���� ����� �޴����� ���������޴�
#define MN_MAKECHARACTER_ABILITY           15    //ĳ���� ����� �޴����� �ɷ�ġ �����޴�

#define MN_MAININTERFACE                   16    //���� �������̽� �޴�
#define MN_STATUS						   17    //�������ͽ� �޴�
#define MN_ABILITY                         18    //�����Ƽ �޴�
#define MN_MAGIC_WIZARD1                   19    //���� �޴� �� ���ڵ� �޴�1(�޴��� ��ũ�� �Ǵ� ������ 3���� ������)
#define MN_MAGIC_WIZARD2                   20    //���� �޴� �� ���ڵ� �޴�2
#define MN_MAGIC_WIZARD3                   21    //���� �޴� �� ���ڵ� �޴�3
#define MN_MAGIC_PRIEST1				   22    //���� �޴� �� ������Ʈ �޴�1(�޴��� ��ũ�� �Ǵ� ������ 3���� ������)
#define MN_MAGIC_PRIEST2                   23    //���� �޴� �� ������Ʈ �޴�2
#define MN_MAGIC_PRIEST3                   24    //���� �޴� �� ������Ʈ �޴�3
#define MN_ITEM                            25    //������ �޴�
#define MN_ARIGEMENT                       26    //�������ͽ��� �����Ƽ �޴����� ������ �����ϸ� ������ �޴�
#define MN_DAIRY_DAIRY                     27    //dairy�� dairy
#define MN_DAIRY_DAIRY_WRITE               28    //dairy�� dairy�� write
#define MN_DAIRY_DAIRY_READ                29    //dairy�� dairy�� read
#define MN_DAIRY_CARD                      30    //dairy�� ���� �����
#define MN_DAIRY_CARD_DEVEL                31    //dairy�� ���� ����� �� �����
#define MN_DAIRY_CARD_READ                 32    //dairy�� ���� ����� �� read
#define MN_DAIRY_CARD_SEND                 33    //dairy�� ���� ����� �� send
#define MN_DAIRY_LETTER                    34    //dairy�� ���� ����
#define MN_DAIRY_LETTER_WRITE              35    //dairy�� ���� ������ ����
#define MN_DAIRY_LETTER_READLIST           36    //dairy�� ���� ������ �б�
#define MN_DAIRY_LETTER_READLIST_READ      37    //dairy�� ���� ������ �б�
#define MN_DAIRY_LETTER_CONVLIST           38    //dairy�� ���� ������ Ȯ�� 
#define MN_DAIRY_LETTER_CONVLIST_READ      39    //dairy�� ���� ������ Ȯ�� 

#define MN_TEMPLE_INTRODUCTION             40    //���� �޴��� INTRODUCTION�޴�
#define MN_TEMPLE_OPERATION				   41    //���� �޴��� OPERATION
#define MN_TEMPLE_TEMPLE1                  42    //���� �޴��� 5���� ����� �ִ�TEMPLE
#define MN_TEMPLE_TEMPLE2                  43    //���� �޴��� 2���� ����� �ִ�TEMPLE
#define MN_TEMPLE_DONE                     44    //���� �޴��� DONE

#define MN_GUILD_INTRODUCTION              45    //��� �޴��� INTRODUCTION�޴�
#define MN_GUILD_OPERATION				   46    //��� �޴��� OPERATION
#define MN_GUILD_GUILD1                    47    //��� �޴��� 5���� ����� �ִ�TEMPLE
#define MN_GUILD_GUILD2                    48    //��� �޴��� 2���� ����� �ִ�TEMPLE
#define MN_GUILD_DONE                      49    //��� �޴��� DONE

#define MN_FACE                            50    //���� �������̽� �޴����� �� ǥ�� ���� �޴� �ٿ��

#define MN_BANK_DEPOSIT					   51    //���� �޴����� ����
#define MN_BANK_DEFRAYAL                   52    //���� �޴����� ���
#define MN_BANK_CUSTODY                    53    //���� �޴����� ����
#define MN_BANK_MAIN	                   54    //���� �޴����� ã��
#define MN_BANK_LOAN                       55    //���� �޴����� ����
#define MN_BANK_REPAYMENT                  56    //���� �޴����� ��ȯ
#define MN_BANK_AUCTION                    57    //���� �޴����� ���

#define MN_RANK                            59    //��� ��ȸ���� ���� ��ũ �޴�

#define MN_PARTY						   60    //���� �������̽� �޴��� ��Ƽ�� �޴�

#define MN_SKILL_MAIN					61	 //��ų �޴��� MAIN, 4���� ����޴��� �ִ�.
#define MN_SKILL_CLASS					62		//��ų �޴��� Class �޴�
#define MN_SKILL_JOB					63		//��ų �޴��� Job ��ų �޴� 
#define MN_SKILL_GENERAL				64		//��ų �޴��� General �޴�
#define MN_SKILL_KNOWLEDGE				65		//��ų �޴��� Knowledge �޴�

#define MN_DUNGEON_ARTIFICIAL			66		//���� �޴��� ��Ƽ���� �޴�
#define MN_DUNGEON_BLAZE				67		//���� �޴��� ������ �޴�
#define MN_DUNGEON_FREEZE				68		//���� �޴��� ������ �޴�

#define MN_LOGO_START					70		//ȸ�� �ΰ�
#define MN_LODING						71		// ���� ȭ������ �Ѿ������ �ε� ȭ��
#define MN_LOGIN						72		// ���� ���� ���ΰ� �ε��� ���ΰ�...
#define MN_LOGON						73		// �ε��Ҷ�, �ߴ� �޴�, ���⼭ ���� �������� �� �� ����.

#define MN_SELECT						74		//���� ���
#define MN_LOCATION						75		//���� ��� ����

#define	MN_BANK_AUCTION_SALE			76		// ��� �޴��� �ȱ� �޴�

#define MN_CALL_FIELD					87		// ����(?) �޴�... �� ����� ���ļ� ����Ѵ�. ( bActive�� Ȯ���� ó��! )
#define MN_MESSAGEBOX_BIG				88		// ���������� ȣ���� �� �ִ� �޽��� �ڽ�
#define MN_MESSAGEBOX_SMALL				89		
#define MN_YESNO						90		//YES-NO MENU

														
#define MN_BLACKSMITH					100		// ���� ��� �޴�
#define MN_FARM							101
#define MN_RESTAURANT					102
#define MN_HERBSHOP						103
#define MN_SHAMBLES						104
#define MN_CANDLE						105
#define MN_SLOPSHOP						106
#define MN_ALCHEMY						107
#define MN_WOODWORKING					108
#define MN_BOWCRAFT						109
#define MN_SHIPYARD						110

#define MN_SKILLGUILD_BUY				111
#define MN_SKILLGUILD_SELL				112
#define MN_SKILLGUILD_SKILL				113
#define MN_SKILLGUILD_ITEM				114
#define MN_SKILLGUILD_REPAIR			115

#define MN_ITEM_EXPLAN					116

#define MN_TOWNHALL                     117    //TOWNHALL�������̽�
#define MN_TOWNHALL_PUBLICNOTICE        118    //TOWNHALL�޴����� PUBLICNOTICE�޴�
#define MN_TOWNHALL_BUILDING            119    //TOWNHALL�޴����� BUILDING�޴�
#define MN_TOWNHALL_COMMERCE1           120    //TOWNHALL�޴����� COMMERCE1�޴�
#define MN_TOWNHALL_COMMERCE2           121    //TOWNHALL�޴����� COMMERCE2�޴�
#define MN_TOWNHALL_COMMERCE3           122    //TOWNHALL�޴����� COMMERCE3�޴�       //����â
#define MN_TOWNHALL_HOUSEREPAIR         123    //TOWNHALL�޴����� HOUSE REPAIR�޴�
#define MN_TOWNHALL_GUILD               124    //TOWNHALL�޴����� Organize Guild�޴�
#define MN_TOWNHALL_FORUM               125    //TOWNHALL�޴����� FORUM�޴�
#define MN_TOWNHALL_EVENT               126    //TOWNHALL�޴����� EVENT�޴�
#define MN_TOWNHALL_RANK1               127    //TOWNHALL�޴����� RANK1�޴�
#define MN_TOWNHALL_RANK2               128    //TOWNHALL�޴����� RANK2�޴�
#define MN_TOWNHALL_NOTICE4             129    //TOWNHALL�޴����� NOTICE4�޴�
#define MN_TOWNHALL_NOTICE3             130    //TOWNHALL�޴����� NOTICE3�޴�
#define MN_TOWNHALL_NOTICE2             131    //TOWNHALL�޴����� NOTICE2�޴�
#define MN_TOWNHALL_NOTICE1             132    //TOWNHALL�޴����� NOTICE1�޴�
#define MN_TOWNHALL_COMMERCE4           133    //TOWNHALL�޴����� COMMERCE4�޴�   //����â
#define MN_TOWNHALL_CONSTRUCTION        134    //TOWNHALL�޴����� CONSTRUCTION�޴�

#define MN_MY_HOME						135		// ����â ����
#define	MN_MY_HOME_EXPLAN				136		// ������ ����Ʈ â
#define MN_HOUSE						137		// �ǹ��ý���
#define MN_MY_HOME_IN					138
#define MN_HOME_PERSON					139

#define	MN_CHATTING						140		// ä��â		

#define MN_GOD1                         141     //�����޴�1
#define MN_GOD2                         142     //�����޴�2
#define MN_GOD3                         143     //�����޴�3

#define MN_MAGICBOOK                    145     //����å
#define MN_FUNCTION                     146     //��� ������

#define MN_SYSTEM                       147     //�ý��� �޴�
#define MN_SYSTEM_OPTION                148     //�ý��� �޴����� �ɼǸ޴�
#define MN_SYSTEM_HELP                  149     //�ý��� �޴����� help�޴�
#define MN_SYSTEM_HELP_KEY              150     //�ý��� �޴����� ��������key
#define MN_SYSTEM_HELP_MESSAGE			151     //�ý��� �޴����� ����������ɾ�
#define MN_SYSTEM_HELP_MACRO            152     //�ý��� �޴����� �������� ��ũ��
#define MN_SYSTEM_LOGOUT                153

#define MN_DRINK_MAIN					154		// ����
#define MN_DRINK_RUMOR					155		//
#define MN_DRINK_BUY					156		//

#define MN_SHOP_MAIN					157		// ��ȭ��
#define MN_SHOP_BUY						158		//
#define MN_SHOP_SELL					159		//

#define MN_HEAL_MAIN					160		// ����
#define MN_HEAL_HEALING					161		// ġ��
#define MN_HEAL_PREVENTING				162		// ����
#define MN_HEAL_LEARN					163		// ��ų ���

#define MN_SKILL_LEARN					164		// ��ų ���

#define MN_INN_MAIN						165
#define MN_INN_REST						166
#define MN_INN_SLEEP					167

#define MN_SELECT_CHARACTER				168		// ĳ�� ����â

#define MN_TACTICS						169		// ��ƽ�� ��
#define	MN_LEVELUP						170		// ���� �㿡�� Ŭ�� ���� �� ���ΰ��� �����̴� ���� ���� ����

#define MN_MAKECHARACTER_AGE			171		// ĳ���� ����⿡�� ���� ����
#define MN_MAKECHARACTER_SPELL2			172		// wizard�� priest���� spell ������ ��...

#define	MN_INFO							173
#define MN_CREDIT						174

#define MN_OKCANCEL_MESSAGEBOX			175		// OK_CANCEL �޸� �޽��� â
#define MN_OK_MESSAGEBOX				176		// OK�� �޸� �޽��� â

#define MN_ITEM_MESSAGEBOX				177		// ������ ���� â

#define MN_OPEN_BOX						178		// �ڽ� ������ â
#define MN_DIVIDE_ITEM					179		// �������� ���� ������ â
#define MN_MAGIC_BOOK					180		// ���� å

#define MN_ITEM_MAKE					181		// ������ ������ �۾���
#define MN_ITEM_MAKE_SELECT				182		// ����� �ִ� ������ ���

#define MN_ITEM_MAKE_OK					183		// ������ ����⿡ �������� ��� 

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//FT_HIDE_NOMAL_�� ����� ����ü ��ȣ ����
#define HN_MAKECHARACTER_GENDER_RECT          0     //ĳ���� ����� �޴����� ���� ������ ������ ���� �簢�� 
#define HN_MAKECHARACTER_GENDER_TEXT          20    //ĳ���� ����� �޴����� ���� ������ ������ ���� ����

#define HN_MAKECHARACTER_FACE                 1     

#define HN_MAKECHARACTER_ARIGEMENT_TEXT       21    //ĳ���� ����� �޴����� ��ġ�� ������ ������ ����
#define HN_MAKECHARACTER_ARIGENENT_RECT       2     //ĳ���� ����� �޴����� ��ġ�� ������ ������ �簢��

#define HN_MAKECHARACTER_CLASS_TEXT           22    //ĳ���� ����� �޴����� Ŭ���� ������ ������ ����
#define HN_MAKECHARACTER_CLASS_RECT           3     //ĳ���� ����� �޴����� Ŭ���� ������ ������ �簡��

#define HN_MAKECHARACTER_SPELL_RECT           4     //ĳ���� ����� �޴����� SPELL ������ ������ �簢��
#define HN_MAKECHARACTER_SPELL_TEXT           23    //ĳ���� ����� �޴����� SPELL ������ ������ ����

#define HN_MAKECHARACTER_COLOR_SELECT           5	  //�Ӹ������ ��Ļ����� �����
//#define HN_MAKECHARACTER_COLOR_HAIR           5     //ĳ���� ����� �޴����� ���õ� �Ӹ� ������ �����
//#define HN_MAKECHARACTER_COLOR_SKIN           6     //ĳ���� ����� �޴����� ���õ� �Ǻ� ������ �����
//#define HN_MAKECHARACTER_COLOR_CLOTHES        7     //ĳ���� ����� �޴����� ���õ� �� ������ �����
//#define HN_MAKECHARACTER_COLOR_ORNAMENT       8     //ĳ���� ����� �޴����� ���õ� ��� ������ �����

#define HN_MAKECHARACTER_TACTICS_MAN_RECT     9    //ĳ���� ����� �޴����� ��ƽ�� ������ ������ ���� �簢��
#define HN_MAKECHARACTER_TACTICS_MAN_TEXT     24    //ĳ���� ����� �޴����� ��ƽ�� ������ ������ ���� ����

#define HN_MAKECHARACTER_TACTICS_WOMAN_RECT   10    //ĳ���� ����� �޴����� ��ƽ�� ������ ������ ���� �簢��
#define HN_MAKECHARACTER_TACTICS_WOMAN_TEXT   25    //ĳ���� ����� �޴����� ��ƽ�� ������ ������ ���� ����

#define HN_MAKECHARACTER_JOB_RECT             11    //ĳ���� ����� �޴����� ���� ������ ������ �簢��
#define HN_MAKECHARACTER_JOB_TEXT             26    //ĳ���� ����� �޴����� ���� ������ ������ ����

#define HN_MAKECHARACTER_ABILITY              12    //ĳ���� ����� �޴����� �ɷ�ġ ������ ������ �ɷ�ġ����

#define HN_TEMPLE_INTRODUTION_TEXT            13    //���� ����
#define HN_TEMPLE_OPERATION_TEXT              15    //
#define HN_TEMPLE_TEMPLE1_TEXT                17    //
#define HN_TEMPLE_TEMPLE2_TEXT                19    //

#define HN_GUILD_INTRODUTION_TEXT             27    //���� ����
#define HN_GUILD_OPERATION_TEXT               28    //
#define HN_GUILD_GUILD1_TEXT                  29    //
#define HN_GUILD_GUILD2_TEXT                  30    //
#define HN_INVENTORY                          31    //�κ��丮â�� ��ũ���� ���� �ʵ� ���� .nSHideNomalCount  .nSHideNomalPlus   .nSHideNomalStart���� ���� ����Ѵ�
#define HN_PARTY_SELECT						  32  // ���� �������̽�, ��Ƽ �޴����� ���� ��ư ����Ʈ

#define HN_SKILL_MAIN_TEXT					33		// ��ų �޴��� ���� ȭ�� ����

#define HN_TOWNHALL_TEXT                      34    //Ÿ��Ȧ �޴����� �޴� ����
#define HN_TOWNHALL_CONSTRUCTION_TEXT         35    //Ÿ��Ȧ �޴����� construction�޴����� ����

#define HN_SYSTEM_TEXT                        36    //�����������̽��� �ý��� �޴�����  ����
#define HN_SYSTEM_HELP_TEXT                   37    //�����������̽��� �ý����� �������� ����

#define HN_DRINK_MAIN_TEXT					38		// �����޴� �������� ���� ����
#define HN_SHOP_MAIN_TEXT					39		// ��ȭ��
#define HN_HEAL_MAIN_TEXT					40		// ����
#define HN_INN_MAIN_TEXT					41		// ����
#define HN_INN_REST_TEXT					42		//


/////////////////////////////////////////////////////////////////////////////////
//Ư���� �Ͼ�� �� ���� ���� ��� ���ÿ� ���� �޴��� �Ҽ�ȭ ��Ű�ų� � ������ üũ�� �޴��� ���ų�
#define SWD_ENTER_MAKECHARACTER            1      //���ν�ŸƮ���� ĳ���� ����� ���� ����
#define SWD_MAKECHARACTER_ENTERNAME        2      //�����޴����� �̸����� �޴��� ���� 
#define SWD_MAKECHARACTER_SPELLORCOLOR     4      //Ŭ���� �޴����� ���õ� Ŭ������ �Ǵ��� SPELL�̳� Į��� ����
#define SWD_MAKECHARACTER_TACTICS          6      //������ �Ǵ���  TACTICS����� �����ش�
#define SWD_MAKECHARACTER_ABILITY          7      //JOB���� ABILITY�޴��� ����

#define SWD_MAININTERFACE_STATUS           9      //���� �������̽����� �������ͽ� �޴� �ٿ��
#define SWD_MAININTERFACE_ABILITYTOSTATUS  10     //�����Ƽ �޴����� �������ͽ� �޴��� �ٿﶧ
#define SWD_MAININTERFACE_MAGIC            11     //���� �������̽����� ���� �޴� �ٿ��(������Ʈ�� ���ڵ� �޴���1�� ���)
#define SWD_MAININTERFACE_ITEM             12     //���� �������̽����� ������ �޴� �ٿ��
#define SWD_MAININTERFACE_ABILITY          13     //���� �������̽��� �������ͽ����� �����Ƽ �޴� �ٿ��    
#define SWD_MAININTERFACE_ARIGEMENT        14     //�������ͽ� �޴��� �����Ƽ �޴����� ��ġ�� �޴� �ٿ��
#define SWD_MAININTERFACE_PARTY			   23     //���� �������̽����� ��Ƽ�� �޴� ����

#define SWD_ARIGEMENT_STATUS               16     //�ƹ��ϵ� ���ϰ� �׳� �ڽŸ� �ݴ´�

#define SWD_MAININTERFACE_FACE             17     //���� �������̽� ���� �� ǥ�� ���� â �ٿ��
#define SWD_FACE_CHOOSE                    18     //ǥ�� ������ ������
#define SWD_FACE_AUTOCLOSE                 19     //��ǥ�� ���� �޴��� �ڵ����� ������� �Ѵ�

#define SWD_UNMOUSEFOCUS                   20     //���콺 ��Ŀ���� Ǯ�� ��� �޴��� ��밡���ϰ� �Ѵ�

#define SWD_LMENUCLOSE                     21     //���� �������̽����� ����ϴ� �޴��� ���ʿ� �ߴ� �޴��� �����̸鼭 ������ ���
#define SWD_RMENUCLOSE                     22     //���� �������̽����� ����ϴ� �޴��� �����ʿ� ��� �޴��� �����̸鼭 ������ ���

#define SWD_YESNO_YES						24		// When select "YES" at YES-NO MENU
#define SWD_YESNO_NO						25		// When select "NO" at YES-NO MENU

#define SWD_CALL_OTHER						26		// �ڱ�ʹ� ������� ���� �޴� ȣ�� �ϱ�
#define SWD_IDPASS							27		//���̵� �н����� ����Ʈ �ڽ� �����
#define SWD_TURN_BUTTON						28		//���� �������̽����� ������ ����ϴ� ��ư

#define SWD_IDEDITBOX						29				// ���̵� ���
#define SWD_PASSEDITBOX						30				// �н����� ���

#define SWD_MAKECHARACTER_GENDERBACK		31		// ���� ���� �޴����� ��ŸƮ �޴��� ���ư���

#define SWD_SMALLMENU_END					32		// �����޴� ������
#define SWD_BANK_OK							33
#define SWD_BANK_CANCEL						34		// ���� �޴����� ok, cancel ��ư
#define SWD_BANK_ITEM						35
#define SWD_BANK_ITEM_END					36

#define SWD_TWO_MENU_OPEN					37		// �ΰ��� �޴��� ���ÿ� ��ﶧ nWillDo�� nSHideNomalNumber�� ����Ѵ�. ����� ��� ��� �޴����� �ȱ� �޴��� �ٲܶ��� ���
#define SWD_SIMPLE_CLOSE					38		// ���� �������̽��� ������ �͸� ���ΰ� ��� �޴��� ���� ��.. (�ΰ� �̻� ����� ���� ��� ���)

#define SWD_SMALL_MENU						39
#define SWD_MENU_OPEN						15		// ���� �������̽����� �׳� ����

#define SWD_ITEM_SELLBUY_OK					40		// ��� �ȱ� �޴����� OK ��ư ������ ��

#define SWD_JOBSKILL_SCROLL_UP				41		//	��� �ȱ� �޴������� ��ũ�� ��ư
#define SWD_JOBSKILL_SCROLL_DOWN			42		//				"

#define SWD_ITEM_SELLBUY_CANCEL				43		// ��忡�� ��� �ȱ� �޴�
#define SWD_LOGON							44		// ��ŸƮ �޴����� �α׿� �Ҷ� ���̵� �н����� üũ
#define SWD_LOGON_OK						45		

#define SWD_TOWN_CONSTRUCTION				46

#define SWD_EDIT_BOX						47		// ���ο��� ����Ʈ �ڽ� ����
#define SWD_MY_HOME							48		// MN_MY_HOME���� ���ư���

#define SWD_INFO_FLAG_SET					49		// Ŭ���Ǹ� �������̽� ���� �÷��׸� ���� ���ٶ�

#define SWD_MAIN_TO_CHAT					50
#define SWD_CHAT_TO_MAIN					51

#define SWD_NORMAL_CHECK_PUT				52		// Ŭ���� �ٸ� �ʵ��� Ÿ���� �ٲ۴�.

#define	SWD_QUIT							53		// ���� ������

#define SWD_BUY								54
#define SWD_SELL							55

#define SWD_LEARN							56		// skill ����
#define SWD_CHARACTER_SELECT				57		// ĳ���� �����ϱ�
#define SWD_CHARACTER_DEL_ADD				58

#define SWD_STATUS_TACTICS					59		// �������ͽ����� ��ƽ����
#define SWD_TACTICS_STATUS					60		// ��ƽ������ �������ͽ���

#define	SWD_PARTY_BUTTON					61
#define	SWD_BACK_SKILL						62

#define SWD_SKILLGUILD_LEARN				63		// ��ų ����, ������ ����
#define	SWD_LEARNSKILL_OTHER				64		// 

#define	SWD_TOWNHALL_TITLE					65		// ���� �Խ��� �׸� ��� 
#define SWD_TOWNGALL_TITLE_READ				66		// �Խ��� �������� ���� ��� â���� ����

#define SWD_OKCANCEL_OK						67		
#define SWD_OKCANCEL_CANCEL					68

#define SWD_BBS_READ						69		// ���� ȸ������ ������ ����� ���� ���� ��
#define	SWD_SUBMENU_BACK					70		// �ڽĸ޴����� ��� �޴��� ���ƿ��� nTemp�� �̿�

#define	SWD_EVENT_JOIN						71		// �̺�Ʈ ��񿡼� �����ϱ� 

#define SWD_PARTY_RELEASE					72		// ��Ƽ�� ����

#define SWD_SELECT_HOUSEKIND				73		// ������ ����
#define SWD_BUY_HOUSE						74		// �� ����

#define	SWD_WILLDO							75		// ���� �޴��� ���� �� ������ �Ѵ�. 

#define SWD_MOVE_OPEN_CLOSE					76		// �����̸� �����ų� ������ �޴� ����. nWillDo�� ���

#define SWD_DIVIDE_OK						77		// ������ ������ â���� OK ��ư 
#define SWD_ITEM_MAKE						78		// ������ ����ũ ��ư�� ���� ���  
#define SWD_ITEM_MAKE_CANCEL				79		// ������ ����ũ ��ư�� ���� ���  

#define SWD_ITEM_MAKE_SELECT_OK				80		// �������� �� �Ŀ� �۾��� ���
#define SWD_ITEM_MAKE_AFTER					81		// ������ ������ �۾��� �ݱ�
/////////////////////////////////////////////////////////////////////////////////
//�޴� ������� Ÿ�Թ�ȣ ����
#define FT_NOMAL_PUT                1  //�̹����� ��� �������
#define FT_NOMAL_PUT_CENTER         2  //�̹����� �����鼭 ���� �޴� x�డ� ���
 
#define FT_TEXT_PUT                 3  //���ڸ� ���
#define FT_TEXT_PUT_CENTER          4  // �����޴� x�� ��� �κп� ���� ���ڿ��� ���

#define FT_HIDE_PUT	                5  //���콺 L��ư�� �������� �̹����� �ٲ㼭 �����ִ� �������
#define FT_HIDE_PUT_CENTER          6  //FT_HIDE_PUT �� ������ ���� �޴� x�డ� ������
#define FT_HIDE_PUT_AUTO            7  //���콺�� �����̸� ���� ��ư�� ������ �ʾƵ� ����üũ
#define FT_HIDE_PUT_CENTER_AUTO     8  //FT_HIDE_PUT_AUTO�� ������ x�� ����� ������

#define FT_HIDE_NOMAL_ONE_PUT       9  //�޴���������� �������� �̹����� ������ ������ ��������1������ �����ؼ� ������� �ϴ� �������
#define FT_HIDE_NOMAL_GROUP_PUT     10 //�޴���������� �������� �̹����� ������ ������ �������� �����ؼ� ������� �ϴ� �������

#define FT_HIDE_WILLDO_PUT          11 //���콺 L��ư���� ������ ���� �ٸ��޴��� ȣ���ϴ� ����
#define FT_HIDE_SPECIAL_WILLDO_PUT  12 //�ܼ��� �޴�ȣ�⸸ �ϴ°� �ƴ϶� �������� Ư���� ���� �Ұ��
#define FT_SPECIAL_WILLDO           13 //�̹����� ���� �ʰ� �۵��Ѵ�

#define FT_HIDE_ISCROLL_PUT         14 //FT_HIDE_NOMAL_ �� ����� ��ũ�� ��ư�� �������� FT_HIDE_NOMAL_�� ���� ������ ���� ����
#define FT_HIDE_DSCROLL_PUT         15 //FT_HIDE_NOMAL_ �� ����� ��ũ�� ��ư�� �������� FT_HIDE_NOMAL_�� ���� ������ ���� ����

#define FT_THROWDICE                16 //�ֻ����� �����ִ� Ÿ��

#define FT_DATA_PUT                 17 //�ѱۿ��� ���� ��� ��� ���� nImageName�� DP_ �� ������ �̿��Ѵ�

#define FT_FIRE                     18 //�Ҳ��� ����ִ� Ÿ��

#define FT_INVENTORY                19 //������ �޴����� �κ��丮 â�� ���õ� �ʵ� ���콺�̺�Ʈ�� üũ�� ������ �̵��� �Ѵ�
#define FT_NO_CHECK                 20  //�׷� �ʵ忡�� ����͵� ����� ���� ������ ���.
#define FT_ACCEL_INVENTORY          21  //���콺 �̺�Ʈ�� üũ�ϴ� ���� ������â 

#define FT_ARMOR_INVENTORY          22  // ���� ���� ȭ�鿡�� ���콺 �̺�Ʈ üũ

#define FT_WILLDO_PUT				23  // ���콺 Ŭ���� �׳� �ٸ� �޴� ȣ�� �Ҷ�

#define FT_DO						24	// �׳� ������ �Ҷ�,
#define FT_GAUGE					25	// ������ �ٿ� ������ ä�ﶧ(����� �ε� ȭ�鸸, �ʿ��ϸ� ���� ������ ���� �ʿ�)
#define FT_DO_DEFAULT				26	// FT_DO ���� ȭ���� ��ũ�� �Ǹ� �㶧 

#define FT_IDEDITBOX				27	//���̵� �Է� ������ �ڽ� ȣ��
#define FT_PASSEDITBOX				28	//�н����� �Է� ������ �ڽ� ȣ��
#define FT_NOMAL_PUT_TALK_BATTLE_PEACE	29		// TALK, PEACE, BATTEL ��ư ����� ����...

#define FT_LODING_LIGHT				30		//�ε��Ҷ�, ����...

#define FT_MAGIC_ITEM_PUT			31		// ���� ������ ���
#define FT_NOMAL_PUT_CENTER_1		32		// _1�� ���� ���� Ʈ���� ���
#define FT_MAGIC_QUICK_ITEM			33		// �� ���� ������ ���

#define FT_COLOR_GAUGE				34		// �ܸ� �� ����
#define FT_MENU_MOVE				35		// �޴��� �巡�׷� �ű涧

#define FT_HIDE_WILLDO_AUTO_PUT		36		//	���콺 �浹�� �׸��� �ٲ� �����ְ� Ŭ���Ҷ� �� �׸��� �ٲٸ鼭 �ٸ� �޴��� ���Ҷ�
#define FT_HIDE_SPECIAL_WILLDO_AUTO_PUT  37		// ���콺 �浹 �׸��� �����ְ� Ŭ���ϸ� �������� ���� �Ҷ�

#define FT_HIDE_ISCROLL_AUTO_PUT		38
#define FT_HIDE_DSCROLL_AUTO_PUT		39	
#define FT_BANK_INVENTORY				40

#define FT_HIDE_AUTO_PUT			42
#define FT_JOB_ITEM					43

#define FT_TOWN_CONSTRUCTION		44	// �������� üũ 
#define FT_HOME_EDITBOX				45	// ���� �ý��ۿ��� �޽��� â ���� ��ư ������
#define	FT_SWITCH_PUT				46	// ������ ���� �׸��� ���� ��
#define FT_SKILL_PUT				47	// ��ų ����
#define FT_SKILL_QUICK				48

#define FT_OPTION_GAUGE				49	// �ɼ� �޴����� ������ �� �����ֱ�
#define FT_SYSTEM_OPTION_SCROLL		50	// �ý��� �ɼ� �޴����� ��ũ�� �� �����̱�

#define FT_KNOWLEDGE_ICON_PUT		51
#define FT_INN						52	// �������� ����� Ÿ��

#define FT_LEVELUP_BUTTON			53	// ���� ȭ�鿡 �ߴ� ��ư
#define	FT_LEVELUP					54	// �����â�� �ߴ� + ��ư��

#define FT_NOMAL_PUT_FX				55	// �޽��� â �ڿ� �ߴ� ȭ�� ȿ��
#define	FT_BBS_GO					56	// ������ ������ �������� �ʵ�

#define FT_PARTY					57	// ��Ƽ�޴������� �ʵ� Ÿ��
#define FT_PARTY_FACE				58	// ����� ����

#define FT_OPENBOX_INV				59	// box_itemâ���� ���ù� ȭ�� ��� �ʵ�
#define FT_DIVIDE_ITEM_PUT			60	// �� ������ â���� ������ ���� ǥ��
#define FT_MAKE_ITEM				61	// ������ ����� â���� ������ ��¹� �۾�

#define FT_ITEM_MAKE_SELECT			62	// ����� �ִ� ������ ���
#define FT_MAIN_MENU				63	// ���� �޴����� �Ļ��Ǵ� �޴� ��ư��... // FT_HIDE_SPECIAL_WILLDO_AUTO_PUT �� ���� ���δ�.

#define FT_MAKE_ITEM_OK				64	// ��������� ������ ���� 

/////////////////////////////////////////////////////////////////////////////////
//��°��� ����  DP_�� FT_�� ��������� FT_�� �׻� �������� �����ִµ� ���� DP_�� ��ġ��� ���� ���÷� �ٲ�°� �����ٶ� ����
#define DP_GENDER                     1             //����
#define DP_NAME						  2             //�̸�
#define DP_ARIGEMENT				  3             //��ġ��
#define DP_CLASS					  4             //Ŭ����
#define DP_SPELL					  5             //����
#define DP_TACTICS					  6             //��ƽ����
#define DP_JOB						  7             //����
#define DP_STR						  8             //STR
#define DP_CON						  9             //
#define DP_DEX						  10		    //
#define DP_WIS						  11	        //
#define DP_INT						  12            //
#define DP_CHA						  13            //
#define DP_MOVP						  14            //
#define DP_ENDU						  15		    //
#define DP_MOR						  16            //
#define DP_WSPS						  17            //
#define DP_LUCK						  18            //  
#define DP_NAMEEDITBOX                19            //�̸��� ������ ĭ

#define DP_FACE                       20            //�� ǥ���� ���

#define DP_INVENTORY                  21            //������ �޴����� �����۸����� ���

#define DP_LEVEL                      22            //������ ���
#define DP_EXP                        23            //����ġ�� ���

#define DP_ARIGEMENT_BAR              24            //��ġ���� ������ �޴����� ��µǴ� ����׷���

#define DP_HP_BAR                     25            //���� �������̽� ���� HP���� �������� �����ش�
#define DP_MP_BAR                     26            //���� �������̽� ���� MP���� �������� �����ش�.

#define DP_HP                         27            //HP��ġ�� �����ش�
#define DP_MP                         28            //MP��ġ�� �����ش�.

#define DP_MAIN_LEVEL			      29			//���� �������̽����� �������� �����ش�.
#define DP_MAIN_STR				      30			//���� �������̽����� STR���� �����ش�.


#define DP_ACCEL_INVENTORY            31             //���� ������â���� ������ ������ �̹����� �����ش�

#define DP_ARMOR_INVENTORY            32             //���� ��� â�� ������ ������ �̹����� �����ش�

#define DP_CONDITION                  33            //���� �������̽����� ĳ���� ���¸� ��Ÿ���� ������ ���
#define DP_FACEIMAGE				34				// �� �̹��� ���

#define DP_GUILD					35
//#define DP_WSPS						36
#define DP_TACTICE					37
#define DP_DAMAGE					38
#define DP_HEALTH					39
#define DP_MOV						40
#define DP_HEAT						41
#define DP_AC						42
#define DP_FAME						43
#define DP_MONEY					44
#define DP_IDEDITBOX				45				// ���̵� ���
#define DP_PASSEDITBOX				46				// �н����� ���

#define DP_HEALTH_GAUGE				47
#define DP_LEVEL_LOGON              48            //�α׿� ȭ�鿡�� ������ ���

#define DP_TEMP_MONEY				49				// ���࿡�� �Է¹޴� â�� �ݾ� ���
#define DP_BANK_SAVE				50				//
#define DP_BANK_TOTAL				51				// ���࿡�� �ѿ��ݾ� ���
#define DP_BANK_INVENTORY			52

#define DP_WEIGHT					53				// ���� ���
#define DP_BANK_CURRENT_PAY			54				// ������ ������
#define DP_BANK_PAY					55

#define DP_CREDIT_TEXT				56				// �ſ� ��� ���
#define DP_LOAN_TOTAL				57				// ���⿡ �Ѿ�
#define DP_LOAN_ABLE				58				// ���� ���ɾ�
#define DP_DAY_TEXT					59				// ��ȯ ��¥ ǥ��

#define DP_REPAYMENT_MONEY			60				// ���� ���ƾ��� �ݾ�
#define DP_REPAYMENT_DATE			61				// ���� ��ȯ�ؾ��� ����

#define DP_GUILD_INVENTORY			62
#define DP_CHARACTER_MONEY			63				// ĳ���� ������ �ִ� �� ��� -> nWillDo�� ����� ĭ�� ����  x,y �� ��ǥ���� �־��ش�

#define DP_STRING_PUT				64				// ���ڿ� ���
#define DP_RECT_STRING_PUT          65				//�����޴�1������ MEssage���
#define DP_SKILL_ICON				66				// ��ų�޴����� ��ų ������ ���
#define	DP_HEALING_EXPLAIN			67				// HEALING ��� ����

#define DP_NAME_SELECT				68				// ĳ���� ����â���� ����� ������
//#define DP_JOB_SELECT				69
//#define DP_CLASS_SELECT				70
//#define DP_AGE_SELECT				71
//#define DP_LEVEL_SELECT				72
//#define DP_CELL_SELECT				73
//#define DP_FACE_SELECT				74

#define DP_TACTICS_DATA				75

#define DP_ABILITY					76				// �����Ƽ â���� ���
#define DP_DATAPUT					77				// ������ ����Ʈ		// nWilldo���� � �ɷ�ġ ����, nRectImage ���� ���̸� �ִ´�.
#define DP_RESIST					78				// �����Ƽ â���� resist���� ���
#define DP_EXP_NEXT					79

#define DP_AGE_MAKE					80				// ���� ����
#define DP_AGE						81				// ���� 

#define DP_TOWNGALL_TITLE			82				// �Խ��� ���� ���
#define DP_TOWNGALL_TITLE_DATE		83				// �Խ��� ��¥ 
#define DP_BBS_PUT					84				// �Խ��� ���� ��� 

#define	DP_HOUSE_PUT				85				// ���������ֱ�
#define DP_HOUSE_REPAIR				86				// �ǹ� �����޴� 

#define DP_ITEM_MESSAGE				87				// item ���� â
#define DP_SELECT_SELECT			88				// ������ ����� �޴����� ������ ������ ǥ��

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
// FT_DO�� ���� ����(1��, 3��, 26���� �����)
#define DO_CHARACTER				10				//ĳ���� ���� ���
#define DO_TEXT_PUT					11				//�޽��� �ڽ����� ���ڿ� ���
#define DO_BANK_SCROLL_UP			35				// ���� �� �ø��� ������ 
#define DO_BANK_SCROLL_DOWN			36
#define DO_BANK_TIME_SCROLL_UP		100				// ��� ��¥ �����ϱ�
#define DO_BANK_TIME_SCROLL_DOWN	101
#define DO_BANK_SCROLL_LEFT			102				// ��� ���� ã��
#define DO_BANK_SCROLL_RIGHT		103

#define DO_SKILL_ICON_SELECT		114				// ��ų �޴� ��ũ�� �� ��� �̹��� �ٲ��ֱ�
#define DO_SKILL_ICON				115				// �����ܰ� Ÿ��Ʋ �ٸ� �����ְ� ������ �����Ű��

#define DO_FACE_MENU				200				// ǥ�� ���� â
#define DO_SELECT_LOAD_CHAR			210				// �ε��� ĳ����������

#define DO_CHATTING_VIEW			300				// ä��â�� ��ȭ �����ֱ�
#define DO_CHATTING_EDITBOX			310				// ä��â�� �� ���� ������ �ڽ�

#define DO_LEARNSKILL_ICON			320				// ���� �ִ� ��ų �����ֱ�

#define DO_DEVIDE_SCROLL_UP			330				// �� ������ â���� ��ũ�� ��ư
#define DO_DEVIDE_SCROLL_DOWN		340


/////////////////////////////////////////////////////////////////////////////////////////////////
//�������� �ϴ� �޴� ���� ����
#define MM_STATUS_OPEN                1             //�����̴� �޴��� �������ͽ� �޴��� ����
#define MM_STATUS_CLOSE               2             //�����̴� �޴��� �������ͽ� �޴��� �����
#define MM_ABILITY_CLOSE              3             //�����̴� �޴��� �����Ƽ �޴��� �����
#define MM_ARIGEMENT_CLOSE            4             //�����̴� �޴��� ��ġ�� �޴��� �����
#define MM_MAGIC_WIZARD1_OPEN         5             //���� ����
#define MM_MAGIC_WIZARD1_CLOSE        6             //���� ����
#define MM_MAGIC_WIZARD2_CLOSE        7             //���� ����
#define MM_MAGIC_WIZARD3_CLOSE        8             //���� ����
#define MM_MAGIC_PRIEST1_OPEN         9             //    "
#define MM_MAGIC_PRIEST1_CLOSE        10            //    "
#define MM_MAGIC_PRIEST2_CLOSE        11            //    "
#define MM_MAGIC_PRIEST3_CLOSE        12            //    "
#define MM_ITEM_OPEN                  13            //    "
#define MM_ITEM_CLOSE                 14            //    "
#define MM_PARTY_OPEN				  15			//�����̴� �޴��� ��Ƽ�޴� ����
#define MM_PARTY_CLOSE				  16			//�����̴� �޴��� ��Ƽ�޴� �����

#define MM_TACTICS_CLOSE			  17			//�����̴� �޴��� ��Ƽ�޴� �����
#define MM_BOX_OPEN					  18			// �ڽ� �������� ������ ���
#define MM_BOX_CLOSE				  19			// �ڽ� �������� ������ ���



