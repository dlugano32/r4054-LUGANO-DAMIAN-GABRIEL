.code 32

.global _undef_instruction_vector
.global _software_interrupt_vector
.global _prefetch_abort_vector
.global _data_abort_vector
.global _IRQ
.global _FIQ


.section .handlers_

_undef_instruction_vector :
    B .

_software_interrupt_vector :
    B .

_prefetch_abort_vector :
    B .

_data_abort_vector :
    B .

_IRQ :
    B .

_FIQ :
    B .

.end

