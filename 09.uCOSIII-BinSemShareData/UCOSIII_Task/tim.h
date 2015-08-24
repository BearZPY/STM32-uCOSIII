#ifndef _MY_TIME_H
#define _MY_TIME_H


#include "includes.h"
#include "task.h"


extern OS_TMR tmr1;
extern OS_TMR tmr2;


void tmr1_callback(void *p_tmr,void *p_arg);
void tmr2_callback(void *p_tmr,void *p_arg);

#endif
