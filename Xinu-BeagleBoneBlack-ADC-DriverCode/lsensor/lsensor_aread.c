/* Author Ashish Katiyar. */

#include <gpio.h>
#include <xinu.h>
#include <stddef.h>


/*--------------------------------------------------------
 *  lsensor_aread  -  Read analog readings from a ADC pin
 *--------------------------------------------------------
 */
 
 devcall lsensor_aread(uint32 pin)
 {
 	volatile unsigned *tmr_addr = (volatile unsigned*)(TMR4_ADDR);
	volatile unsigned *adc_evnt_addr = (volatile unsigned*)(ADC_EVT_CAP_ADDR);
	volatile unsigned *step_con = (volatile unsigned*)(STEP_CONF_ADDR);
	volatile unsigned *step_del = (volatile unsigned*)(STEP_DELAY_ADDR);
	volatile unsigned *step_en = (volatile unsigned*)(STEP_ENABLE_ADDR);
	volatile unsigned *cntrl_addr = (volatile unsigned*)(CNTRL_ADDR);
	volatile unsigned *clk_mdl = (volatile unsigned*)(CLK_MDL);
	volatile unsigned *clk_mdl_t4 = (volatile unsigned*)(CLK_MDL_T4);
	volatile unsigned *adc_stat_addr = (volatile unsigned*)(ADC_STAT);
	
	//Setting up Clock Module
 	*(clk_mdl) &= 0xFFFFFFF0;
	*(clk_mdl) |= 0x2;
	
	//Synchronizing up the timer
	*(clk_mdl_t4) &= 0xFFFFFFF0;
	*(clk_mdl_t4) |= 0x2;
	sleep(1);
	
	//Setting up Control Register
	uint32 creg2 = *(cntrl_addr);
	creg2 |= 5;
	creg2 &= ~(1<<9);
	*(cntrl_addr) = creg2;
	
	//Set up step enable register with the required offset
	*(step_en) = STEP_EN_1;
	
	//Set up step config register with the required configuration and pin pased
	*(step_con ) &= 0xFF87FFFF;
	*(step_con ) |= (pin<<19);
	*(step_con ) &= ~(CON_FIFO0);
	*(step_con ) = *(step_con ) >>2;
	*(step_con ) = *(step_con ) <<2;
	*(step_con ) |= 0;
	
	//Set up step delay
	*(step_del) &= (0x00003F00);
	
	//Enable ADC
	uint32 creg = *adc_evnt_addr;
	creg = creg>>4;
	creg = creg<<4;
	creg = creg | 1;
	*adc_evnt_addr = creg;
	
	
	uint32 creg1 = *tmr_addr;
	creg1 = creg1>>7;
	creg1 = creg1<<7;
	creg1 = creg1 | 18;
	*tmr_addr = creg1;
	
	//Call lread_fifo for recieving the data 
	uint32 creg3 = 0;
	creg3 = lread_fifo();
	return creg3;
 }
