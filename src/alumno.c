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
 ** @brief Codigo duente del modulo alumno para los laboratorios - Electrónica 4 2025
 **/

/* === Headers files inclusions ==================================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "alumno.h"
#include "config.h"

/* === Macros definitions ========================================================================================== */

#ifndef ALUMNOS_MAX_INSTANCIAS
#define ALUMNOS_MAX_INSTANCIAS 2 //!< Cantidad máxima de alumnos
#endif

/* === Private data type declarations ============================================================================== */

//! Estructura que representa el estado de un alumno
struct alumno_s {
    char nombre[20];    //!< Nombre del alumno
    char apellido[20];  //!< Apellido del alumno
    uint32_t documento; //!< Número de documento del alumno
#ifndef USAR_MEMORIA_DINAMICA
    bool ocupado; //!< Indica si la instancia está ocupada
#endif
};

/* === Private function declarations =============================================================================== */

/**
 * @brief Funcion para agregar campos de tipo char con formato json a un string, el ultimo elemento es una ',' por lo
 * que debe ser reemplazada externamente por el retorno de carro.
 *
 * @param campo //!< Nombre del campo.
 * @param valor //!< Valor del campo.
 * @param buffer //!< Puntero al string donde se almacena el json.
 * @param disponible //!< Espacio disponible del Srting al que se le agregan el campo.
 * @return int //!< Devuelve un entero, si es negativo entonces no se pudo serializar.
 */
static int SerializarCadena(const char * campo, const char * valor, char * buffer, uint32_t disponible);

/**
 * @brief Funcion para agregar campos de tipo uint32_t con formato json a un string, el ultimo elemento es una ',' por
 * lo que debe ser reemplazada externamente por el retorno de carro.
 * @param campo //!< Nombre del campo.
 * @param valor //!< Valor del campo
 * @param buffer //!< Puntero al string donde se almacena el json.
 * @param disponible //!< Espacio disponible del Srting al que se le agregan el campo.
 * @return int //!< Devuelve un entero, si es negativo entonces no se pudo serializar.
 */
static int SerializarNumero(const char * campo, uint32_t valor, char * buffer, uint32_t disponible);

/**
 * @brief Funcion para crear instancia de alumnos en caso de NO usar memoria dinamica.
 *
 * @return alumno_p //!< Devuelve NULL en caso de no tener espacio, en caso contrario devuelve la referencia del alumno
 * disponible
 */
static alumno_p CrearInstancia();

/* === Private variable definitions ================================================================================ */

//! Array de alumnos
static struct alumno_s instancias[ALUMNOS_MAX_INSTANCIAS] = {0};

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static int SerializarCadena(const char * campo, const char * valor, char * buffer, uint32_t disponible) {
    return snprintf(buffer, disponible, "\"%s\":\"%s\",", campo, valor);
}

static int SerializarNumero(const char * campo, uint32_t valor, char * buffer, uint32_t disponible) {
    return snprintf(buffer, disponible, "\"%s\":\"%u\",", campo, valor);
}

#ifndef USAR_MEMORIA_DINAMICA
static alumno_p CrearInstancia() {
    alumno_p self = NULL; //!< Referencia al alumno a crear
    int i;

    for (i = 0; i < ALUMNOS_MAX_INSTANCIAS; i++) {
        if (!instancias[i].ocupado) {
            instancias[i].ocupado = true;
            self = &instancias[i];
            break;
        }
    }

    return self;
}
#endif

/* === Public function definitions ================================================================================= */

alumno_p AlumnoCrear(char * nombre, char * apellido, uint32_t dni) {
    alumno_p self; //!< Referencia al alumno a crear

#ifdef USAR_MEMORIA_DINAMICA
    self = malloc(sizeof(struct alumno_s));
#else
    self = CrearInstancia();
#endif

    if (self != NULL) {
        strncpy(self->nombre, nombre, sizeof(self->nombre) - 1);
        strncpy(self->apellido, apellido, sizeof(self->apellido) - 1);
        self->documento = dni;
    }

    return self;
}

int AlumnoSerializar(alumno_p alumno, char * puntero, uint32_t size) {
    int error;        //!< Variable con el resultado de la serializacion de cada cadena.
    int escritos = 1; //!< Variable para llevar la cuenta de caracteres escritos.

    if (alumno == NULL) {
        return -1;
    }

    puntero[0] = '{';
    puntero++;
    error = SerializarCadena("nombre", alumno->nombre, puntero, size - escritos);
    if (error < 0 || error >= (size - escritos)) {
        return -1;
    }
    escritos += error;

    puntero += error;
    error = SerializarCadena("apellido", alumno->apellido, puntero, size - escritos);
    if (error < 0 || error >= (size - escritos)) {
        return -1;
    }
    escritos += error;

    puntero += error;
    error = SerializarNumero("documento", alumno->documento, puntero, size - escritos);
    if (error < 0 || error >= (size - escritos)) {
        return -1;
    }
    escritos += error;

    puntero += (error - 1);
    *puntero = '}';

    if ((size - escritos) < 1) {
        return -1;
    }

    puntero++;
    *puntero = '\n';

    return (escritos + 1);
}

/* === End of documentation ======================================================================================== */
