#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* formatString(char* inputLine);

int main() {

	FILE* inputFile;
	FILE* outputFile;
	char line[150];
	size_t len = 0;

	inputFile = fopen("cep.txt", "r");
	outputFile = fopen("output.txt", "w+");

	while (inputFile == NULL || outputFile == NULL) {
		printf("Falha na leitura dos arquivos\n");
		exit(1);
	}

	while (fgets(line, 150, inputFile) != NULL) {
		line[strlen(line)-1] = '\0';

		char newLine[150];
		char cep[15], estado[3], cidade[39], rua[67];
		sscanf(line, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\r]", cep, estado, cidade, rua);
		sprintf(newLine, "%s|%s|%s|%s\n", rua, cidade, estado, cep);x

		fwrite(newLine, sizeof(char), sizeof(newLine), outputFile);
	}

	fclose(inputFile);
	fclose(outputFile);
	return 0;
}

char* formatString(char* inputLine) {
	char * newLine;
	char cep[15], estado[3], cidade[39], rua[67];
	sscanf(inputLine, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\r]", cep, estado, cidade, rua);
	sprintf(newLine, "%s|%s|%s|%s\n", rua, cidade, estado, cep);
	return newLine;
}