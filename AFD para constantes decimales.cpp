#include <stdlib.h>
#include <stdio.h> /* printf */
#include <ctype.h> /* isdigit */
int Verifica (char *); /* que los caracteres pertenezcan al alfabeto */
int Columna (int); /* dado un caracter, determina la columna que le
 corresponde */
int EsPalabra (const char *);
int EsPalabra (const char *);
int Valor (int);
int main () {
 char s1[] = "12345";
 if (! Verifica(s1)){
  printf("Caracteres invalidos\n");return 0;
 }
 else if (EsPalabra(s1)){
 	printf("Pertenece al lenguaje\n");return 0;
 }
 else
 printf("no pertenece al lenguaje\n");
 return 0;
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

int EsPalabra (const char *cadena) { /* Automata 1 */
 static int tt [4][3] = {{2,1,1}, /* Tabla de Transiciones */
 {2,3,3},
{2,3,3},
{3,3,3}};
 int e = 0; /* estado inicial */
 unsigned int i = 0; /* recorre la cadena */
 int c = cadena[0]; /* primer caracter */

 while (c != '\0') {
 e = tt[e][Columna(c)]; /* nuevo estado */
 c = cadena[++i]; /* proximo caracter */
 }
 if (e == 2) /* estado final */ return 1;
 return 0;
} /* fin EsPalabra */

int EsPalabra2 (const char *s) { /* Automata 2 */
 static int tt [4][3] = {{2,1,1}, /* Tabla de Transiciones */
 {2,3,3}, /* 2 es el estado final */
{2,3,3}, /* 3 es el estado de rechazo */
{3,3,3}};
 int e; /* estado actual del automata */
 unsigned int i; /* recorre la cadena */
 for (e=0,i=0; s[i]!='\0' && e!=3; i++){
 
 e = tt [e][Columna(s[i])];
 
 return e==2;} /* estado final? retorna 1 */
} /* fin EsPalabra2 */

int ObtieneValor (const char *cadena, long *p_numero) {
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
 *p_numero = s * a;
 return 1;
 }
 else return 0;
} /* fin ObtieneValor */

int Valor (int c) {
 return (c - '0');
} /* fin Valor */
