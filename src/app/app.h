/* **************************************
	File Name: App Stuff
	Created: Saturday March 18 2023
*************************************** */
#ifndef _APP_H_
#define _APP_H_

#include "logger.h"
/* **************************************
	#defines
*************************************** */

/* **************************************
	Declarations
*************************************** */
struct appData {
	appLogger log;

	void init();
	void reqExit();
};

/* **************************************
	Extras
*************************************** */

#endif
