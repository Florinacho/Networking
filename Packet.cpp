#include "Packet.h"

#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

struct IEEE_754_32 {
	unsigned long sign : 1;
	unsigned long expoenent : 8;
	unsigned long precision :23;
};

struct IEEE_754_64 {
	unsigned long sign : 1;
	unsigned long expoenent : 11;
	unsigned long long precision :52;
};

union {
	float32_t fvalue;
	IEEE_754_32 rvalue;
	uint32_t uvalue;
} ConverterF32;

union {
	float64_t fvalue;
	IEEE_754_64 rvalue;
	uint64_t uvalue;
} ConverterF64;

union {
	int16_t svalue;
	uint16_t uvalue;
} Converter16;

union {
	int32_t svalue;
	uint32_t uvalue;
	float fvalue;
} Converter32;

union {
	int64_t svalue;
	uint64_t uvalue;
	double fvalue;
	struct {
		uint32_t lword;
		uint32_t hword;
	};
} Converter64;

int16_t htonss(int16_t value) {
	Converter16.svalue = value;
	Converter16.uvalue = htons(Converter16.uvalue);
	return Converter16.svalue;
}

int16_t ntohss(int16_t value) {
	Converter16.svalue = value;
	Converter16.uvalue = ntohs(Converter16.uvalue);
	return Converter16.svalue;
}

int32_t htonls(int32_t value) {
	Converter32.svalue = value;
	Converter32.uvalue = htonl(Converter32.uvalue);
	return Converter32.svalue;
}

int32_t ntohls(int32_t value) {
	Converter32.svalue = value;
	Converter32.uvalue = ntohl(Converter32.uvalue);
	return Converter32.svalue;
}

uint64_t htonll(uint64_t value) {
	uint32_t tmp;

	int num = 42;
	if (*(char *)&num != 42) {
		return value;
	}

	Converter64.uvalue = value;
	tmp = htonl(Converter64.lword);
	Converter64.lword = htonl(Converter64.hword);
	Converter64.hword = tmp;
	return Converter64.uvalue;
}

uint64_t ntohll(uint64_t value) {
	uint32_t tmp;

	int num = 42;
	if (*(char *)&num != 42) {
		return value;
	}

	Converter64.uvalue = value;
	tmp = ntohl(Converter64.lword);
	Converter64.lword = ntohl(Converter64.hword);
	Converter64.hword = tmp;
	return Converter64.uvalue;
}

uint64_t htonlls(int64_t value) {
	uint32_t tmp;

	int num = 42;
	if (*(char *)&num != 42) {
		return value;
	}

	Converter64.svalue = value;
	tmp = ntohl(Converter64.lword);
	Converter64.lword = ntohl(Converter64.hword);
	Converter64.hword = tmp;
	return Converter64.uvalue;
}

int64_t ntohlls(uint64_t value) {
	uint32_t tmp;

	int num = 42;
	if (*(char *)&num != 42) {
		return value;
	}

	Converter64.uvalue = value;
	tmp = ntohl(Converter64.lword);
	Converter64.lword = ntohl(Converter64.hword);
	Converter64.hword = tmp;
	return Converter64.svalue;
}

// Network 32 float is using IEEE_754_32
uint32_t htonf(float32_t value) {
	ConverterF32.fvalue = value;
	ConverterF32.uvalue = htonl(ConverterF32.uvalue);
	return ConverterF32.uvalue;
}

float32_t ntohf(uint32_t value) {
	ConverterF32.uvalue = value;
	ConverterF32.uvalue = ntohl(ConverterF32.uvalue);
	return ConverterF32.fvalue;
}

	// Network 32 float is using IEEE_754_64
uint64_t htond(float64_t value) {
	ConverterF64.fvalue = value;
	ConverterF64.uvalue = htonll(ConverterF64.uvalue);
	return ConverterF64.uvalue;
}

float64_t ntohd(uint64_t value) {
	ConverterF64.uvalue = value;
	ConverterF64.uvalue = ntohll(ConverterF64.uvalue);
	return ConverterF64.fvalue;
}

Packet::Packet(int reserve) {
	if (reserve > 0) {
		data.reserve(reserve);
	}
}

Packet::Packet(const void* bytes, const uint32_t size) {
	set(bytes, size);
}

void Packet::set(const void* bytes, const uint32_t size) {
	data.clear();
	write(bytes, size);
}

void Packet::write(const void* rawdata, const uint32_t size) {
	const unsigned char* cdata = reinterpret_cast<const unsigned char*>(rawdata);
	data.insert(data.end(), cdata, cdata + size);
}

void Packet::write_bool(bool value) {
	const unsigned char* cdata = reinterpret_cast<const unsigned char*>(&value);
	data.insert(data.end(), cdata, cdata + 1);
}
void Packet::write_int8(int8_t value) {
	const unsigned char* cdata = reinterpret_cast<const unsigned char*>(&value);
	data.insert(data.end(), cdata, cdata + 1);
}
void Packet::write_uint8(uint8_t value) {
	const unsigned char* cdata = reinterpret_cast<const unsigned char*>(&value);
	data.insert(data.end(), cdata, cdata + 1);
}
void Packet::write_int16(int16_t value) {
	value = htonss(value);
	const unsigned char* cdata = reinterpret_cast<const unsigned char*>(&value);
	data.insert(data.end(), cdata, cdata + 2);
}
void Packet::write_uint16(uint16_t value) {
	value = htons(value);
	const unsigned char* cdata = reinterpret_cast<const unsigned char*>(&value);
	data.insert(data.end(), cdata, cdata + 2);
}
void Packet::write_int32(int32_t value) {
	value = htonls(value);
	const unsigned char* cdata = reinterpret_cast<const unsigned char*>(&value);
	data.insert(data.end(), cdata, cdata + 4);
}
void Packet::write_uint32(uint32_t value) {
	value = htonl(value);
	const unsigned char* cdata = reinterpret_cast<const unsigned char*>(&value);
	data.insert(data.end(), cdata, cdata + 4);
}
void Packet::write_int64(int64_t value) {
	value = htonlls(value);
	const unsigned char* cdata = reinterpret_cast<const unsigned char*>(&value);
	data.insert(data.end(), cdata, cdata + 8);
}
void Packet::write_uint64(uint64_t value) {
	value = htonll(value);
	const unsigned char* cdata = reinterpret_cast<const unsigned char*>(&value);
	data.insert(data.end(), cdata, cdata + 8);
}
void Packet::write_float32(float32_t value) {
	uint32_t uvalue = htonf(value);
	const unsigned char* cdata = reinterpret_cast<const unsigned char*>(&uvalue);
	data.insert(data.end(), cdata, cdata + 4);
}
void Packet::write_float64(float64_t value) {
	uint64_t uvalue = htond(value);
	const unsigned char* cdata = reinterpret_cast<const unsigned char*>(&uvalue);
	data.insert(data.end(), cdata, cdata + 8);
}
void Packet::write_string(const std::string& value) {
	const uint32_t length = value.size();
	write_uint32(length);
	write(value.c_str(), length);
}
//
bool Packet::read(void* rawdata, uint32_t size) {
	if (read_offset + size > data.size()) {
		return false;
	}

	if (rawdata) {
		memcpy(rawdata, &data[read_offset], size);
	}
	read_offset += size;
	return true;
}

bool Packet::read_bool(bool* value) {
	if (read_offset + 1 > data.size()) {
		return false;
	}
	if (value) {
		memcpy(value, &data[read_offset], 1);
	}
	read_offset += 1;
	return true;
}

bool Packet::read_int8(int8_t* value) {
	if (read_offset + 1 > data.size()) {
		return false;
	}
	if (value) {
		memcpy(value, &data[read_offset], 1);
	}
	read_offset += 1;
	return true;
}
bool Packet::read_uint8(uint8_t* value) {
	if (read_offset + 1 > data.size()) {
		return false;
	}
	if (value) {
		memcpy(value, &data[read_offset], 1);
	}
	read_offset += 1;
	return true;
}
bool Packet::read_int16(int16_t* value) {
	if (read_offset + 2 > data.size()) {
		return false;
	}
	if (value) {
		memcpy(value, &data[read_offset], 2);
		*value = ntohss(*value);
	}
	read_offset += 2;
	return true;
}
bool Packet::read_uint16(uint16_t* value) {
	if (read_offset + 2 > data.size()) {
		return false;
	}
	if (value) {
		memcpy(value, &data[read_offset], 2);
		*value = ntohs(*value);
	}
	read_offset += 2;
	return true;
}
bool Packet::read_int32(int32_t* value) {
	if (read_offset + 4 > data.size()) {
		return false;
	}
	if (value) {
		memcpy(value, &data[read_offset], 4);
		*value = ntohls(*value);
	}
	read_offset += 4;
	return true;
}
bool Packet::read_uint32(uint32_t* value) {
	if (read_offset + 4 > data.size()) {
		return false;
	}
	if (value) {
		memcpy(value, &data[read_offset], 4);
		*value = ntohl(*value);
	}
	read_offset += 4;
	return true;
}
bool Packet::read_int64(int64_t* value) {
	if (read_offset + 8 > data.size()) {
		return false;
	}
	if (value) {
		memcpy(value, &data[read_offset], 8);
		*value = ntohlls(*value);
	}
	read_offset += 8;
	return true;
}
bool Packet::read_uint64(uint64_t* value) {
	if (read_offset + 8 > data.size()) {
		return false;
	}
	if (value) {
		memcpy(value, &data[read_offset], 8);
		*value = ntohll(*value);
	}
	read_offset += 8;
	return true;
}

bool Packet::read_float32(float32_t* value) {
	if (read_offset + 4 > data.size()) {
		return false;
	}
	if (value) {
		uint32_t uvalue;
		memcpy(&uvalue, &data[read_offset], 4);
		*value = ntohf(uvalue);
	}
	read_offset += 4;
	return true;
}

bool Packet::read_float64(float64_t* value) {
	if (read_offset + 8 > data.size()) {
		return false;
	}
	if (value) {
		uint64_t uvalue;
		memcpy(&uvalue, &data[read_offset], 8);
		*value = ntohd(uvalue);
	}
	read_offset += 8;
	return true;
}

bool Packet::read_string(std::string* value) {
	char* buffer = NULL;
	uint32_t length = 0;
	if (read_uint32(&length) == false) {
		return false;
	}

	if (value) {
		value->clear();
		value->resize(length);
		buffer = &(*value)[0];
	}
	if (read(buffer, length) == false) {
		return false;
	}
	return true;
}

void Packet::setOffset(const uint32_t value) {
	if (value >= data.size()) {
		return;
	}

	read_offset = value;
}

uint32_t Packet::getOffset() const {
	return read_offset;
}

const unsigned char* Packet::getData() const {
	return &data[0];
}

const char* Packet::c_str() const {
	return (const char*)&data[0];
}

uint32_t Packet::getSize() const {
	return (uint32_t)data.size();
}

void Packet::clear() {
	data.clear();
	read_offset = 0;
}
