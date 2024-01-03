#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void compare_with_file(FILE *file, char *string);

int main(int argc, char **argv)
{
    FILE *input;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    if (argc < 3)
    {
        puts("Utilize: .\\find_string arquivo.txt \"frase a procurar\" (Case Sensitive)");
        exit(1);
    }

    input = fopen(argv[1], "r");
    if (!input)
    {
        puts("Não foi possivel abrir o arquivo.");
        exit(1);
    }

    compare_with_file(input, argv[2]);

    return 0;
}

void compare_with_file(FILE *file, char *string)
{
    char buffer[1024];
    int line = 1;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (strstr(buffer, string) != NULL)
        {
            printf("Linha %d: %s", line, buffer);
        }
        line++;
    }
}