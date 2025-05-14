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

/** @file main.c
 ** @brief Codigo fuente Principal para el laboratorio 2 - Electrónica 4 2025
 **/

/* === Headers files inclusions ==================================================================================== */

#include <stdio.h>
#include "alumno.h"

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

/* === Public function implementation ============================================================================== */
int main(void) {
    char cadena[100];
    int resultado;

    alumno_p yo = AlumnoCrear("Elías", "Ganem", 43499611);
    if (yo != NULL) {
        resultado = AlumnoSerializar(yo, cadena, sizeof(cadena));

        if (resultado > 0) {
            printf("Serializado: %s", cadena);
            printf("La cantidad de caracteres escritos es %i y los sobrantes son %li\n\n", resultado,
                   (sizeof(cadena) - resultado));
        } else {
            printf("Error al serializar\n");
        }
    } else {
        printf("Error la referencia es nulo\n");
    }

    alumno_p el = AlumnoCrear("Pepito", "Grillo", 43567890);
    if (el != NULL) {
        resultado = AlumnoSerializar(el, cadena, sizeof(cadena));

        if (resultado > 0) {
            printf("Serializado: %s", cadena);
            printf("La cantidad de caracteres escritos es %i y los sobrantes son %li\n\n", resultado,
                   (sizeof(cadena) - resultado));
        } else {
            printf("Error al serializar\n");
        }
    } else {
        printf("Error la referencia es nula\n");
    }

    alumno_p ella = AlumnoCrear("Soledad", "Gricelda", 43824600);
    if (ella != NULL) {
        resultado = AlumnoSerializar(ella, cadena, sizeof(cadena));

        if (resultado > 0) {
            printf("Serializado: %s", cadena);
            printf("La cantidad de caracteres escritos es %i y los sobrantes son %li\n\n", resultado,
                   (sizeof(cadena) - resultado));
        } else {
            printf("Error al serializar\n");
        }
    } else {
        printf("Error la referencia es nula\n");
    }

    return 0;
}
/* === End of documentation ======================================================================================== */
