#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

// Estados del sistema
enum EstadoHabitacion {
    DESOCUPADA,
    OCUPADA_CON_LUZ,
    OCUPADA_SIN_LUZ // Ahorro de energía
};

class SistemaDomotico {
private:
    EstadoHabitacion estadoActual;
    int umbralLuz; // Valor por debajo del cual se encienden las luces

public:
    SistemaDomotico(int umbral) : umbralLuz(umbral), estadoActual(DESOCUPADA) {}

    void actualizar(bool movimiento, int lecturaLDR) {
        EstadoHabitacion siguienteEstado = estadoActual;

        // Lógica de la Máquina de Estados
        switch (estadoActual) {
            case DESOCUPADA:
                if (movimiento) {
                    if (lecturaLDR < umbralLuz) {
                        siguienteEstado = OCUPADA_CON_LUZ;
                        std::cout << "[PIR] Movimiento detectado. [LDR] Luz baja (" << lecturaLDR << ").\n";
                    } else {
                        siguienteEstado = OCUPADA_SIN_LUZ;
                        std::cout << "[PIR] Movimiento detectado. [LDR] Luz suficiente (" << lecturaLDR << ").\n";
                    }
                }
                break;

            case OCUPADA_CON_LUZ:
                if (!movimiento) {
                    siguienteEstado = DESOCUPADA;
                    std::cout << "[PIR] No hay movimiento.\n";
                } else if (lecturaLDR >= umbralLuz) {
                    siguienteEstado = OCUPADA_SIN_LUZ;
                    std::cout << "[LDR] Luz ambiental subió (" << lecturaLDR << ").\n";
                }
                break;

            case OCUPADA_SIN_LUZ:
                if (!movimiento) {
                    siguienteEstado = DESOCUPADA;
                    std::cout << "[PIR] No hay movimiento.\n";
                } else if (lecturaLDR < umbralLuz) {
                    siguienteEstado = OCUPADA_CON_LUZ;
                    std::cout << "[LDR] Luz ambiental bajó (" << lecturaLDR << ").\n";
                }
                break;
        }

        // Acciones al cambiar de estado (Control de Actuadores)
        if (siguienteEstado != estadoActual) {
            estadoActual = siguienteEstado;
            ejecutarAccion();
        }
    }

    void ejecutarAccion() {
        std::cout << ">>> [ACCIÓN] ";
        switch (estadoActual) {
            case DESOCUPADA:
                std::cout << "Apagando TODAS las luces y dispositivos.\n";
                break;
            case OCUPADA_CON_LUZ:
                std::cout << "Encendiendo luces principales.\n";
                break;
            case OCUPADA_SIN_LUZ:
                std::cout << "Manteniendo luces apagadas (Ahorro Energético).\n";
                break;
        }
        std::cout << "-------------------------------------------\n";
    }
};

int main() {
    // Configuración: Umbral de luz de 400 (0-1024)
    SistemaDomotico habitacionPrincipal(400);

    // Simulación de una secuencia de eventos (Lecturas de sensores)
    // Estructura: {Movimiento (bool), LecturaLDR (int)}
    struct Lectura { bool mov; int ldr; };
    std::vector<Lectura> secuencia = {
        {false, 800}, // Noche, habitación sola
        {true, 200},  // Alguien entra, está oscuro -> Enciende luz
        {true, 300},  // Sigue ahí, sigue oscuro
        {true, 600},  // Amanece, luz ambiental sube -> Apaga luz (ahorro)
        {false, 700}  // La persona sale -> Todo apagado
    };

    std::cout << "--- Iniciando Simulación White Tiger Core ---\n\n";

    for (const auto& l : secuencia) {
        habitacionPrincipal.actualizar(l.mov, l.ldr);
        // Simular tiempo entre lecturas
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
