/******************************************************************************

Programa: calculadora_de_pi.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa utiliza pares ordenados dentro de uma circunferencia para calcular o valor de pi.

*******************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main (void) {
    
    int counter;
    float x, y;
    float conta = 0;
    float xyvalido = 0;
    float pi = 0;
    
    srand(time (NULL));
    
    for (counter = 0; counter < 1000000; counter++) {
        x = rand() / (float)RAND_MAX;
        y = rand() / (float)RAND_MAX;
        /*printf ("\n%f,%f", x, y);                         *Imprime cada par ordenado*/
        conta = (x*x) + (y*y);
        if (conta <= 1.0) {
            xyvalido++;
        }
    }
    
    /*printf ("\n\n%.0f", xyvalido);                        *Imprime quantos dos pares esão dentro da circunferencia*/
    
    pi = 4 * xyvalido / 1000000;
    printf ("\n%.2f", pi);

    /*getchar();                                            *Ativar se quiser compilar e rodar o programa pelo Windows*/
    return 0;
}
