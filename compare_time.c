/******************************************************************************

Programa: compare_time.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa compara dois horários e diz qual é maior (usado para aprender estruturas em C).

*******************************************************************************/

#include <stdio.h>
#include <locale.h>

typedef struct _TIME {
    int hora, minuto, segundo;
} TIME;

void input_time (TIME* t);
int compare_time (TIME t1, TIME t2);

int main (void) {
    TIME t1, t2;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    input_time(&t1);
    input_time(&t2);

    switch (compare_time(t1, t2)) {
    case 0:
        printf ("\n%02d:%02d:%02d", t1.hora, t1.minuto, t1.segundo);
        break;

    case 1:
        printf ("\n%02d:%02d:%02d", t1.hora, t1.minuto, t1.segundo);
        break;

    case -1:
        printf ("\n%02d:%02d:%02d", t2.hora, t2.minuto, t2.segundo);
        break;
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

int compare_time (TIME t1, TIME t2) {

    if (t1.hora == t2.hora) {
        if (t1.minuto == t2.minuto) {
            if (t1.segundo == t2.segundo) {
                printf ("As horas são idênticas.");
                return 0;
            } else if (t1.segundo > t2.segundo) {
                printf ("A primeira hora digitada é maior.");
                return 1;
            } else {
                printf ("A segunda hora digitada é maior.");
                return -1;
            }
        } else if (t1.minuto > t2.minuto) {
                printf ("A primeira hora digitada é maior.");
                return 1;
        } else {
            printf ("A segunda hora digitada é maior.");
            return -1;
        }
    } else if (t1.hora > t2.hora) {
        printf ("A primeira hora digitada é maior.");
        return 1;
    } else {
        printf ("A segunda hora digitada é maior.");
        return -1;
    }
}
