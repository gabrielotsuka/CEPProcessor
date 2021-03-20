#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 150

FILE* outputFile;

char* formatLine(char* line);
void transcribeCepFile(void);
// void searchMenu(void);
// void processOption(int option);

int main() {

	transcribeCepFile();
	// searchMenu();

	char line[LINE_SIZE];
	while (fgets(line, LINE_SIZE, outputFile) != NULL) {
		
		
	}
	
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

// void searchMenu(void) {
// 	int option;
// 	do {
// 		printf("----Menu de busca----\n");
// 		printf("|   1- CEP           |\n");
// 		printf("|   2- Estado        |\n");
// 		printf("|   3- Cidade        |\n");
// 		printf("|   4- Logradouro    |\n");
// 		printf("|   5- Sair          |\n");
// 		printf("---------------------\n\n");
// 		printf("Opcao desejada: ");

// 		scanf("%d", &option);

// 		char* foundPlace = malloc(LINE_SIZE);
// 		foundPlace = processOption(option);
// 	} while(option != 5);
	
// 	printf("Abrass!\n");
// }

// char* processOption(int option) {
// 	switch(option) {
// 		case 1:
// 			searchByField()
// 			break
// 	}
// }


