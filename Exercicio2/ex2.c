#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct item {
    int cep;
    char uf[3];
    char cidade[39];
    char logradouro[67];
};

int isAlphaNum(char c) {
    if(c >= 'a' && c <= 'z') return 1;
    if(c >= 'A' && c <= 'Z') return 1;
    if(c >= '0' && c <= '9') return 1;
    return 0;
}

void removeTrailingSpaces(char *line) {
    int sz = strlen(line);
    for (int i=sz-1; i>=0; i--) {
        if(isAlphaNum(line[i])) break;
        line[i] = '\0'; 
    }
}

struct item formatLine(char *line) {
    int cep;
    char uf[3], cidade[39], logradouro[67];
    
    sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]", &cep, uf, cidade, logradouro);

    struct item lineItem;
    lineItem.cep = cep;
    strcpy(lineItem.uf, uf);
    strcpy(lineItem.cidade, cidade);
    strcpy(lineItem.logradouro, logradouro);

    return lineItem;
}

void writeToFile(FILE* outputFile, struct item lineItem) {
    fwrite(&lineItem, sizeof(struct item), 1, outputFile);
}

struct item readFromFile(FILE *inputFile) {
    struct item lineItem;
    fread(&lineItem, sizeof(struct item), 1, inputFile);
    return lineItem;
}

void searchMenu() {

    

}

int main() {
    FILE* inputFile;
	FILE* outputFile;
	inputFile = fopen("cep.txt", "r");
    outputFile = fopen("result-ex2.bin", "rw");
	while (inputFile == NULL || outputFile == NULL) {
		printf("Falha na abertura dos arquivos\n");
		exit(1);
	}

	char line[150], formattedLine[150];
    int cnt = 0;
	while (fgets(line, 150, inputFile) != NULL) {
        cnt++;
        removeTrailingSpaces(line);
        int sz = strlen(line);
        if(sz == 0) continue ;
        struct item lineItem = formatLine(line);
        writeToFile(outputFile, lineItem);
    }
    fclose(inputFile);

    searchMenu();

    fclose(outputFile);
}