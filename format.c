#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int bin_to_dec (char bin[]){
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

return sum;

}

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


static void
get_float_digit( float x, char * digit, int * pow10, float * remainder )
{
	int			p10;

	if ( x == 0.0 )
	{
		*digit = '0';			// digit is always '0'
		*pow10 = 0;
		*remainder = 0.0;
	}
	else
	{
		*pow10 = 0;			// start with 10^0
		while ( x >= 10.0 )		// reduce
		{
			x /= 10.0;		// large values get smaller
			*pow10 += 1;
		}
		while ( x < 1.0 )		// increase
		{
			x *= 10.0;		// small values get larger
			*pow10 -= 1;
		}
		*digit = '0';
		do {				// 10.0 > x >= 1.0
			x -= 1.0;
			*digit += 1;		// digit is always non-'0'zero
		} while ( x >= 1.0 );
		p10 = 0;
		while ( p10 > *pow10 )		// leading digit is now removed from x
		{
			x /= 10;
			p10 -= 1;
		}
		while ( p10 < *pow10 )
		{
			x *= 10;
			p10 += 1;
		}
		*remainder = x;
	}
}

static void
append( char * s, char c )
{
	char		buf[2];

	buf[0] = c;
	buf[1] = '\0';
	strcat( s, buf );
}

union Number {
	int	i;
	float	f;
};

void
floatToASCII( float x, char * output )
{
	char		c;
	int		pow10, p10, plast;
	int		i;
	float		remainder;
	char		exponent[10];
	union Number	a;
	unsigned int	biasedExp;
	unsigned int	mantissa;
	int		sign;

	a.f = x;
	biasedExp = a.i >> 23 & 0x000000ff;
	mantissa = a.i & 0x007fffff;
	sign = a.i >> 31;
	// +/- inf, +/- Nan stuff here
	if (biasedExp == 0xff){
		if(mantissa == 0){
			if(sign != 0){strcpy(output, "ninf");}
			else{strcpy(output, "pinf");}}
		else{strcpy(output, "NaN");}	
	}
	output[0] ='\0';
	if ( x < 0.0 )
	{
		append( output, '-' );
		x = -x;					// make x positive
	}
	get_float_digit( x, &c, &pow10, &remainder );
	append( output, c );
	append( output, '.' );
	x = remainder;
	plast = p10 = pow10;			// pow10 set by get_float_digit()
	for ( i = 1 ; i < 7 ; i++ )		// 7 significant digits in 32-bit float
	{
		get_float_digit( x, &c, &p10, &remainder );
		if ( (plast - p10) > 1 )
		{
			append( output, '0' );	// fill in zero to next nonzero digit
			plast -= 1;
		}
		else
		{
			append( output, c );
			x = remainder;
			plast = p10;
		}
	}
	if ( pow10 < 0 )		// negative exponent
	{
		exponent[0] = 'e';
		intToDecASCII( pow10, exponent+1 );
	}
	else if ( pow10 < 10 )		// positive single-digit exponent
	{
		exponent[0] = 'e';
		exponent[1] = '+';
		exponent[2] = '0';
		intToDecASCII( pow10, exponent+3 );
	}
	else				// positive multi-digit exponent
	{
		exponent[0] = 'e';
		exponent[1] = '+';
		intToDecASCII( pow10, exponent+2 );
	}
	strcat( output, exponent );
}


int main (int argc, char* argv[]){

if(argc != 3){
	printf("error: you enter wrong number of arguments \n");
exit(1);

}

char check[100];
strcpy(check,argv[1]);
int ch = strlen(check);
if(ch != 32){
printf("Error: wrong binary sequence \n");
exit(1);

}

int back;

char fu = argv[1][0];
if (fu == '0'){
back = bin_to_dec(argv[1]);

}
else{
char fan[32];
int i;
strcpy(fan,argv[1]);


int c =31;
char x = '0';
char y = '1';
for (;c>=0;c--){
if (fan[c] == '1'){
if (c == 31){
fan[c] = x;
}
else{
fan[c] = x;
fan[c+1] = y;
}
break;
}
}


char z;
i = 0;
for (;i<32;i++){
z = fan[i];
if (z == '0'){
fan[i] = y;
}
else if (z == '1'){
fan[i] = x;
}
}




back = 0 - bin_to_dec(fan);

//11111111111111111111111100000011


}
char result[20];

if(strcmp(argv[2],"int") == 0){
intToDecASCII(back,result);
}

else if(strcmp(argv[2],"float") == 0){
floatToASCII(back,result);

}

else{
printf("Error: not a correct type to transfer");
}
printf("%s \n",result);


return 0;
}
