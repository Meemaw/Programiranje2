#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#define splitVrstica " ,()"

struct array
{
	int velikost;
	void** array;
};

struct vagon
{
	int VagonID;
	int tezaVagona;
};

struct vlak
{
	int VlakID;
	struct array prikljuceni;
};

struct ukaz 
{
	int VagonID;
	int VlakID;
	int tezaVagona;
	char* Ukaz;
};

struct beseda
{
	char* beseda;
};

int cmprVagon(void* a, void* b) {
	struct vagon* ptra = (struct vagon*)a;
	struct vagon* ptrb = (struct vagon*)b;
	if(ptra->VagonID == ptrb->VagonID) {
		return 1;
	}
	return 0;
}

int komparator(const void* ptra, const void* ptrb) {
	void** a = (void**)ptra;
	void** b = (void**)ptrb;
	struct vlak *vlakA = (struct vlak*)*a;
	struct vlak *vlakB = (struct vlak*)*b;
	return vlakA->VlakID - vlakB->VlakID;
}

int komparatorVagon(const void* ptra, const void* ptrb) {
	void** a = (void**)ptra;
	void** b = (void**)ptrb;
	struct vagon *vagonA = (struct vagon*)*a;
	struct vagon *vagonB = (struct vagon*)*b;
	return vagonA->VagonID - vagonB->VagonID;
}

void dodajElement(struct array *list, void* element){
	int current_size = 10000;
	if(list->velikost == 0){
		list->array = malloc(current_size*sizeof(void*));
	}
	else{
		if(list->velikost == current_size) {
			current_size *= 2;
			list->array = realloc(list->array, current_size*sizeof(void*));
		}
	}
	list->array[list->velikost++] = element;
}

void odstraniElement(struct array *list, void* element, int (*komparator)(void*, void*)) {
	int i;
	int x;
	void** noviList = malloc((list->velikost-1)*sizeof(void*));
	for(i = 0, x = 0; i < list->velikost; i++) {
		if(komparator(list->array[i], element) == 1) {
			continue;
		}
		noviList[x++] = list->array[i];
	}
	list->array = noviList;
	list->velikost--;
}

struct ukaz narediUkaz(char** vrstica) {
	struct ukaz ukaz;
	char* split;
	split = strtok(*vrstica, splitVrstica);
	int i = 0;
	struct beseda *tabela = (struct beseda*)malloc(4*sizeof(struct beseda));
	while(split != NULL) {
		tabela[i++].beseda = split;
		split = strtok(NULL, splitVrstica);
	}
	ukaz.Ukaz = tabela[0].beseda;
	ukaz.VlakID = atoi(tabela[1].beseda);
	ukaz.VagonID = atoi(tabela[2].beseda);
	ukaz.tezaVagona = atoi(tabela[3].beseda);
	return ukaz;
}

void izpisiVlake(struct array *listVlakov) {
	int i;
	int x;
	for(i = 0; i < listVlakov->velikost; i++) {
		int skupnaTeza = 0;
		struct vlak vlak = *(struct vlak*)listVlakov->array[i];
		if(vlak.prikljuceni.velikost == 0) {
			continue;
		}
		printf("%d: ", vlak.VlakID);
		int meja = vlak.prikljuceni.velikost;
		for(x = 0; x < meja; x++) {
			struct vagon vagon = *(struct vagon*)vlak.prikljuceni.array[x];
			printf("%d ", vagon.VagonID);
			skupnaTeza += vagon.tezaVagona;
		}
		printf("(%d)\n", skupnaTeza);
	}
}

int najdiVlak(struct array *listVlakov, int stevilkaVlaka) {
	int i;
	for(i = 0; i < listVlakov->velikost; i++) {
		struct vlak vlak = *(struct vlak*)listVlakov->array[i];
		if(vlak.VlakID == stevilkaVlaka) {
			return i;
		}
	}
	return -1;
}

int najdiVagon(struct array *prikljuceni, int stevilkaVagona) {
	int i;
	for(i = 0; i < prikljuceni->velikost; i++) {
		struct vagon vagon = *(struct vagon*)prikljuceni->array[i];
		if(vagon.VagonID == stevilkaVagona) {
			return i;
		}
	}
	return -1;
}

void izvediUkaz(struct ukaz ukaz, struct array *listVlakov) {
	int stevilkaVlaka = ukaz.VlakID;
	int indeksVlaka = najdiVlak(listVlakov, stevilkaVlaka);

	if(strcmp(ukaz.Ukaz, "P") == 0) {
		struct vlak *vlak;
		if(indeksVlaka == -1) {
			vlak = malloc(sizeof(struct vlak));
			vlak->VlakID = ukaz.VlakID;
			vlak->prikljuceni.velikost = 0;
			dodajElement(listVlakov, vlak);
		}
		else {
			vlak = (struct vlak*)listVlakov->array[indeksVlaka];
		}
		int check = najdiVagon(&vlak->prikljuceni, ukaz.VagonID);
		if(check == -1) {
			struct vagon *vagon = malloc(sizeof(struct vagon));
			vagon->VagonID = ukaz.VagonID;
			vagon->tezaVagona = ukaz.tezaVagona;
			dodajElement(&vlak->prikljuceni, vagon);
		}
	}
	else {
		if(indeksVlaka != -1) {
			struct vlak *vlak = (struct vlak*)listVlakov->array[indeksVlaka];
			int stevilkaVagona = ukaz.VagonID;
			int check = najdiVagon(&vlak->prikljuceni, stevilkaVagona);
			if(check != -1) {
				struct vagon *vagon = (struct vagon*)vlak->prikljuceni.array[check];
				odstraniElement(&vlak->prikljuceni, vagon, cmprVagon);
			}
		}
	}
}


int main() {
	char line[1024];
	char *vrstica;
	struct array listVlakov;
	listVlakov.velikost = 0;


	while(( vrstica = fgets(line,sizeof(line), stdin) ) != NULL) {
		struct ukaz ukaz;
		ukaz = narediUkaz(&vrstica);
		izvediUkaz(ukaz, &listVlakov);
	}
	qsort(listVlakov.array, listVlakov.velikost, sizeof(void*), komparator);
	int i;
	for(i = 0; i < listVlakov.velikost; i++) {
		struct vlak trenutn = *(struct vlak*)listVlakov.array[i];
		qsort(trenutn.prikljuceni.array, trenutn.prikljuceni.velikost, sizeof(void*), komparatorVagon);
	}
	izpisiVlake(&listVlakov);

	return 0;
}
