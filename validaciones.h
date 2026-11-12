#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/* Pide un entero entre min y max. Repite hasta que sea valido. */
int leer_entero(const char *msg, int min, int max);

/* Pide un real entre min y max. Repite hasta que sea valido. */
double leer_real(const char *msg, double min, double max);

#endif