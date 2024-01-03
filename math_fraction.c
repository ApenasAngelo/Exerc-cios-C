/******************************************************************************

Programa: math_fraction.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa realiza operações de frações e imprime elas em formato x/y.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct _FRACAO {
    int numerador, denominador;
} FRACAO;

void input_fraction (FRACAO* f);
FRACAO sum_fraction (FRACAO f1, FRACAO f2);
FRACAO sub_fraction (FRACAO f1, FRACAO f2);
FRACAO multi_fraction (FRACAO f1, FRACAO f2);
FRACAO div_fraction (FRACAO f1, FRACAO f2);
int eval_mdc (int x, int y);

int main (void) {
    FRACAO f1, f2, f_result;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    input_fraction(&f1);
    input_fraction(&f2);

    f_result = sum_fraction(f1, f2);
    printf ("\nA soma das frações é igual a %d/%d", f_result.numerador, f_result.denominador);

    f_result = sub_fraction(f1, f2);
    printf ("\nA subtração das frações é igual a %d/%d", f_result.numerador, f_result.denominador);

    f_result = multi_fraction(f1, f2);
    printf ("\nA multiplicação das frações é igual a %d/%d", f_result.numerador, f_result.denominador);

    f_result = div_fraction(f1, f2);
    printf ("\nA divisão das frações é igual a %d/%d", f_result.numerador, f_result.denominador);

    return 0;
}

void input_fraction (FRACAO* f) {
    printf ("Digite a fração no formato N/D: ");
    scanf ("%d/%d", &f->numerador, &f->denominador);

    if (f->denominador == 0) {
        printf ("Não é possivel dividir por 0.");
        exit (1);
    }
}

FRACAO sum_fraction (FRACAO f1, FRACAO f2) {
    FRACAO temp;
    int mdc;
    temp.denominador = f1.denominador * f2.denominador;
    temp.numerador = (f1.numerador * f2.denominador) + (f2.numerador * f1.denominador);

    mdc = eval_mdc(temp.numerador, temp.denominador);
    temp.denominador /= mdc;
    temp.numerador /= mdc;

    return temp;
}

FRACAO sub_fraction (FRACAO f1, FRACAO f2) {
    FRACAO temp;
    int mdc;
    temp.denominador = f1.denominador * f2.denominador;
    temp.numerador = (f1.numerador * f2.denominador) - (f2.numerador * f1.denominador);

    mdc = eval_mdc(temp.numerador, temp.denominador);
    temp.denominador /= mdc;
    temp.numerador /= mdc;

    return temp;
}

FRACAO multi_fraction (FRACAO f1, FRACAO f2) {
    FRACAO temp;
    int mdc;
    temp.denominador = f1.denominador * f2.denominador;
    temp.numerador = f1.numerador * f2.numerador;

    mdc = eval_mdc(temp.numerador, temp.denominador);
    temp.denominador /= mdc;
    temp.numerador /= mdc;

    return temp;
}

FRACAO div_fraction (FRACAO f1, FRACAO f2) {
    FRACAO temp;
    int mdc;
    temp.denominador = f1.denominador * f2.numerador;
    temp.numerador = f1.numerador * f2.denominador;

    mdc = eval_mdc(temp.numerador, temp.denominador);
    temp.denominador /= mdc;
    temp.numerador /= mdc;

    return temp;
}

int eval_mdc (int x, int y) {
    int resto;

    while (y != 0) {
        resto = x % y;
        x = y;
        y = resto;
    }
    
    return x;
}
