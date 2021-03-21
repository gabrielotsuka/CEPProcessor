#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE* dataFile;
	FILE* idxFile;

	idxFile = fopen("data.idx","rb");
	dataFile = fopen("result.txt", "r");

	while (dataFile == NULL || idxFile == NULL ) {
		printf("Falha na abertura dos arquivos\n");
		exit(1);
	}


	// ler o índice de acordo com o número de bytes
	int position;
	int idxStart;
	int idxEnd;
	// or exemplo, ler o item na terceira posição

	position = 0;
	fseek(idxFile, position*sizeof(int), SEEK_SET);
	fread(&idxStart, sizeof(int), 1, idxFile);
	printf("%d\n", idxStart);
	
	fseek(idxFile, (position+1)*sizeof(int), SEEK_SET);
	fread(&idxEnd, sizeof(int), 1, idxFile);
	printf("%d\n", idxEnd);

	int MAXBUFFER = idxEnd - idxStart;
	printf("%d\n", MAXBUFFER);

	// pular para essa posição do cursor no arquivo resultado e ler a linha
	fseek(dataFile, idxStart, SEEK_SET);

	char buffer[MAXBUFFER];
	int count = fread(&buffer, sizeof(char), MAXBUFFER, dataFile);
	printf("%s\n", buffer);

	fclose(dataFile);
	fclose(idxFile);
	return 0;
}

