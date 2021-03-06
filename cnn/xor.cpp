#include <iostream>
#include <vector>
#include <cstdlib>
#include "types.h"
#include "tensor_t.h"
#include "fc_layer_t.h"

#define EPOCHS_NUM 5000

struct case_t
{
  struct tensor_t<float> data;
  struct tensor_t<float> out;
  case_t() :
    data( 2 ),
    out( 1 )
  {}
};

void add_case(std::vector<case_t> &cases, float x1, float x2, float y)
{
  case_t c;
  c.data( 0 ) = x1;
  c.data( 1 ) = x2;
  c.out( 0 ) = y;
  cases.push_back( c );
}

void add_cases(std::vector<case_t> &cases) {
  add_case(cases, 0, 0, 0);
  add_case(cases, 0, 1, 1);
  add_case(cases, 1, 0, 1);
  add_case(cases, 1, 1, 0);
}

void train ( std::vector<fc_layer_t*>& layers, std::vector<case_t> cases ) // FIXME: const cases
{

  for (uint_t i = 0; i < EPOCHS_NUM; i++) {

    std::cout << std::endl << std::endl << "EPOCH " << i << std::endl;

    for ( uint_t j = 0; j < cases.size(); j++ ) {

      std::cout << std::endl << "case " << j << "  ";

      std::cout << "( " << cases[j].data(0) << ", " << cases[j].data(1) << " ) ->" << cases[j].out(0) << " | ";

      struct tensor_t<float> expected = cases[j].out;

      // forward pass
      for ( uint_t k = 0; k < layers.size(); k++ ) {

        // activate layer k
        if ( k == 0 ) {
          layers[k]->activate(cases[j].data);
        } else {
          layers[k]->activate(layers[k-1]->out);
        }
      }

      std::cout << layers.back()->out(0) << std::endl;

      // backpropagation
      tensor_t<float> grads = layers.back()->out - expected;

      for ( int i = (int)(layers.size() - 1); i >= 0; i-- )
      {
        if ( i == (int)layers.size() - 1 ) {
          layers[i]->update( grads );
        } else {
          layers[i]->update( layers[i + 1]->dE_dIn);
        }
      }

    } // cases loop
  } // epochs loop
}

int main()
{
  std::vector<fc_layer_t*> nn;
  fc_layer_t* layer1 = new fc_layer_t( tsize_t( 2, 1, 1 ), 5);
  fc_layer_t* layer2 = new fc_layer_t( tsize_t( 5, 1, 1 ), 1);
  nn.push_back(layer1);
  nn.push_back(layer2);

  std::vector<case_t> cases;
  add_cases(cases);

  train( nn, cases );

  delete layer1;
  delete layer2;
}
