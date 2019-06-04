#include <stdio.h>
#include <string.h>
#include "Socket.h"
 
static const unsigned int PortAddress = 4321;

int main(int argc, char *argv[]) {
	Socket server;
	Packet packet(1024);
	sockaddr_in from;

	bool running = true;

	if (server.initialize(Socket::UDP, NULL, PortAddress) == false) {
		return 1;
	}

	while (running) {
		if (server.receive(packet, &from, false)) {
			printf("Received from %s::%d: \"%s\"[%d]\n", inet_ntoa(from.sin_addr), from.sin_port, (char*)packet.getData(), packet.getSize());

			if (strcmp((char*)packet.getData(), "server quit") == 0) {
				server.send(Packet("Server will shutdown.", 22), from);
				running = false;
			} else 
			if (strcmp((char*)packet.getData(), "server info") == 0) {
				char buffer[256];
				int length = sprintf(buffer, "\nUDP server\n\tIP: %s\n\tPort: %d\n", server.getIPStr(), server.getPort());
				packet.set(buffer, length + 1);
				server.send(packet, from);
			} else 
			{
				packet.set("Got your message", 17);
				server.send(packet, from);
			}
		}
	}
 }
