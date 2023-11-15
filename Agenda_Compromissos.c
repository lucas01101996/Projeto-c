#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_DATA 40
#define MAX 40
typedef int TIPOCHAVE;

typedef struct
{
  int dia;
  int mes;
  int ano;
} DataRef;

typedef struct
{
  TIPOCHAVE chave;                // Controle ID
  DataRef dataCompromisso;        // Data Compromisso
  char descricaoCompromisso[300]; // Descrição
} Agenda;

typedef struct
{
  Agenda A[40];
  int topo;
} Pilha;

typedef struct
{
  Agenda A[40];
  int nroElem;
} Lista;

void novoCompromisso(Pilha *pilha, Lista *lista);
int passouData(DataRef *dataRef);
void exibirElementos(Lista *lista);
void consultar(Lista *lista);
void alterar(Lista *lista);
void excluir(Lista *lista);
void salvarDados(Lista *lista, const char *nomeArquivo);
void carregarDados(Lista *lista, const char *nomeArquivo);
void desempilharParaLista(Pilha *pilha, Lista *lista);

int main()
{
  DataRef dataRef[MAX_DATA];
  int opcao, arquivo;
  Lista lista;
  lista.nroElem = 0;
  Pilha pilha;
  pilha.topo = 0;
  
    printf("1 - Novo Arquivo\n");
    printf("2 - Carregar Arquivo\n");

    scanf("%d", &arquivo);
    if (arquivo == 2)
    {
        carregarDados(&lista, "agenda.txt");
    }
  do
  {
    printf("\n\n ---------- Menu Principal -----------------\n");
    printf("1. Novo Compromisso\n");
    printf("2. Exibir Agenda\n");
    printf("3. Consultar Agenda\n");
    printf("4. Alterar Agenda\n");
    printf("5. Excluir Agenda\n");
    printf("6. Salvar resgistros\n");
    printf("7. Sair\n");

    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
      novoCompromisso(&pilha, &lista);
      break;
    case 2:
      exibirElementos(&lista);
      break;
    case 3:
      consultar(&lista);
      break;
    case 4:
      alterar(&lista);
      break;
    case 5:
       excluir(&lista);
      break;
   case 6:
      salvarDados(&lista, "agenda.txt");
      break;
    case 7:
      printf("Saindo do programa. Ate logo!\n");
      break;
    default:
      printf("Opcao invalida. Tente novamente.\n");
    }

  } while (opcao != 7);

  return 0;
}

void novoCompromisso(Pilha *pilha, Lista *lista)
{
  DataRef tempData;
  if (pilha->topo < MAX)
  {
    printf("\n\n ---------- Novo Compromisso -----------------\n\n\n");
    printf("Digite a data do Compromisso no formato(dd mm yyyy)...........:");
    
    scanf("%d %d %d", &tempData.dia, &tempData.mes, &tempData.ano);
    if (passouData(&tempData))
    {
      printf("Data solicitada ja passou.\n");
    }
    else
    {
//      scanf("%d %d %d", &pilha->A[pilha->topo].dataCompromisso.dia, &pilha->A[pilha->topo].dataCompromisso.mes, &pilha->A[pilha->topo].dataCompromisso.ano);
	  pilha->A[pilha->topo].dataCompromisso = tempData;

	  printf("Descreva o tipo do Compromisso(Sem espacos): ");
      scanf("%s", pilha->A[pilha->topo].descricaoCompromisso);
      pilha->topo++;

      printf("Compromisso cadastrado com sucesso!\n");
    }
  }
  else
  {
    printf("A pilha esta cheia. Nao eh possivel cadastrar mais compromissos.\n");
  }
  desempilharParaLista(pilha, lista);
}

int passouData(DataRef *dataRef)
{
  time_t dataAtual;
  struct tm *info;
  time(&dataAtual);
  info = localtime(&dataAtual);

  printf("Data atual: %02d/%02d/%04d\n", info->tm_mday, info->tm_mon + 1, info->tm_year + 1900);

  if (dataRef->ano < info->tm_year + 1900)
  {
    return 1;
  }
  else if (dataRef->ano == info->tm_year + 1900)
  {
    if (dataRef->mes < info->tm_mon + 1)
    {
      return 1;
    }
    else if (dataRef->mes == info->tm_mon + 1)
    {
      if (dataRef->dia < info->tm_mday)
      {
        return 1;
      }
    }
  }

  return 0;
}

void exibirElementos(Lista *lista)
{
  printf("\n\n ---------- Lista de Compromissos -----------------\n\n\n");
  int i;
  if (lista->nroElem == 0)
  {
    printf("Nao existe Agenda.");
  }
  for (i = 0; i < lista->nroElem; i++)
  {
    printf(" A data agendada eh: %d %d %d\n", lista->A[i].dataCompromisso.dia, lista->A[i].dataCompromisso.mes, lista->A[i].dataCompromisso.ano );
    printf("Descricao: %s\n", lista->A[i].descricaoCompromisso);
    printf("\n");
  }
}

void consultar(Lista *lista)
{
  DataRef tempData;
  int i;
  printf("Digite a data Agendada no formato(dd mm yyyy): ");
 scanf("%d %d %d", &tempData.dia, &tempData.mes, &tempData.ano);

  for (i = 0; i < lista->nroElem; i++)
  {
    if (tempData.ano == lista->A[i].dataCompromisso.ano){ 
		if (tempData.mes == lista->A[i].dataCompromisso.mes){
			if (tempData.dia == lista->A[i].dataCompromisso.dia){
     		printf("\n\n ---------- Informacoes do Agenda -----------------\n\n\n");
     		printf("Data Agendada: %d %d %d\n", lista->A[i].dataCompromisso.ano, lista->A[i].dataCompromisso.mes, lista->A[i].dataCompromisso.dia);
      		printf("Descricao: %s\n", lista->A[i].descricaoCompromisso);
      		return;
      		}
  		}
    }
  }

  printf("Data nao Agendada.\n");
}
void alterar(Lista *lista){
  DataRef tempData;
  int i;
  printf("Digite a data a ser Alterada no formato(dd mm yyyy): ");
 scanf("%d %d %d", &tempData.dia, &tempData.mes, &tempData.ano);

  for (i = 0; i < lista->nroElem; i++)  {
  	if (tempData.ano == lista->A[i].dataCompromisso.ano){ 
		if (tempData.mes == lista->A[i].dataCompromisso.mes){
			if (tempData.dia == lista->A[i].dataCompromisso.dia){
			  printf("Digite a Nova Data no formato(dd mm yyyy)...........:");
    		  scanf("%d %d %d", &tempData.dia, &tempData.mes, &tempData.ano);
    		  if (passouData(&tempData))	{
      			printf("Data solicitada ja passou.\n");
   			  }else    {
	  			lista->A[i].dataCompromisso = tempData;

	  			printf("Digite o Novo do Compromisso(Sem espacos): ");
     			scanf("%s", lista->A[i].descricaoCompromisso);

     			 printf("Compromisso Alterado com sucesso!\n");
    			}	
			}
  		}
 	}
  }
}

void excluir(Lista *lista){
	  DataRef tempData;
  int i;
  printf("Digite a data a ser Excluida no formato(dd mm yyyy): ");
 scanf("%d %d %d", &tempData.dia, &tempData.mes, &tempData.ano);

  for (i = 0; i < lista->nroElem; i++)  {
  	if (tempData.ano == lista->A[i].dataCompromisso.ano){ 
		if (tempData.mes == lista->A[i].dataCompromisso.mes){
			if (tempData.dia == lista->A[i].dataCompromisso.dia){
				int j;
				for (j = i; j < lista->nroElem - 1; j++){
				
				lista->A[j].dataCompromisso = lista->A[j + 1].dataCompromisso;

     			strcpy(lista->A[j].descricaoCompromisso, lista->A[j + 1].descricaoCompromisso);
    			}
   			 printf("Compromisso Excluido com sucesso!\n");	
   			 lista->nroElem--;
			}
  		}
 	}
  }
}


void desempilharParaLista(Pilha *pilha, Lista *lista)
{
  int i, j;
  Agenda temp;
    if (pilha->topo > 0 && lista->nroElem + pilha->topo <= MAX)
  {
   for (i = pilha->topo - 1; i >= 0; i--)
        {
            lista->A[lista->nroElem] = pilha->A[i];
            lista->nroElem++;
        }
        
    for (i = 0; i < lista->nroElem - 1; i++)
    {
        for (j = 0; j < lista->nroElem - i - 1; j++)
        {
            if (lista->A[j].dataCompromisso.ano > lista->A[j + 1].dataCompromisso.ano)
            {
                temp = lista->A[j];
                lista->A[j] = lista->A[j + 1];
                lista->A[j + 1] = temp;
            }
            else if (lista->A[j].dataCompromisso.ano == lista->A[j + 1].dataCompromisso.ano)
            {
                if (lista->A[j].dataCompromisso.mes > lista->A[j + 1].dataCompromisso.mes)
                {
                    temp = lista->A[j];
                    lista->A[j] = lista->A[j + 1];
                    lista->A[j + 1] = temp;
                }
                else if (lista->A[j].dataCompromisso.mes == lista->A[j + 1].dataCompromisso.mes)
                {
                    if (lista->A[j].dataCompromisso.dia > lista->A[j + 1].dataCompromisso.dia)
                    {
                        temp = lista->A[j];
                        lista->A[j] = lista->A[j + 1];
                        lista->A[j + 1] = temp;
                    }
                }
            }
        }
    }
  }
  printf("Compromissos Ordenados na lista com sucesso!\n");
  pilha->topo = 0;
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