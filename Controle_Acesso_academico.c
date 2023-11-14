#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef int TIPOCHAVE;

enum desc_ocorrencia
{
    Esqueceu = 1,
    Perdeu = 2,
    NaoPossui = 3,
    Outros = 4,
};

typedef struct
{
    int dia;
    int mes;
    int ano;
} dataRef;

typedef struct
{
    dataRef dataAcesso;     // Data de Acesso
    char nomePorteiro[200]; // Nome Porteiro
} dadosHeaderf;

typedef struct
{
    TIPOCHAVE chave; // Controle ID
    char nome[40];
    enum desc_ocorrencia ocorrencia; // Descri��o da Ocorr�ncia (Esqueceu/Perdeu/NaoPossui/Outros cart�o)
    char TipoOcorrencia[10];
} Acesso;

typedef struct
{
    Acesso A[MAX];
    int nroElem;
} Lista;

typedef struct
{
    char nome[40];
} aluno;

// metodos principais
void cadastrarAluno(Lista *lista);
void exibirElementos(Lista *lista);
void consultar(Lista *lista);
int verificarTamanho(Lista *lista);
void alterar(Lista *lista);
void excluir(Lista *lista);
void excluirTudo(Lista *lista);
void salvarDados(Lista *lista, const char *nomeArquivo);
void carregarDados(Lista *lista, const char *nomeArquivo);

// metodos auxiliares
const char *getNomeOcorrencia(enum desc_ocorrencia ocorrencia);

int main()
{
    int opcao, arquivo;
    Lista lista;
    lista.nroElem = 0;

    printf("1 - Novo Arquivo\n");
    printf("2 - Carregar Arquivo\n");

    scanf("%d", &arquivo);
    if (arquivo == 2)
    {
        carregarDados(&lista, "dados.txt");
    }

    do
    {
        printf("\n\n ---------- Menu Principal -----------------\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Exibir Alunos\n");
        printf("3. Consultar Aluno\n");
        printf("4. Verificar Tamanho\n");
        printf("5. Alterar Acesso do aluno\n");
        printf("6. Excluir acesso do aluno\n");
        printf("7. Excluir todos os registros\n");
        printf("8. Salvar Dados\n");
        printf("9. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarAluno(&lista);
            break;
        case 2:
            exibirElementos(&lista);
            break;
        case 3:
            consultar(&lista);
            break;
        case 4:
            if (lista.nroElem == 0)
            {
                printf("Nao existe aluno no sistema");
            }
            else
            {
                verificarTamanho(&lista);
            }
            break;
        case 5:
            alterar(&lista);
            break;
        case 6:
            excluir(&lista);
            break;
        case 7:
            excluirTudo(&lista);
            break;
        case 8:
            salvarDados(&lista, "dados.txt");
            break;
        case 9:
            printf("Saindo do programa. Ate logo!\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 9);

    return 0;
}

void cadastrarAluno(Lista *lista)
{
    if (lista->nroElem < MAX)
    {
        printf("\n\n ---------- Cadastro de aluno -----------------\n\n\n");
        printf("Nome do aluno...........:");
        fflush(stdin);
        fgets(lista->A[lista->nroElem].nome, 40, stdin);

        printf("Ocorr�ncia (1- Esqueceu/ 2 -Perdeu/ 3 -NaoPossui 4-Outros): ");
        scanf("%d", &lista->A[lista->nroElem].ocorrencia);

        lista->nroElem++;
        printf("Aluno cadastrado com sucesso!\n");
    }
    else
    {
        printf("A lista est� cheia. N�o � poss�vel cadastrar mais alunos.\n");
    }
}

void exibirElementos(Lista *lista)
{
    printf("\n\n ---------- Lista de Alunos -----------------\n\n\n");
    int i;
    if (lista->nroElem == 0)
    {
        printf("Nao existe aluno no sistema");
    }
    for (i = 0; i < lista->nroElem; i++)
    {
        printf("Nome do aluno: %s\n", lista->A[i].nome);
        printf("Ocorrencia: %s\n", getNomeOcorrencia(lista->A[i].ocorrencia));
        printf("\n");
    }
}

void consultar(Lista *lista)
{
    char nomeConsulta[40];
    int i;
    printf("Digite o nome do aluno para consultar: ");
    fflush(stdin);
    fgets(nomeConsulta, 40, stdin);

    for (i = 0; i < lista->nroElem; i++)
    {
        if (strcmp(nomeConsulta, lista->A[i].nome) == 0)
        {
            printf("\n\n ---------- Informa��es do Aluno -----------------\n\n\n");
            printf("Nome do aluno: %s\n", lista->A[i].nome);
            printf("Ocorr�ncia: %s\n", lista->A[i].ocorrencia);
            return;
        }
    }

    printf("Aluno nao encontrado.\n");
}

int verificarTamanho(Lista *lista)
{
    if (lista->nroElem > 1)
    {
        printf("Existem %d alunos cadastrados no sistema\n", lista->nroElem);
    }
    else
    {
        printf("Existe %d aluno cadastrado no sistema\n", lista->nroElem);
    }
    return lista->nroElem;
}

void alterar(Lista *lista)
{
    char nomeConsulta[40];
    int i;
    printf("Digite o nome do aluno para editar: ");
    fflush(stdin);
    fgets(nomeConsulta, 40, stdin);

    for (i = 0; i < lista->nroElem; i++)
    {
        if (strcmp(nomeConsulta, lista->A[i].nome) == 0)
        {
            printf("\n\n ---------- Editar Informa��es do Aluno -----------------\n\n\n");
            printf("Nome do aluno (anterior): %s\n", lista->A[i].nome);

            printf("Novo nome do aluno: ");
            fflush(stdin);
            fgets(lista->A[i].nome, 40, stdin);

            printf("Ocorr�ncia (anterior): %d\n", lista->A[i].ocorrencia);
            printf("Nova ocorr�ncia (Esqueceu/Perdeu/NaoPossui/Outros/MalUso/Desgastado): ");
            scanf("%d", &lista->A[i].ocorrencia);

            printf("Informa��es do aluno editadas com sucesso!\n");
            return;
        }
    }

    printf("Aluno nao encontrado.\n");
}

void excluir(Lista *lista)
{
    char nomeConsulta[40];
    printf("Digite o nome do aluno para excluir: ");
    fflush(stdin);
    fgets(nomeConsulta, 40, stdin);
    int i;
    for (i = 0; i < lista->nroElem; i++)
    {
        if (strcmp(nomeConsulta, lista->A[i].nome) == 0)
        {
            // Remover o aluno da lista movendo os elementos restantes
            int j;
            for (j = i; j < lista->nroElem - 1; j++)
            {
                strcpy(lista->A[j].nome, lista->A[j + 1].nome);
                lista->A[j].ocorrencia = lista->A[j + 1].ocorrencia;
            }

            lista->nroElem--;
            printf("Aluno removido com sucesso!\n");
            return;
        }
    }

    printf("Aluno nao encontrado.\n");
}

void excluirTudo(Lista *lista)
{
    lista->nroElem = 0;
    printf("----------- Todos os alunos foram excluidos do sistemas --------------\n");
}

const char *getNomeOcorrencia(enum desc_ocorrencia ocorrencia)
{
    switch (ocorrencia)
    {
    case 1:
    Esqueceu:
        return "Esqueceu";
    case 2:
    Perdeu:
        return "Perdeu";
    case 3:
    NaoPossui:
        return "NaoPossui";
    case 4:
    Outros:
        return "Outros";
    default:
        return "Desconhecido";
    }
}

void salvarDados(Lista *lista, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo para salvar");
        return;
    }

    fwrite(lista, sizeof(Lista), 1, arquivo);

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

void carregarDados(Lista *lista, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo para carregar");
        return;
    }

    fread(lista, sizeof(Lista), 1, arquivo);

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}