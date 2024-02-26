#pragma once

#include <iostream>
#include "cell.h" // Incluir el archivo de encabezado de la clase Cell
#include <vector>
#include <utility> // Para utilizar std::pair
#include <algorithm> // Para std::find

// Declaracion adelantada de la clase Cell
class Cell;

// Definición de la clase Lattice
class Lattice {
public:
    // Constructor que crea las células en memoria dinámica con valor inicial de estado muerta
    Lattice(int N, int M);
    Lattice(const char* filename);
    Lattice(int once);

    // Destructor para liberar la memoria de las células
    ~Lattice();

    std::string getFrontera() const;
    void setFrontera(const std::string& frontera);

    // getters rows y cols
    int getRows() const;
    int getCols() const;

    // getter y setter popmode
    bool getPopMode() const;
    void setPopMode(bool b);

    // Pedir celulas vivas
    void askForLiveCells();

    // Conocer poblacion
    std::size_t Population() const;

    // Condiciones de frontera
    void noFrontier(int i, int j);
    void periodicFrontier();
    void openFrontier(const bool temp);
    void removeBorders();

    // actualizador de posiciones
    void updatePositions();

    // actualizador de estados
    void updateStates();

    // calculo siguiente generacion
    void nextGeneration();

    // guardar a un archivo
    void saveToFile(const char* filename) const;

    // sobrecarga de operadores
    Cell& operator[](const Position& pos) const;
    friend std::ostream& operator<<(std::ostream& os, const Lattice& lattice);
    Lattice& operator=(const Lattice& other);

private:
    int rows;                  // Ancho de la retícula
    int cols;                 // Altura de la retícula
    std::vector<std::vector<Cell*>> cells_;   // Vector de punteros a células
    std::string frontera_;
    bool popMode; // modo population
};
