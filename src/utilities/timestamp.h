#ifndef _Timestamp_h_
#define _Timestamp_h_

#include "json.hpp"
#include <chrono>

using json = nlohmann::json;

class Time {
  public:
	// Get current time in millisecond
	static time_t getCurrentTimeInMilliSec();
};

class Timestamp {
  public:
	std::chrono::time_point<std::chrono::high_resolution_clock> recordedTimeStamp;
	uint64_t integer;
	Timestamp();
	~Timestamp();

	void update();

	void integerToTimestamp(uint64_t input);

	std::chrono::time_point<std::chrono::high_resolution_clock> getRawTimeStamp();
	// long long getTime_microSec();
	// std::chrono::time_point<std::chrono::high_resolution_clock> getRawTimeStamp();
	//  Get second
	double getElapsedSecond();

	// Get millisecond
	double getElapsedTimeInMilliSec();

	// Get microsecond
	long long getElapsedTimeInMicroSec();
	std::string timeString();
};

inline uint64_t getRandom() {
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto epoch = now_ms.time_since_epoch();
	auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
	return value.count();
}

std::string timeStringg(std::chrono::time_point<std::chrono::high_resolution_clock> inputTime);

std::string getTheTime();
void to_json(json &j, const Timestamp &target);
void from_json(const json &j, Timestamp &target);
#endif // !_Timestamp_h_
