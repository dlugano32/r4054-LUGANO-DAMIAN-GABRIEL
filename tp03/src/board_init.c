#include "../inc/gic.h"
#include "../inc/timer.h"

void board_init(void);

__attribute__((section(".text"))) void board_init(void)
{
    __gic_init();
    __timer_init();
}
