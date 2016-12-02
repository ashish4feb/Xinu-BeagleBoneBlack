#include <gpio.h>
#include <xinu.h>
#include <stddef.h>


/*------------------------------------------------------------------------
 *  lread_fifo  -  Read character(s) from a fifo queue of ADC channels
 *------------------------------------------------------------------------
 */
 devcall lread_fifo()
 {
 	volatile unsigned *adc_stat_addr = (volatile unsigned*)(ADC_STAT);
 	volatile unsigned *fifo_addr = (volatile unsigned*)(FIFO0_ADDR);
	volatile unsigned *fifo_count = (volatile unsigned*)(FIFO_COUNT_ADDR);
	//Taking Count of the fifo queue
	uint32 fcount = *fifo_count & 127;
	uint32 creg4 = 0;
	//check if fifo count is atleast 1
  	if(fcount >= 1)
	{
		while(*adc_stat_addr & 0x00000020);
		creg4=*fifo_addr & 0x00000fff;
	}
	return creg4;
}
