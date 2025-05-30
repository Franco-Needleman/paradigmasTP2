#pragma once

#include <iostream>
#include <string>

using namespace std;

class pokemon {
    private:
        string nombre;
        unsigned int experiencia_actual;
    public:
        pokemon(string nombre, unsigned int experiencia_actual);
        string getNombre() const;
        unsigned int getExperienciaActual() const;
        ~pokemon() = default;
};

