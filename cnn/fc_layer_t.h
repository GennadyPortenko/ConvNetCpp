#ifndef FC_LAYER_T_H__
#define FC_LAYER_T_H__

#include <vector>
#include <math.h>
#include <boost/format.hpp>
#include "gradient_t.h"
#include "optimization.h"

struct fc_layer_t {
  layer_type_t type;
  tensor_t<float> in;
  tensor_t<float> out;
  tensor_t<float> weights;
  tensor_t<float> biases;
  std::vector<float> sum;
  tensor_t<float> dE_dIn; // partial derivative of network error by n-th layer input

  fc_layer_t( tsize_t _in_size, uint_t _out_size ) :
    in( _in_size.x, _in_size.y, _in_size.z ),
    out( _out_size ),
    weights( _out_size, _in_size.x * _in_size.y * _in_size.z ),
    biases( _out_size ),
    sum( _out_size ),
    dE_dIn( _in_size.x * _in_size.y * _in_size.z )
  {
    type = LAYER_FC;

    init_weights();
  }

  ~fc_layer_t() {
  }

  // FIXME
  void init_weight_rand_small( float& weight, uint_t maxval ) {
    // random small values
    weight = 2.19722f / maxval * rand() / float( RAND_MAX ); // random small values 
  }

  void init_weight_rand(float& weight) {
    // random values -1..1
    int evn = rand() % 2;
    if (evn == 0) {
      weight = float(rand()) / (float(RAND_MAX) + 1.0);
    } else {
      weight = -1 * float(rand()) / (float(RAND_MAX) + 1.0);
    }
  }

  void init_weights() {
    srand(time(NULL));
    for ( uint_t i = 0 ; i < out.size.x; i++ ) {
      init_weight_rand( biases( i ) );
      for ( uint_t j = 0 ; j < ( in.get_size() ); j++ ) {
        // init_weight_rand_small( weights(i, j, 0), in.size.x * in.size.y * in.size.z ) ;
        init_weight_rand( weights( i, j ) ) ;
      }
    }
  }

  void print_weights()
  {
    for ( uint_t j = 0; j < weights.size.y; j++ ) {
      std::cout << "output neuron " << j << " : ";
      for ( uint_t i = 0; i < weights.size.x; i++ ) {
          std::cout << boost::format("%7.5f") % weights( i, j, 0 ) << "  ";
      }
      std::cout << std::endl;
    }
  }

  uint_t map( point_t p )
  {
    return in.size.z * in.size.y* p.x + 
           in.size.z * p.y + 
           p.z;
           /*
           return p.z * (in.size.x * in.size.y) +
             p.y * (in.size.x) +
             p.x;
           */
  }

  float sig( float x )
  {
    float sig = 1.0f / (1.0f + exp( -x ));
    return sig;
  }

  float activator_function( float x )
  {
    //return tanhf( x );
    return sig(x);
  }

  /*
  float activator_derivative( float x )
  {
    //float t = tanhf( x );
    //return 1 - t * t;
    return sig( x ) * ( 1 - sig( x ) ); // (sig)' = sig * (1 - sig)
  }
  */

  void activate( const tensor_t<float>& _in )
  {
    assert( (_in.size.x == in.size.x) && (_in.size.y == in.size.y) && (_in.size.z == in.size.z) );

    in.copy_from(_in);
    activate();
  }

  void activate()
  {
    for ( uint_t m = 0; m < out.size.x; m++ ) {
      float input_sum = 0;

      for ( uint_t i = 0; i < in.size.x; i++ ) {
        for ( uint_t j = 0; j < in.size.y; j++ ) {
          for ( uint_t z = 0; z < in.size.z; z++ ) {
            int n = map( point_t( i, j, z ) );
            input_sum += in( i, j, z ) * weights( m, n );
          }
        }
      }
      input_sum += biases( m );

      sum[m] = input_sum;
      out( m ) = activator_function( input_sum );
    }
  }

  void update_weight( float& weight )
  {
    
  }

  void update( tensor_t<float>& dE_dIn_next)
  {
    // calculation of deltas vector
    tensor_t<float> deltas( out.get_size() );
    for ( uint_t m = 0; m < out.get_size(); m++ ) {
      deltas( m ) = dE_dIn_next( m ) * out( m ) * ( 1 - out( m ) );
    }

    // weights update
    for ( uint_t n = 0; n < in.get_size(); n++ ) {
      for ( uint_t m = 0; m < out.get_size(); m++ ) {
        // FIXME
        weights( m, n ) -= deltas( m ) * in( n ) ;
      }
    }

    // calculation of dE_dIn vector
    for ( uint_t n = 0; n < in.get_size(); n++ ) {
      dE_dIn( n ) = 0;
      for ( uint_t m = 0; m < out.get_size(); m++ ) {
        dE_dIn( n ) += deltas( m ) * weights( m, n ); // to be used in the previous layer
      }
    }
    
  }

};

#endif
