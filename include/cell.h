#pragma once

#include <utility> // Para utilizar std::pair
#include <vector>
#include <iostream>

// Definición del tipo de dato para la posición
using Position = std::pair<int, int>;
// Definición del tipo de dato para el estado
using State = bool;

// Declaracion adelantada de la clase Lattice
class Lattice;

// Definición de la clase Cell
class Cell {
public:

  // Constructor de la célula
  Cell(const Position& pos, const State& state);

  // getter y setter de estado
  const State getState() const;
  void setState(State newState);

  // getter y setter de siguiente estado
  State getNextState() const;
  void setNextState(State newState);

  // updater
  void updateState();

  // getter y setter de posicion
  const Position getPosition() const;
  void setPosition(int row, int col);

  // vecindad
  std::vector<Cell> getNeighbors(Lattice& lattice);

  // funcion de transicion
  State transitionFunction(std::vector<Cell> neighbors);

  // Sobrecarga del operador<<
  friend std::ostream& operator<<(std::ostream& os, const Cell& cell);

private:
  Position position_; // Posición de la célula en el retículo
  State state_;       // Estado de la célula
  State nextState_;
};
