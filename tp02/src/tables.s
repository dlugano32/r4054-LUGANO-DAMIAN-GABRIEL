.code 32
.global _table_start
.global tables_size

.extern _undef_instruction_vector
.extern _software_interrupt_vector
.extern _prefetch_abort_vector
.extern _data_abort_vector
.extern _IRQ
.extern _FIQ

.section .table_isr

_table_start :
    LDR PC, addr_reset_vector
    LDR PC, addr_undef_instruction_vector
    LDR PC, addr_software_interrupt_vector
    LDR PC, addr_prefetch_abort_vector
    LDR PC, addr_data_abort_vector
    LDR PC, addr_reset_vector //reserved
    LDR PC, addr_IRQ_vector
    LDR PC, addr_FIQ_vector

addr_reset_vector               :.word _reset_vector
addr_undef_instruction_vector   :.word _undef_instruction_vector
addr_software_interrupt_vector  :.word _software_interrupt_vector
addr_prefetch_abort_vector      :.word _prefetch_abort_vector
addr_data_abort_vector          :.word _data_abort_vector    // No puede acceder a una direccion de memoria o no reconoce el opcode
addr_IRQ_vector                 :.word _IRQ
addr_FIQ_vector                 :.word _FIQ

.equ tables_size , (.-_table_start)

.end
