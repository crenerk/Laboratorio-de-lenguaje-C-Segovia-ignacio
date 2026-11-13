#include <stdio.h>
#include "simulador.h"

int main(void)
{
    Cuerpo c;
    double dv, desvio, vf;

    inicializar_orbita(192000.0, 33000.0, &c);
    c.v_orb = calcular_velocidad_orbital(&c);
    c.per = calcular_periodo(&c);
    c.acel = calcular_aceleracion_centripeta(&c);
    c.fuerza = calcular_fuerza_gravitatoria(&c);
    mostrar_reporte(&c);

    calcular_pulso_lateral(&c, 0.50, 10.0, &dv, &desvio, &vf);
    printf("dv=%.2f m/s, desvio=%.2f m, v_final=%.4f m/s\n", dv, desvio, vf);
    return 0;
}