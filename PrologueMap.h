#ifndef PROLOGUEMAP_H 
#define PROLOGUEMAP_H

#include <iostream>   // Biblioteca estándar para entrada/salida
#include <conio.h>    // Biblioteca para _getch(), entrada de teclado sin esperar enter
#include <string>     // Biblioteca para manejar strings
#include <cctype>     // Biblioteca para funciones de caracteres (tolower, etc)
using namespace std;  // Uso del espacio de nombres estándar para evitar std::

/*
    Definición del módulo Prologo (Narrativa inicial) 
    Para evitar redefiniciones múltiples del mismo módulo
*/
#ifndef PROLOGO_H
#define PROLOGO_H

/*
    Clase Prologo:
    Contiene textos narrativos para la introducción y escenas específicas.
    Tiene funciones que llenan arrays de texto y cuentan líneas para mostrarlas.
*/
class Prologo {
public:
    static const int MAX_LINEAS = 10;  // Máximo número de líneas por escena

    // Método que llena el texto de la introducción narrativa inicial del juego
    void introduccionNarrativa(int& lineCount, string texto[MAX_LINEAS]) {
        lineCount = 7;  // Se indican 7 líneas de texto para mostrar
        texto[0] = "...";
        texto[1] = "¿Dónde estoy?";
        texto[2] = "El aire huele a humedad. Todo está en silencio.";
        texto[3] = "Tu cabeza duele... pero no recuerdas por qué.";
        texto[4] = "Solo sabes una cosa...";
        texto[5] = "Debes seguir adelante.";
        texto[6] = "=== Comienza tu aventura ===";
    }

    // Método que llena el texto de la escena donde el jugador encuentra un amuleto
    void escenaAmuleto(int& lineCount, string texto[MAX_LINEAS]) {
        lineCount = 7; // 7 líneas para esta escena
        texto[0] = "*Te agachas entre los arbustos...*";
        texto[1] = "Algo brilla bajo las hojas.";
        texto[2] = "";
        texto[3] = "Has encontrado un objeto antiguo... un amuleto cubierto de vendas oscuras.";
        texto[4] = "Apenas lo tomas, el viento se detiene...";
        texto[5] = "Y un escalofrío recorre tu espalda.";
        texto[6] = "¡Algo se acerca!";
    }

    // Método que llena el texto de la escena de aparición de un Slime enemigo
    void escenaSlime(int& lineCount, string texto[MAX_LINEAS]) {
        lineCount = 4; // 4 líneas para esta escena
        texto[0] = "Un Slime Oscuro emerge de la maleza...";
        texto[1] = "Sus ojos brillan con malicia.";
        texto[2] = "¡Prepárate para el combate!";
        texto[3] = "";
    }
};

#endif // PROLOGO_H

// Definición del tamaño del mapa en filas y columnas
const int FILAS = 30;
const int COLUMNAS = 50;

/*
    Clase Mapa:
    Representa el mapa del juego, la posición del jugador, panel de texto, y controla
    la interacción, movimiento y la narrativa dentro del mapa.
*/
class Mapa {
private:
    char mapa[FILAS][COLUMNAS];  // Matriz que representa el mapa con caracteres
    int jugadorX, jugadorY;      // Posición actual del jugador en el mapa
    string panelTexto;           // Texto que se muestra en el panel de información

    Prologo prologo;             // Objeto para manejar narrativa inicial y escenas
    int prologoLineCount = 0;    // Número de líneas del texto de prólogo
    string prologoTexto[Prologo::MAX_LINEAS];  // Array que contiene líneas del prólogo
    int prologoIndex = 0;        // Índice para recorrer líneas del prólogo
    bool mostrandoPrologo = true; // Estado para saber si se muestra el prólogo

    bool enNarracionAmuleto = false;  // Estado para saber si se está en escena del amuleto
    bool enNarracionSlime = false;    // Estado para saber si se está en escena del Slime
    int narracionIndex = 0;            // Índice para recorrer la narrativa actual
    int narracionLineCount = 0;        // Número de líneas del texto narrativo actual
    string narracionTexto[Prologo::MAX_LINEAS];  // Array con líneas de la narrativa actual

    /*
        Método privado que verifica si alguna casilla adyacente al jugador
        contiene el símbolo especificado.
        Se revisa arriba, abajo, izquierda y derecha.
    */
    bool esAdyacente(char simbolo) const {
        return (mapa[jugadorX - 1][jugadorY] == simbolo ||
                mapa[jugadorX + 1][jugadorY] == simbolo ||
                mapa[jugadorX][jugadorY - 1] == simbolo ||
                mapa[jugadorX][jugadorY + 1] == simbolo);
    }

    /*
        Inicia la narrativa de la escena del amuleto:
        - Llena el texto de la escena.
        - Resetea índice y activa el estado de narración.
        - Muestra la primera línea en el panel de texto.
    */
    void iniciarNarracionAmuleto() {
        prologo.escenaAmuleto(narracionLineCount, narracionTexto);
        narracionIndex = 0;
        enNarracionAmuleto = true;
        panelTexto = narracionTexto[narracionIndex];
    }

    /*
        Inicia la narrativa de la escena del Slime:
        - Similar a la anterior, pero para la escena del Slime.
    */
    void iniciarNarracionSlime() {
        prologo.escenaSlime(narracionLineCount, narracionTexto);
        narracionIndex = 0;
        enNarracionSlime = true;
        panelTexto = narracionTexto[narracionIndex];
    }

    /*
        Método que simula una pantalla de combate (placeholder):
        - Limpia pantalla.
        - Muestra texto de inicio de combate.
        - Espera que el usuario presione tecla.
        - Luego regresa al mapa mostrando mensaje de victoria.
    */
    void combate() {
        system("cls");
        cout << "=== PANTALLA DE COMBATE ===\n";
        cout << "Combate iniciado contra Slime Oscuro!\n";
        cout << "Aquí iría la lógica del combate...\n";
        cout << "Presiona cualquier tecla para continuar...\n";
        _getch();
        system("cls");
        panelTexto = "Has derrotado al Slime Oscuro. Explora el mapa.";
    }

public:
    Mapa(); // Constructor para inicializar el mapa y variables
    void mostrarMapa() const;     // Muestra el mapa con el panel de texto
    void moverJugador(char direccion);  // Mueve al jugador si es posible
    void interactuar();           // Interactúa según el contexto del mapa
    void jugar();                 // Bucle principal del juego
    void mostrarPrologo();        // Avanza y muestra líneas del prólogo
    void avanzarNarracion();      // Avanza líneas en la narrativa de escenas
};

/*
    Constructor de la clase Mapa:
    - Inicializa el mapa con espacios y bordes con caracteres '|' y '-'.
    - Coloca estructuras en el mapa: casas, árboles, agua, etc.
    - Posiciona al jugador en una coordenada inicial.
    - Inicializa el texto del prólogo y muestra la primera línea.
*/
Mapa::Mapa() {
    // Rellenar todo el mapa con espacios vacíos
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            mapa[i][j] = ' ';

    // Dibujar bordes verticales a la izquierda y derecha
    for (int i = 0; i < FILAS; i++) {
        mapa[i][0] = '|';
        mapa[i][COLUMNAS - 1] = '|';
    }

    // Dibujar bordes horizontales arriba, a 4 filas del final y en la última fila
    for (int j = 0; j < COLUMNAS; j++) {
        mapa[0][j] = '-';
        mapa[FILAS - 4][j] = '-';
        mapa[FILAS - 1][j] = '-';
    }

    // Dibujar casas, árboles, arbustos y agua con caracteres específicos
    // Casa: combinación de '/', '_', '\', '|', '#'
    mapa[4][2] = '/'; mapa[3][3] = '_'; mapa[3][4] = '_'; mapa[3][5] = '_'; mapa[3][6] = '_'; mapa[3][7] = '_'; mapa[3][8] = '_'; mapa[4][9] = '\\';
    mapa[5][2] = '|'; mapa[5][3] = '#'; mapa[5][4] = ' '; mapa[5][5] = '_'; mapa[5][6] = ' '; mapa[5][7] = ' '; mapa[5][8] = ' '; mapa[5][9] = '|';
    mapa[6][2] = '|'; mapa[6][3] = '_'; mapa[6][4] = '|'; mapa[6][5] = ' '; mapa[6][6] = '|'; mapa[6][7] = '_'; mapa[6][8] = '_'; mapa[6][9] = '|';

    // Árboles representados con '^'
    mapa[10][10] = '^'; mapa[10][11] = '^'; mapa[11][10] = '^'; mapa[11][11] = '^';

    // Un objeto (posiblemente amuleto) con '(' y ')'
    mapa[20][25] = '('; mapa[20][26] = ')';

    // Agua representada con '~'
    mapa[7][35] = '~'; mapa[7][36] = '~'; mapa[8][35] = '~'; mapa[8][36] = '~';

    // Posición inicial del jugador, marcado con 'O'
    jugadorX = 9;
    jugadorY = 9;
    mapa[jugadorX][jugadorY] = 'O';

    // Inicializa y muestra la narrativa del prólogo
    prologo.introduccionNarrativa(prologoLineCount, prologoTexto);
    prologoIndex = 0;
    mostrandoPrologo = true;
    panelTexto = prologoTexto[prologoIndex];
}

/*
    Método para mostrar el mapa completo en consola,
    línea por línea, con el panel de texto al final.
    El panel de texto se coloca en las últimas filas del mapa.
*/
void Mapa::mostrarMapa() const {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            // En la fila FILAS-3 y columna 2 se muestra título del panel
            if (i == FILAS - 3 && j == 2) {
                string lineaTexto = "=== ACTION PANEL ===";
                cout << lineaTexto;
                // Completar el resto de la línea con espacios para que quede alineado
                int espacios = COLUMNAS - 2 - (int)lineaTexto.length();
                for (int k = 0; k < espacios; ++k) cout << ' ';
                break; // Terminar línea
            }
            // En la fila FILAS-2 y columna 2 se muestra el texto del panel actual
            else if (i == FILAS - 2 && j == 2) {
                cout << panelTexto;
                // Completar espacios para alineación
                int espacios = COLUMNAS - 2 - (int)panelTexto.length();
                for (int k = 0; k < espacios; ++k) cout << ' ';
                break; // Terminar línea
            }
            // Para cualquier otro lugar se imprime el carácter del mapa seguido de un espacio
            cout << mapa[i][j] << ' ';
        }
        cout << endl; // Nueva línea
    }
}

/*
    Método para mover al jugador en el mapa:
    - Recibe un carácter que indica dirección (w,s,a,d).
    - Calcula nueva posición.
    - Verifica que no se salga de límites ni choque con bordes.
    - Actualiza el mapa con la nueva posición del jugador.
    - No mueve si está en narrativa o prólogo.
*/
void Mapa::moverJugador(char direccion) {
    if (mostrandoPrologo || enNarracionAmuleto || enNarracionSlime) return; // No permitir movimiento durante narrativa

    int nuevaX = jugadorX;
    int nuevaY = jugadorY;

    // Cambiar coordenadas según la dirección
    switch (direccion) {
        case 'w': nuevaX--; break;  // Arriba
        case 's': nuevaX++; break;  // Abajo
        case 'a': nuevaY--; break;  // Izquierda
        case 'd': nuevaY++; break;  // Derecha
        default: return;  // Si es otra tecla, no hacer nada
    }

    // Verificar que la nueva posición esté dentro de límites seguros (no en bordes)
    if (nuevaX >= 1 && nuevaX < FILAS - 4 && nuevaY >= 1 && nuevaY < COLUMNAS - 1) {
        char destino = mapa[nuevaX][nuevaY];
        // Permitir movimiento solo sobre espacios vacíos o puntos (pueden ser caminos)
        if (destino == ' ' || destino == '.') {
            mapa[jugadorX][jugadorY] = ' ';  // Borrar antigua posición
            jugadorX = nuevaX;
            jugadorY = nuevaY;
            mapa[jugadorX][jugadorY] = 'O';  // Marcar nueva posición
        }
    }
}

/*
    Método para interactuar con el entorno:
    - Si se está en prólogo, avanza la narrativa del prólogo.
    - Si se está en alguna escena narrativa, avanza esa narrativa.
    - Si no, revisa si cerca del jugador hay algo especial para mostrar mensaje o iniciar escena.
*/
void Mapa::interactuar() {
    if (mostrandoPrologo) {
        mostrarPrologo();
        return;
    }

    if (enNarracionAmuleto || enNarracionSlime) {
        avanzarNarracion();
        return;
    }

    // Según el símbolo en casillas adyacentes, se muestra texto o se inicia escena
    if (esAdyacente('|') || esAdyacente('/') || esAdyacente('\\')) {
        panelTexto = "You see a house. It's locked.";
    } else if (esAdyacente('(') || esAdyacente(')')) {
        // Si cerca está el amuleto, iniciar escena narrativa del amuleto
        iniciarNarracionAmuleto();
    } else if (esAdyacente('^')) {
        panelTexto = "You see a tree.";
    } else if (esAdyacente('~')) {
        panelTexto = "You hear the river flowing nearby.";
    } else {
        panelTexto = "Nothing interesting nearby.";
    }
}

/*
    Método para mostrar la siguiente línea del prólogo:
    - Si no está mostrando prólogo, no hace nada.
    - Incrementa índice y actualiza panel.
    - Cuando termina, cambia el estado y muestra instrucciones básicas.
*/
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

/*
    Método para avanzar en la narrativa actual:
    - Incrementa índice de línea.
    - Si se terminó la narrativa actual, cambia estado:
        * De amuleto pasa a escena Slime
        * De Slime pasa a combate
    - Si no, simplemente muestra la siguiente línea.
*/
void Mapa::avanzarNarracion() {
    narracionIndex++;
    if (narracionIndex >= narracionLineCount) {
        if (enNarracionAmuleto) {
            enNarracionAmuleto = false;
            iniciarNarracionSlime();  // Después del amuleto, inicia narrativa del Slime
        } else if (enNarracionSlime) {
            enNarracionSlime = false;
            combate();  // Después de la narrativa Slime, pasa a combate
        }
    } else {
        panelTexto = narracionTexto[narracionIndex];
    }
}

/*
    Método principal para jugar:
    - Bucle infinito hasta que el jugador decida salir.
    - Limpia pantalla y muestra mapa.
    - Si está en prólogo o narrativa, espera tecla para avanzar texto.
    - Si no, lee la opción del usuario (movimiento, interactuar, salir).
*/
void Mapa::jugar() {
    char opcion;
    while (true) {
        cout << "\033[H"; // Código ANSI para mover cursor al inicio y limpiar pantalla (funciona en algunas terminales)
        mostrarMapa();

        // Si está en prólogo, esperar tecla y mostrar siguiente línea
        if (mostrandoPrologo) {
            cout << "\n[Prologue] Presiona cualquier tecla para continuar...\n";
            _getch();
            mostrarPrologo();
            continue;
        }

        // Si está en escena narrativa, esperar tecla y avanzar narrativa
        if (enNarracionAmuleto || enNarracionSlime) {
            cout << "\n[Narración] Presiona cualquier tecla para continuar...\n";
            _getch();
            avanzarNarracion();
            continue;
        }

        // Mostrar instrucciones para el jugador
        cout << "\nMove: W/A/S/D | Interact: E | Quit: Q\n";
        cout << "Option: ";
        opcion = tolower(_getch());  // Lee tecla y pasa a minúscula para uniformidad

        if (opcion == 'q') break;    // Salir del juego
        else if (opcion == 'e') interactuar();  // Interactuar con el entorno
        else moverJugador(opcion);   // Mover jugador según dirección
    }
}

#endif // PROLOGUEMAP_H
