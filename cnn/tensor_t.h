#ifndef TENSOR_T_H__
#define TENSOR_T_H__

#include <vector>
#include <assert.h>
#include <string.h>
#include "types.h"

template <typename T>
struct tensor_t {
  tsize_t size;
  T* data;
  
  tensor_t( uint_t _x, uint_t _y, uint_t _z ) {
    assert( _x > 0  && _y > 0 && _z > 0 );
    data = new T[_x * _y * _z];
    size.x = _x;
    size.y = _y;
    size.z = _z;
  }

  tensor_t( uint_t _x, uint_t _y ) {
    assert( _x > 0  && _y > 0 );
    data = new T[_x * _y]; // data = new T[_x * _y * 1]
    size.x = _x;
    size.y = _y;
    size.z = 1;
  }

  tensor_t( uint_t _x ) {
    assert( _x > 0 );
    data = new T[_x]; // data = new T[_x * 1 * 1]
    size.x = _x;
    size.y = 1;
    size.z = 1;
  }

  tensor_t( const tensor_t<T>& other ) {
    data = new T[other.size.x * other.size.y * other.size.z];
    memcpy( 
            this->data,
            other.data,
            other.size.x * other.size.y * other.size.z * sizeof( T )
    );
    this->size = other.size;
  }

  T& get( uint_t _x, uint_t _y, uint_t _z )
  {
    assert( _x < size.x  && _y < size.y && _z < size.z );

    return data[ 
                 size.z * size.y* _x + 
                 size.z * _y + 
                 _z
                 /*
                 _z * (size.x * size.y) +
                 _y * (size.x) +
                 _x
                */
            ];
  }

  T& operator()( uint_t _x, uint_t _y, uint_t _z )
  {
    return get( _x, _y, _z );
  }

  T& operator()( uint_t _x, uint_t _y )
  {
    return get( _x, _y, 0 );
  }

  T& operator()( uint_t _x )
  {
    return get( _x, 0, 0 );
  }

  void copy_from( const std::vector<std::vector<std::vector<T> > >& _data )
  {
    uint_t _size_x = _data.size();
    uint_t _size_y = _data[0].size();
    uint_t _size_z = _data[0][0].size();
    assert( size.x == _size_x && size.y == _size_y && size.z == _size_z);

    for (uint_t i = 0; i < _size_x; i++) {
      for (uint_t j = 0; j < _size_y; j++) {
        for (uint_t k = 0; k < _size_z; k++) {
          this->get(i, j, k) = _data[i][j][k];
          /*
          this->get(i, j, k) = _data[k][j][i];
          */
        }
      }
    }
  }

  void copy_from( const tensor_t<T>& other ) {
    assert( (other.size.x == size.x) && (other.size.y == size.y) && (other.size.z == size.z) );
    memcpy( 
            this->data,
            other.data,
            other.size.x * other.size.y * other.size.z * sizeof( T )
    );
  }

  tensor_t<T> operator+( tensor_t<T>& other )
  {
    assert(this->size.x == other.size.x);
    assert(this->size.y == other.size.y);
    assert(this->size.z == other.size.z);
    tensor_t<T> clone(*this);
    for (int i = 0; i < clone.size.x; i++) {
      clone.data[i] += other.data[i];
    }
    return clone;
  }

  tensor_t<T> operator-( tensor_t<T>& other )
  {
    assert(this->size.x == other.size.x);
    assert(this->size.y == other.size.y);
    assert(this->size.z == other.size.z);
    tensor_t<T> clone(*this);
    for (uint_t i = 0; i < clone.size.x; i++) {
      clone.data[i] -= other.data[i];
    }
    return clone;
  }

  uint_t get_size() {
    return size.x * size.y * size.z;
  }

  ~tensor_t()
  {
    delete[] data;
  }
};


#endif
