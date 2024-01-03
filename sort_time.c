/******************************************************************************

Programa: sort_time.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa organiza horarios (usado para aprender estruturas em C).

*******************************************************************************/

#include <stdio.h>
#include <locale.h>

#define TAM 50

typedef struct _TIME {
    int hora, minuto, segundo;
} TIME;

void input_time (TIME* t);
void sort_time (TIME* t);

int main (void) {
    TIME t[TAM];
    int counter;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    for (counter = 0; counter < TAM; counter++) {
        input_time(&t[counter]);
    }

    sort_time (t);

    for (counter = 0; counter < TAM; counter++) {
        printf ("%02d:%02d:%02d\n", t[counter].hora, t[counter].minuto, t[counter].segundo);
    }

    return 0;
}

void input_time (TIME* t) {
    printf ("Entre um horario no formato hh:mm:ss: ");
    scanf ("%d:%d:%d", &t->hora, &t->minuto, &t->segundo);

    while ((t->hora < 0) || (t->minuto > 59 || t->minuto <0) || (t->segundo > 59 || t->segundo <0)) {
        printf ("A hora digitada é invalida, por favor tente novamente.\n");
        printf ("Entre um horario no formato hh:mm:ss: ");
        scanf ("%d:%d:%d", &t->hora, &t->minuto, &t->segundo);
    }
}

void sort_time (TIME* t) {
    int x, y;
    TIME temp;
    
    for (x = 0; x < (TAM - 1); x++) {
        for (y = 0; y < (TAM - x - 1); y++) {
            int t1 = t[y].hora * 3600 + t[y].minuto * 60 + t[y].segundo;
            int t2 = t[y+1].hora * 3600 + t[y+1].minuto * 60 + t[y+1].segundo;

            if (t1 > t2) {
                temp = t[y];
                t[y] = t[y+1];
                t[y+1] = temp;
            }
        }
    }
}
/*Fim*/