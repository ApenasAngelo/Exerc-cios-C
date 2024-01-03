#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

typedef struct _REGISTRO
{
    int vendedor_code, mes;
    float valor_venda;
    char nome[51];
    struct _REGISTRO *prox;
} REGISTRO;

FILE *criar_arquivo(char *nome_arquivo);
void adicionar_registro(REGISTRO **registros);
void remover_registro(REGISTRO **pt_head);
void sort_lista_registro(REGISTRO **pt_head);
void alterar_registro(REGISTRO **pt_head);
void print_registro(REGISTRO *pt_head);
FILE *excluir_registro(char *nome_arquivo, FILE *arquivo);
int finalizar(REGISTRO *pt_head, FILE *arquivo);
void limpar_buffer_entrada();

int main(void)
{
    int opcao, sair;
    char nome_arquivo[101];
    REGISTRO *pt_head = NULL;
    FILE *arquivo = NULL, *temp = NULL;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    while (1)
    {
        puts("-------Menu-------");
        puts("1: Criar o arquivo de dados.");
        puts("2: Incluir um registro.");
        puts("3: Excluir um vendedor.");
        puts("4: Alterar um valor de venda.");
        puts("5: Imprimir os registros na saída.");
        puts("6: Excluir o arquivo de dados.");
        puts("7: Sair");
        printf("> ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            puts("------------------");
            puts("Qual é o nome do arquivo?");
            printf("> ");
            fgets(nome_arquivo, 100, stdin);
            arquivo = criar_arquivo(nome_arquivo);
            break;

        case 2:
            puts("------------------");
            adicionar_registro(&pt_head);
            sort_lista_registro(&pt_head);
            puts("");
            break;

        case 3:
            puts("------------------");
            print_registro(pt_head);
            remover_registro(&pt_head);
            puts("");
            break;

        case 4:
            puts("------------------");
            print_registro(pt_head);
            alterar_registro(&pt_head);
            break;

        case 5:
            puts("------------------");
            print_registro(pt_head);
            break;

        case 6:
            puts("------------------");
            temp = excluir_registro(nome_arquivo, arquivo);
            if (temp == NULL)
                arquivo = temp;
            puts("");
            break;

        case 7:
            sair = finalizar(pt_head, arquivo);
            if (sair == 0)
                return 0;
            break;

        default:
            puts("------------------");
            puts("Valor inválido, tente outro por favor.");
            break;

            return 0;
        }
    }

    return 0;
}

FILE *criar_arquivo(char *nome_arquivo)
{
    FILE *arquivo;
    char option;

    nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';

    arquivo = fopen(nome_arquivo, "r");
    if (arquivo != NULL)
    {
        fclose(arquivo);
        puts("O arquivo já existe, deseja sobreescrever o conteudo? (Y/N)");
        printf("> ");
        option = getchar();
        getchar();
        if (option == 'N' || option == 'n')
            exit(1);
    }

    arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL)
    {
        puts("Não foi possivel criar o arquivo.");
        exit(1);
    }

    puts("Arquivo criado com sucesso.");
    return arquivo;
}

void adicionar_registro(REGISTRO **registros)
{
    REGISTRO *pt_aux, *pt_cmp = *registros;
    REGISTRO *novo = (REGISTRO *)malloc(sizeof(REGISTRO));
    int counter = 0;

    if (novo)
    {
        puts("Qual é o código do vendedor? (Até 6 digitos)");
        printf("> ");
        scanf("%d", &novo->vendedor_code);
        limpar_buffer_entrada();

        puts("Qual é o nome?");
        printf("> ");
        fgets(novo->nome, 50, stdin);
        /*limpar_buffer_entrada();*/

        puts("Qual é o valor da venda? Digite apenas o valor (xxx.xx)");
        printf("> ");
        scanf("%f", &novo->valor_venda);

        while (novo->valor_venda < 0)
        {
            printf("\n");
            puts("O valor digitado é invalido, por favor tente novamente.");
            puts("Qual é o valor da venda? Digite apenas o valor (xxx.xx)");
            printf("> ");
            scanf("%f", &novo->valor_venda);
        }
        /*limpar_buffer_entrada();*/

        puts("Qual é o mês?");
        printf("> ");
        scanf("%d", &novo->mes);

        while (novo->mes > 12 || novo->mes < 1)
        {
            printf("\n");
            puts("O mês digitado é invalido, por favor tente novamente.");
            puts("Qual é o mês?");
            printf("> ");
            scanf("%d", &novo->mes);
        }

        while (pt_cmp != NULL)
        {
            if (novo->vendedor_code == pt_cmp->vendedor_code && novo->mes == pt_cmp->mes)
            {
                counter++;
            }
            pt_cmp = pt_cmp->prox;
        }

        if (counter > 0)
        {
            puts("Não é possível adicionar um registro com o mesmo código e mês.");
            return;
        }

        novo->prox = NULL;

        if (*registros == NULL)
        {
            *registros = novo;
        }
        else
        {
            pt_aux = *registros;
            while (pt_aux->prox != NULL)
            {
                pt_aux = pt_aux->prox;
            }
            pt_aux->prox = novo;
        }
    }
    else
    {
        printf("Erro ao alocar memoria!");
    }
}

void remover_registro(REGISTRO **pt_head)
{
    REGISTRO *pt_atual = *pt_head;
    REGISTRO *pt_anterior = NULL;
    int pos, counter;

    puts("Qual é a posição do registro que deseja remover?");
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
        puts("Registro removido com sucesso!");
    }
    else
    {
        puts("Posição inválida. Registro não encontrado.");
    }
}

void sort_lista_registro(REGISTRO **pt_head)
{
    REGISTRO *pt_atual, *pt_temp, *pt_antes;
    int trocados = 1;

    while (trocados)
    {
        trocados = 0;
        pt_atual = *pt_head;
        pt_antes = NULL;

        while (pt_atual != NULL && pt_atual->prox != NULL)
        {
            pt_temp = pt_atual->prox;

            if (pt_atual->vendedor_code > pt_temp->vendedor_code)
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
            else if ((pt_atual->vendedor_code == pt_temp->vendedor_code) && pt_atual->mes > pt_temp->mes)
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

void alterar_registro(REGISTRO **pt_head)
{
    REGISTRO *pt_atual = *pt_head;
    int pos, counter;
    float novo_valor;

    puts("Qual é a posição do registro que deseja alterar?");
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
        pt_atual = pt_atual->prox;
        counter++;
    }

    if (pt_atual != NULL)
    {
        puts("Qual é o valor da venda? Digite apenas o valor (xxx.xx)");
        printf("> ");
        scanf("%f", &novo_valor);

        while (novo_valor < 0)
        {
            printf("\n");
            puts("O valor digitado é invalido, por favor tente novamente.");
            puts("Qual é o valor da venda? Digite apenas o valor (xxx.xx)");
            printf("> ");
            scanf("%f", &novo_valor);
        }

        pt_atual->valor_venda = novo_valor;
    }
    else
    {
        puts("Posição inválida.");
    }
}

void print_registro(REGISTRO *pt_head)
{
    REGISTRO *pt_aux = NULL;
    int pos = 1;
    pt_aux = pt_head;

    while (pt_aux != NULL)
    {
        pt_aux->nome[strcspn(pt_aux->nome, "\n")] = '\0';

        printf("%d - %s / %06d", pos, pt_aux->nome, pt_aux->vendedor_code);
        printf("\nValor de venda = R$%.2f", pt_aux->valor_venda);
        printf("\nMês = %02d", pt_aux->mes);
        puts("\n");
        pt_aux = pt_aux->prox;
        pos++;
    }
}

FILE *excluir_registro(char *nome_arquivo, FILE *arquivo)
{
    int excluir;
    char option;
    FILE *arquivo_teste;

    arquivo_teste = fopen(nome_arquivo, "r");
    if (arquivo_teste != NULL)
    {
        fclose(arquivo_teste);
        puts("Deseja realmente apagar o arquivo? (Y/N)");
        printf("> ");
        option = getchar();
        getchar();
        if (option == 'N' || option == 'n')
            return arquivo;

        fclose(arquivo);
        nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';
        excluir = remove(nome_arquivo);

        if (excluir == 0)
        {
            puts("O arquivo foi deletado.");
            arquivo = NULL;
            return arquivo;
        }
        else
        {
            perror("Não foi possivel deletar o arquivo.");
            return arquivo;
        }
    }
    else
    {
        puts("Nenhum arquivo para apagar.");
        return NULL;
    }
}

int finalizar(REGISTRO *pt_head, FILE *arquivo)
{
    REGISTRO *pt_aux = pt_head;
    char option;
    char vendedor_code[12], mes[12], valor_venda[20];

    if (arquivo == NULL)
    {
        puts("Nenhum arquivo foi criado, o conteúdo não será salvo.");
        puts("Deseja prosseguir? (Y/N)");
        printf("> ");
        option = getchar();
        getchar();
        if (option == 'N' || option == 'n')
            return 1;
        else
            return 0;
    }

    while (pt_aux != NULL)
    {
        pt_aux->nome[strcspn(pt_aux->nome, "\n")] = '\0';
        sprintf(vendedor_code, "%06d", pt_aux->vendedor_code);
        sprintf(mes, "%02d", pt_aux->mes);
        sprintf(valor_venda, "%.2f", pt_aux->valor_venda);

        fwrite(pt_aux->nome, sizeof(char), strlen(pt_aux->nome), arquivo);
        fwrite("\n", sizeof(char), 1, arquivo);
        fwrite(vendedor_code, sizeof(char), strlen(vendedor_code), arquivo);
        fwrite("\n", sizeof(char), 1, arquivo);
        fwrite(valor_venda, sizeof(char), strlen(valor_venda), arquivo);
        fwrite("\n", sizeof(char), 1, arquivo);
        fwrite(mes, sizeof(char), strlen(mes), arquivo);
        fwrite("\n", sizeof(char), 1, arquivo);
        fwrite("\n", sizeof(char), 1, arquivo);
        pt_aux = pt_aux->prox;
    }

    fclose(arquivo);
    printf("Registros salvos com sucesso.\n");
    return 0;
}

void limpar_buffer_entrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}