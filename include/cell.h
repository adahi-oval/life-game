#include <utility> // Para utilizar std::pair

// Definición del tipo de dato para la posición
using Position = std::pair<int, int>;
// Definición del tipo de dato para el estado
using State = bool;

// Definición de la clase Cell
class Cell {
public:

  // Constructor de la célula
  Cell(const Position& pos, const State& state);

  // getter y setter de estado
  const State getState() const;
  void setState(State newState);

  // getter y setter de posicion
  const Position getPosition() const;
  void setPosition(int row, int col);

private:
  Position position_; // Posición de la célula en el retículo
  State state_;       // Estado de la célula
};
