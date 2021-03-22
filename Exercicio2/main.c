#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

void searchByCEP(FILE * inputFile) {
	printf("Insira o cep para busca: ");
	int targetCep;
	scanf("%d", &targetCep);
	setbuf(stdin, NULL);
	printf("\nEnderecos encontrados:\n");

	struct item entry;
	int flagFound = 0;
	while (fread(&entry, sizeof(struct item), 1, inputFile)) {
	    if(entry.cep == targetCep) {
    		displayEntry(entry);
			flagFound = 1;
	    }
	}

	if(flagFound == 0) {
		printf("Nenhum :(\n");
	}
}

void searchByUF(FILE * inputFile) {
	printf("Insira o codigo UF para busca: ");
	char ufStr[3];
	fgets(ufStr, 3, stdin);

	for(int i = 0; i < strlen(ufStr); i++) 
		ufStr[i] = toupper(ufStr[i]);

	printf("\nEnderecos encontrados:\n");
	struct item entry;
	int flagFound = 0;
	while (fread(&entry, sizeof(struct item), 1, inputFile)) {
	    if(strcmp(entry.uf, ufStr) == 0) {
    		displayEntry(entry);
			flagFound = 1;
	    }
	}

	if(flagFound == 0) {
		printf("Nenhum :(\n");
	}
}

void searchByCidade(FILE* inputFile) {
	printf("Insira a substring da cidade para busca: ");
	char cidadeStr[39];
	fgets(cidadeStr, 39, stdin);

	for(int i = 0; i < strlen(cidadeStr); i++) 
		cidadeStr[i] = toupper(cidadeStr[i]);
	cidadeStr[strlen(cidadeStr) - 1] = '\0';

	printf("\nEnderecos encontrados:\n");

	struct item entry;
	int flagFound = 0;
	while (fread(&entry, sizeof(struct item), 1, inputFile)) {
	    if(strstr(entry.cidade, cidadeStr) != NULL) {
    		displayEntry(entry);
			flagFound = 1;
	    }
	}

	if(flagFound == 0) {
		printf("Nenhum :(\n");
	}
}

void searchByLogradouro(FILE* inputFile) {
	printf("Insira a substring do logradouro para busca: ");
	char logradouroStr[67];
	fgets(logradouroStr, 67, stdin);

	for(int i = 0; i < strlen(logradouroStr); i++) 
		logradouroStr[i] = toupper(logradouroStr[i]);
	logradouroStr[strlen(logradouroStr) - 1] = '\0';

	printf("\nEnderecos encontrados:\n");

	struct item entry;
	int flagFound = 0;
	while (fread(&entry, sizeof(struct item), 1, inputFile)) {
	    if(strstr(entry.logradouro, logradouroStr) != NULL) {
    		displayEntry(entry);
			flagFound = 1;
	    }
	}

	if(flagFound == 0) {
		printf("Nenhum :(\n");
	}
}

void processOption(FILE* inputFile, int option) {
	switch(option) {
		case 1:
			searchByCEP(inputFile);
			break;
		case 2:
			searchByUF(inputFile);
			break;
		case 3:
			searchByCidade(inputFile);
			break;
		case 4:
			searchByLogradouro(inputFile);
			break;
		default:
			printf("Opcao invalida!\n");
	}
}

void searchMenu(FILE* inputFile) {
    int repeat = 2;
    do {
        puts("Escolha o tipo de busca que deseja fazer:");
        puts("1 - Sequecial");
        puts("2 - Por posicao");
        int searchOption;
        scanf("%d", &searchOption);

        if(searchOption == 1) {
            rewind(inputFile);
            int option;
            printf("\n\n----Menu de busca----\n");
            printf("|   1- CEP           |\n");
            printf("|   2- UF            |\n");
            printf("|   3- Cidade        |\n");
            printf("|   4- Logradouro    |\n");
            printf("|   5- Sair          |\n");
            printf("---------------------\n\n");

            printf("Insira o numero da opcao desejada: ");
            scanf("%d", &option);
            setbuf(stdin, NULL);
            
            if(option == 5) break;
            processOption(inputFile, option);
        }
        else {
            puts("Digite a posição que deseja encontrar (a partir de 1)");
            int position;
            scanf("%d", &position);
            findEntry(inputFile, position);
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