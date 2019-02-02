#include <stdio.h>
#include <stdlib.h>

int Factorial(int i){
	int j = 1;
	int result = 1;
	for(;j<=i;++j){
		result *= j;
	}
	return result;
}

int nCr(int k, int j){
	int resu = 0;
	resu = Factorial(k)/(Factorial(j)*Factorial(k-j));
	return resu;
}
