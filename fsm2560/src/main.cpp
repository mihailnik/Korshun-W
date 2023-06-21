#include <Arduino.h>
#include "main.h"
#include "Fsm.h"
#include "Termostat.h"
#include "blink.h"
#include "blink.h"
#include <Arduino_FreeRTOS.h>
#include "task.h"
#include "queue.h"

TaskHandle_t hSleep;
// перевірка 2
// standard arduino functions
void setup()
{
  Serial.begin(9600);
  xTaskCreate(tSleep, "sleep", 1024, NULL, 1, &hSleep);

  Termostat_setup();
  blink_setup();

  Serial.println("serial");
}

void loop()
{
  static float temp = 0; 
  static uint8_t t_vector = 0; 
// changing temp up-down 0-45C
  if (t_vector == 0)
  {
    temp --;
  }else if (t_vector == 1)
  {
    temp ++;
  }
  if (temp < 0)
  {
    t_vector = 1;
  }else if (temp > 45)
  {
    t_vector = 0;
  }
  
  temp += 0.3;
  Termostat_setTerm(temp);

  Termostat_tick();
  // Serial.println(temp);

  delay(500);
  blink_tick();
  delay(500);
}

void tSleep(void * pvParameters){

  for (;;)
  {
  digitalWrite( LED_BUILTIN, HIGH );
  vTaskDelay(500);
  digitalWrite( LED_BUILTIN, LOW );
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}