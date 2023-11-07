// JOY DEMO

//#define WIFI_MODE_AP
#define WIFI_MODE_STA

// WiFi

#ifdef WIFI_MODE_STA
//#define AP_SSID "Vodafone-6459"
//#define AP_PASS "Ha3EDRgA74AT6F6R"
// #define AP_SSID "IGC"
// #define AP_PASS "Jesus-is-Lord"
#define AP_SSID "dlink"
#define AP_PASS ""
//#define AP_SSID "IGCworship"
//#define AP_PASS "IGCworship32"
#endif

#ifdef WIFI_MODE_AP
#define AP_SSID "GHUB"
#define AP_PASS "GHUB2023"
#endif

#include <Arduino.h>
#include <GyverHub.h>
GyverHub hub("MyDevices", "ESP8266", "");

GHpos pos2;

void build() {
    hub.BeginWidgets();
    hub.WidgetSize(50);

    // первый обработаем в билдере
    GHpos pos1;
    if (hub.Joystick(&pos1)) {
        Serial.println(pos1.x);
        Serial.println(pos1.y);
    }

    // второй в loop
    hub.Joystick(&pos2, 0, 1, F("my joy"), GH_RED);
}

void setup() {
    Serial.begin(115200);

#ifdef GH_ESP_BUILD

#ifdef WIFI_MODE_STA
    WiFi.mode(WIFI_STA);
    WiFi.begin(AP_SSID, AP_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    hub.setupMQTT("test.mosquitto.org", 1883);
#endif
#ifdef WIFI_MODE_AP
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);

#endif
    Serial.println();
    Serial.println(WiFi.localIP());

#endif

    hub.onBuild(build);
    hub.begin();
}

void loop() {
    hub.tick();

    if (pos2.changed()) {
        Serial.println("joy 2:");
        Serial.println(pos2.x);
        Serial.println(pos2.y);
    }
}