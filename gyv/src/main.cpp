#include <Arduino.h>
// #define WIFI_AP_MODE 1
#define WIFI_STA_MODE 1
#define LED 22
TaskHandle_t blink;

// пример использования "блоков" для оформления
// данные храним, но никак не используем, это просто пример

#define AP_SSID "Kozaki_WiFi" //
#define AP_PASS "0676181665"  //

#include <GyverPortal.h>
GyverPortal portal;


  int Volume = 10;
  char cTimer[7] = "";
  char cVoice[7] = "";
  char cLight[7] = "";
  bool state;


struct SomeData {
  char ssid[32] = "";
  char pass[32] = "";
  char host[32] = "broker.mqttdashboard.com";
  uint32_t port = 1883;
  bool state;
};

SomeData data;

void build() {
  BUILD_BEGIN();
  GP.THEME(GP_DARK);
  GP.AJAX_UPDATE("lbl_vol_val");

  GP.LABEL("Settings");
  GP.BLOCK_BEGIN();
  GP.LABEL("Power:");
  GP.SWITCH("sw", data.state);
  GP.BREAK();
  GP.LABEL("Local status:");
  GP.LABEL("OK");
  GP.BLOCK_END();

  GP.BLOCK_BEGIN();
  GP.LABEL("Volume: ");
  GP.LABEL("NAN", "lbl_vol_val");
  GP.BREAK();
  GP.SLIDER("sld_vol", Volume, 0, 16, 1);
  GP.BLOCK_END();

  BUILD_END();
}

void action(){
    if (portal.click("sld_vol")) {
      Volume = portal.getInt("sld_vol");
      }
    if(portal.update("lbl_vol_val")){
      portal.answer(Volume);
      Serial.println(Volume);
    }
}

void setup() {
#ifdef WIFI_STA_MODE
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(AP_SSID, AP_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
#endif
#ifdef WIFI_AP_MODE
WiFi.mode(WIFI_AP);
WiFi.softAP("Korshun_16w","12345678"); // password cannot be shorter than 8 characters
#endif


  portal.attachBuild(build);
  portal.attach(action);
  portal.start();
}

void loop() {
  portal.tick();
}