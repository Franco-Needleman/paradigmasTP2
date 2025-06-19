#include "../headers/pokemon.hpp"
#include <fstream>

// Constructor que inicializa nombre y experiencia usando lista de inicializacion
pokemon::pokemon(string nombre, unsigned int experiencia_actual) :
    nombre(nombre), experiencia_actual(experiencia_actual) {}

// Retorna el nombre del Pokemon
string pokemon::getNombre() const {
    return nombre;
}

// Retorna la experiencia actual del Pokemon
unsigned int pokemon::getExperienciaActual() const {
    return experiencia_actual;
}

// Compara dos Pokemon por nombre (la experiencia no se considera)
bool pokemon::operator==(const pokemon& otro) const {
    return nombre == otro.nombre ;
}

// Escribe el Pokemon en formato binario: tamano del nombre + nombre + experiencia
void pokemon::serealizar(ofstream& out) const {
    size_t nombre_size = nombre.size(); // Para saber cuanto leer
    out.write(reinterpret_cast<const char*>(&nombre_size), sizeof(nombre_size)); // Se escribe el tamano del nombre
    out.write(nombre.c_str(), nombre_size); // Se escribe el nombre

    out.write( reinterpret_cast<const char*>(&experiencia_actual), sizeof(experiencia_actual) );

}

// Lee el Pokemon desde formato binario: tamano del nombre + nombre + experiencia
void pokemon::deserealizar(ifstream& in) {
    size_t nombre_size;
    in.read(reinterpret_cast<char*>(&nombre_size), sizeof(nombre_size)); // Se lee el tamano del nombre
    nombre.resize(nombre_size); // Redimensionamos el string para que tenga el tamano correcto
    in.read(&nombre[0], nombre_size); // Se lee el nombre
    in.read( reinterpret_cast<char*>(&experiencia_actual), sizeof(experiencia_actual) );

}