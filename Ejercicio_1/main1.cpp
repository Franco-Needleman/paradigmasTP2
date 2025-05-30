#include "headers/pokemon.hpp"
#include "headers/pokemoninfo.hpp"
#include "headers/pokedex.hpp"

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

    cout << "Mostrando todos los Pokemon en la Pokedex:" << endl;
    pokedex.mostrarTodos();
    cout << endl;
    pokemon Pikachu("Pikachu", 500);

    cout << "Mostrando un Pokemon desconocido:" << endl;
    pokedex.mostrar(Pikachu);

    return 0;
}