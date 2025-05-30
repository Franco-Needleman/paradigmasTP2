#pragma once

#include <iostream>
#include <string>

using namespace std;

class pokemon {
    private:
        string nombre;
        int experiencia_actual;
    public:
        pokemon(string nombre, int experiencia_actual);
        string getNombre() const;
        int getExperienciaActual() const;
        ~pokemon() = default;
};

