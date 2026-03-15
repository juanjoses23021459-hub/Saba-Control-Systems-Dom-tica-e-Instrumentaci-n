#include <iostream>
#include <fstream>
#include <iomanip>

struct DatosSensor {
    float temperatura;
    int humedad;
    long timestamp;
};

void guardarParaAnalisis(DatosSensor d) {
    std::ofstream archivo;
    archivo.open("results/log_sensores.csv", std::ios::app); // Carpeta results/
    
    if (archivo.is_open()) {
        // Formato CSV: tiempo, temp, hum
        archivo << d.timestamp << "," << d.temperatura << "," << d.humedad << "\n";
        archivo.close();
    }
}

int main() {
    std::cout << "Iniciando registro en carpeta results/..." << std::endl;
    
    // Simulando captura de datos
    DatosSensor lectura1 = {24.5, 60, 1710456000};
    DatosSensor lectura2 = {25.2, 58, 1710456060};
    
    guardarParaAnalisis(lectura1);
    guardarParaAnalisis(lectura2);
    
    std::cout << "Datos exportados correctamente para MATLAB." << std::endl;
    return 0;
}
