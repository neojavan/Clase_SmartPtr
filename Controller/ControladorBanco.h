#ifndef CONTROLADORBANCO_H
#define CONTROLADORBANCO_H

// Includes actualizados a los nuevos nombres
#include "../model/Banco.h"
#include "../view/Consola.h"

/**
 * @class ControladorBanco (Controlador)
 * @brief Orquesta la interacción entre la Vista y el Modelo.
 */
class ControladorBanco {
private:
    Banco modelo; // El Controlador posee la instancia del Modelo.
    VistaConsola vista; // El Controlador usa la Vista (estática en este caso).

    // Métodos privados para manejar cada opción del menú
    void manejarAgregarCuenta();
    void manejarAgregarTransaccion();
    void manejarProcesarFila();
    void manejarVerCuentas();
    void manejarBuscarCuenta();
    void manejarVerRanking();
    void manejarAplicarInteres();

public:
    ControladorBanco();
    void ejecutar(); // Método principal que inicia el bucle de la aplicación.
};

#endif //CONTROLADORBANCO_H