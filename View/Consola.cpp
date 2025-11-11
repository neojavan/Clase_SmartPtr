#include "Consola.h"
#include <iostream>
#include <limits>
#include <iomanip> // Para std::setw, std::fixed, std::setprecision

/**
 * @file Consola9.cpp
 * @brief IMPLEMENTACIÓN de la Vista.
 */

int VistaConsola::mostrarMenu() {
    std::cout << "\n===== SIMULADOR BANCARIO (MVC + Punteros Inteligentes) =====" << std::endl; // Título actualizado
    std::cout << "1. Agregar nueva cuenta bancaria" << std::endl;
    std::cout << "2. Agregar transaccion a la fila" << std::endl;
    std::cout << "3. Procesar todas las transacciones de la fila" << std::endl;
    std::cout << "4. Ver estado de todas las cuentas" << std::endl;
    std::cout << "5. Buscar cuenta por ID" << std::endl;
    std::cout << "6. Ver ranking de cuentas por saldo" << std::endl;
    std::cout << "7. Aplicar interes mensual a todas las cuentas" << std::endl;
    std::cout << "8. Salir" << std::endl;
    std::cout << "==========================================================" << std::endl;
    std::cout << "Seleccione una opcion: ";
    int opcion;
    std::cin >> opcion;
    limpiarBufferEntrada();
    return opcion;
}

CuentaBancaria VistaConsola::pedirDatosNuevaCuenta() {
    std::string titular;
    double saldoInicial;
    std::cout << "Ingrese nombre del titular: ";
    std::getline(std::cin, titular);
    std::cout << "Ingrese saldo inicial: $";
    std::cin >> saldoInicial;
    limpiarBufferEntrada();
    return CuentaBancaria(0, titular, saldoInicial); // ID temporal 0
}

Transaccion VistaConsola::pedirDatosTransaccion() {
    Transaccion trans;
    std::cout << "Ingrese ID de la cuenta: ";
    std::cin >> trans.idCuenta;
    std::cout << "Ingrese el monto (positivo para deposito, negativo para retiro): $";
    std::cin >> trans.monto;
    limpiarBufferEntrada();
    return trans;
}

int VistaConsola::pedirIdCuenta() {
    int id;
    std::cout << "Ingrese el ID de la cuenta a buscar: ";
    std::cin >> id;
    limpiarBufferEntrada();
    return id;
}

double VistaConsola::pedirTasaInteres() {
    double tasa;
    std::cout << "Ingrese la tasa de interes (ej. 0.02 para 2%): ";
    std::cin >> tasa;
    limpiarBufferEntrada();
    return tasa;
}

void VistaConsola::mostrarReporte(const std::string& titulo, const std::vector<std::string>& reporte) {
    std::cout << "\n--- " << titulo << " ---" << std::endl;
    if (reporte.empty()) {
        std::cout << "(No hay nada que reportar)" << std::endl;
        return;
    }
    for (const auto& linea : reporte) {
        std::cout << "  " << linea << std::endl;
    }
}

// --- MÉTODO ACTUALIZADO ---
// Ahora itera sobre un vector de punteros (const CuentaBancaria*).
void VistaConsola::mostrarCuentas(const std::vector<const CuentaBancaria*>& cuentas) {
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(25) << "Titular"
              << std::right << std::setw(15) << "Saldo" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    
    // El bucle for-each ahora usa un puntero
    for (const CuentaBancaria* cuenta : cuentas) {
        // Usamos el operador -> en lugar de .
        std::cout << std::left << std::setw(5) << cuenta->getId()
                  << std::setw(25) << cuenta->getTitular()
                  << std::right << std::setw(15) << cuenta->getSaldo() << std::endl;
    }
}

// Este método ya estaba correcto, usaba un puntero.
void VistaConsola::mostrarDetalleCuenta(const CuentaBancaria* cuenta) {
    if (cuenta != nullptr) {
        std::cout << "\n--- Detalle de la Cuenta ---" << std::endl;
        std::cout << "ID:      " << cuenta->getId() << std::endl;
        std::cout << "Titular: " << cuenta->getTitular() << std::endl;
        std::cout << "Saldo:   $" << std::fixed << std::setprecision(2) << cuenta->getSaldo() << std::endl;
    } else {
        std::cout << ">> Error: La cuenta no existe." << std::endl;
    }
}

void VistaConsola::mostrarMensaje(const std::string& mensaje) {
    std::cout << ">> " << mensaje << std::endl;
}

void VistaConsola::esperarEnter() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.get();
}

void VistaConsola::limpiarBufferEntrada() {
    if (std::cin.fail()) {
        std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (std::cin.peek() == '\n') {
       std::cin.ignore();
    }
}