#include <stddef.h>
#include <stdint.h>
#include "../inc/gic.h"
#include "../inc/timer.h"

typedef struct context_t {
    uint32_t cpsr, sp, lr, gpr[13];
}context_t;

void kernel_handler_irq(context_t* context );

__attribute__((section(".text"))) void kernel_handler_irq(context_t* context )
{
    uint32_t id=0;
    _gicc_t*  const GICC0  = (_gicc_t*)GICC0_ADDR;
    _timer_t* const TIMER01 = (_timer_t*)TIMER01_ADDR;

    id=GICC0->IAR & 0x000001FF;

    switch (id)
    {
    case GIC_SOURCE_TIMER01:
        if(TIMER01->Timer1RIS & 0x01)
            TIMER01->Timer1IntClr=0x01;
        else if (TIMER01->Timer2RIS & 0x01)
            TIMER01->Timer2IntClr=0x01;
        break;

    default:
        break;
    }

    GICC0->EOIR|=id;
}