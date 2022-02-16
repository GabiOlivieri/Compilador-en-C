#include <stdlib.h>
#include <stdio.h> /* printf */
#include <ctype.h> /* isdigit */
int Verifica (char *); /* que los caracteres pertenezcan al alfabeto */
int Columna (int); /* dado un caracter, determina la columna que le
 corresponde */
int EsPalabra (const char *);
int EsPalabraHexadecimal (const char *);
int ColumnaHexadecimal(int);
int EsPalabraOctal (const char *);
int ColumnaOctal(int);

int main () {
 char s1[] = "01";
 if (! Verifica(s1)){
  printf("Caracteres invalidos\n");return 0;
 }
 else if (EsPalabra(s1) == 1){
 			printf("La cadena ingresada es una constante decimal \n");
}
 else if (EsPalabra(s1) == 2){
 			printf("La cadena ingresada es una constante decimal con sufijo ");
 }
 else if (EsPalabraHexadecimal(s1) == 1){
 			printf ("La cadena ingresada es una constante hexadecimal sin sufijo");
 		}
 else if (EsPalabraHexadecimal(s1) == 2){
 			printf ("La cadena ingresada es una constante hexadecimal con sufijo");
		 }
 else if (EsPalabraOctal(s1) == 1){
		 	printf ("La cadena ingresada es una constante octal sin sufijo");
		 }
 else if (EsPalabraOctal(s1) == 2){
 			printf("La cadena ingresada es una constante octal con sufijo");
 		}
else 
 printf("La cadena ingresada no es una constante entera");
 return 0;
 }

int Verifica (char *s) {
 unsigned i;
 for (i=0; s[i]; i++)
 if (! (isdigit(s[i]) || s[i] == '+' || s[i] == '-' || (s[i]>='a' && s[i]<='f') || (s[i]>='A' && s[i]<='F') || s[i]=='x' || s[i]=='X' || s[i]=='U' || s[i]=='u' || s[i]=='l' || s[i]=='L' )  )
 	return 0;
 return 1; 
} /* fin Verifica */
int Columna (int c) {
	if (c == '0')
	return 3;
	else if (isdigit(c))
	return 0;
	else if (c=='u' || c=='U')
	return 4;
	else if (c=='l' || c=='L')
	return 5;
else{
 switch (c) {
 case '+': return 1;
 case '-': return 2;
 case '0': return 3;
 default /* no es digito */: return 6;
  }
 }
} /* fin Columna */

int EsPalabra (const char *cadena) { /* Automata 1 */
 static int tt [7][6] = {{2,1,1,6,6,6}, /* Tabla de Transiciones */
 						{2,6,6,6,6,6},
						{2,6,6,2,3,4},
						{6,6,6,6,6,5},
						{6,6,6,5,6,6},
						{6,6,6,6,6,6},
						{6,6,6,6,6,6}};
 int e = 0; /* estado inicial */
 unsigned int i = 0; /* recorre la cadena */
 int c = cadena[0]; /* primer caracter */

 while (c != '\0') {
 e = tt[e][Columna(c)]; /* nuevo estado */
 c = cadena[++i]; /* proximo caracter */
 }
 if (e == 2) /* estado final */ return 1;
 else if (e>=3 && e <=5) return 2;
else
 return 0;
} /* fin EsPalabra */

int ColumnaHexadecimal (int c) {
	if (c=='x' || c=='X')
	return 4;
	else if (c=='u' || c=='U')
	return 5;
	else if (c=='l' || c=='L')
	return 6;
else {
 switch (c) {
 case '+': return 1;
 case '-': return 2;
 case '0': return 3;
 default /* pertenece a DyL */: return 0;
  }
 }
} /* fin Columna */

int EsPalabraHexadecimal (const char *cadena) { /* Automata 1 */
 static int tt [9][7] = {{8,1,1,2,8,8,8}, /* Tabla de Transiciones */
 						{8,8,8,2,8,8,8},
						{8,8,8,8,3,8,8},
						{4,8,8,4,8,8,8},
						{4,8,8,4,8,5,6},
						{8,8,8,8,8,8,7},
						{8,8,8,8,8,7,8},
						{8,8,8,8,8,8,8},
						{8,8,8,8,8,8,8}};
 int e = 0; /* estado inicial */
 unsigned int i = 0; /* recorre la cadena */
 int c = cadena[0]; /* primer caracter */

 while (c != '\0') {
 e = tt[e][ColumnaHexadecimal(c)]; /* nuevo estado */
 c = cadena[++i]; /* proximo caracter */
 }
 if (e == 4 || e == 3) /* estado final sin sufijo */ return 1;
 else if (e>=5 && e<=7) /* estados finales con sufijo */ return 2;
 else
 return 0;
} /* fin EsPalabraHexadecimal */

int ColumnaOctal (int c) {
	if (c>= '1' && c <= '7')
	return 0;
	else if (c=='u' || c=='U')
	return 4;
	else if (c=='l' || c=='L')
	return 5;
else{
 switch (c) {
 case '+': return 1;
 case '-': return 2;
 case '0': return 3;
 default /* no está entre 0 y 7 */: return 6;
  }
 }
} /* fin ColumnaOctal */

int EsPalabraOctal (const char *cadena) { /* Automata 1 */
 static int tt [8][6] = {{7,1,1,2,7,7}, /* Tabla de Transiciones */
 						{7,7,7,2,7,7},
						{3,7,7,3,7,7},
						{3,7,7,3,4,5},
						{7,7,7,7,7,6},
						{7,7,7,7,6,7},
						{7,7,7,7,7,7},
						}; /* la ultima columna, es en caso de que se ingrese un caracter que no pertenece al lenguaje */
 int e = 0; /* estado inicial */
 unsigned int i = 0; /* recorre la cadena */
 int c = cadena[0]; /* primer caracter */

 while (c != '\0') {
 e = tt[e][ColumnaOctal(c)]; /* nuevo estado */
 c = cadena[++i]; /* proximo caracter */
 }
 if (e == 3 || e == 2) /* estados finales sin sufijo */ return 1;
 else if (e >= 4 && e <= 6) /* estados finales con sufijo */ return 2;
 else
 return 0;
} /* fin EsPalabraOctal */
