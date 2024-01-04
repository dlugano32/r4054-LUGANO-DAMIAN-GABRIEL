#ifndef __KERNEL_LIB_H__
#define __KERNEL_LIB_H__

#include <stddef.h>
#include <stdint.h>

typedef struct context_t {
    uint32_t *sp, spsr, gpr[13], *lr;
}context_t;

uint32_t* kernel_handler_irq(context_t* context );

#endif