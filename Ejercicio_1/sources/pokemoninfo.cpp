#include "../headers/pokemoninfo.hpp"
#include <fstream>

// Constructor que inicializa todos los datos usando lista de inicializacion
pokemoninfo::pokemoninfo(string type, string descripcion, map<string,unsigned int> ataquesDisponiblesPorNivel, vector<unsigned int> experienciaProximoNivel)
    : type(type), descripcion(descripcion), ataquesDisponiblesPorNivel(ataquesDisponiblesPorNivel), experienciaProximoNivel(experienciaProximoNivel) {}

// Retorna el tipo del Pokemon
string pokemoninfo::getType() const {
    return type;
}

// Retorna la descripcion del Pokemon
string pokemoninfo::getDescripcion() const {
    return descripcion;
}

// Retorna el mapa de ataques disponibles por nivel
map<string, unsigned int> pokemoninfo::getAtaquesDisponiblesPorNivel() const {
    return ataquesDisponiblesPorNivel;
}

// Retorna el vector de experiencia necesaria por nivel
vector<unsigned int> pokemoninfo::getExperienciaProximoNivel() const {
    return experienciaProximoNivel;
}

// Muestra tipo, descripcion y lista de ataques con su dano
void pokemoninfo::mostrar() const {
    cout << "Tipo: " << type << endl;
    cout << "Descripcion: " << descripcion << endl;
    cout << "Ataques disponibles por nivel:" << endl;
    for (const auto& ataque : ataquesDisponiblesPorNivel) {
        cout << "  - " << ataque.first << ": Dano: " << ataque.second << endl;
    }
    /*
    for (int i=0; i < 3; ++i) {
        if (i > 0){
            cout <<"Experiencia necesaria para nivel "<< i+1 << ": " << experienciaProximoNivel[i];
            break;
        }
        if (experienciaProximoNivel[2]==0){
            cout << "nivel maximo (3)";
            break;
        }
    }
    cout << endl;*/
}

// Serializa todos los datos: tipo, descripcion, ataques y experiencia
void pokemoninfo::serealizar(ofstream& out) const {
    size_t typeSize = type.size(); // Para saber cuanto leer
    out.write(reinterpret_cast<const char*>(&typeSize),sizeof(typeSize)); // Se escribe el tamano del tipo
    out.write(type.c_str(), typeSize);
    size_t descripcionSize = descripcion.size(); // Para saber cuanto leer
    out.write(reinterpret_cast<const char*>(&descripcionSize), sizeof(descripcionSize)); // Se escribe el tamano de la descripcion
    out.write(descripcion.c_str(), descripcionSize);
    size_t ataquesSize = ataquesDisponiblesPorNivel.size(); // Para saber cuanto leer
    out.write(reinterpret_cast<const char*>(&ataquesSize), sizeof(ataquesSize)); // Se escribe el tamano de los ataques
    for (const auto& ataque : ataquesDisponiblesPorNivel) {
        size_t ataqueSize = ataque.first.size(); // Para saber cuanto leer
        out.write(reinterpret_cast<const char*>(&ataqueSize), sizeof(ataqueSize)); // Se escribe el tamano del ataque
        out.write(ataque.first.c_str(), ataqueSize); // Se escribe el nombre del ataque
        out.write(reinterpret_cast<const char*>(&ataque.second), sizeof(ataque.second)); // Se escribe el dano del ataque
    }
    size_t expSize = experienciaProximoNivel.size(); // Para saber cuanto leer
    out.write(reinterpret_cast<const char*>(&expSize), sizeof(expSize)); // Se escribe el tamano de la experiencia
    
    out.write(reinterpret_cast<const char*>(experienciaProximoNivel.data()), expSize * sizeof(unsigned int)); // Se escribe la experiencia
}

// Deserializa todos los datos: tipo, descripcion, ataques y experiencia
void pokemoninfo::deserealizar(ifstream& in) {
    size_t typeSize;
    in.read(reinterpret_cast<char*>(&typeSize), sizeof(typeSize)); // Se lee el tamano del tipo
    type.resize(typeSize); // Redimensionamos el string para que tenga el tamano correcto
    in.read(&type[0], typeSize); // Se lee el tipo

    size_t descripcionSize;
    in.read(reinterpret_cast<char*>(&descripcionSize), sizeof(descripcionSize)); // Se lee el tamano de la descripcion
    descripcion.resize(descripcionSize); // Redimensionamos el string para que tenga el tamano correcto
    in.read(&descripcion[0], descripcionSize); // Se lee la descripcion

    size_t ataquesSize;
    in.read(reinterpret_cast<char*>(&ataquesSize), sizeof(ataquesSize)); // Se lee el tamano de los ataques
    for (size_t i = 0; i < ataquesSize; ++i) {
        size_t ataqueSize;
        in.read(reinterpret_cast<char*>(&ataqueSize), sizeof(ataqueSize)); // Se lee el tamano del ataque
        string ataque;
        ataque.resize(ataqueSize); // Redimensionamos el string para que tenga el tamano correcto
        in.read(&ataque[0], ataqueSize); // Se lee el nombre del ataque
        unsigned int dano;
        in.read(reinterpret_cast<char*>(&dano), sizeof(dano)); // Se lee el dano del ataque
        ataquesDisponiblesPorNivel[ataque] = dano; // Guardamos el ataque en el mapa
    }

    size_t expSize;
    in.read(reinterpret_cast<char*>(&expSize), sizeof(expSize)); // Se lee el tamano de la experiencia
    experienciaProximoNivel.resize(expSize); // Redimensionamos el vector para que tenga el tamano correcto
    in.read(reinterpret_cast<char*>(experienciaProximoNivel.data()), expSize * sizeof(unsigned int)); // Se lee la experiencia
}