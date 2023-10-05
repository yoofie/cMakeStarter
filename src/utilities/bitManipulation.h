#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H

/*!****************************************************************************
**  \file   bit_manipulation.h
**  \brief  functionality for manipulating individual bits in integers.
******************************************************************************/

// include standard typedefs
// #include <bool>
#include <stdint.h>
#include <stdlib.h>

// BIT2MASK hereby deprecated in favour of higher level bit access functions
// #define BIT2MASK(bit)     (1u << (bit))

#define BIT_TO_MASK(bit)		 (1uL << (unsigned)(bit))
#define BITS_TO_MASK(lsb, count) (((1u << (count)) - 1u) << (unsigned)(lsb)) // MISRAFix 3410

/* ******************************************************************************
	The Basics
****************************************************************************** */

#define BIT_SET(var, bit)	  ((var) |= (1u << (unsigned)(bit)))
#define BIT_SET_U32(var, bit) ((var) |= (((uint32_t)1u) << (unsigned)(bit)))
#define BIT_CLR(var, bit)	  ((var) &= ~(1u << (unsigned)(bit)))
#define BIT_GET(var, bit)	  ((0u != ((var) & (1u << (unsigned)(bit)))) ? 1u : 0u)

#define BIT_GET_BOOL(var, bit)			  (0u != ((var) & (1u << (unsigned)(bit))))
#define BIT_GET_BOOL_U32(var, bit)		  (0u != ((var) & ((uint32_t)1u << (unsigned)(bit))))
#define BIT_WRITE(var, bit, val)		  ((var) = ((var) & ~(1u << (unsigned)(bit))) | (((unsigned)(val)&0x1u) << (unsigned)(bit)))
#define BIT_WRITE_BOOL(var, bit, val)	  BIT_WRITE(var, bit, (val) ? 1u : 0u)
#define BIT_WRITE_U16(var, bit, val)	  ((var) = (uint16_t)(((unsigned)(var) & ~(1u << (unsigned)(bit))) | (((unsigned)(val)&0x1u) << (unsigned)(bit))))
#define BIT_WRITE_U8(var, bit, val)		  ((var) = (uint8_t)(((unsigned)(var) & ~(1u << (unsigned)(bit))) | (((unsigned)(val)&0x1u) << (unsigned)(bit))))
#define BIT_WRITE_BOOL_U16(var, bit, val) BIT_WRITE_U16(var, bit, (val) ? 1u : 0u)
#define BIT_WRITE_BOOL_U8(var, bit, val)  BIT_WRITE_U8(var, bit, (val) ? 1u : 0u)

#define BIT_GET_U64(var, bit) \
	((0u != ((var) & ((uint64_t)1u << (uint64_t)(bit)))) ? 1u : 0u)
#define BIT_SET_U64(var, bit) ((var) |= ((uint64_t)1u << (uint64_t)(bit)))
#define BIT_CLR_U64(var, bit) ((var) &= ~((uint64_t)1u << (uint64_t)(bit)))

#define BIT_ARRAY(var, bit, action)                                                                              \
	do {                                                                                                         \
		if ((((size_t)(bit)) / (sizeof((var)[0]) * 8u)) < (sizeof(var) / sizeof((var)[0]))) {                    \
			action((var)[((size_t)(bit)) / (sizeof((var)[0]) * 8u)], ((size_t)(bit)) % (sizeof((var)[0]) * 8u)); \
		} else {                                                                                                 \
		}                                                                                                        \
	} while (false)

#define BIT_SET_ARRAY(var, bit)		 BIT_ARRAY(var, bit, BIT_SET)
#define BIT_GET_ARRAY(var, bit)		 BIT_ARRAY(var, bit, BIT_GET)
#define BIT_GET_BOOL_ARRAY(var, bit) BIT_ARRAY(var, bit, BIT_GET_BOOL)
#define BIT_CLR_ARRAY(var, bit)		 BIT_ARRAY(var, bit, BIT_CLR)

#define BITS_SET(var, bits, pos) (var |= ((bits) << (pos)))

//                                           mask------------------ shift to lsb ------- shift masked value back to bit0
#define BITS_GET(var, lsb, count)		 (((var) & (((1u << (count)) - 1u) << (unsigned)(lsb))) >> (lsb))
#define BITS_GET_U64(var, lsb, count)	 (((var) & (((1u << (count)) - 1u) << (unsigned long long)(lsb))) >> (lsb))
#define BITS_WRITE(var, lsb, count, val) ((var) = ((var) & ~BITS_TO_MASK(lsb, count)) | (((val)&BITS_TO_MASK(0, count)) << (lsb)))
/* ******************************************************************************
	Bit Mask Operations
****************************************************************************** */
// If the var in question has any bits set, aka the value is > 0u
#define BITMASK_ANY(var, mask) (0u != ((var) & (mask)))

// If the var in question has the exact same bit pattern as the mask?
#define BITMASK_ALL(var, mask) ((mask) == ((var) & (mask)))

// If the var in question exactly matches the mask?
#define BITMASK_CHK(var, mask) ((mask) == (var))

// Set the values according to the bitmask
#define BITMASK_SET(var, mask) ((var) |= (mask))

// Clear the values according to the bitmask
#define BITMASK_CLR(var, mask) ((var) &= ~(mask))

// Write the value
#define BITMASK_WRITE(var, mask, val) ((var) = ((var) & ~(mask)) | ((mask) & (val)))

#define BITMASK_ANY_UL(var, mask) (0UL != ((var) & (mask)))

/// this functions exists only for static assertion of types
// static inline void bit_manipulation_init(void)
//{
//     assert(sizeof(unsigned) >= 4u, "unsigned int must equal word length for bit shift macros to work right");
// }

#endif // BIT_MANIPULATION_H
