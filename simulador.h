#ifndef SIMULADOR_H
#define SIMULADOR_H

#define CONST_G 6.674e-11 /* Constante de gravitación universal (m^3 kg^-1 s^-2) */
#define M_TIERRA 5.972e24 /* Masa de la Tierra (kg) */
#define R_TIERRA 6.371e6 /* Radio de la Tierra (m) */
#define PI 3.14159265358979323846 /* Valor de pi */

typedef struct {
    double alt; /* altitud sobre la superficie de la Tierra (m) */
    double masa; /* masa de la nave (kg) */
    double rad_orbital; /* radio orbital (m) */
    double v_orb; /* Velocidad orbital */
    double per; /* tiempo de una vuelta */
    double acel; /* aceleración centrípeta */
    double fuerza; /* fuerza gravitatoria */

} Cuerpo;


void inicializar_orbita(double alt, double masa, Cuerpo *cuerpo);

double calcular_velocidad_orbital(const Cuerpo *cuerpo);

double calcular_periodo(const Cuerpo *cuerpo);

double calcular_aceleracion_centripeta(const Cuerpo *cuerpo);

double calcular_fuerza_gravitatoria(const Cuerpo *cuerpo);

void calcular_pulso_lateral(const Cuerpo *cuerpo, double a, double dt,
                            double *dv, double *desvio, double *v_final);

void mostrar_reporte(const Cuerpo *cuerpo);














#endif