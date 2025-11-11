#ifndef CONSOLA_H
#define CONSOLA_H

#include <string>
#include <vector>
// Incluimos los modelos por sus nuevos nombres
#include "../model/CuentaBancaria.h"
#include "../model/Transaccion.h"

/**
 * @class VistaConsola (Vista)
 * @brief Responsable de toda la interacción (cout/cin) con el usuario.
 */
class VistaConsola {
public:
    static int mostrarMenu();
    static CuentaBancaria pedirDatosNuevaCuenta(); // Simulación
    static Transaccion pedirDatosTransaccion();
    static int pedirIdCuenta();
    static double pedirTasaInteres();

    static void mostrarReporte(const std::string& titulo, const std::vector<std::string>& reporte);

    // --- CAMBIO CLAVE ---
    // Ahora recibe un vector de punteros de observación (const)
    static void mostrarCuentas(const std::vector<const CuentaBancaria*>& cuentas);

    static void mostrarMensaje(const std::string& mensaje);

    // Este ya estaba bien, recibía un puntero
    static void mostrarDetalleCuenta(const CuentaBancaria* cuenta);

    static void esperarEnter();
    static void limpiarBufferEntrada();
};

#endif //CONSOLA_H