#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void searchMenu(void);
void accessPosition(int position);
char* formatLine(char* line);
void transcribeCepFile(void);
int  isAlphaNum(char c);
void removeTrailingSpaces(char *line);
#define LINE_SIZE 150


int main() {
	transcribeCepFile();
	searchMenu();
	return 0;
}

void transcribeCepFile(void) {
	FILE* idxFile = fopen("data.idx","wb");
	FILE* inputFile = fopen("cep.txt", "r");
	FILE* outputFile = fopen("result.txt", "w+");

	while (inputFile == NULL 
		   || outputFile == NULL 
		   ||  idxFile == NULL
	) {
		printf("Falha na abertura dos arquivos\n");
		exit(1);
	}

	char line[LINE_SIZE];
	//escrever a posição inicial do cursor
	int cursor;
	cursor = ftell(outputFile);
	fwrite(& cursor, sizeof cursor, 1, idxFile);

	while (fgets(line, LINE_SIZE, inputFile) != NULL) {
 		removeTrailingSpaces(line);
        if(strlen(line) == 0) {
        	continue;
        }
		fprintf(outputFile, "%s", formatLine(line));
		cursor = ftell(outputFile);
		fwrite(& cursor, sizeof cursor, 1, idxFile);
	}

	fclose(inputFile);
	fclose(outputFile);
	fclose(idxFile);
}


void removeTrailingSpaces(char *line) {
    int sz = strlen(line);
    for (int i=sz-1; i>=0; i--) {
        if(isAlphaNum(line[i])) break;
        line[i] = '\0'; 
    }
}

int isAlphaNum(char c) {
    if(c >= 'a' && c <= 'z') return 1;
    if(c >= 'A' && c <= 'Z') return 1;
    if(c >= '0' && c <= '9') return 1;
    return 0;
}

char* formatLine(char* line) {
	int cep;
    char uf[3], cidade[39], logradouro[67] = "-";
    sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]", &cep, uf, cidade, logradouro);

    char* formattedLine = malloc(LINE_SIZE);
    sprintf(formattedLine, "%s|%s|%s|%d\n", logradouro, cidade, uf, cep);

    return formattedLine;
}




void proessSearch(void) {
	FILE* dataFile;
	FILE* idxFile;

	idxFile = fopen("data.idx","rb");
	dataFile = fopen("result.txt", "r");

	while (dataFile == NULL || idxFile == NULL ) {
		printf("Falha na abertura dos arquivos\n");
		exit(1);
	}
	int position;
	printf("Insira a posição que deseja checar:");
	scanf("%d", &position);
	position--;
	// ler o índice de acordo com o número de bytes
	int idxStart;
	int idxEnd;
	// or exemplo, ler o item na terceira posição
	fseek(idxFile, position*sizeof(int), SEEK_SET);
	fread(&idxStart, sizeof(int), 1, idxFile);
	
	fseek(idxFile, (position+1)*sizeof(int), SEEK_SET);
	fread(&idxEnd, sizeof(int), 1, idxFile);

	int MAXBUFFER = (idxEnd-1) - idxStart;

	// pular para essa posição do cursor no arquivo resultado e ler a linha
	fseek(dataFile, idxStart, SEEK_SET);

	char buffer[MAXBUFFER+1];
	fgets(buffer, MAXBUFFER+1, dataFile);
	printf("=======================\n");
	printf("%s\n", buffer);
	printf("=======================\n");
	
	fclose(dataFile);
	fclose(idxFile);
}



void searchMenu(void) {
	char charOption[4];
	int option;
	while(1) {
		printf("|   1- Buscar por posição |\n");
		printf("|   2- Sair               |\n");

		printf("Insira o numero da opcao desejada: ");
	 	scanf("%d", &option);
	 	setbuf(stdin, NULL);
		
		if(option == 2) break;
		if(option == 1) proessSearch();
	}
	
	printf("Abrass!\n");
}
