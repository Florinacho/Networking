CFLAGS= -c -g3
LFLAGS=

COMMON_LFILES=Timer.o Packet.o IPAddress.o Socket.o
TEST_LFILES=TestPacket.o

build: TestUDPServer TestUDPClient TestTCPServer TestTCPClient LanServer LanClient
#build: LanServer LanClient

TestPacket: TestPacket.o $(COMMON_LFILES)
	g++ $(LFLAGS) TestPacket.o $(COMMON_LFILES) -o TestPacket.out

TestUDPServer: TestUDPServer.o $(COMMON_LFILES)
	g++ $(LFLAGS) TestUDPServer.o $(COMMON_LFILES) -o TestUDPServer.out

TestUDPClient: TestUDPClient.o $(COMMON_LFILES)
	g++ $(LFLAGS)TestUDPClient.o $(COMMON_LFILES) -o TestUDPClient.out

TestTCPServer: TestTCPServer.o $(COMMON_LFILES)
	g++ $(LFLAGS)TestTCPServer.o $(COMMON_LFILES) -o TestTCPServer.out

TestTCPClient: TestTCPClient.o $(COMMON_LFILES)
	g++ $(LFLAGS)TestTCPClient.o $(COMMON_LFILES) -o TestTCPClient.out

LanServer: LanServer.o $(COMMON_LFILES)
	g++ $(LFLAGS) LanServer.o $(COMMON_LFILES) -o LanServer.out

LanClient: LanClient.o $(COMMON_LFILES)
	g++ $(LFLAGS) LanClient.o $(COMMON_LFILES) -o LanClient.out

Timer.o: Timer.cpp
	g++ $(CFLAGS) Timer.cpp -o Timer.o

Packet.o: Packet.cpp
	g++ $(CFLAGS) Packet.cpp -o Packet.o

IPAddress.o: IPAddress.cpp
	g++ $(CFLAGS) IPAddress.cpp -o IPAddress.o

Socket.o: Socket.cpp
	g++ $(CFLAGS) Socket.cpp -o Socket.o

TestPacket.o: TestPacket.cpp
	g++ $(CFLAGS) TestPacket.cpp -o TestPacket.o

TestTCPServer.o: TestTCPServer.cpp
	g++ $(CFLAGS) TestTCPServer.cpp -o TestTCPServer.o

TestTCPClient.o: TestTCPClient.cpp
	g++ $(CFLAGS) TestTCPClient.cpp -o TestTCPClient.o

TestUDPServer.o: TestUDPServer.cpp
	g++ $(CFLAGS) TestUDPServer.cpp -o TestUDPServer.o

TestUDPClient.o: TestUDPClient.cpp
	g++ $(CFLAGS) TestUDPClient.cpp -o TestUDPClient.o

LanServer.o: LanServer.cpp
	g++ $(CFLAGS) LanServer.cpp -o LanServer.o


clean:
	rm -rf *.s *.o *.out

rebuild: clean build
