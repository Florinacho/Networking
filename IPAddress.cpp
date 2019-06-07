#include "IPAddress.h"

#include <sys/socket.h>
#include <arpa/inet.h>

#ifndef INPORT_ANY
#define INPORT_ANY 0
#endif //INPORT_ANY

static char IPAddressStringTMP[INET6_ADDRSTRLEN];

IPAddress::IPAddress(const char* naddress, const unsigned short nport) 
	: ip(INADDR_ANY), port(INPORT_ANY) {
	setIP(naddress);
	setPort(nport);
}

void IPAddress::setIP(const char* value) {
	if (value == 0) {
		ip = INADDR_ANY;
		return;
	}

	if (inet_pton(AF_INET, value, &ip) == -1) {
		return;
	}
}

const char* IPAddress::getIPStr() const {
	static char IPAddressStringTMP[INET6_ADDRSTRLEN];
	return inet_ntop(AF_INET, &ip, IPAddressStringTMP, sizeof(sockaddr_in));
}

void IPAddress::setPort(const unsigned short value) {
	port = htons(value);
}

unsigned short IPAddress::getPort() const {
	return ntohs(port);
}
