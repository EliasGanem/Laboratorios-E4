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
#include "calculadora.h"

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/**
 * @brief Funcion que implementa el producto
 *
 * @param operando1 operando 1
 * @param opernado2 operando 2
 * @return int resultado del producto de los operandos 1 y 2
 */
static int OperacionProducto(int operando1, int opernado2);

/**
 * @brief Funcion que implementa la división
 *
 * @param operando1 operando 1
 * @param opernado2 operando 2
 * @return int resultado del cociente entre el operando 1 y el operando 2
 */
static int OperacionDivision(int operando1, int opernado2);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static int OperacionProducto(int a, int b) {
    return (a * b);
}

static int OperacionDivision(int a, int b) {
    return (a / b);
}

/* === Public function implementation ============================================================================== */
int main(void) {
    char cadena[100];
    int resultado;
    bool operacion_agregada = false;
    char suma[4] = "2+5", resta[] = "2-4", producto[] = "3*15", division[] = "10/2";
    char operador_suma = '+', operador_resta = '-', operador_producto = '*', operador_cociente = '/';

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

    printf("\n-------Prueba de la Calculadora-------\n");

    resultado = 0;

    calculadora_p calculadora = CalculadoraCrear();
    if (calculadora) {
        operacion_agregada = CalculadoraAnadirOperacion(calculadora, operador_suma, OperacionSuma);
        if (!operacion_agregada) {
            printf("ERROR al añadir la operacion Suma\n");
        }

        operacion_agregada = CalculadoraAnadirOperacion(calculadora, operador_resta, OperacionResta);
        if (!operacion_agregada) {
            printf("ERROR al añadir la operacion Resta\n");
        }

        operacion_agregada = CalculadoraAnadirOperacion(calculadora, operador_producto, OperacionProducto);
        if (!operacion_agregada) {
            printf("ERROR al añadir la operacion Producto\n");
        }

        operacion_agregada = CalculadoraAnadirOperacion(calculadora, operador_cociente, OperacionDivision);
        if (!operacion_agregada) {
            printf("ERROR al añadir la operacion Division\n");
        }

        resultado = CalcualdoraCalcular(calculadora, suma);
        printf("El resultado de %s es: %i\n", suma, resultado);

        resultado = 0;
        resultado = CalcualdoraCalcular(calculadora, resta);
        printf("El resultado de %s es: %i\n", resta, resultado);

        resultado = 0;
        resultado = CalcualdoraCalcular(calculadora, producto);
        printf("El resultado de %s es: %i\n", producto, resultado);

        resultado = 0;
        resultado = CalcualdoraCalcular(calculadora, division);
        printf("El resultado de %s es: %i\n", division, resultado);

    } else {
        printf("ERROR al crear la calculadora");
    }

    return 0;
}
/* === End of documentation ======================================================================================== */
