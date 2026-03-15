#include <iostream>
#include <string>

class CerraduraInteligente {
private:
    std::string claveMaestra = "1994"; // Referencia al año de los Power Rangers
    int intentosFallidos = 0;
    const int MAX_INTENTOS = 3;

public:
    bool intentarAcceso(std::string clave) {
        if (intentosFallidos >= MAX_INTENTOS) {
            std::cout << "!!! SISTEMA BLOQUEADO POR SEGURIDAD !!!" << std::endl;
            return false;
        }

        if (clave == claveMaestra) {
            std::cout << "Acceso Concedido. Bienvenido al Centro de Mando." << std::endl;
            intentosFallidos = 0;
            return true;
        } else {
            intentosFallidos++;
            std::cout << "Clave incorrecta. Intentos restantes: " << (MAX_INTENTOS - intentosFallidos) << std::endl;
            return false;
        }
    }
};

int main() {
    CerraduraInteligente puertaPrincipal;
    
    // Simulación de entrada de usuario
    puertaPrincipal.intentarAcceso("1234");
    puertaPrincipal.intentarAcceso("1994");
    
    return 0;
}
