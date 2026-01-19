#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Tamaño tablero
#define N 12

//PROTOTIPOS
int menu(void);
void inicializarTablero(char t[N][N], char simbolo);
void imprimirTablero(char t[N][N], const char *titulo);
void pedirYColocarBarco(char t[N][N], int tam, int numeroBarco);
void colocarBarcosMaquina(char t[N][N]);
int disparosJugador(char tableroMaquina[N][N], char tableroDisparosJugador[N][N]);
int disparosMaquina(char tableroJugador[N][N], char tableroDisparosMaquina[N][N]);
int quedanBarcos(char t[N][N]);

// MAIN
int main(void) {
    srand(time(NULL));

    char tableroJugador[N][N];
    char tableroMaquina[N][N];
    char tableroDisparosJugador[N][N];
    char tableroDisparosMaquina[N][N];

    int opcion;

    do {
        opcion = menu();

        switch (opcion) {

            case 1: {
                int num = 1;

                printf("\nComenzando el juego...\n");

                // Llamar tableros
                inicializarTablero(tableroJugador, 'A');
                inicializarTablero(tableroMaquina, 'A');
                inicializarTablero(tableroDisparosJugador, '*');
                inicializarTablero(tableroDisparosMaquina, '*');

                // Colocación de barcos del jugador
                pedirYColocarBarco(tableroJugador, 4, num++);
                pedirYColocarBarco(tableroJugador, 3, num++);
                pedirYColocarBarco(tableroJugador, 3, num++);
                pedirYColocarBarco(tableroJugador, 2, num++);
                pedirYColocarBarco(tableroJugador, 2, num++);
                pedirYColocarBarco(tableroJugador, 2, num++);

                // Colocación de barcos de la maquina
                colocarBarcosMaquina(tableroMaquina);

                imprimirTablero(tableroJugador, "TABLERO DEL JUGADOR");

                int sigueJugando = 1;
                int acierto;
                int turnoJugador = 1; // 1 = jugador, 0 = máquina

                // Bucle de disparos
                while (sigueJugando) {

                    if (turnoJugador) {
                        acierto = disparosJugador(tableroMaquina, tableroDisparosJugador);

                        if (!quedanBarcos(tableroMaquina)) {
                            printf("\n¡HAS GANADO! Hundiste todos los barcos enemigos.\n");
                            break;
                        }

                        if (!acierto) {
                            turnoJugador = 0; // cambia turno
                        }

                    } 
                    
                    else {

                        acierto = disparosMaquina(tableroJugador, tableroDisparosMaquina);

                        if (!quedanBarcos(tableroJugador)) {
                            printf("\nHAS PERDIDO. La máquina hundió todos tus barcos.\n");
                            break;
                        }

                        if (!acierto) {
                            turnoJugador = 1; // cambia turno
                        }
                    }
                }



                printf("\nPresiona ENTER para volver al menú...");
                getchar();
                break;
            }

            case 2:
                printf("\nMejores puntuaciones (aun no implementado).\n");
                printf("Presiona ENTER para volver al menú...");
                getchar();
                break;

            case 3:
                printf("\nSaliendo del juego. ¡Hasta luego!\n");
                break;

            default:
                printf("\nOpción inválida.\n");
                printf("Presiona ENTER para continuar...");
                getchar();
        }

    } while (opcion != 3);

    return 0;
}

// FUNCIONES
int menu(void) {
    char buffer[32];
    int opcion = 0;

    printf("\n=== HUNDIR LA FLOTA ===\n");
    printf("1. Jugar\n");
    printf("2. Mejor puntuación\n");
    printf("3. Salir\n");
    printf("Selecciona una opción: ");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        sscanf(buffer, "%d", &opcion);
    }

    return opcion;
}

void inicializarTablero(char t[N][N], char simbolo) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            t[i][j] = simbolo;
        }
    }
}

void imprimirTablero(char t[N][N], const char *titulo) {
    int i, j;

    printf("\n%s\n\n", titulo);

    printf("   ");
    for (i = 0; i < N; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (i = 0; i < N; i++) {
        printf("%2d ", i);
        for (j = 0; j < N; j++) {
            printf(" %c ", t[i][j]);
        }
        printf("\n");
    }
}

void pedirYColocarBarco(char t[N][N], int tam, int numeroBarco) {
    int fila, columna, i;
    char orientacion;
    int valido;

    while (1) {
        printf("\nColoca BARCO %d (tamaño %d)\n", numeroBarco, tam);
        printf("Fila inicial (0-%d): ", N - 1);
        scanf("%d", &fila);

        printf("Columna inicial (0-%d): ", N - 1);
        scanf("%d", &columna);

        printf("Orientación (H/V): ");
        scanf(" %c", &orientacion);
        getchar(); // limpiar buffer

        if (orientacion >= 'a' && orientacion <= 'z') {
            orientacion -= 32;
        }

        if (fila < 0 || fila >= N || columna < 0 || columna >= N) {
            printf("Posición fuera del tablero.\n");
            continue;
        }

        if (orientacion == 'H' && columna + tam > N) {
            printf("No cabe horizontalmente.\n");
            continue;
        }

        if (orientacion == 'V' && fila + tam > N) {
            printf("No cabe verticalmente.\n");
            continue;
        }

        if (orientacion != 'H' && orientacion != 'V') {
            printf("Orientación inválida.\n");
            continue;
        }

        valido = 1;
        for (i = 0; i < tam; i++) {
            if ((orientacion == 'H' && t[fila][columna + i] != 'A') ||
                (orientacion == 'V' && t[fila + i][columna] != 'A')) {
                valido = 0;
                break;
            }
        }

        if (!valido) {
            printf("Hay otro barco en esa posición.\n");
            continue;
        }

        for (i = 0; i < tam; i++) {
            if (orientacion == 'H') {
                t[fila][columna + i] = 'B';
            } else {
                t[fila + i][columna] = 'B';
            }
        }

        break;
    }
}

void colocarBarcosMaquina(char t[N][N]) {
    int fila, columna, i;
    int tam;
    char orientacion;
    int valido;
    int b;

    // Barcos de la maquina
    int barcos[] = {4,3,3,2,2,2,};

    for (b = 0; b <6; b++) {
        tam = barcos[b];

        while (1) {
            fila = rand() %N;
            columna = rand() %N;
            orientacion = (rand() % 2 == 0) ? 'H' : 'V';

            // Impedir que se salga del tablero
            if (orientacion == 'H' && columna + tam > N) continue;
            if (orientacion == 'V' && fila + tam > N) continue;

            // Impedir superposicón
            valido = 1;
            if (orientacion == 'H') {
                for (i = 0; i < tam; i++) {
                    if (t[fila][columna + i] != 'A') {
                        valido = 0;
                        break;
                    }
                }
            } 

            else {
                for (i = 0; i <tam; i++) {
                    if (t[fila + i][columna] != 'A') {
                        valido = 0;
                        break;
                    }
                }
            }

            if (!valido) continue;

            // Colocar barcos
            if (orientacion == 'H') {
                for (i = 0; i < tam; i++) {
                    t[fila][columna + i] = 'B';
                }
            }

            else {
                for (i = 0; i < tam; i++) {
                    t[fila + i][columna] = 'B';
                }
            }

            break;
        }
    }

}

int disparosJugador(char tableroMaquina[N][N], char tableroDisparosJugador[N][N]) {
    
    int fila, columna;

    imprimirTablero(tableroDisparosJugador, "TABLERO DE DISPAROS");

    printf("ingresa fila: ");
    scanf("%d", &fila);
    printf("Ingresa columna: ");
    scanf("%d", &columna);
    getchar(); // limpiar buffer

    // Validar rango
    if (fila < 0 || fila >= N || columna < 0 || columna >= N) {
        printf("Disparo fuera del tablero\n");
        return 1;
    }

    // Disparo repetido
    if (tableroDisparosJugador[fila][columna] != '*') {
        printf("Ya disparaste ahí\n");
        return 1;
    }

    // Impacto
    if (tableroMaquina[fila][columna] == 'B') {
        printf("¡IMPACTO!\n");
        tableroDisparosJugador[fila][columna] = 'X';
        tableroMaquina[fila][columna] = 'X';
        return 1; // Volver a disparar
    }

    //Agua
    printf("Agua\n");
    tableroDisparosJugador[fila][columna] = 'A';
    return 0; // Finalizar el turno

    }

int disparosMaquina(char tableroJugador[N][N], char tableroDisparosMaquina[N][N]) {

    int fila, columna;

    do {
        fila = rand() % N;
        columna = rand() % N;
    }

    while (tableroDisparosMaquina[fila][columna] != '*');

    printf("La máquina dispara a (%d, %d)\n", fila, columna);

    if (tableroJugador[fila][columna] == 'B') {
        printf("La máquina acertó\n");
        tableroJugador[fila][columna] = 'X';
        tableroDisparosMaquina[fila][columna] = 'X';
        return 1; // Vuelve a disparar
    }

    printf("La máquina falló\n");
    tableroDisparosMaquina[fila][columna] = 'A';
    return 0;

    }

int quedanBarcos(char t[N][N]) {
    int i, j;
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (t[i][j] == 'B') {
                return 1; // Aún quedan barcos
            }
        }
    }

    return 0; // No quedan barcos
}