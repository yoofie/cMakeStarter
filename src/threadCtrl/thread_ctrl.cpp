/* **************************************
	File Name: Thread Control
*************************************** */
#include "thread_ctrl.h"

#include "globals.h"
#include "spdlog.h"
#include <iostream>

/* **************************************
	#defines
*************************************** */

/* **************************************
	Declarations
*************************************** */

/* **************************************
	Code
*************************************** */

void threadCtrlHandler(copper::buffered_channel<threadCtrl_t> *targetThread, threadCtrl_t cmd, bool &exitThread) {

	switch (cmd) {
		case threadCtrl_t::START: {
			std::cout << "Thread started!\n";
		} break;

		case threadCtrl_t::PAUSE: {
			std::cout << "Thread Paused\n";
		} break;

		case threadCtrl_t::EXIT:
		default: {
			std::cout << "Thread exited\n";
			exitThread = true;
			targetThread->close();
		} break;
	}
}
