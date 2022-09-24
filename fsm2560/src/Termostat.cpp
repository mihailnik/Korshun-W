#include "Fsm.h"
#include "Termostat.h"

// Out pins
const uint8_t LED_ALARM_PIN = 13;
const uint8_t HEATER_PIN = 12;
const uint8_t COOLER_PIN = 14;
const uint8_t LOAD_PIN = 15; // load disabled in VHot,VCold states

// events temp changes
const uint8_t EV_VHot = 1;
const uint8_t EV_Hot = 2;
const uint8_t EV_MHot = 3;
const uint8_t EV_MCold = 4;
const uint8_t EV_Cold = 5;
const uint8_t EV_VCold = 6;

// Temperatures set
const int16_t T_VHot = 40;
const int16_t T_Hot = 30;
const int16_t T_Mid = 25;
const int16_t T_Cold = 10;
const int16_t T_VCold = 5;

const uint8_t T_UP = 1; // temp up
const uint8_t T_DOWN = 0;

int term_trigger = 0;
float Temperature = 0;
uint8_t Term_Vector = T_UP;

State state_term_VHot(&VHot_enter, &VHot_tick, &VHot_exit);
State state_term_Hot(&Hot_enter, &Hot_tick, &Hot_exit);
State state_term_MHot(&MHot_enter, &MHot_tick, &MHot_exit);
State state_term_MCold(&MCold_enter, &MCold_tick, &MCold_exit);
State state_term_Cold(&Cold_enter, &Cold_tick, &Cold_exit);
State state_term_VCold(&VCold_enter, &VCold_tick, &VCold_exit);
Fsm term(&state_term_VHot);

void Termostat_setup()
{
    // transitions
    
    term.add_transition(&state_term_Hot, &state_term_VHot, EV_VHot, &trans_Hot_VHot);
    term.add_transition(&state_term_VHot, &state_term_Hot, EV_Hot, &trans_VHot_Hot);
    term.add_transition(&state_term_MHot, &state_term_Hot, EV_Hot, &trans_MHot_Hot);
    term.add_transition(&state_term_Hot, &state_term_MHot, EV_MHot, &trans_Hot_MHot);
    term.add_transition(&state_term_MCold, &state_term_MHot, EV_MHot, &trans_MCold_MHot);
    term.add_transition(&state_term_MHot, &state_term_MCold, EV_MCold, &trans_MHot_MCold);
    term.add_transition(&state_term_Cold, &state_term_MCold, EV_MCold, &trans_Cold_MCold);
    term.add_transition(&state_term_MCold, &state_term_Cold, EV_Cold, &trans_MCold_Cold);
    term.add_transition(&state_term_VCold, &state_term_Cold, EV_Cold, &trans_VCold_Cold);
    term.add_transition(&state_term_Cold, &state_term_VCold, EV_VCold, &trans_Cold_VCold);
    term.run_machine();
}

void Termostat_tick()
{
    term.tick();
    if (term_trigger)
    {
        term.trigger(term_trigger);
        term_trigger = 0;
    }
}

void Termostat_setTerm(float term)
{
    Temperature = term;
}

float Termostat_getTerm()
{
    return Temperature;
}

// state transition
void trans_Hot_VHot()
{
    Serial.print("VHot: ");
    Serial.println(Temperature);
}
void trans_VHot_Hot()
{
    Serial.print("Hot: ");
    Serial.println(Temperature);
}
void trans_MHot_Hot()
{
    Serial.print("Hot: ");
    Serial.println(Temperature);
}
void trans_Hot_MHot()
{
    Serial.print("MHot: ");
    Serial.println(Temperature);
}
void trans_MHot_MCold()
{
    Serial.print("MCold: ");
    Serial.println(Temperature);
}
void trans_MCold_MHot()
{
    Serial.print("MHot: ");
    Serial.println(Temperature);
}
void trans_Cold_MCold()
{
    Serial.print("MCold: ");
    Serial.println(Temperature);
}
void trans_MCold_Cold()
{
    Serial.print("Cold: ");
    Serial.println(Temperature);
}
void trans_Cold_VCold()
{
    Serial.print("VCold: ");
    Serial.println(Temperature);
}
void trans_VCold_Cold()
{
    Serial.print("Cold: ");
    Serial.println(Temperature);
}

// states functions: in, out, run
void VHot_enter() {}
void VHot_tick()
{
    if (Temperature < T_VHot)
    {
        term_trigger = EV_Hot;
    }
}
void VHot_exit() {}
void Hot_enter() {}
void Hot_tick()
{
    if (Temperature > T_VHot)
    {
        term_trigger = EV_VHot;
    }
    else if (Temperature < T_Hot)
    {
        term_trigger = EV_MHot;
    }
}
void Hot_exit() {}
void MHot_enter() {}
void MHot_tick()
{
    if (Temperature > T_Hot)
    {
        term_trigger = EV_Hot;
    }
    else if (Temperature < T_Mid)
    {
        term_trigger = EV_MCold;
    }
}
void MHot_exit() {}
void MCold_enter() {}
void MCold_tick()
{
    if (Temperature > T_Mid)
    {
        term_trigger = EV_MHot;
    }
    else if (Temperature < T_Cold)
    {
        term_trigger = EV_Cold;
    }
}
void MCold_exit() {}
void Cold_enter() {}
void Cold_tick()
{
    if (Temperature > T_Cold)
    {
        term_trigger = EV_MCold;
    }
    else if (Temperature < T_VCold)
    {
        term_trigger = EV_VCold;
    }
}
void Cold_exit() {}
void VCold_enter() {}
void VCold_tick()
{
    if (Temperature > T_VCold)
    {
        term_trigger = EV_Cold;
    }
}
void VCold_exit() {}