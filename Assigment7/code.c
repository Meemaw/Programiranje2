#include<stdio.h>
#include<stdlib.h>

struct tabela{
	int* znaki;
	int* steviloPonovitev;
	int steviloZnakov;
};

struct besedilo {
	int* znaki;
	int steviloZnakov;
};

char inputName[256];
char outputName[256];




void preberiFile(FILE* odpri, struct besedilo *besedilo) {
	int current_size = 128;
	besedilo->znaki = malloc(current_size*sizeof(int));
	besedilo->steviloZnakov = 0;

	// beremo znak po znak in ga shranjujemo v tabelo znakov
	int buffer = fgetc(odpri);
	while(buffer != EOF) {
		besedilo->znaki[besedilo->steviloZnakov++] = buffer;
		if(besedilo->steviloZnakov == current_size) {
			current_size*=2;
			besedilo->znaki  = realloc(besedilo->znaki, current_size*sizeof(int));
		}
		buffer = fgetc(odpri);
	}
	besedilo->znaki[besedilo->steviloZnakov] = '\0';
}

// funkcija preveri ce se je zaporedje ze pojavilo
int zeObstaja(int* tabela, int* tabelaInt, int dolzinaTabele, int c, int dolzinaZaporedja) {
	int i;
	int ceta = 0;

	for(i = 0; i < dolzinaTabele; i++) {
		// ce je stevilo pojavitev ni enako 0, pomeni da je novo zaporedje
		if(tabelaInt[i] != 0) {
			ceta++;
		}
		// ce najdemo nase zaporedje vrnemo ceto
		if(tabela[i] == c && tabelaInt[i] == dolzinaZaporedja) {
			return ceta-1;
		}
	}
	return -1;
}


void kodirajCete(struct besedilo besedilo, struct tabela *tabela) {
	// inicializacija spremenljivk in alociranje
	int i, dolzinaZaporedja;
	int current_size = 128;
	int* tempTabela = malloc(current_size*sizeof(int));
	int* tempTabelaInt = malloc(current_size*sizeof(int));
	int x = 0;

	// poisce dolzine zaporedja z trenutnim charom
	for(i = 0; i < besedilo.steviloZnakov; i++) {
		int temp = besedilo.znaki[i];
		dolzinaZaporedja = 1;
		// dokler je naslednji char enak trenutnemu
		if(i+1 < besedilo.steviloZnakov) {
			while(besedilo.znaki[i+1] == temp) {
				dolzinaZaporedja++;
				// ce pridemo do konca koncamo
				i++;
				if(i+1 == besedilo.steviloZnakov) {
					break;
				}
			}
		}

		// preverimo ali smo zaporedje ze shranili
		int ceta = zeObstaja(tempTabela, tempTabelaInt, x, temp, dolzinaZaporedja);
		if(ceta == -1) {
			// shranimo novo zaporedje
			tempTabela[x] = temp;
			tempTabelaInt[x] = dolzinaZaporedja;
			x++;
		}
		else {
			// shranimo frekvenco 0 in ceto zaporedja
			tempTabelaInt[x] = 0;
			tempTabela[x] = ceta;
			x++;
		}
		if(x == current_size) {
			// ce napolnimo tabeli, njuni velikosti podvojimo
			current_size*=2;
			tempTabela = realloc(tempTabela, current_size*sizeof(int));
			tempTabelaInt = realloc(tempTabelaInt, current_size*sizeof(int));
		}
	}
	
	tempTabela[x] = '\0';
	// z struktom pokzaemo na nase vrednosti
	tabela->znaki = tempTabela;
	tabela->steviloPonovitev = tempTabelaInt;
	tabela->steviloZnakov = x;
}


void zapisiDatoteko(struct tabela *tabela, FILE* zapisi) {
	int i;
	for(i = 0; i < tabela->steviloZnakov; i++) {
		fprintf(zapisi, "%d,", tabela->steviloPonovitev[i]);
		
		if(i == tabela->steviloZnakov-1) {
			fprintf(zapisi, "%d\n", tabela->znaki[i]);
		}
		else {
			fprintf(zapisi, "%d,", tabela->znaki[i]);
		}
	}
}




int main() {


	// priprava dveh stringov za imena datotek


	scanf("%s", inputName);
	scanf("%s", outputName);

	struct besedilo besedilo;

	// preberem file ki ga je treba zakodirat
	


	struct tabela tabela;
	// ce datoteka obstaja jo kodiram, drugace izpisem da ne obstaja
	FILE* zapisi;
	zapisi = fopen(outputName, "w");
	FILE* odpri;
	odpri = fopen(inputName, "r");
	if(odpri == NULL) {
		fprintf(zapisi, "datoteka ne obstaja");
		fclose(zapisi);
		return 0;
	}
	preberiFile(odpri, &besedilo);
	fclose(odpri);
	kodirajCete(besedilo, &tabela);
	zapisiDatoteko(&tabela, zapisi);
	fclose(zapisi);
	

return 0;

}
