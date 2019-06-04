#include <string.h>
#include <stdio.h>
#include <iostream>

#include "Socket.h"

static const unsigned int PortAddress = 4321;

int main(int argc, char *argv[]) {
	Socket client;
	sockaddr_in address;
	Packet packet;
	std::string line;
	bool running = true;

	if (client.initialize(Socket::UDP) == false) {
		return 1;
	}

	while (running) {
		printf("Message: ");
		std::getline(std::cin, line);

		if (line == "quit") {
			running = false;
			continue;
		} else if (line == "info") {
			printf("\nUDP client\n\tIP: %s\n\tPORT: %d\n\n", client.getIPStr(), client.getPort());
		} else {
			client.broadcast(Packet(line.c_str(), line.size() + 1), PortAddress);

			if (client.receive(packet, &address, true)) {
				printf("Received from %s::%d: \"%s\"[%d]\n", inet_ntoa(address.sin_addr), address.sin_port, (char*)packet.getData(), packet.getSize());
			}
		}
	}

	return 0;
}
