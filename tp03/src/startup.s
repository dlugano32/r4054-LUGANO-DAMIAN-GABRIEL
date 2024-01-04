.code 32

.global _start
.extern _table_start
.extern _PUBLIC_RAM_DEST
.extern tables_size
.extern board_init

.equ USR_MODE, 0x10 /*ARM B1.3.1*/
.equ FIQ_MODE, 0x11
.equ IRQ_MODE, 0x12
.equ SVC_MODE, 0x13
.equ ABT_MODE, 0x17
.equ UND_MODE, 0x1B
.equ SYS_MODE, 0x1F
.equ I_BIT   , 0x80
.equ F_BIT   , 0x40

.section .startup
_start :

    _TABLE_COPY:
        ldr r0, =#_PUBLIC_RAM_DEST
        ldr r1, =_table_start
        ldr r2, =#tables_size
    
    _TABLE_LOOP:
        ldr  r3, [r1], #4
        str  r3, [r0], #4
        subs r2, #4
        cmp  r2, #0 
        bne _TABLE_LOOP

    _STACK_INIT :
        /* Inicializamos los stack pointers para los diferentes modos */
        MSR cpsr_c,#(IRQ_MODE | I_BIT | F_BIT)  /* I=1 Disables IRQ ; F=1 Disables FIQ */
        LDR SP,=__irq_stack_top__   /* IRQ stack pointer */

        MSR cpsr_c,#(SYS_MODE | I_BIT | F_BIT)
        LDR SP,=__fiq_stack_top__   /* SYS stack pointer */

        MSR cpsr_c,#(ABT_MODE | I_BIT | F_BIT)
        LDR SP,=__abt_stack_top__   /* ABT stack pointer */

        MSR cpsr_c,#(UND_MODE | I_BIT | F_BIT)
        LDR SP,=__und_stack_top__   /* UND stack pointer */

        MSR cpsr_c,#(SVC_MODE | I_BIT | F_BIT)
        LDR SP,=__svc_stack_top__   /* SVC stack pointer */
    
    _BOARD_INIT :

        LDR r10,= board_init    /* No uso BL porque no asegura si se cambia el modo de operacion o el lenguaje del codigo */
        MOV lr, pc              /* Guardo el PC */
        BX r10                  /* LLamo a la funcion */

    _IRQ_ENABLE :

        MRS r0, CPSR        
        BIC r0, r0, #0x80
        MSR CPSR_c, r0

    idle :
        WFI
        B idle
.end

