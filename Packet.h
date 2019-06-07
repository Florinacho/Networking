#ifndef __PACKET_H__
#define __PACKET_H__

#include <stdint.h>
#include <vector>
#include <string>

typedef float float32_t;
typedef double float64_t;

class Packet {
	std::vector<unsigned char> data;
	uint32_t read_offset;

public:
	Packet(const int32_t reserve = -1);

	Packet(const void* rawdata, const uint32_t size);

	void set(const void* rawdata, const uint32_t size);

	// write
	void write(const void* rawdata, const uint32_t size);

	void write_bool(bool value);

	void write_int8(int8_t value);

	void write_uint8(uint8_t value);

	void write_int16(int16_t value);

	void write_uint16(uint16_t value);

	void write_int32(int32_t value);

	void write_uint32(uint32_t value);

	void write_int64(int64_t value);

	void write_uint64(uint64_t value);

	void write_string(const std::string& value);

	void write_float32(float32_t value);

	void write_float64(float64_t value);

	// read
	bool read(void* data, uint32_t size);

	bool read_bool(bool* value);

	bool read_int8(int8_t* value);

	bool read_uint8(uint8_t* value);

	bool read_int16(int16_t* value);

	bool read_uint16(uint16_t* value);

	bool read_int32(int32_t* value);

	bool read_uint32(uint32_t* value);

	bool read_int64(int64_t* value);

	bool read_uint64(uint64_t* value);

	bool read_float32(float32_t* value);

	bool read_float64(float64_t* value);

	bool read_string(std::string* value);

	// utils
	void setOffset(const uint32_t value);

	uint32_t getOffset() const;

	const unsigned char* getData() const;

	const char* c_str() const;

	uint32_t getSize() const;

	void clear();
};

#endif //__PACKET_H__
