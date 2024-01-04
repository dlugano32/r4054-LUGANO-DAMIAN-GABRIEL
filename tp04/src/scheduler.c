#include "../inc/scheduler.h"
#include "../inc/kernel.h"
#include "../inc/tareas.h"

#define SVC_MODE 0x13
#define IRQ_MODE 0x12

extern uint32_t __task_irq_idle_stack_top__ , __task1_irq_stack_top__, __task2_irq_stack_top__, __task3_irq_stack_top__;
extern uint32_t __task_svc_idle_stack_top__ , __task1_svc_stack_top__, __task2_svc_stack_top__, __task3_svc_stack_top__;

__attribute__((section(".kernal_data"))) int tick_counter=0;
__attribute__((section(".kernal_data"))) int current_task=0;
__attribute__((section(".kernal_data"))) int task_switch=0;
__attribute__((section(".kernal_data"))) int ticks[4]={5,8,12,5};
__attribute__((section(".kernal_data"))) TCB tcb_tareas[4];
__attribute__((section(".kernal_data"))) void (*funciones[4])(void)={tarea_idle, tarea_1, tarea_2, tarea_3};
__attribute__((section(".kernal_data"))) uint32_t* stacks_top_irq[4]={&__task_irq_idle_stack_top__,&__task1_irq_stack_top__,&__task2_irq_stack_top__, &__task3_irq_stack_top__};
__attribute__((section(".kernal_data"))) uint32_t* stacks_top_svc[4]={&__task_svc_idle_stack_top__,&__task1_svc_stack_top__,&__task2_svc_stack_top__, &__task3_svc_stack_top__};


__attribute__((section(".kernel_text"))) void __sched_init(void) /* Inicializo los TCB*/
{
    uint8_t i=0, j=0;

    for(i=0; i<MAX_TASK; i++)
    {
        tcb_tareas[i].SP_IRQ=stacks_top_irq[i];
        tcb_tareas[i].SP_SVC=stacks_top_svc[i];
        tcb_tareas[i].ticks=ticks[i];
        tcb_tareas[i].id=i;  

        for(j=0; j<16; j++)
        {
            tcb_tareas[i].SP_IRQ--;

            if(j==0)    //LR
            {
                *(tcb_tareas[i].SP_IRQ)=(int)funciones[i];
                tcb_tareas[i].PC=(uint32_t*)funciones[i];
            }

            if(j>0 && j<14) // RO a R12
            {
                *(tcb_tareas[i].SP_IRQ)=0;
            }

            if(j==15)   // SP que apunta a R0
            {
                *(tcb_tareas[i].SP_IRQ)=(int)(tcb_tareas[i].SP_IRQ+2);
            }

            if(j==14)   //CPSR
            {
                asm("cpsie i");     //cps interrupt enable IRQ
                asm("mrs %0, cpsr" : "=r"(*(tcb_tareas[i].SP_IRQ)));
                asm("cpsid i"); //cps interrupt disable IRQ
                tcb_tareas[i].SPSR=*(tcb_tareas[i].SP_IRQ);
            }
        } 

    }
}

__attribute__((section(".kernel_text"))) uint32_t* scheduler_c(void)
{
    uint32_t old_task=current_task;
    tick_counter++;

    if( tick_counter >  tcb_tareas[current_task].ticks)
    {
        task_switch=1;
        tick_counter=0;
        current_task= (current_task+1) % MAX_TASK;

        if(task_switch)
        {
            task_switch=0;
            //Guardo el SP_IRQ de la tarea antes de hacer el switch
            asm( "str sp, %0" : "=m"(tcb_tareas[old_task].SP_IRQ));

            //Cambio en SVC
            asm("CPS #0x13");

            //Guardo el SP_SVC
            asm("str sp, %0" : "=m"(tcb_tareas[old_task].SP_SVC));
            //asm("mov sp, %0" : "=r"(tcb_tareas[current_task].SP_SVC));
            asm("ldr sp, %0" : "=m"(tcb_tareas[current_task].SP_SVC));


            //Cambio a IRQ
            asm("CPS #0x12");
            //asm("mov sp, %0" : "=r"(tcb_tareas[current_task].SP_IRQ));
            asm("ldr sp, %0" : "=m"(tcb_tareas[current_task].SP_IRQ));
        }
    }

    return tcb_tareas[current_task].SP_IRQ;
}