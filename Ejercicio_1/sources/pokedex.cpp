#include "../headers/pokedex.hpp"
#include <iostream>
#include <fstream>

Pokedex::Pokedex() : nombre_archivo("pokedex.dat") {}

size_t PokemonHash::operator()(const pokemon& p) const {
    return hash<string>()(p.getNombre() );//+ to_string(p.getExperienciaActual()));
}

void Pokedex::agregar(const pokemon& p, const pokemoninfo& info) {
    pokedex[p] = info;
    ofstream out(nombre_archivo, ios::binary | ios::trunc);
    if (out.is_open()){
        this->serealizar(out);
        out.close();
    }
}

void Pokedex::imprimir_exp(const pokemon& p, const pokemoninfo& pinf) const { // para poder reutilizarla
    vector<unsigned int> experienciaProximoNivel = pinf.getExperienciaProximoNivel();
    unsigned int exp =p.getExperienciaActual();
    for (int i=0; i < 3; ++i) {
        if (exp<experienciaProximoNivel[i]){
            cout << "nivel actual: " << i << endl;
            cout <<"Experiencia necesaria para nivel "<< i+1 << ": " << experienciaProximoNivel[i]-exp<<endl;
            break;
        }
        if (exp>experienciaProximoNivel[2]){
            cout << "nivel maximo (3)"<<endl;
            break;
        }
    }
}

void Pokedex::mostrar(const pokemon& p) const {
    auto it = pokedex.find(p);
    if (it != pokedex.end() && p.getNombre() == it->first.getNombre()) {
        cout << "Pokemon: " << p.getNombre() << endl;
        cout << "Experiencia Actual: " << p.getExperienciaActual() << endl;
        it->second.mostrar();
        imprimir_exp(p,it->second);
    } else {
        cout << "¡Pokemon desconocido!" << endl;
    }
} 

void Pokedex::mostrarTodos() const {
    for (const auto& entry : pokedex) {
        cout << "Pokemon: " << entry.first.getNombre() << endl;//no se reutiliza la funcion mostrar pq esta itera devuelta en el map y es menos eficiente
        cout << "Experiencia Actual: " << entry.first.getExperienciaActual() << endl;
        entry.second.mostrar();
        imprimir_exp(entry.first,entry.second);
        cout << "------------------------" << endl;
    }
}

void Pokedex::serealizar(ofstream& out) const {
    size_t size = pokedex.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& entry : pokedex) {
        entry.first.serealizar(out);
        entry.second.serealizar(out);
    }
}
void Pokedex::deserealizar(ifstream& in) {
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        pokemon p;
        pokemoninfo info;
        p.deserealizar(in);
        info.deserealizar(in);
        pokedex[p] = info;
    }
}

Pokedex::Pokedex(ifstream& in) : nombre_archivo("pokedex.dat") { 
    deserealizar(in);
}