#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"

int main(int argc, char const *argv[])
{
  Display display(800, 600, "ITMOG Awesome Window");

  Vertex vertices[] = {
      Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(0.0, 0.0)),
      Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.5, 1.0)),
      Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0, 0.0))};

  Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

  Shader shader("./res/shaders/basicShader");

  Texture texture("./res/images/bricks.jpg");

  Transform transform;

  float counter = 0.0f;

  while (!display.isClosed())
  {
    display.clear(0.0f, 0.15f, 0.3f, 1.0f);

    float sinCounter = sinf(counter);
    float cosCounter = abs(cosf(counter));

    transform.getPos().x = sinCounter;
    transform.getRot().z = counter; //cosf(counter);
    transform.setScale(glm::vec3(cosCounter, cosCounter, cosCounter));

    shader.bind();
    texture.bind(0);
    shader.update(transform);
    mesh.draw();

    display.update();

    counter += 0.01f;
  }

  return 0;
};