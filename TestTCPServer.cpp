#include "Socket.h"

#include <stdio.h>
#include <string.h>

int main() {
	Socket socket;
	Socket connection;
	std::vector<Socket> connectionList;
	Packet packet;
	bool running = true;

	if (socket.listen("127.0.0.1", 4321) == false) {
		printf("Failed to listen\n");
		return 2;
	}

	while (running) {
		// Accept new connections
		if ((connectionList.size() < 2) && socket.accept(&connection, false)) {
			connectionList.push_back(connection);
			printf("Got new connection %s::%d. Connection count = %lu.\n", connection.getIPStr(), connection.getPort(), connectionList.size());
		}

		// Receiving messages
		for (unsigned int index = 0; index < connectionList.size(); ++index) {
			if (connectionList[index].receive(packet, false)) {
				printf("Received from %s::%d: \"%s\"[%d]\n", connectionList[index].getIPStr(), connectionList[index].getPort(), packet.getData(), packet.getSize());

				if (strcmp((const char*)packet.getData(), "server quit") == 0) {
					packet.set("Server will shutdown.", 22);
					running = false;
				} else 
				if (strcmp((const char*)packet.getData(), "server info") == 0) {
					char buffer[256];
					int length = sprintf(buffer, "\nTCP server\n\tIP: %s\n\t Port: %d\n", socket.getIPStr(), socket.getPort());
					packet.set(buffer, length + 1);
				} else 
				{
					packet.set("Got your message.", 18);
				}
				connectionList[index].send(packet);
			}
		}

		// Remove dead connections
		for (unsigned int index = 0; index < connectionList.size(); ++index) {
			if (connectionList[index].isValid() == false) {
				printf("Connection %d lost.\n", index);
				connectionList[index].uninitialize();
				connectionList.erase(connectionList.begin() + index);
			}
		}
	}

	socket.uninitialize();
	for (unsigned int index = 0; index < connectionList.size(); ++index) {
		connectionList[index].uninitialize();
	}

	return 0;
}
