#pragma once

#include <iostream>
#include <string>
using namespace std;

class pokemoninfo {
private:
    string type;
    string descripcion;
    void* ataquesDisponiblesPorNivel;
    void* experienciaProximoNivel;

public:
    ~pokemoninfo() {
        // Liberar la memoria de los punteros
        if (ataquesDisponiblesPorNivel != nullptr) {
            delete ataquesDisponiblesPorNivel;
        }
        if (experienciaProximoNivel != nullptr) {
            delete experienciaProximoNivel;
        }
    }
}; 