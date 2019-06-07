#include <string.h>
#include <stdio.h>
#include <iostream>

#include "Socket.h"

static const unsigned int PortAddress = 4321;

int main(int argc, char *argv[]) {
	Socket client;
	IPAddress address;
	Packet packet;
	std::string line;
	bool running = true;

	if (client.initialize(Socket::UDP) == false) {
		return 1;
	}

	client.setBroadcast(true);

	while (running) {
		while (client.receive(packet, &address, false)) {
			printf("Received from %s::%d: \"%s\"[%d]\n", address.getIPStr(), address.getPort(), packet.c_str(), packet.getSize());
		}

		printf("Message: ");
		std::getline(std::cin, line);

		if (line == "quit") {
			running = false;
			continue;
		} else if (line == "info") {
			printf("\nUDP client\n\tIP: %s\n\tPORT: %d\n\n", client.getIPStr(), client.getPort());
		} else {
			client.sendBroadcast(Packet(line.c_str(), line.size() + 1), PortAddress);
		}
	}

	client.uninitialize();

	return 0;
}
