#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nCr.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void intToDecASCII(int i, char * integer){
char sign;
if (i < 0){
sign = '-';
i = 0 - i;
}
else{
sign = '+';
}


char as[16];
int k;

int j = 0;
int x;
do{
x = i %10,
as[j] = '0' + x;
i = i/10;
j+=1;

}while(i> 0);
if(sign == '-'){
as[j] = '-';
as[j+1] = '\0';
}
else{
as[j] = '\0';
}

char temp;
j = strlen(as) -1;
for(k =0; k<((j+1)/2); k++){
temp = as[k];
as[k] = as[j-k];
as[j-k] = temp;
}

strcpy(integer,as);

}



int main(int argc, char *argv[]) {

	
	if(argc != 2){
		printf("Error:enter wrong numbers of argument \n");
	} 
	
	if(strcmp(argv[1],"-h") == 0){
		printf("formula <positive integer>");
		exit(1);
	}
	else{
	char digit = argv[1][0];
	if (!isdigit(digit)){
		printf("Error:enter wrong type of argument \n");
		exit(1);
	}
}	
	
	int expo = atoi(argv[1]);
	int i;
	int fact = 1;
	char mid[10] = "*x^";

	char result[20];
	char last[99];
	char qian[30];
	char hou[5];
	int jian = expo;
	for (i = 1;i <= expo;i++){
	
	int	result = nCr(jian,i);


	intToDecASCII(result,qian);

	intToDecASCII(i,hou);
	printf("hou:%s \n",hou);

	strcat(qian,mid);

	strcat(qian,hou);
	printf("qian:%s \n",qian);
	char sign[30] = " + ";
	strcat(sign,qian);
	printf("sign:%s \n",sign);
	
	strcat(last,sign);
	printf("last:%s \n",last);
}
	
	printf("(1+x)^%d", expo);
	printf(" = 1");
	printf("%s \n",last);
	return 0;
	
}
