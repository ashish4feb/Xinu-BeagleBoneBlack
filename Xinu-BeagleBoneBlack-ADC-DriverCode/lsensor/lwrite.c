#include <xinu.h> 
devcall lwrite(uint32 id, char* data) { 
	switch(id) { 
		case 0: lsensor_write(1, 21, data); 
				break; 
	} 
	return OK; 
}