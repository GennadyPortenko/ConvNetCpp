#include <iostream>
#include "tensor_t.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_tensor_t

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_tensor_t_constructor )
{
  tensor_t<float> t1(1, 2, 3);
  BOOST_CHECK(t1.size.x == 1);
  BOOST_CHECK(t1.size.y == 2);
  BOOST_CHECK(t1.size.z == 3);

  tensor_t<float> t2(t1);
  BOOST_CHECK(t1.size.x == 1);
  BOOST_CHECK(t1.size.y == 2);
  BOOST_CHECK(t1.size.z == 3);
}

BOOST_AUTO_TEST_CASE( test_tensor_t_get )
{
  tensor_t<float> t(2, 2, 3);
  t.data[0] = 0;
  t.data[1] = 1.1f;
  t.data[2] = 2.2f;
  t.data[3] = 3.3f;
  t.data[4] = 4.4f;
  t.data[5] = 5.5f;
  t.data[6] = 6.6f;
  t.data[7] = 7.7f;
  t.data[8] = 8.8f;
  t.data[9] = 9.9f;
  t.data[10] = 10.10f;
  t.data[11] = 11.11f;

  BOOST_CHECK(t.get(0, 0, 0) == 0);
  BOOST_CHECK(t.get(1, 0, 1) == 7.7f);
  BOOST_CHECK(t.get(0, 1, 1) == 4.4f);
  BOOST_CHECK(t.get(1, 1, 2) == 11.11f);
}

BOOST_AUTO_TEST_CASE( test_tensor_t_operatot_get )
{
  tensor_t<float> t(2, 2, 3);
  t.data[0] = 0;
  t.data[1] = 1.1f;
  t.data[2] = 2.2f;
  t.data[3] = 3.3f;
  t.data[4] = 4.4f;
  t.data[5] = 5.5f;
  t.data[6] = 6.6f;
  t.data[7] = 7.7f;
  t.data[8] = 8.8f;
  t.data[9] = 9.9f;
  t.data[10] = 10.10f;
  t.data[11] = 11.11f;

  BOOST_CHECK(t(0, 0, 0) == 0);
  BOOST_CHECK(t(1, 0, 1) == 7.7f);
  BOOST_CHECK(t(0, 1, 1) == 4.4f);
  BOOST_CHECK(t(1, 1, 2) == 11.11f);
}

BOOST_AUTO_TEST_CASE( test_tensor_t_copy_from )
{
  std::vector<std::vector<std::vector<float> > > data;

  std::vector<std::vector<float> > y;

  std::vector<float> z;
  z.push_back(0);
  z.push_back(1.1f);
  z.push_back(2.2f);
  y.push_back(z);

  z.clear();
  z.push_back(3.3f);
  z.push_back(4.4f);
  z.push_back(5.5f);
  y.push_back(z);

  data.push_back(y);
  y.clear();

  z.clear();
  z.push_back(6.6f);
  z.push_back(7.7f);
  z.push_back(8.8f);
  y.push_back(z);

  z.clear();
  z.push_back(9.9f);
  z.push_back(10.10f);
  z.push_back(11.11f);
  y.push_back(z);

  data.push_back(y);

  tensor_t<float> t(2, 2, 3);
  t.copy_from(data);

  BOOST_CHECK(t(0, 0, 0) == 0);
  BOOST_CHECK(t(1, 0, 1) == 7.7f);
  BOOST_CHECK(t(0, 1, 1) == 4.4f);
  BOOST_CHECK(t(1, 1, 2) == 11.11f);
}

