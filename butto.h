#ifndef _BUTTON_H_
#define _BUTTON_H_
int buttonInit(void);
int buttonExit(void);

#define MESSAGE_ID 1122
typedef struct
{
	long int messageNum;
	int keyInput;
	int pressed;
} BUTTON_MSG_T;

#endif _BUTTON_H_
