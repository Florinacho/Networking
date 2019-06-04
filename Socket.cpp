#include "Socket.h"

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/socket.h>

Socket::Socket()
	: fd(-1), type(-1) {
	memset(&address, 0, sizeof(address));
}

Socket::~Socket() {
}

bool Socket::initialize(const Type& ntype) {
	if (fd != -1) {
		close(fd);
		fd = -1;
	}

	switch (ntype) {
	case Socket::UDP :
		fd = socket(AF_INET, SOCK_DGRAM, 0);
		break;
	case Socket::TCP :
		fd = socket(AF_INET, SOCK_STREAM, 0);
		break;
	default :
		return false;
	}

	if (fd == -1) {
		return false;
	}

	type = ntype;

	int option = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option)) != 0) {
		return false;
	}

	return true;
}

bool Socket::initialize(const Type& ntype, const char* ip, int port) {
	if (initialize(ntype) == false) {
		return false;
	}

	unsigned int addressLength = sizeof(address);
	memset(&address, 0, addressLength);
	address.sin_family = AF_INET;
	if (ip) {
		if (inet_pton(AF_INET, ip, &address.sin_addr) != 1) {
			uninitialize();
			return false;
		}
	} else {
		address.sin_addr.s_addr = INADDR_ANY;
	}
	address.sin_port = htons(port);
 
	if (bind(fd, (sockaddr*)&address, addressLength) < 0) {
		close(fd);
		fd = -1;
		return false;
	}
	
	return true;
}

void Socket::uninitialize() {
	if (fd != -1) {
		close(fd);
		fd = -1;
	}
	type = -1;

	memset(&address, 0, sizeof(address));
}

bool Socket::isValid() const {
	return (fd != -1);
}

bool Socket::listen(const char* ip, int port) {
	if (initialize(Socket::TCP, ip, port) == false) {
		return false;
	}

	static const int Backlog = 8;

	return (::listen(fd, Backlog) != -1);
}

bool Socket::accept(Socket* socket, bool blocking) {
	if (isValid() == false) {
		return false;
	}

	if (type != Socket::TCP) {
		return false;
	}

	unsigned int addressLength = sizeof(sockaddr_in);

	if (blocking == false) {
		fd_set set;
		FD_ZERO(&set);
		FD_SET(fd, &set);

		timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 0;

		int status = select(fd + 1, &set, NULL, NULL, &tv);
		if (status == -1) {
			return false;
		} else if (status == 0) {
			return false;
		} 
	}
	socket->fd = ::accept(fd, (sockaddr*)&socket->address, &addressLength);
	socket->type = Socket::TCP;

	return ((socket->fd != -1) && (addressLength > 0));
}

bool Socket::connect(const char* ip, int port) {
	if (initialize(Socket::TCP) == false) {
		return false;
	}

	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	if (inet_pton(AF_INET, ip, &address.sin_addr) == -1) {
		return false;
	}

	if (::connect(fd, (sockaddr*)&address, sizeof(sockaddr)) == -1) {
		return false;
	}

	return true;
}

bool Socket::send(const Packet& packet, const sockaddr_in& newaddress) {
	if (isValid() == false) {
		return false;
	}

	if (type != Socket::UDP) {
		return false;
	}

	if ((::sendto(fd, packet.getData(), packet.getSize(), 0, (sockaddr *)&newaddress, sizeof(sockaddr_in))) < 0) {
		close(fd);
		fd = -1;
		return false;
	}
	return true;
}

bool Socket::receive(Packet& packet, sockaddr_in* newaddress, bool blocking) {
	const unsigned int bufferLength = 1024;
	char* buffer[bufferLength];
	socklen_t inAddressLength = sizeof(sockaddr_in);
	int receivedLength = 0;

	if (isValid() == false) {
		return false;
	}

	if (type != Socket::UDP) {
		return false;
	}

	if (blocking == false) {
		fd_set set;
		FD_ZERO(&set);
		FD_SET(fd, &set);

		timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 0;

		int status = select(fd + 1, &set, NULL, NULL, &tv);
		if (status == -1) {
			return false;
		} else if (status == 0) {
			return false;
		} 
	}

	packet.clear();

	memset(buffer, 0, bufferLength);
	if ((receivedLength = recvfrom(fd, buffer, bufferLength, 0, (sockaddr*)newaddress, &inAddressLength)) < 0) {
		return false;
	}

	packet.set(buffer, receivedLength);
	return true;
}

bool Socket::broadcast(const Packet& packet, int port) {
	sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = INADDR_ANY;

	return send(packet, address);
}

bool Socket::send(const Packet& packet) {
	if (isValid() == false) {
		return false;
	}

	if (type != Socket::TCP) {
		return false;
	}

	if (::send(fd, packet.getData(), packet.getSize(), 0) == -1) {
		close(fd);
		fd = -1;
		return false;
	}

	return true;
}

bool Socket::receive(Packet& packet, bool blocking) {
	static const unsigned int BufferLength = 1024;
	char buffer[BufferLength];
	int length = 0;

	if (isValid() == false) {
		return false;
	}

	if (type != Socket::TCP) {
		return false;
	}

	if (blocking == false) {
		fd_set set;
		FD_ZERO(&set);
		FD_SET(fd, &set);

		timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 0;

		length = select(fd + 1, &set, NULL, NULL, &tv);
		if (length == -1) {
			return false;
		} else if (length == 0) {
			return false;
		}
	}

	length = recv(fd, buffer, BufferLength, 0);
	if (length == -1) {
		close(fd);
		fd = -1;
		return false;
	} else if (length == 0) {
		close(fd);
		fd = -1;
		return false;
	}

	packet.set(buffer, length);
	return true;
}

const char* Socket::getIPStr() const {
	static const unsigned int BufferLength = 256;
	static char buffer[BufferLength];
	return inet_ntop(AF_INET, &address.sin_addr, buffer, sizeof(address));
}

int Socket::getPort() const {
	return ntohs(address.sin_port);
}
