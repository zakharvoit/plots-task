#ifndef DRAWER_H
#define DRAWER_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <memory>
#include <map>

struct pool_canvas: Fl_Widget
{
  pool_canvas(size_t width, size_t height);
  void rescale(double left, double top, double right, double bottom);
  void set_screen_size(size_t width, size_t height);
  virtual void draw() override;

private:
  Fl_Color get_color_by_id(int color_id) const;
  
  size_t width;
  size_t height;
  double x;
  double y;
  double real_width;
  double real_height;

  mutable std::map<int, Fl_Color> color_map;
  mutable int first_unused_color;
};

struct drawer
{
  drawer(int argc, char** argv);

private:
  static const size_t WIDTH = 1920;
  static const size_t HEIGHT = 1080;

  std::unique_ptr<Fl_Window> window;
  std::unique_ptr<pool_canvas> canvas;
};

#endif // DRAWER_H
