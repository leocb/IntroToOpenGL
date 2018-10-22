#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define WIDTH 800
#define HEIGHT 600

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
  Camera camera(glm::vec3(0, 0, -3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
  Transform transform;

  float counter = 0.0f;

  while (!display.isClosed())
  {
    display.clear(0.0f, 0.15f, 0.3f, 1.0f);

    float sinCounter = sinf(counter);
    float cosCounter = cosf(counter);

    transform.getPos().x = sinCounter;
    transform.getPos().z = cosCounter;
    transform.getRot().z = counter;
    transform.getRot().x = counter;
    transform.getRot().y = counter;

    //transform.setScale(glm::vec3(abs(cosCounter), abs(cosCounter), abs(cosCounter)));

    shader.bind();
    texture.bind(0);
    shader.update(transform, camera);
    mesh.draw();

    display.update();

    counter += 0.01f;
  }

  return 0;
};