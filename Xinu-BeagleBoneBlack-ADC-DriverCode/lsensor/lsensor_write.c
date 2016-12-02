#include <gpio.h>
#include <xinu.h>
#include <stddef.h>


/*--------------------------------------------
 *  lsensor_write  -  Set output to a GPIO PIN
 *--------------------------------------------
 */
 
 devcall lsensor_write(uint32 chip,uint32 led,char* data)
 {
 	volatile unsigned *gpio_addr = NULL;
 	volatile unsigned *gpio_oe_addr = NULL;
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
 	
 	uint32 USR_LED=1<<led;
 	*(gpio_addr + GPIO_OE) = *(gpio_addr + GPIO_OE) & ~(USR_LED);
 	//Set up the data to write
 	if (strncmp(data, "on", 2) == 0)
	{
		*(gpio_addr + GPIO_OUT) = *(gpio_addr + GPIO_OUT) | USR_LED;
	}
	else if (strncmp(data, "off", 3) == 0)
	{
		*(gpio_addr + GPIO_OUT) = *(gpio_addr + GPIO_OUT) & (~USR_LED);
	}
	else
	{
		kprintf("Wrong data");
	}
	return OK;
}
