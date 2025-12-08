#include <stdio.h>

int main() {

    int opcion;
    int salir = 0;

    while (salir == 0) {

        printf("\n===== MENU =====\n");
        printf("1. Jugar\n");
        printf("2. Mejor puntaje\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {

            case 1: {
                int tablero[12][12];
                int i, j;

                // 1. Inicializar tablero en 0 (agua)
                for (i = 0; i < 12; i++) {
                    for (j = 0; j < 12; j++) {
                        tablero[i][j] = 0;
                    }
                }

                // 2. Colocar naves en posiciones fijas

                // Portaaviones (4 espacios) - valor 4
                for (j = 3; j <= 6; j++) {
                    tablero[1][j] = 4;
                }

                // Crucero 1 (3 espacios) - valor 3
                for (i = 4; i <= 6; i++) {
                    tablero[i][2] = 3;
                }

                // Crucero 2 (3 espacios) - valor 3
                for (j = 7; j <= 9; j++) {
                    tablero[5][j] = 3;
                }

                // Patrullero 1 (2 espacios) - valor 2
                tablero[9][1] = 2;
                tablero[9][2] = 2;

                // Patrullero 2 (2 espacios) - valor 2
                tablero[10][5] = 2;
                tablero[10][6] = 2;

                // Patrullero 3 (2 espacios) - valor 2
                tablero[7][9] = 2;
                tablero[8][9] = 2;

                // 3. Mostrar numeros arriba
                printf("\n    ");
                for (j = 1; j <= 12; j++) {
                    printf("%2d ", j);
                }
                printf("\n");

                // 4. Mostrar tablero con letras
                for (i = 0; i < 12; i++) {
                    printf(" %c  ", 'a' + i);
                    for (j = 0; j < 12; j++) {
                        printf("%2d ", tablero[i][j]);
                    }
                    printf("\n");
                }

                break;
            }

            case 2:
                // No hace nada, solo vuelve al menu
                printf("\nOpcion de puntaje no implementada.\n");
                printf("Volviendo al menu...\n");
                break;

            case 3:
                printf("\nSaliendo del juego...\n");
                salir = 1;
                break;

            default:
                printf("\nOpcion no valida\n");
        }
    }

    return 0;
}
