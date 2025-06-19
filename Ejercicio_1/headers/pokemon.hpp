#pragma once

#include <iostream>
#include <string>

using namespace std;

// Clase que representa un Pokemon con nombre y experiencia
class pokemon {
    private:
        string nombre;
        unsigned int experiencia_actual;
    public:
        // Constructor que inicializa un Pokemon con nombre y experiencia
        pokemon(string nombre, unsigned int experiencia_actual);
        pokemon() = default;
        
        // Getters para acceder a los datos del Pokemon
        string getNombre() const;
        unsigned int getExperienciaActual() const;
        
        // Compara dos Pokemon por nombre (ignora experiencia)
        bool operator==(const pokemon& otro) const;
        ~pokemon() = default;

        // Serializa/deserializa el Pokemon
        void serealizar(ofstream& out) const;
        void deserealizar(ifstream& in);
};

