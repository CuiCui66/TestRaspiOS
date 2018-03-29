#include "Serial.h"
#include "AUX.h"
#include "GPIO.h"
void Serial::init() {
    aux->irqs.spi0 = false;
    aux->irqs.spi1 = false;
    aux->irqs.mini_uart = false;

    aux->enable.mini_uart = true;

    asm("dmb");
    mu->irq_en.transmit = false;
    mu->irq_en.recieve = false;

    mu->control.clear();

    mu->line_control.set8bits(true);

    mu->modem_control = 0;

    mu->irq_ident.clearFIFOs(bits(0,1));

    mu->setBaud(115200);

    asm("dmb");

    gpio->funcs.setFun(14, GPIO::Func::F5);
    gpio->funcs.setFun(15, GPIO::Func::F5);

    gpio->gppud.set(GPIO::NONE,bits(14,15));

    asm("dmb");
    mu->control.transmit_enable = true;
    mu->control.recieve_enable = true;

}

void Serial::putc(char c) {
    if (c == '\r') {
        while(!mu->line_status.transmit_ready);
        mu->data = '\r';
        while(!mu->line_status.transmit_ready);
        mu->data = '\n';
        return;
    }
    asm("dmb");
    while(!mu->line_status.transmit_ready);
    mu->data = c;
    asm("dmb");
}

void Serial::puts(const char* str) {
    while(*str){
        putc(*str);
        ++str;
    }
}

char Serial::getc() {
    asm("dmb");
    while(!mu->line_status.receive_new);
    char val = mu->data;
    asm("dmb");
    return val;
}
