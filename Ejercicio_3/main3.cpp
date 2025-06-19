#include <thread>
#include <string>
#include <iostream>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

// Estructura que representa una tarea generada por un sensor
struct Tarea {
    int idSensor;
    int idTarea;
    string descripcionTarea;
};

// Variables globales para sincronizacion
int numeroTareas = 1; 
mutex  mutexTareas;        // Protege el contador de tareas
mutex terminal;            // Protege la salida a consola
queue<Tarea> colaTareas;   // Cola compartida de tareas
mutex mutexCola;           // Protege la cola de tareas
condition_variable cvCola; // Para notificar cuando hay nuevas tareas

bool sensoresFinalizados = false; // Flag para indicar que los sensores terminaron

// Funcion que simula un sensor generando tareas
void sensor(int idSensor, int cantidadTareas) {
    for (int i = 0; i < cantidadTareas; ++i) {
        // Simular tiempo de creacion de la tarea
        this_thread::sleep_for(chrono::milliseconds(175));
        // Crear la tarea
        Tarea tarea;
        tarea.idSensor = idSensor;
        mutexTareas.lock();
        tarea.idTarea = numeroTareas ;
        numeroTareas++;
        mutexTareas.unlock();
        tarea.descripcionTarea = "Tarea con descripcion general generada por sensor " + to_string(idSensor) + ", numero " + to_string(i + 1);
        // Agregar la tarea a la cola compartida
        lock_guard<mutex> lock(mutexCola);
        colaTareas.push(tarea);
        terminal.lock();
        cout << "[Sensor " << idSensor << "] Genero tarea " << tarea.idTarea << endl;
        terminal.unlock();
        // Notificar a los robots que hay una nueva tarea
        cvCola.notify_all();
    }
}

// Funcion que simula un robot procesando tareas
void robot(int idRobot) {
    while (true) {
        unique_lock<mutex> lock(mutexCola);

        // Esperar hasta que haya tareas o los sensores hayan terminado
        cvCola.wait(lock, [] { return !colaTareas.empty() || sensoresFinalizados; });

        // Si la cola esta vacia y los sensores terminaron, salir
        if (colaTareas.empty() && sensoresFinalizados) {
            break;
        }

        // Si hay tareas, procesar la primera
        if (!colaTareas.empty()) {
            Tarea tarea = colaTareas.front();
            colaTareas.pop();
            terminal.lock();
            // Imprimir mensaje de procesamiento (dentro del lock para evitar superposicion)
            cout << "[Robot " << idRobot << "] Procesando tarea " << tarea.idTarea
                 << " del sensor " << tarea.idSensor << ": " << tarea.descripcionTarea << endl;
            terminal.unlock();

            // Liberar el lock antes de procesar (para que otros robots puedan acceder a la cola)
            lock.unlock();

            // Simular procesamiento
            this_thread::sleep_for(chrono::milliseconds(250));
        }
    }
    // Mensaje de finalizacion
    terminal.lock();
    cout << "[Robot " << idRobot << "] Finalizo su trabajo" << endl;
    terminal.unlock();
}

int main() {
    const int cantidadSensores = 3;
    const int cantidadRobots = 3;
    const int tareasPorSensor = 5;

    // Crear y lanzar los threads de sensores
    thread sensores[cantidadSensores];
    for (int i = 0; i < cantidadSensores; ++i) {
        sensores[i] = thread(sensor, i + 1, tareasPorSensor);
    }

    // Crear y lanzar los threads de robots
    thread robots[cantidadRobots];
    for (int i = 0; i < cantidadRobots; ++i) {
        robots[i] = thread(robot, i + 1);
    }

    // Esperar a que terminen los sensores
    for (int i = 0; i < cantidadSensores; ++i) {
        sensores[i].join();
    }

    // Avisar a los robots que los sensores han finalizado
    sensoresFinalizados = true;
    cvCola.notify_all();

    // Esperar a que terminen los robots
    for (int i = 0; i < cantidadRobots; ++i) {
        robots[i].join();
    }

    terminal.lock();
    cout << "Todos los sensores y robots han finalizado." << endl;
    terminal.unlock();
    return 0;
}
