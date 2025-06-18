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
        pokemon() = default;
        string getNombre() const;
        unsigned int getExperienciaActual() const;
        bool operator==(const pokemon& otro) const;
        ~pokemon() = default;

        void serealizar(ofstream& out) const;
        void deserealizar(ifstream& in);
};

