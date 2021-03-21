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
    logradouro[0] = '\0';

    sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]", &cep, uf, cidade, logradouro);

    struct item lineItem;
    lineItem.cep = cep;
    strcpy(lineItem.uf, uf);
    strcpy(lineItem.cidade, cidade);
    strcpy(lineItem.logradouro, logradouro);

    return lineItem;
}

void displayEntry(struct item entry) {
    printf("%d | %s | %s | %s\n", entry.cep, entry.uf, entry.cidade, entry.logradouro);
}

void writeToFile(FILE* outputFile, struct item lineItem) {
    fwrite(&lineItem, sizeof(struct item), 1, outputFile);
}

void findEntry(FILE * inputFile, int position) {
    int startAtFile = (position-1) * sizeof(struct item);
    fseek(inputFile, startAtFile, SEEK_SET);

    struct item entry;
    fread(&entry, sizeof(struct item), 1, inputFile);

    displayEntry(entry);
}

void searchMenu(FILE* outputFile) {
    int repeat = 2;
    do {
        puts("Escolha o tipo de busca que deseja fazer:");
        puts("1 - Sequecial");
        puts("2 - Por posicao");
        int searchOption;
        scanf("%d", &searchOption);

        if(searchOption == 1) {
            puts("Escolha por que atributo deseja buscar sequencialmente:");
            puts("1 - CEP");
            puts("2 - UF");
            puts("3 - Cidade");
            puts("4 - Logradouro");
            int attributeOption;
            scanf("%d", &attributeOption);
            if(attributeOption == 1) {
                
            }
            else if(attributeOption == 2) {

            }
            else if(attributeOption == 3) {

            }
            else {

            }
        }
        else {
            puts("Digite a posição que deseja encontrar (a partir de 1)");
            int position;
            scanf("%d", &position);
            findEntry(outputFile, position);
        }

        puts("Você deseja fazer outra consulta? (1 - Sim | 2 - Nao)");
        scanf("%d", &repeat);
    }
    while(repeat != 2);
}

int main() {
    FILE* inputFile;
	FILE* outputFile;
	inputFile = fopen("cep.txt", "r");
    outputFile = fopen("result.bin", "w");
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
    fclose(outputFile);

    inputFile = fopen("result.bin", "r");

    searchMenu(inputFile);
}