#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_FREQUENCY_NAME "frequency"
#define BUZZER_ENABLE_NAME "enable"
char gBuzzerBaseSysDir[128];

int buzzerInit(void){
        DIR*dir_info = opendir(BUZZER_BASE_SYS_PATH);
        int ifNotFound =1;
        if (dir_info != NULL){
                while(1){
                        struct dirent *dir_entry;
                        dir_entry = readdir(dir_info);
                        if(dir_entry == NULL)break;
                        if(strncasecmp(BUZZER_FILENAME, dir_entry ->d_name, strlen(BUZZER_FILENAME))==0){ifNotFound =0;
sprintf(gBuzzerBaseSysDir,"%s%s/",BUZZER_BASE_SYS_PATH,dir_entry->d_name);
                        }
                }
        }
        printf("find %s\n",gBuzzerBaseSysDir);
        return ifNotFound;
}
int buzzerEnable(int bEnable)
{
        char path[200];
        sprintf(path, "%s%s",gBuzzerBaseSysDir,BUZZER_ENABLE_NAME);
        int fd =open(path,O_WRONLY);
        if(bEnable) write(fd,&"1",1);
        else       write(fd, &"0",1);
        close(fd);
}
const int scale[MAX_SCALE_STEP]={262,294,330,349,392,440,494,523};
void setFrequency(int frequency)
{
        char path[200];
        sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
        int fd=open(path,O_WRONLY);
        dprintf(fd,"%d",frequency);
        close(fd);
}
void buzzerOn(int a)
{
        setFrequency(scale[a]);
        buzzerEnable(1);
}

/ㅇㅇ/
