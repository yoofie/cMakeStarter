/* **************************************
	File Name: App Logger
*************************************** */
#include "logger.h"
/* **************************************
	#defines
*************************************** */

/* **************************************
	Declarations
*************************************** */

/* **************************************
	Code
*************************************** */

void appLogger::init() {

	spdlog::set_pattern(
		"{\"timestamp\":\"%Y-%m-%d %H:%M:%S.%e %f\",\"tDelta_ms\":\"%o\",\"logger\":\"%n\",\"log_"
		"level\":\"%l\",\"file\":\"%s\",\"function\":\"%!\", \"line\":\"%#\",\"process_id\":%P,\"thread_id\":%t, \"message\": \"%v\"},");

	appSession = basic_logger_mt<spdlog::async_factory>("appSession", "debuglog.json");
	appWindow = basic_logger_mt<spdlog::async_factory>("app_Window", "debuglog.json");
	appLog = basic_logger_mt<spdlog::async_factory>("____appLog", "debuglog.json");
};
