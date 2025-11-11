#include "Banco.h"
#include <iostream>
#include <stdexcept>
#include <cmath>       // Para std::abs
#include <algorithm>   // Para std::find_if, std::sort, std::for_each
#include <functional>
#include <memory>      // Para std::make_unique, std::move

/**
 * @file Banco9.cpp
 * @brief IMPLEMENTACIÓN del Modelo Banco usando punteros inteligentes.
 */

// --- MÉTODO ACTUALIZADO ---
// Ahora crea un puntero inteligente y lo *mueve* al vector.
void Banco::agregarCuenta(std::string titular, double saldoInicial) {
    // 1. Creamos el objeto en el heap usando std::make_unique
    auto nuevaCuenta = std::make_unique<CuentaBancaria>(proximoIdCuenta, titular, saldoInicial);
    
    // 2. Movemos la posesión del puntero al vector.
    this->cuentas.push_back(std::move(nuevaCuenta));
    proximoIdCuenta++;
}

void Banco::agregarTransaccion(Transaccion trans) {
    this->filaDeEspera.push(trans);
}

// --- MÉTODO ACTUALIZADO ---
// La lambda ahora compara contra el objeto dentro del unique_ptr.
std::vector<std::unique_ptr<CuentaBancaria>>::iterator Banco::buscarCuenta(int id) {
    auto predicado_busqueda = [id](const std::unique_ptr<CuentaBancaria>& cuentaPtr) {
        return cuentaPtr->getId() == id;
    };
    return std::find_if(cuentas.begin(), cuentas.end(), predicado_busqueda);
}

// --- MÉTODO ACTUALIZADO ---
// La lambda es similar, y .get() devuelve el raw pointer.
const CuentaBancaria* Banco::getCuentaPorId(int id) const {
    auto predicado_busqueda = [id](const std::unique_ptr<CuentaBancaria>& cuentaPtr) {
        return cuentaPtr->getId() == id;
    };
    
    auto iterador = std::find_if(cuentas.cbegin(), cuentas.cend(), predicado_busqueda);

    if (iterador != cuentas.cend()) {
        return iterador->get(); // .get() obtiene el raw pointer del unique_ptr
    }
    return nullptr;
}

// --- MÉTODO ACTUALIZADO ---
// Debe des-referenciar el iterador (*iterador) para obtener el unique_ptr,
// y luego usar -> para llamar al método del objeto.
std::vector<std::string> Banco::procesarFila() {
    std::vector<std::string> reporte;
    while (!filaDeEspera.empty()) {
        Transaccion trans = filaDeEspera.front();
        filaDeEspera.pop();

        auto iteradorCuenta = buscarCuenta(trans.idCuenta);

        if (iteradorCuenta != cuentas.end()) {
            try {
                // (*iteradorCuenta) es el unique_ptr
                // (*iteradorCuenta)->... es la llamada al método
                if (trans.monto > 0) {
                    (*iteradorCuenta)->depositar(trans.monto);
                    reporte.push_back("EXITO: Deposito de $" + std::to_string(trans.monto) + " a cuenta " + std::to_string(trans.idCuenta));
                } else {
                    (*iteradorCuenta)->retirar(std::abs(trans.monto));
                    reporte.push_back("EXITO: Retiro de $" + std::to_string(std::abs(trans.monto)) + " de cuenta " + std::to_string(trans.idCuenta));
                }
            } catch (const std::exception& e) {
                reporte.push_back("FALLO (Cuenta " + std::to_string(trans.idCuenta) + "): " + e.what());
            }
        } else {
            reporte.push_back("FALLO: Cuenta " + std::to_string(trans.idCuenta) + " no encontrada.");
        }
    }
    return reporte;
}

// --- MÉTODO ACTUALIZADO ---
// Transforma el vector de unique_ptr en un vector de raw pointers (const)
// para que la Vista los pueda leer.
std::vector<const CuentaBancaria*> Banco::getCuentas() const {
    std::vector<const CuentaBancaria*> punteros;
    punteros.reserve(cuentas.size()); // Buena práctica

    // Usamos std::transform para convertir cada unique_ptr a su raw pointer
    std::transform(cuentas.begin(), cuentas.end(), std::back_inserter(punteros),
        [](const std::unique_ptr<CuentaBancaria>& ptr) {
            return ptr.get(); // .get() obtiene el raw pointer
        });
        
    return punteros;
}

// --- MÉTODO ACTUALIZADO ---
// Reutiliza getCuentas() y ordena el vector de raw pointers.
std::vector<const CuentaBancaria*> Banco::getRankingDeCuentas() const {
    // 1. Obtenemos el vector de punteros de observación
    std::vector<const CuentaBancaria*> punterosCuentas = this->getCuentas();

    // 2. Definimos la lambda de comparación (ahora compara punteros)
    auto lambda_comparacion = [](const CuentaBancaria* a, const CuentaBancaria* b) {
        return a->getSaldo() > b->getSaldo(); // Orden descendente
    };

    // 3. Usamos std::sort
    std::sort(punterosCuentas.begin(), punterosCuentas.end(), lambda_comparacion);

    return punterosCuentas;
}

// --- MÉTODO ACTUALIZADO ---
// La lambda de for_each ahora opera sobre el unique_ptr.
void Banco::aplicarInteresMensual(double tasa) {
    // 1. Definimos la lambda de acción.
    // Recibe el unique_ptr por referencia.
    auto lambda_aplicar_interes = [tasa](std::unique_ptr<CuentaBancaria>& cuentaPtr) {
        if (cuentaPtr->getSaldo() > 0) {
            double interes = cuentaPtr->getSaldo() * tasa;
            try {
                cuentaPtr->depositar(interes);
            } catch (...) { /* Ignorar errores en este caso */ }
        }
    };

    // 2. Usamos el algoritmo std::for_each
    std::for_each(cuentas.begin(), cuentas.end(), lambda_aplicar_interes);
}