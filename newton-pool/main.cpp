#include "colorizer.h"
#include "drawer.h"

int main(int argc, char** argv) {
  drawer drawer(argc, argv);
  return Fl::run();
}
