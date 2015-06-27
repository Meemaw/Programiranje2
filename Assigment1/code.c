#include<stdio.h>
#include <stdlib.h>

struct Ploscica
{
	int sirina;
	int dolzina;
};


int greGor(struct Ploscica p1, struct Ploscica p2) {
	if((p1.dolzina < p2.dolzina && p1.sirina < p2.sirina) || (p1.dolzina < p2.sirina && p1.sirina < p2.dolzina)) {
		return 1;
	}
	return 0;
}


int steviloMoznosti (struct Ploscica tabela[], int velikost, int memo[], int trenutnIx) {
	struct Ploscica trenutna = tabela[trenutnIx];
	if(memo[trenutnIx] != -1) {
		return memo[trenutnIx];
	}
	int max = 0;
	int i;
	for(i = 0; i < velikost; i++) {
		if(greGor(tabela[i],trenutna)) {
			int trenutnoStevilo = steviloMoznosti(tabela,velikost,memo,i);
			if(trenutnoStevilo > max) {
				max = trenutnoStevilo;
			}
		}
	}
	memo[trenutnIx] = max + 1;
	return memo[trenutnIx];
}



int main() {
	int steviloPloscic;
	scanf("%d", &steviloPloscic);
	struct Ploscica tabela[steviloPloscic];
	int memo[steviloPloscic];
	int i;
	for(i = 0; i < steviloPloscic; i++) {
		memo[i] = -1;
		struct Ploscica trenutna;
		scanf("%d", &trenutna.sirina);
		scanf("%d", &trenutna.dolzina);
		tabela[i] = trenutna;
	}

	int max = 0;
	for(i = 0; i < steviloPloscic; i++) {
		int trenutnoStevilo = steviloMoznosti(tabela,steviloPloscic,memo,i);
		if(trenutnoStevilo > max) {
			max = trenutnoStevilo;
		}
	}

	printf("%d\n", max);
	return 0;
}
