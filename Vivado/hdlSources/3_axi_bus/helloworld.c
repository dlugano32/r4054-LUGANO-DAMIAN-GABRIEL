/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

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

#define ALL_LEDS 0xFF

Xuint32 * LED_CONTROLLER_AXI_BUS_ADDR = (Xuint32 *) XPAR_AXI_COMM_BUS_0_BASEADDR;

// Macro, reemplaza esto en la funcion Xil_Out32

#define LED_Controller_AXI_BUS_mWriteReg(BaseAddress, RegOffset, Data) \
	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

// Macro, reemplaza esto en la funcion Xil_In32

#define LED_Controller_AXI_BUS_mReadReg(BaseAddress, RegOffset) \
	Xil_In32((BaseAddress) + (RegOffset))

int main()
{
    init_platform();

    print("Hello World\n\r");

    while(1)
    {
    	sleep(1);
    	LED_Controller_AXI_BUS_mWriteReg(LED_CONTROLLER_AXI_BUS_ADDR, SLV_REG0, ALL_LEDS);
    }

    cleanup_platform();
    return 0;
}
