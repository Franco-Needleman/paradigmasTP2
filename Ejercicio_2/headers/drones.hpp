#include <iostream>
#include <mutex>
#pragma once
using namespace std;

// Clase que simula el control de drones usando mutexs para sincronizacion
class Drones {
private:
    mutex drones[5];    // Mutexs para controlar acceso a cada dron
    mutex areas[5];     // Mutexs para controlar acceso a cada area
    mutex terminal;     // Mutex para controlar acceso a la terminal
public:
    Drones() = default;
    ~Drones() = default;
    
    // Hace despegar un dron especifico (adquiere mutex del dron)
    void despegar(int dron);
    
    // Verifica si quedan drones por despegar
    bool falta_despegar();
    
    // Simula los vuelos de todos los drones con sincronizacion
    void simularVuelos();
};