#include <thread>
#include <string>
#include <iostream>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

struct Tarea {
    int idSensor;
    int idTarea;
    string descripcionTarea;
};

int numeroTareas = 1; 
mutex  mutexTareas;
mutex terminal;
queue<Tarea> colaTareas;
mutex mutexCola;
condition_variable cvCola;

bool sensoresFinalizados = false;

void sensor(int idSensor, int cantidadTareas) {
    for (int i = 0; i < cantidadTareas; ++i) {
        // Simular tiempo de creación de la tarea
        this_thread::sleep_for(chrono::milliseconds(175));
        // Crear la tarea
        Tarea tarea;
        tarea.idSensor = idSensor;
        mutexTareas.lock();
        tarea.idTarea = numeroTareas ;
        numeroTareas++;
        mutexTareas.unlock();
        tarea.descripcionTarea = "Tarea con descripcion general generada por sensor " + to_string(idSensor) + ", número " + to_string(i + 1);
        // Agregar la tarea a la cola compartida
        lock_guard<mutex> lock(mutexCola);
        colaTareas.push(tarea);
        terminal.lock();
        cout << "[Sensor " << idSensor << "] Generó tarea " << tarea.idTarea << endl;
        terminal.unlock();
        // Notificar a los robots que hay una nueva tarea
        cvCola.notify_all();
    }
}

void robot(int idRobot) {
    while (true) {
        unique_lock<mutex> lock(mutexCola);

        // Esperar hasta que haya tareas o los sensores hayan terminado
        cvCola.wait(lock, [] { return !colaTareas.empty() || sensoresFinalizados; });

        // Si la cola está vacía y los sensores terminaron, salir
        if (colaTareas.empty() && sensoresFinalizados) {
            break;
        }

        // Si hay tareas, procesar la primera
        if (!colaTareas.empty()) {
            Tarea tarea = colaTareas.front();
            colaTareas.pop();
            terminal.lock();
            // Imprimir mensaje de procesamiento (dentro del lock para evitar superposición)
            cout << "[Robot " << idRobot << "] Procesando tarea " << tarea.idTarea
                 << " del sensor " << tarea.idSensor << ": " << tarea.descripcionTarea << endl;
            terminal.unlock();

            // Liberar el lock antes de procesar (para que otros robots puedan acceder a la cola)
            lock.unlock();

            // Simular procesamiento
            this_thread::sleep_for(chrono::milliseconds(250));
        }
    }
    // Mensaje de finalización (opcional, también protegido por el lock)
    terminal.lock();
    cout << "[Robot " << idRobot << "] Finalizó su trabajo" << endl;
    terminal.unlock();
}

int main() {
    const int cantidadSensores = 3;
    const int cantidadRobots = 3;
    const int tareasPorSensor = 5; // Puedes ajustar la cantidad de tareas por sensor

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
    //lock_guard<mutex> lock(mutexCola);
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
