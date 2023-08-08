


#define		CMD_SERVER_MAGIC_POSITION		20000
#define		CMD_SERVER_CHARACTER_CONDITION	20001

typedef	struct	server_magic_position
{
	short int	target_id;
	short int	x;
	short int	y;
}	t_server_magic_position;
//< CSD-010907
/*
typedef struct	server_character_condition
{
	short int	condition;
	short int	change_HP;
}	t_server_character_condition;
*/
struct t_server_character_condition
{
  WORD idTarget;
  __int32 nLife;
  BYTE nState;
};
//> CSD-010907
typedef union	angra_pub
{
	t_server_character_condition	server_character_condition;
	t_server_magic_position			server_magic_position;
}	t_angra;