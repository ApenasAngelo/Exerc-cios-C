#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

typedef struct _DATA
{
    int dia, mes, ano;
} DATA;

typedef struct _CONTATO
{
    char nome[51];
    char telefone[16];
    DATA aniversario;
    struct _CONTATO *prox;
} CONTATO;

void salvar_contatos(CONTATO *pt_head, char *nome_arquivo);
CONTATO *carregar_contatos(char *nome_arquivo);
void print_contatos(CONTATO *pt_head);
void adicionar_contato(CONTATO **contatos);
void remover_contato(CONTATO **contatos);
void sort_lista_contatos(CONTATO **pt_head);
void print_contatos_by_name(CONTATO *pt_head);
void print_contatos_by_letter(CONTATO *pt_head);
void print_birthdays(CONTATO *pt_head);
void limpar_buffer_entrada();

int main(void)
{
    int opcao;
    CONTATO *pt_head;

    setlocale(LC_ALL, "pt_BR.UTF-8");

#ifdef _WIN32
    pt_head = carregar_contatos("lista_contatos.txt");
#elif __linux
    pt_head = carregar_contatos("lista_contatos");
#endif

    while (1)
    {
        puts("-------Menu-------");
        puts("1: Inserir contato");
        puts("2: Remover contato");
        puts("3: Pesquisar contato");
        puts("4: Listar todos os contatos");
        puts("5: Listar todos os contatos com inicial");
        puts("6: Imprimir os aniversariantes do mês");
        puts("7: Sair");
        printf("> ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            puts("------------------");
            adicionar_contato(&pt_head);
            sort_lista_contatos(&pt_head);
            puts("\n");
            break;

        case 2:
            puts("------------------");
            print_contatos(pt_head);
            remover_contato(&pt_head);
            puts("\n");
            break;

        case 3:
            puts("------------------");
            print_contatos_by_name(pt_head);
            break;

        case 4:
            puts("------------------");
            print_contatos(pt_head);
            break;

        case 5:
            puts("------------------");
            print_contatos_by_letter(pt_head);
            break;

        case 6:
            puts("------------------");
            print_birthdays(pt_head);
            break;

        case 7:
            if (pt_head != NULL)
            {
#ifdef _WIN32
                salvar_contatos(pt_head, "lista_contatos.txt");
#elif __linux
                salvar_contatos(pt_head, "lista_contatos");
#elif __APPLE__
                salvar_contatos(pt_head, "lista_contatos.txt");
#endif
            }
            return 0;

        default:
            puts("------------------");
            puts("Valor inválido, tente outro por favor.");
            break;

            return 0;
        }
    }

    return 0;
}

void salvar_contatos(CONTATO *pt_head, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    CONTATO *pt_aux = pt_head;
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para salvar os contatos.\n");
        return;
    }

    while (pt_aux != NULL)
    {
        fprintf(arquivo, "%s", pt_aux->nome);
        fprintf(arquivo, "%s\n", pt_aux->telefone);
        fprintf(arquivo, "%02d/%02d/%04d\n", pt_aux->aniversario.dia, pt_aux->aniversario.mes, pt_aux->aniversario.ano);
        pt_aux = pt_aux->prox;
    }

    fclose(arquivo);
    printf("Contatos salvos com sucesso no arquivo %s.\n", nome_arquivo);
}

CONTATO *carregar_contatos(char *nome_arquivo)
{
    FILE *file = fopen(nome_arquivo, "r");
    CONTATO *pt_head = NULL;
    char linha[67];

    if (file == NULL)
    {
        return NULL;
    }

    while (fgets(linha, sizeof(linha), file))
    {
        CONTATO *novo = (CONTATO *)malloc(sizeof(CONTATO));

        strcpy(novo->nome, linha);

        fgets(linha, sizeof(linha), file);
        linha[strcspn(linha, "\n")] = '\0';
        strcpy(novo->telefone, linha);

        fgets(linha, sizeof(linha), file);
        linha[strcspn(linha, "\n")] = '\0';
        sscanf(linha, "%d/%d/%d", &novo->aniversario.dia, &novo->aniversario.mes, &novo->aniversario.ano);

        novo->prox = NULL;

        if (pt_head == NULL)
        {
            pt_head = novo;
        }
        else
        {
            CONTATO *pt_aux = pt_head;
            while (pt_aux->prox != NULL)
            {
                pt_aux = pt_aux->prox;
            }
            pt_aux->prox = novo;
        }
    }

    fclose(file);
    printf("**Contatos carregados com sucesso do arquivo %s.\n", nome_arquivo);
    return pt_head;
}

void print_contatos(CONTATO *pt_head)
{
    CONTATO *pt_aux = NULL;
    int pos = 1;
    pt_aux = pt_head;

    while (pt_aux != NULL)
    {
        printf("%d - %s", pos, pt_aux->nome);
        printf("%s", pt_aux->telefone);
        printf("\n%02d/%02d/%04d", pt_aux->aniversario.dia, pt_aux->aniversario.mes, pt_aux->aniversario.ano);
        puts("\n");
        pt_aux = pt_aux->prox;
        pos++;
    }
}

void adicionar_contato(CONTATO **contatos)
{
    CONTATO *aux;
    CONTATO *novo = (CONTATO *)malloc(sizeof(CONTATO));

    time_t agora = time(NULL);
    struct tm *dataAtual = localtime(&agora);

    if (novo)
    {
        puts("Qual é o nome do contato?");
        printf("> ");
        fgets(novo->nome, 50, stdin);

        puts("Qual é o telefone? Digite no formato (xx)9xxxx-xxxx");
        printf("> ");
        fgets(novo->telefone, 15, stdin);

        limpar_buffer_entrada();
        puts("Qual é a data de aniversário? Digite no formato dd/mm/aaaa");
        printf("> ");
        scanf("%d/%d/%d", &novo->aniversario.dia, &novo->aniversario.mes, &novo->aniversario.ano);

        while ((novo->aniversario.dia > 31 || novo->aniversario.dia < 0) || (novo->aniversario.mes > 12 || novo->aniversario.mes < 1) || (novo->aniversario.ano > (dataAtual->tm_year + 1900) || novo->aniversario.ano < 0))
        {
            printf("\n");
            puts("A data digitada é invalida, por favor tente novamente");
            puts("Qual é a data de aniversário? Digite no formato dd/mm/aaaa");
            printf("> ");
            scanf("%d/%d/%d", &novo->aniversario.dia, &novo->aniversario.mes, &novo->aniversario.ano);
        }

        while (novo->aniversario.ano > (dataAtual->tm_year + 1900) || (novo->aniversario.ano == (dataAtual->tm_year + 1900) && novo->aniversario.mes > (dataAtual->tm_mon + 1)) || (novo->aniversario.ano == (dataAtual->tm_year + 1900) && novo->aniversario.mes == (dataAtual->tm_mon + 1) && novo->aniversario.dia > dataAtual->tm_mday))
        {
            printf("\n");
            puts("A data digitada é invalida, por favor tente novamente");
            puts("Qual é a data de aniversário? Digite no formato dd/mm/aaaa");
            printf("> ");
            scanf("%d/%d/%d", &novo->aniversario.dia, &novo->aniversario.mes, &novo->aniversario.ano);
        }

        novo->prox = NULL;

        if (*contatos == NULL)
        {
            *contatos = novo;
        }
        else
        {
            aux = *contatos;
            while (aux->prox != NULL)
            {
                aux = aux->prox;
            }
            aux->prox = novo;
        }
    }
    else
    {
        printf("Erro ao alocar memoria!");
    }
}

void remover_contato(CONTATO **pt_head)
{
    CONTATO *pt_atual = *pt_head;
    CONTATO *pt_anterior = NULL;
    int pos, counter;

    puts("Qual é a posição do contato que deseja remover?");
    printf("> ");
    scanf("%d", &pos);
    limpar_buffer_entrada();

    if (pos <= 0)
    {
        printf("Posição inválida.\n");
        return;
    }

    counter = 1;

    while (pt_atual != NULL && counter != pos)
    {
        pt_anterior = pt_atual;
        pt_atual = pt_atual->prox;
        counter++;
    }

    if (pt_atual != NULL)
    {
        if (pt_anterior == NULL)
        {
            *pt_head = pt_atual->prox;
        }
        else
        {
            pt_anterior->prox = pt_atual->prox;
        }
        free(pt_atual);
        printf("Contato removido com sucesso!\n");
    }
    else
    {
        printf("Posição inválida. Contato não encontrado.\n");
    }
}

void sort_lista_contatos(CONTATO **pt_head)
{
    CONTATO *pt_atual, *pt_temp, *pt_antes;
    int trocados = 1;

    while (trocados)
    {
        trocados = 0;
        pt_atual = *pt_head;
        pt_antes = NULL;

        while (pt_atual != NULL && pt_atual->prox != NULL)
        {
            pt_temp = pt_atual->prox;

            if (strcmp(pt_atual->nome, pt_temp->nome) > 0)
            {
                trocados = 1;
                pt_atual->prox = pt_temp->prox;
                pt_temp->prox = pt_atual;

                if (pt_antes == NULL)
                {
                    *pt_head = pt_temp;
                }
                else
                {
                    pt_antes->prox = pt_temp;
                }

                pt_antes = pt_temp;
            }
            else
            {
                pt_antes = pt_atual;
                pt_atual = pt_atual->prox;
            }
        }
    }
}

void print_contatos_by_name(CONTATO *pt_head)
{
    int pos = 1, achados = 0, i;
    char nome[51], nome_cmp[51];
    CONTATO *pt_aux = pt_head;

    puts("Qual nome você quer procurar?");
    printf("> ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    while (pt_aux != NULL)
    {
        strcpy(nome_cmp, pt_aux->nome);
        nome_cmp[strcspn(pt_aux->nome, "\n")] = '\0';

        for (i = 0; nome_cmp[i]; i++)
        {
            if (nome_cmp[i] >= 65 && nome_cmp[i] <= 90)
            {
                nome_cmp[i] = (nome_cmp[i] + 32);
            }
        }
        for (i = 0; nome[i]; i++)
        {
            if (nome[i] >= 65 && nome[i] <= 90)
            {
                nome[i] = (nome[i] + 32);
            }
        }

        if (strstr(nome_cmp, nome) != NULL)
        {
            achados++;
            printf("%d - %s", pos, pt_aux->nome);
            printf("%s", pt_aux->telefone);
            printf("\n%02d/%02d/%04d", pt_aux->aniversario.dia, pt_aux->aniversario.mes, pt_aux->aniversario.ano);
            puts("\n");
        }

        pt_aux = pt_aux->prox;
        pos++;
    }
    if (achados == 0)
        printf("Não existe ninguém com esse nome na sua lista de contatos.\n");
}

void print_contatos_by_letter(CONTATO *pt_head)
{
    int pos = 1, achados = 0;
    char letra;
    CONTATO *pt_aux = pt_head;

    puts("Qual letra você quer procurar?");
    printf("> ");
    letra = getc(stdin);

    while (pt_aux != NULL)
    {
        if (pt_aux->nome[0] == letra || pt_aux->nome[0] == (letra + 32) || pt_aux->nome[0] == (letra - 32))
        {
            achados++;
            printf("%d - %s", pos, pt_aux->nome);
            printf("%s", pt_aux->telefone);
            printf("\n%02d/%02d/%04d", pt_aux->aniversario.dia, pt_aux->aniversario.mes, pt_aux->aniversario.ano);
            puts("\n");
        }

        pt_aux = pt_aux->prox;
        pos++;
    }
    if (achados == 0)
        printf("Não existe ninguém com essa inicial na sua lista de contatos.\n");
}

void print_birthdays(CONTATO *pt_head)
{
    int achados = 0, mes_atual;
    CONTATO *pt_aux = pt_head;
    time_t agora;
    struct tm *dataAtual;

    time(&agora);
    dataAtual = localtime(&agora);
    mes_atual = dataAtual->tm_mon + 1;

    while (pt_aux != NULL)
    {
        if (pt_aux->aniversario.mes == mes_atual)
        {
            achados++;
            printf("%s", pt_aux->nome);
            printf("%s", pt_aux->telefone);
            printf("\n%02d/%02d/%04d", pt_aux->aniversario.dia, pt_aux->aniversario.mes, pt_aux->aniversario.ano);
            puts("\n");
        }

        pt_aux = pt_aux->prox;
    }
    if (achados == 0)
        printf("Ninguém faz aniversário este mês.\n");
}

void limpar_buffer_entrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}