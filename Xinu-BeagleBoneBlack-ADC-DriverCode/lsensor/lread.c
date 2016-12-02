#include <xinu.h>
devcall lread(uint32 id) { 
	uint32 data; 
	uint32 lux; 
	switch(id) { 
		case 0: data = lsensor_read(1, 28); 
				break; 
		case 1: data = lsensor_aread(1); 
				lux = 1137500.0 / (4095 - data); 
				data = lux; 
				break; 
	} 
	return data; 
}