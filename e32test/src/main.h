#pragma once

#include "globals.h"

#define BAUD_RATE       115200  // serial debug port baud rate

#ifndef LED_BUILTIN
#define LED_BUILTIN     22 // please check PIN where LED attached
#endif

extern TaskHandle_t hSleep;
void tBlink(void * pvParameters);
