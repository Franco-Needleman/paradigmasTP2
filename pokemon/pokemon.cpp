#include "pokemon.hpp"

pokemon::pokemon(string nombre, int experiencia_actual) {
    this->nombre = nombre;
    this->experiencia_actual = experiencia_actual;
}

string pokemon::getNombre() const {
    return nombre;
}

int pokemon::getExperienciaActual() const {
    return experiencia_actual;
}

pokemon::~pokemon() {
    // El destructor está vacío ya que no hay memoria dinámica que liberar
} 