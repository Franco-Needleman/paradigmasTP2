#include "headers/pokemon.hpp"
#include "headers/pokemoninfo.hpp"
#include "headers/pokedex.hpp"
#include <iostream>
#include <fstream>

int main(){
    pokemon Squirtle("Squirtle",100);
    pokemoninfo SquirtleInfo(
        "Agua",
        "Una tortuga pequeña que lanza chorros de agua.",
        {{"Pistola Agua",4}, {"Hidrobomba",6}, {"Danza Lluvia",5}},
        {0, 400, 1000}
    );

    pokemon Bulbasaur("Bulbasaur",270);
    pokemoninfo BulbasaurInfo(
        "Planta",
        "Tiene una semilla en su lomo que crece con el tiempo",
        {{"Latigazo",4}, {"Hoja Afilada",6}, {"Rayo Solar",5}},
        {0, 300, 1100}
    );

    pokemon Charmander("Charmander",633);
    pokemoninfo CharmanderInfo(
        "Fuego",
        "Una lagartija con una llama en su cola",
        {{"Ascuas",4}, {"Lanzallamas",6}, {"Giro Fuego",5}},
        {0, 250, 1300}
    );

    Pokedex pokedex;
    pokedex.agregar(Squirtle, SquirtleInfo);
    pokedex.agregar(Bulbasaur, BulbasaurInfo);
    pokedex.agregar(Charmander, CharmanderInfo);

    // Guardar la Pokedex en el archivo
    ofstream out("data/pokedex.dat", ios::binary);
    if (out.is_open()) {
        pokedex.serealizar(out);
        out.close();
        cout << "Pokedex guardada exitosamente en 'data/pokedex.dat'" << endl;
    } else {
        cerr << "Error al abrir el archivo para guardar la Pokedex." << endl;
    }

    cout << "Mostrando todos los Pokemon en la Pokedex:" << endl;
    pokedex.mostrarTodos();
    cout << endl;
    pokemon Pikachu("Pikachu", 500);

    cout << "Mostrando un Pokemon conocido:" << endl;
    pokedex.mostrar(pokemon("Squirtle",870));

    cout << "Mostrando un Pokemon desconocido:" << endl;
    pokedex.mostrar(Pikachu);

    ifstream in("../data/pokedex.dat", ios::binary);
    if (in.is_open()) {
        Pokedex loadedPokedex(in);
        in.close();
        cout << "Pokedex cargada desde 'pokedex.dat':" << endl;
        loadedPokedex.mostrarTodos();
    } else {
        cerr << "Error al abrir el archivo para cargar la Pokedex." << endl;
    }

    return 0;
}