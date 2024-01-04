.code 32

.global _undef_instruction_vector
.global _software_interrupt_vector
.global _prefetch_abort_vector
.global _data_abort_vector
.global _IRQ
.global _FIQ

.extern kernel_handler_irq


.section .handlers_

_undef_instruction_vector :
    B .

_software_interrupt_vector :
    B .

_prefetch_abort_vector :
    B .

_data_abort_vector :
    B .

_IRQ :  /* Por hw ya estoy usando los registros de irq */
    sub     lr, lr, #4
    stmfd   sp!, { r0-r12, lr } /* Guardo todo el contexto de donde se llamo la interrupcion en el stack de IRQ */
    mov     r7, sp
    mrs     r8, spsr    /* se guarda el cpsr en spsr por hw */
    push    { r7, r8 }   /* pusheo al stack */

    mov     r0, sp  /* Guarda el tcb de la tarea actual */
    bl      kernel_handler_irq
    mov     sp, r0

    pop     { r7, r8 }
    mov     sp, r7
    msr     spsr, r8
    ldmfd   sp!, { r0-r12, pc }^    /* Con el ^ hago spsr->cpsr xq no lo hace automatico*/

_FIQ :
    B .

.end

