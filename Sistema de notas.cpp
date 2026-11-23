#include <stdio.h>
#include <string.h>

int main()
{
    char nombres[30][30];
    float notas[30];
    int cantidad = 0;
    int opcion;
    int i;
    float suma, promedio;
    char buscar[30];

    do
    {
        printf("\n=== SISTEMA DE NOTAS ===\n");
        printf("1. Registrar estudiante\n");
        printf("2. Mostrar registros\n");
        printf("3. Buscar estudiante\n");
        printf("4. Calcular promedio general\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                printf("\nNombre del estudiante: ");
                scanf("%s", nombres[cantidad]);

                printf("Nota del estudiante: ");
                scanf("%f", &notas[cantidad]);

                cantidad++;

                printf("Estudiante registrado correctamente.\n");
                break;

            case 2:
                if(cantidad == 0) {
                    printf("No hay registros.\n");
                }
                else {
                    printf("\nLISTA DE ESTUDIANTES\n");

                    for(i = 0; i < cantidad; i++) {
                        printf("%d. %s - %.2f\n",
                               i + 1,
                               nombres[i],
                               notas[i]);
                    }
                }
                break;

            case 3:
                printf("\nIngrese el nombre a buscar: ");
                scanf("%s", buscar);

                for(i = 0; i < cantidad; i++) {
                    if(strcmp(nombres[i], buscar) == 0) {
                        printf("Estudiante encontrado.\n");
                        printf("Nombre: %s\n", nombres[i]);
                        printf("Nota: %.2f\n", notas[i]);
                        break;
                    }
                }

                if(i == cantidad) {
                    printf("Estudiante no encontrado.\n");
                }

                break;

            case 4:
                suma = 0;

                for(i = 0; i < cantidad; i++) {
                    suma = suma + notas[i];
                }

                if(cantidad > 0) {
                    promedio = suma / cantidad;
                    printf("Promedio general: %.2f\n", promedio);
                }
                else {
                    printf("No hay estudiantes registrados.\n");
                }

                break;

            case 5:
                printf("Saliendo del sistema...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while(opcion != 5);

    return 0;
}
