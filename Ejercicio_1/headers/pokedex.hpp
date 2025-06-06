#pragma once

#include <unordered_map>
#include "pokemon.hpp"
#include "pokemoninfo.hpp"

using namespace std;

struct PokemonHash {
    size_t operator()(const pokemon& p) const;
};

class Pokedex {
private:
    
    unordered_map<pokemon, pokemoninfo, PokemonHash> pokedex;
public:
    Pokedex(ifstream& in);
    Pokedex() = default;
    ~Pokedex() = default;
    void agregar(const pokemon& p, const pokemoninfo& info);
    void mostrar(const pokemon& p) const;
    void mostrarTodos() const;
    void serealizar(ofstream& out) const;
    void deserealizar(ifstream& in);
}; 