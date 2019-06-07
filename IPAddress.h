#ifndef __IP_ADDRESS_H__
#define __IP_ADDRESS_H__

struct IPAddress {
	unsigned long ip;
	unsigned short port;

	IPAddress(const char* naddress = 0, const unsigned short nport = 0);

	void setIP(const char* value);

	const char* getIPStr() const;

	void setPort(const unsigned short value);

	unsigned short getPort() const;
};

#endif //__IP_ADDRESS_H__
