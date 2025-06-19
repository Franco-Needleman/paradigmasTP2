#include "../headers/drones.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

// Simula el despegue de un dron especifico con sincronizacion de areas
void Drones::despegar(int dron){
    terminal.lock();
    cout << "Dron " << dron << " esperando para despegar..." << endl;
    terminal.unlock();

    lock(areas[dron], areas[(dron+1)%5]);

    terminal.lock();
    cout << "Dron " << dron << " despegando..." << endl;
    terminal.unlock();

    this_thread::sleep_for(chrono::seconds(5));

    terminal.lock();
    cout << "Dron " << dron << " alcanzo altura de 10m" << endl;
    terminal.unlock();
    areas[dron].unlock();
    areas[(dron+1)%5].unlock();
}

// Simula vuelos de todos los drones en orden aleatorio usando threads
void Drones::simularVuelos(){
    vector<jthread> vuelos;
    vector<int> despegaron;
    

    srand(time(NULL));
    for(int i=0;i<5;i++){
        int despegando = rand()%5;
        while( find(despegaron.begin(), despegaron.end(), despegando) != despegaron.end()){
            despegando = rand()%5;
        }
        vuelos.push_back(jthread(&Drones::despegar, this, despegando)); 
        despegaron.push_back(despegando);
    }
    
}