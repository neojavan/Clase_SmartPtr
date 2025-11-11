#ifndef CUENTABANCARIA_H
#define CUENTABANCARIA_H

#include <string>
#include <stdexcept> // Para las excepciones

/**
 * @class CuentaBancaria (Modelo)
 * @brief Gestiona los datos de una cuenta. Usa excepciones para errores.
 */
class CuentaBancaria {
private:
    int id;
    std::string titular;
    double saldo;

public:
    CuentaBancaria(int id, std::string titular, double saldoInicial)
        : id(id), titular(titular), saldo(saldoInicial > 0 ? saldoInicial : 0.0) {}

    // Getters
    int getId() const { return id; }
    double getSaldo() const { return saldo; }
    std::string getTitular() const { return titular; }

    // Métodos de negocio que lanzan excepciones
    void depositar(double monto) {
        if (monto <= 0) {
            throw std::invalid_argument("Monto a depositar debe ser positivo.");
        }
        this->saldo += monto;
    }

    void retirar(double monto) {
        if (monto <= 0) {
            throw std::invalid_argument("Monto a retirar debe ser positivo.");
        }
        if (monto > this->saldo) {
            throw std::runtime_error("Fondos insuficientes.");
        }
        this->saldo -= monto;
    }
};

#endif //CUENTABANCARIA_H