#pragma once

void block_menu(Interface *interf, JsonObject *data);
void block_demopage(Interface *interf, JsonObject *data);
void block_mipage(Interface *interf, JsonObject *data);
void action_demopage(Interface *interf, JsonObject *data);
void action_mipage(Interface *interf, JsonObject *data);
void action_blink(Interface *interf, JsonObject *data);
void pubCallback(Interface *interf);
void setRate(Interface *interf, JsonObject *data);
void setVolume(Interface *interf, JsonObject *data);
void setVoice(Interface *interf, JsonObject *data);
void setTimer(Interface *interf, JsonObject *data);
void sensorPublisher();
void action_miblink(Interface *interf, JsonObject *data);
void blinker();

//void remote_action(RA action, ...);
//uint8_t uploadProgress(size_t len, size_t total);
