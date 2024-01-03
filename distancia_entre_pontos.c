/******************************************************************************

Programa: distancia_entre_pontos.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa diz a distancia entre dois pontos em um plano (usado para aprender estruturas em C).

*******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <locale.h>

typedef struct _PONTO {
    float x, y;
} PONTO;

float distance(PONTO p1, PONTO p2);

int main (void) {
    PONTO p1, p2;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    printf ("Entre com as coordenadas do ponto 1: ");
    scanf ("%f %f", &p1.x, &p1.y);

    printf ("Entre com as coordenadas do ponto 2: ");
    scanf ("%f %f", &p2.x, &p2.y);

    printf ("A distancia entre os pontos é: %.2f", distance(p1, p2));

    return 0;
}

float distance(PONTO p1, PONTO p2) {
    float resultado;

    resultado = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));

    return resultado;
}
