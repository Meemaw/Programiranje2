#include<stdio.h>
#include <stdlib.h>
#include<string.h>

char izberiZnak(int sivina, char* tabelaCharov, int* tabelaIntov) {
    for(int i = 0; i < 9; i++) {
        if(sivina >= tabelaIntov[i]) {
            return tabelaCharov[i];
        }
    }
    return 'e';
}





void preberiFile(char* inputName, char* outputName, int velikostOkna) {
    FILE* odpri;
    odpri = fopen(inputName, "rb");
    int sirinaSlike, visinaSlike, red, green, blue, piksli, novPiksl;
    char read_string[100];
    char* split;
    
    
    
    // preberemo prve 3 vrstice (glava slike)
    for(int i = 0; i < 3; i++) {
        fgets(read_string,sizeof(read_string),odpri);
        if(i == 1) {
            split = strtok(read_string, " ");
            sirinaSlike = atoi(split);
            split = strtok(NULL, " ");
            visinaSlike = atoi(split);
        }
    }
    int** tabelaPikslov;
    tabelaPikslov = (int**) malloc(sizeof(int*) * visinaSlike);
    
    
    // preberemo vse piksle in jih shranimo v tabelo
    for(int i = 0; i < visinaSlike; i++) {
        tabelaPikslov[i] = (int*)malloc(sizeof(int)*sirinaSlike);
        for(int x = 0; x < sirinaSlike; x++) {
            red = fgetc(odpri);
            green = fgetc(odpri);
            blue = fgetc(odpri);
            piksli = (red + green + blue);
            tabelaPikslov[i][x] = piksli;
        }
    }
    
    int tabelaIntov[9];
    tabelaIntov[0] = 230;
    tabelaIntov[1] = 200;
    tabelaIntov[2] = 180;
    tabelaIntov[3] = 160;
    tabelaIntov[4] = 130;
    tabelaIntov[5] = 100;
    tabelaIntov[6] = 70;
    tabelaIntov[7] = 50;
    tabelaIntov[8] = 0;
    
    char tabela[9];
    tabela[0] = ' ';
    tabela[1] = '.';
    tabela[2] = '\'';
    tabela[3] = ':';
    tabela[4] = 'o';
    tabela[5] = '&';
    tabela[6] = '8';
    tabela[7] = '#';
    tabela[8] = '@';
    
    FILE* zapisi;
    zapisi = fopen(outputName, "w");
    char izpisi;
    
    
    
    int delimo = velikostOkna * velikostOkna * 3;
    
    // pripravimo novo tabelo glede na velikost okna
    for(int i = 0; i < visinaSlike; i+= velikostOkna) {
        for(int x = 0; x < sirinaSlike; x+= velikostOkna) {
            
            novPiksl = 0;
            int mejaA = i + velikostOkna;
            int mejaB = x + velikostOkna;
            
            // gremo skozi kvadrat velikostOkna*velikostOkna in izracunamo povprecen piksel
            for(int a = i; a < mejaA; a++) {
                for(int b = x; b < mejaB; b++) {
                    novPiksl+= tabelaPikslov[a][b];
                }
            }
            int sivina = novPiksl / delimo;
            izpisi = izberiZnak(sivina, tabela, tabelaIntov);
            fputc(izpisi, zapisi);
        }
        fprintf(zapisi, "\n");
    }
    
    free(tabelaPikslov);
    fclose(zapisi);
    fclose(odpri);
}



int main() {
    
    
    char inputName[256];
    char outputName[256];
    int velikostOkna;
    
    scanf("%s", inputName);
    scanf("%s", outputName);
    scanf("%d", &velikostOkna);
    
    
    preberiFile(inputName, outputName, velikostOkna);
    
    
    
    
    return 0;
}
