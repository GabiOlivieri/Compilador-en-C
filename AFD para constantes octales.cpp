#include <stdlib.h>
#include <stdio.h> /* printf */
#include <ctype.h> /* isdigit */
int Verifica (char *); /* que los caracteres pertenezcan al alfabeto */
int Columna (int); /* dado un caracter, determina la columna que le
 corresponde */
int EsPalabraOctal (const char *);
int Valor (int);
int main () {
 char s1[] = "012345Al";
 if (!Verifica(s1)){
  printf("Caracteres invalidos\n");return 0;
 }
 else if (EsPalabraOctal(s1) == 1){
 	printf("Pertenece al lenguaje\n");return 0;
 }
 else if (EsPalabraOctal(s1) == 2) {
 	printf("Pertenece al lenguaje con sufijo\n");return 0;
 }
 else
 printf("no pertenece al lenguaje\n");
 return 0;
 }

int Verifica (char *s) {
 unsigned i;
 for (i=0; s[i]; i++)
 if (! (isdigit(s[i]) || s[i] == '+' || s[i] == '-'))
 	if(s[i]==8 && s[i]==9) return 0;
 return 1; 
} /* fin Verifica */
int ColumnaOctal (int c) {
	if (c=='u' || c=='U')
	return 4;
	else if (c=='l' || c=='L')
	return 5;
else{
 switch (c) {
 case '+': return 1;
 case '-': return 2;
 case '0': return 3;
 case '1': return 0;
 case '2': return 0;
 case '3': return 0;
 case '4': return 0;
 case '5': return 0;
 case '6': return 0;
 case '7': return 0;
 default /* no está entre 0 y 7 */: return 6;
  }
 }
} /* fin ColumnaOctal */

int EsPalabraOctal (const char *cadena) { /* Automata 1 */
 static int tt [8][7] = {{7,1,1,2,7,7,7}, /* Tabla de Transiciones */
 						{7,7,7,2,7,7,7},
						{3,7,7,3,7,7,7},
						{3,7,7,3,4,5,7},
						{7,7,7,7,7,6,7},
						{7,7,7,7,6,7,7},
						{7,7,7,7,7,7,7},
						{7,7,7,7,7,7,7}}; /* El ultimo elemento, es en caso de que se ingrese un caracter que no pertenece al lenguaje */
 int e = 0; /* estado inicial */
 unsigned int i = 0; /* recorre la cadena */
 int c = cadena[0]; /* primer caracter */

 while (c != '\0') {
 e = tt[e][ColumnaOctal(c)]; /* nuevo estado */
 c = cadena[++i]; /* proximo caracter */
 }
 if (e == 3 || e == 2) /* estado final */ return 1;
 else if (e >= 4 && e <= 6) return 2;
 else
 return 0;
} /* fin EsPalabraOctal */
