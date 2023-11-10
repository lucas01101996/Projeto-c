#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef int TIPOCHAVE;

enum desc_ocorrencia {Esqueceu=1, Perdeu, NaoPossui, Outros};

typedef struct {
    int dia;
    int mes;
    int ano;
} dataRef;

typedef struct {
    dataRef dataAcesso; // Data de Acesso
    char nomePorteiro[200]; // Nome Porteiro
} dadosHeaderf;

typedef struct {
    TIPOCHAVE chave; // Controle ID
    char nome[40];
    enum desc_ocorrencia ocorrencia; // Descrição da Ocorrência (Esqueceu/Perdeu/NaoPossui/Outros cartão)
    char TipoOcorrencia[10];
} Acesso;

typedef struct {
    Acesso A[MAX];
    int nroElem;
} Lista;

typedef struct {
    char nome[40];
} aluno;

void cadastrarAluno(Lista *lista);
void exibirElementos(Lista *lista);
void consultar(Lista *lista);
int verificarTamanho(Lista *lista);
void alterar(Lista *lista);
void excluir(Lista *lista);

//meotedos auxiliares
const char *getNomeOcorrencia(enum desc_ocorrencia ocorrencia);


int main() {
    int opcao;
    Lista lista;
    lista.nroElem = 0;

    do {
        printf("\n\n ---------- Menu Principal -----------------\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Exibir Alunos\n");
        printf("3. Consultar Aluno\n");
        printf("4. Verificar Tamanho\n");
        printf("5. Alterar Acesso do aluno\n");
        printf("6. Excluir acesso do aluno\n");
        printf("7. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
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
                if(lista.nroElem ==0){
                    printf("Nao existe aluno no sistema");                                                         
                }else{
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
                printf("Saindo do programa. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 5);

    return 0;
}

void cadastrarAluno(Lista *lista) {
    if (lista->nroElem < MAX) {
        printf("\n\n ---------- Cadastro de aluno -----------------\n\n\n");
        printf("Nome do aluno...........:");
        fflush(stdin);
        fgets(lista->A[lista->nroElem].nome, 40, stdin);

        printf("Ocorrência (1- Esqueceu/ 2 -Perdeu/ 3 -NaoPossui 4-Outros): ");
        scanf("%d", &lista->A[lista->nroElem].ocorrencia);

        // Outras informações podem ser adicionadas conforme necessário

        lista->nroElem++;
        printf("Aluno cadastrado com sucesso!\n");
    } else {
        printf("A lista está cheia. Não é possível cadastrar mais alunos.\n");
    }
}

void exibirElementos(Lista *lista) {
    printf("\n\n ---------- Lista de Alunos -----------------\n\n\n");
    int i;
    if(lista->nroElem==0){
         printf("Nao existe aluno no sistema");                                     
    }                     
    for ( i = 0; i < lista->nroElem; i++) {
        printf("Nome do aluno: %s\n", lista->A[i].nome);
        printf("Ocorrencia: %d\n", getNomeOcorrencia(lista->A[i].ocorrencia));
        // Exibir outras informações conforme necessário
        printf("\n");
    }
}

void consultar(Lista *lista) {
    char nomeConsulta[40];
    int i;
    printf("Digite o nome do aluno para consultar: ");
    fflush(stdin);
    fgets(nomeConsulta, 40, stdin);

    for (i = 0; i < lista->nroElem; i++) {
        if (strcmp(nomeConsulta, lista->A[i].nome) == 0) {
            printf("\n\n ---------- Informações do Aluno -----------------\n\n\n");
            printf("Nome do aluno: %s\n", lista->A[i].nome);
            printf("Ocorrência: %d\n", lista->A[i].ocorrencia);
            // Exibir outras informações conforme necessário
            return;
        }
    }

    printf("Aluno nao encontrado.\n");
}

int verificarTamanho(Lista *lista) {
    if(lista->nroElem>1){
      printf("Existem %d alunos cadastrados no sistema\n",lista->nroElem);                   
    }else{
      printf("Existe %d aluno cadastrado no sistema\n",lista->nroElem);    
    }
    return lista->nroElem;
}

void alterar(Lista *lista) {
    char nomeConsulta[40];
    printf("Digite o nome do aluno para editar: ");
    fflush(stdin);
    fgets(nomeConsulta, 40, stdin);
    int i; 
    for (i= 0; i < lista->nroElem; i++) {
        if (strcmp(nomeConsulta, lista->A[i].nome) == 0) {
            printf("\n\n ---------- Editar Informações do Aluno -----------------\n\n\n");
            printf("Nome do aluno (anterior): %s\n", lista->A[i].nome);

            printf("Novo nome do aluno: ");
            fflush(stdin);
            fgets(lista->A[i].nome, 40, stdin);

            printf("Ocorrência (anterior): %d\n", lista->A[i].ocorrencia);
            printf("Nova ocorrência (Esqueceu/Perdeu/NaoPossui/Outros): ");
            scanf("%d", &lista->A[i].ocorrencia);

            // Outras informações podem ser editadas conforme necessário

            printf("Informações do aluno editadas com sucesso!\n");
            return;
        }
    }

    printf("Aluno nao encontrado.\n");
}

void excluir(Lista *lista) {
    char nomeConsulta[40];
    printf("Digite o nome do aluno para excluir: ");
    fflush(stdin);
    fgets(nomeConsulta, 40, stdin);
    int i;
    for ( i = 0; i < lista->nroElem; i++) {
        if (strcmp(nomeConsulta, lista->A[i].nome) == 0) {
            // Remover o aluno da lista movendo os elementos restantes
            int j;
            for ( j= i; j < lista->nroElem - 1; j++) {
                strcpy(lista->A[j].nome, lista->A[j + 1].nome);
                lista->A[j].ocorrencia = lista->A[j + 1].ocorrencia;
                // Copie outras informações conforme necessário
            }

            lista->nroElem--;
            printf("Aluno removido com sucesso!\n");
            return;
        }
    }

    printf("Aluno nao encontrado.\n");
}

const char *getNomeOcorrencia(enum desc_ocorrencia ocorrencia) {
    switch (ocorrencia) {
        case Esqueceu:
            return "Esqueceu";
        case Perdeu:
            return "Perdeu";
        case NaoPossui:
            return "NaoPossui";
        case Outros:
            return "Outros";
        default:
            return "Desconhecido";
     }
}

