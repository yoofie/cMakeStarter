/* **************************************
	File Name: 
	Created: Saturday April 23 2022
*************************************** */
#ifndef _UTILS_H_
#define _UTILS_H_


/* **************************************
	#defines
*************************************** */
#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])
#define ISOLATE_AND_GET_BITS(var, startPosition, numOfBits) (((var) & (((1u << (numOfBits)) - 1u) << (unsigned)(startPosition))) >> (startPosition))


/* **************************************
	Declarations
*************************************** */
/* For variant Overload */
template <class... Fs> struct Overload : Fs... { using Fs::operator()...; };
template <class... Fs> Overload(Fs...)->Overload<Fs...>;


/* ********************************************************
	auto y = std::visit(
			Overload{
				[](double input) {
					auto v = static_cast<float>(input);
					return v; },
			//[](int input) { return std::get<int>(input); },
			//[](int32_t input) { return std::get<int32_t>(input); },
			//[](uint32_t input) { return std::get<uint32_t>(input); },
			},
			my_data.at(idx));
******************************************************** */
/* **************************************
	Extras
*************************************** */



template <typename T>
inline T RandomRangeX(T min, T max) {
	T scale = rand() / (T)RAND_MAX;
	return min + scale * (max - min);
}
#endif
