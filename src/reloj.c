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

/* === Private function declarations =========================================================== */

/* === Private variable definitions ============================================================ */

struct clock_s {
    bool time_is_valid;
    hora_t hora_actual;
    hora_t alarma;
    unsigned int ticks_count;
    unsigned int ticks_per_second;
};

/* === Public variable definition  ============================================================= */

/* === Private function definitions ============================================================ */

/* === Public function implementation ========================================================== */

clock_t RelojCreate(unsigned int ticks_per_second, void * alarm_handler) {
    static struct clock_s instance = {0};

    clock_t clock = &instance;
    clock->time_is_valid = false;
    memset(clock->hora_actual, 0, sizeof(hora_t));

    return clock;

    // clock_t reloj;
    // reloj = (clock_t)malloc(sizeof(struct clock_s));
    // if (reloj) {
    //     reloj->ticks_per_second = ticks_per_second;
    //     RelojGetCurrentTime(reloj, reloj->hora_actual);
    //     // memset(reloj->alarma, alarm_handler, sizeof(hora_t)); ??
    // }
    // printf("alarma %d", alarm_handler);
    // return reloj;
};

bool RelojGetCurrentTime(clock_t clock, hora_t hora_actual) {
    // if (!clock->time_is_valid) {
    //     return false;
    // }
    memcpy(hora_actual, clock->hora_actual, sizeof(hora_t));
    return clock->time_is_valid;
};

bool RelojSetupCurrentTime(clock_t clock, const hora_t nueva_hora) {
    memcpy(clock->hora_actual, nueva_hora, sizeof(hora_t));
    clock->time_is_valid = true;
    return true;
};

void RelojNewTick(clock_t clock) {
    // if (clock->ticks_per_second % 3 == 0) {
    //     if (clock->hora_actual[5] > 9) {
    //         clock->hora_actual[5] = 0;
    //         if (clock->hora_actual[4] > 5) {
    //             clock->hora_actual[4] = 0;
    //             if (clock->hora_actual[3] > 9) {
    //                 clock->hora_actual[3] = 0;
    //                 if (clock->hora_actual[2] > 5) {
    //                     clock->hora_actual[2] = 0;
    //                     if (clock->hora_actual[1] > 9) {
    //                         clock->hora_actual[1] = 0;
    //                         if (clock->hora_actual[0] == 2) {
    //                             if (clock->hora_actual[1] > 3) {
    //                                 clock->hora_actual[0] = 0;
    //                             }
    //                         }
    //                         clock->hora_actual[0]++;
    //                     }
    //                     clock->hora_actual[1]++;
    //                 }
    //                 clock->hora_actual[2]++;
    //             }
    //             clock->hora_actual[3]++;
    //         }
    //         clock->hora_actual[4]++;
    //     }
    //     clock->hora_actual[5]++;
    // }

    clock->hora_actual[5] = 7;
};

// uint8_t RelojGetAlarm(clock_t clock, hora_t alarma) {
//     memset(clock->alarma, alarma, sizeof(hora_t));
//     return clock->alarma;
//     // return false;
// };
/* === End of documentation ==================================================================== */
