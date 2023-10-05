/* **************************************
	File Name: Thread CTRL
	Created: Wednesday October 19 2022
*************************************** */
#ifndef _THREAD_CTRL_H_
#define _THREAD_CTRL_H_

#include "copper.h"
/* **************************************
	#defines
*************************************** */

/* **************************************
	Declarations
*************************************** */
enum class threadCtrl_t {
	START = 0,
	PAUSE,
	EXIT
};

/* **************************************
	Extras
*************************************** */
void threadCtrlHandler(copper::buffered_channel<threadCtrl_t> *targetThread, threadCtrl_t cmd, bool &exitThread);

#endif
