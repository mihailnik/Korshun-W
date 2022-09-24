#pragma once

#include "globals.h"

#define BAUD_RATE       115200  // serial debug port baud rate

#ifndef LED_BUILTIN
#define LED_BUILTIN     22 // please check PIN where LED attached
#endif

extern TaskHandle_t hSleep;
void tSleep(void * pvParameters);
extern TaskHandle_t hTermostat;
void tTermo(void * pvParameters);
// Transition callback functions
void on_light_on_enter();
void on_light_on_exit();
void on_light_off_enter();
void on_light_off_exit();
void on_trans_light_on_light_off();
void on_trans_light_off_light_on();