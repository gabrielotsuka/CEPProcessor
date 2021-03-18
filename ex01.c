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
	char newLine[500];
	char splitted[5][500];
	char* tok;
	int pos = 0;
	do {
		tok = strtok(inputLine, "\t");
		if(tok == NULL) break;
		strcpy(splitted[pos], tok);
		printf("%d - %s\n", pos, splitted[pos]);
		pos++;
	} while (tok != NULL);

	printf("%s %s %s %s\n", splitted[3], splitted[2], splitted[1], splitted[0]);
	// sprintf(newLine, "%s|%s|%s|%s\n", splitted[3], splitted[2], splitted[1], splitted[0]);

	// printf("%s\n", newLine);
	// return newLine;
}