#include "../headers/drones.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <random>


void Drones::despegar(int drone){
    if (drones[drone].try_lock()){
        terminal.lock();
        cout << "Dron" << drone << "esperando para despegar..." << endl;
        terminal.unlock();

        lock(areas[drone], areas[(drone+1)%5]);

        terminal.lock();
        cout << "Dron" << drone << "despegando..." << endl;
        terminal.unlock();

        this_thread::sleep_for(chrono::seconds(5));

        
        terminal.lock();
        cout << "Dron" << drone << "alcanzó altura de 10m" << endl;
        terminal.unlock();
        areas[drone].unlock();
        areas[(drone+1)%5].unlock();
    }
}

void Drones::simularVuelos(){
    Drones drones;
    srand(12332);
    for(int i;i<=5;i++){
        thread thread(&Drones::despegar, this, randint()%5)

    }

}