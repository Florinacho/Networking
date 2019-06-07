#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <arpa/inet.h>

#include "Packet.h"
#include "IPAddress.h"

#define closesocket close

class Socket {
	int fd;
	int type;
	sockaddr_in address;
	bool broadcastOption;

	int send(void* data, int length);

	int receive(void* data, int* length, bool blocking = true);

public:
	enum Type {
		UDP,
		TCP
	};

	Socket();

	~Socket();

	// Create the socket file descriptor and set the REUSE* option
	bool initialize(const Type& type);

	// Create the socket file descriptor, set the REUSE* option and bind to
	// the ip and port
	bool initialize(const Type& type, const char* ip, int port);

	// Destroy the  file descriptor
	void uninitialize();

	void setBroadcast(bool value);

	bool getBroadcast() const;

	// Verify if the connection is active. Updated after send, receive
	bool isValid() const;

	// Listen for new connections
	bool listen(const char* ip, int port);

	// Accept a new connection
	bool accept(Socket* socket, bool blocking = true);

	// Connect to a server using ip and port
	bool connect(const char* ip, int port);

	// Send a UDP packet 
//	bool send(const Packet& packet, const sockaddr_in& newaddress);
	bool send(const Packet& packet, const IPAddress& newaddress);

	// Receive UDP packet and store the sender's address in newaddress
//	bool receive(Packet& packet, sockaddr_in* newaddress, bool blocking = true);
	bool receive(Packet& packet, IPAddress* newaddress, bool blocking = true);

	// Broadcast a packet 
	bool sendBroadcast(const Packet& packet, int port);

	// Send a TCP packet
	bool send(const Packet& packet);

	// Receive a TCP packet
	bool receive(Packet& packet, bool blocking);

	// Returns the ip address as an string
	const char* getIPStr() const;

	// Returns the port address
	int getPort() const;
};

#endif //__SOCKET_H__
