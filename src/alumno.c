/*********************************************************************************************************************
Copyright (c) 2025, Elías Ganem <eliasgfac@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

/** @file alumno.c
 ** @brief Codigo duente del modulo alumno para el laboratorio 2 - Electrónica 4 2025
 **/

/* === Headers files inclusions ==================================================================================== */

#include <stdio.h>
#include "alumno.h"

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/**
 * @brief Funcion para agregar campos con formato json a un string, el ultimo elemento es una ',' por lo que debe ser
 * reemplazada externamente por el retorno de carro.
 *
 * @param campo //!< Nombre del campo.
 * @param valor //!< Valor del campo.
 * @param buffer //!< Puntero al string donde se almacena el json.
 * @param disponible //!< Espacio disponible del Srting al que se le agregan el campo.
 * @return int
 */
static int SerializarCadena(const char * campo, const char * valor, char * buffer, uint32_t disponible);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

int SerializarCadena(const char * campo, const char * valor, char * buffer, uint32_t disponible) {
    return snprintf(buffer, disponible, "\"%s\":\"%s\",", campo, valor);
}

/* === Public function definitions ================================================================================= */

int Serializar(alumno_p alumno, char * puntero, uint32_t size) {
    int error;        //!< Variable con el resultado de la serializacion de cada cadena.
    int escritos = 1; //!< Variable para llevar la cuenta de caracteres escritos.
    char documento[10];

    snprintf(documento, sizeof(documento), "%u", alumno->documento);

    puntero[0] = '{';
    puntero++;
    error = SerializarCadena("nombre", alumno->nombre, puntero, size - escritos);
    if (error < 0) {
        return -1;
    }
    escritos += error;

    puntero += error;
    error = SerializarCadena("apellido", alumno->apellido, puntero, size - escritos);
    if (error < 0) {
        return -1;
    }
    escritos += error;

    puntero += error;
    error = SerializarCadena("documento", documento, puntero, size - escritos);
    if (error < 0) {
        return -1;
    }

    puntero += (error - 1);
    *puntero = '}';
    puntero++;
    *puntero = '\n';

    return error;
}

/* === End of documentation ======================================================================================== */
