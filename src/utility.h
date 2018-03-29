#pragma once

#include <stddef.h>

typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
typedef int iptr;
typedef unsigned int uptr;

static_assert(sizeof(i8)==1);
static_assert(sizeof(u8)==1);
static_assert(sizeof(i16)==2);
static_assert(sizeof(u16)==2);
static_assert(sizeof(i32)==4);
static_assert(sizeof(u32)==4);
static_assert(sizeof(i64)==8);
static_assert(sizeof(u64)==8);
static_assert(sizeof(size_t)==4);
static_assert(sizeof(iptr) == sizeof(void*));
static_assert(sizeof(uptr) == sizeof(void*));


/// The base in the processor physical memory of the peripheral area on Raspi2 & 3
#define PERIPH_BASE_PHY 0x3F000000

/** number of unitsize sized element needed to cover size */
inline constexpr u32 place(u32 size, u32 unitsize){
    return (size + unitsize -1)/unitsize;
}

inline void wait(u32 time){
    for(volatile u32 i = 0 ; i < time ; ++i);
}

inline constexpr u64 bits(){ return 0;}
inline constexpr u64 bits(u8 a){ return 1ull << a;}
inline constexpr u64 bits(u8 a, u8 b){ return (1ull << a) & (1ull << b);}
inline constexpr u64 bits(u8 a, u8 b, u8 c){ return (1ull << a) & (1ull << b) & (1ull << c);}
