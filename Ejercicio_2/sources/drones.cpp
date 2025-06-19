#include "../headers/drones.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>

// Simula el despegue de un dron especifico con sincronizacion de areas
void Drones::despegar(int dron){
    terminal.lock();
    cout << "Dron " << dron << " esperando para despegar..." << endl;
    terminal.unlock();
    //doble lock para evitar deadlock
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
    
    
    // no hace falta un random porque los threads se ejecutan en paralelo y no hay orden garantizado
    for(int i=0;i<5;i++){
        vuelos.push_back(jthread(&Drones::despegar, this, i)); 
    }
    
}