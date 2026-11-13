#include <stdio.h>
#include <math.h>
#include "simulador.h"

void inicializar_orbita(double alt, double masa, Cuerpo *cuerpo)
{
    cuerpo->alt = alt;
    cuerpo->masa = masa;
    cuerpo->rad_orbital = R_TIERRA + alt;
    cuerpo->v_orb = 0.0;
    cuerpo->per = 0.0;
    cuerpo->acel = 0.0;
    cuerpo->fuerza = 0.0;
}

double calcular_velocidad_orbital(const Cuerpo *cuerpo)
{
    return sqrt(CONST_G * M_TIERRA / cuerpo->rad_orbital);
}

double calcular_periodo(const Cuerpo *cuerpo)
{
    return 2.0 * PI * cuerpo->rad_orbital / cuerpo->v_orb;
}

double calcular_aceleracion_centripeta(const Cuerpo *cuerpo)
{
    return cuerpo->v_orb * cuerpo->v_orb / cuerpo->rad_orbital;
}

double calcular_fuerza_gravitatoria(const Cuerpo *cuerpo)
{
    return CONST_G * M_TIERRA * cuerpo->masa /
           (cuerpo->rad_orbital * cuerpo->rad_orbital);
}

void calcular_pulso_lateral(const Cuerpo *cuerpo, double a, double dt,
                            double *dv, double *desvio, double *v_final)
{
    *dv = a * dt;
    *desvio = 0.5 * a * dt * dt;
    *v_final = sqrt(cuerpo->v_orb * cuerpo->v_orb + (*dv) * (*dv));
}

void mostrar_reporte(const Cuerpo *cuerpo)
{
    printf("\n===== REPORTE ORBITAL =====\n");
    printf("Altitud:              %.2f km\n", cuerpo->alt / 1000.0);
    printf("Masa de la nave:      %.2f kg\n", cuerpo->masa);
    printf("Radio orbital:        %.2f km\n", cuerpo->rad_orbital / 1000.0);
    printf("Velocidad orbital:    %.2f m/s\n", cuerpo->v_orb);
    printf("Periodo orbital:      %.2f s (%.2f min)\n",
           cuerpo->per, cuerpo->per / 60.0);
    printf("Aceleracion centripeta: %.4f m/s^2\n", cuerpo->acel);
    printf("Fuerza gravitatoria:  %.2f N\n", cuerpo->fuerza);
}