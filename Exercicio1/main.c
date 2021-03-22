/*
	Gabriel José Bueno Otsuka - 11721BCC018
	Marcos Felipe Belisário Costa - 11811BCC020
	Pedro Henrique Bufulin de Almeida - 11711BCC028
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_SIZE 150

FILE* outputFile;

char* formatLine(char* line);
void transcribeCepFile(void);
int  isAlphaNum(char c);
void removeTrailingSpaces(char *line);
void searchMenu(void);
void processOption(int option);
void searchByCEP(void);
void searchByUF(void);
void searchByCidade(void);
void searchByLogradouro(void);

int main() {

	transcribeCepFile();
	searchMenu();

	fclose(outputFile);
	return 0;
}

void transcribeCepFile(void) {

	FILE* inputFile = fopen("cep.txt", "r");
	outputFile = fopen("result.txt", "w+");
	while (inputFile == NULL || outputFile == NULL) {
		printf("Falha na abertura dos arquivos\n");
		exit(1);
	}

	char line[LINE_SIZE];
	while (fgets(line, LINE_SIZE, inputFile) != NULL) {
 		removeTrailingSpaces(line);
        if(strlen(line) == 0) {
        	continue ;
        }
		fprintf(outputFile, "%s", formatLine(line));
	}

	fclose(inputFile);
}

void removeTrailingSpaces(char *line) {
    int sz = strlen(line);
    for (int i=sz-1; i>=0; i--) {
        if(isAlphaNum(line[i])) break;
        line[i] = '\0'; 
    }
}

int isAlphaNum(char c) {
    if(c >= 'a' && c <= 'z') return 1;
    if(c >= 'A' && c <= 'Z') return 1;
    if(c >= '0' && c <= '9') return 1;
    return 0;
}

char* formatLine(char* line) {
	int cep;
    char uf[3], cidade[39], logradouro[67] = "-";
    sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]", &cep, uf, cidade, logradouro);

    char* formattedLine = malloc(LINE_SIZE);
    sprintf(formattedLine, "%s|%s|%s|%d\n", logradouro, cidade, uf, cep);

    return formattedLine;
}

void searchMenu(void) {
	char charOption[4];
	int option;
	while(1) {
		rewind(outputFile);
		printf("\n\n----Menu de busca----\n");
		printf("|   1- CEP           |\n");
		printf("|   2- UF            |\n");
		printf("|   3- Cidade        |\n");
		printf("|   4- Logradouro    |\n");
		printf("|   5- Sair          |\n");
		printf("---------------------\n\n");

		printf("Insira o numero da opcao desejada: ");
	 	scanf("%d", &option);
	 	setbuf(stdin, NULL);
		
		if(option == 5) break;
		processOption(option);
	}
}

void processOption(int option) {
	switch(option) {
		case 1:
			searchByCEP();
			break;
		case 2:
			searchByUF();
			break;
		case 3:
			searchByCidade();
			break;
		case 4:
			searchByLogradouro();
			break;
		default:
			printf("Opcao invalida!\n");
	}
}

void searchByCEP(void) {
	printf("Insira o cep para busca: ");
	char cepStr[LINE_SIZE];
	fgets(cepStr, LINE_SIZE, stdin);
	int targetCEP = atoi(cepStr);
	printf("\nEnderecos encontrados:\n");

	char line[LINE_SIZE];
	int flagFound = 0;
	while (fgets(line, LINE_SIZE, outputFile) != NULL) {
		int cep;
	    char uf[3], cidade[39], logradouro[67];
	    sscanf(line, "%[^|]|%[^|]|%[^|]|%d", logradouro, cidade, uf, &cep);

	    if(cep == targetCEP) {
    		printf("%s|%s|%s|%d\n", logradouro, cidade, uf, cep);
			flagFound = 1;
	    }
	}

	if(flagFound == 0) {
		printf("Nenhum :(\n");
	}
}

void searchByUF(void) {
	printf("Insira o codigo UF para busca: ");
	char ufStr[3];
	fgets(ufStr, 3, stdin);

	for(int i = 0; i < strlen(ufStr); i++) 
		ufStr[i] = toupper(ufStr[i]);

	printf("\nEnderecos encontrados:\n");
	char line[LINE_SIZE];
	int flagFound = 0;
	while (fgets(line, LINE_SIZE, outputFile) != NULL) {
		int cep;
	    char uf[3], cidade[39], logradouro[67];
	    sscanf(line, "%[^|]|%[^|]|%[^|]|%d", logradouro, cidade, uf, &cep);
	    if(strcmp(uf, ufStr) == 0) {
    		printf("%s|%s|%s|%d\n", logradouro, cidade, uf, cep);
			flagFound = 1;
	    }
	}

	if(flagFound == 0) {
		printf("Nenhum :(\n");
	}
}

void searchByCidade(void) {
	printf("Insira o prefixo da cidade para busca: ");
	char cidadeStr[39];
	fgets(cidadeStr, 39, stdin);

	for(int i = 0; i < strlen(cidadeStr); i++) 
		cidadeStr[i] = toupper(cidadeStr[i]);
	cidadeStr[strlen(cidadeStr) - 1] = '\0';

	printf("\nEnderecos encontrados:\n");

	char line[LINE_SIZE];
	int flagFound = 0;
	while (fgets(line, LINE_SIZE, outputFile) != NULL) {
		int cep;
	    char uf[3], cidade[39], logradouro[67];
	    sscanf(line, "%[^|]|%[^|]|%[^|]|%d", logradouro, cidade, uf, &cep);
	    if(strstr(cidade, cidadeStr) != NULL) {
    		printf("%s|%s|%s|%d\n", logradouro, cidade, uf, cep);
			flagFound = 1;
	    }
	}

	if(flagFound == 0) {
		printf("Nenhum :(\n");
	}
}

void searchByLogradouro(void) {
	printf("Insira o prefixo do logradouro para busca: ");
	char logradouroStr[67];
	fgets(logradouroStr, 67, stdin);

	for(int i = 0; i < strlen(logradouroStr); i++) 
		logradouroStr[i] = toupper(logradouroStr[i]);
	logradouroStr[strlen(logradouroStr) - 1] = '\0';

	printf("\nEnderecos encontrados:\n");

	char line[LINE_SIZE];
	int flagFound = 0;
	while (fgets(line, LINE_SIZE, outputFile) != NULL) {
		int cep;
	    char uf[3], cidade[39], logradouro[67];
	    sscanf(line, "%[^|]|%[^|]|%[^|]|%d", logradouro, cidade, uf, &cep);
	    if(strstr(logradouro, logradouroStr) != NULL) {
    		printf("%s|%s|%s|%d\n", logradouro, cidade, uf, cep);
			flagFound = 1;
	    }
	}

	if(flagFound == 0) {
		printf("Nenhum :(\n");
	}
}
