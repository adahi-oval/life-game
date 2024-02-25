#include "cell.h"

Cell::Cell(const Position& pos, const State& state) {
  position_ = pos;
  state_ = state;
}

const State Cell::getState() const {
  return state_;
}

void Cell::setState(State newState) {
  state_ = newState;
}

const Position Cell::getPosition() const {
  return position_;
}

void Cell::setPosition(int row, int col) {
  position_.first = row;
  position_.second = col;
}