#include "io.h"
#include "serial.h"

static void set_divisor() {
    u8 lcr = inb(_LCR);
    outb(_LCR, lcr | (1 << 7)); // Set DLAB = 1
    outb(_DLL, 0);
    outb(_DLM, 1);
    outb(_LCR, lcr & (~(1 << 7))); // Set DLAB = 0
}

static void set_thr_empty_interupt() {
    u8 lcr = inb(_LCR);
    outb(_LCR, lcr & (~(1 << 7))); // Set DLAB = 0

    u8 ier = inb(_IER);
    outb(_IER, ier | (1 << 1)); // Enable Transmitter Holding Register Empty Interrupt
}

static void set_fifo() {
    u8 lcr = inb(_LCR);
    outb(_LCR, lcr & (~(1 << 7))); // Set DLAB = 0

    u8 fcr = inb(_FCR);
    outb(_FCR, fcr | 1); // Enable FIFO
    outb(_FCR, fcr | (1 << 1)); // Clear receive FIFO
    outb(_FCR, fcr | (1 << 2)); // Clear transmit FIFO
    outb(_FCR, fcr | (1 << 6)); // Interrupt trigger level 14 bytes
    outb(_FCR, fcr | (1 << 7)); // Interrupt trigger level 14 bytes
}

static void set_lcr() {
    u8 lcr = inb(_LCR);
    outb(_LCR, lcr & (~(1 << 7))); // Set DLAB = 0
    outb(_LCR, lcr | 1); // 8 bits length
    outb(_LCR, lcr | (1 << 1)); // 8 bits length
    outb(_LCR, lcr | (1 << 3)); // 
}

void init_serial() {
    set_divisor();
    set_thr_empty_interupt();
    set_fifo();
    set_lcr();
}

int write(const char* buf, unsigned long count) {
    int i;
    
    for (i = 0; i < count; ++i) {
        outb(_THR, buf[i]);
    }
    return i;
}