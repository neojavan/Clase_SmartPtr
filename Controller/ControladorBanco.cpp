#include "ControladorBanco.h"
#include <vector>
#include <string>

/**
 * @file ControladorBanco.cpp
 * @brief IMPLEMENTACIÓN del Controlador.
 */

ControladorBanco::ControladorBanco() {
    // Inicializamos el banco con datos de ejemplo.
    modelo.agregarCuenta("Javier Gallego", 500000);
    modelo.agregarCuenta("Anastasia Romanov", 200000);
    modelo.agregarCuenta("Aragorn Elessar Telcontar", 750000);
}

void ControladorBanco::ejecutar() {
    int opcion = 0;
    do {
        opcion = vista.mostrarMenu();
        switch (opcion) {
            case 1: manejarAgregarCuenta(); break;
            case 2: manejarAgregarTransaccion(); break;
            case 3: manejarProcesarFila(); break;
            case 4: manejarVerCuentas(); break;
            case 5: manejarBuscarCuenta(); break;
            case 6: manejarVerRanking(); break;
            case 7: manejarAplicarInteres(); break;
            case 8: vista.mostrarMensaje("Saliendo del sistema..."); break;
            default: vista.mostrarMensaje("Opción no válida."); break;
        }
        if (opcion != 8) {
            vista.esperarEnter();
        }
    } while (opcion != 8);
}

void ControladorBanco::manejarAgregarCuenta() {
    CuentaBancaria temp = vista.pedirDatosNuevaCuenta();
    modelo.agregarCuenta(temp.getTitular(), temp.getSaldo());
    vista.mostrarMensaje("Cuenta agregada con éxito.");
}

void ControladorBanco::manejarAgregarTransaccion() {
    Transaccion trans = vista.pedirDatosTransaccion();
    modelo.agregarTransaccion(trans);
    vista.mostrarMensaje("Transacción agregada a la fila.");
}

void ControladorBanco::manejarProcesarFila() {
    vista.mostrarMensaje("Procesando fila de transacciones...");
    std::vector<std::string> reporte = modelo.procesarFila();
    vista.mostrarReporte("Resultado del Procesamiento", reporte);
}

// Este método ahora funciona correctamente porque
// modelo.getCuentas() devuelve vector<const CuentaBancaria*>
// y vista.mostrarCuentas() acepta ese tipo.
void ControladorBanco::manejarVerCuentas() {
    vista.mostrarReporte("Estado Actual de Cuentas", {});
    vista.mostrarCuentas(modelo.getCuentas());
}

// Este método ya estaba bien, getCuentaPorId() devuelve const CuentaBancaria*
// y mostrarDetalleCuenta() acepta ese tipo.
void ControladorBanco::manejarBuscarCuenta() {
    int id = vista.pedirIdCuenta();
    const CuentaBancaria* cuenta = modelo.getCuentaPorId(id);
    vista.mostrarDetalleCuenta(cuenta);
}

// --- MÉTODO ACTUALIZADO ---
void ControladorBanco::manejarVerRanking() {
    // 1. El tipo de 'ranking' debe cambiar para coincidir
    //    con el nuevo tipo de retorno de getRankingDeCuentas().
    std::vector<const CuentaBancaria*> ranking = modelo.getRankingDeCuentas();
    
    // 2. Pasa el resultado a la vista (esto ya funciona)
    vista.mostrarReporte("Ranking de Cuentas por Saldo", {});
    vista.mostrarCuentas(ranking);
}

void ControladorBanco::manejarAplicarInteres() {
    double tasa = vista.pedirTasaInteres();
    modelo.aplicarInteresMensual(tasa);
    vista.mostrarMensaje("Interes aplicado a todas las cuentas.");
    // Muestra el resultado (esto ya funciona)
    manejarVerCuentas();
}