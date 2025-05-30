#include "../headers/pokedex.hpp"
#include <iostream>

size_t PokemonHash::operator()(const pokemon& p) const {
    return hash<string>()(p.getNombre() + to_string(p.getExperienciaActual()));
}

void Pokedex::agregar(const pokemon& p, const pokemoninfo& info) {
    pokedex[p] = info;
}

void Pokedex::mostrar(const pokemon& p) const {
    auto it = pokedex.find(p);
    if (it != pokedex.end()) {
        cout << "Pokemon: " << p.getNombre() << endl;
        cout << "Experiencia Actual: " << p.getExperienciaActual() << endl;
        it->second.mostrar();
    } else {
        cout << "¡Pokemon desconocido!" << endl;
    }
} 

void Pokedex::mostrarTodos() const {
    for (const auto& entry : pokedex) {
        cout << "Pokemon: " << entry.first.getNombre() << endl;
        cout << "Experiencia Actual: " << entry.first.getExperienciaActual() << endl;
        entry.second.mostrar();
        cout << "------------------------" << endl;
    }
}