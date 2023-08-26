/* **************************************
	File Name: Timestamp
*************************************** */
#include "Timestamp.h"
#include <algorithm>
using namespace std::chrono;
/* **************************************
	#defines
*************************************** */

/* **************************************
	Declarations
*************************************** */

/* **************************************
	Code
*************************************** */

Timestamp::Timestamp() {
	update();
}

Timestamp::~Timestamp() {}

void Timestamp::update() {
	recordedTimeStamp = high_resolution_clock::now();
}

std::chrono::time_point<std::chrono::high_resolution_clock> getRawTimeStamp() {
	return high_resolution_clock::now();
}

/* long long getTime_microSec() {
	return duration_cast<microseconds>(high_resolution_clock::now()).count();
} */

void Timestamp::integerToTimestamp(uint64_t input) {
	integer = input;
}

// Get second

double Timestamp::getElapsedSecond() {
	return getElapsedTimeInMicroSec() * 0.000001;
}

// Get millisecond

double Timestamp::getElapsedTimeInMilliSec() {
	return this->getElapsedTimeInMicroSec() * 0.001;
}

// Get microsecond

long long Timestamp::getElapsedTimeInMicroSec() {
	return duration_cast<microseconds>(high_resolution_clock::now() - recordedTimeStamp).count();
}

time_t Time::getCurrentTimeInMilliSec() {
	return duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
}

void to_json(json &j, const Timestamp &target) {
	j["timestamp"].push_back(target.recordedTimeStamp.time_since_epoch().count());
}

void from_json(const json &j, Timestamp &target) {
	auto vv = j["timestamp"];
	// target.recordedTimeStamp = j["timestamp"];
}

std::string Timestamp::timeString() {
	auto duration = recordedTimeStamp.time_since_epoch();
	typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<21>>::type> Days;
	Days days = std::chrono::duration_cast<Days>(duration);
	duration -= days;

	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	duration -= hours;

	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
	duration -= minutes;
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
	duration -= seconds;

	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	duration -= milliseconds;

	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);
	duration -= microseconds;

	auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

	std::string ss;

	ss += "M:" + std::to_string(minutes.count()) + " " + std::to_string(seconds.count()) + ":" + std::to_string(milliseconds.count()) + ":" + std::to_string(microseconds.count()) + ":" + std::to_string(nanoseconds.count());

	return ss;
}

/* ********************************************************
	Global
******************************************************** */
std::string getTheTime() {
	std::time_t reqTime = std::time(nullptr);
	std::string theTime = std::asctime(std::localtime(&reqTime));
	std::replace(theTime.begin(), theTime.end(), '\n', ' ');
	return theTime;
}

std::string timeStringg(std::chrono::time_point<std::chrono::high_resolution_clock> inputTime) {
	auto duration = inputTime.time_since_epoch();
	typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<21>>::type> Days;
	Days days = std::chrono::duration_cast<Days>(duration);
	duration -= days;

	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	duration -= hours;

	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
	duration -= minutes;
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
	duration -= seconds;

	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	duration -= milliseconds;

	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);
	duration -= microseconds;

	auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

	std::string ss;

	ss += "M:" + std::to_string(minutes.count()) + " " + std::to_string(seconds.count()) + ":" + std::to_string(milliseconds.count()) + ":" + std::to_string(microseconds.count()) + ":" + std::to_string(nanoseconds.count());

	return ss;
}
