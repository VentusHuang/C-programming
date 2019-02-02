#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include "y86emul.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int rege[8];
int counter;
int size;
unsigned char * mem;
int OF,ZF,SF;

Status status = AOK;

unsigned char first;
unsigned char second;
unsigned char inchar;
int inum;
int amount;
int total;
int addres; 

void regdest(unsigned char * reg1, unsigned char * reg2)
{
	int temp = mem[counter+1];
	*reg1 = (temp & 0xf0);
	*reg1 = *reg1>>4;
	*reg2 = (temp & 0x0f);
}


union charr{
	char cr[4];
	int l;
};

union charr change;

void pp(){

	int b = 0;
	int i;
if (rege[4] > size){
		status = ADR;
		printf("Addrese overflow");
		return;
	}
	else{
		rege[4] -= 4;
		b = rege[4];
	}
	
	for(i = 0; i< 4;i++){
		mem[b+i] = change.cr[i];
	}
}
void rrmovl(){
	
			regdest(&first,&second);

			if (first >= 0 && first < 8 && second >= 0 && second < 8){
			rege[second] = rege[first];
		}
			counter += 2;
}

void irmovl(){
	regdest(&first,&second);
	if(first != 15 || (second < 0 && second >=8)){
		status = ADR;
		printf("first argumetn should be f and second argument should between 0 and 8");
		return;
	}
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+2];
	} 
	amount = change.l;
	rege[second] = amount;
	
	counter += 6;
	
}

void rmmovl(){
	regdest(&first,&second);
	if((second < 0 && second >=8) || (first < 0 && first >=8)){
	status = ADR;
	printf("Do not have this register");
	return;
	}
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+2];
	} 
	
	amount = change.l + rege[second];
	if(amount >= size - 3){
		status = ADR;
		printf("Address overflow");
		return;
	}
	change.l = rege[first];
	
	for(i = 0;i<4;i++){
		mem[amount+i] = change.cr[i];
	}
	
	counter += 6;
	
}

void mrmovl(){
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+2];
	} 
	regdest(&first,&second);
	if((second < 0 || second >=8) || (first < 0 || first >=8)){
	status = ADR;
	printf("Do not have this register");
	return;
	}
	
	amount = change.l+rege[second];
	if(amount >= size - 3){
		status = ADR;
		printf("Address overflow");
		return;
	}
	for(i = 0; i < 4;i++){
	change.cr[i] = mem[amount+i];
}
	rege[first] = change.l;
	counter += 6;
}

void add(){
	regdest(&first,&second);
	int a = rege[first];
	int b = rege[second];
	int total = a + b;
	ZF = OF = SF = 0;
	
	if(total == 0){
		ZF = 1;
	}
	else if(total < 0){
		SF = 1;
	}
	
	if (total < 0 ){
		if (a > 0){
			if (b >0){
				OF = 1;
			}
		}
	}
	
	if (total> 0 ){
		if (a < 0){
			if (b < 0){
				OF = 1;
			}
		}
	}
	rege[second] = total;
	counter += 2;
}

void sub(){
	regdest(&first,&second);
	int a = rege[first];
	int b = rege[second];
	int total = b - a;
	ZF = OF = SF = 0;
	
	if(total == 0){
		ZF = 1;
	}
	else if(total < 0){
		SF = 1;
	}
	
	if (b < 0 ){
		if (a > 0){
			if (total > 0){
				OF = 1;
			}
		}
	}
	
	if (total< 0 ){
		if (a < 0){
			if (b > 0){
				OF = 1;
			}
		}
	}
	rege[second] = total;
	counter += 2;
}

void andl(){
	regdest(&first,&second);
	ZF  = SF = 0;
	rege[second] = rege[first] & rege[second];
	if(rege[second] == 0){
		ZF = 1;
	}
	if(rege[second] < 0){
		SF = 1;
	}
	counter += 2;
	
}

void xorl(){
	regdest(&first,&second);
	ZF  = SF = 0;
	rege[second] = rege[first] ^ rege[second];
	if(rege[second] == 0){
		ZF = 1;
	}
	if(rege[second] < 0){
		SF = 1;
	}
	counter += 2;
}

void mul(){
	regdest(&first,&second);
	int a = rege[first];
	int b = rege[second];
	int total = b * a;
	ZF = OF = SF = 0;
	if(total == 0){
		ZF = 1;
	}
	else if(total < 0){
		SF = 1;
	}
	if (a > 0 && b > 0 && total < 0){
		OF =1;
	}
	else if (a > 0 && b < 0 && total > 0){
		OF =1;
	}
	else if (a < 0 && b > 0 && total > 0){
		OF =1;
	}
	else if (a < 0 && b < 0 && total < 0){
		OF =1;
	}
	rege[second] = total;
	counter += 2;
}

void cmp(){
	regdest(&first,&second);
	ZF = OF = SF = 0;
	int total = rege[second] - rege[first];
	if (total == 0){
		ZF = 1;
	}
	else if(total < 0){
		SF =1;
	}
	
	if (rege[second] < 0 ){
		if (rege[first] > 0){
			if (total > 0){
				OF = 1;
			}
		}
	}
	
	if (total< 0 ){
		if (rege[first] < 0){
			if (rege[second] > 0){
				OF = 1;
			}
		}
	}
	
	counter += 2;
}

void jmp(){
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+1];
	} 
	counter = change.l;
}

void jle(){
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+1];
	} 
	if(ZF == 1){
		counter = change.l;
	}
	else if((SF^OF)){
		counter = change.l;
	}
	else{
		counter += 5;
	}
}

void jl(){
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+1];
	} 
	if ((SF^OF)){
		counter = change.l;
	}
	else{
		counter += 5;
	}
}

void je(){
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+1];
	} 
	if(ZF == 1){
		counter = change.l;
	}
	else{
		counter += 5;
	}
}

void jne(){
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+1];
	} 
	if(ZF == 0){
		counter = change.l;
	}
	else{
		counter += 5;
	}
}

void jge(){
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+1];
	} 
	if(!(SF^OF)){
		counter = change.l;
	}
	else{
		counter += 5;
	}
}

void jg(){
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+1];
	} 
	if(ZF == 0){
		if(!(SF^OF)){
			counter = change.l;
		}
	}
	else{
		counter += 5;
	}
}

void call(){
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+1];
	}
	int a = counter +5;
	
	counter = change.l;
	change.l = a;
	pp();
	
}

void po(){
	int i;
	int j = rege[4];
	rege[4] += 4;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[j+i];
	}
	
}

void ret(){
	po();
	counter = change.l;
	
}

void push(){
	regdest(&first,&second);
	if(first < 0 || first >=8){
	status = ADR;
	printf("Do not have this register");
	return;
	}
	change.l = rege[first];
	pp();
	counter +=2;
}

void pop(){
	po();
	regdest(&first,&second);
	if(first < 0 || first >=8){
	status = ADR;
	printf("Do not have this register");
	return;
	}
	rege[first] = change.l;
	counter += 2;
}

void readb(){
	regdest(&first,&second);
	if(first < 0 || first >=8){
	status = ADR;
	printf("Do not have this register");
	return;
	}
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+2];
	} 
	ZF = 0;
	if (scanf("%c",&inchar) == EOF){
		ZF = 1;
	}
	mem[rege[first]+change.l] = inchar;
	counter += 6;
}

void readl(){
	regdest(&first,&second);
	if(first < 0 || first >=8){
	status = ADR;
	printf("Do not have this register");
	return;
	}
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+2];
	} 

	ZF = 0;
	
	if (scanf("%d",&inum) == EOF){
		ZF = 1;
	}
	if (inum >= 13){
		status = INS;
		printf("Interger can only lower than 13 \n");
	}
	amount = change.l + rege[first];
	change.l = inum;
	for(i = 0; i< 4;i++){
		mem[amount+i] = change.cr[i];
	}
	counter += 6;
	
}



void writeb(){
	regdest(&first,&second);
	if(first < 0 || first >=8){
	status = ADR;
	printf("Do not have this register");
	return;
	}
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+2];
	} 
	char a = (char)mem[rege[first] + change.l];
	printf("%c",a);
	counter += 6;
}

void writel(){
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+2];
	} 
	amount = change.l;
	regdest(&first,&second);
	amount += rege[first];
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[amount+i];
	} 
	int back = change.l;
	printf("%d",back);
	counter += 6;
	
}

void movsb(){
	regdest(&first,&second);
	if((second < 0 || second >=8) || (first < 0 || first >=8)){
	status = ADR;
	printf("Do not have this register");
	return;
	}
	int i;
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[counter+i+2];
	} 
	amount = change.l;
	change.l = rege[second];
	inchar = change.cr[i];
	amount += rege[second];
	
	for(i = 0; i< 4;i++){
		change.cr[i] = mem[amount+i];
	} 
	counter += 6;
	rege[first] = change.l;
}

void decode(){
	switch(mem[counter]){
		case 0x00:
			counter ++;
			break;
		case 0x10:
			status = HLT;
			break;
		case 0x20:
			rrmovl();
			break;
		case 0x30:
			irmovl();
			
			break;
		case 0x40:
			rmmovl();
			
			break;
		case 0x50:
			mrmovl();
			
			break;
		case 0x60:
			add();
			
			break;
		case 0x61:
			sub();
			
			break; 
		case 0x62:
			andl();
		
			break;
		case 0x63:
			xorl();
			
			break;
		case 0x64:
			mul();
			
			break;
		case 0x65:
			cmp();
			
			break;
		case 0x70:
			jmp();
			
			break;
		case 0x71:
			jle();
			
			break;
		case 0x72:
			jl();
			
			break;
		case 0x73:

			je();
			
			break;
		case 0x74:

			jne();
			
			break;
		case 0x75:

			jge();
			
			break;
		case 0x76:
			jg();
			
			break;
		case 0x80:		
			call();
			break;
		case 0x90:

			ret();
			
			break;
		case 0xA0:
			push();
			
			break;
		case 0xB0:
			pop();
			
			break;
		case 0xC0:
			readb();
			
			break;
		case 0xC1:

			readl();
			
			break;
		case 0xD0:
			writeb();

			break;
		case 0xD1:
			writel();
						printf("writel \n");		
			break;
		case 0xE0:
			movsb();
			
			break; 
		default:
			status = INS;
		break; 
	}
}


void fetch(){
	int lol = addres + total/2;
	
	while(status == AOK && counter < lol){
		decode();
	}
	if(status == HLT){
		printf("A halt instruction has been encountered");
	}
	else{
		printf("Invalid instruction!");
		
	}
}

int main(int argc, char** argv) {
	if (argc <= 1 && argc >3){
		printf("ERROR,not the correct amount of input. \n");
		exit(1);
	}
	
	char help[] = "-h";
	char * in =(char *)malloc(sizeof(argv[1]));
	strcpy(in,argv[1]);
	
	if (strcmp(in,help)== 0){
	printf("This emulator can run y86 program. \n");
	printf("Usage : y86emul <the file name.> \n");
	free(in);
	exit(1);
}

	FILE * inputfile = fopen(in,"r");
	if(inputfile == NULL){
		printf("Error:can't find the file.");
		exit(1);
	}
	counter = 0;
	int siz = 0;
	char input[1996];
	while(fgets(input,1996,inputfile)!= NULL){
		char * token;
		


		
		int number = 0;
		token = strtok(input, "\t\n\r");
	
		if(strcmp(token,".size")== 0){
			if(siz != 0){
				printf("It should only have 1 size");
			}
			else{
				siz = 1;
			}
		
		token = strtok(NULL, "\t\n\r");
		
		sscanf(token,"%x",&size);
		mem = (unsigned char*)malloc(sizeof(unsigned char)*size);
		}
		
		else if(strcmp(token,".byte") == 0){
			token = strtok(NULL, "\t\n\r");
			sscanf(token,"%x",&addres);
			token = strtok(NULL, "\t\n\r");
			sscanf(token,"%2x",&number);
			char n = number;
			mem[addres] = (unsigned char)n;
			
		}	
		
		else if(strcmp(token,".long") == 0){
			token = strtok(NULL, "\t\n\r");
			sscanf(token,"%x",&addres);
			token = strtok(NULL, "\t\n\r");
			sscanf(token,"%d",&number);
			mem[addres] = number;
		
		}
		
		else if(strcmp(token,".text") == 0){
			char temp[3];
			token = strtok(NULL, "\t\n\r");
			sscanf(token,"%x",&addres);
			token = strtok(NULL, "\t\n\r");
			
			if (counter == 0){
			counter = addres;}
			else{
			printf("There should no more than 1 text \n");
			counter = addres;
		}
			int j = addres;
			int	i = 0;
			char n;
			total = strlen(token);
			while(i < strlen(token)){
				temp[0] = token[i];
				temp[1] = token[i+1];
				temp[2] = '\0';
				sscanf(temp,"%2x",&number);
				n = number;
				mem[j] = (unsigned char)n;
				j ++;
				i += 2;
			}
			
		}
		
		else if(strcmp(token,".string") == 0){
		
			token = strtok(NULL, " \t\n\r");
			sscanf(token,"%x",&addres);
			token = strtok(NULL, " \t\n\r");
			token ++;
			int i= addres;
						
			while (token != NULL){

			int j;
			for(j = 0; j < strlen(token);j++){
				mem[i] = (unsigned char)token[j];
				i++;
				
			}
			mem[i] = ' ';
			i++;
			token = strtok(NULL, " \t\n\r");
		}
		char last = ' ';
		mem[i-1] = (unsigned char)last;

	}
		
		else{
			printf("Not a correct format in file");
			exit(1);
		}
		
					

		}
	fclose(inputfile);
	status = AOK;
	fetch();
		
	
	return 0;
}
