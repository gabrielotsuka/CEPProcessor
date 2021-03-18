#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void formatString(char* inputLine);

int main() {

	FILE* inputFile;
	FILE* outputFile;
	char line[1234];
	size_t len = 0;

	inputFile = fopen("cep.txt", "r");
	outputFile = fopen("output.txt", "w+");

	if (inputFile == NULL || outputFile == NULL) {
		printf("Falha na leitura dos arquivos\n");
		exit(1);
	}

	if (fgets(line, 500, inputFile) != NULL) {
		line[strlen(line)-1] = '\0';
		formatString(line);
		
	}
	return 0;
}

void formatString(char* inputLine) {
	char newLine[12344];
	char cep[1234], estado[1234], cidade[1234], rua[1234];
	sscanf(inputLine, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]", cep, estado, cidade, rua);

	printf("%s|%s|%s|%s\n", cep, estado, cidade, rua);
	

	printf("%s\n", newLine);
	// return newLine;
}