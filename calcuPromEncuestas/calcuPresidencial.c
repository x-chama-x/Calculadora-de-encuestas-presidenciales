#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct encuesta{
    char nombre[20];
    char provincia[20];
    float milei;
    float massa;
    float bullrich;
    float bregman;
    float schiaretti;
} Encuesta;

// Prototipos de funciones
void menuPrincipal();
void TeclaParaContinuar();
void altaEncuesta();
void mostrarEncuestas();
void pasarEncuestasAarchivoTexto();
void crearEncuestaPromedio();
void mostrarEncuestaPromedio();
Encuesta buscarEncuesta(char nombre[20]);

int main(){
    menuPrincipal(); // Llama a la función del menú principal
    return 0;
}

void menuPrincipal(){
    int opcion;
    do {
        system("cls");
        printf("Calculadora promedio de encuestas\n");
        printf("menu principal\n");
        printf("1. Agregar encuesta\n");
        printf("2. Mostrar encuestas\n");
        printf("3. Mostrar promedio de encuestas\n");
        printf("4. Pasar encuestas a archivo de texto\n");
        printf("5. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                system("cls");
                altaEncuesta();
                break;
            case 2:
                system("cls");
                printf("Encuestas Presidenciales\n");
                mostrarEncuestas();
                break;
            case 3:
                system("cls");
                printf("Encuesta presidencial promedio\n");
                crearEncuestaPromedio(); // crea la encuesta promedio en el momento
                mostrarEncuestaPromedio();
                break;
            case 4:
                system("cls");
                printf("pasar encuestas a txt\n");
                pasarEncuestasAarchivoTexto();
                break;
            case 5:
                printf("Salir\n");
                break;
            default:
                printf("Opcion incorrecta\n");
                TeclaParaContinuar();
                break;
        } 
    } while (opcion != 5);
}


void TeclaParaContinuar(){
    printf("Presione una tecla para continuar...");
    getch();
}

// Función para dar de alta encuestas y guardarlas en un archivo binario
void altaEncuesta(){
    Encuesta encuesta;
    FILE *archivo;
    archivo = fopen("encuestas.dat", "ab");
    if (archivo == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    printf("Ingrese el nombre de la encuesta: ");
    fflush(stdin);
    gets(encuesta.nombre);
    // buscar si existe la encuesta
    Encuesta encuestaBuscada = buscarEncuesta(encuesta.nombre);
    if (strcmp(encuestaBuscada.nombre, encuesta.nombre) == 0){
        printf("La encuesta ya existe\n");
        TeclaParaContinuar();
        return;
    } else {
        printf("Ingrese la provincia: ");
        fflush(stdin);
        gets(encuesta.provincia);
        printf("Ingrese el porcentaje de Milei: ");
        scanf("%f", &encuesta.milei);
        printf("Ingrese el porcentaje de Massa: ");
        scanf("%f", &encuesta.massa);
        printf("Ingrese el porcentaje de Bullrich: ");
        scanf("%f", &encuesta.bullrich);
        printf("Ingrese el porcentaje de Bregman: ");
        scanf("%f", &encuesta.bregman);
        printf("Ingrese el porcentaje de Schiaretti: ");
        scanf("%f", &encuesta.schiaretti);
        fwrite(&encuesta, sizeof(Encuesta), 1, archivo);
        printf("Encuesta guardada con exito\n");
        TeclaParaContinuar();
    }
    fclose(archivo);
}

// Función para mostrar el archivo binario de encuestas
void mostrarEncuestas(){
    Encuesta encuesta;
    FILE *archivo;
    archivo = fopen("encuestas.dat", "rb");
    if (archivo == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    while (fread(&encuesta, sizeof(Encuesta), 1, archivo)){
        printf("Nombre: %s\n", encuesta.nombre);
        printf("Provincia: %s\n", encuesta.provincia);
        printf("Milei: %.2f%%\n", encuesta.milei);
        printf("Massa: %.2f%%\n", encuesta.massa);
        printf("Bullrich: %.2f%%\n", encuesta.bullrich);
        printf("Bregman: %.2f%%\n", encuesta.bregman);
        printf("Schiaretti: %.2f%%\n", encuesta.schiaretti);
        printf("\n");
    }
    fclose(archivo);
    TeclaParaContinuar();
}

// Función para buscar una encuesta por nombre
Encuesta buscarEncuesta(char nombre[20]){
    Encuesta encuesta;
    FILE *archivo;
    archivo = fopen("encuestas.dat", "rb");
    if (archivo == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    while (fread(&encuesta, sizeof(Encuesta), 1, archivo)){
        if (strcmp(encuesta.nombre, nombre) == 0){
            return encuesta;
        }
    }
    fclose(archivo);
    return encuesta;
}

// Función para crear una encuesta promedio a partir de las encuestas guardadas y guardarla en un archivo binario
void crearEncuestaPromedio(){
    Encuesta encuesta;
    Encuesta encuestaSuma;
    Encuesta encuestaPromedio;
    int contador = 0;
    FILE *archivo;
    archivo = fopen("encuestas.dat", "rb");
    if (archivo == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    // inicializar en 0 los valores de la encuestaSuma
    encuestaSuma.milei = 0;
    encuestaSuma.massa = 0;
    encuestaSuma.bullrich = 0;
    encuestaSuma.bregman = 0;
    encuestaSuma.schiaretti = 0;

    while (fread(&encuesta, sizeof(Encuesta), 1, archivo)){
        encuestaSuma.milei += encuesta.milei;
        encuestaSuma.massa += encuesta.massa;
        encuestaSuma.bullrich += encuesta.bullrich;
        encuestaSuma.bregman += encuesta.bregman;
        encuestaSuma.schiaretti += encuesta.schiaretti;
        contador++;
    }
    fclose(archivo);
    encuestaPromedio.milei = encuestaSuma.milei / contador;
    encuestaPromedio.massa = encuestaSuma.massa / contador;
    encuestaPromedio.bullrich = encuestaSuma.bullrich / contador;
    encuestaPromedio.bregman = encuestaSuma.bregman / contador;
    encuestaPromedio.schiaretti = encuestaSuma.schiaretti / contador;
    archivo = fopen("encuestaPromedio.dat", "wb");
    if (archivo == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    fwrite(&encuestaPromedio, sizeof(Encuesta), 1, archivo);
    fclose(archivo);
}

// Función para mostrar la encuesta promedio ordenada por mayor porcentaje de votos
void mostrarEncuestaPromedio() {
    Encuesta encuestaPromedio;
    FILE *archivo;
    archivo = fopen("encuestaPromedio.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    fread(&encuestaPromedio, sizeof(Encuesta), 1, archivo);
    fclose(archivo);

    // Definir un arreglo temporal para almacenar los porcentajes y nombres de los candidatos
    struct {
        float porcentaje;
        char nombre[20];
    } candidatos[5];

    // Copiar los porcentajes de votos y nombres de candidatos en el arreglo temporal
    candidatos[0].porcentaje = encuestaPromedio.milei;
    strcpy(candidatos[0].nombre, "Milei");
    candidatos[1].porcentaje = encuestaPromedio.massa;
    strcpy(candidatos[1].nombre, "Massa");
    candidatos[2].porcentaje = encuestaPromedio.bullrich;
    strcpy(candidatos[2].nombre, "Bullrich");
    candidatos[3].porcentaje = encuestaPromedio.bregman;
    strcpy(candidatos[3].nombre, "Bregman");
    candidatos[4].porcentaje = encuestaPromedio.schiaretti;
    strcpy(candidatos[4].nombre, "Schiaretti");

    // Ordenar el arreglo temporal por el mayor porcentaje de votos
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (candidatos[i].porcentaje < candidatos[j].porcentaje) {
                // Intercambiar elementos si es necesario
                float tempPorcentaje = candidatos[i].porcentaje;
                candidatos[i].porcentaje = candidatos[j].porcentaje;
                candidatos[j].porcentaje = tempPorcentaje;

                char tempNombre[20];
                strcpy(tempNombre, candidatos[i].nombre);
                strcpy(candidatos[i].nombre, candidatos[j].nombre);
                strcpy(candidatos[j].nombre, tempNombre);
            }
        }
    }

    // Mostrar la encuesta promedio ordenada
    for (int i = 0; i < 5; i++) {
        printf("%s: %.2f%%\n", candidatos[i].nombre, candidatos[i].porcentaje);
    }

    TeclaParaContinuar();
}


// Función para pasar las encuestas a un archivo de texto
void pasarEncuestasAarchivoTexto(){
    Encuesta encuesta;
    FILE *archivo;
    FILE *archivoTexto;
    archivo = fopen("encuestas.dat", "rb");
    archivoTexto = fopen("encuestas.txt", "w");
    if (archivo == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    if (archivoTexto == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    while (fread(&encuesta, sizeof(Encuesta), 1, archivo)){
        fprintf(archivoTexto, "Nombre: %s\n", encuesta.nombre);
        fprintf(archivoTexto, "Provincia: %s\n", encuesta.provincia);
        fprintf(archivoTexto, "Milei: %.2f%%\n", encuesta.milei);
        fprintf(archivoTexto, "Massa: %.2f%%\n", encuesta.massa);
        fprintf(archivoTexto, "Bullrich: %.2f%%\n", encuesta.bullrich);
        fprintf(archivoTexto, "Bregman: %.2f%%\n", encuesta.bregman);
        fprintf(archivoTexto, "Schiaretti: %.2f%%\n", encuesta.schiaretti);
        fprintf(archivoTexto, "\n");
    }
    fclose(archivo);
    fclose(archivoTexto);
    printf("Encuestas guardadas en el archivo de texto\n");
    TeclaParaContinuar();
}