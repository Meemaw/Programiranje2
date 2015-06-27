#include<stdio.h>
#define true 1
#define false 0
#define zavijLevo 2
#define zavijDesno 3
#define desno 0
#define dol 1
#define levo 2
#define gor 3

struct Predmet 
{
	int x;
	int y;
	int vrsta;
};

struct tocka
{
	int x;
	int y;
};

struct kaca
{
	int stolpec;
	int vrstica;
	int trenutnaDolzina;
	int smer;
};



void uporabiPredmet(struct kaca *kaca, int vrsta) {
	if(vrsta == 1) {
		kaca->trenutnaDolzina++;
	}
	if(vrsta == zavijLevo) {
		if(kaca->smer == desno) {
			kaca->smer = gor;
		}
		else {
			(kaca->smer)--;
		}
	}
	if(vrsta == zavijDesno) {
		if(kaca->smer == gor) {
			kaca->smer = desno;
		}
		else {
			(kaca->smer)++;
		}
	}
}

void premakniKaco(struct kaca *kaca) {
		if(kaca->smer == desno) {
			kaca->stolpec++;
		}
		else if(kaca->smer == dol) {
			kaca->vrstica++;
		}
		else if(kaca->smer == levo) {
			kaca->stolpec--;
		}
		else if(kaca->smer == gor) {
			kaca->vrstica--;
		}
}

int dolzinaKace(struct Predmet tabela[], int steviloPredmetov,int steviloKorakov) {
	struct kaca kaca;
	kaca.trenutnaDolzina = 1;
	kaca.smer = 0;
	kaca.vrstica = 0;
	kaca.stolpec = 0;
	int jePojedla = false;
	struct tocka ptr[steviloKorakov+1];
	ptr[0].x = kaca.stolpec;
	ptr[0].y = kaca.vrstica;
	int pozicija = 0;

	while(steviloKorakov > 0) {

		jePojedla = false;
		int i;
		struct Predmet uporabljen;
		for(i = 0; i < steviloPredmetov; i++) {
			if(tabela[i].x == kaca.stolpec && tabela[i].y == kaca.vrstica) {
				uporabljen = tabela[i];
				jePojedla = true;
				break;
			}
		}

		if(jePojedla == true) {
			uporabiPredmet(&kaca, uporabljen.vrsta);
		}

		premakniKaco(&kaca);


		int shraniPozicijo = pozicija;

		if(kaca.trenutnaDolzina > 4) {
			int x;
			for(x = 0; x < kaca.trenutnaDolzina; x++) {
				if(ptr[pozicija].x == kaca.stolpec && ptr[pozicija].y == kaca.vrstica) {
					kaca.trenutnaDolzina = 0;
					return kaca.trenutnaDolzina;
				}
				pozicija--;;
			}
		}
		// vprasaj
		pozicija = shraniPozicijo;
		pozicija++;

		ptr[pozicija].x = kaca.stolpec;
		ptr[pozicija].y = kaca.vrstica;

		steviloKorakov--;
	}
	return kaca.trenutnaDolzina;
}




int main() {


	int steviloPredmetov;
	scanf("%d", &steviloPredmetov);
	struct Predmet tabela[steviloPredmetov];


	int i;
	for(i = 0; i < steviloPredmetov; i++) {
		struct Predmet trenutn;
		scanf("%d", &trenutn.y);
		scanf("%d", &trenutn.x);
		scanf("%d", &trenutn.vrsta);
		tabela[i] = trenutn;
	}
	int steviloKorakov;
	scanf("%d", &steviloKorakov);

	int ljubezen = dolzinaKace(tabela,steviloPredmetov,steviloKorakov);
	printf("%d\n", ljubezen);


	return 0;
}
