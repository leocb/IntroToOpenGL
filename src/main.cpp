#include <iostream>
#include <GL/glew.h>
#include "display.h"

int main(int argc, char const *argv[])
{
  Display display(800, 600, "ITMOG Awesome Window");

  while (!display.isClosed())
  {
    display.clear(0.0f, 0.15f, 0.3f, 1.0f);
    display.update();
  }

  return 0;
};