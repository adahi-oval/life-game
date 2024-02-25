#pragma once

#include <vector>
#include <iostream>
#include "cell.h"

// Declaración adelantada de la clase Cell
class Cell;

// Declaración de la clase Lattice
class Lattice {
public:
  // Constructor
  Lattice(int size, std::string frontera);

  // Destructor
  ~Lattice();

  int getSize() const;
  std::string getFrontera() const;

  // Método para obtener una referencia constante a una célula en una posición específica
  const Cell& getCell(const Position& position) const;

  // Método para cargar la configuración inicial del autómata celular
  void loadInitialConfiguration(std::vector<char>);
  void nextGeneration();

  // Sobrecarga del operador <<
  friend std::ostream& operator<<(std::ostream&, const Lattice&);

private:
  std::vector<Cell*> cells_;
  int size_;
  std::string frontera_;
};
