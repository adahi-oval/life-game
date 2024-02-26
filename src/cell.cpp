#include "cell.h"
#include "lattice.h"

Cell::Cell(const Position& pos, const State& state) {
  position_ = pos;
  state_ = state;
  nextState_ = false;
}

const State Cell::getState() const {
  return state_;
}

void Cell::setState(State newState) {
  state_ = newState;
}

State Cell::getNextState() const {
  return nextState_;
}

void Cell::setNextState(State newState) {
  nextState_ = newState;
}

void Cell::updateState() {
  state_ = nextState_;
}

const Position Cell::getPosition() const {
  return position_;
}

void Cell::setPosition(int row, int col) {
  position_.first = row;
  position_.second = col;
}

// Vecindad
std::vector<Cell> Cell::getNeighbors(Lattice& lattice) {
  
  lattice.updatePositions();
  std::vector<Cell> neighbors;
  Position pos(this->getPosition());

  if (lattice.getFrontera() != "noBorder")
  {
    // Conocer los estados de su vecindad, en sentido horario empezando por la izquierda
    neighbors.push_back(lattice[std::make_pair(pos.first, pos.second - 1)]); // izquierda
    neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second - 1)]); // arriba izquierda
    neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second)]); // arriba
    neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second + 1)]); // arriba derecha
    neighbors.push_back(lattice[std::make_pair(pos.first, pos.second + 1)]); // derecha
    neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second + 1)]); // abajo derecha
    neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second)]); // abajo
    neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second - 1)]); // abajo izquierda
  } else
  {
    if (pos.first == 0 && pos.second == 0) // Esquina superior izq
    {

      neighbors.push_back(lattice[std::make_pair(pos.first, pos.second + 1)]); // derecha
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second + 1)]); // abajo derecha
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second)]); // abajo

    } else if (pos.first == 0 && pos.second == lattice.getCols() - 1) // Esquina superior derecha
    {

      neighbors.push_back(lattice[std::make_pair(pos.first, pos.second - 1)]); // izquierda
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second)]); // abajo
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second - 1)]); // abajo izquierda

    } else if (pos.first == lattice.getRows() - 1 && pos.second == lattice.getCols() - 1) // Esquina inferior derecha
    {
      
      neighbors.push_back(lattice[std::make_pair(pos.first, pos.second - 1)]); // izquierda
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second - 1)]); // arriba izquierda
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second)]); // arriba

    } else if (pos.first == lattice.getRows() - 1 && pos.second == 0) // Esquina inferior izquierda
    {
      
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second)]); // arriba
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second + 1)]); // arriba derecha
      neighbors.push_back(lattice[std::make_pair(pos.first, pos.second + 1)]); // derecha

    } else if (pos.first == 0) // Borde superior
    {

      neighbors.push_back(lattice[std::make_pair(pos.first, pos.second - 1)]); // izquierda
      neighbors.push_back(lattice[std::make_pair(pos.first, pos.second + 1)]); // derecha
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second + 1)]); // abajo derecha
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second)]); // abajo
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second - 1)]); // abajo izquierda

    } else if (pos.second == lattice.getCols() - 1) // Borde derecho
    {
      
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second)]); // abajo
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second - 1)]); // abajo izquierda
      neighbors.push_back(lattice[std::make_pair(pos.first, pos.second - 1)]); // izquierda
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second - 1)]); // arriba izquierda
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second)]); // arriba

    } else if (pos.first == lattice.getRows() - 1) // Borde inferior
    {

      neighbors.push_back(lattice[std::make_pair(pos.first, pos.second - 1)]); // izquierda
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second - 1)]); // arriba izquierda
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second)]); // arriba
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second + 1)]); // arriba derecha
      neighbors.push_back(lattice[std::make_pair(pos.first, pos.second + 1)]); // derecha

    } else if (pos.second == 0) // Borde izquierdo
    {
      
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second)]); // arriba
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second + 1)]); // arriba derecha
      neighbors.push_back(lattice[std::make_pair(pos.first, pos.second + 1)]); // derecha
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second + 1)]); // abajo derecha
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second)]); // abajo

    } else
    {
      // Conocer los estados de su vecindad, en sentido horario empezando por la izquierda
      neighbors.push_back(lattice[std::make_pair(pos.first, pos.second - 1)]); // izquierda
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second - 1)]); // arriba izquierda
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second)]); // arriba
      neighbors.push_back(lattice[std::make_pair(pos.first - 1, pos.second + 1)]); // arriba derecha
      neighbors.push_back(lattice[std::make_pair(pos.first, pos.second + 1)]); // derecha
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second + 1)]); // abajo derecha
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second)]); // abajo
      neighbors.push_back(lattice[std::make_pair(pos.first + 1, pos.second - 1)]); // abajo izquierda
    }
  }
  
  
  
  return neighbors;
}

// Funcion de transicion
State Cell::transitionFunction(std::vector<Cell> neighbors) {
  // Contar células vivas en los vecinos
  int aliveCount = 0;

  for (int i = 0; i < neighbors.size(); i++)
  {
    if(neighbors[i].getState()){
      aliveCount++;
    }
  }
  
  // Lógica de la funcion de transicion
  if (this->getState())
  {
    if (aliveCount == 2 || aliveCount == 3)
    {
      return true;
    } else
    {
      return false;
    }
  } else
  {
    if (aliveCount == 3)
    {
      return true;
    } else
    {
      return false;
    } 
  }
}

// Implementación de la sobrecarga del operador <<
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  // Si el estado de la célula es 1(true), imprimir 'X', de lo contrario, imprimir ' '
  os << (cell.getState() ? 'X' : '-');
  return os;
}