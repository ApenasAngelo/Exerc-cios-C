/******************************************************************************

Programa: input_jogador.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa recebe uma lista de "jogadores" e os organiza decrescentemente por pontos (usado para aprender estruturas em C).

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAM 5

typedef struct _JOGADOR {
    int pontos;
    char nome[42];
} JOGADOR;

void input_jogador (JOGADOR* j, int i);
void sort_jogador (JOGADOR* j);

int main (void) {
    JOGADOR j[TAM];
    int counter;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    for (counter = 0; counter < TAM; counter++) {
        input_jogador(j, counter);
    }

    sort_jogador (j);

    for (counter = 0; counter < TAM; counter++) {
        printf ("\nO jogador %s tem %d pontos", j[counter].nome, j[counter].pontos);
    }

    return 0;
}

void input_jogador (JOGADOR* j, int i) {
    puts ("Qual é o nome desse jogador?: ");
    fgets ((j+i)->nome, 41, stdin);
    (j+i)->nome[strlen((j+i)->nome) - 1] = 0;

    puts ("Quantos pontos o jogador fez?: ");
    scanf ("%d", &(j+i)->pontos);
    getchar();
}

void sort_jogador (JOGADOR* j) {
    int x, y;
    JOGADOR temp;
    
    for (x = 0; x < (TAM - 1); x++) {
        for (y = 0; y < (TAM - x - 1); y++) {
            int j1 = j[y].pontos;
            int j2 = j[y+1].pontos;


            if (j1 < j2) {
                temp = j[y];
                j[y] = j[y+1];
                j[y+1] = temp;
            }
        }
    }
}
