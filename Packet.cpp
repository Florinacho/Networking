#include "Packet.h"

#include <string.h>

Packet::Packet(int reserve) {
	if (reserve > 0) {
		data.reserve(reserve);
	}
}

Packet::Packet(const void* bytes, int length) {
	set(bytes, length);
}

void Packet::set(const void* bytes, const unsigned int length) {
	data.clear();
	data.insert(data.begin(), (char*)bytes, (char*)bytes + length);
}

void Packet::push_front(const void* bytes, unsigned int length) {
	data.insert(data.begin(), (unsigned char*)bytes, (unsigned char*)bytes + length);
}

void Packet::push_back(const void* bytes, unsigned int length) {
	data.insert(data.end(), (unsigned char*)bytes, (unsigned char*)bytes + length);
}

bool Packet::pop_front(void* bytes, const unsigned int length) {
	if (data.size() < length) {
		return false;
	}

	if (bytes) {
		memcpy(bytes, &data.front(), length);
	}
	data.erase(data.begin(), data.begin() + length);

	return true;
}

bool Packet::pop_back(void* bytes, const unsigned int length) {
	if (data.size() < length) {
		return false;
	}

	if (bytes) {
		memcpy(bytes, (unsigned char*)&data.back() - length, length);
	}
	data.erase(data.end() - length - 1, data.end() - 1);

	return true;
}

bool Packet::read(void* bytes, int length, int offset) {
	if (offset + length >= data.size()) {
		return false;
	}

	memcpy(bytes, &data[offset], length);
	return true;
}

bool Packet::read(void* bytes, int length) {
	if (read_offset + length >= data.size()) {
		return false;
	}

	memcpy(bytes, &data[read_offset], length);
	read_offset += length;
	return true;
}

void Packet::setOffset(int value) {
	if (value >= data.size()) {
		return;
	}

	read_offset = value;
}

int Packet::getOffset() const {
	return read_offset;
}

const unsigned char* Packet::getData() const {
	return &data[0];
}

unsigned int Packet::getSize() const {
	return data.size();
}

void Packet::clear() {
	data.clear();
	read_offset = 0;
}

unsigned char& Packet::operator [] (const int index) {
	return data[index];
}
