#include<stdio.h>
#include<stdlib.h>


int steviloVeder;
int zahtevanaKolicina;
int *velikostiVeder;

struct vedro
{
	unsigned short trenutnoStanje;
};

struct stanje
{
	struct vedro *tabela;
};

struct kolekcijaStanj
{
	struct stanje *stanja;
	int steviloStanj;
	int moznaStanja;
};

struct array
{
	int velikost;
	struct stanje* array;
	int maxSize;
};


struct hashTable 
{
	struct array *bucket;
	int velikostTabele;
	int steviloElementov;
};

struct hashTable vsaStanja;


void inicializirajTabeloPrivate(struct hashTable *hashTable, int velikost) {
	hashTable->velikostTabele = velikost;
	hashTable->steviloElementov = 0;
	hashTable->bucket = malloc(hashTable->velikostTabele * (sizeof(struct array)));
	int i;
	for(i = 0; i < hashTable->velikostTabele; i++) {
		hashTable->bucket[i].velikost = 0;
		hashTable->bucket[i].maxSize = 10;
	}
}

int komparator(struct stanje prvo, struct stanje drugo){
	int i;
	for(i = 0; i < steviloVeder; i++){
		if(prvo.tabela[i].trenutnoStanje != drugo.tabela[i].trenutnoStanje)
			return 0;
	}
	return 1;
}

unsigned int hasher(struct stanje stanje) {

    unsigned int hash = 0;
    int i;
    for (i = 0 ; i < steviloVeder ; i++)
    {
        hash = ((hash<<5)+hash) + stanje.tabela[i].trenutnoStanje;
    }
    return hash;
}

int vsebujeElement(struct array list, struct stanje element){
	//printf("Enter vsebuje element");
	//printf("%d\n", list.velikost);
	int i;
	for(i = 0; i < list.velikost; i++) {
		if(komparator(list.array[i], element) == 1) {
	//printf("exit vsebuje element");
			return 1;
		}
	}
	//printf("exit vsebuje element");
	return 0;
}

void dodajElement(struct array *list, struct stanje element){
	if(list->velikost == 0){
		list->array = (struct stanje*)malloc(list->maxSize*sizeof(struct stanje));
	}
	else{
		if(list->velikost == list->maxSize) {
			list->maxSize *= 2;
			list->array = (struct stanje*)realloc(list->array, list->maxSize*sizeof(struct stanje));
		}
	}
	list->array[list->velikost++] = element;
	//printf("Exit dodaj element\n");
}

int vsebuje(struct stanje element, struct hashTable *hashTable) {
	//printf("Enter vsebuje");
	unsigned int hash = hasher(element)%hashTable->velikostTabele;

	//printf("%d\n", hash);
	struct array podArray = hashTable->bucket[hash];
	int val = vsebujeElement(podArray, element);
	//printf("Exit vsebuje");
	return val;
}

void vstavi(struct stanje element, struct hashTable *hashTable) {

	unsigned int hash = hasher(element)%hashTable->velikostTabele;
	struct array *podArray = &(hashTable->bucket[hash]);
	dodajElement(podArray, element);
	hashTable->steviloElementov++;
}



void napolniVedro(struct vedro *vedro, int i) {
	vedro->trenutnoStanje = velikostiVeder[i];
}

int jePolno(struct vedro *vedro, int i) {
	return vedro->trenutnoStanje == velikostiVeder[i];
}

int stanjeVedra(struct vedro *vedro) {
	return vedro->trenutnoStanje;
}

void zprazniVedro(struct vedro *vedro) {
	vedro->trenutnoStanje = 0;
}

int lahkoPrelijem(struct vedro *prvo, struct vedro *drugo, int indeksPrvo, int indeksDrugo) {
	if(prvo->trenutnoStanje == 0 || drugo->trenutnoStanje == velikostiVeder[indeksDrugo]) {
		return 0;
	}
	else {
		return prvo->trenutnoStanje >= velikostiVeder[indeksDrugo]-drugo->trenutnoStanje || velikostiVeder[indeksDrugo]-drugo->trenutnoStanje >= prvo->trenutnoStanje;
	}
	
}

void prelij(struct vedro *prvo, struct vedro *drugo, int indeksPrvo, int indeksDrugo) {
	if(prvo->trenutnoStanje >= velikostiVeder[indeksDrugo]-drugo->trenutnoStanje) {
		prvo->trenutnoStanje -= velikostiVeder[indeksDrugo]-drugo->trenutnoStanje;
		drugo->trenutnoStanje = velikostiVeder[indeksDrugo];
	}
	else {
		drugo->trenutnoStanje += prvo->trenutnoStanje;
		prvo->trenutnoStanje = 0;
	}
}



int jeKonec(struct stanje stanje){
	int i;
	for(i = 0; i < steviloVeder; i++) {
		if(stanje.tabela[i].trenutnoStanje == zahtevanaKolicina) {
			return 1;
		}
	}
	return 0;
}

int jeKonecPrograma(struct kolekcijaStanj kolekcija) {
	int i;
	for(i = 0; i < kolekcija.steviloStanj; i++) {
		if(jeKonec(kolekcija.stanja[i])) {
			return 1;
		}
	}
	return 0;
}


void izpisiStanje(struct stanje stanje){ 
    int i;
    printf("[");
    for(i=0; i<steviloVeder; i++) {
        printf("%d ", stanje.tabela[i].trenutnoStanje);
    }
    printf("]\n");
} 

void izpisiKolekcijo(struct kolekcijaStanj *kolekcija) {
	int i;
	for(i = 0; i < kolekcija->steviloStanj; i++) {
		izpisiStanje(kolekcija->stanja[i]);
	}
	printf("\n");
}


int primerjajStanji(struct stanje *ena, struct stanje *dva) {
	int i;
	for(i = 0; i < steviloVeder; i++) {
		if(ena->tabela[i].trenutnoStanje != dva->tabela[i].trenutnoStanje) {
			return 0;
		}
	}
	return 1;
}

int zeObstajaStanje(struct kolekcijaStanj *kolekcijaStanj, struct stanje *trenutno) {
	int i;
	for(i = 0; i < kolekcijaStanj->steviloStanj; i++) {
		if(primerjajStanji(&kolekcijaStanj->stanja[i], trenutno) == 1) {
			return 1;
		}
	}
	return 0;
}





struct vedro *kopirajTabelo(struct vedro *tabela) {
	int i;
	struct vedro *novaTabela = malloc(steviloVeder*sizeof(struct vedro));
	for(i = 0; i < steviloVeder; i++) {
		novaTabela[i] = tabela[i];
	}
	return novaTabela;
}


int dodajNaKolekcijo(struct kolekcijaStanj *kolekcija, struct stanje dodaj) {
	if(jeKonec(dodaj)) {
		kolekcija->stanja[kolekcija->steviloStanj++] = dodaj;
		return 1;
	}
	if(!vsebuje(dodaj, &vsaStanja)) {
		kolekcija->stanja[kolekcija->steviloStanj++] = dodaj;
		if(kolekcija->steviloStanj == kolekcija->moznaStanja) {
			kolekcija->moznaStanja*=2;
			struct stanje *novaStanja = realloc(kolekcija->stanja, kolekcija->moznaStanja*sizeof(struct stanje));
			if(novaStanja == NULL) {
				printf("ERROR RELOCATING");
				exit(0);
			}
			kolekcija->stanja = novaStanja;
		}
		vstavi(dodaj, &vsaStanja);
	}
	return 0;
}




int generirajStanja(struct kolekcijaStanj *kolekcija, struct vedro *tabela){
	int i;
	int x;

	for(i = 0; i < steviloVeder; i++) {
		struct vedro trenutno = tabela[i];
		// NAPOLNIMO VSA VEDRA
		if(!jePolno(&trenutno, i)) {
			struct vedro *novaTabela = kopirajTabelo(tabela);
			napolniVedro(&novaTabela[i], i);
			struct stanje stanje;
			stanje.tabela = novaTabela;
			int a = dodajNaKolekcijo(kolekcija, stanje);
			if(a) {
				return 1;
			}
			
		}
		// IZPRAZNIMO VSA VEDRA
		if(trenutno.trenutnoStanje != 0) {
			struct vedro *novaTabela = kopirajTabelo(tabela);
			zprazniVedro(&novaTabela[i]);
			struct stanje stanje;
			stanje.tabela = novaTabela;
			int a = dodajNaKolekcijo(kolekcija, stanje);
			if(a) {
				return 1;
			}
			
		}
		// PRELIJEMO VSA VEDRA
		for(x = 0; x < steviloVeder; x++) {
			struct vedro novo = tabela[x];
			if(i == x) {
				continue;
			}
			if(lahkoPrelijem(&trenutno,&novo, i , x)) {
				struct stanje stanje;
				struct vedro *novaTabela = kopirajTabelo(tabela);
				prelij(&novaTabela[i], &novaTabela[x], i, x);
				stanje.tabela = novaTabela;
				int a = dodajNaKolekcijo(kolekcija, stanje);
				if(a) {
					return 1;
				}
			}
		}

	}
	return 0;
}




int main() {
	//setbuf(stdout, NULL);

	// PREBRAN VHOD
	scanf("%d", &steviloVeder);
	int i;
	struct stanje stanje;
	velikostiVeder = malloc(steviloVeder*sizeof(int));
	stanje.tabela = malloc(steviloVeder*sizeof(struct vedro));
	for(i = 0; i < steviloVeder; i++) {
		scanf("%d", &velikostiVeder[i]);
		stanje.tabela[i].trenutnoStanje = 0;
	}
	scanf("%d", &zahtevanaKolicina);
	// PREBRAN VHOD
	//printf("STEVILO VEDER: %d\n", steviloVeder);
	//printf("ZELJENA KOLICINA: %d\n", zahtevanaKolicina);

	// INICIALIZACIJA STANJ
	struct kolekcijaStanj kolekcijaStanj;
	struct kolekcijaStanj stara;
	inicializirajTabeloPrivate(&vsaStanja, 100000);
	scanf("%d", &zahtevanaKolicina);
	kolekcijaStanj.moznaStanja = 1000;
	stara.moznaStanja = 1000;
	kolekcijaStanj.stanja = malloc(kolekcijaStanj.moznaStanja*sizeof(struct stanje));
	stara.stanja = malloc(stara.moznaStanja*sizeof(struct stanje));
	stara.steviloStanj = 1;
	stara.stanja[0] = stanje;
	kolekcijaStanj.steviloStanj = 0;
	// INICIALIZACIJA STANJ
	

	int steviloKorakov = 0;

	// DOKLER SE PROGRAM NE ZAKLJUČI
	while(!jeKonecPrograma(stara)) {
		
		steviloKorakov++;
		// for zanka skoz vsako stanje za generiranje stanj
		for(i = 0; i < stara.steviloStanj; i++) {
			stanje = stara.stanja[i];
			int a = generirajStanja(&kolekcijaStanj, stanje.tabela);
			if(a) {
				break;
			}
		}
		// stara se bo uporabla v naslednji iteraciji, kolekcijaStanj gre na nič za nova stanja
		struct kolekcijaStanj temp = stara;
		stara = kolekcijaStanj;
		kolekcijaStanj = temp;
		kolekcijaStanj.steviloStanj = 0;


		//izpisiKolekcijo(&stara);
		//printf("ITEARCIJA, STEVILO STANJ %d %d\n", steviloKorakov, vsaStanja.steviloElementov);
	}
	// DOKLER SE PROGRAM NE ZAKLJUČI
	printf("%d\n", steviloKorakov);

	return 0;
}
