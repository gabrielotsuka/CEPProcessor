#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void searchMenu(void);
void accessPosition(int position);

int main() {
	searchMenu();
	return 0;
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
