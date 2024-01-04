.code 32

.global _start
.extern _table_start
.extern _PUBLIC_RAM_DEST
.extern tables_size

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

    b .

.end

