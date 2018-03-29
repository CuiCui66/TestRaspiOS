#pragma once

class Serial{
public:
    static void init();
    static void putc(char c);
    static void puts(const char* str);
    static char getc();
};
