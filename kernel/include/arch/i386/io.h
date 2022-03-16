//
// Created by scot on 12/03/2022.
//

#ifndef MYOS_KERNEL_IO_H
#define MYOS_KERNEL_IO_H
#include "stdint.h"

static inline void outb(uint8_t v, uint16_t port)
{
    asm volatile("outb %0,%1" : : "a" (v), "dN" (port));
}
static inline uint8_t inb(uint16_t port)
{
    uint8_t v;
    asm volatile("inb %1,%0" : "=a" (v) : "dN" (port));
    return v;
}


#endif //MYOS_KERNEL_IO_H
