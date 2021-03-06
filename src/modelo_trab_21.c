#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define LETRAS 80

void ler(char **nome, int *matricula, float *salario, int tam);
int demissao(char aux_nome[LETRAS], char **nome, int *matricula, float *salario, int tam);
int pesquisaNome(char aux_nome[LETRAS], char **nome, int *matricula, float *salario, int tam);
void pesquisaSalario(float aux_salario, char **nome, int *matricula, float *salario, int tam);
void alterar(char aux_nome[LETRAS], char **nome, int *matricula, float *salario, int tam);
void ordenar(char **nome, int *matricula, float *salario, int tam);
void exibir(char **nome, int *matricula, float *salario, int tam);
void salvar(char **nome, int *matricula, float *salario, FILE *arq, int *tam);
void leitura(char **nome, int *matricula, float *salario, FILE *arq, int tam);

int main()
{
	setlocale(LC_ALL, "Portuguese");

	system ("color 3F");
	
	FILE *arq;
	
	int posicao, quantidade, aux, i, acao, *tam_p, tam=0, verificar_nome;
	float aux_salario;
	char usuario[LETRAS], aux_nome[LETRAS];
	
	tam_p=&tam;
	
	if((arq=fopen("dadosprojeto1.dat","rb"))!=NULL)
		if(fread(tam_p,sizeof(int),1,arq)!=1)
			fprintf(stderr,"O tamanho n?o foi lido!\n");

			
	
	char **nome;
	nome=(char **)malloc(tam * sizeof(char *)); 
	for(i=0;i<tam;i++)
		nome[i] = (char *)malloc(50 * sizeof(char));
	
	int *matricula;
	matricula=(int *)malloc(tam * sizeof(int));
	
	float *salario;
	salario=(float *)malloc(tam * sizeof(float));
	
	if(tam>0){
		leitura(nome,matricula,salario,arq, tam);
		fclose(arq);
	}
		
		
	printf("Ol?, bem-vindo ? nossa plataforma. Qual ? o seu nome?\n");
	gets(usuario);
	system("cls");

	do
	{
		printf("O que voc? deseja fazer %s? - OBS: N?o feche o programa sem usar a op??o sair!\n", usuario);

		printf("1 - Cadastrar novo(s) funcion?rio(s)\n");
		printf("2 - Excluir funcion?rio(s)\n");
		printf("3 - Pesquisar por nome\n");
		printf("4 - Pesquisar por sal?rio\n");
		printf("5 - Alterar dados  de funcion?rio(s)\n");
		printf("6 - Exibir os atuais funcion?rios\n");
		printf("7 - Sair do programa\n");

		printf("\n");

		scanf("%d", &acao);
		fflush(stdin);

		switch(acao)
		{
		case 1:
			printf("\nQuantos funion?rios ser?o cadastrados no programa?\n");
			scanf("%d", &quantidade);
			fflush(stdin);

			for(i = 1; i <= quantidade; i++){
				printf("\nInsira o nome, matr?cula e sal?rio do funcion?rio a ser cadastrado: \n");
				
				tam++;
			
				nome = (char **)realloc(nome, tam * sizeof(char *));
				nome[tam - 1] = (char *)malloc(50 * sizeof(char));
				matricula = (int *)realloc(matricula, tam * sizeof(int));
				salario = (float *)realloc(salario, tam * sizeof(float));
				
				if(nome==NULL)          
    				printf("ERRO: nome n?o realocado. Verifique sua mem?ria.\n");
				if(matricula==NULL)          
    				printf("ERRO: matr?cula n?o realocado. Verifique sua mem?ria.\n");
  	  	  	    if(salario==NULL)          
    				printf("ERRO: sal?rio n?o realocado. Verifique sua mem?ria.\n");
				
				ler(nome, matricula, salario, tam);
				ordenar(nome, matricula, salario, tam);
				
				fflush(stdin);
				
			}
			
			break;
		case 2:
			if(tam>0){
				printf("\nQuantos funion?rios ser?o exclu?dos do programa?\n");
				scanf("%d", &quantidade);
				fflush(stdin);
				
				printf("\n");
				
				for(aux=1; aux <= quantidade; aux++){
					printf("\nDigite o nome do %d? funcion?rio a ser exclu?do: ", aux);
					gets(aux_nome);
					fflush(stdin);
	
					verificar_nome = demissao(aux_nome, nome, matricula, salario, tam);
					if(verificar_nome!=-1){
					   	free(nome[tam-1]);		
					   	nome = (char **)realloc(nome, (tam-1) * sizeof(char *));
					   	matricula = (int *)realloc(matricula, (tam-1) * sizeof(int));
					   	salario = (float *)realloc(salario, (tam-1) * sizeof(float));
					
					   	tam--;
					
						   	if(nome==NULL)          
		            	printf("ERRO: nome n?o realocado. Verifique sua mem?ria.\n");
		           		 if(matricula==NULL)          
		            	printf("ERRO: matr?cula n?o realocado. Verifique sua mem?ria.\n");
		           		 if(salario==NULL)          
		            	printf("ERRO: sal?rio n?o realocado. Verifique sua mem?ria.\n");
					}
					else{
						printf("Esse funcion?rio n?o existe.\n");
					}
				}
						printf("\nDessa forma, ");
						exibir(nome, matricula, salario, tam);
			
				}
			else{
				printf("N?o ? poss?vel excluir, pois n?o h? funcion?rios.\n");
			}
			break;
		case 3:
			printf("\nDigite o nome do funcion?rio a ser pesquisado: ");
			gets(aux_nome);
			fflush(stdin);

			posicao = pesquisaNome(aux_nome, nome, matricula, salario, tam);
			
			if(posicao == -1){
				printf("\nN?o foi encontrado um funcion?rio com esse nome.\n");
			}
			
			else{
				printf("\nO funcion?rio encontrado foi: \n");
				printf("%s/ %d/ %.2f reais;\n", nome[posicao], matricula[posicao], salario[posicao]);
				
				printf("\nDeseja alterar algum dado deste funcion?rio? 1- para sim, 2- para n?o.\n");
				scanf("%d", &acao);
				fflush(stdin);
				
				if(acao == 1)
					alterar(aux_nome, nome, matricula, salario, tam);
			}
			
			break;
		case 4:
			printf("\nDigite o sal?rio a ser buscado: ");
			scanf("%f", &aux_salario);
			fflush(stdin);

			pesquisaSalario(aux_salario, nome, matricula, salario, tam);
			
			break;
		case 5:
			printf("\nInsira o nome do funcion?rio que ser? alterado: ");
			gets(aux_nome);
			fflush(stdin);

			alterar(aux_nome, nome, matricula, salario, tam);
			
			break;
		case 6:
			printf("\n");
			exibir(nome, matricula, salario, tam);
			
			break;
		case 7:
			if((arq=fopen("dadosprojeto1.dat","wb"))==NULL){
				printf("Erro ao abrir o arquivo.\n");
				exit(1);}
			printf("abriu arquivo\n");	
			salvar(nome, matricula, salario, arq, tam_p);
			printf("salvou\n");
			fclose(arq);
			printf("fechou arquivo\n");
			for(posicao=0;posicao<tam;posicao++){
				free(nome[i]);
				nome[i]=NULL;
			}
			printf("free strings\n");
			free(nome);
			printf("free nome\n");
			free(matricula);
			printf("free matricula\n");
			matricula=NULL;
			free(salario);
			salario=NULL;
			printf("free salario\n");
			exit(EXIT_SUCCESS);
			
			break;
		}

		system("pause");
		system("cls");

	}while(1);

}

void ler(char **nome, int *matricula, float *salario, int tam)
{

	gets(nome[tam - 1]);
	scanf("%d", &matricula[tam - 1]);
	scanf("%f", &salario[tam - 1]);
}

int demissao(char aux_nome[LETRAS], char **nome, int *matricula, float *salario, int tam){
	int pos, j;

	pos = pesquisaNome(aux_nome, nome, matricula, salario, tam);
	if(pos!=-1){
		for(j = pos; j < tam-1; j++){
			strcpy(nome[j], nome[j+1]);
			matricula[j] = matricula[j+1];
			salario[j] = salario[j+1];
		}
	}
	return pos;
}
		
int pesquisaNome(char aux_nome[LETRAS], char **nome, int *matricula, float *salario, int tam){
	int j, cont=-1;

	for(j = 0; j < tam; j++)
		if(strcmp(aux_nome, nome[j]) == 0)
			cont = j;
	return cont;
}

void pesquisaSalario(float aux_salario, char **nome, int *matricula, float *salario, int tam){
	int j, aux = 1;

	for(j = 0; j < tam; j++)
		if(aux_salario == salario[j]){
			printf("%d - %s/ %d/ %.2f reais;\n",aux, nome[j], matricula[j], salario[j]);
			aux++;
		}
		
		printf("\n");
}

void alterar(char aux_nome[LETRAS], char **nome, int *matricula, float *salario, int tam){
	int local, opcao;
	int aux_matricula;
	float aux_salario;

	local = pesquisaNome(aux_nome, nome, matricula, salario, tam);

	printf("\nO que ser? alterado? 1 - para nome, 2 - para matr?cula, 3 - para sal?rio.\n");
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
		printf("\nDigite o valor da nova matr?cula: \n");
		scanf("%d", &aux_matricula);
		
		matricula[local] = aux_matricula;
		
		break;
	case 3:
		printf("\nDigite o valor do novo sal?rio: \n");
		scanf("%f", &aux_salario);
		
		salario[local] = aux_salario;
		
		break;
	}
	
	printf("\nOs atuais dados deste funcion?rio s?o: \n");
	printf("%s/ %d/ %.2f reais;\n", nome[local], matricula[local], salario[local]);
	ordenar(nome, matricula, salario, tam);
}

void ordenar(char **nome, int *matricula, float *salario, int tam){
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

void exibir(char **nome, int *matricula, float *salario, int tam){
	int aux = 1, i;

	printf("Os nomes/ matr?culas/ sal?rios, dos atuais funcion?rios, em ordem, s?o, respectivamente: \n");

	for(i = 0; i < tam; i++, aux++)
		printf("%d - %s/ %d/ %.2f reais;\n", aux, nome[i], matricula[i], salario[i]);
	
	printf("\n");
}

void leitura(char **nome, int *matricula, float *salario, FILE *arq, int tam){
	int i,n;
	
	for(i=0;i<tam;i++){
		if(fread(&n,sizeof(int),1,arq)!=1)
			fprintf(stderr, "A mem?ria para o nome %d n?o foi salva!\n",i);
		if(fread(nome[i],n+1,1,arq)!=1)
			fprintf(stderr, "O nome %d n?o foi salvo!\n",i);
	}	
	if(fread(matricula,sizeof(int),tam,arq)!=tam)
		fprintf(stderr, "Uma ou mais matr?culas n?o foi/foram salva(s)!\n");
	if(fread(salario,sizeof(float),tam,arq)!=tam)
		fprintf(stderr, "Um ou mais sal?rios n?o foi/foram salvo(s)!\n");	
	
}

void salvar(char **nome, int *matricula, float *salario, FILE *arq, int *tam_p){
	int i,n;
	
	if(fwrite(tam_p,sizeof(int),1,arq)!=1)
		fprintf(stderr, "O tamanho n?o foi salvo!\n");
	for(i=0;i<*tam_p;i++){
		n=strlen(nome[i]);
		if(fwrite(&n,sizeof(int),1,arq)!=1)
			fprintf(stderr, "A mem?ria para o nome %d n?o foi salva!\n",i);
		if(fwrite(nome[i],n+1,1,arq)!=1)
			fprintf(stderr, "O nome %d n?o foi salvo!\n",i);
	}	
	if(fwrite(matricula,sizeof(int),*tam_p,arq)!= *tam_p)
		fprintf(stderr, "Uma ou mais matr?culas n?o foi/foram salva(s)!\n");
	if(fwrite(salario,sizeof(float),*tam_p,arq)!= *tam_p)
		fprintf(stderr, "Um ou mais sal?rios n?o foi/foram salvo(s)!\n");	
	
}