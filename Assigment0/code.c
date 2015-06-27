#include<stdio.h>

#define true 1
#define false 0

int primeFactors(int stevilo) {
	int stRazlicnih = 0;
	int stDeljiteljev = 0;
	int test;
	int i;
	while(stevilo % 2 == 0) {
		stevilo /= 2;
		stDeljiteljev++;
	}
	for(i = 3; i <= stevilo; i+=2) {
		test = true;
		while(stevilo % i == 0) {
			stevilo /= i;
			stDeljiteljev++;
			if(stDeljiteljev > 2) {
				return 0;
			}
			if(test == true) {
				stRazlicnih++;
				test = false;
			}
		}
	}
	return stRazlicnih;
}

int main() {
	int stevilo;
	scanf("%d", &stevilo);
	if(primeFactors(stevilo) == 2) printf("Y \n");
	else printf("N \n");
	return 0;
}
