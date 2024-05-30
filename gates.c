#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// example data: a NAND gate
const float x[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
const float y[4] = {1, 1, 1, 0};

float sigmoid(float x) {
  return 1 / (exp(-1*x) + 1);
}

// find predicted value y_prime
// note: caller needs to free memory
float *f(float w0, float w1, float b) {
  float *yp = (float*)malloc(sizeof(float) * 4);
  for (size_t i = 0; i < 4; ++i) {
    yp[i] = sigmoid(x[i][0]*w0 + x[i][1]*w1 + b);
  }
  return yp;
}

// find cost of using a certain w
float cost(float w0, float w1, float b) {
  float *yp = f(w0, w1, b);
  float res = 0;
  for (size_t i = 0; i < 4; ++i) {
    res += pow(yp[i] - y[i], 2);
  }
  res = sqrtf(res);
  free(yp);
  return res;
}


float randf() {
  return (float)rand() / (float)(RAND_MAX);
}
int main(int argc, char**argv) {
  if (argc != 2) {
    fprintf(stderr, "ERROR: invalid argument count. Exiting.\n");
    exit(1);
  }
  srand(2024);
  float w0 = randf();
  float w1 = randf();
  float b = randf();
  float h = 1e-3;  // delta value for derivative, in theory should drive -> 0
  float r = 1e-2;  // learning rate
  float c;
  float dw0;       // partial derivative of cost function w/ respect to w0
  float dw1;       // partial derivative of cost function w/ respect to w1
  float db;        // partial derivative of cost function w/ respect to b
  int num_iter = atoi(argv[1]);
  for (size_t i = 0; i < num_iter; ++i) {
    c = cost(w0, w1, b);
    dw0 = (cost(w0 + h, w1, b) - c) / h;
    dw1 = (cost(w0, w1 + h, b) - c) / h;
    db = (cost(w0, w1, b + h) - c) / h;
    w0 -= r*dw0;
    w1 -= r*dw1;
    b -= r*db;
    printf("i = %zu: w = [%f, %f], b = %f, cost = %f\n", i, w0, w1, b, cost(w0, w1, b));
  }
  printf("=========================================================================\n");
  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      printf("%zu | %zu => %f\n", i, j, sigmoid(i*w0 + j*w1 + b));
    }
  }
}
