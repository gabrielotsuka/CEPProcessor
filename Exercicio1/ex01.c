#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	FILE* inputFile;
	FILE* outputFile;
	inputFile = fopen("cep.txt", "r");
	outputFile = fopen("result.txt", "w");
	while (inputFile == NULL || outputFile == NULL) {
		printf("Falha na abertura dos arquivos\n");
		exit(1);
	}

	char line[150], formattedLine[150];
	while (fgets(line, 150, inputFile) != NULL) {

		char* cep = strtok(line, "\t");
		char* uf = strtok(NULL, "\t");
		char* city = strtok(NULL, "\t");
		char* street = strtok(NULL, "\n\r");
		
		if (street == NULL){
			strtok(city, "\n\r");
			sprintf(formattedLine, "%s | %s | %s\n", city, uf, cep);
		} else {
			sprintf(formattedLine, "%s | %s | %s | %s\n", street, city, uf, cep);
		}
		fprintf(outputFile, "%s", formattedLine);
	}

	fclose(outputFile);
	fclose(inputFile);
	return 0;
}

