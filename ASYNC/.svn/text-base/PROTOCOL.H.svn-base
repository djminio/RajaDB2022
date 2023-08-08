#ifndef PROTOCOL_H
#define PROTOCOL_H
/*
enum	PTCL {
	PTCL_USER_LOGIN_NAME_PASSWORD	=	2,
	PTCL_SERVER_UP					=	15,		// 한 서버가 재기동하면 다른 모든 서버로 접속한 후에 각각의 서버에 보낸다      
	PTCL_CHAT_BROADCAST				=	101,	// 유져 전체에게 보내는 메시지
	PTCL_TEST						=	255
};
*/
// 프로토콜 작성규칙
// 접두어 CTS : 클라이언트가 서버에 보내는 메세지 
// 접두어 STC : 서버가 클라이언트에게 
// 접두어 STS : 서버가 서버에게 
// 예를 들어 로긴서버가 게임서버로부터 STC로 시작하는 메세지를 받으면 플레이어소켓넘버를 참조해 바로 넘긴다.
// 10~230번까지 사용하고 230번 이후는 두바이트메세지로 확장하기 위해 남겨둔다. 

//0~20 로그인 관련 정보, 유저 관련 입출입 정보
#define MSG_USER_LOGIN_NAME_PASSWORD	0			// name & id

#define MSG_LOGIN_OK					2			// 로그인 성공
#define MSG_LOGIN_FAIL					3			// 로그인 실패 ( 지금은  DB가 없으니까 쓴다. 나중에 삭제).
#define MSG_WRONG_ID					4			// 잘못된 아이디
#define MSG_WRONG_PASSWORD				5			// 잘못된 패스워드
#define MSG_WHO_KNOWS					6			// 이유를 모르지만 로그인 실패

#define MSG_SOMEONE_ROOM_IN				7			//누군가 방에 들어왔을때.
#define MSG_SOMEONE_ROOM_OUT			8
#define MSG_NOW_ROOM_SYSOP_NUM			9			//send this protocol when sysop is out or changed

#define MSG_NOW_MONEY					14
#define MSG_NOW_ROOM_INFO				15

#define MSG_ARE_YOU_ALIVE				18			// Asking Message for User of mui is alive
#define MSG_I_AM_ALIVE					19			// Answering Message for I AM ALIVE


//메시지 관련 정보, 서버공지 사항 관련. 에러코드 공지 관련
#define MSG_CHAT_MEMO					20			// 특정 아이디로 보내는 쪽지 숫자 아이디
#define MSG_CHAT_BROADCAST				21			// 유저 전체에게 보내는 메시지

#define STC_ANNOUNCEMENT				26			//서버에서 공지하는 내용.
#define STC_ANNOUNCEMENT_TO_ONE			27			//서버에서 한사람에게만 보내는 내용
#define STC_ANNOUNCEMENT_TO_ROOM		28			//서버에서 정해진 방에만 보내는 내용
#define MSG_ERROR_CODE					29			// error is occured





//from sebary start1
// 대기실서버 영역
//
#define LTS_MESSAGE						125
#define MSG_WAIT_ROOM					125			// 대기실에서온 메시지 임
#define LTS_CONNECT_GAME_SERVER			31			// 대기실에서 게임서버로 접속요청
	#define LRV_OK						1			// 접속 성공
	#define LRV_FAIL					4			// 실패
	#define LRV_ALREADY					5

#define LTS_GAME_START					32			// 게임 시작을 하자고 하는 대기실의 말씀 :)
	#define LRV_GO						1			// 방 만들기 성공하면 반송할 GO ! 값
	#define LRV_WAIT					2			// 기다리라고? 음. 왜 만들었는지 모르겠다. 어쨌던. 그냥...
	#define LRV_CANT					3			// 방을 만들수 엄쓸뜨애~~ :)

#define LTS_GAME_END					33

//from sebary end



#endif         