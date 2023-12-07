#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void trim(char *s) {
    char *p = s;
    int l = strlen(p);

    while (isspace(p[l - 1])) p[--l] = 0;
    while (*p && isspace(*p)) ++p, --l;

    memmove(s, p, l + 1);
}

int calcularPuntaje(int aciertos) {
  if (aciertos > 0){
    return (int)pow(2, aciertos - 1);
  }
  return 0;
}

int contiene(int numero, const int *puntero, size_t longitud) {
    for (size_t i = 0; i < longitud; i++) {
        if (puntero[i] == numero) {
            return 1;
        }
    }
    return 0;
}

int sumarElementos(int arreglo[], int longitud) {
    int suma = 0;
    for (int i = 0; i < longitud; i++) {
        suma += arreglo[i];
    }
    return suma;
}

int *obtenerNumeros(const char *cadena, size_t *cantidadNumeros) {
    *cantidadNumeros = 0;
    const char *ptr = cadena;

    while (*ptr != '\0') {
        if (isdigit(*ptr)) {
            (*cantidadNumeros)++;
            while (isdigit(*ptr)) {
                ptr++;
            }
        } else {
            ptr++;
        }
    }

    int *numeros = (int *)malloc(*cantidadNumeros * sizeof(int));

    ptr = cadena;
    int indice = 0;

    while (*ptr != '\0') {
        if (isdigit(*ptr)) {
            numeros[indice++] = atoi(ptr);
            while (isdigit(*ptr)) {
                ptr++;
            }
        } else {
            ptr++;
        }
    }

    return numeros;
}

void separarNumeros(char *cadena, int **numerosGanadores, int **numerosTarjeta, size_t *cantidadG, size_t *cantidadT) {
    char *posicion = strchr(cadena, '|');

    size_t longitud = strlen(posicion + 1);
    size_t longitudIzquierda = posicion - cadena;

    char *numerosDerecha = (char *)malloc(longitud + 1);
    char *numerosIzquierda = (char *)malloc(longitudIzquierda + 1);

    strcpy(numerosDerecha, posicion + 1);
    strncpy(numerosIzquierda, cadena, longitudIzquierda);
    numerosIzquierda[longitudIzquierda] = '\0';  // Agregado

    trim(numerosDerecha);
    trim(numerosIzquierda);

    char *semicolonPos = strchr(numerosIzquierda, ':');
    size_t longitudCard = strlen(semicolonPos + 1);
    
    char *numerosCard = (char *)malloc(longitudCard + 1);
    strcpy(numerosCard, semicolonPos + 1);
    trim(numerosCard);

    *numerosGanadores = obtenerNumeros(numerosCard, cantidadG);
    *numerosTarjeta = obtenerNumeros(numerosDerecha, cantidadT);

    free(numerosDerecha);
    free(numerosIzquierda);
    free(numerosCard);
}

int main() {
    FILE *f;
    char filename[] = "../input.txt";
    f = fopen(filename, "r");

    char str[1000];
    int puntajeTotal = 0;

    int N = 212; // cartas iniciales
    int scratchcards[N];
    for (int i = 0; i < N; i++) {
        scratchcards[i] = 1; 
    }

    int j = 0;
    while (fgets(str, sizeof(str), f)) {
        int *numerosGanadores;
        size_t cantidadG;
        int *numerosTarjeta;
        size_t cantidadT;
        int aciertos = 0;
        separarNumeros(str, &numerosGanadores, &numerosTarjeta, &cantidadG, &cantidadT);

        for (size_t i = 0; i < cantidadT; i++) {
            if (contiene(numerosTarjeta[i], numerosGanadores, cantidadG)) {
                aciertos++;
            }
        }

        for (int i = j + 1; i <= aciertos + j; i++) {
            scratchcards[i] += scratchcards[j];
        }
 
        puntajeTotal += calcularPuntaje(aciertos);
        free(numerosGanadores);
        free(numerosTarjeta);
        j++;
    }
    printf("El puntaje total es de %i\n", puntajeTotal);
    printf("Se termina con %d cartas\n", sumarElementos(scratchcards, 212));

    fclose(f);

    return 0;
}
