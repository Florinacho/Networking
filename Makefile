CFLAGS= -c -g3
LFLAGS=

build: TestUDPServer TestUDPClient TestTCPServer TestTCPClient

TestUDPServer: TestUDPServer.o Packet.o Socket.o
	g++ $(LFLAGS) TestUDPServer.o Packet.o Socket.o -o TestUDPServer.out

TestUDPServer.o: TestUDPServer.cpp
	g++ $(CFLAGS) TestUDPServer.cpp -o TestUDPServer.o

TestUDPClient: TestUDPClient.o Packet.o Socket.o
	g++ $(LFLAGS)TestUDPClient.o Packet.o Socket.o -o TestUDPClient.out

TestUDPClient.o: TestUDPClient.cpp
	g++ $(CFLAGS) TestUDPClient.cpp -o TestUDPClient.o

TestTCPServer.o: TestTCPServer.cpp
	g++ $(CFLAGS) TestTCPServer.cpp -o TestTCPServer.o

TestTCPServer: TestTCPServer.o Packet.o Socket.o
	g++ $(LFLAGS)TestTCPServer.o Packet.o Socket.o -o TestTCPServer.out

TestTCPClient.o: TestTCPClient.cpp
	g++ $(CFLAGS) TestTCPClient.cpp -o TestTCPClient.o

TestTCPClient: TestTCPClient.o Packet.o Socket.o
	g++ $(LFLAGS)TestTCPClient.o Packet.o Socket.o -o TestTCPClient.out

Packet.o: Packet.cpp
	g++ $(CFLAGS) Packet.cpp -o Packet.o

Socket.o: Socket.cpp
	g++ $(CFLAGS) Socket.cpp -o Socket.o

clean:
	rm -rf Packet.o
	rm -rf Socket.o
	rm -rf TestUDPServer.o TestUDPServer.out
	rm -rf TestUDPClient.o TestUDPClient.out
	rm -rf TestTCPServer.o TestTCPServer.out
	rm -rf TestTCPClient.o TestTCPClient.out
	rm -rf a.out

rebuild: clean build
