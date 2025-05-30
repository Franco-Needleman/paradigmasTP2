#include "../headers/pokemoninfo.hpp"
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