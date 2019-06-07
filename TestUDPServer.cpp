#include <stdio.h>
#include <string.h>
#include "Socket.h"
#include <stdlib.h>
 
static const unsigned int PortAddress = 4321;

int main(int argc, char *argv[]) {
	Socket server;
	Packet packet(1024);
	IPAddress address;

	bool running = true;

	if (server.initialize(Socket::UDP, NULL, PortAddress) == false) {
		return 1;
	}
	printf("UDP server initialized on %s::%d.\n", server.getIPStr(), server.getPort());
	while (running) {
		if (server.receive(packet, &address, false)) {
			printf("Received from %s::%d: \"%s\"[%d]\n", address.getIPStr(), address.getPort(), packet.c_str(), packet.getSize());

			if (strcmp((char*)packet.getData(), "server quit") == 0) {
				server.send(Packet("Server will shutdown.", 22), address);
				running = false;
			} else 
			if (strcmp((char*)packet.getData(), "server restart") == 0) {
				server.send(Packet("Server will restart.", 22), address);
				running = false;
				system("./TestUDPServer.out&");
			} else 
			if (strcmp((char*)packet.getData(), "server info") == 0) {
				char buffer[256];
				int length = sprintf(buffer, "\nUDP server\n\tIP: %s\n\tPort: %d\n", server.getIPStr(), server.getPort());
				packet.set(buffer, length + 1);
				server.send(packet, address);
			} else 
			{
				server.send(Packet("Got your message.", 17), address);
			}
		}
	}
	server.uninitialize();
	printf("UDP server uninitialized.\n");
	return 0;
 }
