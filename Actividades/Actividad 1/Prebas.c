#include <stdio.h>

int main() {

    int opcion;
    int salir = 0;
    int tablero[12][12];

    // Inicializar tablero en 0
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            tablero[i][j] = 0;
        }
    }

    while (!salir) {

        // Mostrar menu
        printf("\n===== HUNDIR LA FLOTA =====\n");
        printf("1. Jugar\n");
        printf("2. Mejor puntaje\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {

            case 1:
                // Jugar
                printf("\n--- INICIO DEL JUEGO ---\n");

                // Numeros arriba
                printf("    ");
                for (int j = 1; j <= 12; j++) {
                    printf("%2d ", j);
                }
                printf("\n");

                // Letras a la izquierda
                for (int i = 0; i < 12; i++) {
                    printf(" %c  ", 'a' + i);
                    for (int j = 0; j < 12; j++) {
                        printf("%2d ", tablero[i][j]);
                    }
                    printf("\n");
                }

                printf("\nPresione ENTER para volver al menu...");
                getchar();  // limpiar buffer
                getchar();  // esperar ENTER
                break;

            case 2:
                // Mejor puntaje
                printf("\n--- MEJOR PUNTAJE ---\n");
                printf("Puntaje mas alto: 150\n");  // ejemplo

                printf("\nPresione ENTER para volver al menu...");
                getchar();
                getchar();
                break;

            case 3:
                // Salir
                printf("\nSaliendo del juego...\n");
                salir = 1;
                break;

            default:
                printf("\nOpcion invalida. Intente de nuevo.\n");
        }
    }

    return 0;
}
