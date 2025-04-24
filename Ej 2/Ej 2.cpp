/*2) Modificar el programa anterior de manera que se puedan realizar búsquedas por
Apellido y por nombre a la vez.*/

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

int main() {
    int opc = 0;
    bool flag = true;

    printf("Bienvenido\n");

    do {
        printf("\nQue accion desea realizar:\n1. Ingresar a un usuario\n2. Buscar usuario por DNI\n3.Buscar usuario por nombre y apellido\n4. Salir\n");
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

    printf("Ingrese el nombre: ");
    fgets(usuario.Nombre, sizeof(usuario.Nombre), stdin);
    usuario.Nombre[strcspn(usuario.Nombre, "\n")] = '\0';

    printf("Ingrese el apellido: ");
    fgets(usuario.Apellido, sizeof(usuario.Apellido), stdin);
    usuario.Apellido[strcspn(usuario.Apellido, "\n")] = '\0';

    printf("Ingrese el DNI: ");
    scanf("%d", &usuario.DNI);
    getchar();

    FILE *archivo = fopen("usuarios.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fwrite(&usuario, sizeof(struct Usuario), 1, archivo);
    fclose(archivo);

    printf("Usuario guardado correctamente.\n");
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
            printf("Usuario encontrado:\n");
            printf("Nombre: %s\n", usuario.Nombre);
            printf("Apellido: %s\n", usuario.Apellido);
            printf("DNI: %d",usuario.DNI);
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
            printf("Usuario encontrado:\n");
            printf("Nombre: %s\n", usuario.Nombre);
            printf("Apellido: %s\n", usuario.Apellido);
            printf("DNI: %d",usuario.DNI);
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        printf("Usuario %s %s no encontrado.\n", nombreBuscado,apellidoBuscado);
    }

    fclose(archivo);
}
