/* **************************************
	File Name: EVENTS
	Created: Sunday March 19 2023
*************************************** */
#ifndef _CHANNEL_EVENTS_H_
#define _CHANNEL_EVENTS_H_

#include <variant>
/* **************************************
	#defines
*************************************** */

/* **************************************
	Declarations
*************************************** */

/* **************************************
	Extras
*************************************** */
enum class uiEvent {
	SWITCH_ACTIVE_USER_SESSION,
	REQ_APP_EXIT
};

using eventData = std::variant<uiEvent, uint32_t, float>;
#endif
