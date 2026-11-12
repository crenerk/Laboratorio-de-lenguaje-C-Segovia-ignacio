#include <stdio.h>
#include "validaciones.h"

int main(void)
{
    int n = leer_entero("Entero (1-10): ", 1, 10);
    double x = leer_real("Real (0-100): ", 0.0, 100.0);
    printf("Ingresaste %d y %.2f\n", n, x);
    return 0;
}