#ifndef PROLOGUEMAP_H
#define PROLOGUEMAP_H

#include <iostream>
#include <conio.h>
#include <string>
#include <cctype>
using namespace std;

// Prologo (igual que antes)
#ifndef PROLOGO_H
#define PROLOGO_H

class Prologo {
public:
    static const int MAX_LINEAS = 10;

    void introduccionNarrativa(int& lineCount, string texto[MAX_LINEAS]) {
        lineCount = 7;
        texto[0] = "...";
        texto[1] = "¿Dónde estoy?";
        texto[2] = "El aire huele a humedad. Todo está en silencio.";
        texto[3] = "Tu cabeza duele... pero no recuerdas por qué.";
        texto[4] = "Solo sabes una cosa...";
        texto[5] = "Debes seguir adelante.";
        texto[6] = "=== Comienza tu aventura ===";
    }

    void escenaAmuleto(int& lineCount, string texto[MAX_LINEAS]) {
        lineCount = 7;
        texto[0] = "*Te agachas entre los arbustos...*";
        texto[1] = "Algo brilla bajo las hojas.";
        texto[2] = "";
        texto[3] = "Has encontrado un objeto antiguo... un amuleto cubierto de vendas oscuras.";
        texto[4] = "Apenas lo tomas, el viento se detiene...";
        texto[5] = "Y un escalofrío recorre tu espalda.";
        texto[6] = "¡Algo se acerca!";
    }

    void escenaSlime(int& lineCount, string texto[MAX_LINEAS]) {
        lineCount = 4;
        texto[0] = "Un Slime Oscuro emerge de la maleza...";
        texto[1] = "Sus ojos brillan con malicia.";
        texto[2] = "¡Prepárate para el combate!";
        texto[3] = "";
    }
};

#endif // PROLOGO_H

const int FILAS = 30;
const int COLUMNAS = 50;

class Mapa {
private:
    char mapa[FILAS][COLUMNAS];
    int jugadorX, jugadorY;
    string panelTexto;

    Prologo prologo;
    int prologoLineCount = 0;
    string prologoTexto[Prologo::MAX_LINEAS];
    int prologoIndex = 0;
    bool mostrandoPrologo = true;

    bool enNarracionAmuleto = false;
    bool enNarracionSlime = false;
    int narracionIndex = 0;
    int narracionLineCount = 0;
    string narracionTexto[Prologo::MAX_LINEAS];

    bool esAdyacente(char simbolo) const {
        return (mapa[jugadorX - 1][jugadorY] == simbolo ||
                mapa[jugadorX + 1][jugadorY] == simbolo ||
                mapa[jugadorX][jugadorY - 1] == simbolo ||
                mapa[jugadorX][jugadorY + 1] == simbolo);
    }

    void iniciarNarracionAmuleto() {
        prologo.escenaAmuleto(narracionLineCount, narracionTexto);
        narracionIndex = 0;
        enNarracionAmuleto = true;
        panelTexto = narracionTexto[narracionIndex];
    }

    void iniciarNarracionSlime() {
        prologo.escenaSlime(narracionLineCount, narracionTexto);
        narracionIndex = 0;
        enNarracionSlime = true;
        panelTexto = narracionTexto[narracionIndex];
    }

    void combate() {
        system("cls");
        cout << "=== PANTALLA DE COMBATE ===\n";
        cout << "Combate iniciado contra Slime Oscuro!\n";
        cout << "Aquí iría la lógica del combate...\n";
        cout << "Presiona cualquier tecla para continuar...\n";
        _getch();
        // Al finalizar combate, puedes reiniciar el juego o regresar al mapa
        system("cls");
        panelTexto = "Has derrotado al Slime Oscuro. Explora el mapa.";
    }

public:
    Mapa();
    void mostrarMapa() const;
    void moverJugador(char direccion);
    void interactuar();
    void jugar();
    void mostrarPrologo();
    void avanzarNarracion();
};

Mapa::Mapa() {
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            mapa[i][j] = ' ';

    for (int i = 0; i < FILAS; i++) {
        mapa[i][0] = '|';
        mapa[i][COLUMNAS - 1] = '|';
    }

    for (int j = 0; j < COLUMNAS; j++) {
        mapa[0][j] = '-';
        mapa[FILAS - 4][j] = '-';
        mapa[FILAS - 1][j] = '-';
    }

    // Casas, árboles, arbustos, agua
    mapa[4][2] = '/'; mapa[3][3] = '_'; mapa[3][4] = '_'; mapa[3][5] = '_'; mapa[3][6] = '_'; mapa[3][7] = '_'; mapa[3][8] = '_'; mapa[4][9] = '\\';
    mapa[5][2] = '|'; mapa[5][3] = '#'; mapa[5][4] = ' '; mapa[5][5] = '_'; mapa[5][6] = ' '; mapa[5][7] = ' '; mapa[5][8] = ' '; mapa[5][9] = '|';
    mapa[6][2] = '|'; mapa[6][3] = '_'; mapa[6][4] = '|'; mapa[6][5] = ' '; mapa[6][6] = '|'; mapa[6][7] = '_'; mapa[6][8] = '_'; mapa[6][9] = '|';

    mapa[10][10] = '^'; mapa[10][11] = '^'; mapa[11][10] = '^'; mapa[11][11] = '^';

    mapa[20][25] = '('; mapa[20][26] = ')';

    mapa[7][35] = '~'; mapa[7][36] = '~'; mapa[8][35] = '~'; mapa[8][36] = '~';

    jugadorX = 9;
    jugadorY = 9;
    mapa[jugadorX][jugadorY] = 'O';

    prologo.introduccionNarrativa(prologoLineCount, prologoTexto);
    prologoIndex = 0;
    mostrandoPrologo = true;
    panelTexto = prologoTexto[prologoIndex];
}

void Mapa::mostrarMapa() const {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (i == FILAS - 3 && j == 2) {
                string lineaTexto = "=== ACTION PANEL ===";
                cout << lineaTexto;
                int espacios = COLUMNAS - 2 - (int)lineaTexto.length();
                for (int k = 0; k < espacios; ++k) cout << ' ';
                break;
            }
            else if (i == FILAS - 2 && j == 2) {
                cout << panelTexto;
                int espacios = COLUMNAS - 2 - (int)panelTexto.length();
                for (int k = 0; k < espacios; ++k) cout << ' ';
                break;
            }
            cout << mapa[i][j] << ' ';
        }
        cout << endl;
    }
}

void Mapa::moverJugador(char direccion) {
    if (mostrandoPrologo || enNarracionAmuleto || enNarracionSlime) return; // No mover en narración

    int nuevaX = jugadorX;
    int nuevaY = jugadorY;

    switch (direccion) {
        case 'w': nuevaX--; break;
        case 's': nuevaX++; break;
        case 'a': nuevaY--; break;
        case 'd': nuevaY++; break;
        default: return;
    }

    if (nuevaX >= 1 && nuevaX < FILAS - 4 && nuevaY >= 1 && nuevaY < COLUMNAS - 1) {
        char destino = mapa[nuevaX][nuevaY];
        if (destino == ' ' || destino == '.') {
            mapa[jugadorX][jugadorY] = ' ';
            jugadorX = nuevaX;
            jugadorY = nuevaY;
            mapa[jugadorX][jugadorY] = 'O';
        }
    }
}

void Mapa::interactuar() {
    if (mostrandoPrologo) {
        mostrarPrologo();
        return;
    }

    if (enNarracionAmuleto || enNarracionSlime) {
        avanzarNarracion();
        return;
    }

    if (esAdyacente('|') || esAdyacente('/') || esAdyacente('\\')) {
        panelTexto = "You see a house. It's locked.";
    } else if (esAdyacente('(') || esAdyacente(')')) {
        // Inicia narración de amuleto
        iniciarNarracionAmuleto();
    } else if (esAdyacente('^')) {
        panelTexto = "You see a tree.";
    } else if (esAdyacente('~')) {
        panelTexto = "You hear the river flowing nearby.";
    } else {
        panelTexto = "Nothing interesting nearby.";
    }
}

void Mapa::mostrarPrologo() {
    if (!mostrandoPrologo) return;

    prologoIndex++;
    if (prologoIndex >= prologoLineCount) {
        mostrandoPrologo = false;
        panelTexto = "Use W/A/S/D to move, E to interact, Q to quit.";
    } else {
        panelTexto = prologoTexto[prologoIndex];
    }
}

void Mapa::avanzarNarracion() {
    narracionIndex++;
    if (narracionIndex >= narracionLineCount) {
        if (enNarracionAmuleto) {
            enNarracionAmuleto = false;
            // Inicia narración slime
            iniciarNarracionSlime();
        } else if (enNarracionSlime) {
            enNarracionSlime = false;
            combate();  // Cambia a pantalla de combate
        }
    } else {
        panelTexto = narracionTexto[narracionIndex];
    }
}

void Mapa::jugar() {
    char opcion;
    while (true) {
        cout << "\033[H"; // limpia pantalla
        mostrarMapa();

        if (mostrandoPrologo) {
            cout << "\n[Prologue] Presiona cualquier tecla para continuar...\n";
            _getch();
            mostrarPrologo();
            continue;
        }

        if (enNarracionAmuleto || enNarracionSlime) {
            cout << "\n[Narración] Presiona cualquier tecla para continuar...\n";
            _getch();
            avanzarNarracion();
            continue;
        }

        cout << "\nMove: W/A/S/D | Interact: E | Quit: Q\n";
        cout << "Option: ";
        opcion = tolower(_getch());

        if (opcion == 'q') break;
        else if (opcion == 'e') interactuar();
        else moverJugador(opcion);
    }
}

#endif // PROLOGUEMAP_H
