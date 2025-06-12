    #ifndef JUGADOR_H // ifndef para saber si este archivo ya fue incluido en otro .h
    #define JUGADOR_H // si no ha sido incluido en ningun otro, pues hara que se pueda usar aqui

    // NO INCLUIMOS "using namespace std;" EN UN ARCHIVO .h POR QUE PODRIA DAR CONFLICTOS CON ARCHIVOS .cpp O DECLARACION DE NOMBRES (BUENA PRACTICA)

    #include <string> // para poder usar cadenas de texto

    class Jugador
    {
        // Lo declaramos privado para que solo se puedan hacer modificaciones dentro del archivo .h y que no se puedan modificar dentro de main al momento de incluirlo
    private:
        std::string nombre;  // Nombre del jugador que sera un nombre quemado
        int vida;            // Atibuto vida que representara la salud que tiene el jugador
        int ataque;          // Atributo ataque que representara el ataque que tiene el jugador
        int defensa;         // atributo defensa que representara cuanta defensa tiene el jugador
        int ataque_especial; // atributo ataque especial que representara su ataque especial

    public: // Permitimos que el constructor sea publico para poder usarse fuera de la clase por ejemplo usarse en main.cpp
            // Constructor: crea un jugador con su vida, ataque defensa y ataque especial
        Jugador(int vida, int ataque, int defensa, int ataque_especial);

        // Que es const? esto dice que no va modificar nada del objeto solo leera los datos que tenga

        // Metodos de utilidad, solo sirven para obterner los valores leerlos y mostrarlos y no devuelveen ningun valor (Por eso los inicialiamos con void = vacio)
        void mostrarStats() const;
        void recibirDanio(int danio); // Declaramos una variable daño por que este puede variar

        // Funciones publicas "Getters" para obtener datos de una clase privada
        int getAtaque() const;
        int getVida() const;
        int getAtaqueEspecial() const;
        int getDefensa() const;
        std::string getNombre() const;
    };

    #endif