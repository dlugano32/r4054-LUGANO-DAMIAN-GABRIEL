#ifndef __SCHEDULER_LIB_H
#define __SCHEDULER_LIB_H

#include <stddef.h>
#include <stdint.h>

#define MAX_TASK 4

typedef struct{
    int ticks;
    int id;
    int *PC;    
    int *SP_IRQ;    /* Este SP va a apuntar a donde empieza el contexto de mi tarea. No coincide con el stack pointer de la tarea. Es el stack pointer de IRQ. Todo esa pila es de IRQ*/
    int *SP_SVC;
    int SPSR;
}TCB;

void __sched_init(void);
uint32_t* scheduler_c(void);
#endif