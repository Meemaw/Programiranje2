#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <string.h>
#define splitVrstica " \r\n\t"


struct beseda
{
	char* crke;
	short steviloPonovitev;
};

struct hashMap
{
	struct beseda *vseBesede;
	int steviloBesed;
};


int vsebujeBesedo(struct hashMap *besedilo, char* crke) {
	int i;
	for(i = 0; i < besedilo->steviloBesed; i++) {
		if(strcmp(besedilo->vseBesede[i].crke,crke) == 0) {
			return i;
		}
	}
	return -1;
}

// prebere besedilo iz vhoda
char* preberiBesedilo() {
 	unsigned int current_size = 1024;

 	char *pStr = NULL;
 	pStr = malloc(current_size);
 	if(pStr != NULL) {
 		int c = EOF;
 		unsigned int i = 0;
 		while(( c = getchar() ) != EOF) {
 			// locila ignorira
 			if(ispunct(c)) {
 				continue;
 			}
 			// sproti transforma tolower
 			pStr[i++]=tolower((char)c);
 			if(i == current_size) {
 				current_size *= 2;
 				pStr = realloc(pStr, current_size);
 			}
 		}
 	pStr[i] = '\0';
 	}
 	return pStr;
}

void narediSlovar(struct hashMap *slovar, char* besedilo) {
	slovar->steviloBesed = 0;
	unsigned short current_size = 1024;
	slovar->vseBesede = malloc(current_size*sizeof(struct beseda));
	char* split;
	split = strtok(besedilo, splitVrstica);
	while(split != NULL) {
		int indeks = vsebujeBesedo(slovar,split);
		if(indeks != -1) {
			slovar->vseBesede[indeks].steviloPonovitev++;
		}
		else {
			struct beseda trenutna;
			trenutna.crke = malloc(32786*sizeof(char));
			trenutna.crke = split;
			trenutna.steviloPonovitev = 1;
			slovar->vseBesede[slovar->steviloBesed++] = trenutna;
			if(slovar->steviloBesed == current_size) {
				current_size*=2;
				slovar->vseBesede = realloc(slovar->vseBesede, current_size*sizeof(struct beseda));
			}
		}

		split = strtok(NULL,splitVrstica);
	}
}

int cmpfunc (const void * a, const void * b)
{
	struct beseda prva = *(struct beseda*)a;
	struct beseda druga = *(struct beseda*)b;
	if(prva.steviloPonovitev == druga.steviloPonovitev) {
	 	return strcmp(prva.crke, druga.crke);
	}
   	return druga.steviloPonovitev - prva.steviloPonovitev;
}


void izpisiSlovar(struct hashMap slovar, int steviloIzpisov) {
	int i;
	for(i = 0; i < steviloIzpisov; i++) {
		if(i == slovar.steviloBesed){
			break;
		}
		printf("%s %d\n", slovar.vseBesede[i].crke, slovar.vseBesede[i].steviloPonovitev);
	}
}


int main() {


	int steviloIzpisov;
	scanf("%d",&steviloIzpisov);
	char* besedilo = preberiBesedilo();
	struct hashMap slovar;
	narediSlovar(&slovar, besedilo);


	qsort(slovar.vseBesede, slovar.steviloBesed, sizeof(struct beseda), cmpfunc);
	izpisiSlovar(slovar,steviloIzpisov);




	return 0;
}
