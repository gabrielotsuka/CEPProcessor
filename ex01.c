#include <stdio.h>

int main() {

	FILE* inputFile, outputFile;
	char* line = NULL;
	size_t len = 0;

	inputFile = fopen("cep.txt", "r");
	outputFile = fopen("/answers/ex01.txt", "w");

	if (inputFile == NULL || outputFile == NULL) {
		printf("Falha na leitura dos arquivos\n");
		exit(1);
	}

	while (getline(&line, &len, inputFile) != -1) {
		outputLine = formatString(line);
	}


	printf("Minha parte ta feita, agr é só terminar Marquin <3\n");
	return 0;
}

char* formatString(char* inputLine) {

}