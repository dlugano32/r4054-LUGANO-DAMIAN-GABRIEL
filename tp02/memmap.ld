/* 
    Definiciones necesarias: formato de salida, arquitectura

    Directivas, data para el linker : le decis que es de 32 bit (ARM) y que es little endian 
    y el punto de entrada se llama _start
*/
OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_reset_vector)

/* 
    Definiciones de simbolos necesarios

    Son define de posiciones de memoria
*/

_PUBLIC_RAM_INIT = 0X70010000;
_PUBLIC_STACK_INIT = 0X70020000;
_PUBLIC_RAM_DEST = 0x00000000;

/*
    Definicion del mapa de memoria

    se define dos regiones de memoria donde se le indica cual es el origen y el tamanio
    0x1000 -> 4Kb
*/
MEMORY
{
    public_ram : org = _PUBLIC_RAM_INIT, len = 0x1000       /* va de 0x70010000 a 0x70010FFF*/
    public_stack : org = _PUBLIC_STACK_INIT, len = 0x1000   /* va de 0x70020000 a 0x70020FFF */
}

/*
    Definicion de las secciones
*/
SECTIONS
{
    . = _PUBLIC_RAM_INIT;   /* el . es el program counter del linker, le digo que arranque en _PUBLIC_RAM_INIT y le indico donde quiero que me ponga el codigo */
    .text : {               /* el .text es la seccion de salida */
        *(.reset_vector*)   /* secciones de entrada  */
        *(.text*)
        *(.startup*)
        *(.table_isr*)
        *(.handlers_*)
    } > public_ram          /* lo asocio a public ram para que controle que no me pase de largo */
    
    /*Datos y variables globales inicializadas*/
    .data : { *(.data*) } > public_ram  /* El * (el de la derecha) es un comodin para agarrar a todos los archivos que empiecen igual. El de la izq es para las secciones de entrada (ponerlo siempre)  */

    .bss : {    /* datos y variables globales no inicializadas */
        . = ALIGN(4);   /* Lo alinea en 4 bytes */
        __bss_start__ = .;
        *(bss*)
        __bss_end__ = .;
    } > public_ram
}