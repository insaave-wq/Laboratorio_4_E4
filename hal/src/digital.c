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

/** @file digital.c
 ** @brief Implementación de funciones para el manejo de entradas y salidas
 * digitales
 **/

/* === Headers files inclusions
 * ================================================================ */

#include "digital.h"
#include "chip.h"
#include <stdlib.h>

/* === Macros definitions
 * ====================================================================== */

/* === Private data type declarations
 * ========================================================== */
struct digital_input_s {
    uint32_t port;
    uint8_t pin;
    bool inverted;
    bool last_state;
};

struct digital_output_s {
    uint32_t port;
    uint8_t pin;
    bool inverted;
};
/* === Private function declarations
   =========================================================== */

/* === Private variable definitions
   ============================================================ */

/* === Public variable definition
   ============================================================= */

/* === Private function definitions
   ============================================================ */

bool DigitalInputGetState(digital_input_t input) {
    bool state = Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, input->port, input->pin) == 0;
    return input->inverted ? !state : state;
};

digital_input_t DigitalInputCreate(uint32_t port, uint8_t pin, bool inverted) {
    digital_input_t self;
    self = (digital_input_t)malloc(sizeof(struct digital_input_s));
    if (self != NULL) {
        self->port = port;
        self->pin = pin;
        self->inverted = inverted;
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, port, pin, false);
        self->last_state = DigitalInputGetState(self);
    }
    return self;
};

bool DigitalInputHasChanged(digital_input_t input) {
    bool resultado = DigitalInputGetState(input) != input->last_state;
    input->last_state = DigitalInputGetState(input);
    return resultado;
};

bool DigitalInputHasActivated(digital_input_t input) {
    bool current_state = DigitalInputGetState(input);
    return DigitalInputHasChanged(input) && current_state == true;
};

bool DigitalInputHasDeactivated(digital_input_t input) {
    bool current_state = DigitalInputGetState(input);
    return DigitalInputHasChanged(input) && current_state == false;
};

digital_output_t DigitalOutputCreate(uint32_t port, uint8_t pin, bool inverted) {
    digital_output_t self;
    self = (digital_output_t)malloc(sizeof(struct digital_output_s));
    if (self != NULL) {
        self->port = port;
        self->pin = pin;
        self->inverted = inverted;
        DigitalOutputDeactivate(self);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, port, pin, true);
    }
    return self;
};

void DigitalOutputActivate(digital_output_t output) {
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, !output->inverted);
};

void DigitalOutputDeactivate(digital_output_t output) {
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, output->inverted);
};

void DigitalOutputToggle(digital_output_t output) {
    if (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, output->port, output->pin) == 0) {
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, true);
    } else {
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, false);
    }
};

/* === Public function implementation
 * ========================================================== */

/* === End of documentation
 * ==================================================================== */
