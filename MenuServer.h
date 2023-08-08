extern void MakeStoreList( void );
extern void CallSmallMenu( int cn, int storelistindex, int menu );
extern void RecvItemBuy( int cn, t_client_item_buy *p );
extern void RecvItemSell( int cn, t_client_item_sell *p );

extern void SendRumor( t_connection c[],  int cn );