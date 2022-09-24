
// Main headers
#include "EmbUI.h"
#include "uistrings.h"   // non-localized text-strings
#include "main.h"
#include "Fsm.h"

// fsm 
#define FLIP_LIGHT_SWITCH 1

State state_light_on(on_light_on_enter, NULL, &on_light_on_exit);
State state_light_off(on_light_off_enter, NULL, &on_light_off_exit);
Fsm fsm(&state_light_off);

// Transition callback functions
void on_light_on_enter()
{
  Serial.println("Entering LIGHT_ON");
}

void on_light_on_exit()
{
  Serial.println("Exiting LIGHT_ON");
}

void on_light_off_enter()
{
  Serial.println("Entering LIGHT_OFF");
}

void on_light_off_exit()
{
  Serial.println("Exiting LIGHT_OFF");
}

void on_trans_light_on_light_off()
{
  Serial.println("Transitioning from LIGHT_ON to LIGHT_OFF");
}

void on_trans_light_off_light_on()
{
  Serial.println("Transitioning from LIGHT_OFF to LIGHT_ON");
}

/**
 * построение интерфейса осуществляется в файлах 'interface.*'
 *
 */
TaskHandle_t hSleep;
TaskHandle_t hTermostat;
// MAIN Setup
void setup() {
pinMode(GPIO_NUM_15, INPUT_PULLDOWN);

  xTaskCreate(tSleep, "sleep", 1024, NULL, 1, &hSleep);
  xTaskCreate(tTermo, "termo", 1024, NULL, 1, &hTermostat);

  Serial.begin(BAUD_RATE);

  LOG(printf_P, PSTR("\n\nsetup: free heap  : %d\n"), ESP.getFreeHeap());
#ifdef ESP32
  LOG(printf_P, PSTR("setup: free PSRAM  : %d\n"), ESP.getFreePsram()); // 4194252
#endif

  Serial.println("Starting test...");

  pinMode(LED_BUILTIN, OUTPUT); // we are goning to blink this LED

  // Start EmbUI framework
  embui.begin();

  // restore LED state from configuration
//  digitalWrite( LED_BUILTIN, !embui.param(FPSTR(V_LED)).toInt() );
  if(!embui.param(FPSTR(V_LED)).toInt() ){
    if (eTaskGetState(hSleep)== eSuspended)
    {
      vTaskResume(hSleep);
    }else{
    vTaskSuspend(hSleep);
    }
  }

  // fsm transition ini
    fsm.add_transition(&state_light_on, &state_light_off,
                     FLIP_LIGHT_SWITCH,
                     &on_trans_light_on_light_off);
    fsm.add_transition(&state_light_off, &state_light_on,
                     FLIP_LIGHT_SWITCH,
                     &on_trans_light_off_light_on);
}

// MAIN loop
void loop() {
  embui.handle();
}

void tSleep(void * pvParameters){

  for (;;)
  {
  digitalWrite( LED_BUILTIN, HIGH );
  vTaskDelay(500 / portTICK_PERIOD_MS);
  digitalWrite( LED_BUILTIN, LOW );
  vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void tTermo(void * pvParameters){

  for (;;)
  {
  vTaskDelay(100 / portTICK_PERIOD_MS);
  digitalWrite( LED_BUILTIN, HIGH );
  // fsm.trigger(FLIP_LIGHT_SWITCH);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  digitalWrite( LED_BUILTIN, LOW );
  // fsm.trigger(FLIP_LIGHT_SWITCH);
  }
}