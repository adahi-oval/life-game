#include "cell.h"
#include "lattice.h"

// Constructor de la célula
Cell::Cell(const Position& position, const State& initialState) {
  position_ = position;
  state_ = initialState;
}

// Obtener el estado de la célula
State Cell::getState() const {
  return state_;
}

// Obtener el estado siguiente de la célula
State Cell::getNextState() const {
  return nextState_;
}

// Establecer el estado de la célula
void Cell::setState(State newState) {
  state_ = newState;
}

// Establecer nextState_
void Cell::setNextState(State newState) {
  nextState_ = newState;
}

std::vector<State> Cell::getNeighbors(const Lattice& lattice) const {
  std::vector<State> neighbors;

  if (position_ > 0 && position_ < lattice.getSize() - 1) { // Verificar si la posición actual no es la primera
    neighbors.push_back(lattice.getCell(position_ - 1).getState());
    neighbors.push_back(lattice.getCell(position_ + 1).getState());
  } 
  
  else if(position_ == 0) { // Caso para la primera Célula

    if(lattice.getFrontera() == "abiertaFria") { 
      neighbors.push_back(false);
      neighbors.push_back(lattice.getCell(position_ + 1).getState());
    }  

    else if(lattice.getFrontera() == "abiertaCaliente") { 
      neighbors.push_back(true);
      neighbors.push_back(lattice.getCell(position_ + 1).getState());
    }

    else if(lattice.getFrontera() == "periodic") {
      neighbors.push_back(lattice.getCell(lattice.getSize() - 1).getState()); // última posición
      neighbors.push_back(lattice.getCell(position_ + 1).getState());
    }

    else { throw std::invalid_argument("Tipo de frontera no válido"); }
  } 
  
  else if(position_ == lattice.getSize() - 1) { // Caso para última célula

    if(lattice.getFrontera() == "abiertaFria") { 
      neighbors.push_back(lattice.getCell(position_ - 1).getState());
      neighbors.push_back(false); 
    }

    else if(lattice.getFrontera() == "abiertaCaliente") { 
      neighbors.push_back(lattice.getCell(position_ - 1).getState());
      neighbors.push_back(true); 
    }

    else if(lattice.getFrontera() == "periodic") {
      neighbors.push_back(lattice.getCell(position_ - 1).getState());
      neighbors.push_back(lattice.getCell(0).getState()); // primera posición
    }

    else { throw std::invalid_argument("Tipo de frontera no válido"); }
  }

  return neighbors;
}


// Función de transición, para next State usando la regla 110
const State Cell::transitionFunction(const State& C, const State& L, const State& R) const {
  State result = C + R + C * R + L * C * R;
  return result;
}

// Calcular el siguiente estado de la célula
void Cell::nextState(const Lattice& lattice) {
  std::vector<State> vecinos = this->getNeighbors(lattice);

  State C = this->getState();
  State L = vecinos[0];
  State R = vecinos[1];

  this->nextState_ = transitionFunction(C, L, R);
}

// Actualizar estado
void Cell::updateState() {
  this->setState(this->getNextState());
}

// Implementación de la sobrecarga del operador <<
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  // Si el estado de la célula es 1(true), imprimir 'X', de lo contrario, imprimir ' '
  os << (cell.getState() ? 'X' : '-');
  return os;
}
