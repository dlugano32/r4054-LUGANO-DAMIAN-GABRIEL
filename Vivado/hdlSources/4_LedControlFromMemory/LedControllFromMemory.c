#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "xbasic_types.h"
#include "xil_io.h"
#include "sleep.h"
#include "xil_cache.h"

#define SLV_REG0 0
#define SLV_REG1 1
#define SLV_REG2 2
#define SLV_REG3 3
#define SLV_REG4 4
#define SLV_REG5 5

#define LED0	0x01
#define LED1	0x02
#define LED2	0x04
#define LED3	0x08
#define LED4	0x10
#define LED5	0x20
#define LED6	0x40
#define LED7	0x80

#define ENA (1<<13)
#define WEA (1<<14)
#define DINA 5

#define ENB (1<<20)
#define ADDRB (15)

#define MEMORY_DEPTH 32

#define ALL_LEDS 0xFF

Xuint32 * LED_CONTROLLER_AXI_BUS_ADDR = (Xuint32 *) XPAR_AXI_COMM_BUS_0_BASEADDR;

// Macro, reemplaza esto en la funcion Xil_Out32

#define LED_Controller_AXI_BUS_mWriteReg(BaseAddress, RegOffset, Data) \
	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

// Macro, reemplaza esto en la funcion Xil_In32

#define LED_Controller_AXI_BUS_mReadReg(BaseAddress, RegOffset) \
	Xil_In32((BaseAddress) + (RegOffset))

void InitSecuencia(void);

int main()
{
	uint8_t addr=0, seq=0;


    init_platform();
    InitSecuencia();

    while(1)
    {
		LED_Controller_AXI_BUS_mWriteReg(LED_CONTROLLER_AXI_BUS_ADDR, SLV_REG1, ENB | addr<<ADDRB);
		usleep(10);
		seq=0xFF & ( LED_Controller_AXI_BUS_mReadReg(LED_CONTROLLER_AXI_BUS_ADDR, SLV_REG5) );
		usleep(10);
		LED_Controller_AXI_BUS_mWriteReg(LED_CONTROLLER_AXI_BUS_ADDR, SLV_REG0, seq);
		addr++;
		addr%=MEMORY_DEPTH;
		sleep(1);
    }

    cleanup_platform();
    return 0;
}

void InitSecuencia(void)
{
/*	uint32_t seq[MEMORY_DEPTH]={ALL_LEDS, LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7,
								LED0 | LED1, LED0 | LED1, LED0 | LED2, LED0 | LED3, LED0 | LED4,
								LED0 | LED5, LED0 | LED6, LED0 | LED7, LED1 | LED0, LED1 | LED2,
								LED1 | LED3, LED1 | LED4, LED1 | LED5, LED1 | LED6, LED1 | LED7,
								LED2 | LED0, LED2 | LED1, LED2 | LED3, LED2 | LED4, LED2 | LED5,
								LED2 | LED6, LED2 | LED7, LED3 | LED0};
*/

	uint32_t seq[MEMORY_DEPTH]={ALL_LEDS, LED0, LED1, LED0 | LED1, LED2, LED2 | LED0, LED2 | LED1, LED2 | LED1 | LED0,
								LED3, LED3 | LED0, LED3 | LED1, LED3 | LED1 | LED0, LED3 | LED2, LED3 | LED2 | LED0, LED3 | LED2 | LED1, LED3 | LED2 | LED1 | LED0,
								LED4, LED4 | LED0, LED4 | LED1, LED4 | LED1 |LED0, LED4 | LED2, LED4 | LED2 | LED0, LED4 | LED2 | LED1, LED4 | LED2 | LED1 | LED0,
								LED4 | LED3, LED4 | LED3 | LED0, LED4 | LED3 | LED1, LED4 | LED3 | LED1 | LED0, LED4 | LED3 | LED2, LED4 | LED3 |LED2| LED0, LED4 | LED3 |LED2| LED1, LED4 | LED3 |LED2| LED1 | LED0};

	uint8_t i=0, addr=0;

	for(i=0; i<MEMORY_DEPTH; i++, addr++) //ITS THE MEMORY STUPID!!!!!!!!!
	{
		LED_Controller_AXI_BUS_mWriteReg(LED_CONTROLLER_AXI_BUS_ADDR, SLV_REG1, ENA | WEA | ((seq[i])<<DINA) | addr );
		usleep(10);
		LED_Controller_AXI_BUS_mWriteReg(LED_CONTROLLER_AXI_BUS_ADDR, SLV_REG1, (ENA | ((seq[i])<<DINA) | addr) & (~WEA) );
		usleep(10);
	}
}
