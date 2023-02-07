#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

typedef uint8_t u8;       ///<   8-bit unsigned integer.
typedef uint16_t u16;     ///<  16-bit unsigned integer.
typedef uint32_t u32;     ///<  32-bit unsigned integer.
typedef uint64_t u64;     ///<  64-bit unsigned integer.
typedef __uint128_t u128; ///< 128-bit unsigned integer.

typedef int8_t s8;       ///<   8-bit signed integer.
typedef int16_t s16;     ///<  16-bit signed integer.
typedef int32_t s32;     ///<  32-bit signed integer.
typedef int64_t s64;     ///<  64-bit signed integer.
typedef __int128_t s128; ///< 128-bit unsigned integer.

typedef volatile u8 vu8;     ///<   8-bit volatile unsigned integer.
typedef volatile u16 vu16;   ///<  16-bit volatile unsigned integer.
typedef volatile u32 vu32;   ///<  32-bit volatile unsigned integer.
typedef volatile u64 vu64;   ///<  64-bit volatile unsigned integer.
typedef volatile u128 vu128; ///< 128-bit volatile unsigned integer.

typedef volatile s8 vs8;     ///<   8-bit volatile signed integer.
typedef volatile s16 vs16;   ///<  16-bit volatile signed integer.
typedef volatile s32 vs32;   ///<  32-bit volatile signed integer.
typedef volatile s64 vs64;   ///<  64-bit volatile signed integer.
typedef volatile s128 vs128; ///< 128-bit volatile signed integer.

typedef unsigned char   uchar;
typedef	unsigned short	ushort;
typedef	unsigned int	uint;	
typedef	unsigned long	ulong;

typedef unsigned char   undefined;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined3;
typedef unsigned int    undefined4;
typedef unsigned long    undefined8;

#define ALIGN_UP(x, a) ((((uintptr_t)x) + (((uintptr_t)a)-1)) & ~(((uintptr_t)a)-1))
#define ALIGN_DOWN(x, a) ((uintptr_t)(x) & ~(((uintptr_t)(a)) - 1))
#define ALIGNED(a)      __attribute__((aligned(a)))
#define ON_INIT         __attribute__((constructor))
#define NOINLINE        __attribute__((noinline))
#define NORETURN        __attribute__((noreturn))
#define UNREACHABLE __builtin_unreachable()
#define PAGE_SIZE (0x1000)
#define ALWAYS_INLINE inline __attribute__((always_inline))
#define BITSIZEOF(x) (sizeof(x) * CHAR_BIT)

typedef __builtin_va_list va_list;
#define va_start(v,l) __builtin_va_start(v,l)
#define va_end(v) __builtin_va_end(v)

#define RAD(deg) (deg * (M_PI / 180)) // converts Degrees to Radians
#define DEG(rad) (rad * (180 / M_PI)) // converts Radians to Degrees
#define BTOC(bool) (bool ? "true" : "false") // converts boolean to true/false char
#define ACNT(arr) (sizeof(arr) / sizeof(arr[0]))  // returns size of inputted array
// used to convert macro values to strings
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

//using u64 = std::uint64_t;
//using s64 = std::int64_t;

// stores a result on a lot of OS-related functions
typedef u32 Result;
typedef u32 Handle;
typedef void (*ThreadFunc)(void*);
