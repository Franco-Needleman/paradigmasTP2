#include "../headers/pokemoninfo.hpp"
#include <fstream>
pokemoninfo::pokemoninfo(string type, string descripcion, map<string,unsigned int> ataquesDisponiblesPorNivel, vector<unsigned int> experienciaProximoNivel)
    : type(type), descripcion(descripcion), ataquesDisponiblesPorNivel(ataquesDisponiblesPorNivel), experienciaProximoNivel(experienciaProximoNivel) {}

string pokemoninfo::getType() const {
    return type;
}
string pokemoninfo::getDescripcion() const {
    return descripcion;
}

map<string, unsigned int> pokemoninfo::getAtaquesDisponiblesPorNivel() const {
    return ataquesDisponiblesPorNivel;
}
vector<unsigned int> pokemoninfo::getExperienciaProximoNivel() const {
    return experienciaProximoNivel;
}

void pokemoninfo::mostrar() const {
    cout << "Tipo: " << type << endl;
    cout << "Descripción: " << descripcion << endl;
    cout << "Ataques disponibles por nivel:" << endl;
    for (const auto& ataque : ataquesDisponiblesPorNivel) {
        cout << "  - " << ataque.first << ": Daño: " << ataque.second << endl;
    }
    cout << "Experiencia para próximos niveles: ";
    for (const auto& exp : experienciaProximoNivel) {
        cout << exp << " ";
    }
    cout << endl;
}

void pokemoninfo::serealizar(ofstream& out) const {
    size_t typeSize = type.size(); // Para saber cuanto leer
    out.write(reinterpret_cast<const char*>(&typeSize),sizeof(typeSize)); // Se escribe el tamaño del tipo
    out.write(type.c_str(), typeSize);
    size_t descripcionSize = descripcion.size(); // Para saber cuanto leer
    out.write(reinterpret_cast<const char*>(&descripcionSize), sizeof(descripcionSize)); // Se escribe el tamaño de la descripción
    out.write(descripcion.c_str(), descripcionSize);
    size_t ataquesSize = ataquesDisponiblesPorNivel.size(); // Para saber cuanto leer
    out.write(reinterpret_cast<const char*>(&ataquesSize), sizeof(ataquesSize)); // Se escribe el tamaño de los ataques
    for (const auto& ataque : ataquesDisponiblesPorNivel) {
        size_t ataqueSize = ataque.first.size(); // Para saber cuanto leer
        out.write(reinterpret_cast<const char*>(&ataqueSize), sizeof(ataqueSize)); // Se escribe el tamaño del ataque
        out.write(ataque.first.c_str(), ataqueSize); // Se escribe el nombre del ataque
        out.write(reinterpret_cast<const char*>(&ataque.second), sizeof(ataque.second)); // Se escribe el daño del ataque
    }
    size_t expSize = experienciaProximoNivel.size(); // Para saber cuanto leer
    out.write(reinterpret_cast<const char*>(&expSize), sizeof(expSize)); // Se escribe el tamaño de la experiencia
    
    out.write(reinterpret_cast<const char*>(experienciaProximoNivel.data()), expSize * sizeof(unsigned int)); // Se escribe la experiencia
}

void pokemoninfo::deserealizar(ifstream& in) {
    size_t typeSize;
    in.read(reinterpret_cast<char*>(&typeSize), sizeof(typeSize)); // Se lee el tamaño del tipo
    type.resize(typeSize); // Redimensionamos el string para que tenga el tamaño correcto
    in.read(&type[0], typeSize); // Se lee el tipo

    size_t descripcionSize;
    in.read(reinterpret_cast<char*>(&descripcionSize), sizeof(descripcionSize)); // Se lee el tamaño de la descripción
    descripcion.resize(descripcionSize); // Redimensionamos el string para que tenga el tamaño correcto
    in.read(&descripcion[0], descripcionSize); // Se lee la descripción

    size_t ataquesSize;
    in.read(reinterpret_cast<char*>(&ataquesSize), sizeof(ataquesSize)); // Se lee el tamaño de los ataques
    for (size_t i = 0; i < ataquesSize; ++i) {
        size_t ataqueSize;
        in.read(reinterpret_cast<char*>(&ataqueSize), sizeof(ataqueSize)); // Se lee el tamaño del ataque
        string ataque;
        ataque.resize(ataqueSize); // Redimensionamos el string para que tenga el tamaño correcto
        in.read(&ataque[0], ataqueSize); // Se lee el nombre del ataque
        unsigned int daño;
        in.read(reinterpret_cast<char*>(&daño), sizeof(daño)); // Se lee el daño del ataque
        ataquesDisponiblesPorNivel[ataque] = daño; // Guardamos el ataque en el mapa
    }

    size_t expSize;
    in.read(reinterpret_cast<char*>(&expSize), sizeof(expSize)); // Se lee el tamaño de la experiencia
    experienciaProximoNivel.resize(expSize); // Redimensionamos el vector para que tenga el tamaño correcto
    in.read(reinterpret_cast<char*>(experienciaProximoNivel.data()), expSize * sizeof(unsigned int)); // Se lee la experiencia
}