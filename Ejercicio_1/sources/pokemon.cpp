#include "../headers/pokemon.hpp"
#include <fstream>
pokemon::pokemon(string nombre, unsigned int experiencia_actual) :
    nombre(nombre), experiencia_actual(experiencia_actual) {}

string pokemon::getNombre() const {
    return nombre;
}

unsigned int pokemon::getExperienciaActual() const {
    return experiencia_actual;
}

bool pokemon::operator==(const pokemon& otro) const {
    return nombre == otro.nombre && experiencia_actual == otro.experiencia_actual;
}

void pokemon::serealizar(ofstream& out) const {
    size_t nombre_size = nombre.size(); // Para saber cuanto leer
    out.write(reinterpret_cast<const char*>(&nombre_size), sizeof(nombre_size)); // Se escribe el tamaño del nombre
    out.write(nombre.c_str(), nombre_size); // Se escribe el nombre

    out.write( reinterpret_cast<const char*>(&experiencia_actual), sizeof(experiencia_actual) );

}

void pokemon::deserealizar(ifstream& in) {
    size_t nombre_size;
    in.read(reinterpret_cast<char*>(&nombre_size), sizeof(nombre_size)); // Se lee el tamaño del nombre
    nombre.resize(nombre_size); // Redimensionamos el string para que tenga el tamaño correcto
    in.read(&nombre[0], nombre_size); // Se lee el nombre
    in.read( reinterpret_cast<char*>(&experiencia_actual), sizeof(experiencia_actual) );

}