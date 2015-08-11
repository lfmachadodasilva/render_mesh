/*
 *  randnormal.h
 *  Water
 *
 */
#ifndef RAND_NORMAL
#define RAND_NORMAL

#include <stdlib.h>	// for rand()

static float table[][2] = {
{.00, .5},
{.01, .504},
{.02, .508},
{.03, .512},
{.06, .5239},
{.08, .5319},
{.11, .5438},
{.13, .5517},
{.16, .5636},
{.18, .5714},
{.21, .5832},
{.23, .5910},
{.26, .6026},
{.28, .6103},
{.31, .6217},
{.34, .6331},
{.36, .6406},
{.39, .6517},
{.42, .6628},
{.44, .6700},
{.47, .6808},
{.50, .6915},
{.53, .7019},
{.56, .7123},
{.59, .7224},
{.62, .7324},
{.65, .7422},
{.68, .7517},
{.71, .7611},
{.74, .7703},
{.78, .7823},
{.81, .7910},
{.85, .8023},
{.88, .8106},
{.92, .8212},
{.96, .8315}, 
{1.0, .8413},
{1.04, .8508},
{1.09, .8621},
{1.13, .8708},
{1.18, .8810},
{1.23, .8907},
{1.29, .9015},
{1.35, .9115},
{1.41, .9207},
{1.48, .9306},
{1.56, .9406},
{1.65, .9505},
{1.76, .9608},
{1.89, .9706},
{2.06, .9803},
{2.33, .9901},
{99.0, 1.0}};

float randnormal(float mean, float stdev)
{
  int i = 0;
  float u = rand() / (float) RAND_MAX;
  float n;
    
  if (u >= 0.5) {
    while (u > table[i][1]) {
      i++;
    }
  n = table[i-1][0];
  } else {
    u = 1 - u;
    while (u > table[i][1]) {
      i++;
    }
    n = 1 - table[i-1][0];
  }
  //printf("u: %f, n: %f, i: %d\n", u, n, i);	//debug

  return (mean + stdev * n);
}

#endif

