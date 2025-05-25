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

/** @file calculadora.c
 ** @brief Codigo duente del modulo calculadora para los laboratorios - Electrónica 4 2025
 **/

/* === Headers files inclusions ==================================================================================== */

#include "calculadora.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

//! Puntero a una operacion de una lista enlazada simple
typedef struct operacion_s * operacion_p;

//! Declaracion de una operacion perteneciente a un lista enlazada simple
struct operacion_s {
    char operador;               //!< caracter que representa a la operacion
    funcion_operacion_p funcion; //!< funcion que hace la operacion
    operacion_p siguiente;       //!< puntero a la siguiente operacion en la lista
};

//! Estructura que representa al objeto calculadora
struct calculadora_s {
    operacion_p operaciones; //!< lista enlazada simple con las operaciones de la calculadora
};

/* === Private function declarations =============================================================================== */

static operacion_p BuscarOperacion(calculadora_p self, char operador);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static operacion_p BuscarOperacion(calculadora_p self, char operador) {
    operacion_p funcion = self->operaciones;

    while (funcion) {
        if (funcion->operador == operador) {
            return funcion;
        }
        funcion = funcion->siguiente;
    }

    return NULL;
}

/* === Public function definitions ================================================================================= */

calculadora_p CalculadoraCrear(void) {
    calculadora_p self = malloc(sizeof(struct operacion_s));

    if (self) {
        self->operaciones = NULL;
    }

    return self;
}

bool CalculadoraAnadirOperacion(calculadora_p calcualdora, char operador, funcion_operacion_p funcion) {

    if (!calcualdora || !funcion || BuscarOperacion(calcualdora, operador)) {
        return false;
    }

    operacion_p operacion = malloc(sizeof(struct operacion_s));
    if (operacion) {
        operacion->funcion = funcion;
        operacion->operador = operador;
        operacion->siguiente = calcualdora->operaciones;
        calcualdora->operaciones = operacion;
        return true;
    }
    return false;
}

int CalcualdoraCalcular(calculadora_p calculadora, const char * expresion) {
    int a = 0, b = 0;
    char operador = '\0';
    int resultado = 0;

    if (!calculadora || !expresion) {
        return 0;
    }

    for (int i = 0; i < strlen(expresion); i++) {
        if (expresion[i] < '0' || expresion[i] > '9') {
            operador = expresion[i];
            a = atoi(expresion);
            b = atoi(expresion + i + 1);
            break;
        }
    }

    operacion_p operacion = BuscarOperacion(calculadora, operador);
    if (operacion) {
        return operacion->funcion(a, b);
    }

    return 0;
}

int OperacionSuma(int a, int b) {
    return (a + b);
}

int OperacionResta(int a, int b) {
    return (a - b);
}

/* === End of documentation ======================================================================================== */
