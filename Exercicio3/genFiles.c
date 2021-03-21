#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_SIZE 150


char* formatLine(char* line);
void transcribeCepFile(void);
int  isAlphaNum(char c);
void removeTrailingSpaces(char *line);

int main() {
	transcribeCepFile();
	return 0;
}

void transcribeCepFile(void) {
	FILE* idxFile = fopen("data.idx","wb");
	FILE* idxFileTxt = fopen("index.txt","w");
	FILE* inputFile = fopen("cep.txt", "r");
	FILE* outputFile = fopen("result.txt", "w+");

	while (inputFile == NULL 
		   || outputFile == NULL 
		   || idxFileTxt == NULL
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
	fprintf(idxFileTxt, "%d\n", cursor);

	while (fgets(line, LINE_SIZE, inputFile) != NULL) {
 		removeTrailingSpaces(line);
        if(strlen(line) == 0) {
        	continue;
        }
		fprintf(outputFile, "%s", formatLine(line));
		cursor = ftell(outputFile);
		fwrite(& cursor, sizeof cursor, 1, idxFile);
		//arquivo para debug:
		fprintf(idxFileTxt, "%d\n", cursor);
	}

	fclose(inputFile);
	fclose(outputFile);
	fclose(idxFile);
	fclose(idxFileTxt);
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
