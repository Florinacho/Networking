#include "Socket.h"
#include "Lan.h"
#include "Timer.h"

#include <string.h>
#include <stdio.h>

int main() {
	Socket socketUDP;
	Socket socketTCP;
	Socket newClient;
	std::vector<Socket> clients;
	IPAddress address;
	Packet packet;
	bool running = true;
	unsigned long long lastMessageTime = 0;

	printf("Initializing UDP socket for port %hu ... ", UDPPort);
	if (socketUDP.initialize(Socket::UDP, NULL, UDPPort)) {
		printf("SUCCESS!\n");
	} else {
		printf("FAILED!\n");
		return 1;
	}

	printf("Start listening for UDP messages on %s::%hu ... ", socketUDP.getIPStr(), socketUDP.getPort());
	if (socketTCP.listen(NULL, TCPPort)) {
		printf("SUCCES!\n");
	} else {
		printf("FAILED!\n");
		return 2;
	}

	printf("Started listening for TCP messages on %s::%hu.\n", socketTCP.getIPStr(), socketTCP.getPort());
	while (running) {
		const unsigned long long currentTime = Timer::GetMilliSeconds();

		if (socketUDP.receive(packet, &address, false)) {
			printf("Received UDP message \"%s\"[%d].\n", 
				packet.c_str(), 
				packet.getSize());

			if (strcmp(packet.c_str(), Message[SEARCHING_FOR_SERVER]) == 0) {
				printf("Send TCP server informations ... ");
				if (socketUDP.send(Packet(Message[CONNECT_TO_ME], (uint32_t)MessageLength[CONNECT_TO_ME]), address)) {
					printf("SUCCESS!\n");
				} else {
					printf("FAILED!\n");
				}
			}
		}

		if (socketTCP.accept(&newClient, false)) {
			printf("Client %d with address %s::%hu has connected.\n", 
				(int)clients.size(), 
				newClient.getIPStr(), 
				newClient.getPort());
			newClient.send(Packet("Hello new user.", (uint32_t)16));
			clients.push_back(newClient);
		}

		for (unsigned int index = 0; index < clients.size(); ++index) {
			if (clients[index].receive(packet, false)) {
				printf("Received from %s::%hu: \"%s\"[%d]\n", clients[index].getIPStr(), clients[index].getPort(), packet.c_str(), packet.getSize());
			}
		}

		for (unsigned int index = 0; index < clients.size(); ++index) {
			if (clients[index].isValid() == false) {
				printf("Client %d with address %s::%hu has disconnected.\n", 
					index, 
					clients[index].getIPStr(), 
					clients[index].getPort());
				clients[index].uninitialize();
				clients.erase(clients.begin() + index);
			}
		}

		if (currentTime - lastMessageTime >= 1000) {
			for (unsigned int index = 0; index < clients.size(); ++index) {
				clients[index].send(Packet("You are connected.", (uint32_t)19));
			}
			lastMessageTime = currentTime;
		}
	}

	for (unsigned int index = 0; index < clients.size(); ++index) {
		clients[index].uninitialize();
	}
	socketTCP.uninitialize();
	socketUDP.uninitialize();

	return 0;
}
