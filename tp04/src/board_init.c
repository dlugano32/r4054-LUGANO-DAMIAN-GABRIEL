#include "../inc/gic.h"
#include "../inc/timer.h"
#include "../inc/scheduler.h"

void board_init(void);

__attribute__((section(".text"))) void board_init(void)
{
    __sched_init(); // Lo pongo aca para que no me interrumpa el timer. Porque tengo que habilitar las interrupciones para guardar el cpsr con las interrupciones activadas
    __gic_init();
    __timer_init();
}
