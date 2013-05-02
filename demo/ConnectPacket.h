#ifndef CONNECTPACKET_H_
#define CONNECTPACKET_H_

#pragma pack(push, 2)
	struct ConnectPacket
	{
		U16 header;
		U8 usrname_size;
		U8 passwd_size;
		char username[32];
		char password[32];
	};
#pragma pack(pop)

#endif