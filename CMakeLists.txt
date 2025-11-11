cmake_minimum_required(VERSION 4.0)
project(Clase_SmartPtr)

set(CMAKE_CXX_STANDARD 20)

add_executable(Clase_SmartPtr main.cpp
        Model/Transaccion.h
        Model/CuentaBancaria.h
        Model/Banco.cpp
        Model/Banco.h
        View/Consola.cpp
        View/Consola.h
        Controller/ControladorBanco.cpp
        Controller/ControladorBanco.h)
