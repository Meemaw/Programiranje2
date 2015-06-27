#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define KONSTANTA 1
#define OPERACIJA 0
#define OKLEPAJ 2


struct element
{
	char* znaki;
	int tip;
	int prioriteta;
};


struct stack
{
	struct element *elementi;
	int steviloElementov;
	int maxSize;
};

struct izraz
{
	struct element *elementi;
	int steviloElementov;
};


int jeOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int jeOklepaj(char c) {
	return (c == '(' || c == ')');
}


void inicializirajStack(struct stack *stack) {
	stack->steviloElementov = 0;
	stack->maxSize = 1028;
	stack->elementi = malloc(stack->maxSize*sizeof(struct element));
}

int isEmpty(struct stack *stack) {
	if(stack->steviloElementov == 0) {
		return 1;
	}
	return 0;
}

int velikostStacka(struct stack * stack) {
	return stack->steviloElementov;
}

struct element returnLast(struct stack *stack) {
    return stack->elementi[stack->steviloElementov-1];
    if(stack->steviloElementov-1 == -1) {
    	printf("ERROR RETURNING LAST\n");
    }
}

void push(struct stack *stack, struct element element) {
	stack->elementi[stack->steviloElementov++] = element;
	if(stack->steviloElementov == stack->maxSize) {
		stack->maxSize*= 2;
		struct element *relociraj = realloc(stack->elementi, stack->maxSize*sizeof(struct element));
		if(relociraj == NULL) {
			printf("ERROR RELOCATING");
			exit(0);
		}
		stack->elementi = relociraj;
	}
}


void pop(struct stack *stack) {
	stack->steviloElementov--;
	if(stack->steviloElementov == -1) {
		printf("ERROR TOO FEW ELEMENTS ON STACK\n");
	}
}

void izpisiStack(struct stack *stack) {
	int i;
	for(i = 0; i < stack->steviloElementov; i++) {
		struct element element = stack->elementi[i];
		printf("%s ", element.znaki);
	}
	printf("\n");
}

int dolociPrioriteto(char c) {
	if(c == '*') {
		return 3;
	}
	else if(c == '/') {
		return 3;
	}
	else if(c == '+') {
		return 2;
	}
	else if(c == '-') {
		return 2;
	}
	return 0;
}


void preberiVhod(struct izraz *izraz) {

	struct element *elementi;
	izraz->steviloElementov = 0;
	int current_size = 1028;
	elementi = malloc(current_size * sizeof(struct element));

	char c = EOF;
	char* beseda;
	while((c = fgetc(stdin) ) != EOF) {
		beseda = malloc(20*sizeof(char));
		int dolzinaBesede = 0;
		beseda[dolzinaBesede++] = c;
		if(jeOperator(c) || jeOklepaj(c)) {
			beseda[dolzinaBesede] = '\0';
			struct element e;
			if(jeOperator(c)) {
				e.tip = OPERACIJA;
			}
			else {
				e.tip = OKLEPAJ;
			}
			e.znaki = beseda;
			e.prioriteta = dolociPrioriteto(c);
			elementi[izraz->steviloElementov++] = e;
		}
		else if(c != ' ' && c != '\n'){
			while((c = fgetc(stdin) ) != EOF) {
				if(jeOklepaj(c) || jeOperator(c)) {
					beseda[dolzinaBesede] = '\0';
					struct element stari;
					stari.znaki = beseda;
					stari.tip = KONSTANTA;
					stari.prioriteta = 0	;
					elementi[izraz->steviloElementov++] = stari;
					char* noviZnak = malloc(2*sizeof(char));
					noviZnak[0] = c;
					noviZnak[1] = '\0';
					struct element e;
					e.znaki = noviZnak;
					if(jeOklepaj(c)) {
						e.tip = OKLEPAJ;
					}
					else{
						e.tip = OPERACIJA;
					}
					e.prioriteta = dolociPrioriteto(c);
					elementi[izraz->steviloElementov++] = e;
					beseda = NULL;
					break;
				}
				else{
					beseda[dolzinaBesede++] = c;
				}
			}
			if(beseda != NULL) {
				beseda[dolzinaBesede] = '\0';
				struct element stari;
				stari.znaki = beseda;
				stari.tip = KONSTANTA;
				stari.prioriteta = 0;
				elementi[izraz->steviloElementov++] = stari;
			}
		}
		if(izraz->steviloElementov + 2 >= current_size) {
			current_size *= 2;
			struct element *relociraj = realloc(elementi, current_size * sizeof(struct element));
			if(relociraj == NULL) {
				printf("ERROR RELOCATING");
				exit(0);
			}
			elementi = relociraj;
		}
	}
	izraz->elementi = elementi;
}

int najdiOklepaj(struct izraz *izraz, int indeks) {
	int preveri = 1;
	while(indeks >= 0) {
		if(strcmp(izraz->elementi[indeks].znaki , "(") == 0) {
			preveri--;
		}
		if(strcmp(izraz->elementi[indeks].znaki, ")") == 0) {
			preveri++;
		}
		if(preveri == 0) {
			return indeks-1;
		}
		indeks--;
	}
	return -5;
}


int uporabiMinus(struct izraz *izraz, int i) {
	// ce je naslednji element konstanta
	if(izraz->elementi[i+1].tip == KONSTANTA) {
		// ce je pozitiven ga pretvorimo v negativnega
		if(izraz->elementi[i+1].znaki[0] != '-') {
			char* string = malloc(30*sizeof(char));
			sprintf(string, "-%s", izraz->elementi[i+1].znaki);
			izraz->elementi[i+1].znaki = string;
		}
		if(i-1 < 0 || (izraz->elementi[i-1].tip != KONSTANTA && strcmp(izraz->elementi[i-1].znaki, ")") != 0)) {
			return 0;
		}
	}
	else if(izraz->elementi[i+1].tip == OKLEPAJ) {
		if(i-1 < 0 || (izraz->elementi[i-1].tip != KONSTANTA && strcmp(izraz->elementi[i-1].znaki, ")") != 0)) {
			return 0;
		}
	}
	return 1;
}

void preveriPredOklepaj(struct izraz *izraz, int i, struct stack *outputStack) {
	int predOklepajem = najdiOklepaj(izraz, i);
	if(predOklepajem >= 0 && strcmp(izraz->elementi[predOklepajem].znaki, "-") == 0) {
		struct element mnozenjeMinus;
		mnozenjeMinus.znaki = "-1";
		mnozenjeMinus.tip = KONSTANTA;
		mnozenjeMinus.prioriteta = 0;
		push(outputStack, mnozenjeMinus);
		struct element mnozenje;
		mnozenje.znaki = "*";
		mnozenje.tip = OPERACIJA;
		mnozenje.prioriteta = 3;
		push(outputStack, mnozenje);
	}
}


struct stack reversePolishNotation(struct izraz *izraz) {
	struct stack operatorStack;
	struct stack outputStack;
	inicializirajStack(&operatorStack);
	inicializirajStack(&outputStack);

	int i;
	for(i = 0; i < izraz->steviloElementov; i++) {
		struct element trenutn = izraz->elementi[i];
		if(trenutn.tip == KONSTANTA) {
			push(&outputStack, trenutn);
		}
		else if(trenutn.tip == OPERACIJA) {
			if(strcmp(trenutn.znaki, "-") == 0) {
				if(uporabiMinus(izraz, i)) {
					struct element novi;
					novi.znaki = "+";
					novi.tip = OPERACIJA;
					novi.prioriteta = 2;
					trenutn = novi;
				}
				else {
					continue;
				}
				
			}
			while(trenutn.prioriteta <= returnLast(&operatorStack).prioriteta) {
				push(&outputStack, returnLast(&operatorStack));
				pop(&operatorStack);
			}
			push(&operatorStack, trenutn);
		}
		else if(trenutn.tip == OKLEPAJ) {
			if(strcmp(trenutn.znaki,"(") == 0) {
				push(&operatorStack, trenutn);
			}
			else {
				while(strcmp(returnLast(&operatorStack).znaki,"(") != 0) {
					push(&outputStack, returnLast(&operatorStack));
					pop(&operatorStack);
				}
				pop(&operatorStack);
				preveriPredOklepaj(izraz,i-1,&outputStack);
			}
		}
	}
	while(isEmpty(&operatorStack) == 0) {
		push(&outputStack, returnLast(&operatorStack));
		pop(&operatorStack);
	}
	return outputStack;
}


long izracunajPredhodna(char* znaki, long prvo, long drugo){
	if(strcmp(znaki, "-") == 0) {
		return prvo - drugo;
	}
	else if(strcmp(znaki, "+") == 0) {
		return prvo + drugo;
	}
	else if(strcmp(znaki, "/") == 0) {
		return prvo / drugo;
	}
	else if(strcmp(znaki, "*") == 0) {
		return prvo * drugo;
	}
	return 0;
}

int minusPogoj(struct stack *polishNotation, int i) {
	return ((strcmp(polishNotation->elementi[i].znaki, "*") == 0 || strcmp(polishNotation->elementi[i].znaki, "/") == 0) && polishNotation->elementi[i-1].znaki[0] == '-' && polishNotation->elementi[i+1].znaki[0] == '-');
}


long parsePolishNotation(struct stack *polishNotation) {
	int i;
	struct stack novi;
	inicializirajStack(&novi);
	for(i = 0; i < velikostStacka(polishNotation); i++) {
		if(polishNotation->elementi[i].tip == KONSTANTA) {
			push(&novi, polishNotation->elementi[i]);
		}
		else if(polishNotation->elementi[i].tip == OPERACIJA){
			long drugoStevilo = atol(returnLast(&novi).znaki);
			pop(&novi);
			long prvoStevilo = atol(returnLast(&novi).znaki);
			pop(&novi);
			long zracunaj = izracunajPredhodna(polishNotation->elementi[i].znaki, prvoStevilo, drugoStevilo);
			struct element pushaj;
			char* str = malloc(30*sizeof(char));
			sprintf(str, "%ld", zracunaj);
			pushaj.znaki = str;
			pushaj.tip = KONSTANTA;
			pushaj.prioriteta = 0;
			push(&novi, pushaj);
		}
		else {
			printf("WRONG OPERATOR ON STACK\n");
			printf("%s\n", polishNotation->elementi[i].znaki);
		}
	}
	if(novi.steviloElementov == 1) {
		return atol(returnLast(&novi).znaki);
	}
	else{
		printf("TOO MANY ELEMENTS AT END \n");
		izpisiStack(&novi);
		exit(0);
		return 0;
	}
}





int main() {
	struct izraz izraz;
	preberiVhod(&izraz);
	struct stack polishNotation = reversePolishNotation(&izraz);
	long rezultat = parsePolishNotation(&polishNotation);
	printf("%ld\n", rezultat);

}
