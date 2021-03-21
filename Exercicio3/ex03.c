#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std; 
#define MAXBUFF 150

int main() {

	FILE* inputFile;
	FILE* outputFile;
	FILE* idxFile;
	FILE* idxFileTxt;

	inputFile = fopen("cep.txt", "r");
	outputFile = fopen("result.txt", "w");
	idxFile = fopen("data.idx","wb");
	idxFileTxt = fopen("index.txt","w");


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
		int cursor = ftell(inputFile);
		fwrite(& cursor, sizeof cursor, 1, idxFile);
		// esse idxFileTxt é só um arquivo que eu fiz para debugar e ver se tá lendo certo
		fprintf(idxFileTxt, "%d\n", cursor);
		fprintf(outputFile, "%s", formattedLine);
	}


	// agora fazer a leitura  do índice
	// reabir os arquivos como leitura
	fclose(idxFile);
	fclose(outputFile);
	idxFile = fopen("data.idx","rb");
	outputFile = fopen("result.txt", "r");

	// ler o índice de acordo com o número de bytes
	int position;
	int idx;
	// por exemplo, ler o item na terceira posição
	position = 2;
	int dataPos = fseek(idxFile, position*sizeof(int), SEEK_SET);
	fread(&idx, sizeof(int), 1, idxFile);
	printf("%d", idx);
	// pular para essa posição do cursor no arquivo resultado e ler a linha
	fseek(outputFile, dataPos, SEEK_SET);


	char lineR[MAXBUFF];
	while(1) {
		char *c = NULL;
		while ((c = fgets(lineR, MAXBUFF, outputFile)) != NULL) {
			if (lineR[0] == '\n'){
				printf("pulando linha");
				break;
			}
			printf("%s", lineR);
	    }
		if (c ==NULL) break;
	}




	
	fclose(outputFile);
	fclose(inputFile);
	return 0;
}

