#pragma once

#include <unordered_map>
#include "pokemon.hpp"
#include "pokemoninfo.hpp"

using namespace std;

// Estructura hash para usar pokemon como clave en unordered_map
struct PokemonHash {
    size_t operator()(const pokemon& p) const;
};

// Clase que representa una Pokedex completa usando unordered_map
class Pokedex {
private:
    string nombre_archivo;
    unordered_map<pokemon, pokemoninfo, PokemonHash> pokedex;
public:
    // Constructor que carga datos desde archivo
    Pokedex(ifstream& in);
    Pokedex();
    ~Pokedex() = default;
    
    // Agrega un nuevo Pokemon y guarda automaticamente en archivo
    void agregar(const pokemon& p, const pokemoninfo& info);
    
    // Muestra informacion de un Pokemon especifico o de todos
    void mostrar(const pokemon& p) const;
    void mostrarTodos() const;
    
    // Calcula y muestra el nivel actual y experiencia necesaria para subir
    void imprimir_exp(const pokemon& p, const pokemoninfo& pinf) const;
    
    // Serializa/deserializa toda la Pokedex
    void imprimir_exp(const pokemon& p, const pokemoninfo& pinf) const;
    void serealizar(ofstream& out) const;
    void deserealizar(ifstream& in);
}; 