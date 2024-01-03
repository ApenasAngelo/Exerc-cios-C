/******************************************************************************

Programa: string_sandbox.c
Autor: Miguel Angelo Gonzaga Marques
Data: 30/10/2022
Descrição: Este programa realiza diferentes operações entre duas strings sem utilizar a header <string.h>.

*******************************************************************************/

#include <stdio.h>
#include <locale.h>

#define NONSTR "a"

int mystrlen(char* s);
void limpar_buffer(char* s);
int rmvln(char* s);

int main (void) {

    char str1[255];
    char str2[255];
    char str3[509];
    char caracter;
    int opcao;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    while (1) {
        printf ("\nDigite a primeira string: ");
        fgets (str1, 255, stdin);
        limpar_buffer(str1);
        rmvln(str1);

        printf ("Digite a segunda string: ");
        fgets (str2, 255, stdin);
        limpar_buffer(str2);
        rmvln(str2);

        printf ("\n===========================\n");
        printf ("1. Mostrar as strings invertidas\n");
        printf ("2. Copiar as strings lado a lado\n");
        printf ("3. Informar qual é a maior string\n");
        printf ("4. Identificar a ocorrência de algum caracter\n");
        printf ("5. Encerrar\n");
        printf ("\nO que deseja fazer?: ");
        scanf ("%d", &opcao);
        limpar_buffer(NONSTR);

        switch (opcao) {
            case 1:
                for (int x = mystrlen(str1); x >= 0; x--) printf ("%c", str1[x]);
                printf ("\n");
                for (int x = mystrlen(str2); x >= 0; x--) printf ("%c", str2[x]);
                printf ("\n");
                break;

            case 2:
                for (int x = 0; str1[x] != '\0'; x++) str3[x] = str1[x];
                int x = mystrlen(str1);
                for (int y = 0; str2[y] != '\0'; x++, y++) str3[x] = str2[y];

                puts (str3);
                break;

            case 3:
                if (mystrlen(str1) > mystrlen(str2)) printf ("A primeira string e maior\n");
                else printf ("A segunda string e maior.\n");
                break;

            case 4:
                printf ("qual caracter deseja achar?: ");
                caracter = getchar();
                getchar();

                for (x = 0; str1[x] != '\0'; x++) {
                    if (str1[x] == caracter) {
                        printf ("Caracter %d° posição da 1° string\n", x);
                    }
                }
                printf ("\n");
                for (x = 0; str2[x] != '\0'; x++) {
                    if (str2[x] == caracter) {
                        printf ("Caracter %d° posição da 2° string\n", x);
                    }
                }
                break;

            case 5:
                return 0;
        }
    }
    return 0;
}

int mystrlen(char* s) {
    int length;
    for (length = 0; *s++; length++);
    return length;
}

void limpar_buffer(char* s) {
    int flag;
    int c;

    for (int i = 0; s[i]; i++){        /*Verifica se a string possui '\n'*/
        if(s[i] == '\n') flag = 0;
    }
    if (flag != 0) flag = 1;

    if (flag) while ((c = getchar()) != '\n' && c != EOF) {}
}

int rmvln(char* string){
    int i;

    for (i = 0; string[i]; i++){        /*Verifica se a string possui '\n'*/
        if(string[i] == '\n') {
            string[i] = '\0';
            return 1;
        }
    }
    return 0;
}
