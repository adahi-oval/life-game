#pragma once

#include <vector>
#include <iostream>

// Definiciones de tipos
using Position = int; // Tipo de dato para la posición dentro del retículo
using State = bool;   // Tipo de dato para el estado binario de la célula

// Declaración adelantada de la clase Lattice
class Lattice;

// Declaración de la clase Cell
class Cell {
public:
  // Constructor
  Cell(const Position& position, const State& initialState = false);

  // Métodos
  State getState() const; // Método para obtener el estado de la célula
  State getNextState() const;
  void setState(State newState); // Método para establecer el estado de la célula
  void setNextState(State newState);
  void nextState(const Lattice& lattice); // Método para calcular el siguiente estado de la célula
  void updateState(); // Método para actualizar el estado de la célula
  const State transitionFunction(const State& C, const State& L, const State& R) const;
  std::vector<State> getNeighbors(const Lattice& lattice) const;

  // Operador de inserción en flujo para la clase Cell
  friend std::ostream& operator<<(std::ostream& os, const Cell& cell);

private:
  Position position_; // Posición dentro del retículo
  State state_;       // Estado actual de la célula
  State nextState_;   // Estado siguiente de la célula
};
