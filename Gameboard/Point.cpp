#include "Point.h"

Point::Point(uint8_t x, uint8_t y) {
  _x = x;
  _y = y;
}

uint8_t Point::GetX() {
  return _x;
}

uint8_t Point::GetY() {
  return _y;
}

