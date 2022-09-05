#pragma once

// Set of flash-strings that might be reused multiple times within the code

// General
  static const char T_HEADLINE[] PROGMEM = "Korshun 16";    // имя проекта

// Our variable names
static const char V_BLINK_LED[] PROGMEM = "vBlinkLED";
static const char V_LED[] PROGMEM = "vLED";
static const char V_VAR1[] PROGMEM = "v1";
static const char V_VAR2[] PROGMEM = "v2";
static const char V_UPDRATE[] PROGMEM = "updrt";    // update rate
static const char V_UPDVOL[] PROGMEM = "updvolume";    // update volume
static const char V_UPDVOICE[] PROGMEM = "updvoice";    // update voice
static const char V_UPDTIMER[] PROGMEM = "updtimer";    // update voice

// UI blocks
static const char T_DEMO[] PROGMEM = "dem";     // генерация UI-секции "демо"
static const char T_MIUI[] PROGMEM = "miui";     //M генерация UI-секции "korshun"

// UI handlers
static const char T_SET_DEMO[] PROGMEM = "do_demo";     // обработка данных из секции "демо"
static const char T_SET_MIUI[] PROGMEM = "do_miui";     // обработка данных из секции "демо"
static const char T_SET_MORE[] PROGMEM = "do_more";
