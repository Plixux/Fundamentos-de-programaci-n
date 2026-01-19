#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Tamaño del tablero 12*12
#define N 12

// Ranking top 3
#define RANKING_FILE "ranking.txt"

// Solicitud de nombre del jugador
void pedirNombre(char nombre[]){
    printf("\nIngrese su nombre (3 letras): ");
    scanf("%3s", nombre);
}

// Crear tablero
void imprimirTablero(char tablero[N][N]) {

    int i, j;

    printf("\nTABLERO:\n");

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%c ", tablero[i][j]);
        }
        printf("\n");
    }
}

// Colocar barco del jugador en el tablero
void colocarBarcoJugador(char tablero[N][N], int tam, const char *nombreBarco){

    int fila, col;
    char orientacion;
    int i;
    int valido;

    while (1) {
        printf("\n== colocar %s (tamano %d) ==\n", nombreBarco, tam);

        printf("Fila inicial 1-12: ");
        scanf("%d", &fila);

        printf("Columna inicial 1-12: ");
        scanf("%d", &col);

        // validar rango
        if (fila < 1 || fila > 12 || col < 1 || col > 12){
            printf("Coordenadas fuera de rango. Use 1 a 12.\n");
            continue;
        }

        // convertir a indices 0-11 para la matriz
        fila = fila - 1;
        col  = col  - 1;

        // opciones validas (derecha y abajo)
        int puedeH = (col + (tam - 1) < N);
        int puedeV = (fila + (tam - 1) < N);

        // Mostrar opciones posibles
        printf("Opciones posibles desde esa posicion:\n");
        if (puedeH) printf(" H) Horizontal derecha hasta (%d, %d)\n", fila + 1, (col + tam - 1) + 1);
        if (puedeV) printf(" V) Vertical abajo    hasta (%d, %d)\n", (fila + tam - 1) + 1, col + 1);

        if (!puedeH && !puedeV){
            printf("No cabe ni horizontal ni vertical. Intente otra posicion.\n");
            continue;
        }

        // Orientacion horizontal o vertical
        printf("Elija orientacion (H/V): ");
        scanf(" %c", &orientacion);

        // Aceptar minusculas
        if (orientacion >= 'a' && orientacion <= 'z') {
            orientacion = orientacion - ('a' - 'A');
        }

        // validar orientacion segun las opciones
        if (orientacion == 'H' && !puedeH){
            printf("No cabe horizontal desde ahi.\n");
            continue;
        }
        if (orientacion == 'V' && !puedeV){
            printf("No cabe vertical desde ahi.\n");
            continue;
        }
        if (orientacion != 'H' && orientacion != 'V'){
            printf("Orientacion invalida. Use H o V.\n");
            continue;
        }

        // Validacion de superposicion
        valido = 1;

        if (orientacion == 'H'){
            for (i = 0; i < tam; i++) {
                if (tablero[fila][col + i] != 'A'){
                    valido = 0;
                    break;
                }
            }
        } else {
            for (i = 0; i < tam; i++){
                if (tablero[fila + i][col] != 'A'){
                    valido = 0;
                    break;
                }
            }
        }

        if (!valido) {
            printf("Hay un barco en esa zona. Intente otra posicion.\n");
            continue;
        }

        // colocar barco
        if (orientacion == 'H'){
            for (i = 0; i < tam; i++){
                tablero[fila][col + i] = 'B';
            }
        } else {
            for (i = 0; i < tam; i++) {
                tablero[fila + i][col] = 'B';
            }
        }

        printf("%s colocado correctamente.\n", nombreBarco);
        break;
    }
}

// Verifica si un barco cabe y no se superpone
int puedeColocar(char tablero[N][N], int fila, int col, int tam, int horizontal) {

    int i;

    for (i = 0; i < tam; i++) {
        int f = fila + (horizontal ? 0 : i);
        int c = col  + (horizontal ? i : 0);

        if (f < 0 || f >= N || c < 0 || c >= N) return 0;
        if (tablero[f][c] != 'A') return 0;
    }

    return 1;
}

// Coloca un barco en el tablero (ya validado)
void colocarBarcoAuto(char tablero[N][N], int fila, int col, int tam, int horizontal) {

    int i;

    for (i = 0; i < tam; i++) {
        int f = fila + (horizontal ? 0 : i);
        int c = col  + (horizontal ? i : 0);
        tablero[f][c] = 'B';
    }
}

// Coloca toda la flota de la maquina
void colocarFlotaMaquina(char tablero[N][N]) {

    int barcos[] = {4, 3, 3, 2, 2, 2};
    int total = 6;
    int b;

    for (b = 0; b < total; b++) {
        int tam = barcos[b];

        while (1) {
            int fila = rand() % N;
            int col  = rand() % N;
            int horizontal = rand() % 2;

            if (puedeColocar(tablero, fila, col, tam, horizontal)) {
                colocarBarcoAuto(tablero, fila, col, tam, horizontal);
                break;
            }
        }
    }
}

// Disparos del jugador sobre el tablero de la maquina devuelve 1 si acierta 0 si falla
int disparoJugador(char tableroMaquina[N][N]) {

    int fila, col;

    printf("\nDISPARO DEL JUGADOR\n");
    printf("Fila (1-12): ");
    scanf("%d", &fila);

    printf("Columna (1-12): ");
    scanf("%d", &col);

    // Validar rango
    if (fila < 1 || fila > 12 || col < 1 || col > 12) {
        printf("Disparo fuera del tablero.\n");
        return 0;
    }

    // Convertir a indices
    fila--;
    col--;

    // Ya disparado
    if (tableroMaquina[fila][col] == 'X' || tableroMaquina[fila][col] == '*') {
        printf("Ya disparaste ahi.\n");
        return 0;
    }

    // Tocado
    if (tableroMaquina[fila][col] == 'B') {
        tableroMaquina[fila][col] = 'X';
        printf("TOCADO!\n");
        return 1;
    }

    // Agua
    tableroMaquina[fila][col] = '*';
    printf("💧 Agua.\n");
    return 0;
}

// Disparo de la maquina sobre el tablero del jugado devuelve 1 si acierta 0 si falla

int disparoMaquina(char tableroJugador[N][N]) {

    int fila, col;

    // Buscar una casilla que no haya sido disparada antes
    while (1) {
        fila = rand() % N;   // 0-11
        col  = rand() % N;

        if (tableroJugador[fila][col] != 'X' && tableroJugador[fila][col] != '*') {
            break;
        }
    }

    printf("\nDISPARO DE LA MAQUINA\n");
    printf("La maquina dispara a (%d, %d)\n", fila + 1, col + 1);

    // Tocado
    if (tableroJugador[fila][col] == 'B') {
        tableroJugador[fila][col] = 'X';
        printf("La maquina Toco un barco!\n");
        return 1;
    }

    // Agua
    tableroJugador[fila][col] = '*';
    printf("La maquina fallo.\n");
    return 0;
}

// Devuelve si aun quedan barcos  o no
int quedanBarcos(char tablero[N][N]) {

    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (tablero[i][j] == 'B') {
                return 1;
            }
        }
    }

    return 0;
}

// tablero oculto de la maquina no mostrar B si mostrar aciertos  y agua

void imprimirTableroOculto(char tablero[N][N]) {

    int i, j;

    printf("\nTABLERO (OCULTO):\n");

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {

            if (tablero[i][j] == 'B') {
                printf("A ");   // o puedes poner ". " si prefieres
            } else {
                printf("%c ", tablero[i][j]);
            }
        }
        printf("\n");
    }
}

// Mejores puntajes

typedef struct {
    char nombre[4];   // 3 letras + '\0'
    int puntaje;
    char fecha[11];   // "DD/MM/YYYY" + '\0'
} Registro;

// Guarda la fecha actual en formato DD/MM/YYYY
void obtenerFechaActual(char fechaOut[11]) {
    time_t ahora = time(NULL);
    struct tm *t = localtime(&ahora);

    // dia/mes/anio
    sprintf(fechaOut, "%02d/%02d/%04d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
}

//// Carga el ranking desde el archivo. Si no existe, lo inicializa en vacio.
// Devuelve cuántos registros reales cargó (0 a 3).

int cargarRanking(Registro top[3]) {

    FILE *f = fopen(RANKING_FILE, "r");
    int n = 0;

    // Inicializar en "vacio"
    for (int i = 0; i < 3; i++) {
        top[i].nombre[0] = '\0';
        top[i].puntaje = -999999;   // muy bajo para comparar
        top[i].fecha[0] = '\0';
    }

    if (f == NULL) {
        return 0; // no existe el archivo todavía
    }

    // Formato: NOMBRE PUNTAJE FECHA
    // Ej: EST 120 18/01/2026
    while (n < 3 && fscanf(f, "%3s %d %10s", top[n].nombre, &top[n].puntaje, top[n].fecha) == 3) {
        n++;
    }

    fclose(f);
    return n;
}

// Guarda el ranking top 3 en el archivo
void guardarRanking(Registro top[3]) {

    FILE *f = fopen(RANKING_FILE, "w");
    if (f == NULL) {
        printf("No se pudo guardar el ranking.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        // Solo escribir si el registro existe
        if (top[i].nombre[0] != '\0' && top[i].puntaje > -999999) {
            fprintf(f, "%s %d %s\n", top[i].nombre, top[i].puntaje, top[i].fecha);
        }
    }

    fclose(f);
}

// Inserta un nuevo registro en el TOP 3 si su puntaje es suficientemente alto.
// Mantiene el orden: top[0] >= top[1] >= top[2]

void actualizarRanking(Registro top[3], const char nombre[4], int puntaje, const char fecha[11]) {

    Registro nuevo;
    snprintf(nuevo.nombre, sizeof(nuevo.nombre), "%s", nombre);
    nuevo.puntaje = puntaje;
    snprintf(nuevo.fecha, sizeof(nuevo.fecha), "%s", fecha);

    // Si no entra ni al puesto 3, no se hace nada
    if (puntaje < top[2].puntaje) return;

    // Insertar en el lugar correcto
    if (puntaje >= top[0].puntaje) {
        top[2] = top[1];
        top[1] = top[0];
        top[0] = nuevo;
    }
    else if (puntaje >= top[1].puntaje) {
        top[2] = top[1];
        top[1] = nuevo;
    }
    else {
        top[2] = nuevo;
    }
}

// Mostrar el ranking desde el menú

void mostrarRanking() {
    Registro top[3];
    int n = cargarRanking(top);

    printf("\n===== TOP 3 PUNTAJES =====\n");

    if (n == 0) {
        printf("Aun no hay puntuaciones registradas.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        if (top[i].nombre[0] != '\0' && top[i].puntaje > -999999) {
            printf("%d) %s - %d - %s\n", i + 1, top[i].nombre, top[i].puntaje, top[i].fecha);
        }
    }
}


int main(void) {
    
    srand(time(NULL));

    int opcion = 0;
    char nombreJugador[4];

    // Bucle del menu
    do {
        printf("\nHundir la flota\n");
        printf("1) Jugar\n");
        printf("2) Mejor puntuacion\n");
        printf("3) Salir\n");
        printf("Seleccione una opcion: ");

        scanf("%d", &opcion);

        if (opcion == 1) {
            pedirNombre(nombreJugador);
            printf("\nBienvenido %s!\n", nombreJugador);

            char tableroJugador[N][N];
            int i, j;
            char tableroMaquina[N][N];

            // llenar con agua
            for (i = 0; i < N; i++){
                for (j = 0; j < N; j++){
                    tableroJugador[i][j] = 'A';
                    tableroMaquina[i][j] = 'A';
                }
            }

            // colocar Barcos 
            colocarBarcoJugador(tableroJugador, 4, "Portaviones");
            colocarBarcoJugador(tableroJugador, 3, "crucero 1");
            colocarBarcoJugador(tableroJugador, 3, "crucero 2");
            colocarBarcoJugador(tableroJugador, 2, "Patrullero 1");
            colocarBarcoJugador(tableroJugador, 2, "Patrullero 2");
            colocarBarcoJugador(tableroJugador, 2, "Patrullero 3");
            colocarFlotaMaquina(tableroMaquina);

            
            // Bucle del juego
            int puntosJugador = 0;
            int puntosMaquina = 0;
            int turno = 0; // 0 = jugador, 1 = maquina
            
            printf("\nComienza el juego\n");
            
            while (quedanBarcos(tableroJugador) && quedanBarcos(tableroMaquina)) {

        printf("\nPuntos -> %s: %d | MAQ: %d\n",
               nombreJugador, puntosJugador, puntosMaquina);

        if (turno == 0) {

            printf("\nTURNO DE %s\n", nombreJugador);
            printf("\nTU TABLERO:\n");
            imprimirTablero(tableroJugador);

            printf("\nTABLERO DE DISPAROS (MAQUINA):\n");
            imprimirTableroOculto(tableroMaquina);

            int acierto = disparoJugador(tableroMaquina);

            if (acierto == 1) {
                puntosJugador += 10;
                printf("Acierto! Sigues jugando.\n");
            } else {
                puntosJugador -= 1;
                printf("Fallo. Turno de la maquina.\n");
                turno = 1;
            }

        } else {

            printf("\nTURNO DE LA MAQUINA\n");
            int acierto = disparoMaquina(tableroJugador);

            if (acierto == 1) {
                puntosMaquina += 10;
                printf("La maquina acerto y sigue.\n");
            } else {
                puntosMaquina -= 1;
                printf("La maquina fallo. Tu turno.\n");
                turno = 0;
            }
        }
    }

    printf("\n=== FIN DEL JUEGO ===\n");
    printf("Puntaje final -> %s: %d | MAQ: %d\n", nombreJugador, puntosJugador, puntosMaquina);
    
    if (quedanBarcos(tableroMaquina) == 0) {
    printf("Ganaste, %s!\n", nombreJugador);

} else {
    
    printf("Gano la maquina (MAQ).\n");

}

Registro top[3];
cargarRanking(top);

char fecha[11];
obtenerFechaActual(fecha);

char nombreGanador[4];
int puntajeGanador;

if (!quedanBarcos(tableroMaquina)) {
    // gano el jugador
    snprintf(nombreGanador, sizeof(nombreGanador), "%s", nombreJugador);
    puntajeGanador = puntosJugador;
} else {
    // gano la maquina
    snprintf(nombreGanador, sizeof(nombreGanador), "MAQ");
    puntajeGanador = puntosMaquina;
}

actualizarRanking(top, nombreGanador, puntajeGanador, fecha);
guardarRanking(top);

printf("\nRanking actualizado.\n");

            // mostrar tablero
            imprimirTablero(tableroJugador);

            printf("\nPortaviones listo. (Luego seguimos con cruceros y patrulleros)\n");
        }
        else if (opcion == 2){
            mostrarRanking();
        }
        else if (opcion == 3){
            printf("\nSaliendo. Gracias por jugar.\n");
        }
        else {
            printf("\nOpcion invalida. Intente de nuevo.\n");
        }

    } while (opcion != 3);

    return 0;
}
