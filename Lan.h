#ifndef __LAN_GAME_H__
#define __LAN_GAME_H__

static const unsigned short UDPPort = 4444;
static const unsigned short TCPPort = 5555;

enum MessageTypes {
	SEARCHING_FOR_SERVER,
	CONNECT_TO_ME,

	MESSAGE_TYPE_COUNT
};

static const char* Message[MESSAGE_TYPE_COUNT] = {
	"SEARCHING_FOR_SERVER",
	"CONNECT_TO_ME"
};

static const uint32_t MessageLength[MESSAGE_TYPE_COUNT] = {
	21,
	14
};

#endif //__LAN_GAME_H__
