#pragma once

typedef unsigned int   u32;
typedef          int   s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char  u8;
typedef          char  s8;


inline u16 low_16(u32 address) 
{
    return (u16)((address) & 0xFFFF);
}

inline u16 high_16(u32 address)
{
    return  (u16)(((address) >> 16) & 0xFFFF);
}
