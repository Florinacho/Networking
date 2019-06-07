#include "Timer.h"
#include "Socket.h"
#include "Lan.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>

enum State {
	INITIALIZE,
	SEARCH,
	CONNECT,
	APPLICATION
};

int main() {
	Socket socket;
	IPAddress address;
	Packet packet;

	bool running = true;
	int state = INITIALIZE;
	unsigned long long lastMessageTime = 0;

	while (running) {
		usleep(1000 / 30);
		const unsigned long long currentTime = Timer::GetMilliSeconds();

		switch (state) {
		case INITIALIZE :
			printf("Initializing UDP socket ... ");
			if (socket.initialize(Socket::UDP, NULL, 0)) {
				printf("SUCCESS!\n");
				socket.setBroadcast(true);
				state = SEARCH;
			} else {
				printf("FAILED!\n");
				return 1;
			}
			break;

		case SEARCH :
			if (currentTime - lastMessageTime > 1000) {
				printf("Send UDP message to %s::%d: \"%s\"[%d] ... ",
					"255.255.255.255",
					UDPPort,
					Message[SEARCHING_FOR_SERVER], 
					MessageLength[SEARCHING_FOR_SERVER]);
				if (socket.sendBroadcast(Packet(Message[SEARCHING_FOR_SERVER], (uint32_t)MessageLength[SEARCHING_FOR_SERVER]), UDPPort)) {
					printf("SUCCESS!\n");
				} else {
					printf("FAILED!\n");
				}
				lastMessageTime = currentTime;
			}
			if (socket.receive(packet, &address, false)) {
				printf("Received UDP message from %s::%d: \"%s\"[%d]\n", 
					address.getIPStr(), 
					address.getPort(),
					packet.c_str(), 
					packet.getSize());

				if (strcmp(packet.c_str(), Message[CONNECT_TO_ME]) == 0) {
					printf("Found server %s::%d.\n", 
						address.getIPStr(),
						address.getPort());
					state = CONNECT;
					continue;
				}
			}
			break;

		case CONNECT :
			printf("Connecting to TCP server %s::%d ... ", address.getIPStr(), TCPPort);
			if (socket.connect(address.getIPStr(), TCPPort)) {
				printf("SUCCESS!\n");
				socket.setBroadcast(false);
				state = APPLICATION;
			} else {
				printf("FAIL!\n");
				socket.uninitialize();
				state = INITIALIZE;
				printf("\n\n\n");
			}
			break;

		case APPLICATION :
			if (socket.receive(packet, false)) {
				printf("Received TCP message from %s::%d: \"%s\"[%d].\n", 
					socket.getIPStr(),
					socket.getPort(),
					packet.c_str(),
					packet.getSize());
			}

			if (socket.isValid() == false) {
				printf("Disconnected from the server %s::%d.\n", socket.getIPStr(), socket.getPort());
				printf("\n\n\n");
				socket.uninitialize();
				state = INITIALIZE;
			}
			break;
		}
	}

	socket.uninitialize();

	return 0;
}
