/*6) Realizar un programa que realice las siguientes acciones
a. Guarde el registro del nombre y el puntaje de un jugador (solicitando el ingreso
de los datos del usuario)
b. Muestre el resultado de los 10 mejores jugadores ordenados por mayor
puntaje.
c. Realice y muestre una búsqueda de un Nombre y devuelva sus resultados
NOTA: el registro debe permanecer aunque se apague la PC.*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


struct Jugador{
	char nombre[50];
	int puntaje;
};

void registro();
void mostrarTop();
void buscarJuga();

int main(){
	int opc;
	bool flag=true;
	
	printf("Bienvenido\n");
	do{
	
	printf("Que desea hacer:\n1.Registrar jugador\n2.Mostrar 10 mejores jugadores de mayor a menor (en puntaje)\n3. Buscar a un jugador por su nombre\n4.Salir\n");
	scanf("%d",&opc);
	getchar(); 
	switch(opc){
		case 1:
			registro();
			flag=true;
			break;
	
		case 2:
			mostrarTop();
			flag=true;
			break;
		case 3:
			buscarJuga();
			flag=true;
			break;
		case 4:
			printf("Saliendo...");
			return 0;
		default:
			printf("Ingrese una opcion correcta\n");
			flag=true;
			break;
			
	}
	
	}
	while(flag==true);
	
}


void registro(){
	struct Jugador juga;
	bool seguir = false;

	printf("Ingrese el nombre del jugador:\n");
	fgets(juga.nombre, sizeof(juga.nombre), stdin);
	juga.nombre[strcspn(juga.nombre, "\n")] = '\0';

	do {
		printf("Ingrese el puntaje del jugador (1-10):\n");
		scanf("%d", &juga.puntaje); 
		if (juga.puntaje < 1 || juga.puntaje > 10) {
			printf("Ingrese un puntaje dentro del rango aclarado.\n");
			seguir = false;
		} else {
			seguir = true;
		}
	} while (!seguir);
	
	FILE *archivo = fopen("jugadores.txt", "a");
    	if (archivo == NULL) {
        	printf("Error al abrir el archivo.\n");
        	return;
    }

    fwrite(&juga, sizeof(struct Jugador), 1, archivo);
    fclose(archivo);

    printf("Jugador guardado correctamente.\n------------------------------------------------------------------------------------------------------------------------------\n");
}

void mostrarTop(){
	struct Jugador juga[50];
	int cantJuga=0;
	int i,j;
	 FILE *archivo = fopen("jugadores.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
	
	while (fread(&juga[cantJuga], sizeof(struct Jugador), 1, archivo)) {
        cantJuga++;
    }
    fclose(archivo);
	
	if (cantJuga==0) {
        printf("No hay jugadores registrados aún.\n");
        return;
    }
	
	for (i=0;i<cantJuga-1;i++) {
        for (j=i+1;j<cantJuga;j++) {
            if (juga[i].puntaje<juga[j].puntaje) {
                struct Jugador temp=juga[i];
                juga[i]=juga[j];
                juga[j]=temp;
            }
        }
    }

printf("\tEl top 10 de jugadores\n");
    for (i=0;i<cantJuga && i<10;i++) {
        printf("\t%d. %s - Puntaje: [%d]\n", i + 1, juga[i].nombre, juga[i].puntaje);
    }
}







void buscarJuga(){
	char nombreBuscado[50];
	struct Jugador juga;
	bool encontrado=false;
	
	printf("Ingrese el nombre del jugador a buscar:\n");
	fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
	nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0';
	
	FILE *archivo = fopen("jugadores.txt", "r");
    	if (archivo == NULL) {
        	printf("Error al abrir el archivo.\n");
        	return;
    }
    while (fread(&juga, sizeof(struct Jugador), 1, archivo)) {
        if (strcmp(juga.nombre, nombreBuscado) == 0){
        	printf("Nombre:%s\n",juga.nombre);
        	printf("Puntaje: [%d]\n",juga.puntaje);
        	encontrado=true;
        	break;
		}
	}
	if (encontrado==false) {
        printf("No se a encontrado al jugador %s\n", nombreBuscado);
    }
	
	fclose(archivo);
}

