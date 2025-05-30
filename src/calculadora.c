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
#include <config.h>
#include <stdbool.h>

/* === Macros definitions ========================================================================================== */
#ifndef CALCUALDORA_MAX_OPERACIONES
#define CALCUALDORA_MAX_OPERACIONES 4
#endif

#ifndef CALCUALDORA_MAX_INSTANCIAS
#define CALCUALDORA_MAX_INSTANCIAS 2
#endif
/* === Private data type declarations ============================================================================== */

//! Puntero a una operación de una lista enlazada simple
typedef struct operacion_s * operacion_p;

//! Declaración de una operación perteneciente a un lista enlazada simple
struct operacion_s {
    char operador;                 //!< caracter que representa a la operación
    funcion_calculadora_p funcion; //!< función que implementa la operación
    operacion_p siguiente;         //!< puntero a la siguiente operación en la lista
#ifndef USAR_MEMORIA_DINAMICA
    bool ocupado; //!< en caso de no usar memoria dinamica indica si el espacio de memoria esta ocupado
#endif
};

//! Estructura que representa al objeto calculadora
struct calculadora_s {
    operacion_p operaciones; //!< lista enlazada simple con las operaciones de la calculadora
#ifndef USAR_MEMORIA_DINAMICA
    bool ocupado; //!< en caso de no usar memoria dinamica indica si el espacio de memoria esta ocupado
#endif
};

/* === Private function declarations =============================================================================== */

/**
 * @brief Función que busca si la operación fue agregada a la calcuadora
 *
 * @param self calculadora
 * @param operador operador de la operación que se busca
 * @return retorna un puntero al elemento de la lista enlazada que se buscaba, si no se encontró devuelve NULL
 */
static operacion_p BuscarOperacion(calculadora_p self, char operador);

#ifndef USAR_MEMORIA_DINAMICA
/**
 * @brief Funcion para crear referencias de una calculado en caso de no usar memoria dinámica
 *
 * @return retorna la referencia a la calculadora creada, en caso de no ser posible devuelve NULL
 */
static calculadora_p CalculadoraCrearInstancia();

/**
 * @brief Funcion para tener espacio para operaciones en caso de no usar memoria dinamica
 *
 * @return retorna la referencia a la operacion creada, en caso de no ser posible devuelve NULL
 */
static operacion_p OperacionesCrearInstancia();
#endif

/* === Private variable definitions ================================================================================ */

#ifndef USAR_MEMORIA_DINAMICA
static struct calculadora_s instancias_calculadora[CALCUALDORA_MAX_INSTANCIAS] = {0};
static struct operacion_s instancias_operaciones[CALCUALDORA_MAX_OPERACIONES] = {0};
#endif

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
#ifndef USAR_MEMORIA_DINAMICA
static calculadora_p CalcualdoraCrearInstancia() {
    calculadora_p self = NULL;
    int i;

    for (i = 0; i < CALCUALDORA_MAX_INSTANCIAS; i++) {
        if (!instancias_calculadora[i].ocupado) {
            instancias_calculadora[i].ocupado = true;
            self = &instancias_calculadora[i];
            break;
        }
    }

    return self;
}

static operacion_p OperacionesCrearInstancia() {
    operacion_p self = NULL;
    int i;

    for (i = 0; i < CALCUALDORA_MAX_OPERACIONES; i++) {
        if (!instancias_operaciones[i].ocupado) {
            instancias_operaciones[i].ocupado = true;
            self = &instancias_operaciones[i];
            break;
        }
    }

    return self;
}
#endif

/* === Public function definitions ================================================================================= */

calculadora_p CalculadoraCrear(void) {
#ifdef USAR_MEMORIA_DINAMICA
    calculadora_p self = malloc(sizeof(struct operacion_s));
#else
    calculadora_p self = CalcualdoraCrearInstancia();
#endif

    if (self) {
        self->operaciones = NULL;
    }

    return self;
}

bool CalculadoraAnadirOperacion(calculadora_p calcualdora, char operador, funcion_calculadora_p funcion) {

    if (!calcualdora || !funcion || BuscarOperacion(calcualdora, operador)) {
        return false;
    }

#ifdef USAR_MEMORIA_DINAMICA
    operacion_p operacion = malloc(sizeof(struct operacion_s));
#else
    operacion_p operacion = OperacionesCrearInstancia();
#endif
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
