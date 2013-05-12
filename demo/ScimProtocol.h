#ifndef CONNECTPACKET_H_
#define CONNECTPACKET_H_

#pragma pack(push, 2)
	struct Connect
	{
		U16 header;
		U8 usrname_size;
		U8 passwd_size;
		char username[32];
		char password[32];
	};
	struct RequestPortal
	{
		U16 header;
		U32 id;
	};
#pragma pack(pop)

#endif