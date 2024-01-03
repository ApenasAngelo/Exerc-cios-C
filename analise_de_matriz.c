/******************************************************************************

Programa: analise_de_matriz.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa analisa linhas, colunas e diagonais de uma matriz 3x3 e diz caso algum valores idênticos.

*******************************************************************************/

#include <stdio.h>
#include <locale.h>

#define SIZE 3

int main (void) {

    char array[SIZE][SIZE];
    char arrayOld;
    int x = 0, y = 0, z = 0, counter = 0;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    printf ("Digite valores seguidos para compor a matriz e de ENTER a cada um deles (apenas 0 ou 1)\n");
    for (x = 0; x < SIZE; x++) {
        for (y = 0; y < SIZE; y++) {
            z = 0;
            while (z == 0) {
                scanf("%c", &array[x][y]);
                getchar();
                if (array[x][y] != '0' && array[x][y] != '1') {
                    printf ("O número precisa ser 0 ou 1!\n");
                } else {
                    z = 1;
                }
            }
        }
    }

    printf ("\nEssa é uma visualização da sua matriz:\n");
    for (x = 0; x < SIZE; x++) {
        for (y = 0; y < SIZE; y++) {
        printf ("%c ", array[x][y]);
        }
        printf ("\n");
    }
    
    for (x = 0; x < SIZE; x++) {
        y = 0;
        for (counter = 0, arrayOld = array[x][y]; y < SIZE; y++) {
            if (array[x][y] == arrayOld){
                counter++;
            }
            if (counter == SIZE) {
                printf ("\nA linha %d possui todos os seus elementos idênticos.", x);
            }
        }
    }

    for (y = 0; y < SIZE; y++) {
        x = 0;
        for (counter = 0, arrayOld = array[x][y]; x < SIZE; x++) {
            if (array[x][y] == arrayOld){
                counter++;
            }
            if (counter == SIZE) {
                printf ("\nA coluna %d possui todos os seus elementos idênticos.", y);
            }
        }
    }

    for (x = 0, y = 0, counter = 0, arrayOld = array[0][0]; x < SIZE && y < SIZE; x++, y++) {
        if (array[x][y] == arrayOld){
            counter++;
        }
        if (counter == SIZE) {
            printf ("\nA diagonal superior esquerda possui todos os seus elementos idênticos.");
        }
    }

    for (x = 0, y = SIZE, counter = 0, arrayOld = array[0][SIZE]; x < SIZE; x++) {
        if (array[x][y] == arrayOld){
            counter++;
            y--;
        }
        if (counter == SIZE) {
            printf ("\nA diagonal superior direita possui todos os seus elementos idênticos.");
        }
    }

    return 0;
}
