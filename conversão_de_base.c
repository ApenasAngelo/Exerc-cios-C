/******************************************************************************

Programa: conversão_de_base.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa converte números de uma base específica para outra.

*******************************************************************************/

#include <stdio.h>
#include <locale.h>

int main (void) {
    
    int opcao, num;

    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    while (1) {
        printf ("\n===========================\n");
        printf ("1. decimal para hexadecimal\n");
        printf ("2. hexadecimal para decimal\n");
        printf ("3. decimal para octal\n");
        printf ("4. octal para decimal\n");
        printf ("5. Encerrar\n");
        printf ("\nO que deseja fazer?: ");
        scanf ("%d", &opcao);
        
        switch (opcao) {
            case 1:
            printf ("\nDigite o número que você deseja converter: ");
            scanf ("%d", &num);
            printf ("%d em hexadecimal é %X\n", num, num);
            break;
            
            case 2:
            printf ("\nDigite o número que você deseja converter: ");
            scanf ("%X", &num);
            printf ("%X em decimal é %d\n", num, num);
            break;
            
            case 3:
            printf ("\nDigite o número que você deseja converter: ");
            scanf ("%d", &num);
            printf ("%d em octal é %o\n", num, num);
            break;
            
            case 4:
            printf ("\nDigite o número que você deseja converter: ");
            scanf ("%o", &num);
            printf ("%o em decimal é %d\n", num, num);
            break;
            
            case 5:
            return 0;
        }
    }

    /*getchar();                                            *Ativar se quiser compilar e rodar o programa pelo Windows*/
    return 0;
    }
