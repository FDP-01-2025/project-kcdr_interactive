#ifndef PROLOGO_H
#define PROLOGO_H

#include <string>

class Prologo {
public:
    static const int MAX_LINEAS = 10;

    void introduccionNarrativa(int& lineCount, std::string texto[MAX_LINEAS]) {
        lineCount = 7;
        texto[0] = "...";
        texto[1] = "¿Dónde estoy?";
        texto[2] = "El aire huele a humedad. Todo está en silencio.";
        texto[3] = "Tu cabeza duele... pero no recuerdas por qué.";
        texto[4] = "Solo sabes una cosa...";
        texto[5] = "Debes seguir adelante.";
        texto[6] = "=== Comienza tu aventura ===";
    }

    void escenaAmuleto(int& lineCount, std::string texto[MAX_LINEAS]) {
        lineCount = 7;
        texto[0] = "*Te agachas entre los arbustos...*";
        texto[1] = "Algo brilla bajo las hojas.";
        texto[2] = "";
        texto[3] = "Has encontrado un objeto antiguo... un amuleto cubierto de vendas oscuras.";
        texto[4] = "Apenas lo tomas, el viento se detiene...";
        texto[5] = "Y un escalofrío recorre tu espalda.";
        texto[6] = "¡Algo se acerca!";
    }

    void escenaSlime(int& lineCount, std::string texto[MAX_LINEAS]) {
        lineCount = 4;
        texto[0] = "Un Slime Oscuro emerge de la maleza...";
        texto[1] = "Sus ojos brillan con malicia.";
        texto[2] = "¡Prepárate para el combate!";
        texto[3] = "";
    }
};

#endif // PROLOGO_H
