#ifndef BANCO_H
#define BANCO_H

#include <vector>
#include <queue>
#include <string>
#include <memory> // ¡NUEVO! Para punteros inteligentes
#include "CuentaBancaria.h"
#include "Transaccion.h"

/**
 * @class Banco (Modelo)
 * @brief Clase principal del modelo. Gestiona las cuentas y transacciones.
 * AHORA usa std::unique_ptr para poseer las cuentas.
 */
class Banco {
private:
    // --- CAMBIO CLAVE ---
    // El banco ahora *posee* las cuentas usando punteros únicos.
    std::vector<std::unique_ptr<CuentaBancaria>> cuentas;

    std::queue<Transaccion> filaDeEspera;
    int proximoIdCuenta = 1;

    // Método de utilidad (ahora busca en un vector de unique_ptr)
    std::vector<std::unique_ptr<CuentaBancaria>>::iterator buscarCuenta(int id);

public:
    void agregarCuenta(std::string titular, double saldoInicial);
    void agregarTransaccion(Transaccion trans);
    std::vector<std::string> procesarFila();

    // --- CAMBIO CLAVE ---
    // Devuelve un vector de punteros de *observación* (raw pointers)
    // para que la Vista pueda leerlos sin tomar posesión.
    std::vector<const CuentaBancaria*> getCuentas() const;

    // --- (Clase 22) ---

    // El prototipo no cambia, sigue devolviendo un raw pointer de observación.
    const CuentaBancaria* getCuentaPorId(int id) const;

    // --- CAMBIO CLAVE ---
    // Devuelve un vector de punteros de observación ordenados.
    std::vector<const CuentaBancaria*> getRankingDeCuentas() const;

    // Método que usa std::for_each para modificar las cuentas.
    void aplicarInteresMensual(double tasa);
};

#endif //BANCO_H