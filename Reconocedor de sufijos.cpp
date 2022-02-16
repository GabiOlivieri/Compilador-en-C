#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int largocadena(char cadena[]);
int chequeartodoelsufijo(char cadena2[],char cadena[],int i,int x);
int determinarsufijo(char cadena[],char cadena2[]);

int main()
{
	char cadena[20];
	char cadena2[20];
	
	
	printf("Ingrese una cadena (max %d caracteres): ", 20);
	
	fgets(cadena, 20,stdin);
	if(cadena[strlen(cadena)-1]=='\n'){
	cadena[strlen(cadena)-1]='\0';
	}
	
	printf("Ingrese otra cadena: ");
	
	fgets(cadena2,20,stdin);
	if(cadena2[strlen(cadena2)-1]=='\n'){
	cadena2[strlen(cadena2)-1]='\0';
	}
	
	int j= determinarsufijo(cadena,cadena2);
	
	if (j==1){
		printf("La cadena ingresada es sufijo de la anterior\n");		
	}
	else{
		printf("La cadena ingresada no es sufijo de la anterior\n");
		printf("%d",j);
	}
	system("pause");
	return 0;

}

int largocadena(char cadena[]) 
{
	int i=0;
	
	while(cadena[i]!='\0')
	{
		i++;
	}
	
	return i;
}

int determinarsufijo(char cadena[],char cadena2[]){
	int i=0,x=0,j=0;
	while(cadena[x]!='\0'){
		if(cadena2[i]==cadena[x]){
			j=chequeartodoelsufijo(cadena2,cadena,i,x);
			return j;
		}
		else{
			x++;
		}		
	}return 0;
	
;
}

int chequeartodoelsufijo(char cadena2[],char cadena[],int i,int x){

	while(cadena2[i]!='\0' && cadena[x]!='\0'){
		if(cadena2[i]==cadena[x]){
			i++;
			x++;
		}
		else{
		return 0;
		}
	}
	return 1;
}





