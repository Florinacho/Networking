#include "Packet.h"

#include <stdio.h>
#include <limits>

struct Person {
	int id;
	std::string name;
	bool male;
	unsigned age;
	float weight;

	bool operator == (const Person& other) const {
		return (id == other.id
			&& name == other.name
			&& male == other.male
			&& age == other.age
			&& weight == other.weight);
	}

	void print() {
		printf("Person\n");
		printf("\tid: %d\n", id);
		printf("\tname: %s\n", name.c_str());
		printf("\tmale: %hhu\n", male);
		printf("\tage: %u\n", age);
		printf("\tweight: %f\n", weight);
	}

	void printCompare(const Person& other) {
		printf("Person\n");
		printf("\tid: %d %s %d\n", id, (id == other.id) ? "==" : "!=", other.id);
		printf("\tname: \"%s\" %s \"%s\"\n", name.c_str(), (name == other.name) ? "==" : "!=", other.name.c_str());
		printf("\tmale: %hhu %s %hhu\n", male, (male == other.male) ? "==" : "!=", other.male);
		printf("\tage: %u %s %u\n", age, (age == other.age) ? "==" : "!=", other.age);
		printf("\tweight: %f %s %f\n", weight, (weight == other.weight) ? "==" : "!=", other.weight);
	}
};

int main() {
	int totalTestCount = 0;
	int testPassed = 0;
	int testFailed = 0;
	Packet packet;

	printf("Test: Packet\n\n");

	{
	// signed 8 bit integer
	const int8_t InitialValue = INT8_MIN;
	int8_t value = InitialValue;
	printf("Testing int8_t ... ");
	++totalTestCount;
	packet.clear();
	packet.write_int8(value);
	if (packet.read_int8(&value)) {
		if (value == InitialValue) {
			printf("PASSED! %hhd == %hhd\n", value, InitialValue);
			++testPassed;
		} else {
			printf("FAILED! %hhd != %hhd\n", value, InitialValue);
			++testFailed;
		}
	} else {
		printf("FAILED! Cannot read int8\n");
		++testFailed;
	}
	}
	
	{
	// unsigned 8 bit integer
	const uint8_t InitialValue = UINT8_MAX;
	uint8_t value = InitialValue;
	printf("Testing uint8_t ... ");
	++totalTestCount;
	packet.clear();
	packet.write_uint8(value);
	if (packet.read_uint8(&value)) {
		if (value == InitialValue) {
			printf("PASSED! %hhu == %hhu\n", value, InitialValue);
			++testPassed;
		} else {
			printf("FAILED! %hhu != %hhu\n", value, InitialValue);
			++testFailed;
		}
	} else {
		printf("FAILED! Cannot read uint8\n");
		++testFailed;
	}
	}

	{
	// signed 16 bit integer
	const int16_t InitialValue = INT16_MIN;
	int16_t value = InitialValue;
	printf("Testing int16_t ... ");
	++totalTestCount;
	packet.clear();
	packet.write_int16(value);
	if (packet.read_int16(&value)) {
		if (value == InitialValue) {
			printf("PASSED! %hd == %hd\n", value, InitialValue);
			++testPassed;
		} else {
			printf("FAILED! %hd != %hd\n", value, InitialValue);
			++testFailed;
		}
	} else {
		printf("FAILED! Cannot read int16\n");
		++testFailed;
	}
	}
	
	{
	// unsigned 16 bit integer
	const uint16_t InitialValue = UINT16_MAX;
	uint16_t value = InitialValue;
	printf("Testing uint16_t ... ");
	++totalTestCount;
	packet.clear();
	packet.write_uint16(value);
	if (packet.read_uint16(&value)) {
		if (value == InitialValue) {
			printf("PASSED! %hu == %hu\n", value, InitialValue);
			++testPassed;
		} else {
			printf("FAILED! %hu != %hu\n", value, InitialValue);
			++testFailed;
		}
	} else {
		printf("FAILED! Cannot read uint16\n");
		++testFailed;
	}
	}

	{
	// signed 32 bit integer
	const int32_t InitialValue = INT32_MIN;
	int32_t value = InitialValue;
	printf("Testing int32_t ... ");
	++totalTestCount;
	packet.clear();
	packet.write_int32(value);
	if (packet.read_int32(&value)) {
		if (value == InitialValue) {
			printf("PASSED! %d == %d\n", value, InitialValue);
			++testPassed;
		} else {
			printf("FAILED! %d != %d\n", value, InitialValue);
			++testFailed;
		}
	} else {
		printf("FAILED! Cannot read int32\n");
		++testFailed;
	}
	}
	
	{
	// unsigned 32 bit integer
	const uint32_t InitialValue = UINT32_MAX;
	uint32_t value = InitialValue;
	printf("Testing uint32_t ... ");
	++totalTestCount;
	packet.clear();
	packet.write_uint32(value);
	if (packet.read_uint32(&value)) {
		if (value == InitialValue) {
			printf("PASSED! %u == %u\n", value, InitialValue);
			++testPassed;
		} else {
			printf("FAILED! %u != %u\n", value, InitialValue);
			++testFailed;
		}
	} else {
		printf("FAILED! Cannot read uint32\n");
		++testFailed;
	}
	}

	{
	// signed 64 bit integer
	const int64_t InitialValue = INT64_MIN;
	int64_t value = InitialValue;
	printf("Testing int64_t ... ");
	++totalTestCount;
	packet.clear();
	packet.write_int64(value);
	if (packet.read_int64(&value)) {
		if (value == InitialValue) {
			printf("PASSED! %ld == %ld\n", value, InitialValue);
			++testPassed;
		} else {
			printf("FAILED! %ld != %ld\n", value, InitialValue);
			++testFailed;
		}
	} else {
		printf("FAILED! Cannot read int64\n");
		++testFailed;
	}
	}
	
	{
	// unsigned 64 bit integer
	const uint64_t InitialValue = UINT64_MAX;
	uint64_t value = InitialValue;
	printf("Testing uint64_t ... ");
	++totalTestCount;
	packet.clear();
	packet.write_uint64(value);
	if (packet.read_uint64(&value)) {
		if (value == InitialValue) {
			printf("PASSED! %lu == %lu\n", value, InitialValue);
			++testPassed;
		} else {
			printf("FAILED! %lu != %lu\n", value, InitialValue);
			++testFailed;
		}
	} else {
		printf("FAILED! Cannot read uint64\n");
		++testFailed;
	}
	}

	{
	// 32 bit float
	const float32_t InitialValue = -1234.567f;
	float32_t value = InitialValue;
	printf("Testing float32_t ... ");
	++totalTestCount;
	packet.clear();
	packet.write_float32(value);
	if (packet.read_float32(&value)) {
		if (value == InitialValue) {
			printf("PASSED! %f == %f\n", value, InitialValue);
			++testPassed;
		} else {
			printf("FAILED! %f != %f\n", value, InitialValue);
			++testFailed;
		}
	} else {
		printf("FAILED! Cannot read float32\n");
		++testFailed;
	}
	}
	
	{
	// 64 bit float
	const float64_t InitialValue = -765.4321;
	float64_t value = InitialValue;
	printf("Testing float64_t ... ");
	++totalTestCount;
	packet.clear();
	packet.write_float64(value);
	if (packet.read_float64(&value)) {
		if (value == InitialValue) {
			printf("PASSED! %lf == %lf\n", value, InitialValue);
			++testPassed;
		} else {
			printf("FAILED! %lf != %lf\n", value, InitialValue);
			++testFailed;
		}
	} else {
		printf("FAILED! Cannot read float64\n");
		++testFailed;
	}
	}

	{
	// string
	const std::string InitialValue = "Hello World!\t 1234";
	std::string value = InitialValue;
	printf("Testing string ... ");
	++totalTestCount;
	packet.clear();
	packet.write_string(value);
	if (packet.read_string(&value)) {
		if (value == InitialValue) {
			printf("PASSED! \"%s\" == \"%s\"\n", value.c_str(), InitialValue.c_str());
			++testPassed;
		} else {
			printf("FAILED! \"%s\" != \"%s\"\n", value.c_str(), InitialValue.c_str());
			++testFailed;
		}
	} else {
		printf("FAILED! Cannot read string\n");
		++testFailed;
	}
	}

	{
	// Custom struct
	Person InitialValue;
	InitialValue.id = 123;
	InitialValue.name = "Tony";
	InitialValue.male = true;
	InitialValue.age = 21;
	InitialValue.weight = 60;

	Person value = InitialValue;
	printf("Testing custom struct ... ");
	++totalTestCount;
	packet.clear();

	packet.write_int32(value.id);
	packet.write_string(value.name);
	packet.write_bool(value.male);
	packet.write_uint32(value.age);
	packet.write_float32(value.weight);

	if (packet.read_int32(&value.id) == false) {
		printf("FAILED! Cannot read id.\n");
	}
	if (packet.read_string(&value.name) == false) {
		printf("FAILED! Cannot read name.\n");
	}
	if (packet.read_bool(&value.male) == false) {
		printf("FAILED! Cannot read sex.\n");
	}
	if (packet.read_uint32(&value.age) == false) {
		printf("FAILED! Cannot read age.\n");
	}
	if (packet.read_float32(&value.weight) == false) {
		printf("FAILED! Cannot read weight.\n");
	}
	if (value == InitialValue) {
		printf("PASSED!\n");
		value.print();
		++testPassed;
	} else {
		printf("FAILED!\n");
		value.printCompare(InitialValue);
		++testFailed;
	}
	}

	printf("\n\nTest summary:\n");
	printf("\tTotal tests run: %d\n", totalTestCount);
	printf("\tPassed tests: %d\n", testPassed);
	printf("\tFailed tests: %d\n", testFailed);
	printf("\tPass rate: %.1f\n\n\n", ((float)testPassed / (float)totalTestCount) * 100.0f);
	return (testPassed == totalTestCount);
}
