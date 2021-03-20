#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 150

FILE* outputFile;

char* formatLine(char* line);
void transcribeCepFile(void);
void searchMenu(void);
void processOption(int option);
int hasSubstring(char* string, char* subString);
void searchByCEP(void);

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
		fprintf(outputFile, "%s", formatLine(line));
	}

	fclose(inputFile);
}

char* formatLine(char* line) {
	char* cep = strtok(line, "\t");
	char* uf = strtok(NULL, "\t");
	char* city = strtok(NULL, "\t");
	char* street = strtok(NULL, "\n\r");
	
	char* formattedLine = malloc(LINE_SIZE);
	if (street == NULL){
		strtok(city, "\n\r");
		sprintf(formattedLine, "%s|%s|%s\n", city, uf, cep);
	} else {
		sprintf(formattedLine, "%s|%s|%s|%s\n", street, city, uf, cep);
	}

	return formattedLine; 
}

void searchMenu(void) {
	int option;
	do {
		printf("----Menu de busca----\n");
		printf("|   1- CEP           |\n");
		printf("|   2- Estado        |\n");
		printf("|   3- Cidade        |\n");
		printf("|   4- Logradouro    |\n");
		printf("|   5- Sair          |\n");
		printf("---------------------\n\n");

		printf("Insira o numero da opcao desejada: ");
		scanf("%d", &option);
		
		processOption(option);
	} while(option != 5);
	
	printf("Abrass!\n");
}

void processOption(int option) {
	switch(option) {
		case 1:
			searchByCEP();
			break;
	}
}

void searchByCEP(void) {
	printf("Insira o valor a ser buscado: ");

	char subString[LINE_SIZE];
	fflush(stdin);
	fgets(subString, LINE_SIZE, stdin);

	char line[LINE_SIZE], lineCopy[LINE_SIZE];
	while (fgets(line, LINE_SIZE, outputFile) != NULL) {
		strcpy(lineCopy, line);
		char* street = strtok(line, "|");
		char* city = strtok(NULL, "|");
		char* uf = strtok(NULL, "|");
		char* cep = strtok(NULL, "\n\r");
	
		if (cep == NULL){
			if (hasSubstring(uf, lineCopy) == 1) 
				printf("%s\n", lineCopy);
		} 
		else {
			if (hasSubstring(cep, lineCopy) == 1) 
				printf("%s\n", lineCopy);
		}
	}
} 	


int hasSubstring(char* string, char* subString) {
	if (strstr(string, subString) != NULL)
		return 1;
	else 
		return 0;
}