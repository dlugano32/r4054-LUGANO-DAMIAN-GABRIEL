#ifndef __GIC_LIB_H
#define __GIC_LIB_H

#include <stddef.h>
#include <stdint.h>
#include "macro.h"

#define GICC0_ADDR 0x1E000000
#define GICD0_ADDR 0x1E001000
#define GICC1_ADDR 0x1E010000
#define GICD1_ADDR 0x1E011000
#define GICC2_ADDR 0x1E020000
#define GICD2_ADDR 0x1E021000
#define GICC3_ADDR 0x1E030000
#define GICD3_ADDR 0x1E031000

#define GIC_SOURCE_TIMER01 36
#define GIC_SOURCE_TIMER23 37
#define GIC_SOURCE_TIMER45 73
#define GIC_SOURCE_TIMER67 74

#define GIC_SOURCE_UART0 44
#define GIC_SOURCE_UART1 45
#define GIC_SOURCE_UART2 46
#define GIC_SOURCE_UART3 47

void __gic_init(void);

typedef volatile struct
    {
        uint32_t    CTLR;    
        uint32_t    PMR;    
        uint32_t    BPR;    
        uint32_t    IAR;    
        uint32_t    EOIR;    
        uint32_t    RPR;    
        uint32_t    HPPIR;    
    } _gicc_t;

typedef volatile struct
    {
        uint32_t CTLR;
        uint32_t TYPER;
        reserved(0, 0x0008, 0x00FC);
        uint32_t ISENABLER[3];
        reserved(1, 0x010C, 0x017C);
        uint32_t ICENABLER[3];
        reserved(2, 0x018C, 0x01FC);
        uint32_t ISPENDR[3];
        reserved(3, 0x020C, 0x027C);
        uint32_t ICPENDR[3];
        reserved(4, 0x028C, 0x02FC);
        uint32_t ISACTIVER[3];
        reserved(5, 0x030C, 0x03FC);
        uint32_t IPRIORITYR[24];
        reserved(6, 0x0460, 0x07FC);
        uint32_t ITARGETSR[24];
        reserved(7, 0x860, 0x0BFC);
        uint32_t ICFGR[6];
        reserved(8, 0x0C18, 0x0EFC);
        uint32_t SGIR;
        reserved(9, 0x0F04, 0x0FFC);
    } _gicd_t;

#endif // __GIC_LIB_H