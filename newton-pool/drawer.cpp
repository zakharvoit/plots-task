#include "drawer.h"

#include <FL/fl_draw.H>

#include <vector>
#include <algorithm>
#include <iostream>

pool_canvas::pool_canvas(size_t width, size_t height)
  : Fl_Widget(0, 0, width, height)
  , width(width)
  , height(height)
{
  rescale(-10.0, -10.0, 20.0, 20.0);
}

void pool_canvas::rescale(double x, double y, double width, double height)
{
  this->x = x;
  this->y = y;
  this->real_width = width;
  this->real_height = height;
}

void pool_canvas::draw()
{
  double eps = calculate_eps();
  for (size_t i = 0; i < width; i++) {
    for (size_t j = 0; j < height; j++) {
      int color_id = get_color(calculate_real_point(i, j), eps);
      fl_color(color_id);
      fl_point(i, j);
    }
  }

  fl_color(FL_WHITE);
  fl_line_style(FL_SOLID, 2);
  static const int size = 10;
  for (size_t i = 0; i < highlighted_curve.size(); i++) {
    auto const& p = highlighted_curve[i];
    auto const& displayed = calculate_display_point(p);
    fl_pie(displayed.first - size / 2, displayed.second - size / 2, size, size, 0.0, 360.0);
    char buffer[256];
    sprintf(buffer, "(%.2f, %.2f)", p.x, p.y);
    auto text_size = size * 3;
    fl_draw(buffer, displayed.first - text_size / 2, displayed.second + text_size / 2, text_size, text_size, FL_ALIGN_LEFT);
    if (i < highlighted_curve.size() - 1) {
      auto const& next = calculate_display_point(highlighted_curve[i + 1]);
      fl_line(displayed.first, displayed.second, next.first, next.second);
    }
  }
}

int pool_canvas::handle(int event)
{
  switch(event) {
  case FL_PUSH:
    std::cerr << "Pushed!\n";
    highlight_curve_from_point(Fl::event_x(), Fl::event_y());
    return 1;
  }
  return 0;
}

double pool_canvas::calculate_eps() const
{
  return std::min(real_width / width, real_height / height);
}

complex_num pool_canvas::calculate_real_point(size_t x, size_t y) const
{
  return { this->x + x * real_width / width, this->y + y * real_height / height };
}

std::pair<size_t, size_t> pool_canvas::calculate_display_point(complex_num const& p) const
{
  return { size_t((p.x - this->x) * width / real_width), size_t((p.y - this->y) * height / real_height) };
}

void pool_canvas::highlight_curve_from_point(size_t x, size_t y)
{
  auto point = calculate_real_point(x, y);
  highlighted_curve = get_convergence(point, calculate_eps());
  highlighted_curve.insert(highlighted_curve.begin(), point);
  redraw();
}

drawer::drawer(int argc, char** argv)
  : window(new Fl_Window(Fl::w(), Fl::h()))
  , canvas(new pool_canvas(Fl::w(), Fl::h()))
{
  window->begin();
  window->add(canvas.get());
  window->end();
  window->show(argc, argv);
}
