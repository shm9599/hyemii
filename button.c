#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <sys/ipc.h>
#include <pthread.h>

#include "button.h"

#define INPUT_DEVICE_LIST "/dev/input/event"
#define HAVE_TO_FIND_1 "n:NAME=/ "ecube-button\"|n"
static int fd;
static int msgID=0;
static pthread_t buttonTh_id;
static void buttonThFunc(void* arg );

static void buttonThFunc(void* arg)
{    
	BUTTON_MSG_T msgTx;
	msgTx.messageNum = 1;
	struct input_event stEvent;
	while (1)
	{
		read(fd, &stEvent, sizeof (stEvent));
		
		if ( ( stEvent.type == EV_KEY) &&(stEvent.value==0))
		{
			msgTx.keyInput = stEvent.code;
			
			msgsnd(msgID, &msgTx, sizeof(int), 0);
		}
    }
}

#define BUTTON_DRIVE_NAME "dev/peributton"

int buttonInit(void)
{
	fd=open (BUTTON_DRIVE_NAME, O_RDONLY);
	msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
	pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
	
}

int buttonExit(void)
{
	pthread_cancel(buttonTh_id);
	close(fd);
}


