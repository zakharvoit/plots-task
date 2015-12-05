#ifndef COLORIZER_H
#define COLORIZER_H

#include <cmath>
#include <cstdlib>
#include <vector>

struct complex_num {
  double x, y;

  complex_num()
    : complex_num(0.0, 0.0) {}

  complex_num(double a, double b)
    : x(a), y(b) {}

  double abs(complex_num a) {
    return sqrt((a.x - x)*(a.x - x) + (a.y - y)*(a.y - y));
  }

  // Assume that this is not (0,0)
  complex_num get_next() {
    double denom = (x*x - y*y)*(x*x - y*y) + 4 * x*x * y*y;

    double nx = 2 * x + (x*x - y*y) / denom;
    nx /= 3.0;

    double ny = 2 * y - (2 * x * y) / denom;
    ny /= 3.0;

    return complex_num(nx, ny);
  }
};

int get_color(complex_num a, double eps);
std::vector<complex_num> get_convergence(complex_num a, double eps);

#endif // COLORIZER_H
