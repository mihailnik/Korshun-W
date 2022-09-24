#pragma once

#include <Arduino.h>
#include "Fsm.h"

    // state transition
    void trans_VHot_Hot();
    void trans_Hot_VHot();
    void trans_MHot_Hot();
    void trans_Hot_MHot();
    void trans_MHot_MCold();
    void trans_MCold_MHot();
    void trans_Cold_MCold();
    void trans_MCold_Cold();
    void trans_Cold_VCold();
    void trans_VCold_Cold();

    // states functions: in, out, run
    void VHot_enter();
    void VHot_tick();
    void VHot_exit();
    void Hot_enter();
    void Hot_tick();
    void Hot_exit();
    void MHot_enter();
    void MHot_tick();
    void MHot_exit();
    void MCold_enter();
    void MCold_tick();
    void MCold_exit();
    void Cold_enter();
    void Cold_tick();
    void Cold_exit();
    void VCold_enter();
    void VCold_tick();
    void VCold_exit();

    void Termostat_setup();
    void Termostat_tick();
    void Termostat_setTerm(float term);
    float Termostat_getTerm(void);




