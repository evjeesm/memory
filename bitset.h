#ifndef _BITSET_H_
#define _BITSET_H_
#include <string.h> /* strcat, memset */

/*
* Macros that operate with raw memory on bit level.
* Bit field granularity can be varied, which is useful,
* when several bits need to be grouped logically together.
*
* Note: byte by byte memory access,
*       works only for array of chars as `memory` argument.
*/

/*
* Bit field sizes:
*/
#define BYTE 8
#define NIBBLE 4
#define CRUMB 2

/*
* Initialize bitset to zero.
*/
#define bitset_init(memory, size) do { memset(memory, 0, size); } while(0)

/*
* Get current value of the bit field.
*/
#define bitset_test(memory, field_size, index) \
    (field_mask(field_size) & ( \
        to_char_ptr(memory)[byte_for(field_size, index)] >> shift_for(field_size, index) \
        ) \
    )

/*
* Set bit field to a specific value.
*/
#define bitset_set(memory, field_size, index, value) \
    ( to_char_ptr(memory)[byte_for(field_size, index)] \
        ^= ( bitset_test(memory, field_size, index) ^ (char)value ) \
            << shift_for(field_size, index) )

/*
* Write contents of the bit field to string buffer.
* String buffer has to be large enough to fit bitset contents including spacing.
* spacing - parameter specifies how many bits to separate with single `space` character.
*/
#define bitset_to_str(memory, buf, size, spacing) do {\
    buf[0] = '\0'; \
    for (size_t i = 0; i < size; ++i) \
    {\
        if (spacing && !(i % spacing)) strcat(buf, " "); \
        char bit = bitset_test(memory, 1, i); \
        strcat(buf, bit ? "1" : "0"); \
    } \
} while (0)


#define byte_for(field_size, index) (index / (BYTE / field_size))

#define shift_for(field_size, index) (index * field_size % BYTE)

#define field_mask(field_size) ((1 << field_size) - 1)

#define to_char_ptr(memory) ((char*)memory)

#endif/*_BITSET_H_*/
