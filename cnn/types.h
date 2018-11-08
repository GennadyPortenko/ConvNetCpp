#ifndef TYPES_H__
#define TYPES_H__

typedef unsigned int uint_t;
typedef uint_t uint32_t;

struct point_t {
  uint_t x, y, z;
  point_t() {}
  point_t( uint_t& _x, uint_t& _y, uint_t& _z )
  {
    x = _x;
    y = _y;
    z = _z;
  }
};

struct tsize_t {
  uint_t x, y, z;
  tsize_t() { }
  tsize_t( int _x, int _y, int _z )
  {
    x = (uint_t)_x;
    y = (uint_t)_y;
    z = (uint_t)_z;
  }
};

typedef enum {
  LAYER_FC,
  LAYER_CONV,
  LAYER_RELU,
  LAYER_POOL
} layer_type_t;

#endif
