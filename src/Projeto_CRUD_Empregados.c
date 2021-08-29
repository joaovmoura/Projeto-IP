#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define LETRAS 80

void ler(char **nome, int *matricula, float *salario, int);
void demissao(char aux_nome[LETRAS], char **nome, int *matricula, float *salario, int);
int pesquisaNome(char aux_nome[LETRAS], char **nome, int *matricula, float *salario, int);
void pesquisaSalario(float aux_salario, char **nome, int *matricula, float *salario, int);
void alterar(char aux_nome[LETRAS], char **nome, int *matricula, float *salario, int);
void ordenar(char **nome, int *matricula, float *salario, int);
void exibir(char **nome, int *matricula, float *salario, int);
void Leitura_Arquivo(char **nome, int *matricula, float *salario, int tam);
void Escrever_Arquivo(char **nome, int *matricula, float *salario, int tam);

int main()
{
	setlocale(LC_ALL, "Portuguese");

	system ("color 3F");
	
	int tam = 0;

	char **nome;
	nome = (char **)malloc(tam * sizeof(char *));
	int *matricula;
	matricula = (int *)malloc(tam * sizeof(int));
	float *salario;
	salario = (float *)malloc(tam * sizeof(float));

	int i, posicao, quantidade, aux, acao;
	float aux_salario;
	char usuario[LETRAS], aux_nome[LETRAS];

	printf("Olá, bem-vindo à nossa plataforma. Qual é o seu nome?\n");
	gets(usuario);
	
	Leitura_Arquivo(nome, matricula, salario, tam);

	system("cls");

	do
	{
		printf("O que você deseja fazer %s? - OBS: Não feche o programa sem usar a opção sair!\n", usuario);

		printf("1 - Cadastrar novo(s) funcionário(s)\n");
		printf("2 - Excluir funcionário(s)\n");
		printf("3 - Pesquisar por nome\n");
		printf("4 - Pesquisar por salário\n");
		printf("5 - Alterar dados  de funcionário(s)\n");
		printf("6 - Exibir os atuais funcionários\n");
		printf("7 - Sair do programa\n");

		printf("\n");

		scanf("%d", &acao);
		fflush(stdin);

		switch(acao)
		{
		case 1:
			printf("\nQuantos funionários serão cadastrados no programa?\n");
			scanf("%d", &quantidade);
			fflush(stdin);

			for(i = 1; i <= quantidade; i++)
			{
				printf("\nInsira o nome, matrícula e salário do funcionário a ser cadastrado: \n");

				tam++;

				nome = (char **)realloc(nome, tam * sizeof(char *));
				nome[tam - 1] = (char *)malloc(50 * sizeof(char));
				matricula = (int *)realloc(matricula, tam * sizeof(int));
				salario = (float *)realloc(salario, tam * sizeof(float));

				if(nome == NULL)
					printf("ERRO: nome não realocado. Verifique sua memória.\n");
				if(matricula == NULL)
					printf("ERRO: matrícula não realocado. Verifique sua memória.\n");
				if(salario == NULL)
					printf("ERRO: salário não realocado. Verifique sua memória.\n");

				ler(nome, matricula, salario, tam);
				ordenar(nome, matricula, salario, tam);
				
				fflush(stdin);

			}

			break;
		case 2:
			if(tam > 0)
			{
				printf("\nQuantos funionários serão excluídos do programa?\n");
				scanf("%d", &quantidade);
				fflush(stdin);

				printf("\n");

				for(i = 1, aux = 1; i <= quantidade; i++, aux++)
				{
					printf("Digite o nome do %dº funcionário a ser excluído: ", aux);
					gets(aux_nome);
					fflush(stdin);

					demissao(aux_nome, nome, matricula, salario, tam);

					free(nome[tam - 1]);
					nome = (char **)realloc(nome, (tam - 1) * sizeof(char *));
					matricula = (int *)realloc(matricula, (tam - 1) * sizeof(int));
					salario = (float *)realloc(salario, (tam - 1) * sizeof(float));

					tam--;

					if(nome == NULL)
						printf("ERRO: nome não realocado. Verifique sua memória.\n");
					if(matricula == NULL)
						printf("ERRO: matrícula não realocado. Verifique sua memória.\n");
					if(salario == NULL)
						printf("ERRO: salário não realocado. Verifique sua memória.\n");
				}
				printf("\nDessa forma. ");
				exibir(nome, matricula, salario, tam);
			}
			else
			{
				printf("Não é possível excluir, pois não há funcionários");
			}
			break;
		case 3:
			printf("\nDigite o nome do funcionário a ser pesquisado: ");
			gets(aux_nome);
			fflush(stdin);

			posicao = pesquisaNome(aux_nome, nome, matricula, salario, tam);

			if(posicao == -1)
			{
				printf("Não foi encontrado um funcionário com esse nome\n");
			}

			else
			{
				printf("\nO funcionário encontrado foi: \n");
				printf("%s/ %d/ %.2f reais;\n", nome[posicao], matricula[posicao], salario[posicao]);

				printf("\nDeseja alterar algum dado deste funcionário? 1- para sim, 2- para não.\n");
				scanf("%d", &acao);
				fflush(stdin);

				if(acao == 1)
					alterar(aux_nome, nome, matricula, salario, tam);
			}

			break;
		case 4:
			printf("\nDigite o salário a ser buscado: ");
			scanf("%f", &aux_salario);
			fflush(stdin);

			pesquisaSalario(aux_salario, nome, matricula, salario, tam);

			break;
		case 5:
			printf("\nInsira o nome do funcionário que será alterado: ");
			gets(aux_nome);
			fflush(stdin);

			alterar(aux_nome, nome, matricula, salario, tam);

			break;
		case 6:
			printf("\n");
			exibir(nome, matricula, salario, tam);

			break;
		case 7:
			Escrever_Arquivo(nome, matricula, salario, tam);
				
			for(posicao = 0; posicao < tam; posicao++)
			{
				free(nome[posicao]);
				nome[posicao] = NULL;
			}
			free(nome);
			free(matricula);
			matricula = NULL;
			free(salario);
			salario = NULL;

			exit(EXIT_SUCCESS);

			break;
		}

		system("pause");
		system("cls");

	}
	while(1);
}

void ler(char **nome, int *matricula, float *salario, int tam)
{
	gets(nome[tam - 1]);
	scanf("%d", &matricula[tam - 1]);
	scanf("%f", &salario[tam - 1]);
}

void demissao(char aux_nome[LETRAS], char **nome, int *matricula, float *salario, int tam)
{
	int pos, j;

	pos = pesquisaNome(aux_nome, nome, matricula, salario, tam);

	for(j = pos; j < tam - 1; j++)
	{
		strcpy(nome[j], nome[j + 1]);
		matricula[j] = matricula[j + 1];
		salario[j] = salario[j + 1];
	}
}

int pesquisaNome(char aux_nome[LETRAS], char **nome, int *matricula, float *salario, int tam)
{
	int j, cont = -1;

	for(j = 0; j < tam; j++)
		if(strcmp(aux_nome, nome[j]) == 0)
			cont = j;
	return cont;
}

void pesquisaSalario(float aux_salario, char **nome, int *matricula, float *salario, int tam)
{
	int j, aux = 1;

	for(j = 0; j < tam; j++)
		if(aux_salario == salario[j])
		{
			printf("%d - %s/ %d/ %.2f reais;\n", aux, nome[j], matricula[j], salario[j]);
			aux++;
		}

	printf("\n");
}

void alterar(char aux_nome[LETRAS], char **nome, int *matricula, float *salario, int tam)
{
	int local, opcao;
	int aux_matricula;
	float aux_salario;

	local = pesquisaNome(aux_nome, nome, matricula, salario, tam);

	printf("\nO que será alterado? 1 - para nome, 2 - para matrícula, 3 - para salário.\n");
	scanf("%d", &opcao);
	fflush(stdin);

	switch(opcao)
	{
	case 1:
		printf("\nDigite o novo nome: \n");
		gets(aux_nome);
		fflush(stdin);

		strcpy(nome[local], aux_nome);

		break;
	case 2:
		printf("\nDigite o valor da nova matrícula: \n");
		scanf("%d", &aux_matricula);

		matricula[local] = aux_matricula;

		break;
	case 3:
		printf("\nDigite o valor do novo salário: \n");
		scanf("%f", &aux_salario);

		salario[local] = aux_salario;

		break;
	}

	printf("\nOs atuais dados deste funcionário são: \n");
	printf("%s/ %d/ %.2f reais;\n", nome[local], matricula[local], salario[local]);

}

void ordenar(char **nome, int *matricula, float *salario, int tam)
{
	int i, cont, mat_aux;
	float sal_aux;
	char aux[LETRAS];

	for(i = 0; i < tam; i++)
		for(cont = 0; cont < tam - 1; cont++)
			if(strcmp(nome[cont], nome[cont + 1]) == 1)
			{
				strcpy(aux, nome[cont]);
				strcpy(nome[cont], nome[cont + 1]);
				strcpy(nome[cont + 1], aux);

				mat_aux = matricula[cont];
				matricula[cont] = matricula[cont + 1];
				matricula[cont + 1] = mat_aux;

				sal_aux = salario[cont];
				salario[cont] = salario[cont + 1];
				salario[cont + 1] = sal_aux;
			}
}

void exibir(char **nome, int *matricula, float *salario, int tam)
{
	int aux = 1, i;

	printf("Os nomes/ matrículas/ salários respectivamente dos atuais funcionários em ordem são: \n");

	for(i = 0; i < tam; i++, aux++)
		printf("%d - %s/ %d/ %.2f reais;\n", aux, nome[i], matricula[i], salario[i]);

	printf("\n");
}

void Leitura_Arquivo(char **nome, int *matricula, float *salario, int tam)
{
	FILE *arquivo;//Declarando apontador do tipo FILE que irá apontar para o arquivo desejado

	int i;
	char aux[LETRAS];

	arquivo = fopen("dados.txt", "r");
	
	if(arquivo == NULL)
	{
		arquivo = fopen("dados.txt", "w");//Se não existir o arquivo, a função criará.
		fclose(arquivo);
	}
	
	else
	{
		fscanf(arquivo, "%d\n", &tam);//Varia dependendo do padrão que você deseja utilizar para armazenar
		printf("%d", tam);
		for(i = 0; i < tam; i++)
		{
			fgets(aux, LETRAS, arquivo); //Função de leitura de string
			strcpy(nome[i], aux); //Apenas copiando o aux pra posição do array de nomes.
			printf("erro 2");
			fscanf(arquivo, "%d\n", &matricula[i]); //Função de leitura.
			fscanf(arquivo, "%f\n", &salario[i]); //Função de leitura.
		}
	
		fclose(arquivo);
	}
}

void Escrever_Arquivo(char **nome, int *matricula, float *salario, int tam)
{
	FILE *arquivo;

	int i;

	arquivo = fopen("dados.txt", "w");

	if(arquivo == NULL) //Ele não conseguiu abrir o arquivo/criar. Deve estar em algum lugar que precisa de permissão de ADM por exemplo
	{
		printf("Erro. \n");
	}
	else
	{
		fprintf(arquivo, "%d\n", tam); //Escrevendo a quantidade no arquivo, para que possa ser recuperado quando o programa for aberto novamente

		for(i = 0; i < tam; i++)
		{
			fprintf(arquivo, " %s\n", nome[i]);
			fprintf(arquivo, " %d\n", matricula[i]);
			fprintf(arquivo, " %f\n", salario[i]);
		}

		fclose(arquivo);
	}
}