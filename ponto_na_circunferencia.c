/******************************************************************************

Programa: ponto_na_circunferência.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa diz se um ponto está dentro de um determinado circulo (usado para aprender estruturas em C).

*******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <locale.h>

typedef struct _PONTO {
    float x, y;
} PONTO;

typedef struct _CIRCLE {
    float raio;
    PONTO centro;
} CIRCLE;

float distance(PONTO p1, PONTO p2);

int main (void) {
    PONTO p1;
    CIRCLE c1;
    float reta;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    printf ("Entre com as coordenadas do ponto 1: ");
    scanf ("%f %f", &p1.x, &p1.y);

    printf ("Entre com as coordenadas do centro da circunferência: ");
    scanf ("%f %f", &c1.centro.x, &c1.centro.y);

    printf ("Qual é o tamanho do raio?: ");
    scanf ("%f", &c1.raio);

    reta = distance(p1, c1.centro);

    if (reta < c1.raio) {
        printf ("O ponto está dentro da circunferência.");
    } else {
        printf ("O ponto não está dentro da circunferência.");
    }

    return 0;
}

float distance(PONTO p1, PONTO p2) {
    float resultado;

    resultado = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));

    return resultado;
}
