#include<stdio.h>
#include <unistd.h>
#define tuCrta 2
#define false 0
#define nepregledano 0
#define pregledano 7


struct risalnaPlosca
{
	int visina;
	int sirina;
};

struct premica
{
	int x1;
	int y1;
	int x2;
	int y2;
};

void tabelaNaNic(int visina, int sirina, int tabela[visina][sirina]) {
	int i;
	int j;
	for(i = 0; i < visina; i++) {
		for(j = 0; j < sirina; j++) {
			tabela[i][j] = nepregledano;
		}
	}
}

void narisiCrte(int visina, int sirina, int tabela[visina][sirina], struct premica trenutna) {
		int a;
		int b;
		for(a = trenutna.y1; a <= trenutna.y2; a++) {
			for(b = trenutna.x1; b <= trenutna.x2; b++) {
				tabela[a][b] = tuCrta;
			}
		}
}

//void clearScreen()
//{
//  const char* CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";
//  write(STDOUT_FILENO,CLEAR_SCREE_ANSI,12);
//}

void printajTabelo(int visina, int sirina, int tabela[visina][sirina]) {
	int a;
	int b;
	
	printf("\n");
	char enter[50];
	fgets(enter, 100, stdin);
	//clearScreen();
	for(a = 0; a < visina; a++) {
		for(b = 0; b < sirina; b++) {
			printf("%d", tabela[a][b]);
		}
		printf("\n");
	}
}


void rekurzija(int visina, int sirina, int tabela[visina][sirina], int y, int x) {
	tabela[y][x] = pregledano;
	if(x+1 < sirina && tabela[y][x+1] == nepregledano) {
		rekurzija(visina, sirina, tabela, y, x+1);
	}
	if(y+1 < visina && tabela[y+1][x] == nepregledano) {
		rekurzija(visina, sirina, tabela, y+1, x);
	}
	if(x-1 >= 0 && tabela[y][x-1] == nepregledano) {
		rekurzija(visina, sirina, tabela, y, x-1);
	}
	if(y-1 >= 0 && tabela[y-1][x] == nepregledano) {
		rekurzija(visina, sirina, tabela, y-1, x);
	}

}


int steviloObmocij(struct premica crte[], int steviloCrt, struct risalnaPlosca plosca) {
	int tabela[plosca.visina][plosca.sirina];
	int steviloObmocij = 0;
	// da celotno tabelo na 0
	tabelaNaNic(plosca.visina, plosca.sirina, tabela);

	int i;
	for(i = 0; i < steviloCrt; i++) {
		struct premica trenutna = crte[i];
		// nariše premice v tabeli
		narisiCrte(plosca.visina, plosca.sirina, tabela, trenutna);
		//printajTabelo(plosca.visina, plosca.sirina, tabela);
	}


	int c;
	int d;


	for(c = 0; c < plosca.visina; c++) {
		for(d = 0; d < plosca.sirina; d++) {
			if(tabela[c][d] == nepregledano) {
				steviloObmocij++;
				rekurzija(plosca.visina, plosca.sirina, tabela, c, d); 
				//printajTabelo(plosca.visina, plosca.sirina, tabela);
			}
		}
	}

	return steviloObmocij;
}




int main() {
	struct risalnaPlosca plosca;

	scanf("%d", &plosca.sirina);
	scanf("%d", &plosca.visina);

	int steviloCrt;
	scanf("%d", &steviloCrt);
	int i;
	struct premica crte[steviloCrt];

	for(i = 0; i < steviloCrt; i++) {
		struct premica trenutnaPremica;
		scanf("%d", &trenutnaPremica.x1);
		scanf("%d", &trenutnaPremica.y1);
		scanf("%d", &trenutnaPremica.x2);
		scanf("%d", &trenutnaPremica.y2);
		crte[i] = trenutnaPremica;
	}


	int ljubezen = steviloObmocij(crte,steviloCrt,plosca);
	printf("%d\n", ljubezen);

	return 0;
}
