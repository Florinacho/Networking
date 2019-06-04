#include "Socket.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

int main() {
	Socket socket;
	Packet packet;
	std::string line;

	bool running = true;

	if (socket.connect("127.0.0.1", 4321) == false) {
		printf("Error! Cannot connect to 127.0.0.1::4321.\n");
		return 1;
	}

	while(running) {
		if (socket.isValid() == false) {
			printf("Server has disconnected.\n");
			running = false;
			continue;
		}

		printf("Message: ");
		std::getline(std::cin, line);

		if (line == "quit") {
			running = false;
			continue;
		} else if (line == "info") {
			printf("\nTCP client\n\t IP: %s\n\tPort: %d\n", socket.getIPStr(), socket.getPort());
		} else {
			packet.set(line.c_str(), line.size() + 1);
			socket.send(packet);
			if (socket.receive(packet, true)) {
				printf("Received from %s::%d: \"%s\"[%d]\n", socket.getIPStr(), socket.getPort(), packet.getData(), packet.getSize());
			}
		}
	}

	socket.uninitialize();

	return 0;
}
