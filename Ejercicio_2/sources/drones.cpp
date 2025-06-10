#include "../headers/drones.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>


void Drones::despegar(int drone){
    
        terminal.lock();
        cout << "Dron " << drone << " esperando para despegar..." << endl;
        terminal.unlock();

        lock(areas[drone], areas[(drone+1)%5]);

        terminal.lock();
        cout << "Dron " << drone << " despegando..." << endl;
        terminal.unlock();

        this_thread::sleep_for(chrono::seconds(5));

        
        terminal.lock();
        cout << "Dron " << drone << " alcanzó altura de 10m" << endl;
        terminal.unlock();
        areas[drone].unlock();
        areas[(drone+1)%5].unlock();
        
    
    
}



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
        cout<<i<<endl;
    }
    
}