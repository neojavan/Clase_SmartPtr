#ifndef TRANSACCION_H
#define TRANSACCION_H

/**
 * @struct Transaccion (Modelo)
 * @brief Almacena los datos de una operación pendiente.
 */
struct Transaccion {
    int idCuenta;
    double monto; // Positivo para depósito, negativo para retiro
};

#endif //TRANSACCION_H