#include <stdlib.h>
#include <fcntl.h>
#define MAX_FND_NUM 6
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)



typedef struct FNDWriteDataForm_tag
{

char DataNumeric[FND_DATA_BUFF_LEN];
char DataDot[FND_DATA_BUFF_LEN];
char DataValid[FND_DATA_BUFF_LEN];
}stFndWriteForm,*pStFndWriteform;

#define FND_DRIVER_NAME "/dev/perifnd"

int fndDisp(int num, int dotflag)
{
int fd;
int temp,i;
stFndWriteForm stWriteData;
for(i = 0; i <MAX_FND_NUM; i++)
{
stWriteData.DataDot[i] = (dotflag & (0x1 << i)) ? 1 : 0;
stWriteData.DataValid[i] = 1;
}


temp = num % 1000000; stWriteData.DataNumeric[0]= temp /100000;
temp = num % 100000; stWriteData.DataNumeric[1]= temp /10000;
temp = num % 10000; stWriteData.DataNumeric[2]= temp /1000;
temp = num % 1000; stWriteData.DataNumeric[3]= temp /100;
temp = num % 100; stWriteData.DataNumeric[4]= temp /10;
stWriteData.DataNumeric[5] = num % 10;

fd = open(FND_DRIVER_NAME, O_RDWR);
if(fd<0)
{
perror("driver open error.\n");
return 0;
}
write(fd, &stWriteData, sizeof(stFndWriteForm));
close(fd);
return 1;
}
