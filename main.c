#include <stdio.h>
#include "simulador.h"
#include "validaciones.h"

int main(void)
{
    Cuerpo c;
    double alt_km, masa, a, dt;
    double dv = 0.0, desvio = 0.0, vf = 0.0;
    int opcion;
    int datos_cargados = 0;
    int calculado = 0;
    int pulso_hecho = 0;

    do {
        printf("\n=== SIMULADOR ARTEMIS - ORBITA TERRESTRE BAJA ===\n");
        printf("1. Ingresar datos de la mision\n");
        printf("2. Calcular parametros orbitales\n");
        printf("3. Simular pulso lateral\n");
        printf("4. Ver reporte final\n");
        printf("5. Salir\n");
        opcion = leer_entero("Opcion: ", 1, 5);

        switch (opcion) {
        case 1:
            alt_km = leer_real("Altitud sobre la superficie (km, 100-2000): ",
                               100.0, 2000.0);
            masa = leer_real("Masa de la nave (kg, 1-1000000): ",
                             1.0, 1000000.0);
            inicializar_orbita(alt_km * 1000.0, masa, &c);
            datos_cargados = 1;
            calculado = 0;
            pulso_hecho = 0;
            printf("Datos cargados correctamente.\n");
            break;

        case 2:
            if (!datos_cargados) {
                printf("Primero ingrese los datos (opcion 1).\n");
                break;
            }
            c.v_orb = calcular_velocidad_orbital(&c);
            c.per = calcular_periodo(&c);
            c.acel = calcular_aceleracion_centripeta(&c);
            c.fuerza = calcular_fuerza_gravitatoria(&c);
            calculado = 1;
            printf("Velocidad orbital: %.2f m/s\n", c.v_orb);
            printf("Periodo: %.2f s (%.2f min)\n", c.per, c.per / 60.0);
            printf("Aceleracion centripeta: %.4f m/s^2\n", c.acel);
            printf("Fuerza gravitatoria: %.2f N\n", c.fuerza);
            break;

        case 3:
            if (!calculado) {
                printf("Primero calcule los parametros (opcion 2).\n");
                break;
            }
            a = leer_real("Aceleracion del propulsor (m/s^2, 0-10): ",
                          0.0, 10.0);
            dt = leer_real("Duracion del pulso (s, 0-600): ", 0.0, 600.0);
            calcular_pulso_lateral(&c, a, dt, &dv, &desvio, &vf);
            pulso_hecho = 1;
            printf("Cambio de velocidad lateral: %.2f m/s\n", dv);
            printf("Desviacion lateral: %.2f m\n", desvio);
            printf("Velocidad final: %.4f m/s\n", vf);
            break;

        case 4:
            if (!calculado) {
                printf("Primero calcule los parametros (opcion 2).\n");
                break;
            }
            mostrar_reporte(&c);
            if (pulso_hecho) {
                printf("--- Pulso lateral ---\n");
                printf("Cambio de velocidad: %.2f m/s\n", dv);
                printf("Desviacion lateral:  %.2f m\n", desvio);
                printf("Velocidad final:     %.4f m/s\n", vf);
            }
            break;

        case 5:
            printf("Fin del simulador.\n");
            break;
        }
    } while (opcion != 5);

    return 0;
}