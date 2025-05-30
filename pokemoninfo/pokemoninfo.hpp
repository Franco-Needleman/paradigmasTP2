#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class pokemoninfo {
private:
    string type;
    string descripcion;
    map<string,unsigned int> ataquesDisponiblesPorNivel;
    vector<unsigned int> experienciaProximoNivel;
public:
    pokemoninfo(string type, string descripcion, map<string,unsigned int> ataquesDisponiblesPorNivel, vector<unsigned int> experienciaProximoNivel);

    string getType() const;

    string getDescripcion() const;

    map<string, unsigned int> getAtaquesDisponiblesPorNivel() const;
    vector<unsigned int> getExperienciaProximoNivel() const;

    unsigned int getsiguientenivel() const ;

};

