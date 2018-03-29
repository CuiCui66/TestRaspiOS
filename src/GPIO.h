#pragma once

#include "utility.h"

/** File constant and layouts base found on BCM2835-ARM-Peripherals manual.
    link : https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf

    GPIO information starts at page 89
*/

#define GPIO_BASE PERIPH_BASE_PHY + 0x200000
#define GPIO_NUMBER 54

struct GPIO{
    class Func{
        u32 data[5];
    public:
        enum Fun {INPUT, OUTPUT, F5, F4, F0, F1, F2, F3};
        Fun getFun(u8 pin) volatile {
            // assert(pin < GPIO_NUMBER)
            return Fun((data[pin/10] >> 3 * (pin%10)) & 0b111);
        }
        void setFun(u8 pin, Fun fun) volatile {
            //assert(pin < GPIO_NUMBER and fun < 8)
            u32 val = data[pin/10];
            val |= ~(0b111 << 3 * (pin%10));
            val &= fun << 3 * (pin%10);
            data[pin/10] = val;
        }
    };
    static_assert(sizeof(Func) == 20);
    class PinBitField {
        u32 data[2];
    public:
        bool get(u8 pin) volatile {
            return (data[pin/32] >> pin%32) & 1;
        }
        void set(u8 pin, bool val) volatile {
            //assert(pin < GPIO_NUMBER and fun < 8)
            u32 tmp = data[pin/10];
            tmp |= ~(1 << (pin%10));
            tmp &= val << (pin%10);
            data[pin/10] = tmp;
        }
    };
    static_assert(sizeof(PinBitField) == 8);

    enum GPPUDDir{ NONE, PULL_UP, PULL_DOWN};
    class GPPUDGroup{
        u32 GPPUD;
        u32 GPPUDCLK[2];
    public:
        void set(GPPUDDir dir, u64 pins) volatile{
            // In fact the next 2 are no-op (u64 is passed on 2 registers).
            u32 pin_low = pins;
            u32 pin_high = pins >> 32;
            GPPUD = dir;
            wait(150);
            // dmb
            if(pin_low)GPPUDCLK[0] = pin_low;
            if(pin_high)GPPUDCLK[1] = pin_high;
            wait(150);
            //dmb
            GPPUD = 0;
            GPPUDCLK[0] = 0;
            GPPUDCLK[1] = 0;
        }
    };

    Func funcs;
    u32 reserved1;
    PinBitField force_set;
    u32 reserved2;
    PinBitField force_clear;
    u32 reserved3;
    PinBitField lvl;
    u32 reserved4;
    PinBitField event_detect;
    u32 reserved5;
    PinBitField rising_edge;
    u32 reserved6;
    PinBitField falling_edge;
    u32 reserved7;
    PinBitField high_detect;
    u32 reserved8;
    PinBitField low_detect;
    u32 reserved9;
    PinBitField async_rising_edge;
    u32 reserved10;
    PinBitField async_falling_edge;
    u32 reserved11;
    GPPUDGroup gppud;
};


volatile GPIO* const  gpio = (GPIO*)(GPIO_BASE);
