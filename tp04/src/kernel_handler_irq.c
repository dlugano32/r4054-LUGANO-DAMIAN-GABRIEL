#include "../inc/gic.h"
#include "../inc/timer.h"
#include "../inc/scheduler.h"
#include "../inc/kernel.h"

__attribute__((section(".text"))) uint32_t* kernel_handler_irq(context_t* context )
{
    uint32_t id=0;
    uint32_t* ret=(context->sp-2);
    _gicc_t*  const GICC0  = (_gicc_t*)GICC0_ADDR;
    _timer_t* const TIMER01 = (_timer_t*)TIMER01_ADDR;

    id=GICC0->IAR & 0x000001FF;

    switch (id)
    {
        case GIC_SOURCE_TIMER01:
            if(TIMER01->Timer1RIS & 0x01)
            {
                TIMER01->Timer1IntClr=0x01;
                ret=scheduler_c();

            }
            else if (TIMER01->Timer2RIS & 0x01)
            {
                TIMER01->Timer2IntClr=0x01;
            }
            break;

            default:
            break;
    }

    GICC0->EOIR|=id;

    return ret;
}