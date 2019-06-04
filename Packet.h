#ifndef __PACKET_H__
#define __PACKET_H__

#include <vector>

class Packet {
	std::vector<unsigned char> data;
	int read_offset;

public:
	Packet(int reserve = -1);

	Packet(const void* bytes, int length);

	void set(const void* bytes, const unsigned int length);

	void push_front(const void* bytes, unsigned int length);

	void push_back(const void* bytes, unsigned int length);

	bool pop_front(void* bytes, const unsigned int length);

	bool pop_back(void* bytes, const unsigned int length);

	bool read(void* bytes, int length, int offset);

	bool read(void* bytes, int length);

	void setOffset(int value);

	int getOffset() const;

	const unsigned char* getData() const;

	unsigned int getSize() const;

	void clear();

	unsigned char& operator [] (const int index);
};

#endif //__PACKET_H__
