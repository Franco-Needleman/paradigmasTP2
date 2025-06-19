#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

// Clase que contiene informacion detallada de un tipo de Pokemon
class pokemoninfo {
private:
    string type;
    string descripcion;
    map<string,unsigned int> ataquesDisponiblesPorNivel;
    vector<unsigned int> experienciaProximoNivel;
public:
    // Constructor que inicializa con tipo, descripcion, ataques y experiencia por nivel
    pokemoninfo(string type, string descripcion, map<string,unsigned int> ataquesDisponiblesPorNivel, vector<unsigned int> experienciaProximoNivel);
    pokemoninfo() = default;
    ~pokemoninfo() = default;

    // Getters para acceder a la informacion del Pokemon
    string getType() const;
    string getDescripcion() const;
    map<string, unsigned int> getAtaquesDisponiblesPorNivel() const;
    vector<unsigned int> getExperienciaProximoNivel() const;

    // Muestra toda la informacion del Pokemon en consola
    void mostrar() const;
    
    // Serializa/deserializa la informacion
    void serealizar(ofstream& out) const;
    void deserealizar(ifstream& in);
};

