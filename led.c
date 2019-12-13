#include "led.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 
unsigned int ledValue = 0; 
int fd = 0; 
int ledOnOff (int ledNum, int ledOn) 
{ 
int i=1; 
i=i<<ledNum; 
ledValue = ledValue& (~i); 
if (ledOn !=0) ledValue |= i; 
printf ("LEDNUm:%d, ledOn;%d, value:%d\r\n",ledNum, ledOn, ledValue);
write (fd, &ledValue, 4); 
} 
int ledLibInit(void) 
{ 
fd=open("/dev/periled",O_WRONLY); 
ledValue = 0; 
}
int ledLibExit(void)
{
ledValue =0;
ledOnOff (0,0);
close(fd);
}
