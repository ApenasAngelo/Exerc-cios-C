/******************************************************************************

Programa: lista_sandbox.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa realiza diversas operacões com uma lista encadeada.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct _LISTA{
    int valor;
    struct _LISTA *prox;
} LISTA;

    void print_lista (LISTA *pt_head);
    void adicionar_lista(LISTA **pt_head);
    void sort_lista(LISTA **pt_head);
    void find_lista(LISTA *pt_head);


int main(void) {
    LISTA *pt_head = NULL;
    int counter = 0;

    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(NULL));

    for (counter = 0; counter < 5; counter++) {
    adicionar_lista(&pt_head);
    }

    printf ("-------Não Ordenados-------");
    print_lista (pt_head);

    sort_lista(&pt_head);
    printf ("-------Ordenados-------");
    print_lista (pt_head);

    find_lista(pt_head);

    return 0;
}

void print_lista (LISTA *pt_head) {
    LISTA *pt_aux = NULL;
    pt_aux = pt_head;
    printf ("\n");
    while (pt_aux != NULL) {
        printf ("%d", pt_aux->valor);
        printf ("\n");
        pt_aux = pt_aux->prox;
    }
}

void adicionar_lista(LISTA **lista) {
    LISTA *aux;
    LISTA *novo = (LISTA *)malloc(sizeof(LISTA));
       
    if (novo){
        novo->valor = rand() % 100;
        novo->prox = NULL;

        if (*lista == NULL){
            *lista = novo;
        } else {
            aux = *lista;
            while(aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = novo;
        }    
    } else {
        printf("Erro ao alocar memoria!\n");
    }       
}

void sort_lista(LISTA **pt_head) {
    LISTA *pt_atual, *pt_temp, *pt_antes;
    int trocados = 1;

    while (trocados) {
        trocados = 0;
        pt_atual = *pt_head;
        pt_antes = NULL;

        while (pt_atual != NULL && pt_atual->prox != NULL) {
            pt_temp = pt_atual->prox;

            if (pt_atual->valor > pt_temp->valor) {
                trocados = 1;
                pt_atual->prox = pt_temp->prox;
                pt_temp->prox = pt_atual;

                if (pt_antes == NULL) {
                    *pt_head = pt_temp;
                } else {
                    pt_antes->prox = pt_temp;
                }

                pt_antes = pt_temp;
            } else {
                pt_antes = pt_atual;
                pt_atual = pt_atual->prox;
            }
        }
    }
}

void find_lista(LISTA* pt_head) {
    int valor, pos = 1, achados = 0;
    LISTA *pt_aux = pt_head;

    printf ("\nQual valor você deseja procurar? Entre 1-100: ");
    scanf ("%d", &valor);

    while (pt_aux != NULL && pt_aux->prox != NULL) {
        if (pt_aux->valor == valor) {
            achados++;
            printf("O valor está na posição %d", pos);
            pt_aux = pt_aux->prox;
        } else {
            pt_aux = pt_aux->prox;
        }
        pos++;
    }
    if (achados == 0)
        printf("O valor não existe");
}
