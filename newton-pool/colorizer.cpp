#include "colorizer.h"

using namespace std;

const complex_num r1 = complex_num(1.0, 0.0);
const complex_num r2 = complex_num(-1.0/2.0, -sqrt(3.0)/2.0);
const complex_num r3 = complex_num(-1.0/2.0, sqrt(3.0)/2.0);

int get_color(complex_num a, double eps) {
  if (abs(a.x) < eps && abs(a.y) < eps)
    return 0;

  complex_num prev = a, curr;

  while (true) {
    curr = prev.get_next();
    if (prev.abs(curr) < eps) {
      break;
    }
    prev = curr;
  }

  if (curr.abs(r1) < eps)
    return 1;
  if (curr.abs(r2) < eps)
    return 2;
  if (curr.abs(r3) < eps)
    return 3;

  return 0;
}

vector <complex_num> get_convergence(complex_num a, double eps){
  vector<complex_num> ans;

  if (abs(a.x) < eps && abs(a.y) < eps)
    return ans;

  complex_num prev = a, curr;

  while (true) {
    curr = prev.get_next();
    if (prev.abs(curr) < eps) {
      break;
    }
    ans.push_back(curr);
    prev = curr;
  }

  if (curr.abs(r1) < eps || curr.abs(r2) < eps || curr.abs(r3) < eps)
    return ans;

  ans.resize(0);
  return ans;
}

