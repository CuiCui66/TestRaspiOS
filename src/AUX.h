#pragma once

#include "utility.h"

/** File constant and layouts base found on BCM2835-ARM-Peripherals manual.
    link : https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf

    AUX information starts at page 8
*/


#define AUX_BASE PERIPH_BASE_PHY + 0x215000
#define MU_BASE AUX_BASE + 0x40
#define SYS_FREQ 250 * 1000 *1000 // 250MHz

struct AUX{
    struct Three {
        bool mini_uart :1;
        bool spi0 :1;
        bool spi1 :1;
        u32 reserved:29;
    } __attribute__((packed));
    static_assert(sizeof(Three) == 4);
    Three irqs;
    Three enable;
};

struct MiniUART{
    struct IER{ // IER & IIR
        bool transmit :1;
        bool recieve :1;
        u32 reserved:30;
    } __attribute__((packed));
    class IIR{
    public:
        bool pending : 1;
    private:
        u8 data : 2;
        u32 reserved : 29;
    public:
        enum {FIFO_TRANSMIT = 1, FIFO_RECIEVE = 2};
        void clearFIFOs(u8 flags) volatile {data = flags;}
    } __attribute__((packed));
    class LCR{
        u8 size : 2;
        u32 reserved : 5;
    public:
        bool breakTX : 1;
        u8 reserved2[3];
        void set8bits(bool b) volatile {
            if(b) size = 0b11;
            else size = 0;
        }
    } __attribute__((packed));
    struct LSR{
        bool receive_new :1;
        bool receive_overflow : 1;
        u8 reserved:3;
        bool transmit_ready:1;
        bool transmit_idle:1;
        u32 reserved2: 25;
    } __attribute__((packed));
    struct CNTL{
        bool recieve_enable:1;
        bool transmit_enable:1;
        bool RTS_enable:1;
        bool CTS_enable:1;
        enum RTSLevel{ L3, L2, L1, L4};
        RTSLevel RTS_level : 2;
        bool RTS_assert_level:1;
        bool CTS_assert_level:1;
        u8 reserved[3];
        void clear()volatile{*reinterpret_cast<volatile u32*>(this) = 0;}
    };

    u8 data;
    u8 reserved[3];
    IER irq_en;
    IIR irq_ident;
    LCR line_control;
    u32 modem_control;
    LSR line_status;
    u32 modem_status;
    u8 scratch;
    u8 reserved2[3];
    CNTL control;
    u32 status;
    u16 baud_reg;
    u16 reserved3;
    void setBaud(u32 baud) volatile {
        /// Section 2.2.1 of the manual
        baud_reg = ( SYS_FREQ / ( 8 * baud ) ) - 1;
    }
}__attribute__((packed));
static_assert(sizeof(MiniUART) == 11*4);


volatile AUX* const  aux = (AUX*)(AUX_BASE);
volatile MiniUART* const mu = (MiniUART*)(MU_BASE);
