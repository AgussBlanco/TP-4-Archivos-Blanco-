/*4) Modificar dicho programa de manera que me muestre los datos de manera ordenada
Según se desee por nombre y apellido o por DNI*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Usuario {
    char Nombre[50];
    char Apellido[50];
    int DNI;
};

//Funciones
void menuIngreso();
void busquedaUsuarioDNI();
void busquedaUsuarioNA();
void validacionDNI(int dniTemp, bool *encontrado);
void mostrarDatos(struct Usuario usuario);
void mostrarUsuariosOrdenados();

int main() {
    int opc = 0;
    bool flag = true;

    printf("Bienvenido\n");

    do {
        printf("\nQue accion desea realizar:\n1. Ingresar a un usuario\n2. Buscar usuario por DNI\n3.Buscar usuario por nombre y apellido\n4. Mostrar todos los usuarios ordenados\n5. Salir\n");
        scanf("%d", &opc);
        getchar(); 

        switch (opc) {
            case 1:
                menuIngreso();
                break;

            case 2:
                busquedaUsuarioDNI();
                break;
	    case 3:
		busquedaUsuarioNA();
		break;
            case 4:
		mostrarUsuariosOrdenados();
		break;
            case 5:
                printf("Saliendo...\n");
                return 0;

            default:
                printf("Ingrese una opcion correcta\n");
                break;
        }
    } while (flag);

    return 0;
}

void menuIngreso() {
    struct Usuario usuario;
    int dniTemp;
    bool encontrado=false;

    printf("Ingrese el nombre: ");
    fgets(usuario.Nombre, sizeof(usuario.Nombre), stdin);
    usuario.Nombre[strcspn(usuario.Nombre, "\n")] = '\0';

    printf("Ingrese el apellido: ");
    fgets(usuario.Apellido, sizeof(usuario.Apellido), stdin);
    usuario.Apellido[strcspn(usuario.Apellido, "\n")] = '\0';
	
	
    printf("Ingrese el DNI: ");
    scanf("%d", &dniTemp);
    
	
	validacionDNI(dniTemp, &encontrado);
	
	if(encontrado==false){
	usuario.DNI=dniTemp;
    FILE *archivo = fopen("usuarios.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
	
    fwrite(&usuario, sizeof(struct Usuario), 1, archivo);
    fclose(archivo);

    printf("Usuario guardado correctamente.\n");
	}
	else{
		printf("El usuario no se a podido guardar\n");
	}

}

void busquedaUsuarioDNI() {
    int dniBuscado;
    struct Usuario usuario;
    bool encontrado = false;

    printf("Ingrese el DNI del usuario a buscar: ");
    scanf("%d", &dniBuscado);
    getchar();
	
    FILE *archivo = fopen("usuarios.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    while (fread(&usuario, sizeof(struct Usuario), 1, archivo)) {
        if (usuario.DNI == dniBuscado) {
        	mostrarDatos(usuario);
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        printf("Usuario con DNI %d no encontrado.\n", dniBuscado);
    }

    fclose(archivo);
}

void busquedaUsuarioNA() {
    char nombreBuscado[50];
    char apellidoBuscado[50];
    
    struct Usuario usuario;
    bool encontrado = false;

    printf("Ingrese el nombre del usuario a buscar: ");
    fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
    nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0';
    
    printf("Ingrese el apellido del usuario a buscar: ");
    fgets(apellidoBuscado, sizeof(apellidoBuscado), stdin);
    apellidoBuscado[strcspn(apellidoBuscado, "\n")] = '\0';
    
    
    FILE *archivo = fopen("usuarios.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    while (fread(&usuario, sizeof(struct Usuario), 1, archivo)) {
        if (strcmp(usuario.Nombre, nombreBuscado) == 0 && strcmp(usuario.Apellido, apellidoBuscado) == 0){
            mostrarDatos(usuario);
            encontrado=true;
            break;
        }
    }

    if (!encontrado) {
        printf("Usuario %s %s no encontrado.\n", nombreBuscado,apellidoBuscado);
    }

    fclose(archivo);
}
void validacionDNI(int dniTemp, bool *encontrado){
	 struct Usuario usuario;
	 
	 FILE *archivo = fopen("usuarios.txt", "r");
    if (archivo==NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    
    while (fread(&usuario, sizeof(struct Usuario), 1, archivo)) {
    	if(usuario.DNI==dniTemp){
    		printf("Ya hay un usuario registrado con ese DNI\n");
    		*encontrado=true;
		}
        
    }
    fclose(archivo);
}

void mostrarDatos(struct Usuario usuario){
	
	int opc=0;
	bool seguir=true;
	
	
	printf("El usuario a sido encontrado:\n");
	do{
	printf("Desea ver:\n 1.Nombre y Apellido\n2. DNI\n");
	scanf("%d",&opc);
	
	if(opc==1){
		printf("Nombre: %s\n", usuario.Nombre);
    	printf("Apellido: %s\n", usuario.Apellido);
    	seguir=false;
	}
	else if(opc==2){
		printf("DNI: %d",usuario.DNI);
		seguir=false;
	}
	else{
		printf("Ingrese una opcion correcta\n");
		seguir=true;
	}
	}
	while(seguir==true);
}

void mostrarUsuariosOrdenados() {
    struct Usuario usuarios[100];
    int cantidad = 0;
    int opcionOrden;
    int i,j;
    FILE *archivo = fopen("usuarios.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    while (fread(&usuarios[cantidad], sizeof(struct Usuario), 1, archivo)) {
        cantidad++;       
    }
    fclose(archivo);

    if (cantidad == 0) {
        printf("No hay usuarios para mostrar.\n");
        return;
    }

    printf("Como desea ordenar los usuarios:\n1. Por Nombre (alfabetico)\n2. Por DNI (de menor a mayor)\n");
    scanf("%d", &opcionOrden);
    getchar();

    if (opcionOrden == 1) {
        for (i=0;i<cantidad - 1;i++) {
            for (j=i + 1;j<cantidad;j++) {
                if (strcmp(usuarios[i].Nombre, usuarios[j].Nombre)>0) {
                    struct Usuario temp = usuarios[i];
                    usuarios[i] = usuarios[j];
                    usuarios[j] = temp;
                }
            }
        }
    } else if (opcionOrden == 2) {
       
        for (i=0;i<cantidad - 1;i++) {
            for (j=i + 1;j<cantidad;j++) {
                if (usuarios[i].DNI > usuarios[j].DNI) {
                    struct Usuario temp = usuarios[i];
                    usuarios[i] = usuarios[j];
                    usuarios[j] = temp;
                }
            }
        }
    } else {
        printf("Opcion no valida.\n");
        return;
    }

    printf("\nUsuarios registrados:\n");
    for (i=0;i<cantidad;i++) {
        printf("Nombre: %s | Apellido: %s | DNI: %d\n", usuarios[i].Nombre, usuarios[i].Apellido, usuarios[i].DNI);
    }
}
