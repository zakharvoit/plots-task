#ifndef DRAWER_H
#define DRAWER_H

#include "colorizer.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <memory>
#include <map>
#include <vector>

struct pool_canvas: Fl_Widget
{
  pool_canvas(size_t width, size_t height);
  void rescale(double left, double top, double right, double bottom);
  virtual void draw() override;
  virtual int handle(int event) override;

private:
  double calculate_eps() const;
  complex_num calculate_real_point(size_t x, size_t y) const;
  std::pair<size_t, size_t> calculate_display_point(complex_num const&) const;
  void highlight_curve_from_point(size_t x, size_t y);
  void recalculate_field();
  
  size_t width;
  size_t height;
  double x;
  double y;
  double real_width;
  double real_height;

  std::vector<complex_num> highlighted_curve;
  std::vector<Fl_Color> field;
};

struct drawer
{
  drawer(int argc, char** argv);

private:
  std::unique_ptr<Fl_Window> window;
  std::unique_ptr<pool_canvas> canvas;
};

#endif // DRAWER_H
