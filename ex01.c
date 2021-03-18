#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void formatString(char* inputLine);

int main() {

	FILE * inputFile;
	char* line = NULL;
	size_t len = 0;

	inputFile = fopen("cep.txt", "r");

	if (inputFile == NULL) {
		printf("Falha na leitura dos arquivos\n");
		exit(1);
	}

	while (getline(&line, &len, inputFile) != -1) {
		formatString(line);
	}

	printf("Minha parte ta feita, agr é só terminar Marquin <3\n");
	return 0;
}

void formatString(char* inputLine) {
	char* splitted;
	splitted = strtok(inputLine, "\t");
	while (splitted != NULL) {
		printf("%s\n", splitted);
		splitted = strtok(NULL, "\t");
	}
	printf("\n\n");
}