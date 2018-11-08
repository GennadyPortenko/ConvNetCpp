#include <iostream>
#include "types.h"
#include "tensor_t.h"
#include "fc_layer_t.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_tensor_t

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_fc_layer_t_constructor )
{
  tsize_t tsize = {2, 2, 3};
  fc_layer_t l(tsize, 3);

  tensor_t<float> in_t(2, 2, 3);
  in_t.data[0] = 0;
  in_t.data[1] = 1.1f;
  in_t.data[2] = 2.2f;
  in_t.data[3] = 3.3f;
  in_t.data[4] = 4.4f;
  in_t.data[5] = 5.5f;
  in_t.data[6] = 6.6f;
  in_t.data[7] = 7.7f;
  in_t.data[8] = 8.8f;
  in_t.data[9] = 9.9f;
  in_t.data[10] = 10.10f;
  in_t.data[11] = 11.11f;

  for( uint_t i = 0; i < (l.in.size.x * l.in.size.y * l.in.size.z); i++ ) {
    l.weights( i, 0, 0 ) = 0.1;
    l.weights( i, 1, 0 ) = 0.5;
    l.weights( i, 2, 0 ) = 1;
  }

  l.print_weights();

  l.activate(in_t);

  // std::cout << "in_t.data[6] = " << in_t.data[6] << std::endl;
  // std::cout << "weights( 6, 0, 0 ) = " << (*l.weights)( 6, 0, 0 ) << std::endl;

  // FIXME
  // BOOST_CHECK((*l.out)( 2, 0, 0 ) == 66 );
}

