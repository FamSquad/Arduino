#ifndef POINT_H
#define POINT_H

#include <stdint.h>

class Point {
  private:
    uint8_t _x, _y;

  public:
    Point(uint8_t x, uint8_t y);
    uint8_t GetX();
    uint8_t GetY();
};


#endif
