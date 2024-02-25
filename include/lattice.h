#include <iostream>
#include "cell.h" // Incluir el archivo de encabezado de la clase Cell
#include <vector>
#include <utility> // Para utilizar std::pair
#include <algorithm> // Para std::find

// Definición de la clase Lattice
class Lattice {
public:
    // Constructor que crea las células en memoria dinámica con valor inicial de estado muerta
    Lattice(int N, int M);
    Lattice(const char* filename);

    // Destructor para liberar la memoria de las células
    ~Lattice();

    std::string getFrontera() const;
    void setFrontera(const std::string& frontera);

    // Pedir celulas vivas
    void askForLiveCells();

    // Conocer poblacion
    std::size_t Population() const;

    // Condiciones de frontera
    void noFrontier(int i, int j);
    void periodicFrontier();
    void openFrontier(const bool temp);
    void removeBorders();

    Cell& operator[](const Position& pos) const;

private:
    int rows;                  // Ancho de la retícula
    int cols;                 // Altura de la retícula
    std::vector<std::vector<Cell*>> cells_;   // Vector de punteros a células
    std::string frontera_;
};
