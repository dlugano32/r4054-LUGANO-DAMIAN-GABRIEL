.code 32

.global _memcpy

.section .functions

_memcpy :

        push {r1,r3}        // lo guardo en la pila para no perder el contenido de r3 en el caso de estar en uso
        asr r2, #2          //aritmetic shift right// copio de a 4 bytes
        more:   ldr r3, [r0], #4    //Con el #4 le decis que postincremente 4 bytes
                str r3, [r1], #4
                subs r2, #1
                cmp r2, #0
        bne more
        pop {r1,r3}     // vuelvo a guardar el valor de los registros que salve
        mov pc, lr

.end
