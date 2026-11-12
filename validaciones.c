#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "validaciones.h"

/* Lee una linea completa del teclado en buf.
   Devuelve 1 si entro completa, 0 si era demasiado larga. */
static int leer_linea(char *buf, int tam)
{
    int c;

    if (fgets(buf, tam, stdin) == NULL) {
        printf("\nEntrada cerrada. Fin del programa.\n");
        exit(1);
    }
    if (strchr(buf, '\n') == NULL) {
        /* La linea no entro entera: descartamos el resto */
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        return 0;
    }
    return 1;
}

int leer_entero(const char *msg, int min, int max)
{
    char buf[64];
    char *fin;
    long n;

    while (1) {
        printf("%s", msg);
        if (!leer_linea(buf, sizeof(buf))) {
            printf("Error: entrada demasiado larga.\n");
            continue;
        }
        n = strtol(buf, &fin, 10);
        if (fin == buf || (*fin != '\n' && *fin != '\0'))
            printf("Error: ingrese un numero entero.\n");
        else if (n < min || n > max)
            printf("Error: el valor debe estar entre %d y %d.\n", min, max);
        else
            return (int)n;
    }
}

double leer_real(const char *msg, double min, double max)
{
    char buf[64];
    char *fin;
    double x;

    while (1) {
        printf("%s", msg);
        if (!leer_linea(buf, sizeof(buf))) {
            printf("Error: entrada demasiado larga.\n");
            continue;
        }
        x = strtod(buf, &fin);
        if (fin == buf || (*fin != '\n' && *fin != '\0'))
            printf("Error: ingrese un numero (use punto decimal, ej: 192.5).\n");
        else if (!isfinite(x))
            printf("Error: valor no valido.\n");
        else if (x < min || x > max)
            printf("Error: el valor debe estar entre %.2f y %.2f.\n", min, max);
        else
            return x;
    }
}