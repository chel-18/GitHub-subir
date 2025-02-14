#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cctype>

std::string generarContrasena(int longitud) {
    // Definimos los conjuntos de caracteres posibles
    const std::string mayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string minusculas = "abcdefghijklmnopqrstuvwxyz";
    const std::string numeros = "0123456789";
    const std::string simbolos = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    // Combinamos todos los conjuntos
    const std::string todosCaracteres = mayusculas + minusculas + numeros + simbolos;

    // Inicializamos un generador de números aleatorios
    std::random_device rd;
    std::mt19937 generador(rd());
    std::uniform_int_distribution<> distribucion(0, todosCaracteres.size() - 1);

    std::string contrasena;
    bool tieneMayuscula = false;
    bool tieneMinuscula = false;
    bool tieneNumero = false;
    bool tieneSimbolo = false;

    // Generamos la contraseña
    while (contrasena.length() < longitud) {
        char caracter = todosCaracteres[distribucion(generador)];

        // Verificamos que no haya secuencias repetidas de más de dos caracteres
        if (contrasena.length() >= 2 && 
            caracter == contrasena[contrasena.length() - 1] && 
            caracter == contrasena[contrasena.length() - 2]) {
            continue; // Saltamos este caracter para evitar repeticiones
        }

        // Añadimos el caracter a la contraseña
        contrasena += caracter;

        // Actualizamos los flags según el tipo de caracter
        if (mayusculas.find(caracter) != std::string::npos) {
            tieneMayuscula = true;
        } else if (minusculas.find(caracter) != std::string::npos) {
            tieneMinuscula = true;
        } else if (numeros.find(caracter) != std::string::npos) {
            tieneNumero = true;
        } else if (simbolos.find(caracter) != std::string::npos) {
            tieneSimbolo = true;
        }
    }

    // Verificamos que la contraseña cumpla con todos los requisitos
    if (!tieneMayuscula || !tieneMinuscula || !tieneNumero || !tieneSimbolo) {
        // Si no cumple, regeneramos la contraseña
        return generarContrasena(longitud);
    }

    return contrasena;
}

int main() {
    int longitud;
    std::cout << "Ingrese la longitud de la contraseña: ";
    std::cin >> longitud;

    std::string contrasena = generarContrasena(longitud);
    std::cout << "Contraseña generada: " << contrasena << std::endl;

    return 0;
}