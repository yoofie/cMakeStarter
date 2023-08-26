/* **************************************
	File Name: Loggers
	Created: Sunday March 19 2023
*************************************** */
#ifndef _LOGGING_H_
#define _LOGGING_H_
#include "async.h"
#include "spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
using namespace spdlog;
/* **************************************
	#defines
*************************************** */

/* **************************************
	Declarations
*************************************** */
struct appLogger {
	std::shared_ptr<spdlog::logger> appSession;
	std::shared_ptr<spdlog::logger> appWindow;
	std::shared_ptr<spdlog::logger> appLog;

	void init();
};

/* **************************************
	Extras
*************************************** */

#endif
