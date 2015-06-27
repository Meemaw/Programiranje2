#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct program
{
	char znaki[60000];
	int steviloZnakov;
};


int findClosingBrace(struct program program, int index) {
	int stevilo = 1;
	while(stevilo != 0) {
		if(program.znaki[index] == '[') {
			stevilo++;
		}
		if(program.znaki[index] == ']') {
			stevilo--;
		}

		if(stevilo == 0) {
			return index;
		}
		index++;
	}
	printf("ERROR\n");
	return index;
}


char* pozeni(struct program program, char* ptr, int indeksZnakov) {
	int ixPrograma;
	for(ixPrograma = indeksZnakov; ixPrograma < program.steviloZnakov; ixPrograma++) {
		char c = program.znaki[ixPrograma];

		switch(c)
		{
			case '+' :
				++*ptr;
				break;

			case '-' :
				--*ptr;
				break;
			case '>' :
				ptr++;
				break;
			case '<' :
				ptr--;
				break;
			case '.' :
				putchar(*ptr);
				break;
			case ',' :
				*ptr = getchar();
				fputs("NOT IMPLEMENTED", stderr);
				exit(0);
				break;
			case '[' :
				while(*ptr != 0) {
					ptr = pozeni(program, ptr, ixPrograma+1);
				}
				ixPrograma = findClosingBrace(program, ixPrograma+1);
				break;
			case ']' :
				return ptr;
		}
	}
	return ptr;
}


int validChar(char c) {
	if(c == '+' || c == '-' || c == '<' || c == '>'|| c == '[' || c == ']' || c == '.') {
		return 1;
	}
	return 0;
}

void narediArray(struct program* program) {
	int trenutnaPozicija = 0;
	program->steviloZnakov = 0;
	char c = EOF;
	while((c = getchar() ) != EOF) {
		if(validChar(c) == 1) {
			program->znaki[trenutnaPozicija++] = c;
			program->steviloZnakov++;
		}
	}
	program->znaki[trenutnaPozicija] = '\0';
}


int main() {

	char trak[30000] = {0};
	char* ptr = trak;

	struct program program;
	narediArray(&program);
	int ixPrograma = 0;
	pozeni(program, ptr, ixPrograma);


	return 0;
}
