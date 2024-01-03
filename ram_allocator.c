/******************************************************************************

Programa: ram_allocator.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa descobre o maior bloco de RAM disponivel para ser alocado.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(void) {

    size_t tamanho = 1;
    void *p = NULL;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    while ((p = malloc(tamanho)) != NULL) {
        printf("Tamanho da memória alocada: %zu bytes\n", tamanho);
        free(p);
        tamanho += 1000000;
    }
    
    while ((p = malloc(tamanho)) == NULL) {
        printf("Tamanho da memória que não foi possivel alocar: %zu bytes\n", tamanho);
        free(p);
        tamanho -= 10000;
    }
    
    while ((p = malloc(tamanho)) != NULL) {
        printf("Tamanho da memória alocada: %zu bytes\n", tamanho);
        free(p);
        tamanho += 100;
    }
    
    while ((p = malloc(tamanho)) == NULL) {
        printf("Tamanho da memória que não foi possivel alocar: %zu bytes\n", tamanho);
        free(p);
        tamanho -= 1;
    }
    
    printf("Tamanho máximo de memória alocável: %zu bytes\n", tamanho);

    return 0;
}
