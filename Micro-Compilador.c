/* Compilador del Lenguaje Micro (Fischer)	*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMESTADOS 15
#define NUMCOLS 13
#define TAMLEX 32+1
#define TAMNOM 20+1

FILE * in;

typedef enum {
 INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO, PARENDERECHO, PUNTOYCOMA, COMA, ASIGNACION, SUMA, RESTA, FDT, ERRORLEXICO
} TOKEN; /* Los atributos en en la tabla de simbolos son numeros enteros */

typedef struct {
     char identifi[TAMLEX];
     TOKEN t;	/* t=0, 1, 2, 3 Palabra Reservada, t=ID=4 Identificador */
     } RegTS;
RegTS TS[1000] = { {"inicio", INICIO}, {"fin", FIN}, {"leer", LEER}, {"escribir", ESCRIBIR}, {"$", 99} };

typedef struct{
     TOKEN clase;
     char nombre[TAMLEX];
     int valor;
     } REG_EXPRESION;
     
typedef char REG_OPERACION;

char buffer[TAMLEX];
TOKEN tokenActual;
int flagToken = 0;


TOKEN scanner(); 
int columna(int c);
int estadoFinal(int e);
void Objetivo(void); 
void Programa(void);
void ListaSentencias(void);
void Sentencia(void);
void ListaIdentificadores(void);
void Identificador(REG_EXPRESION * presul);
void ListaExpresiones(void);
void Expresion(REG_EXPRESION * presul);
void Primaria(REG_EXPRESION * presul);
void OperadorAditivo(char * presul);

REG_EXPRESION ProcesarCte(void);
REG_EXPRESION ProcesarId(void);
char * ProcesarOp(void);
void Leer(REG_EXPRESION in);
void Escribir(REG_EXPRESION out);
REG_EXPRESION GenInfijo(REG_EXPRESION e1, REG_OPERACION * op, REG_EXPRESION e2);

void Match(TOKEN t);
TOKEN ProximoToken();
void ErrorLexico();
void ErrorSintactico();
void Generar(char * co, char * a, char * b, char * c);
char * Extraer(REG_EXPRESION * preg);
int Buscar(char * id, RegTS * TS, TOKEN * t);
void Colocar(char * id, RegTS * TS);
void Chequear(char * s);
void Comenzar(void);
void Terminar(void);
void Asignar(REG_EXPRESION izq, REG_EXPRESION der);


int main(int argc, char * argv[]) {
 char nomArchi[TAMNOM];
 int l;
 
 
 strcpy(nomArchi,"archivo.m");
 l = strlen(nomArchi);
 if ( l > TAMNOM ) {
  printf("Nombre incorrecto del Archivo Fuente\n"); return -1; }
// requiere para compilar un archivo de extensión.m archivo.m
 if ( (in = fopen(nomArchi, "r") ) == NULL )  {
  printf("No se pudo abrir archivo fuente\n");  return -1;//no pudo abrir archivo
  

}

 Objetivo();
 fclose(in);
 return 0;
}

TOKEN scanner() {
int tabla[NUMESTADOS][NUMCOLS] =
 //  L   D  +   -   (   )   ,    ;   :   =  EOF ´´ OTRO
 { { 1, 3 , 5 , 6 , 7 , 8 , 9 , 10, 11, 14, 13, 0, 14 },
 { 1, 1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 },
 { 14, 14, 14, 14, 14, 14, 14, 14, 14 , 14, 14, 14, 14 }, // ID
 { 4, 3 , 4 , 4 , 4 , 4 , 4 , 4 , 4 , 4, 4, 4, 4 }, 
 { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 }, // CTE
 { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
 { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
 { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
 { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
 { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
 { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
 { 14, 14, 14, 14, 14, 14, 14, 14, 14, 12, 14, 14, 14 }, // :
 { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 }, // = Asignacion
 { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
 { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 } };
int car;
int col;
int estado = 0;
int i = 0; do { car =
fgetc(in);
col = columna(car);
estado = tabla[estado][col];
 if ( col != 11 ) { //si es espacio no lo agrega al buffer
 buffer[i] = car; i++;
 }
}
while ( !estadoFinal(estado) && !(estado == 14) );
buffer[i] = '\0'; //complete la cadena
switch ( estado )
{
 case 2 : if ( col != 11 ){ //si el carácter espureo no es blanco…
 ungetc(car, in); // lo retorna al flujo
 buffer[i-1] = '\0';
 }
 return ID;
 case 4 : if ( col != 11 ) {
 ungetc(car, in);
 buffer[i-1] = '\0';
 }
 return CONSTANTE;
	case 5 : return SUMA; 
	case 6  : return RESTA; 
	case 7  : return PARENIZQUIERDO;
	case 8  : return PARENDERECHO;
	case 9  : return COMA; 
	case 10 : return PUNTOYCOMA; 
	case 12 : return ASIGNACION; 
	case 13 : return FDT;
 	case 14 : return ERRORLEXICO;
	}
	return 0;
} 

int estadoFinal(int e){
if ( e == 0 || e == 1 || e == 3 || e == 11 || e == 14 ) return 0; return 1;
}

int columna(int c){
	 if ( isalpha(c) ) return 0;
	 if ( isdigit(c) ) return 1;
	 if ( c == '+' ) return 2;
	  if ( c == '-' ) return 3;
	   if ( c == '(' ) return 4;
	    if ( c == ')' ) return 5; 
		if ( c == ',' ) return 6;
		 if ( c ==';' ) return 7; 
		 if ( c == ':' ) return 8; 
		 if ( c == '=' ) return 9;
		  if ( c == EOF ) return 10;
		   if (isspace(c) ) return 11;
return 12; /* Si ingresa algo que no esta definido devuelve el 12 que es el de nada */
}  

void Objetivo (void){
	Programa();
	Match (FDT);
	return;
}

void Programa(void)
{

Comenzar();
Match(INICIO);
ListaSentencias();
Match(FIN);
}

void ListaSentencias(void)
{

 Sentencia();
 while ( 1 ) {
  switch ( ProximoToken() )  {
   	case ID : case LEER : case ESCRIBIR :
   	Sentencia();
   	break;
   	default : return; 
    }
  }
}

void Sentencia(void) {
 TOKEN tok = ProximoToken();
 REG_EXPRESION izq, der;
//typedef struct{  TOKEN clase;  char nombre[TAMLEX];  int valor;  } REG_EXPRESION;
 switch ( tok )  {
  case ID :	
   Identificador(&izq);
   Match(ASIGNACION);
   Expresion(&der);
   Asignar(izq, der); 
   Match(PUNTOYCOMA);
   break;
  case LEER : 
   Match(LEER);
   Match(PARENIZQUIERDO);
   ListaIdentificadores();
   Match(PARENDERECHO);
   Match(PUNTOYCOMA);
   break;
  case ESCRIBIR :	
   Match(ESCRIBIR);
   Match(PARENIZQUIERDO);
   ListaExpresiones();
   Match(PARENDERECHO);
   Match(PUNTOYCOMA);
   break;
  default : return;
 }
}

void ListaIdentificadores(void) {
 /* <listaIdentificadores> -> <identificador> #leer_id {COMA <identificador> #leer_id} */
 TOKEN t;
 REG_EXPRESION reg;
 Identificador(&reg);
 Leer(reg);
 for ( t = ProximoToken(); t == COMA; t = ProximoToken() ) {
  Match(COMA);
  Identificador(&reg);
  Leer(reg);
 }
}

void Identificador(REG_EXPRESION * presul) {
 /* <identificador> -> ID #procesar_id */
 Match(ID);
 *presul = ProcesarId();//rutina semantica
}

void ListaExpresiones(void) {
 /* <listaExpresiones> -> <expresion> #escribir_exp {COMA <expresion> #escribir_exp} */
 TOKEN t;
 REG_EXPRESION reg;
 Expresion(&reg);
 Escribir(reg);
 for ( t = ProximoToken(); t == COMA; t = ProximoToken() ) {
  	Match(COMA);
  	Expresion(&reg);
  	Escribir(reg);
  }
}



void Expresion (REG_EXPRESION *presul) {
/* <expresión>-><primaria>{<operadorAditivo><primaria> #gen_infijo}*/
 REG_EXPRESION operandoIzq, operandoDer;
 REG_OPERACION op[TAMLEX];
 TOKEN t;
 Primaria(&operandoIzq);
 for(t=ProximoToken();t==SUMA||t== RESTA;t=ProximoToken()){
  OperadorAditivo(op);
  Primaria(&operandoDer);
  operandoIzq = GenInfijo(operandoIzq, op, operandoDer);
 }
 *presul = operandoIzq;
}

void Primaria(REG_EXPRESION * presul) {
 TOKEN tok = ProximoToken();
 switch ( tok ) {
  case ID :	/* <primaria> -> <identificador> */
   Identificador(presul);    break;
  case CONSTANTE :	/* <primaria> -> CONSTANTE #procesar_cte */
   Match(CONSTANTE);   *presul = ProcesarCte();    break;
  case PARENIZQUIERDO :	
   Match(PARENIZQUIERDO);    Expresion(presul);
   Match(PARENDERECHO);    break;
  default : return;
 }
}

void OperadorAditivo(char * presul) {
 /* <operadorAditivo> -> SUMA #procesar_op | RESTA #procesar_op */
 TOKEN t = ProximoToken();
 if ( t == SUMA || t == RESTA )  {
  Match(t);
  strcpy(presul, ProcesarOp());
 }  else
  ErrorSintactico(t);
}

REG_EXPRESION ProcesarCte(void)
{
 /* Convierte cadena que representa numero a entero y construye un registro semantico */
 REG_EXPRESION reg;
 reg.clase = CONSTANTE;
 strcpy(reg.nombre, buffer);
 sscanf(buffer, "%d", &reg.valor);
 return reg;
}

REG_EXPRESION ProcesarId(void) {
 /* Declara ID y construye el correspondiente registro semantico */
 REG_EXPRESION reg;
 Chequear(buffer); //function auxiliar
 reg.clase = ID;
 strcpy(reg.nombre, buffer);
 return reg;
}

char * ProcesarOp(void) {
 /* Declara OP y construye el correspondiente registro semantico */
 return buffer;
}

void Leer(REG_EXPRESION in) {
 /* Genera la instruccion para leer */
 Generar("Read", in.nombre, "Entera", "");
}

void Escribir(REG_EXPRESION out) {
 /* Genera la instruccion para escribir */
 Generar("Write", Extraer(&out), "Entera", "");
}

REG_EXPRESION GenInfijo(REG_EXPRESION e1, char * op, REG_EXPRESION e2){

 REG_EXPRESION reg;
 static unsigned int numTemp = 1;
 char cadTemp[TAMLEX] ="Temp&";
 char cadNum[TAMLEX];
 char cadOp[TAMLEX];
 if ( op[0] == '-' ) strcpy(cadOp, "Restar");
 if ( op[0] == '+' ) strcpy(cadOp, "Sumar");
 sprintf(cadNum, "%d", numTemp);
 numTemp++;
 strcat(cadTemp, cadNum);
 if ( e1.clase == ID) Chequear(Extraer(&e1));
 if ( e2.clase == ID) Chequear(Extraer(&e2));
 Chequear(cadTemp);
 Generar(cadOp, Extraer(&e1), Extraer(&e2), cadTemp);
 strcpy(reg.nombre, cadTemp);
 return reg;
}

void Match(TOKEN t) {
 if ( !(t == ProximoToken()) ) ErrorSintactico();
 flagToken = 0;
}

TOKEN ProximoToken() {
 if ( !flagToken )  {
  tokenActual = scanner();
  if ( tokenActual == ERRORLEXICO ) ErrorLexico();
  flagToken = 1;
  if ( tokenActual == ID )   {
   Buscar(buffer, TS, &tokenActual);
  }
 }
 return tokenActual;
}

void ErrorLexico() {
 printf("Error Lexico\n");
}

void ErrorSintactico() {
 printf("Error Sintactico\n");
}

void Generar(char * co, char * a, char * b, char * c) {

 printf("%s %s%c%s%c%s\n", co, a, ',', b, ',', c);
}

char * Extraer(REG_EXPRESION * preg) {

 return preg->nombre;
}

int Buscar(char * id, RegTS * TS, TOKEN * t) {
 
 int i = 0;
 while ( strcmp("$", TS[i].identifi) ) {
  if ( !strcmp(id, TS[i].identifi) )  {
   *t = TS[i].t;
   return 1; 
  }
  i++;
 }
 return 0;
}

void Colocar(char * id, RegTS * TS){

 int i = 4;
 while ( strcmp("$", TS[i].identifi) ) i++;
  if ( i < 999 ) {
  strcpy(TS[i].identifi, id );
  TS[i].t = ID;
  strcpy(TS[++i].identifi, "$" );
 }
}

void Chequear(char * s){

 TOKEN t;
 if ( !Buscar(s, TS, &t) ) {
  Colocar(s, TS);
  Generar("Declara", s, "Entera", "");
 }
}

void Comenzar(void) {

}	

void Terminar(void) {
 
 Generar("Detiene", "", "", "");
}

void Asignar(REG_EXPRESION izq, REG_EXPRESION der){
 
 Generar("Almacena", Extraer(&der), izq.nombre, "");
}


