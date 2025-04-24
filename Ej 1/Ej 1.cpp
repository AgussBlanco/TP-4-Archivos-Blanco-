/*1) Realizar un programa en el cual se ingresen los siguientes datos Nombre, Apellido y
DNI
a) Crear un menú donde se ingresen los datos y los guarde en un archivo
b) Otro ítem donde se pueda realizar una búsqueda por DNI y devuelva los datos de
Nombre y apellido
c) Salir del mismo*/

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
void busquedaUsuario();

int main() {
    int opc = 0;
    bool flag = true;

    printf("Bienvenido\n");

    do {
        printf("\nQue accion desea realizar:\n1. Ingresar a un usuario\n2. Buscar usuario\n3. Salir\n");
        scanf("%d", &opc);
        getchar(); 

        switch (opc) {
            case 1:
                menuIngreso();
                break;

            case 2:
                busquedaUsuario();
                break;

            case 3:
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

void busquedaUsuario() {
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
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        printf("Usuario con DNI %d no encontrado.\n", dniBuscado);
    }

    fclose(archivo);
}
