#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main(int argc, char **argv)
{
    FILE *input;
    FILE *output;
    char option;
    int tamanho, i;
    char *buffer;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    if (argc < 3)
    {
        puts("Por favor digite o caminho do arquivo de entrada e um nome para o arquivo de saida na chamada da função.");
        exit(1);
    }

    input = fopen(argv[1], "r");

    if (!input)
    {
        puts("Não foi possivel abrir o arquivo.");
        exit(1);
    }

    if ((fopen(argv[2], "r")) != NULL)
    {
        puts("O arquivo já existe, deseja sobreescrever o conteudo? (Y/N): ");
        option = getchar();
        getchar();
        if (option == 'N' || option == 'n')
            return 1;
    }

    output = fopen(argv[2], "w");
    if (!output)
    {
        puts("Não foi possivel abrir o arquivo.");
        exit(1);
    }

    /*while (fgets(linha, sizeof(linha), input) != NULL) {  ***Use esse bloco caso queira inverter cada linha individualmente, mas mantendo sua posição

        linha[strcspn(linha, "\n")] = '\0';

        tamanho = strlen(linha);
        for (i = 0; i < (tamanho / 2); i++) {
            char temp = linha[i];
            linha[i] = linha[tamanho - i - 1];
            linha[tamanho - i - 1] = temp;
        }


        fprintf(output, "%s\n", linha);
    }*/

    fseek(input, 0, SEEK_END);
    tamanho = ftell(input);
    rewind(input);
    tamanho -= 2;
    buffer = (char *)malloc(tamanho * sizeof(char));
    if (!buffer)
    {
        puts("Não foi possível alocar o espaço de memória.");
        exit(1);
    }

    fread(buffer, sizeof(char), tamanho, input);

    for (i = 1; i <= tamanho; i++)
    {
        fputc(buffer[tamanho - i], output);
    }

    fclose(input);
    fclose(output);

    return 0;
}