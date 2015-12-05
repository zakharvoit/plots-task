#include "drawer.h"
#include "colorizer.h"

#include <FL/fl_draw.H>

#include <vector>

pool_canvas::pool_canvas(size_t width, size_t height)
  : Fl_Widget(0, 0, width, height)
  , width(width)
  , height(height)
  , first_unused_color(1)
{
  rescale(-1000.0, -1000.0, 2000.0, 2000.0);
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
  // Assuming that height / real_height is the same
  double eps = width / real_width;
  for (size_t i = 0; i < width; i++) {
    for (size_t j = 0; j < height; j++) {
      int color_id = get_color({ i * real_width / width, j * real_height / height }, eps);
      fl_color(get_color_by_id(color_id));
      fl_point(i, j);
    }
  }
}

Fl_Color pool_canvas::get_color_by_id(int color_id) const
{
  auto& color = color_map[color_id];
  if (color == 0) {
    color = first_unused_color++;
  }
  return color;
}

drawer::drawer(int argc, char** argv)
  : window(new Fl_Window(WIDTH, HEIGHT))
  , canvas(new pool_canvas(WIDTH, HEIGHT))
{
  window->begin();
  window->add(canvas.get());
  window->end();
  window->show(argc, argv);
}
