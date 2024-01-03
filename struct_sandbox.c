/******************************************************************************

Programa: struct_sandbox.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa realiza diversas operações em uma estrutura com dados diversos (usado para aprender estruturas em C).

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TAM 5

typedef struct _BANDA {
    char nome [40];
    char genero [20];
    int qntd_Integrantes, pos_ranking;
    struct _BANDA *pt_banda;
} BANDA;

BANDA* aloca_banda ();
void le_banda (BANDA *pt_aux);
void print_banda (BANDA *pt_aux);
void sort_banda(BANDA** pt_head);

int main () {
    BANDA* pt_head = NULL;
    BANDA* pt_aux = NULL;
    int counter = 0;

    for (counter = 0; counter < TAM; counter++) {
        pt_aux = aloca_banda();

        printf ("\n%d° Banda:\n", (counter+1));
        le_banda(pt_aux);
        
        pt_aux->pt_banda = pt_head;
        pt_head = pt_aux;
    }
    
    sort_banda(&pt_head);

    print_banda(pt_head);
    
    return 0;
}

BANDA* aloca_banda () {
    BANDA* ptr;
    ptr = (BANDA*) malloc (sizeof (BANDA));
    if (!ptr) {
        puts ("Ponteiro não alocado.");
        exit(1);
    }
    return ptr;
}

void le_banda (BANDA* pt_aux) {
    puts ("Qual é o nome da banda?");
    fgets (pt_aux->nome, 39, stdin);
    
    puts ("Qual é genero que essa banda toca?");
    fgets (pt_aux->genero, 19, stdin);

    puts ("Quantos integrantes a banda tem?");
    scanf ("%d", &pt_aux->qntd_Integrantes);
    getchar();
    
    puts ("De 1 a 5, em qual posição das suas favoritas ela está?");
    scanf ("%d", &pt_aux->pos_ranking);
    getchar();

    pt_aux->pt_banda = NULL;
}

void print_banda (BANDA* pt_aux) {
    while (pt_aux != NULL) {
        printf ("\n");

        printf ("Banda: %s", pt_aux->nome);
        
        printf ("Genero: %s", pt_aux->genero);
        
        printf ("Qntd. Integrantes: %d\n", pt_aux->qntd_Integrantes);
        
        printf ("Ranking: %d\n", pt_aux->pos_ranking);

        pt_aux = pt_aux->pt_banda;
    }
}

void sort_banda(BANDA** pt_head) {
    BANDA *pt_atual, *pt_temp, *pt_antes;
    int trocados = 1;

    while (trocados) {
        trocados = 0;
        pt_atual = *pt_head;
        pt_antes = NULL;

        while (pt_atual != NULL && pt_atual->pt_banda != NULL) {
            pt_temp = pt_atual->pt_banda;

            if (pt_atual->pos_ranking > pt_temp->pos_ranking) {
                trocados = 1;
                pt_atual->pt_banda = pt_temp->pt_banda;
                pt_temp->pt_banda = pt_atual;

                if (pt_antes == NULL) {
                    *pt_head = pt_temp;
                } else {
                    pt_antes->pt_banda = pt_temp;
                }

                pt_antes = pt_temp;
            } else {
                pt_antes = pt_atual;
                pt_atual = pt_atual->pt_banda;
            }
        }
    }
}
