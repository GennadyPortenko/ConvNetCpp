#ifndef GRADIENT_T_H__
#define GRADIENT_T_H__

struct gradient_t
{
  float grad;
  float oldgrad;
  gradient_t()
  {
    grad = 0;
    oldgrad = 0;
  }
};

#endif
