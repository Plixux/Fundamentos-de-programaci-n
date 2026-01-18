#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 12

int main(void) {
    srand(time(NULL));
    
    char disparos[N][N];
    char tablero[N][N];
    char maquina[N][N];
    char tableroJugador[N][N];
    char tableroMaquina[N][N];
    char disparosJugador[N][N];
    char disparosMaquina[N][N];
    int i, j;
    int num = 1;
    int opcion;

        // Bucle del menú
    do {
        opcion = menu();

        // Opción jugar
        switch (opcion) {
            case 1:
                printf("\nComenzando el juego...\n");

                for (i = 0; i < N; i++) {
                    for (j = 0; j < N; j++) {
                        tableroJugador[i][j] = 'A';
                        tableroMaquina[i][j] = 'A';
                        disparosJugador[i][j] = '*';
                        disparosMaquina[i][j] = '*';

                    }
                }

                num = 1;

                // Colocar varios barcos
                pedirYColocarBarco(tableroJugador, 4, num++); // barco grande
                pedirYColocarBarco(tableroJugador, 3, num++); // barcos medianos
                pedirYColocarBarco(tableroJugador, 3, num++); 
                pedirYColocarBarco(tableroJugador, 2, num++); // barcos pequeños
                pedirYColocarBarco(tableroJugador, 2, num++);
                pedirYColocarBarco(tableroJugador, 2, num++);

                // Cadena de texto para tablero jugador y disparos
                imprimirTablero(tableroJugador, "Tablero del jugador");

                break;

        // Opción mejores puntajes
            case 2:
                printf("\nMostrando mejores puntajes...\n");
                break;

        // Opción salir del juego
            case 3:
                printf("\nSaliendo del juego.\n");
                break;

            default:
                printf("Opción invalida. Por favor intenta de nuevo.\n");

        }
    } 

    while (opcion != 3);

    // Todavía no se ha disparado
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            disparos[i][j] = '*';
        }
    }

    // llenar con agua
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            tablero[i][j] = 'A';
        }
    }

    return 0;
}

int menu(void) {
    int opcion;

    printf("\n=== HUNDIR LA FLOTA ===\n");
    printf("1. Jugar\n");
    printf("2. Mejor puntuación\n");
    printf("3. Salir\n");
    printf("Selección una opción: ");
    scanf("%d", &opcion);

    return opcion;
}

void imprimirTablero(char t[N][N], const char *titulo) {
    int i, j;
    printf("\n%s\n", titulo);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%c ", t[i][j]);
        }
        printf("\n");
    }
}

void pedirYColocarBarco(char t[N][N], int tam, int numeroBarco) {
    int fila, columna, i;
    char orientacion;
    int valido;

    while (1) {
        printf("\n== Coloca BARCO %d (tamano %d) ==\n", numeroBarco, tam);

        printf("Ingresa la fila inicial (0 a %d): ", N - 1);
        scanf("%d", &fila);

        printf("Ingresa la columna inicial (0 a %d): ", N - 1);
        scanf("%d", &columna);

        printf("Orientacion (H = horizontal, V = vertical): ");
        scanf(" %c", &orientacion);

        // aceptar minusculas
        if (orientacion >= 'a' && orientacion <= 'z') {
            orientacion = orientacion - ('a' - 'A');
        }

        // validar rango
        if (fila < 0 || fila >= N || columna < 0 || columna >= N) {
            printf("❌ Fuera del tablero.\n");
            continue;
        }

        // validar que no se salga
        if (orientacion == 'H' && columna + tam - 1 >= N) {
            printf("❌ No cabe horizontal.\n");
            continue;
        }
        if (orientacion == 'V' && fila + tam - 1 >= N) {
            printf("❌ No cabe vertical.\n");
            continue;
        }
        if (orientacion != 'H' && orientacion != 'V') {
            printf("❌ Orientacion invalida. Usa H o V.\n");
            continue;
        }

        // validar superposicion
        valido = 1;
        if (orientacion == 'H') {
            for (i = 0; i < tam; i++) {
                if (t[fila][columna + i] != 'A') { valido = 0; break; }
            }
        } else {
            for (i = 0; i < tam; i++) {
                if (t[fila + i][columna] != 'A') { valido = 0; break; }
            }
        }

        if (!valido) {
            printf("❌ Hay un barco en esa zona. Intenta otra posicion.\n");
            continue;
        }

        // colocar barco
        if (orientacion == 'H') {
            for (i = 0; i < tam; i++) t[fila][columna + i] = 'B';
        } else {
            for (i = 0; i < tam; i++) t[fila + i][columna] = 'B';
        }

        break;
    }
}

int disparosJugador(char maquina[N][N], char tableroMaquina[N][N], char tableroDisparos[N][N]) {
    int fila, columna;

    printf("\n=== TU TURNO ===\n");
    imprimirTablero(tableroDisparos, "Tablero de disparos");

    printf("Ingresa fila (0 a %d): ", N - 1);
    scanf("%d", &fila);

    printf("Ingresa columna (0 a %d): ", N - 1);
    scanf("%d", &columna);

    // Indicador de disparo fuera
    if (fila < 0 || fila >= N || columna < 0 || columna >= N) {
        printf("Fuera del tablero");
        return 1;
    }

    // Indicador de disparo mismo lugar
    if (tableroDisparos[fila][columna] != '*') {
        printf("Ya disparaste ahí. \n");
        return 1;
    }

    // Indicador de disparo acertado
    if (maquina[fila][columna] == 'B') {
         printf("¡IMPACTO!");
         tableroDisparos[fila][columna] = 'X';
         maquina[fila][columna] = 'X';
         return 1;
    }

    // Indicador de disparo fallado
    else {
        printf("Agua. \n");
        tableroDisparos[fila][columna] = 'A';
        return 0;
    }
}

int disparosMaquina(char tableroJugador[N][N], char disparosMaquina[N][N]) {
    int fila, columna;

    printf("\n=== TURNO DE LA MAQUINA ===\n");

    // Disparo aleatorio
    do {
        fila = rand() % N;
        columna = rand() % N;
    } 
    
    while (disparosMaquina[fila][columna] != '*');

    printf("La maquina dispara a (%d, %d)\n", fila, columna);

    // Comprobación del disparo
    if (tableroJugador[fila][columna] == 'B') {
        printf("La maquina ¡ACERTÓ!\n");
        tableroJugador[fila][columna] = 'X';
        disparosMaquina[fila][columna] = 'X';
        return 1;
    } 

    else {
        printf("La maquina falló.\n");
        disparosMaquina[fila][columna] = 'A';
        return 0;
    }

}