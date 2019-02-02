#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>



int bin_to_dec (char bin[], int jg){
strcpy(bin,bin+1);
int len = strlen(bin);
int sum = 0;
int j = 0;
int i =len-1;
for (; j <=len-1; j++){
if (bin[i] == '1'){
sum += pow(2,j);
}
i--;
}
if (jg == 1){

sum = 0 -sum;
}
return sum;

}

int oct_to_dec(char bin[], int jg){
strcpy(bin,bin+1);
int len = strlen(bin);
int sum = 0;
int i = 0, k = 0;
int j = len-1;
for (; i<= len-1; i++){
k = (bin[i]-48)*(pow(8,j));
sum += k;
j--;
}
if (jg == 1){
sum = 0 -sum;
}
return sum;
}

int hex_to_dec(char bin[], int jg){
strcpy(bin,bin+1);
int len = strlen(bin);
int sum = 0;
int i = 0, k = 0;
int j = len-1;
for (; i<= len-1; i++){
if (bin[i] == 'A'){
k = 10 * (pow(16,j));
}
else if (bin[i] == 'B'){
k = 11 * (pow(16,j));
}
else if (bin[i] == 'C')
k = 12 * (pow(16,j));
else if (bin[i] == 'D')
k = 13 * (pow(16,j));
else if (bin[i] == 'E')
k = 14 * (pow(16,j));
else if (bin[i] == 'F')
k = 15 * (pow(16,j));
else{
k = (bin[i]-48)*(pow(16,j));
}
sum += k;
j--;
}
if (jg == 1){
sum = 0 -sum;
}
return sum;
}

int dec_to_bin(int in){
int ba[30];
int a,b;
int i = 0;
while(in != 0){
b = in/2;
i++;
ba[i] = in - b*2;
in= in/2;
}
for (a=i; a >= 1; a--){
printf("binary answer is %d", ba[a]);
}
return i;
}


int main (int argc, char* argv[]){
int first = 0;
int second = 0;
if(argc != 5){
	printf("error: you enter a wrong number of argument \n");
exit(1);

}
char plus = argv[1][0];
if (plus == '+'){
}
else if (plus == '-'){
}
else{
printf("we only support + and - \n");
}

char oper;
int jg = 0;
char *n1;
char n111[30];
n1 = argv[2];
strcpy(n111,n1);


char min = argv[2][0];
if (min == '-'){
jg = 1;
char n11[30];
int i = 1;
int le = strlen(n1);
while (i< le){
n11[i-1] = n1[i];
i++;
}
jg = 1;
strcpy(n111,n11);
}


oper = n111[0];
if (oper == 'b'){
first = bin_to_dec(n111,jg);
}

else if (oper == 'o'){
first = oct_to_dec(n111,jg);
}

else if (oper == 'x'){
first = hex_to_dec(n111,jg);
}

else if (oper == 'd'){
char *dec;

if (jg == 1){
dec = argv[2]+2;
}


else{
dec = argv[2]+1;
}
first = atoi(dec);

if(jg == 1){
first = 0 -first;
}
}


else {
printf("error: enter a wrong indicator. \n ");
exit(1);
}







int jg2 = 0;
char *n2;
char n222[30];
n2 = argv[3];
strcpy(n222,n2);


char min2 = argv[3][0];
if (min2 == '-'){
jg2 = 1;
char n22[30];
int i = 1;
int le = strlen(n2);
while (i< le){
n22[i-1] = n2[i];
i++;
}
jg2 = 1;
strcpy(n222,n22);
}


oper = n222[0];
if (oper == 'b'){
second = bin_to_dec(n222,jg2);
}

else if (oper == 'o'){
second = oct_to_dec(n222,jg2);
}

else if (oper == 'x'){
second = hex_to_dec(n222,jg2);
}

else if (oper == 'd'){
char *dec2;

if (jg2 == 1){
dec2 = argv[3]+2;
}


else{
dec2 = argv[3]+1;
}
second = atoi(dec2);

if(jg2 == 1){
second = 0 - second;
}
}

else {
printf("error: enter a wrong indicator. \n ");
exit(1);

}

int total;

if (plus == '+')
total = first + second;
else
total = first - second;



char out = argv[4][0];

if (total < 0){
if (out != 'd'){
int m = 0 - total;
int ba[30];
char er[32];
int a,b;
int c= 0;
int i = 0;
while(m != 0){
b = m/2;
i++;
ba[i] = m - b*2;
m= m/2;
}

char z = '0';
char x = '1';
for (a=i; a >= 1; a--){
if (ba[a] == 1){
er[c] = z;
}
else if (ba[a] == 0){
er[c] = x;
}
c++;
}

int l = 0;
int u = 32-c;
char zan[32];
int y = 0;
for(;y < u; y++){
zan[y] = x;
}

for(;y < 32;y++){
zan[y] = er[l];
l++;
}
c =31;
for (;c>=0;c--){
if (zan[c] == '0'){
if (c == 31){
zan[c] =x;
break;
}
else{
zan[c] = x;
zan[c+1] = z;
break;
}
}
}

total = bin_to_dec(zan,0);
}
}

if (out == 'b'){
int ba[32];
int a,b;
int i = 0;
while(total != 0){
b = total/2;
i++;
ba[i] = total - b*2;
total= total/2;
}
printf("b");
for (a=i; a >= 1; a--){
printf("%d", ba[a]);
}
printf("\n");
}

else if (out == 'd'){
printf("d%d",total);
}

else if (out == 'o'){
int a,b,c,d,e = 0;
int j = 0;
a = total;
if (a<8)
b= a;
else
c =a ;
do{
d = c%8;
e += d* pow(10.0,j);
c/= 8;
j++;
}while(c>=8);
b = c*pow(10,j)+e;
printf("o%d", b);
}

else if (out == 'x'){
char u16[32];
int w=0,a,b,i;
     
if(total==0)
{
 u16[0]='0';
w++;
}
 else
{
 a=total;
 while(a != 0)
{
 b=a%16;
if(b<10)
{
u16[w]='0'+b;
}
else
{
u16[w]='A'+b-10;
}
a=a/16;
w++;
}
}
printf("x");
for(i=w-1;i>=0;i--)
{
printf("%c",u16[i]);
}
printf("\n");
}

return 0;




}



