/******************************************************************************

Programa: add_time.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa soma dois horários (usado para aprender estruturas em C).

*******************************************************************************/

#include <stdio.h>
#include <locale.h>

typedef struct _TIME {
    int hora, minuto, segundo;
} TIME;

void input_time (TIME* t);
TIME add_time (TIME t1, TIME t2);

int main (void) {
    TIME t1, t2, t3;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    input_time(&t1);
    input_time(&t2);

    t3 = add_time(t1, t2);

    printf ("As horas somadas ficam: %02d:%02d:%02d", t3.hora, t3.minuto, t3.segundo);

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

TIME add_time (TIME t1, TIME t2) {
    TIME t3;

    t3.segundo = (t1.segundo + t2.segundo) % 60;
    t3.minuto = (t1.minuto + t2.minuto +((t1.segundo + t2.segundo) / 60)) % 60;
    t3.hora = (t1.hora + t2.hora +((t1.minuto + t2.minuto) / 60));

    return t3;
}
