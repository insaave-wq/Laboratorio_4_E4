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

#ifndef DIGITAL_H_
#define DIGITAL_H_

/** @file digital.h
 ** @brief Plantilla para la creacion de entradas y salidas digitales
 **/

/* === Headers files inclusions ====================================================================================*/

#include <stdint.h>
#include <stdbool.h>

/* === Header for C++ compatibility
 * ================================================================================
 */
#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions
 * ===================================================================================
 */

/* === Public data type declarations
 * ===============================================================================
 */

/**
 * @brief Delaración de estructura de salida digital
 *
 */
typedef struct digital_output_s * digital_output_t;

/**
 * @brief Declaración de estructura de una entrada digital
 *
 */
typedef struct digital_input_s * digital_input_t;

/* === Public variable declarations
 * ================================================================================
 */

/* === Public function declarations
 * ================================================================================
 */

/**
 * @brief Función para crear una entrada digital
 *
 * @param port puerto de entrada que se desea utilizar
 * @param pin pin de entrada que se desea utilizar
 * @param inverted modo de funcionamiento negado o directo de la entrada
 * @param last_state último estado del puerto de entrada
 * @return digital_input_t
 */
digital_input_t DigitalInputCreate(uint32_t port, uint8_t pin, bool inverted);

/**
 * @brief Función que detecta un cambio en una entrada
 *
 * @param input Estructura de la entrada
 * @return true Cuando hubo un cambio en la entrada digital,
 * @return false Cuando no hubo un cambio en la entrada digital
 */
bool DigitalInputHasChanged(digital_input_t input);

/**
 * @brief Función que detecta que una entrada digital se activó
 *
 * @param input Estructura de la entrada digital
 * @return true Cuando la entrada digital se activó,
 * @return false Cuando la entrada digital no se activó
 */
bool DigitalInputHasActivated(digital_input_t input);

/**
 * @brief Función que detecta que una entrada digital se desactivó
 *
 * @param input Estructura de la entrada digital
 * @return true Cuando la entrada digital se desactivó,
 * @return false Cuando la entrada digital no se desactivó
 */
bool DigitalInputHasDeactivated(digital_input_t input);

/**
 * @brief Función que lee el estatdo de la entrada digital
 *
 * @param input Estructura de la entrada digital
 * @return true Cuando la entrada digital está en estado alto,
 * @return false Cuando la entrada digital está en estado bajo
 */
bool DigitalInputGetState(digital_input_t input);

/**
 * @brief Función para crear una salida digital
 *
 * @param port Puerto de la salida digital que se desea utilizar
 * @param pin Pin de la salida digital que se desea utilizar
 * @param inverted "true" para salida invertida, "false" para salida no invertida
 * @return digital_output_t
 */
digital_output_t DigitalOutputCreate(uint32_t port, uint8_t pin, bool inverted);

/**
 * @brief Función que activa una salida digital
 *
 * @param output Estructura de la salida digital
 */
void DigitalOutputActivate(digital_output_t output);

/**
 * @brief Función que desactiva una salida digital
 *
 * @param output Estructura de la salida digital
 */
void DigitalOutputDeactivate(digital_output_t output);

/**
 * @brief Función que cambia de estado una salida digital
 *
 * @param output Estructura de la salida digital
 */
void DigitalOutputToggle(digital_output_t output);

/* === End of conditional blocks
 * ===================================================================================
 */

#ifdef __cplusplus
}
#endif

#endif /* DIGITAL_H_ */
