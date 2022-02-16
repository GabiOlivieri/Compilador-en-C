#include <stdlib.h>
#include <stdio.h> /* printf */
#include <ctype.h> /* isdigit */
int Verifica (char *); /* que los caracteres pertenezcan al alfabeto */
int Columna (int); /* dado un caracter, determina la columna que le
 corresponde */
int EsPalabra (const char *);
int EsPalabra (const char *);
int Valor (int);
int ObtieneValor(const char *,int);

int main () {
 int x=0;
 char s1[] = "-12345";
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
 if (! (isdigit(s[i]) || s[i] == '+' || s[i] == '-')) return 0;
 return 1;
} /* fin Verifica */
int Columna (int c) {
 switch (c) {
 case '+': return 1;
 case '-': return 2;
 default /* es digito */: return 0;
 }
} /* fin Columna */


int ObtieneValor (const char *cadena, int x) {
 static int tt [4][3] = {{2,1,1},
						{2,3,3},
						{2,3,3},
						{3,3,3}};
 int e = 0; /* estado inicial */
 unsigned i = 0; /* recorre la cadena */
 int c = cadena[0]; /* primer caracter */
 long a = 0; /* contiene valor numerico absoluto de la
cadena */
 int s = 1; /* signo del número: 1 = positivo; -1 =
negativo */
 while (c != '\0') {
 e = tt [e][Columna(c)];
 switch (e) {
 case 1: if (c=='-') s = -1;
 break;
 case 2: a = 10 * a + Valor(c);
 break;
 default /* error */: break;
 }
 c = cadena[++i];
 }
 if (e == 2) { /* estado final */
 x = s * a;
 return x;
 }
 else return 0;
} /* fin ObtieneValor */

int Valor (int c) {
 return (c - '0');
} /* fin Valor */
