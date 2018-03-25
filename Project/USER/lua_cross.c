#include "time.h"
#include "stm32f10x.h"

time_t time(time_t * time) {  
    return 0;  
}  
  
void exit(int status)  {
	(void)status;
}  
  
int system(const char * string) {  
    return 0;  
}