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

#ifndef CALCULADORA_H_
#define CALCULADORA_H_

/** @file calculadora.h
 ** @brief Declaraciones del modulo calculadora - Electrónica 4 2025
 **/

/* === Headers files inclusions ==================================================================================== */

#include <stdbool.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

//! Referencia del objeto calculadora
typedef struct calculadora_s * calculadora_p;

//! Interfase para la caculadora
typedef int (*funcion_calculadora_p)(int, int);

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Funcion para crear una calculadora
 *
 * @return Devuele calculadora_p que es una referencia al objeto calculadora creado, en caso de no poder crearlo
 * devuelve NULL
 */
calculadora_p CalculadoraCrear(void);

/**
 * @brief Funcion para añadir una operacion a una calculadora
 *
 * @param calcualdora calculadora a la que se añade la operacion
 * @param operador caracter usado para la operacion
 * @param funcion puntero a la funcion que implementa la operacion
 * @return bool devuelve true si se añadió la operación, y false si la operacion ya esta o los argumentos son
 * incorrectos
 */
bool CalculadoraAnadirOperacion(calculadora_p calcualdora, char operador, funcion_calculadora_p funcion);

/**
 * @brief Realiza el calculo con una cadena de caracteres
 *
 * @param calculadora referencia de la caluladora que realizara el calculo
 * @param expresion cadena de caracteres con la operacion a realizar
 * @return int devuelve el resultado del calculo
 */
int CalcualdoraCalcular(calculadora_p calculadora, const char * expresion);

/**
 * @brief Funcion que implementa la suma, debe ser agreaga a la calculadora
 *
 * @param operando1 operando 1
 * @param operando2 operando 2
 * @return int resultado de la suma
 */
int OperacionSuma(int operando1, int operando2);

/**
 * @brief Funcion que implementa la resta, debe ser agreaga a la calculadora
 *
 * @param operando1 operando 1
 * @param operando2 operando 2
 * @return int resultado de la resta
 */
int OperacionResta(int operando1, int operamdo2);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* CALCULADORA_H_ */
