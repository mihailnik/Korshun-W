
// Main headers
#include "EmbUI.h"
#include "uistrings.h"   // non-localized text-strings
#include "main.h"

/**
 * построение интерфейса осуществляется в файлах 'interface.*'
 *
 */
TaskHandle_t hSleep;
// MAIN Setup
void setup() {
pinMode(GPIO_NUM_15, INPUT_PULLDOWN);

  xTaskCreate(tSleep, "blink", 1024, NULL, 1, &hSleep);

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