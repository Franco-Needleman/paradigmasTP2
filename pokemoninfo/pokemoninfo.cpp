#include "pokemoninfo.hpp"
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
unsigned int pokemoninfo::getsiguientenivel() const {
    if (experienciaProximoNivel.empty()) {
        return 0; // Indica que no hay niveles siguientes
    }

    for (const auto& exp: experienciaProximoNivel) {
        if (exp > 0) {
            return exp; 
            // Retorna el primer nivel con experiencia positiva
        }
    }
    return 0;
}