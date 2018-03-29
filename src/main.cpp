#include "GPIO.h"
#include "AUX.h"
#include "Serial.h"

extern "C" int kmain(){
    Serial::init();
    Serial::puts("Hello world!\n");

    while(true) Serial::putc(Serial::getc());

    /// can't return from main;
    while(true);
}
