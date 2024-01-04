.code 32

.extern _start
.global _reset_vector


.section .reset_vector

_reset_vector : //Garantizo que siempre entro por el mismo punto  //SVC(supervisor) modo en el que arranca el procesador
    b _start

.end


