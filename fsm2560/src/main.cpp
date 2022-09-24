#include <Arduino.h>
#include "main.h"
#include "Fsm.h"
#include "Termostat.h"
#include "blink.h"

// standard arduino functions
void setup()
{
  Serial.begin(9600);

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

