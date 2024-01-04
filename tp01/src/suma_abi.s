.extern suma_c   /*Crea un simbolo que se va a poder acceder despues*/
.extern _PUBLIC_STACK_INIT

.global _start /*Le digo que lo que hago sirve para afuera del archivo*/

.code 32    /*Le digo que trabaje en ARM*/
.section .text
_start :
    LDR SP, =_PUBLIC_STACK_INIT

    MOV R0, #0x10
    MOV R1, #0x20   /*Le paso 2 argumentos al programa en C -> suma_c(R0, R1)*/

    /* B suma_c */

    LDR R10, =suma_c
    MOV LR, PC
    BX R10

    B .

.end    /*Es el final del codigo, lo que esta abajo no lo ensambla*/
