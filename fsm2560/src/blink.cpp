#include <Arduino.h>
#include "main.h"
#include "Fsm.h"
#include "blink.h"

// State machine variables
#define FLIP_LIGHT_SWITCH 1

State state_light_on(NULL, NULL, NULL);
State state_light_off(NULL, NULL, NULL);
// State state_light_on(&on_light_on_enter, &on_light_on_run, &on_light_on_exit);
// State state_light_off(&on_light_off_enter, &on_light_off_run, &on_light_off_exit);
Fsm fsm(&state_light_off);

void blink_setup(){
      pinMode(13, OUTPUT);
// transitions
  fsm.add_transition(&state_light_on, &state_light_off, FLIP_LIGHT_SWITCH, &on_trans_light_on_light_off);
  fsm.add_transition(&state_light_off, &state_light_on, FLIP_LIGHT_SWITCH, &on_trans_light_off_light_on);
  fsm.run_machine();
}

void blink_tick(){
  // No "fsm.run_machine()" call needed as no "on_state" funcions or timmed transitions exists
 // fsm.tick();
  fsm.trigger(FLIP_LIGHT_SWITCH);
}

// Transition callback functions
void on_light_on_enter()
{
  Serial.println("Entering LIGHT_ON");
}

void on_light_on_exit()
{
  Serial.println("exiting light_on");
}
void on_light_on_run()
{
  Serial.println("RUN LIGHT_ON");
}

void on_light_off_enter()
{
  Serial.println("Entering LIGHT_OFF");
}

void on_light_off_exit()
{
  Serial.println("Exiting LIGHT_OFF");
}
void on_light_off_run()
{
  Serial.println("RUN LIGHT_OFF");
}

void on_trans_light_on_light_off()
{
  Serial.println("LIGHT_ON to LIGHT_OFF");
}

void on_trans_light_off_light_on()
{
  Serial.println("LIGHT_OFF to LIGHT_ON");
}
