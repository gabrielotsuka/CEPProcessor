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

	//escrever a posição inicial do cursos
	int cursor = ftell(outputFile);
	fwrite(& cursor, sizeof cursor, 1, idxFile);
	fprintf(idxFileTxt, "%d\n", cursor);


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
	
		// esse idxFileTxt é só um arquivo que eu fiz para debugar e ver se tá lendo certo
		fprintf(idxFileTxt, "%d\n", cursor);
		fprintf(outputFile, "%s", formattedLine);
		cursor = ftell(outputFile);
		fwrite(& cursor, sizeof cursor, 1, idxFile);
	}


	// agora fazer a leitura  do índice
	// reabir os arquivos como leitura
	fclose(idxFile);
	fclose(outputFile);
	idxFile = fopen("data.idx","rb");
	outputFile = fopen("result.txt", "r");

	// ler o índice de acordo com o número de bytes
	int position;
	int idxStart;
	int idxEnd;
	// por exemplo, ler o item na terceira posição

	position = 2;
	fseek(idxFile, position*sizeof(int), SEEK_SET);
	fread(&idxStart, sizeof(int), 1, idxFile);
	printf("%d\n", idxStart);
	
	fseek(idxFile, (position+1)*sizeof(int), SEEK_SET);
	fread(&idxEnd, sizeof(int), 1, idxFile);
	printf("%d\n", idxEnd);

	int MAXBUFFER = idxEnd - idxStart;
	printf("%d\n", MAXBUFFER);

	// pular para essa posição do cursor no arquivo resultado e ler a linha
	fseek(outputFile, idxStart, SEEK_SET);

	char buffer[MAXBUFFER];
	int count = fread(&buffer, sizeof(char), MAXBUFFER, outputFile);
	printf("%s\n", buffer);


	
	fclose(outputFile);
	fclose(inputFile);
	fclose(idxFile);
	return 0;
}

