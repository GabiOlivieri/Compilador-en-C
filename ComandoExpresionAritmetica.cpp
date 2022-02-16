#include <stdlib.h>
#include <stdio.h> /* printf */
#include <ctype.h> /* isdigit */
int Verifica (char *); /* que los caracteres pertenezcan al alfabeto */
int Columna (int); /* dado un caracter, determina la columna que le
 corresponde */
int Valor (int);
int ObtieneValor(const char *,int);
void RestablecerYAsignar(long &,long &);


int main () {
 int x=0;
 char s1[] = "123/45";
 if (!Verifica(s1)){
  printf("Caracteres invalidos\n");return 0;
 }
 else{
  	x = ObtieneValor(s1,x);
 	printf("El valor de la cadena ingresada es: %d \n",x);
 	return 0;
 }
 }

int Verifica (char *s) {
 unsigned i;
 for (i=0; s[i]; i++)
 if (! (isdigit(s[i]) || s[i] == '+' || s[i] == '-' || s[i]== '*' || s[i]== '/')) return 0;
 return 1;
} /* fin Verifica */
int Columna (int c) {
 switch (c) {
 case '+': return 1;
 case '-': return 2;
 case '*': return 3;
 case '/': return 4;
 default /* es digito */: return 0;
 }
} /* fin Columna */


int ObtieneValor (const char *cadena, int x) {
 static int tt [8][5] = {{1,3,3,3,3},
						{1,3,4,5,6},
						{2,7,7,7,7},
						{2,7,7,7,7},
						{2,7,7,7,7},
						{2,7,7,7,7},
						{2,7,7,7,7},
						{7,7,7,7,7}};
 int e = 0; /* estado inicial */
 unsigned i = 0; /* recorre la cadena */
 int c = cadena[0]; /* primer caracter */
 long a = 0,b = 0 ; /* contiene los valores numericos absolutos de las cadenas */
 int s = 1; /* Operación, 1 = suma, 2 = resta, 3 = multiplicacion, 4 = dividir */
 while (c != '\0') {
 e = tt [e][Columna(c)];
 switch (e) {
 case 1: a= 10 * a + Valor(c);
 break;
 case 2: b = 10 * b + Valor(c);
 break;
 case 3: s=1;
 break;
 case 4: s=2;
 break;
 case 5: s=3;
 break;
 case 6: s=4;
 break;
 default /* error */: break;
 }
 c = cadena[++i];
 }
 if (e == 1 || e == 2) { /* estado final */
 	switch(s){
 		case 1: x = a + b; break;
 		case 2: x = a - b; break;
		case 3: x = a * b; break;
		case 4: x = a / b; break; 
	 }
 return x;
 }
 else
 printf("Hubo un error");
  return 0;
} /* fin ObtieneValor */

int Valor (int c) {
 return (c - '0');
} /* fin Valor */


