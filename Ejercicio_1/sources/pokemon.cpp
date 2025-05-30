#include "pokemon.hpp"

pokemon::pokemon(string nombre, unsigned int experiencia_actual) :
    nombre(nombre), experiencia_actual(experiencia_actual) {}

string pokemon::getNombre() const {
    return nombre;
}

unsigned int pokemon::getExperienciaActual() const {
    return experiencia_actual;
}
