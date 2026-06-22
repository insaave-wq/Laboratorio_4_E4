/*********************************************************************************************************************
Copyright 2026
Facultad de Ciencias Exactas y Tecnología
Universidad Nacional de Tucuman
http://www.microprocesadores.unt.edu.ar/

Copyright 2026, Ignacio Nicolás Saavedra <insaave@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @file reloj.c
 ** @brief Implementación del reloj
 **/

/* === Headers files inclusions ================================================================ */

#include "reloj.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */
typedef void (*alarm_handler_t)(void);
/* === Private function declarations =========================================================== */

bool TimeIsValid(hora_t hora);

/* === Private variable definitions ============================================================ */

struct clock_s {
    hora_t hora_actual;
    bool time_is_valid;
    hora_t alarma;
    bool alarm_enabled;
    uint32_t ticks_count;
    uint32_t ticks_per_second;
    alarm_handler_t alarm_handler;
};

/* === Public variable definition  ============================================================= */

/* === Private function definitions ============================================================ */

/* === Public function implementation ========================================================== */

bool TimeIsValid(hora_t hora) {
    if (hora[0] > 2)
        return false;
    if (hora[1] > 3)
        return false;
    if (hora[2] > 5)
        return false;
    if (hora[3] > 9)
        return false;
    if (hora[4] > 5)
        return false;
    if (hora[5] > 9)
        return false;
    return true;
}

clock_t RelojCreate(uint32_t ticks_per_second, void * alarm_handler) {
    static struct clock_s instance = {0};

    clock_t clock = &instance;
    clock->time_is_valid = false;
    clock->alarm_enabled = false;
    clock->alarm_status = false;
    clock->ticks_per_second = ticks_per_second;
    clock->ticks_count = 0;
    clock->alarm_handler = alarm_handler;
    memset(clock->hora_actual, 0, sizeof(hora_t));
    memset(clock->alarma, 0, sizeof(hora_t));

    return clock;
}

bool RelojGetCurrentTime(clock_t clock, hora_t hora_actual) {
    memcpy(hora_actual, clock->hora_actual, sizeof(hora_t));
    return clock->time_is_valid;
}

bool RelojSetupCurrentTime(clock_t clock, const hora_t nueva_hora) {
    if (TimeIsValid(nueva_hora)) {
        memcpy(clock->hora_actual, nueva_hora, sizeof(hora_t));
        clock->time_is_valid = true;
    } else {
        return false;
    }
    return clock->time_is_valid;
}

void RelojNewTick(clock_t clock) {
    clock->ticks_count = clock->ticks_count + 1;
    if (clock->ticks_count >= clock->ticks_per_second) {

        uint32_t segundos = clock->hora_actual[0] * 3600 * 10 + clock->hora_actual[1] * 3600 +
                            clock->hora_actual[2] * 60 * 10 + clock->hora_actual[3] * 60 + clock->hora_actual[4] * 10 +
                            clock->hora_actual[5];
        segundos = segundos + 1;
        clock->ticks_count = 0;

        clock->hora_actual[0] = (segundos / 3600 % 24) / 10;
        clock->hora_actual[1] = (segundos / 3600 % 24) % 10;

        clock->hora_actual[2] = (segundos / 60 % 60) / 10;
        clock->hora_actual[3] = (segundos / 60 % 60) % 10;

        clock->hora_actual[4] = (segundos % 60) / 10;
        clock->hora_actual[5] = (segundos % 60) % 10;
    }
    if (memcmp(clock->hora_actual,clock->alarma,sizeof(hora_t))==0) {
        clock->alarm_handler();
    }
}

bool RelojGetAlarm(clock_t clock, hora_t alarma) {
    if (clock->alarm_enabled) {
        memcpy(alarma, clock->alarma, sizeof(hora_t));
    }
    return clock->alarm_enabled;
}

bool RelojSetupAlarm(clock_t clock, hora_t alarma) {
    if (TimeIsValid(alarma)) {
        memcpy(clock->alarma, alarma, sizeof(hora_t));
        clock->alarm_enabled = true;
    }
    return clock->alarm_enabled;
}

void RelojTogleAlarm(clock_t clock) {
    clock->alarm_enabled = !clock->alarm_enabled;
}

/* === End of documentation ==================================================================== */
