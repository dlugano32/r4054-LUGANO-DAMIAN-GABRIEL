#include "../inc/tareas.h"

__attribute__((section(".tarea_data"))) int g_i=0, g_d=0;

__attribute__((section(".tarea_idle"))) void tarea_idle(void)
{
    while (1)
    {
        asm("WFI");
    };
    
}

__attribute__((section(".tarea_1"))) void tarea_1(void)
{
    int A=0;

    while (1)
    {
        A++;
        g_i++;
    };
    
}

__attribute__((section(".tarea_2"))) void tarea_2(void)
{
    int A=0;

    while (1)
    {
        A--;
        g_d--;
    };
    
}

__attribute__((section(".tarea_3"))) void tarea_3(void)
{
    while (1)
    {
        g_i--;
        g_d++;
    };
}