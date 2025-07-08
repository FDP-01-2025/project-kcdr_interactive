# Proyecto de C++ - Brothers of the Dawn: Fragments of the Alba

## Tematica y ambientacion 

Este juego es un RPG desarrollado en C++ con un diseño visual completamente hecho en terminal, lo que le da un estilo retro y nostálgico. Ambientado en un mundo mágico y misterioso, el jugador explora diferentes zonas del mapa enfrentándose a enemigos mientras desentraña una aventura épica. La historia gira en torno a una misión heroica: rescatar a sus hermanos, quien ha sido capturado por los cuatro poderosos jefes que dominan cada región del mapa. Cada victoria acerca al jugador a la libertad de un pueblo encantado, atrapado bajo el yugo oscuro de estos jefes. Con un enfoque en la exploración, el combate y la narrativa emocional, el juego sumerge al jugador en una experiencia única desde la simplicidad de la terminal.

## Mecánica principal

La temática central del juego gira en torno al combate estratégico. A lo largo del mapa, el jugador se enfrenta a monstruos enviados por los jefes finales, cuyo objetivo es impedir su avance. Cada enfrentamiento pone a prueba la valentía, la preparación y las decisiones del jugador, quien debe luchar para seguir adelante en su misión. Cada personaje disponible cuenta con fortalezas únicas, lo que permite distintas formas de encarar las batallas. Además, una buena toma de decisiones puede marcar la diferencia entre sobrevivir o caer, ya que en ciertos casos es posible evitar combates innecesarios con enemigos especialmente peligrosos. El juego invita a pensar antes de actuar y a usar la inteligencia tanto como la fuerza.

## Idea general de la jugabilidad 

La jugabilidad se basa en la exploración, la estrategia y la elección del personaje. Al iniciar la aventura, el jugador elige entre varios personajes, cada uno con habilidades y fortalezas distintas que influirán en su estilo de juego. A medida que explora el mapa, deberá enfrentarse a enemigos, evitar trampas y encontrar llaves ocultas que son esenciales para desbloquear las puertas que conducen a los jefes finales. Esta dinámica combina la toma de decisiones, el combate y la búsqueda de objetos clave, ofreciendo una experiencia desafiante y progresiva dentro de un mundo mágico lleno de secretos.

## Aplicación de los temas vistos
`Tipos de datos:` En todos las variables del programa.

**Estructuras condicionales**
`if:` Para el funcionamiento de los objetos que dropean los enemigos.
`else:` Complementa al uso del if.
`switch:` Para manejar las opciones del menu principal del juego.

**Ciclos**
`for:` Para ayudar a la generación de los bordes del mapa.
`while:` En el funcionamiento principal del juego, en playGame().
`do while:` Para mantener la tienda activa mientras el jugador realiza compras.

`Funciones:` El juego utiliza funciones en la mayoria de archivos .h.

`Estructuras de datos: ` En el sistema de guardado.

`Manejo de archivos: ` Al igual que las estructuras, el manejo de archivo se utiliza en el sistema de guardado.

`Manejo de errores: ` El manejo de errores es parte del funciomaniento de la tienda. Al verificar la cantidad de dinero disponible.

## Consideraciones tecnicas del desarrollo

**Lenguaje y herramientas**
El juego esta hecho en c++, se utilizó el IDE Visual Studio Code para su realización y se ejecuta por medio de g++/MinGW. El juego al momento tiene soporte únicamente en Windows. Todas las librerias estas hechas para que funcionen en ese sistema operativo.

**Modularidad y Organización**
El proyecto está dividido en múltiples archivos .h y .cpp, cada uno con responsabilidades claras (menús, inventario, combate, guardado, historia, etc.).
Se utilizan namespaces y clases para evitar colisiones de nombres y mejorar la mantenibilidad.

**Interfaz de Usuario en Consola**
El juego utiliza ASCII art y paneles de texto para la presentación visual.
Los mensajes importantes pueden mostrarse tanto en paneles pequeños como en pantalla completa, según el contexto.
Se emplean funciones para centrar y formatear texto en el grid.


## Mockups
**Menú principal**  
![image](https://github.com/user-attachments/assets/bf6456a9-30e8-4c02-bc18-b0f839d9cec7)  

**Mapa central del juego**  
![image](https://github.com/user-attachments/assets/778fcae0-9152-4b7e-ad95-9e6e8591c451)  


**Combate con enemigos del juego (uno de ellos)**  
![image](https://github.com/user-attachments/assets/aa053ea6-6dfd-4330-a1c2-5c24eb2dd7f7)  


**Combate con el Boss del juego (uno de ellos)**  
![image](https://github.com/user-attachments/assets/fddcdf06-be11-4c6c-9e92-bece8d02f87a)  


**Interfaz de tienda**  
![image](https://github.com/user-attachments/assets/9026d329-1a65-48f0-b054-b38db7db0366)  


**Inventario**  
![image](https://github.com/user-attachments/assets/f959883a-3ed0-4312-9c6e-2d13d2f1c779)  


**Pantalla de derrota**  
![image](https://github.com/user-attachments/assets/f54eb8e5-2d05-421c-b1ed-c035eb302cfc)  


**Pantalla de victoria**  
![image](https://github.com/user-attachments/assets/94e7ae5b-6889-489e-bf1b-483a02b18375)  










## Equipo

- **Nombre del equipo:** KCDR Interactive

### Integrantes del equipo

1. **Nombre completo:** [Diego Fernando Villegas Gómez]  
   **Carnet:** [00109825]

2. **Nombre completo:** [Rodrigo Javier Mendoza Alvarado]  
   **Carnet:** [00110125]

3. **Nombre completo:** [Christopher Alessandro Juárez Ponce]  
   **Carnet:** [00127525]

3. **Nombre completo:** [Kevin Vladimir Rodriguez Alvarado]  
   **Carnet:** [00039425]

  ## Link de los diagramas  

  https://drive.google.com/file/d/1fSZxHB4dRFUcre_ctgWz_VOCyYwcfalo/view?usp=sharing

## Instrucciones de Ejecución

1. Clona este repositorio en tu máquina local:
   ```bash
   git clone [https://github.com/FDP-01-2025/project-kcdr_interactive.git]


   
