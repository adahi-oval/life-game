#include "lattice.h"
#include <stdexcept>

// Constructor del retículo
Lattice::Lattice(int size, std::string frontera) {

  size_ = size;
  frontera_ = frontera;

  // Crear las células del retículo en memoria dinámica y agregar punteros a ellas al vector
  for (int i = 0; i < size_; ++i) {
    cells_.push_back(new Cell(i, false)); // Agrega un nuevo puntero a célula al final del vector
  }
}

// Destructor del retículo
Lattice::~Lattice() {
  // Liberar la memoria de las células
  for (auto cellPtr : cells_) {
    delete cellPtr;
  }
}

// getter para size_
int Lattice::getSize() const {
  return size_;
}

// getter para frontera_
std::string Lattice::getFrontera() const {
  return frontera_;
}

// Método para obtener una referencia constante a una célula en una posición específica
const Cell& Lattice::getCell(const Position& position) const {
  if (position >= 0 && position < size_) {
    return *cells_[position];
  }
  throw std::out_of_range("Position is out of range");
}

void Lattice::loadInitialConfiguration(std::vector<char> initialConfig) {
  if (initialConfig.size() != 0) {
    for (int i = 0; i < initialConfig.size(); i++)
    {
      if (initialConfig[i] == '0')
      {
        cells_[i]->setState(false);
      }else
      {
        cells_[i]->setState(true);
      }
    }
    
  }else
  {
    // Colocar el valor de estado "0" en todas las células
    for (auto cellPtr : cells_) {
      cellPtr->setState(false);
    }
    // Asignar el valor de estado "1" a la célula central
    if (size_ % 2 == 0) {
      cells_[size_ / 2]->setState(true);
    } else {
      cells_[size_ / 2]->setState(true);
    }
  }
  
}

// Funcion para pasar a la siguiente generacion de las celulas en el reticulo, dos recorridos.
void Lattice::nextGeneration() {
  // Primer recorrido
  for (int i = 0; i < this->cells_.size(); i++)
  {
    this->cells_[i]->nextState(*this);
  }

  // Segundo recorrido
  for (int i = 0; i < this->cells_.size(); i++)
  {
    this->cells_[i]->updateState();
  }
}

// Sobrecarga del operador <<
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  for (int i = 0; i < lattice.cells_.size(); i++)
  {
    os << *lattice.cells_[i];
  }
  
  return os;
}