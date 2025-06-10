#include <iostream>
#include <mutex>
#pragma once
using namespace std;


class Drones {
private:
    mutex drones[5];
    mutex areas[5];
    mutex terminal;
public:
    Drones() = default;
    ~Drones() = default;
    void despegar(int drone);
    void simularVuelos();
};