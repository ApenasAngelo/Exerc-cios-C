/******************************************************************************

Programa: verify_circle.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa o estado entre dois circulos (usado para aprender estruturas em C).

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
void input_circle (CIRCLE* c);

int main (void) {
    CIRCLE c1, c2;
    float reta, sum_r, sub_r;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    input_circle (&c1);
    input_circle (&c2);

    reta = distance(c1.centro, c2.centro);

    sum_r = c1.raio + c2.raio;
    sub_r = c1.raio - c2.raio;

    if (reta < sub_r) {
        printf("As circunferências estao uma interna a outra.\n");
    } else if (reta == sub_r) {
        printf("As circunferências sao tangentes internamente.\n");
    } else if (reta > sub_r && reta < sum_r) {
        printf("As circunferências sao secantes.\n");
    } else if (reta == sum_r) {
        printf("As circunferências sao tangentes externamente.\n");
    } else {
        printf("As circunferências estao externas uma a outra.\n");
    }

    return 0;
}

void input_circle (CIRCLE* c) {
    printf ("Entre com as coordenadas do centro da circunferência: ");
    scanf ("%f %f", &c->centro.x, &c->centro.y);

    printf ("Qual é o tamanho do raio?: ");
    scanf ("%f", &c->raio);
}

float distance(PONTO p1, PONTO p2) {
    float resultado;

    resultado = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));

    return resultado;
}
/*Fim*/