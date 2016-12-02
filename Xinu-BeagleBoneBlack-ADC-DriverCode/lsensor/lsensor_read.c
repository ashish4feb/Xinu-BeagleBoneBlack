#include <gpio.h>
#include <xinu.h>
#include <stddef.h>


/*------------------------------------------------------------------------
 *  lsensor_read  -  Read character(s) from a light sensor device
 *------------------------------------------------------------------------
 */
 
 devcall lsensor_read(uint32 chip,uint32 pin)
 {
 	volatile unsigned *gpio_addr = NULL;
 	//Check for the GPIO chip to which the device is connected
 	if(chip==0)
 	{
 		gpio_addr = (volatile unsigned*)GPIO0_START_ADDR;
 	}
 	else if(chip==1)
 	{
 		gpio_addr = (volatile unsigned*)GPIO1_START_ADDR;
 	}
 	else if(chip==2)
 	{
 		gpio_addr = (volatile unsigned*)GPIO2_START_ADDR;
 	}
 	else if(chip==3)
 	{
 		gpio_addr = (volatile unsigned*)GPIO3_START_ADDR;
 	}
 	else
 	{
 		kprintf("Wrong Chip No. Selected");
 		return SYSERR;
 	}

	//Check if the output enable is on or off
 	if(((*(gpio_addr+GPIO_OE)&(1<<pin))>>pin)==0)
 	{
 		*(gpio_addr + GPIO_OE) = *(gpio_addr + GPIO_OE) | (1<<pin);
 	}
	
	//Set the output to a readable binary format 
 	uint32 creg=*(gpio_addr + GPIO_IN)&(1<<pin);
 	creg = creg>>pin;
 	return creg;
 }
