/* **************************************
	File Name: Random Numbers
	Created: Saturday March 25 2023
*************************************** */
#ifndef _RANDOM_NUMBERS_H_
#define _RANDOM_NUMBERS_H_
#include <random>
/* **************************************
	#defines
*************************************** */

/* **************************************
	Declarations
*************************************** */

/* **************************************
	Extras
*************************************** */
template <typename T>
T generateID(uint64_t min, uint64_t max) {
	std::random_device rd;	// obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max);
	return distr(gen);
}

#endif
